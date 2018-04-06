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
// This header file is used to select the library code that gets included in the
// TPM built

#ifndef _LIB_SUPPORT_H_
#define _LIB_SUPPORT_H_

// OSSL has a full suite but yields an executable that is much larger than it needs
// to be.
#define     OSSL        1
// LTC has symmetric support, RSA support, and inadequate ECC support
#define     LTC         2
// MSBN only provides math support so should not be used as the hash or symmetric
// library
#define     MSBN        3
// SYMCRYPT only provides symmetric cryptography so would need to be combined with
// another library that has math support
#define     SYMCRYPT    4
// WolfCrypt from the statically linkable GPL WolfSLL, other commercial licenses
// also available
#define     WOLF        5

//*********************
#if RADIX_BITS == 32
#   define RADIX_BYTES 4
#elif RADIX_BITS == 64
#   define RADIX_BYTES 8
#else
#error  "RADIX_BITS must either be 32 or 64."
#endif

// Include the options for hashing
// If all the optional headers were always part of the distribution then it would
// not be necessary to do the conditional testing before the include. )-;
#if HASH_LIB == OSSL
#  include "ossl/TpmToOsslHash.h"
#elif HASH_LIB == LTC
#  include "ltc/TpmToLtcHash.h"
#elif HASH_LIB == SYMCRYPT
#include "symcrypt/TpmToSymcryptHash.h"
#elif HASH_LIB == WOLF
#  include "wolf/TpmToWolfHash.h"
#else
#  error "No hash library selected"
#endif


// Set the linkage for the selected symmetric library
#if SYM_LIB == OSSL
#  include "ossl/TpmToOsslSym.h"
#elif SYM_LIB == LTC
#  include "ltc/TpmToLtcSym.h"
#elif SYM_LIB == SYMCRYPT
#include "symcrypt/TpmToSymcryptSym.h"
#elif SYM_LIB == WOLF
#  include "wolf/TpmToWolfSym.h"
#else
#  error "No symmetric library selected"
#endif

#undef MIN
#undef MIN


// Select a big number Library.
// This uses a define rather than an include so that the header will not be included
// until the required values have been defined.
#if MATH_LIB == OSSL
#  define MATHLIB_H  "ossl/TpmToOsslMath.h"
#elif MATH_LIB == LTC
#  define MATHLIB_H  "ltc/TpmToLtcMath.h"
#elif MATH_LIB == MSBN
#define MATHLIB_H  "msbn/TpmToMsBnMath.h"
#elif MATH_LIB == WOLF
#  define MATHLIB_H  "wolf/TpmToWolfMath.h"
#else
#  error "No math library selected"
#endif

#endif // _LIB_SUPPORT_H_
