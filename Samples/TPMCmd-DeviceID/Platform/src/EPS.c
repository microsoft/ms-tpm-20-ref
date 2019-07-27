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

#if !defined(_MSC_VER) && defined(USE_PLATFORM_EPS)
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <unistd.h>
#include <net/if.h> 
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <libudev.h>
#include <sys/stat.h>

#include "Tpm.h"
#include "Platform_fp.h"

#define DEVICEID_SIZE 48

// This extension is needed as TPM2B_STRING only define TPM2B variable when #GLOBAL_C is defined.
#define TPM2B_STRING_EXTENSION(name, value)                 \
TPM2B_STRING(name, value);                                  \
const TPM2B_##name##_ name##_ = STRING_INITIALIZER(value);  \
const TPM2B *name = &name##_.b

TPM2B_STRING_EXTENSION(EPS_CREATION, "EPS Creation");

// Definition for Device ID value.
TPM2B_TYPE(DEVICEID, DEVICEID_SIZE);
const unsigned int MAC_ADDRESS_MAXIMUM_SIZE = 6;

// This value is used to store device id derived from hardware parameters.
static TPM2B_DEVICEID deviceID = {0};
static BOOL isDeviceIDSet = FALSE;

// Read mac address of the device and copy over to the given buffer.
// Returns 0 for success and -1 for error.

static int GetMacAddress()
{
    struct ifreq interfaceRequest = {0};
    struct ifconf interfaceConfiguration = {0};
    char interfaceConfigurationBuffer[1024] = {0};

    int inetSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (inetSocket == -1)
    {
        return -1;
    }

    interfaceConfiguration.ifc_len = sizeof(interfaceConfigurationBuffer);
    interfaceConfiguration.ifc_buf = interfaceConfigurationBuffer;
    if((ioctl(inetSocket, SIOCGIFCONF, &interfaceConfiguration)) == -1)
    {
        close(inetSocket);
        return -1;
    }

    struct ifreq* intefaceRequestStart = interfaceConfiguration.ifc_req;
    const struct ifreq* const interfaceRequestEnd = intefaceRequestStart + (interfaceConfiguration.ifc_len / sizeof(struct ifreq));

    int32_t result = -1;

    for (; intefaceRequestStart != interfaceRequestEnd; ++intefaceRequestStart)
    {
        strcpy(interfaceRequest.ifr_name, intefaceRequestStart->ifr_name);
        if (ioctl(inetSocket, SIOCGIFFLAGS, &interfaceRequest) == 0)
        {
            // don't count loopback
            if ((interfaceRequest.ifr_flags & IFF_LOOPBACK) == 0)
            {
                if (ioctl(inetSocket, SIOCGIFHWADDR, &interfaceRequest) == 0)
                {
                    result = 0;
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    if (result == 0)
    {
        unsigned int size = deviceID.t.size <= MAC_ADDRESS_MAXIMUM_SIZE ? deviceID.t.size : MAC_ADDRESS_MAXIMUM_SIZE;
        memcpy(deviceID.t.buffer, interfaceRequest.ifr_hwaddr.sa_data, size);
    }

    close(inetSocket);
    return result;
}

// Read primary harddisk/emmc disk serial id from device and copy over to the given buffer.
// Returns 0 for success and -1 for error.

static int GetDiskSerialNumber()
{
    struct udev *ud = NULL;
    struct stat statbuf;
    struct udev_device *device = NULL;
    struct udev_list_entry *entry = NULL;
    int result = -1;

    ud = udev_new();
    if (NULL == ud)
    {
        return result;
    }
    else
    {

        const unsigned int diskDeviceNamesSize = 2;
        const char *diskDeviceNames[] = {
            "/dev/sda", // primary hard disk.
            "/dev/mmcblk0" // primary eMMC disk.
        };

        unsigned int i = 0;
        while (i < diskDeviceNamesSize)
        {
            if (0 == stat(diskDeviceNames[i], &statbuf))
            {
                break;
            }
            i++;
        }

        if (i == diskDeviceNamesSize)
        {
            goto Cleanup;
        }

        const char blockDeviceType = 'b';
        device = udev_device_new_from_devnum(ud, blockDeviceType, statbuf.st_rdev);
        if (NULL == device)
        {
            goto Cleanup;
        }
        else
        {
            entry = udev_device_get_properties_list_entry(device);
            while (NULL != entry)
            {
                if (0 == strcmp(udev_list_entry_get_name(entry),
                    "ID_SERIAL")) 
                {
                    break;
                }

                entry = udev_list_entry_get_next(entry);
            }

            if(entry == NULL)
            {
                goto Cleanup;
            }

            const char* serialNumber = udev_list_entry_get_value(entry);
            size_t serialNumberLength = strlen(serialNumber);

            size_t dataCopyLength = deviceID.t.size - MAC_ADDRESS_MAXIMUM_SIZE;
            if (serialNumberLength < dataCopyLength)
            {
                dataCopyLength = serialNumberLength;
            }

            memcpy(deviceID.t.buffer, serialNumber, dataCopyLength);

            result = 0;
        }

Cleanup:
        if(device)
        {
            udev_device_unref(device);
        }

        (void)udev_unref(ud);
        return result;
    }
}

#if defined(SIMULATION) && (SIMULATION == YES)
// Get device id from hardware parameters.
// CAUTION: Primary seeds derived from device unique IDs are guaranteed to remain the same as long as the reference
//  implementation manufactures its NV state on the same device. Since this implementation of GetDeviceID() relies 
//  solely on publicly accessible values (storage device serial numbers and networking card MAC address), it can 
//  only be used for the simulation purposes, as it cannot be used to produce a secret value.
// pre-requisites - assumes that MAC address or disk device (i.e. /dev/sda or /dev/mmcblk0) present on the device.
TPM_RC GetDeviceID()
{
    if(isDeviceIDSet == FALSE)
    {
        if(GetMacAddress() == 0)
        {
            isDeviceIDSet = TRUE;
        }

        if(GetDiskSerialNumber() == 0)
        {
            isDeviceIDSet = TRUE;
        }

        if(isDeviceIDSet == FALSE)
        {
            return TPM_RC_FAILURE;
        }
    }

    return TPM_RC_SUCCESS;
}
#endif

void GetSeed(UINT16 size, uint8_t *seed, const TPM2B *purpose)
{
    RAND_STATE rand;

    TPM_RC result = GetDeviceID();
    if(result != TPM_RC_SUCCESS)
    {
        LOG_FAILURE(FATAL_ERROR_INTERNAL);
        return;
    }
    
    result = DRBG_InstantiateSeeded(&rand.drbg, &deviceID.b, purpose, NULL, NULL);
    if(result != TPM_RC_SUCCESS)
    {
        LOG_FAILURE(FATAL_ERROR_INTERNAL);
        return;
    }

    if(DRBG_Generate(&rand, seed, size) == 0)
    {
        LOG_FAILURE(FATAL_ERROR_INTERNAL);
    }
    return;
}

void
_plat__GetEPS(
    UINT16 size,
    uint8_t *seed
    )
{
    // Ignore GCC warning.
    (void)EPS_CREATION_;
    GetSeed(size, seed, EPS_CREATION);
}

#endif