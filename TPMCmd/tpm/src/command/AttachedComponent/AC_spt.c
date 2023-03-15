/* Microsoft Reference Implementation for TPM 2.0
 *
 *  The copyright in this software is being made available under the BSD License,
 *  included below. This software may be subject to other third party and
 *  contributor rights, including patent rights, and no such rights are granted
 *  under this license.
 *
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//** Introduction
// This code in this clause is provided for testing of the TPM's command interface.
// The implementation of Attached Components is not expected to be as shown in this
// code.

//** Includes
#include "Tpm.h"
#include "AC_spt_fp.h"

// This is the simulated AC data. This should be present in an actual
// implementation.
#if 1

typedef struct
{
    TPMI_RH_AC            ac;
    TPML_AC_CAPABILITIES* acData;

} acCapabilities;

TPML_AC_CAPABILITIES acData0001 = {1, {{TPM_AT_PV1, 0x01234567}}};

acCapabilities       ac[1]      = {{0x0001, &acData0001}};

#  define NUM_AC (sizeof(ac) / sizeof(acCapabilities))

#endif  // 1 The simulated AC data

//** Functions

//*** AcToCapabilities()
// This function returns a pointer to a list of AC capabilities.
TPML_AC_CAPABILITIES* AcToCapabilities(TPMI_RH_AC component  // IN: component
)
{
    UINT32 index;
    //
    for(index = 0; index < NUM_AC; index++)
    {
        if(ac[index].ac == component)
            return ac[index].acData;
    }
    return NULL;
}

//*** AcIsAccessible()
// Function to determine if an AC handle references an actual AC
//  Return Type: BOOL
BOOL AcIsAccessible(TPM_HANDLE acHandle)
{
    // In this implementation, the AC exists if there are some capabilities to go
    // with the handle
    return AcToCapabilities(acHandle) != NULL;
}

//*** AcCapabilitiesGet()
// This function returns a list of capabilities associated with an AC
//  Return Type: TPMI_YES_NO
//      YES         if there are more handles available
//      NO          all the available handles has been returned
TPMI_YES_NO
AcCapabilitiesGet(TPMI_RH_AC            component,      // IN: the component
                  TPM_AT                type,           // IN: start capability type
                  UINT32                count,          // IN: requested number
                  TPML_AC_CAPABILITIES* capabilityList  // OUT: list of handle
)
{
    TPMI_YES_NO more = NO;
    UINT32      i;
    // Get the list of capabilities and their values associated with the AC
    TPML_AC_CAPABILITIES* capabilities;

    pAssert(HandleGetType(component) == TPM_HT_AC);
    capabilities = AcToCapabilities(component);

    // Initialize output handle list
    capabilityList->count = 0;
    if(count > MAX_AC_CAPABILITIES)
        count = MAX_AC_CAPABILITIES;

    if(capabilities != NULL)
    {
        // Find the first capability less than or equal to type
        for(i = 0; i < capabilities->count; i++)
        {
            if(capabilities->acCapabilities[i].tag >= type)
            {
                // copy the capabilities until we run out or fill the list
                for(; (capabilityList->count < count) && (i < capabilities->count);
                    i++)
                {
                    capabilityList->acCapabilities[capabilityList->count] =
                        capabilities->acCapabilities[i];
                    capabilityList->count++;
                }
                more = i < capabilities->count;
            }
        }
    }
    return more;
}

//*** AcSendObject()
// Stub to handle sending of an AC object
//  Return Type: TPM_RC
TPM_RC
AcSendObject(TPM_HANDLE      acHandle,  // IN: Handle of AC receiving object
             OBJECT*         object,    // IN: object structure to send
             TPMS_AC_OUTPUT* acDataOut  // OUT: results of operation
)
{
    NOT_REFERENCED(object);
    NOT_REFERENCED(acHandle);
    acDataOut->tag = TPM_AT_ERROR;  // indicate that the response contains an
                                    // error code
    acDataOut->data = TPM_AE_NONE;  // but there is no error.

    return TPM_RC_SUCCESS;
}
