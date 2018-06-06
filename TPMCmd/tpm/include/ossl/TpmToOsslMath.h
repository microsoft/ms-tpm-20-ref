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
// This file contains the structure definitions used for ECC in the LibTopCrypt
// version of the code. These definitions would change, based on the library.
// The ECC-related structures that cross the TPM interface are defined
// in TpmTypes.h
//

#ifndef _TPM_TO_OSSL_MATH_H
#define _TPM_TO_OSSL_MATH_H

#if MATH_LIB == OSSL

#include <openssl/evp.h>
#include <openssl/ec.h>
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
#include <openssl/bn_lcl.h>
#endif
#include <openssl/bn.h>

//** Macros and Defines

// Make sure that the library is using the correct size for a crypt word
#if    defined THIRTY_TWO_BIT && (RADIX_BITS != 32)  \
    || ((defined SIXTY_FOUR_BIT_LONG || defined SIXTY_FOUR_BIT) \
        && (RADIX_BITS != 64))
#  error "Ossl library is using different radix"
#endif

// Allocate a local BIGNUM value. For the allocation, a bigNum structure is created
// as is a local BIGNUM. The bigNum is initialized and then the BIGNUM is
// set to reference the local value.
#define BIG_VAR(name, bits)                                         \
    BN_VAR(name##Bn, (bits));                                       \
    BIGNUM          _##name;                                        \
    BIGNUM          *name = BigInitialized(&_##name,                \
                                BnInit(name##Bn,                    \
                                BYTES_TO_CRYPT_WORDS(sizeof(_##name##Bn.d))))

// Allocate a BIGNUM and initialize with the values in a bigNum initializer
#define BIG_INITIALIZED(name, initializer)                      \
    BIGNUM           _##name;                                   \
    BIGNUM          *name = BigInitialized(&_##name, initializer)


typedef struct
{
    const ECC_CURVE_DATA    *C;     // the TPM curve values
    EC_GROUP                *G;     // group parameters
    BN_CTX                  *CTX;   // the context for the math (this might not be
                                    // the context in which the curve was created>;
} OSSL_CURVE_DATA;

typedef OSSL_CURVE_DATA      *bigCurve;

#define AccessCurveData(E)      ((E)->C)

#define CURVE_INITIALIZED(name, initializer)                        \
    OSSL_CURVE_DATA     _##name;                                 \
    bigCurve            name =  BnCurveInitialize(&_##name, initializer)

#include "TpmToOsslSupport_fp.h"

#define CURVE_FREE(E)                   \
    if(E != NULL)                       \
    {                                   \
        if(E->G != NULL)                \
            EC_GROUP_free(E->G);        \
        OsslContextLeave(E->CTX);       \
    }

#define OSSL_ENTER()     BN_CTX      *CTX = OsslContextEnter()

#define OSSL_LEAVE()     OsslContextLeave(CTX)

// This definition would change if there were something to report
#define MathLibSimulationEnd()

#endif // MATH_LIB == OSSL

#endif
