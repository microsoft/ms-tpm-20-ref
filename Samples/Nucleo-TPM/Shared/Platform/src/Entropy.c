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

//** Includes
#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <memory.h>
#include "PlatformData.h"
#include "Platform_fp.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

extern RNG_HandleTypeDef hrng;

//** Local values
// This is the last 32-bits of hardware entropy produced. We have to check to
// see that two consecutive 32-bit values are not the same because
// (according to FIPS 140-2, annex C
//
// 1. If each call to a RNG produces blocks of n bits (where n > 15), the first
// n-bit block generated after power-up, initialization, or reset shall not be
// used, but shall be saved for comparison with the next n-bit block to be
// generated. Each subsequent generation of an n-bit block shall be compared with
// the previously generated block. The test shall fail if any two compared n-bit
// blocks are equal.
extern uint32_t        lastEntropy;

extern int             firstValue;

//** _plat__GetEntropy()
// This function is used to get available hardware entropy. In a hardware
// implementation of this function, there would be no call to the system
// to get entropy.
// If the caller does not ask for any entropy, then this is a startup indication
// and 'firstValue' should be reset.

// return type: int32_t
//  < 0        hardware failure of the entropy generator, this is sticky
// >= 0        the returned amount of entropy (bytes)
//
LIB_EXPORT int32_t
_plat__GetEntropy(
    unsigned char       *entropy,           // output buffer
    uint32_t             amount             // amount requested
    )
{
    uint32_t random32bit;

    if(amount == 0)
    {
        firstValue = 1;
        return 0;
    }

    if(firstValue)
    {
        firstValue = 0;
    }

    for(uint32_t n = 0; n < amount; n += sizeof(random32bit))
    {
        if((HAL_RNG_GenerateRandomNumber(&hrng, &random32bit) != HAL_OK) ||
           (~firstValue && (lastEntropy == random32bit)))
        {
            return -1;
        }
        memcpy(&entropy[n], &random32bit, MIN(sizeof(random32bit), amount - n));
        lastEntropy = random32bit;
    }

    return (int32_t)amount;
}
