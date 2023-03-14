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
//
// This header file is used to 'splice' the OpenSSL hash code into the TPM code.
//
#ifndef HASH_LIB_DEFINED
#define HASH_LIB_DEFINED

#define HASH_LIB_OSSL

#include <openssl/evp.h>
#include <openssl/sha.h>

#if ALG_SM3_256
#  if defined(OPENSSL_NO_SM3) || OPENSSL_VERSION_NUMBER < 0x10101010L
#    undef ALG_SM3_256
#    define ALG_SM3_256 ALG_NO
#  elif OPENSSL_VERSION_NUMBER >= 0x10200000L
#    include <openssl/sm3.h>
#  else
// OpenSSL 1.1.1 keeps smX.h headers in the include/crypto directory,
// and they do not get installed as part of the libssl package
#    define SM3_LBLOCK (64 / 4)

typedef struct SM3state_st
{
    unsigned int A, B, C, D, E, F, G, H;
    unsigned int Nl, Nh;
    unsigned int data[SM3_LBLOCK];
    unsigned int num;
} SM3_CTX;

int sm3_init(SM3_CTX* c);
int sm3_update(SM3_CTX* c, const void* data, size_t len);
int sm3_final(unsigned char* md, SM3_CTX* c);
#  endif  // OpenSSL < 1.2
#endif    // ALG_SM3_256

#include <openssl/ossl_typ.h>

#define HASH_ALIGNMENT RADIX_BYTES

//***************************************************************
//** Links to the OpenSSL HASH code
//***************************************************************

// Redefine the internal name used for each of the hash state structures to the
// name used by the library.
// These defines need to be known in all parts of the TPM so that the structure
// sizes can be properly computed when needed.
#define tpmHashStateSHA1_t    SHA_CTX
#define tpmHashStateSHA256_t  SHA256_CTX
#define tpmHashStateSHA384_t  SHA512_CTX
#define tpmHashStateSHA512_t  SHA512_CTX
#define tpmHashStateSM3_256_t SM3_CTX

// The defines below are only needed when compiling CryptHash.c or CryptSmac.c.
// This isolation is primarily to avoid name space collision. However, if there
// is a real collision, it will likely show up when the linker tries to put things
// together.

#ifdef _CRYPT_HASH_C_

typedef BYTE*       PBYTE;
typedef const BYTE* PCBYTE;

// Define the interface between CryptHash.c to the functions provided by the
// library. For each method, define the calling parameters of the method and then
// define how the method is invoked in CryptHash.c.
//
// All hashes are required to have the same calling sequence. If they don't, create
// a simple adaptation function that converts from the "standard" form of the call
// to the form used by the specific hash (and then send a nasty letter to the
// person who wrote the hash function for the library).
//
// The macro that calls the method also defines how the
// parameters get swizzled between the default form (in CryptHash.c)and the
// library form.
//
// Initialize the hash context
#  define HASH_START_METHOD_DEF void(HASH_START_METHOD)(PANY_HASH_STATE state)
#  define HASH_START(hashState) ((hashState)->def->method.start)(&(hashState)->state);

// Add data to the hash
#  define HASH_DATA_METHOD_DEF \
    void(HASH_DATA_METHOD)(PANY_HASH_STATE state, PCBYTE buffer, size_t size)
#  define HASH_DATA(hashState, dInSize, dIn) \
    ((hashState)->def->method.data)(&(hashState)->state, dIn, dInSize)

// Finalize the hash and get the digest
#  define HASH_END_METHOD_DEF \
    void(HASH_END_METHOD)(BYTE * buffer, PANY_HASH_STATE state)
#  define HASH_END(hashState, buffer) \
    ((hashState)->def->method.end)(buffer, &(hashState)->state)

// Copy the hash context
// Note: For import, export, and copy, memcpy() is used since there is no
// reformatting necessary between the internal and external forms.
#  define HASH_STATE_COPY_METHOD_DEF \
    void(HASH_STATE_COPY_METHOD)(    \
        PANY_HASH_STATE to, PCANY_HASH_STATE from, size_t size)
#  define HASH_STATE_COPY(hashStateOut, hashStateIn)          \
    ((hashStateIn)->def->method.copy)(&(hashStateOut)->state, \
                                      &(hashStateIn)->state,  \
                                      (hashStateIn)->def->contextSize)

// Copy (with reformatting when necessary) an internal hash structure to an
// external blob
#  define HASH_STATE_EXPORT_METHOD_DEF \
    void(HASH_STATE_EXPORT_METHOD)(BYTE * to, PCANY_HASH_STATE from, size_t size)
#  define HASH_STATE_EXPORT(to, hashStateFrom)         \
    ((hashStateFrom)->def->method.copyOut)(            \
        &(((BYTE*)(to))[offsetof(HASH_STATE, state)]), \
        &(hashStateFrom)->state,                       \
        (hashStateFrom)->def->contextSize)

// Copy from an external blob to an internal formate (with reformatting when
// necessary
#  define HASH_STATE_IMPORT_METHOD_DEF \
    void(HASH_STATE_IMPORT_METHOD)(PANY_HASH_STATE to, const BYTE* from, size_t size)
#  define HASH_STATE_IMPORT(hashStateTo, from)                 \
    ((hashStateTo)->def->method.copyIn)(                       \
        &(hashStateTo)->state,                                 \
        &(((const BYTE*)(from))[offsetof(HASH_STATE, state)]), \
        (hashStateTo)->def->contextSize)

// Function aliases. The code in CryptHash.c uses the internal designation for the
// functions. These need to be translated to the function names of the library.
// external name of the
// initialization method
#  define tpmHashStart_SHA1          SHA1_Init
#  define tpmHashData_SHA1           SHA1_Update
#  define tpmHashEnd_SHA1            SHA1_Final
#  define tpmHashStateCopy_SHA1      memcpy
#  define tpmHashStateExport_SHA1    memcpy
#  define tpmHashStateImport_SHA1    memcpy
#  define tpmHashStart_SHA256        SHA256_Init
#  define tpmHashData_SHA256         SHA256_Update
#  define tpmHashEnd_SHA256          SHA256_Final
#  define tpmHashStateCopy_SHA256    memcpy
#  define tpmHashStateExport_SHA256  memcpy
#  define tpmHashStateImport_SHA256  memcpy
#  define tpmHashStart_SHA384        SHA384_Init
#  define tpmHashData_SHA384         SHA384_Update
#  define tpmHashEnd_SHA384          SHA384_Final
#  define tpmHashStateCopy_SHA384    memcpy
#  define tpmHashStateExport_SHA384  memcpy
#  define tpmHashStateImport_SHA384  memcpy
#  define tpmHashStart_SHA512        SHA512_Init
#  define tpmHashData_SHA512         SHA512_Update
#  define tpmHashEnd_SHA512          SHA512_Final
#  define tpmHashStateCopy_SHA512    memcpy
#  define tpmHashStateExport_SHA512  memcpy
#  define tpmHashStateImport_SHA512  memcpy
#  define tpmHashStart_SM3_256       sm3_init
#  define tpmHashData_SM3_256        sm3_update
#  define tpmHashEnd_SM3_256         sm3_final
#  define tpmHashStateCopy_SM3_256   memcpy
#  define tpmHashStateExport_SM3_256 memcpy
#  define tpmHashStateImport_SM3_256 memcpy

#endif  // _CRYPT_HASH_C_

#define LibHashInit()
// This definition would change if there were something to report
#define HashLibSimulationEnd()

#endif  // HASH_LIB_DEFINED
