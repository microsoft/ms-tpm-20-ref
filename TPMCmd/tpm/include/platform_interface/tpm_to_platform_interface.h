
// This file represents the functional interface that all platform libraries must
// provide because they are called by the Core TPM library.
#ifndef _TPM_TO_PLATFORM_INTERFACE_H_
#define _TPM_TO_PLATFORM_INTERFACE_H_

// need to read configuration for ACT_SUPPORT flag check below
#include <TpmConfiguration/TpmBuildSwitches.h>
#include <TpmConfiguration/TpmProfile.h>
#include <stddef.h>

//** From Cancel.c

//***_plat__IsCanceled()
// Check if the cancel flag is set
//  Return Type: int
//      TRUE(1)         if cancel flag is set
//      FALSE(0)        if cancel flag is not set
LIB_EXPORT int _plat__IsCanceled(void);

//***_plat__TimerRead()
// This function provides access to the tick timer of the platform. The TPM code
// uses this value to drive the TPM Clock.
//
// The tick timer is supposed to run when power is applied to the device. This timer
// should not be reset by time events including _TPM_Init. It should only be reset
// when TPM power is re-applied.
//
// If the TPM is run in a protected environment, that environment may provide the
// tick time to the TPM as long as the time provided by the environment is not
// allowed to go backwards. If the time provided by the system can go backwards
// during a power discontinuity, then the _plat__Signal_PowerOn should call
// _plat__TimerReset().
LIB_EXPORT uint64_t _plat__TimerRead(void);

//*** _plat__TimerWasReset()
// This function is used to interrogate the flag indicating if the tick timer has
// been reset.
//
// If the resetFlag parameter is SET, then the flag will be CLEAR before the
// function returns.
LIB_EXPORT int _plat__TimerWasReset(void);

//*** _plat__TimerWasStopped()
// This function is used to interrogate the flag indicating if the tick timer has
// been stopped. If so, this is typically a reason to roll the nonce.
//
// This function will CLEAR the s_timerStopped flag before returning. This provides
// functionality that is similar to status register that is cleared when read. This
// is the model used here because it is the one that has the most impact on the TPM
// code as the flag can only be accessed by one entity in the TPM. Any other
// implementation of the hardware can be made to look like a read-once register.
LIB_EXPORT int _plat__TimerWasStopped(void);

//***_plat__ClockRateAdjust()
// Adjust the clock rate
// the old function name is ClockAdjustRate, and took a value which was an absolute
// number of ticks.
//
// ClockRateAdjust uses predefined signal values and encapsulates the platform
// specifics regarding the number of ticks the underlying clock is running at.
//
// The adjustment must be one of these values. A COARSE adjustment is 1%, MEDIUM
// is 0.1%, and FINE is the smallest amount supported by the platform.  The
// total (cumulative) adjustment is limited to ~15% total.  Attempts to adjust
// the clock further are silently ignored as are any invalid values.  These
// values are defined here to insulate them from spec changes and to avoid
// needing visibility to the doc-generated structure headers.
typedef enum _plat__ClockAdjustStep
{
    PLAT_TPM_CLOCK_ADJUST_COARSE_SLOWER = -3,
    PLAT_TPM_CLOCK_ADJUST_MEDIUM_SLOWER = -2,
    PLAT_TPM_CLOCK_ADJUST_FINE_SLOWER   = -1,
    PLAT_TPM_CLOCK_ADJUST_FINE_FASTER   = 1,
    PLAT_TPM_CLOCK_ADJUST_MEDIUM_FASTER = 2,
    PLAT_TPM_CLOCK_ADJUST_COARSE_FASTER = 3
} _plat__ClockAdjustStep;
LIB_EXPORT void _plat__ClockRateAdjust(_plat__ClockAdjustStep adjustment);

//** From DebugHelpers.c

#if CERTIFYX509_DEBUG

//*** DebugFileInit()
// This function opens the file used to hold the debug data.
//  Return Type: int
//   0        success
//  != 0          error
int DebugFileInit(void);

//*** DebugDumpBuffer()
void DebugDumpBuffer(int size, unsigned char* buf, const char* identifier);
#endif  // CERTIFYX509_DEBUG

//** From Entropy.c

//*** _plat__GetEntropy()
// This function is used to get available hardware entropy. In a hardware
// implementation of this function, there would be no call to the system
// to get entropy.
//  Return Type: int32_t
//  < 0        hardware failure of the entropy generator, this is sticky
// >= 0        the returned amount of entropy (bytes)
//
LIB_EXPORT int32_t _plat__GetEntropy(unsigned char* entropy,  // output buffer
                                     uint32_t       amount    // amount requested
);

//** From LocalityPlat.c

//***_plat__LocalityGet()
// Get the most recent command locality in locality value form.
// This is an integer value for locality and not a locality structure
// The locality can be 0-4 or 32-255. 5-31 is not allowed.
LIB_EXPORT unsigned char _plat__LocalityGet(void);

//***_plat__NVEnable()
// Enable NV memory.
//
// This version just pulls in data from a file. In a real TPM, with NV on chip,
// this function would verify the integrity of the saved context. If the NV
// memory was not on chip but was in something like RPMB, the NV state would be
// read in, decrypted and integrity checked.
//
// The recovery from an integrity failure depends on where the error occurred. It
// it was in the state that is discarded by TPM Reset, then the error is
// recoverable if the TPM is reset. Otherwise, the TPM must go into failure mode.
//
//  Return Type: int
//      0           if success
//      >0          if recoverable error
//      <0          if unrecoverable error
LIB_EXPORT int _plat__NVEnable(
    void*  platParameter,  // platform specific parameter
    size_t paramSize       // size of parameter. If size == 0, then
                           // parameter is a sizeof(void*) scalar and should
                           // be cast to an integer (intptr_t), not dereferenced.
);

//***_plat__GetNvReadyState()
// Check if NV is available
//  Return Type: int
//      0               NV is available
//      1               NV is not available due to write failure
//      2               NV is not available due to rate limit
#define NV_READY        0
#define NV_WRITEFAILURE 1
#define NV_RATE_LIMIT   2
LIB_EXPORT int _plat__GetNvReadyState(void);

//***_plat__NvMemoryRead()
// Function: Read a chunk of NV memory
//  Return Type: int
//      TRUE(1)         offset and size is within available NV size
//      FALSE(0)        otherwise; also trigger failure mode
LIB_EXPORT int _plat__NvMemoryRead(unsigned int startOffset,  // IN: read start
                                   unsigned int size,  // IN: size of bytes to read
                                   void*        data   // OUT: data buffer
);

//*** _plat__NvGetChangedStatus()
// This function checks to see if the NV is different from the test value. This is
// so that NV will not be written if it has not changed.
//  Return Type: int
//      NV_HAS_CHANGED(1)       the NV location is different from the test value
//      NV_IS_SAME(0)           the NV location is the same as the test value
//      NV_INVALID_LOCATION(-1) the NV location is invalid; also triggers failure mode
#define NV_HAS_CHANGED      (1)
#define NV_IS_SAME          (0)
#define NV_INVALID_LOCATION (-1)
LIB_EXPORT int _plat__NvGetChangedStatus(
    unsigned int startOffset,  // IN: read start
    unsigned int size,         // IN: size of bytes to read
    void*        data          // IN: data buffer
);

//***_plat__NvMemoryWrite()
// This function is used to update NV memory. The "write" is to a memory copy of
// NV. At the end of the current command, any changes are written to
// the actual NV memory.
// NOTE: A useful optimization would be for this code to compare the current
// contents of NV with the local copy and note the blocks that have changed. Then
// only write those blocks when _plat__NvCommit() is called.
//  Return Type: int
//      TRUE(1)         offset and size is within available NV size
//      FALSE(0)        otherwise; also trigger failure mode
LIB_EXPORT int _plat__NvMemoryWrite(unsigned int startOffset,  // IN: write start
                                    unsigned int size,  // IN: size of bytes to write
                                    void*        data   // OUT: data buffer
);

//***_plat__NvMemoryClear()
// Function is used to set a range of NV memory bytes to an implementation-dependent
// value. The value represents the erase state of the memory.
LIB_EXPORT int _plat__NvMemoryClear(unsigned int startOffset,  // IN: clear start
                                    unsigned int size  // IN: number of bytes to clear
);

//***_plat__NvMemoryMove()
// Function: Move a chunk of NV memory from source to destination
//      This function should ensure that if there overlap, the original data is
//      copied before it is written
LIB_EXPORT int _plat__NvMemoryMove(unsigned int sourceOffset,  // IN: source offset
                                   unsigned int destOffset,  // IN: destination offset
                                   unsigned int size  // IN: size of data being moved
);

//***_plat__NvCommit()
// This function writes the local copy of NV to NV for permanent store. It will write
// NV_MEMORY_SIZE bytes to NV. If a file is use, the entire file is written.
//  Return Type: int
//  0       NV write success
//  non-0   NV write fail
LIB_EXPORT int _plat__NvCommit(void);

//***_plat__TearDown
// notify platform that TPM_TearDown was called so platform can cleanup or
// zeroize anything in the Platform.  This should zeroize NV as well.
LIB_EXPORT void _plat__TearDown();

//** From PlatformACT.c

#if ACT_SUPPORT
//*** _plat__ACT_GetImplemented()
// This function tests to see if an ACT is implemented. It is a belt and suspenders
// function because the TPM should not be calling to manipulate an ACT that is not
// implemented. However, this could help the simulator code which doesn't necessarily
// know if an ACT is implemented or not.
LIB_EXPORT int _plat__ACT_GetImplemented(uint32_t act);

//*** _plat__ACT_GetRemaining()
// This function returns the remaining time. If an update is pending, 'newValue' is
// returned. Otherwise, the current counter value is returned. Note that since the
// timers keep running, the returned value can get stale immediately. The actual count
// value will be no greater than the returned value.
LIB_EXPORT uint32_t _plat__ACT_GetRemaining(uint32_t act  //IN: the ACT selector
);

//*** _plat__ACT_GetSignaled()
LIB_EXPORT int _plat__ACT_GetSignaled(uint32_t act  //IN: number of ACT to check
);

//*** _plat__ACT_SetSignaled()
LIB_EXPORT void _plat__ACT_SetSignaled(uint32_t act, int on);

//*** _plat__ACT_UpdateCounter()
// This function is used to write the newValue for the counter. If an update is
// pending, then no update occurs and the function returns FALSE. If 'setSignaled'
// is TRUE, then the ACT signaled state is SET and if 'newValue' is 0, nothing
// is posted.
LIB_EXPORT int _plat__ACT_UpdateCounter(uint32_t act,      // IN: ACT to update
                                        uint32_t newValue  // IN: the value to post
);

//***_plat__ACT_EnableTicks()
// This enables and disables the processing of the once-per-second ticks. This should
// be turned off ('enable' = FALSE) by _TPM_Init and turned on ('enable' = TRUE) by
// TPM2_Startup() after all the initializations have completed.
LIB_EXPORT void _plat__ACT_EnableTicks(int enable);

//***_plat__ACT_Initialize()
// This function initializes the ACT hardware and data structures
LIB_EXPORT int _plat__ACT_Initialize(void);

#endif  // ACT_SUPPORT

//** From PowerPlat.c

//*** _plat__WasPowerLost()
// Test whether power was lost before a _TPM_Init.
//
// This function will clear the "hardware" indication of power loss before return.
// This means that there can only be one spot in the TPM code where this value
// gets read. This method is used here as it is the most difficult to manage in the
// TPM code and, if the hardware actually works this way, it is hard to make it
// look like anything else. So, the burden is placed on the TPM code rather than the
// platform code
//  Return Type: int
//      TRUE(1)         power was lost
//      FALSE(0)        power was not lost
LIB_EXPORT int _plat__WasPowerLost(void);

//** From PPPlat.c

//***_plat__PhysicalPresenceAsserted()
// Check if physical presence is signaled
//  Return Type: int
//      TRUE(1)         if physical presence is signaled
//      FALSE(0)        if physical presence is not signaled
LIB_EXPORT int _plat__PhysicalPresenceAsserted(void);

//***_plat__Fail()
// This is the platform depended failure exit for the TPM.
LIB_EXPORT NORETURN void _plat__Fail(void);

//** From Unique.c

#if VENDOR_PERMANENT_AUTH_ENABLED == YES
//** _plat__GetUnique()
// This function is used to access the platform-specific unique values.
// This function places the unique value in the provided buffer ('b')
// and returns the number of bytes transferred. The function will not
// copy more data than 'bSize'.
// zero indicates value does not exist or an error occurred.
//
// 'which' indicates the unique value to return:
// 0 = RESERVED, do not use
// 1 = the VENDOR_PERMANENT_AUTH_HANDLE authorization value for this device
LIB_EXPORT uint32_t _plat__GetUnique(uint32_t       which,
                                     uint32_t       bSize,  // size of the buffer
                                     unsigned char* b       // output buffer
);
#endif

//** _plat__GetPlatformManufactureData
// This function allows the platform to provide a small amount of data to be
// stored as part of the TPM's PERSISTENT_DATA structure during manufacture.  Of
// course the platform can store data separately as well, but this allows a
// simple platform implementation to store a few bytes of data without
// implementing a multi-layer storage system.  This function is called on
// manufacture and CLEAR.  The buffer will contain the last value provided
// to the Core library.
LIB_EXPORT void _plat__GetPlatformManufactureData(uint8_t* pPlatformPersistentData,
                                                  uint32_t bufferSize);

// return the 4 character Manufacturer Capability code.  This
// should come from the platform library since that is provided by the manufacturer
LIB_EXPORT uint32_t _plat__GetManufacturerCapabilityCode(void);

// return the 4 character VendorStrings for Capabilities.
// Index is ONE-BASED, and may be in the range [1,4] inclusive.
// Any other index returns all zeros. The return value will be interpreted
// as an array of 4 ASCII characters (with no null terminator)
LIB_EXPORT uint32_t _plat__GetVendorCapabilityCode(int index);

// return the most-significant 32-bits of the TPM Firmware Version reported by
// getCapability.
LIB_EXPORT uint32_t _plat__GetTpmFirmwareVersionHigh(void);

// return the least-significant 32-bits of the TPM Firmware Version reported by
// getCapability.
LIB_EXPORT uint32_t _plat__GetTpmFirmwareVersionLow(void);

// return the TPM Firmware's current SVN.
LIB_EXPORT uint16_t _plat__GetTpmFirmwareSvn(void);

// return the maximum value that the TPM Firmware SVN may take.
LIB_EXPORT uint16_t _plat__GetTpmFirmwareMaxSvn(void);

#if SVN_LIMITED_SUPPORT
//***_plat__GetTpmFirmwareSvnSecret()
// Function: Obtain a Firmware SVN Secret bound to the given SVN. Fails if the
// given SVN is greater than the firmware's current SVN.
// size must equal PRIMARY_SEED_SIZE.
// Return Type: int
//  0           success
//  != 0        error
LIB_EXPORT int _plat__GetTpmFirmwareSvnSecret(
    uint16_t  svn,              // IN: specified SVN
    uint16_t  secret_buf_size,  // IN: size of secret buffer
    uint8_t*  secret_buf,       // OUT: secret buffer
    uint16_t* secret_size       // OUT: secret buffer
);
#endif  // SVN_LIMITED_SUPPORT

#if FW_LIMITED_SUPPORT
//***_plat__GetTpmFirmwareSecret()
// Function: Obtain a Firmware Secret bound to the current firmware image.
// Return Type: int
//  0           success
//  != 0        error
LIB_EXPORT int _plat__GetTpmFirmwareSecret(
    uint16_t  secret_buf_size,  // IN: size of secret buffer
    uint8_t*  secret_buf,       // OUT: secret buffer
    uint16_t* secret_size       // OUT: secret buffer
);
#endif  // FW_LIMITED_SUPPORT

// return the TPM Type returned by TPM_PT_VENDOR_TPM_TYPE
LIB_EXPORT uint32_t _plat__GetTpmType(void);

// platform PCR initialization functions
#include <platform_interface/prototypes/platform_pcr_fp.h>

#endif  // _TPM_TO_PLATFORM_INTERFACE_H_
