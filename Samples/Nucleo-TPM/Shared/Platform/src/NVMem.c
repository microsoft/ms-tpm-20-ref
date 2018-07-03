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
 *  list of conditions and the following disclaimer in the documentation and/or other
 *  materials provided with the distribution.
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

//**Introduction
/*
    This file contains the NV read and write access methods.  This implementation
    uses RAM/file and does not manage the RAM/file as NV blocks.
    The implementation may become more sophisticated over time.
*/

//** Includes
#include <memory.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <wolfssl/wolfcrypt/sha512.h>
#include "StmUtil.h"
#undef INLINE
#include "stm32l4xx_hal.h"
#include "PlatformData.h"
#include "Platform_fp.h"

#define NVINTEGRITYMAGIC (0x44494E54) // TNID - TPM NV Integrity Data
typedef union
{
    struct
    {
        struct
        {
            uint32_t magic;
            time_t created;
            time_t lastWrite;
            uint32_t writeCount;
            uint8_t nvDigest[WC_SHA512_DIGEST_SIZE];
        } sig;
        uint8_t nvSignature[WC_SHA512_DIGEST_SIZE];
    } s;
    unsigned char b[0x800];
    unsigned int w[0x200];
} IntegrityData_t, *pIntegrityData_t;

__attribute__((section(".integrity"))) const IntegrityData_t nvIntegrity;
__attribute__((section(".nvfile"))) const uint8_t nvFile[NV_MEMORY_SIZE];

//**Functions
static BOOL NvHash2Data(uint8_t* data1, uint32_t data1Size, uint8_t* data2, uint32_t data2Size, uint8_t* digest)
{
    wc_Sha512 hash;
    if(wc_InitSha512(&hash))
    {
        dbgPrint("ERROR wc_InitSha512() failed.\r\n");
        return FALSE;
    }
    else if(data1 && (data1Size > 0) && wc_Sha512Update(&hash, data1, data1Size))
    {
        dbgPrint("ERROR wc_Sha512Update() failed.\r\n");
        return FALSE;
    }
    else if(data2 && (data2Size > 0) && wc_Sha512Update(&hash, data2, data2Size))
    {
        dbgPrint("ERROR wc_Sha512Update() failed.\r\n");
        return FALSE;
    }
    else if(wc_Sha512Final(&hash, (byte*)digest))
    {
        dbgPrint("ERROR wc_Sha512Final failed.\r\n");
        return FALSE;
    }
    wc_Sha512Free(&hash);
    return TRUE;
}

static BOOL NvErasePages(void* dest, uint32_t size)
{
    BOOL result = TRUE;
    uint32_t pageError = 0;
    FLASH_EraseInitTypeDef eraseInfo = {FLASH_TYPEERASE_PAGES,
                                        FLASH_BANK_1,
                                        ((uint32_t)dest - 0x08000000) / 0x800,
                                        (size + 0x7ff) / 0x800};

    // Open the memory protection
    for(uint32_t m = 0; m < 10; m++)
    {
        if((result = (HAL_FLASH_Unlock() == HAL_OK)) != FALSE)
        {
            break;
        }
        dbgPrint("WARNING HAL_FLASH_Unlock() retry %u.\r\n", (unsigned int)m);
        // Bring the flash subsystem into a defined state.
        HAL_FLASH_Lock();
        HAL_Delay(1);
    }
    if(!result)
    {
        dbgPrint("ERROR HAL_FLASH_Unlock() failed.\r\n");
        goto Cleanup;
    }

    // Erase the necessary pages
    for(uint32_t m = 0; m < 10; m++)
    {
        if((result = ((HAL_FLASHEx_Erase(&eraseInfo, &pageError) == HAL_OK) && (pageError == 0xffffffff))))
        {
            break;
        }
        dbgPrint("WARNING HAL_FLASHEx_Erase() retry %u.\r\n", (unsigned int)m);
    }
    if(!result)
    {
        dbgPrint("ERROR HAL_FLASHEx_Erase() failed.\r\n");
        goto Cleanup;
    }

Cleanup:
    HAL_FLASH_Lock();
    return result;
}

static BOOL NvFlashPages(void* dest, void* src, uint32_t size)
{
    BOOL result = TRUE;

    // Parameter check
    if(!(result = ((((uint32_t)src % sizeof(uint32_t)) == 0))))
    {
        goto Cleanup;
    }

    // Erase the required area
    if(!(result = NvErasePages(dest, size)))
    {
        goto Cleanup;
    }

    // Open the memory protection
    if(!(result = (HAL_FLASH_Unlock() == HAL_OK)))
    {
        goto Cleanup;
    }

    // Flash the src buffer 8 byte at a time and verify
    for(uint32_t n = 0; n < ((size + sizeof(uint64_t) - 1) / sizeof(uint64_t)); n++)
    {
        result = FALSE;
        for(uint32_t m = 0; m < 10; m++)
        {
            uint32_t progPtr = (uint32_t)&(((uint64_t*)dest)[n]);
            uint64_t progData = ((uint64_t*)src)[n];
            if((progData == *((uint64_t*)progPtr)) ||
               ((result = (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, progPtr, progData) == HAL_OK)) &&
                (progData == *((uint64_t*)progPtr))))
            {
                result = TRUE;
                break;
            }
            dbgPrint("WARNING HAL_FLASH_Program() retry %u.\r\n", (unsigned int)m);
        }
        if(result == FALSE)
        {
            dbgPrint("ERROR HAL_FLASH_Program() failed.\r\n");
            goto Cleanup;
        }
    }

Cleanup:
    HAL_FLASH_Lock();
    return result;
}

char* NvMakeTimeStamp(time_t time, char* nvTimeStamp, uint32_t size)
{
    struct tm* timeInfo = NULL;
    timeInfo = gmtime(&time);
    snprintf(nvTimeStamp, size, "%04d.%02d.%02d-%02d:%02d:%02dGMT",
                                 timeInfo->tm_year + 1900,
                                 timeInfo->tm_mon + 1,
                                 timeInfo->tm_mday,
                                 timeInfo->tm_hour,
                                 timeInfo->tm_min,
                                 timeInfo->tm_sec);
    return nvTimeStamp;
}
//*** _plat__NvErrors()
// This function is used by the simulator to set the error flags in the NV
// subsystem to simulate an error in the NV loading process
//LIB_EXPORT void
//_plat__NvErrors(
//    int              recoverable,
//    int            unrecoverable
//    )
//{
//    s_NV_unrecoverable = unrecoverable;
//    s_NV_recoverable = recoverable;
//}

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
// return type: int
//      0           if success
//      > 0         if receive recoverable error
//      <0          if unrecoverable error
LIB_EXPORT int
_plat__NVEnable(
    void            *platParameter  // IN: platform specific parameters
    )
{
    BOOL result = TRUE;
    uint8_t tpmUnique[WC_SHA512_DIGEST_SIZE];
    uint8_t tpmUniqueSize = 0;
    tpmUniqueSize = _plat__GetUnique(0, sizeof(tpmUnique), tpmUnique);

    // Start assuming everything is OK
    s_NV_unrecoverable = FALSE;
    s_NV_recoverable = FALSE;
    memcpy(s_NV, nvFile, sizeof(s_NV));

    // Perform integrity verification
    if((nvIntegrity.s.sig.magic != NVINTEGRITYMAGIC) || (platParameter))
    {
        // Initialize NV
        IntegrityData_t newIntegrity = {0};

        if((result = NvErasePages((uint8_t*)&nvIntegrity, sizeof(nvIntegrity))) == FALSE)
        {
            dbgPrint("ERROR NvErasePages(nvIntegrity) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if((result = NvErasePages((uint8_t*)nvFile, sizeof(nvFile))) == FALSE)
        {
            dbgPrint("ERROR NvErasePages(nvFile) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }

        newIntegrity.s.sig.magic = NVINTEGRITYMAGIC;
        newIntegrity.s.sig.created = time(NULL);
        if((result = NvHash2Data((uint8_t*)nvFile, sizeof(nvFile), NULL, 0, newIntegrity.s.sig.nvDigest)) == FALSE)
        {
            dbgPrint("WARNING NvHash2Data(nvFile) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if((result = NvHash2Data(tpmUnique, tpmUniqueSize, (uint8_t*)&newIntegrity.s.sig, sizeof(newIntegrity.s.sig), newIntegrity.s.nvSignature)) == FALSE)
        {
            dbgPrint("WARNING NvHash2Data(tpmUnique, newIntegrity) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if((result = NvFlashPages((uint8_t*)&nvIntegrity, (uint8_t*)&newIntegrity, sizeof(newIntegrity))) == FALSE)
        {
            dbgPrint("ERROR NvFlashPages(nvIntegrity) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        dbgPrint("Initialized %dkb NVFile.\r\n", sizeof(nvFile)/1024);
        memcpy(s_NV, nvFile, sizeof(s_NV));
        s_NV_recoverable = TRUE;
    }
    else
    {
        uint8_t nvDigest[WC_SHA512_DIGEST_SIZE];
        if((result = NvHash2Data(tpmUnique, tpmUniqueSize, (uint8_t*)&nvIntegrity.s.sig, sizeof(nvIntegrity.s.sig), nvDigest)) == FALSE)
        {
            dbgPrint("WARNING NvHash2Data(tpmUnique, nvIntegrity) failed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if(memcmp(nvDigest, nvIntegrity.s.nvSignature, sizeof(nvDigest)))
        {
            dbgPrint("WARNING NV signature invalid.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if((result = NvHash2Data((uint8_t*)nvFile, sizeof(nvFile), NULL, 0, nvDigest)) == FALSE)
        {
            dbgPrint("WARNING NvHash2Data(nvFile) filed.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
        if(memcmp(nvDigest, nvIntegrity.s.sig.nvDigest, sizeof(nvDigest)))
        {
            dbgPrint("WARNING NV integrity measurement invalid.\r\n");
            s_NV_unrecoverable = TRUE;
            goto Cleanup;
        }
    }
    char created[50];
    char written[50];
    dbgPrint("NVFile loaded (%dkb, %s created, %d writes, %s last)\r\n",
             sizeof(nvFile)/1024,
             NvMakeTimeStamp(nvIntegrity.s.sig.created, created, sizeof(created)),
             (int)nvIntegrity.s.sig.writeCount,
             (nvIntegrity.s.sig.lastWrite) ? NvMakeTimeStamp(nvIntegrity.s.sig.lastWrite, written, sizeof(written)) : "NEVER");

Cleanup:
    HAL_FLASH_Lock();
    if(s_NV_unrecoverable)
        return -1;
    return s_NV_recoverable;
}

//***_plat__NVDisable()
// Disable NV memory
LIB_EXPORT void
_plat__NVDisable(
    void
    )
{
    return;
}

//***_plat__IsNvAvailable()
// Check if NV is available
// return type: int
//      0               NV is available
//      1               NV is not available due to write failure
//      2               NV is not available due to rate limit
LIB_EXPORT int
_plat__IsNvAvailable(
    void
    )
{
    // NV is not available if the TPM is in failure mode
    if(!s_NvIsAvailable)
        return 1;

    return 0;
}

//***_plat__NvMemoryRead()
// Function: Read a chunk of NV memory
LIB_EXPORT void
_plat__NvMemoryRead(
    unsigned int     startOffset,   // IN: read start
    unsigned int     size,          // IN: size of bytes to read
    void            *data           // OUT: data buffer
    )
{
    assert(startOffset + size <= NV_MEMORY_SIZE);

    // Copy data from RAM
    memcpy(data, &s_NV[startOffset], size);
    return;
}

//*** _plat__NvIsDifferent()
// This function checks to see if the NV is different from the test value. This is
// so that NV will not be written if it has not changed.
// return value: int
//  TRUE(1)    the NV location is different from the test value
//  FALSE(0)   the NV location is the same as the test value
LIB_EXPORT int
_plat__NvIsDifferent(
    unsigned int     startOffset,   // IN: read start
    unsigned int     size,          // IN: size of bytes to read
    void            *data           // IN: data buffer
    )
{
    return (memcmp(&s_NV[startOffset], data, size) != 0);
}

//***_plat__NvMemoryWrite()
// This function is used to update NV memory. The "write" is to a memory copy of
// NV. At the end of the current command, any changes are written to
// the actual NV memory.
// NOTE: A useful optimization would be for this code to compare the current 
// contents of NV with the local copy and note the blocks that have changed. Then
// only write those blocks when _plat__NvCommit() is called.
LIB_EXPORT void
_plat__NvMemoryWrite(
    unsigned int     startOffset,   // IN: write start
    unsigned int     size,          // IN: size of bytes to write
    void            *data           // OUT: data buffer
    )
{
    assert(startOffset + size <= NV_MEMORY_SIZE);

    // Copy the data to the NV image
    memcpy(&s_NV[startOffset], data, size);
}

//***_plat__NvMemoryClear()
// Function is used to set a range of NV memory bytes to an implementation-dependent
// value. The value represents the erase state of the memory.
LIB_EXPORT void
_plat__NvMemoryClear(
    unsigned int     start,         // IN: clear start
    unsigned int     size           // IN: number of bytes to clear
    )
{
    assert(start + size <= NV_MEMORY_SIZE);

    // In this implementation, assume that the errase value for NV is all 1s
    memset(&s_NV[start], 0xff, size);
}

//***_plat__NvMemoryMove()
// Function: Move a chunk of NV memory from source to destination
//      This function should ensure that if there overlap, the original data is
//      copied before it is written
LIB_EXPORT void
_plat__NvMemoryMove(
    unsigned int     sourceOffset,  // IN: source offset
    unsigned int     destOffset,    // IN: destination offset
    unsigned int     size           // IN: size of data being moved
    )
{
    assert(sourceOffset + size <= NV_MEMORY_SIZE);
    assert(destOffset + size <= NV_MEMORY_SIZE);

    // Move data in RAM
    memmove(&s_NV[destOffset], &s_NV[sourceOffset], size);

    return;
}

//***_plat__NvCommit()
// Update NV chip
// return type: int
//  0       NV write success
//  non-0   NV write fail
LIB_EXPORT int
_plat__NvCommit(
    void
    )
{
    BOOL result = TRUE;
    char created[50];
    char written[50];
    IntegrityData_t newIntegrity = {0};
    uint8_t tpmUnique[WC_SHA512_DIGEST_SIZE];
    uint8_t tpmUniqueSize = 0;

    tpmUniqueSize = _plat__GetUnique(0, sizeof(tpmUnique), tpmUnique);
    memcpy(&newIntegrity, &nvIntegrity, sizeof(newIntegrity));

    if((result = NvHash2Data(s_NV, sizeof(s_NV), NULL, 0, newIntegrity.s.sig.nvDigest)) == FALSE)
    {
        dbgPrint("WARNING NvHash2Data(s_NV) failed.\r\n");
        result = FALSE;
        goto Cleanup;
    }
    if((result = NvHash2Data(tpmUnique, tpmUniqueSize, (uint8_t*)&nvIntegrity.s.sig, sizeof(nvIntegrity.s.sig), newIntegrity.s.nvSignature)) == FALSE)
    {
        dbgPrint("WARNING NvHash2Data(tpmUnique, nvIntegrity) failed.\r\n");
        result = FALSE;
        goto Cleanup;
    }

    if((memcmp(newIntegrity.s.sig.nvDigest, nvIntegrity.s.sig.nvDigest, sizeof(newIntegrity.s.sig.nvDigest))) ||
       (memcmp(newIntegrity.s.nvSignature, nvIntegrity.s.nvSignature, sizeof(newIntegrity.s.nvSignature))))
    {
        newIntegrity.s.sig.lastWrite = time(NULL);
        newIntegrity.s.sig.writeCount++;
        if((result = NvHash2Data(tpmUnique, tpmUniqueSize, (uint8_t*)&newIntegrity.s.sig, sizeof(newIntegrity.s.sig), newIntegrity.s.nvSignature)) == FALSE)
        {
            dbgPrint("WARNING NvHash2Data(tpmUnique, newIntegrity) failed.\r\n");
            result = FALSE;
            goto Cleanup;
        }
        if((result = NvFlashPages((uint8_t*)nvFile, s_NV, sizeof(s_NV))) == FALSE)
        {
            dbgPrint("ERROR NvFlashPages(nvFile) failed.\r\n");
            result = FALSE;
            goto Cleanup;
        }
        if((result = NvFlashPages((uint8_t*)&nvIntegrity, (uint8_t*)&newIntegrity, sizeof(newIntegrity))) == FALSE)
        {
            dbgPrint("ERROR NvFlashPages(nvIntegrity) failed.\r\n");
            result = FALSE;
            goto Cleanup;
        }
        dbgPrint("NVFile written (%dkb, %s created, %d writes, %s last)\r\n",
                 sizeof(nvFile)/1024,
                 NvMakeTimeStamp(nvIntegrity.s.sig.created, created, sizeof(created)),
                 (int)nvIntegrity.s.sig.writeCount,
                 (nvIntegrity.s.sig.lastWrite) ? NvMakeTimeStamp(nvIntegrity.s.sig.lastWrite, written, sizeof(written)) : "NEVER");
    }
    else
    {
        dbgPrint("NVFile unchanged (%dkb, %s created, %d writes, %s last)\r\n",
                 sizeof(nvFile)/1024,
                 NvMakeTimeStamp(nvIntegrity.s.sig.created, created, sizeof(created)),
                 (int)nvIntegrity.s.sig.writeCount,
                 (nvIntegrity.s.sig.lastWrite) ? NvMakeTimeStamp(nvIntegrity.s.sig.lastWrite, written, sizeof(written)) : "NEVER");
    }


Cleanup:
    return (result != TRUE);
}

//***_plat__SetNvAvail()
// Set the current NV state to available.  This function is for testing purpose
// only.  It is not part of the platform NV logic
LIB_EXPORT void
_plat__SetNvAvail(
    void
    )
{
    s_NvIsAvailable = TRUE;
    return;
}

//***_plat__ClearNvAvail()
// Set the current NV state to unavailable.  This function is for testing purpose
// only.  It is not part of the platform NV logic
LIB_EXPORT void
_plat__ClearNvAvail(
    void
    )
{
    s_NvIsAvailable = FALSE;
    return;
}
