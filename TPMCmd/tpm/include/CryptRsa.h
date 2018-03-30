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
// This file contains the RSA-related structures and defines.

#ifndef _CRYPT_RSA_H
#define _CRYPT_RSA_H

// This structure is a succinct representation of the cryptographic components
// of an RSA key. It is used in testing
typedef struct
{
    UINT32        exponent;      // The public exponent pointer
    TPM2B        *publicKey;     // Pointer to the public modulus
    TPM2B        *privateKey;    // The private prime
} RSA_KEY;

// These values are used in the bigNum representation of various RSA values.

#define RSA_BITS            (MAX_RSA_KEY_BYTES * 8)
BN_TYPE(rsa, RSA_BITS);
#define BN_RSA(name)       BN_VAR(name, RSA_BITS)
#define BN_RSA_INITIALIZED(name, initializer)                      \
    BN_INITIALIZED(name, RSA_BITS, initializer)

#define BN_PRIME(name)     BN_VAR(name, (RSA_BITS / 2))
BN_TYPE(prime, (RSA_BITS / 2));
#define BN_PRIME_INITIALIZED(name, initializer)                    \
    BN_INITIALIZED(name, RSA_BITS / 2, initializer)

typedef struct privateExponent
{
#if CRT_FORMAT_RSA == NO
    bn_rsa_t            D;
#else
    bn_prime_t          Q;
    bn_prime_t          dP;
    bn_prime_t          dQ;
    bn_prime_t          qInv;
#endif // CRT_FORMAT_RSA
} privateExponent_t;

#endif      // _CRYPT_RSA_H
