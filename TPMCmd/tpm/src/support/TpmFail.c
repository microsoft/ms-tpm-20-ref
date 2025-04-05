//** Includes, Defines, and Types
#define TPM_FAIL_C
#include "Tpm.h"

// On MS C compiler, can save the alignment state and set the alignment to 1 for
// the duration of the TpmTypes.h include.  This will avoid a lot of alignment
// warnings from the compiler for the unaligned structures. The alignment of the
// structures is not important as this function does not use any of the structures
// in TpmTypes.h and only include it for the #defines of the capabilities,
// properties, and command code values.
#include "TpmTypes.h"

//** Typedefs
// These defines are used primarily for sizing of the local response buffer.
typedef struct
{
    TPM_ST tag;
    UINT32 size;
    TPM_RC code;
} HEADER;

typedef struct
{
    BYTE tag[sizeof(TPM_ST)];
    BYTE size[sizeof(UINT32)];
    BYTE code[sizeof(TPM_RC)];
} PACKED_HEADER;

typedef struct
{
    BYTE size[sizeof(UINT16)];
    struct
    {
        BYTE function[sizeof(UINT32)];
        BYTE line[sizeof(UINT32)];
        BYTE code[sizeof(UINT32)];
    } values;
    BYTE returnCode[sizeof(TPM_RC)];
} GET_TEST_RESULT_PARAMETERS;

typedef struct
{
    BYTE moreData[sizeof(TPMI_YES_NO)];
    BYTE capability[sizeof(TPM_CAP)];  // Always TPM_CAP_TPM_PROPERTIES
    BYTE tpmProperty[sizeof(TPML_TAGGED_TPM_PROPERTY)];
} GET_CAPABILITY_PARAMETERS;

typedef struct
{
    BYTE header[sizeof(PACKED_HEADER)];
    BYTE getTestResult[sizeof(GET_TEST_RESULT_PARAMETERS)];
} TEST_RESPONSE;

typedef struct
{
    BYTE header[sizeof(PACKED_HEADER)];
    BYTE getCap[sizeof(GET_CAPABILITY_PARAMETERS)];
} CAPABILITY_RESPONSE;

typedef union
{
    BYTE test[sizeof(TEST_RESPONSE)];
    BYTE cap[sizeof(CAPABILITY_RESPONSE)];
} RESPONSES;

// Buffer to hold the responses. This may be a little larger than
// required due to padding that a compiler might add.
// Note: This is not in Global.c because of the specialized data definitions above.
// Since the data contained in this structure is not relevant outside of the
// execution of a single command (when the TPM is in failure mode. There is no
// compelling reason to move all the typedefs to Global.h and this structure
// to Global.c.
#ifndef __IGNORE_STATE__  // Don't define this value
static BYTE response[sizeof(RESPONSES)];
#endif

//** Local Functions

//*** MarshalUint16()
// Function to marshal a 16 bit value to the output buffer.
static INT32 MarshalUint16(UINT16 integer, BYTE** buffer)
{
    UINT16_TO_BYTE_ARRAY(integer, *buffer);
    *buffer += 2;
    return 2;
}

//*** MarshalUint32()
// Function to marshal a 32 bit value to the output buffer.
static INT32 MarshalUint32(UINT32 integer, BYTE** buffer)
{
    UINT32_TO_BYTE_ARRAY(integer, *buffer);
    *buffer += 4;
    return 4;
}

//** Public Functions

//*** SetForceFailureMode()
// This function is called by the simulator to enable failure mode testing.
#if ALLOW_FORCE_FAILURE_MODE
LIB_EXPORT void SetForceFailureMode(void)
{
    g_forceFailureMode = TRUE;
    return;
}
#endif  // ALLOW_FORCE_FAILURE_MODE

//*** TpmFail()
// This function is called by TPM.lib when a failure occurs. It will set up the
// failure values to be returned on TPM2_GetTestResult().
NORETURN void TpmFail(
#if FAIL_TRACE
    const char* function,
    int         line,
#else
    uint64_t locationCode,
#endif
    int failureCode)
{
    // Save the values that indicate where the error occurred.
    // On a 64-bit machine, this may truncate the address of the string
    // of the function name where the error occurred.
#if FAIL_TRACE
    s_failFunctionName = function;
    s_failFunction     = (UINT32)(ptrdiff_t)function;
    s_failLine         = line;
#else
    s_failFunction = (UINT32)(locationCode >> 32);
    s_failLine     = (UINT32)(locationCode);
#endif
    s_failCode = failureCode;

    // We are in failure mode
    g_inFailureMode = TRUE;

    // Notify the platform that we hit a failure.
    //
    // In the LONGJMP case, the reference platform code is expected to long-jmp
    // back to the ExecuteCommand call and output a failure response.
    //
    // In the NO_LONGJMP case, this is a notification to the platform, and the
    // platform may take any (implementation-defined) behavior, including no-op,
    // debugging, or whatever. The core library is expected to surface the failure
    // back to ExecuteCommand through error propagation and return an appropriate
    // failure reply.
    _plat__Fail();
}

//*** TpmFailureMode(
// This function is called by the interface code when the platform is in failure
// mode.
void TpmFailureMode(uint32_t        inRequestSize,    // IN: command buffer size
                    unsigned char*  inRequest,        // IN: command buffer
                    uint32_t*       outResponseSize,  // OUT: response buffer size
                    unsigned char** outResponse       // OUT: response buffer
)
{
    UINT32 marshalSize;
    UINT32 capability;
    HEADER header;  // unmarshaled command header
    UINT32 pt;      // unmarshaled property type
    UINT32 count;   // unmarshaled property count
    UINT8* buffer = inRequest;

    // If there is no command buffer or it is too small,
    // then just return TPM_RC_FAILURE
    if(inRequestSize < 10 || inRequest == NULL)
        goto FailureModeReturn;
    // If the header is not correct for TPM2_GetCapability() or
    // TPM2_GetTestResult() then just return the in failure mode response;
    header.tag = BYTE_ARRAY_TO_UINT16(buffer);
    header.size = BYTE_ARRAY_TO_UINT32(buffer + 2);
    header.code = BYTE_ARRAY_TO_UINT32(buffer + 6);
    buffer += 10;
    if(header.tag != TPM_ST_NO_SESSIONS || header.size != inRequestSize)
        goto FailureModeReturn;
    switch(header.code)
    {
        case TPM_CC_GetTestResult:
            // make sure that the command size is correct
            if(header.size != 10)
                goto FailureModeReturn;
            buffer      = &response[10];
            marshalSize = MarshalUint16(3 * sizeof(UINT32), &buffer);
            marshalSize += MarshalUint32(s_failFunction, &buffer);
            marshalSize += MarshalUint32(s_failLine, &buffer);
            marshalSize += MarshalUint32(s_failCode, &buffer);
            if(s_failCode == FATAL_ERROR_NV_UNRECOVERABLE)
                marshalSize += MarshalUint32(TPM_RC_NV_UNINITIALIZED, &buffer);
            else
                marshalSize += MarshalUint32(TPM_RC_FAILURE, &buffer);
            break;
        case TPM_CC_GetCapability:
            // make sure that the size of the command is exactly the size
            // returned for the capability, property, and count
            if(header.size != (10 + (3 * sizeof(UINT32))))
                goto FailureModeReturn;
            capability = BYTE_ARRAY_TO_UINT32(buffer);
            pt = BYTE_ARRAY_TO_UINT32(buffer + 4);
            count = BYTE_ARRAY_TO_UINT32(buffer + 8);
            // also verify that this is requesting TPM properties
            if(capability != TPM_CAP_TPM_PROPERTIES)
                goto FailureModeReturn;

            if(count > 0)
                count = 1;
            else if(pt > TPM_PT_FIRMWARE_VERSION_2)
                count = 0;
            if(pt < TPM_PT_MANUFACTURER)
                pt = TPM_PT_MANUFACTURER;
            // set up for return
            buffer = &response[10];
            // if the request was for a PT less than the last one
            // then we indicate more, otherwise, not.
            if(pt < TPM_PT_FIRMWARE_VERSION_2)
                *buffer++ = YES;
            else
                *buffer++ = NO;
            marshalSize = 1;

            // indicate the capability type
            marshalSize += MarshalUint32(capability, &buffer);
            // indicate the number of values that are being returned (0 or 1)
            marshalSize += MarshalUint32(count, &buffer);
            // indicate the property
            marshalSize += MarshalUint32(pt, &buffer);

            if(count > 0)
                switch(pt)
                {
                    case TPM_PT_MANUFACTURER:
                        // the vendor ID unique to each TPM manufacturer
                        pt = _plat__GetManufacturerCapabilityCode();
                        break;

                    case TPM_PT_VENDOR_STRING_1:
                        // the first four characters of the vendor ID string
                        pt = _plat__GetVendorCapabilityCode(1);
                        break;

                    case TPM_PT_VENDOR_STRING_2:
                        // the second four characters of the vendor ID string
                        pt = _plat__GetVendorCapabilityCode(2);
                        break;

                    case TPM_PT_VENDOR_STRING_3:
                        // the third four characters of the vendor ID string
                        pt = _plat__GetVendorCapabilityCode(3);
                        break;

                    case TPM_PT_VENDOR_STRING_4:
                        // the fourth four characters of the vendor ID string
                        pt = _plat__GetVendorCapabilityCode(4);
                        break;

                    case TPM_PT_VENDOR_TPM_TYPE:
                        // vendor-defined value indicating the TPM model
                        // We just make up a number here
                        pt = _plat__GetTpmType();
                        break;

                    case TPM_PT_FIRMWARE_VERSION_1:
                        // the more significant 32-bits of a vendor-specific value
                        // indicating the version of the firmware
                        pt = _plat__GetTpmFirmwareVersionHigh();
                        break;

                    default:  // TPM_PT_FIRMWARE_VERSION_2:
                        // the less significant 32-bits of a vendor-specific value
                        // indicating the version of the firmware
                        pt = _plat__GetTpmFirmwareVersionLow();
                        break;
                }
            marshalSize += MarshalUint32(pt, &buffer);
            break;
        default:  // default for switch (cc)
            goto FailureModeReturn;
    }
    // Now do the header
    buffer      = response;
    marshalSize = marshalSize + 10;              // Add the header size to the
                                                 // stuff already marshaled
    MarshalUint16(TPM_ST_NO_SESSIONS, &buffer);  // structure tag
    MarshalUint32(marshalSize, &buffer);         // responseSize
    MarshalUint32(TPM_RC_SUCCESS, &buffer);      // response code

    *outResponseSize = marshalSize;
    *outResponse     = (unsigned char*)&response;
    return;
FailureModeReturn:
    buffer      = response;
    marshalSize = MarshalUint16(TPM_ST_NO_SESSIONS, &buffer);
    marshalSize += MarshalUint32(10, &buffer);
    marshalSize += MarshalUint32(TPM_RC_FAILURE, &buffer);
    *outResponseSize = marshalSize;
    *outResponse     = (unsigned char*)response;
    return;
}

//*** UnmarshalFail()
// This is a stub that is used to catch an attempt to unmarshal an entry
// that is not defined. Don't ever expect this to be called but...
void UnmarshalFail(void* type, BYTE** buffer, INT32* size)
{
    NOT_REFERENCED(type);
    NOT_REFERENCED(buffer);
    NOT_REFERENCED(size);
    FAIL(FATAL_ERROR_INTERNAL);
}
