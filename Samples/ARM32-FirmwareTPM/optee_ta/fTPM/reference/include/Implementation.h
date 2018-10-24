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

#ifndef _IMPLEMENTATION_H_
#define _IMPLEMENTATION_H_

#include    "RuntimeSupport.h"

#include    <TpmBuildSwitches.h>
#include    <BaseTypes.h>
#include    <TPMB.h>

#undef TRUE
#undef FALSE

#undef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Table 2:3 - Definition of Base Types
// Base Types are in BaseTypes.h

// Table 2:4 - Defines for Logic Values
#define TRUE                1
#define FALSE               0
#define YES                 1
#define NO                  0
#define SET                 1
#define CLEAR               0

// Table 0:1 - Defines for Processor Values
#ifndef BIG_ENDIAN_TPM
#define BIG_ENDIAN_TPM              NO
#endif // BIG_ENDIAN_TPM
#define LITTLE_ENDIAN_TPM           !BIG_ENDIAN_TPM
#ifndef MOST_SIGNIFICANT_BIT_0
#define MOST_SIGNIFICANT_BIT_0      NO
#endif // MOST_SIGNIFICANT_BIT_0
#define LEAST_SIGNIFICANT_BIT_0     !MOST_SIGNIFICANT_BIT_0
#ifndef AUTO_ALIGN
#define AUTO_ALIGN                  NO
#endif // AUTO_ALIGN

// Table 0:3 - Defines for Key Size Constants
#define RSA_KEY_SIZES_BITS              {1024,2048}
#define RSA_KEY_SIZE_BITS_1024          RSA_ALLOWED_KEY_SIZE_1024
#define RSA_KEY_SIZE_BITS_2048          RSA_ALLOWED_KEY_SIZE_2048
#define MAX_RSA_KEY_BITS                2048
#define MAX_RSA_KEY_BYTES               256

#define TDES_KEY_SIZES_BITS             {128,192}
#define TDES_KEY_SIZE_BITS_128          TDES_ALLOWED_KEY_SIZE_128
#define TDES_KEY_SIZE_BITS_192          TDES_ALLOWED_KEY_SIZE_192
#define MAX_TDES_KEY_BITS               192
#define MAX_TDES_KEY_BYTES              24
#define MAX_TDES_BLOCK_SIZE_BYTES       \
            MAX(TDES_128_BLOCK_SIZE_BYTES, MAX(TDES_192_BLOCK_SIZE_BYTES, 0))

#define AES_KEY_SIZES_BITS              {128,256}
#define AES_KEY_SIZE_BITS_128           AES_ALLOWED_KEY_SIZE_128
#define AES_KEY_SIZE_BITS_256           AES_ALLOWED_KEY_SIZE_256
#define MAX_AES_KEY_BITS                256
#define MAX_AES_KEY_BYTES               32
#define MAX_AES_BLOCK_SIZE_BYTES        \
            MAX(AES_128_BLOCK_SIZE_BYTES, MAX(AES_256_BLOCK_SIZE_BYTES, 0))

#define SM4_KEY_SIZES_BITS              {128}
#define SM4_KEY_SIZE_BITS_128           SM4_ALLOWED_KEY_SIZE_128
#define MAX_SM4_KEY_BITS                128
#define MAX_SM4_KEY_BYTES               16
#define MAX_SM4_BLOCK_SIZE_BYTES        MAX(SM4_128_BLOCK_SIZE_BYTES, 0)

#define CAMELLIA_KEY_SIZES_BITS         {128}
#define CAMELLIA_KEY_SIZE_BITS_128      CAMELLIA_ALLOWED_KEY_SIZE_128
#define MAX_CAMELLIA_KEY_BITS           128
#define MAX_CAMELLIA_KEY_BYTES          16
#define MAX_CAMELLIA_BLOCK_SIZE_BYTES   MAX(CAMELLIA_128_BLOCK_SIZE_BYTES, 0)

// Table 0:4 - Defines for Implemented Curves
#define ECC_NIST_P192                   NO
#define ECC_NIST_P224                   NO
#define ECC_NIST_P256                   YES
#define ECC_NIST_P384                   YES
#define ECC_NIST_P521                   YES
#ifdef USE_WOLFCRYPT
#define ECC_BN_P256                     NO
#define ECC_SM2_P256                    NO
#else
#define ECC_BN_P256                     YES
#define ECC_SM2_P256                    YES
#endif
#define ECC_BN_P638                     NO
#define ECC_CURVES                      \
            {TPM_ECC_BN_P256,   TPM_ECC_BN_P638,   TPM_ECC_NIST_P192,              \
             TPM_ECC_NIST_P224, TPM_ECC_NIST_P256, TPM_ECC_NIST_P384,              \
             TPM_ECC_NIST_P521, TPM_ECC_SM2_P256}
#define ECC_CURVE_COUNT                 \
            (ECC_BN_P256   + ECC_BN_P638   + ECC_NIST_P192 + ECC_NIST_P224 +       \
             ECC_NIST_P256 + ECC_NIST_P384 + ECC_NIST_P521 + ECC_SM2_P256)
#define MAX_ECC_KEY_BITS                \
            MAX(ECC_BN_P256 * 256,   MAX(ECC_BN_P638 * 638,                        \
            MAX(ECC_NIST_P192 * 192, MAX(ECC_NIST_P224 * 224,                      \
            MAX(ECC_NIST_P256 * 256, MAX(ECC_NIST_P384 * 384,                      \
            MAX(ECC_NIST_P521 * 521, MAX(ECC_SM2_P256 * 256,                       \
            0))))))))
#define MAX_ECC_KEY_BYTES               BITS_TO_BYTES(MAX_ECC_KEY_BITS)

// Table 0:6 - Defines for PLATFORM Values
#define PLATFORM_FAMILY         TPM_SPEC_FAMILY
#define PLATFORM_LEVEL          TPM_SPEC_LEVEL
#define PLATFORM_VERSION        TPM_SPEC_VERSION
#define PLATFORM_YEAR           TPM_SPEC_YEAR
#define PLATFORM_DAY_OF_YEAR    TPM_SPEC_DAY_OF_YEAR

// Table 0:7 - Defines for Implementation Values
#define FIELD_UPGRADE_IMPLEMENTED       NO
#define RADIX_BITS                      32
#define HASH_ALIGNMENT                  4
#define SYMMETRIC_ALIGNMENT             4
#ifdef USE_WOLFCRYPT
#define HASH_LIB                        WOLF
#define SYM_LIB                         WOLF
#define MATH_LIB                        WOLF
#else
#define HASH_LIB                        OSSL
#define SYM_LIB                         OSSL
#define MATH_LIB                        OSSL
#endif
#define BSIZE                           UINT16
#define IMPLEMENTATION_PCR              24
#define PLATFORM_PCR                    24
#define DRTM_PCR                        17
#define HCRTM_PCR                       0
#define NUM_LOCALITIES                  5
#define MAX_HANDLE_NUM                  3
#define MAX_ACTIVE_SESSIONS             64
#define CONTEXT_SLOT                    UINT16
#define CONTEXT_COUNTER                 UINT64
#define MAX_LOADED_SESSIONS             3
#define MAX_SESSION_NUM                 3
#define MAX_LOADED_OBJECTS              3
#define MIN_EVICT_OBJECTS               2
#define NUM_POLICY_PCR_GROUP            1
#define NUM_AUTHVALUE_PCR_GROUP         1
#define MAX_CONTEXT_SIZE                2474
#define MAX_DIGEST_BUFFER               1024
#define MAX_NV_INDEX_SIZE               2048
#define MAX_NV_BUFFER_SIZE              1024
#define MAX_CAP_BUFFER                  1024
#define NV_MEMORY_SIZE                  16384
#define MIN_COUNTER_INDICES             8
#define NUM_STATIC_PCR                  16
#define MAX_ALG_LIST_SIZE               64
#define PRIMARY_SEED_SIZE               32
#define CONTEXT_ENCRYPT_ALGORITHM       AES
#define NV_CLOCK_UPDATE_INTERVAL        12
#define NUM_POLICY_PCR                  1
#define MAX_COMMAND_SIZE                4096
#define MAX_RESPONSE_SIZE               4096
#define ORDERLY_BITS                    8
#define MAX_SYM_DATA                    128
#define MAX_RNG_ENTROPY_SIZE            64
#define RAM_INDEX_SPACE                 512
#define RSA_DEFAULT_PUBLIC_EXPONENT     0x00010001
#define ENABLE_PCR_NO_INCREMENT         YES
#define CRT_FORMAT_RSA                  YES
#define VENDOR_COMMAND_COUNT            0
#define MAX_VENDOR_BUFFER_SIZE          1024
#define TPM_MAX_DERIVATION_BITS         8192

// Table 0:2 - Defines for Implemented Algorithms
#define ALG_AES                         ALG_YES
#define ALG_CAMELLIA                    ALG_NO      /* Not specified by vendor */
#define ALG_CBC                         ALG_YES
#define ALG_CFB                         ALG_YES
#define ALG_CMAC                        ALG_YES
#define ALG_CTR                         ALG_YES
#define ALG_ECB                         ALG_YES
#define ALG_ECC                         ALG_YES
#define ALG_ECDAA                       (ALG_YES && ALG_ECC)
#define ALG_ECDH                        (ALG_YES && ALG_ECC)
#define ALG_ECDSA                       (ALG_YES && ALG_ECC)
#define ALG_ECMQV                       (ALG_NO && ALG_ECC)
#define ALG_ECSCHNORR                   (ALG_YES && ALG_ECC)
#define ALG_HMAC                        ALG_YES
#define ALG_KDF1_SP800_108              ALG_YES
#define ALG_KDF1_SP800_56A              (ALG_YES && ALG_ECC)
#define ALG_KDF2                        ALG_NO
#define ALG_KEYEDHASH                   ALG_YES
#define ALG_MGF1                        ALG_YES
#define ALG_OAEP                        (ALG_YES && ALG_RSA)
#define ALG_OFB                         ALG_YES
#define ALG_RSA                         ALG_YES
#define ALG_RSAES                       (ALG_YES && ALG_RSA)
#define ALG_RSAPSS                      (ALG_YES && ALG_RSA)
#define ALG_RSASSA                      (ALG_YES && ALG_RSA)
#define ALG_SHA                         ALG_NO      /* Not specified by vendor */
#define ALG_SHA1                        ALG_YES
#define ALG_SHA256                      ALG_YES
#define ALG_SHA384                      ALG_YES
#define ALG_SHA512                      ALG_YES
#define ALG_SM2                         (ALG_NO && ALG_ECC)
#define ALG_SM3_256                     ALG_NO
#define ALG_SM4                         ALG_NO
#define ALG_SYMCIPHER                   ALG_YES
#define ALG_TDES                        ALG_NO
#define ALG_XOR                         ALG_YES

// Table 1:2 - Definition of TPM_ALG_ID Constants 
typedef UINT16                          TPM_ALG_ID;
#define     ALG_ERROR_VALUE             0x0000
#define TPM_ALG_ERROR                   (TPM_ALG_ID)(ALG_ERROR_VALUE)
#define     ALG_RSA_VALUE               0x0001
#if         ALG_RSA
#define TPM_ALG_RSA                     (TPM_ALG_ID)(ALG_RSA_VALUE)
#endif   // ALG_RSA
#define     ALG_TDES_VALUE              0x0003
#if         ALG_TDES
#define TPM_ALG_TDES                    (TPM_ALG_ID)(ALG_TDES_VALUE)
#endif   // ALG_TDES
#define     ALG_SHA_VALUE               0x0004
#if         ALG_SHA
#define TPM_ALG_SHA                     (TPM_ALG_ID)(ALG_SHA_VALUE)
#endif   // ALG_SHA
#define     ALG_SHA1_VALUE              0x0004
#if         ALG_SHA1
#define TPM_ALG_SHA1                    (TPM_ALG_ID)(ALG_SHA1_VALUE)
#endif   // ALG_SHA1
#define     ALG_HMAC_VALUE              0x0005
#if         ALG_HMAC
#define TPM_ALG_HMAC                    (TPM_ALG_ID)(ALG_HMAC_VALUE)
#endif   // ALG_HMAC
#define     ALG_AES_VALUE               0x0006
#if         ALG_AES
#define TPM_ALG_AES                     (TPM_ALG_ID)(ALG_AES_VALUE)
#endif   // ALG_AES
#define     ALG_MGF1_VALUE              0x0007
#if         ALG_MGF1
#define TPM_ALG_MGF1                    (TPM_ALG_ID)(ALG_MGF1_VALUE)
#endif   // ALG_MGF1
#define     ALG_KEYEDHASH_VALUE         0x0008
#if         ALG_KEYEDHASH
#define TPM_ALG_KEYEDHASH               (TPM_ALG_ID)(ALG_KEYEDHASH_VALUE)
#endif   // ALG_KEYEDHASH
#define     ALG_XOR_VALUE               0x000A
#if         ALG_XOR
#define TPM_ALG_XOR                     (TPM_ALG_ID)(ALG_XOR_VALUE)
#endif   // ALG_XOR
#define     ALG_SHA256_VALUE            0x000B
#if         ALG_SHA256
#define TPM_ALG_SHA256                  (TPM_ALG_ID)(ALG_SHA256_VALUE)
#endif   // ALG_SHA256
#define     ALG_SHA384_VALUE            0x000C
#if         ALG_SHA384
#define TPM_ALG_SHA384                  (TPM_ALG_ID)(ALG_SHA384_VALUE)
#endif   // ALG_SHA384
#define     ALG_SHA512_VALUE            0x000D
#if         ALG_SHA512
#define TPM_ALG_SHA512                  (TPM_ALG_ID)(ALG_SHA512_VALUE)
#endif   // ALG_SHA512
#define     ALG_NULL_VALUE              0x0010
#define TPM_ALG_NULL                    (TPM_ALG_ID)(ALG_NULL_VALUE)
#define     ALG_SM3_256_VALUE           0x0012
#if         ALG_SM3_256
#define TPM_ALG_SM3_256                 (TPM_ALG_ID)(ALG_SM3_256_VALUE)
#endif   // ALG_SM3_256
#define     ALG_SM4_VALUE               0x0013
#if         ALG_SM4
#define TPM_ALG_SM4                     (TPM_ALG_ID)(ALG_SM4_VALUE)
#endif   // ALG_SM4
#define     ALG_RSASSA_VALUE            0x0014
#if         ALG_RSASSA
#define TPM_ALG_RSASSA                  (TPM_ALG_ID)(ALG_RSASSA_VALUE)
#endif   // ALG_RSASSA
#define     ALG_RSAES_VALUE             0x0015
#if         ALG_RSAES
#define TPM_ALG_RSAES                   (TPM_ALG_ID)(ALG_RSAES_VALUE)
#endif   // ALG_RSAES
#define     ALG_RSAPSS_VALUE            0x0016
#if         ALG_RSAPSS
#define TPM_ALG_RSAPSS                  (TPM_ALG_ID)(ALG_RSAPSS_VALUE)
#endif   // ALG_RSAPSS
#define     ALG_OAEP_VALUE              0x0017
#if         ALG_OAEP
#define TPM_ALG_OAEP                    (TPM_ALG_ID)(ALG_OAEP_VALUE)
#endif   // ALG_OAEP
#define     ALG_ECDSA_VALUE             0x0018
#if         ALG_ECDSA
#define TPM_ALG_ECDSA                   (TPM_ALG_ID)(ALG_ECDSA_VALUE)
#endif   // ALG_ECDSA
#define     ALG_ECDH_VALUE              0x0019
#if         ALG_ECDH
#define TPM_ALG_ECDH                    (TPM_ALG_ID)(ALG_ECDH_VALUE)
#endif   // ALG_ECDH
#define     ALG_ECDAA_VALUE             0x001A
#if         ALG_ECDAA
#define TPM_ALG_ECDAA                   (TPM_ALG_ID)(ALG_ECDAA_VALUE)
#endif   // ALG_ECDAA
#define     ALG_SM2_VALUE               0x001B
#if         ALG_SM2
#define TPM_ALG_SM2                     (TPM_ALG_ID)(ALG_SM2_VALUE)
#endif   // ALG_SM2
#define     ALG_ECSCHNORR_VALUE         0x001C
#if         ALG_ECSCHNORR
#define TPM_ALG_ECSCHNORR               (TPM_ALG_ID)(ALG_ECSCHNORR_VALUE)
#endif   // ALG_ECSCHNORR
#define     ALG_ECMQV_VALUE             0x001D
#if         ALG_ECMQV
#define TPM_ALG_ECMQV                   (TPM_ALG_ID)(ALG_ECMQV_VALUE)
#endif   // ALG_ECMQV
#define     ALG_KDF1_SP800_56A_VALUE    0x0020
#if         ALG_KDF1_SP800_56A
#define TPM_ALG_KDF1_SP800_56A          (TPM_ALG_ID)(ALG_KDF1_SP800_56A_VALUE)
#endif   // ALG_KDF1_SP800_56A
#define     ALG_KDF2_VALUE              0x0021
#if         ALG_KDF2
#define TPM_ALG_KDF2                    (TPM_ALG_ID)(ALG_KDF2_VALUE)
#endif   // ALG_KDF2
#define     ALG_KDF1_SP800_108_VALUE    0x0022
#if         ALG_KDF1_SP800_108
#define TPM_ALG_KDF1_SP800_108          (TPM_ALG_ID)(ALG_KDF1_SP800_108_VALUE)
#endif   // ALG_KDF1_SP800_108
#define     ALG_ECC_VALUE               0x0023
#if         ALG_ECC
#define TPM_ALG_ECC                     (TPM_ALG_ID)(ALG_ECC_VALUE)
#endif   // ALG_ECC
#define     ALG_SYMCIPHER_VALUE         0x0025
#if         ALG_SYMCIPHER
#define TPM_ALG_SYMCIPHER               (TPM_ALG_ID)(ALG_SYMCIPHER_VALUE)
#endif   // ALG_SYMCIPHER
#define     ALG_CAMELLIA_VALUE          0x0026
#if         ALG_CAMELLIA
#define TPM_ALG_CAMELLIA                (TPM_ALG_ID)(ALG_CAMELLIA_VALUE)
#endif   // ALG_CAMELLIA
#define     ALG_CMAC_VALUE              0x003F
#if         ALG_CMAC
#define TPM_ALG_CMAC                    (TPM_ALG_ID)(ALG_CMAC_VALUE)
#endif   // ALG_CMAC
#define     ALG_CTR_VALUE               0x0040
#if         ALG_CTR
#define TPM_ALG_CTR                     (TPM_ALG_ID)(ALG_CTR_VALUE)
#endif   // ALG_CTR
#define     ALG_OFB_VALUE               0x0041
#if         ALG_OFB
#define TPM_ALG_OFB                     (TPM_ALG_ID)(ALG_OFB_VALUE)
#endif   // ALG_OFB
#define     ALG_CBC_VALUE               0x0042
#if         ALG_CBC
#define TPM_ALG_CBC                     (TPM_ALG_ID)(ALG_CBC_VALUE)
#endif   // ALG_CBC
#define     ALG_CFB_VALUE               0x0043
#if         ALG_CFB
#define TPM_ALG_CFB                     (TPM_ALG_ID)(ALG_CFB_VALUE)
#endif   // ALG_CFB
#define     ALG_ECB_VALUE               0x0044
#if         ALG_ECB
#define TPM_ALG_ECB                     (TPM_ALG_ID)(ALG_ECB_VALUE)
#endif   // ALG_ECB
// Values derived from Table 1:2
#define     ALG_FIRST_VALUE             0x0001
#define TPM_ALG_FIRST                   (TPM_ALG_ID)(ALG_FIRST_VALUE)
#define     ALG_LAST_VALUE              0x0044
#define TPM_ALG_LAST                    (TPM_ALG_ID)(ALG_LAST_VALUE)

// Table 1:3 - Definition of TPM_ECC_CURVE Constants 
typedef UINT16              TPM_ECC_CURVE;
#define TPM_ECC_NONE        (TPM_ECC_CURVE)(0x0000)
#define TPM_ECC_NIST_P192   (TPM_ECC_CURVE)(0x0001)
#define TPM_ECC_NIST_P224   (TPM_ECC_CURVE)(0x0002)
#define TPM_ECC_NIST_P256   (TPM_ECC_CURVE)(0x0003)
#define TPM_ECC_NIST_P384   (TPM_ECC_CURVE)(0x0004)
#define TPM_ECC_NIST_P521   (TPM_ECC_CURVE)(0x0005)
#define TPM_ECC_BN_P256     (TPM_ECC_CURVE)(0x0010)
#define TPM_ECC_BN_P638     (TPM_ECC_CURVE)(0x0011)
#define TPM_ECC_SM2_P256    (TPM_ECC_CURVE)(0x0020)

// Table 1:12 - Defines for SHA1 Hash Values
#define SHA1_DIGEST_SIZE    20
#define SHA1_BLOCK_SIZE     64
#define SHA1_DER_SIZE       15
#define SHA1_DER            \
            0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B, 0x0E,                        \
            0x03, 0x02, 0x1A, 0x05, 0x00, 0x04, 0x14

// Table 1:13 - Defines for SHA256 Hash Values
#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE   64
#define SHA256_DER_SIZE     19
#define SHA256_DER          \
            0x30, 0x31, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,                        \
            0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,                        \
            0x00, 0x04, 0x20

// Table 1:14 - Defines for SHA384 Hash Values
#define SHA384_DIGEST_SIZE  48
#define SHA384_BLOCK_SIZE   128
#define SHA384_DER_SIZE     19
#define SHA384_DER          \
            0x30, 0x41, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,                        \
            0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02, 0x05,                        \
            0x00, 0x04, 0x30

// Table 1:15 - Defines for SHA512 Hash Values
#define SHA512_DIGEST_SIZE  64
#define SHA512_BLOCK_SIZE   128
#define SHA512_DER_SIZE     19
#define SHA512_DER          \
            0x30, 0x51, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,                        \
            0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05,                        \
            0x00, 0x04, 0x40

// Table 1:16 - Defines for SM3_256 Hash Values
#define SM3_256_DIGEST_SIZE     32
#define SM3_256_BLOCK_SIZE      64
#define SM3_256_DER_SIZE        18
#define SM3_256_DER             \
            0x30, 0x30, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x81,                        \
            0x1C, 0x81, 0x45, 0x01, 0x83, 0x11, 0x05, 0x00,                        \
            0x04, 0x20

// Table 1:17 - Defines for AES Symmetric Cipher Algorithm Constants
#define AES_ALLOWED_KEY_SIZE_128    YES
#define AES_ALLOWED_KEY_SIZE_192    YES
#define AES_ALLOWED_KEY_SIZE_256    YES
#define AES_128_BLOCK_SIZE_BYTES    16
#define AES_192_BLOCK_SIZE_BYTES    16
#define AES_256_BLOCK_SIZE_BYTES    16

// Table 1:18 - Defines for SM4 Symmetric Cipher Algorithm Constants
#define SM4_ALLOWED_KEY_SIZE_128    YES
#define SM4_128_BLOCK_SIZE_BYTES    16

// Table 1:19 - Defines for CAMELLIA Symmetric Cipher Algorithm Constants
#define CAMELLIA_ALLOWED_KEY_SIZE_128   YES
#define CAMELLIA_ALLOWED_KEY_SIZE_192   YES
#define CAMELLIA_ALLOWED_KEY_SIZE_256   YES
#define CAMELLIA_128_BLOCK_SIZE_BYTES   16
#define CAMELLIA_192_BLOCK_SIZE_BYTES   16
#define CAMELLIA_256_BLOCK_SIZE_BYTES   16

// Table 1:17 - Defines for TDES Symmetric Cipher Algorithm Constants
#define TDES_ALLOWED_KEY_SIZE_128   YES
#define TDES_ALLOWED_KEY_SIZE_192   YES
#define TDES_128_BLOCK_SIZE_BYTES   8
#define TDES_192_BLOCK_SIZE_BYTES   8

// Table 0:5 - Defines for Implemented Commands
#define CC_AC_GetCapability                 CC_YES
#define CC_AC_Send                          CC_YES
#define CC_ActivateCredential               CC_YES
#define CC_Certify                          CC_YES
#define CC_CertifyCreation                  CC_YES
#define CC_ChangeEPS                        CC_YES
#define CC_ChangePPS                        CC_YES
#define CC_Clear                            CC_YES
#define CC_ClearControl                     CC_YES
#define CC_ClockRateAdjust                  CC_YES
#define CC_ClockSet                         CC_YES
#define CC_Commit                           (CC_YES && ALG_ECC)
#define CC_ContextLoad                      CC_YES
#define CC_ContextSave                      CC_YES
#define CC_Create                           CC_YES
#define CC_CreateLoaded                     CC_YES
#define CC_CreatePrimary                    CC_YES
#define CC_DictionaryAttackLockReset        CC_YES
#define CC_DictionaryAttackParameters       CC_YES
#define CC_Duplicate                        CC_YES
#define CC_ECC_Parameters                   (CC_YES && ALG_ECC)
#define CC_ECDH_KeyGen                      (CC_YES && ALG_ECC)
#define CC_ECDH_ZGen                        (CC_YES && ALG_ECC)
#define CC_EC_Ephemeral                     (CC_YES && ALG_ECC)
#define CC_EncryptDecrypt                   CC_YES
#define CC_EncryptDecrypt2                  CC_YES
#define CC_EventSequenceComplete            CC_YES
#define CC_EvictControl                     CC_YES
#define CC_FieldUpgradeData                 CC_NO
#define CC_FieldUpgradeStart                CC_NO
#define CC_FirmwareRead                     CC_NO
#define CC_FlushContext                     CC_YES
#define CC_GetCapability                    CC_YES
#define CC_GetCommandAuditDigest            CC_YES
#define CC_GetRandom                        CC_YES
#define CC_GetSessionAuditDigest            CC_YES
#define CC_GetTestResult                    CC_YES
#define CC_GetTime                          CC_YES
#define CC_HMAC                             (CC_YES && !ALG_CMAC)
#define CC_HMAC_Start                       (CC_YES && !ALG_CMAC)
#define CC_Hash                             CC_YES
#define CC_HashSequenceStart                CC_YES
#define CC_HierarchyChangeAuth              CC_YES
#define CC_HierarchyControl                 CC_YES
#define CC_Import                           CC_YES
#define CC_IncrementalSelfTest              CC_YES
#define CC_Load                             CC_YES
#define CC_LoadExternal                     CC_YES
#define CC_MAC                              (CC_YES && ALG_CMAC)
#define CC_MAC_Start                        (CC_YES && ALG_CMAC)
#define CC_MakeCredential                   CC_YES
#define CC_NV_Certify                       CC_YES
#define CC_NV_ChangeAuth                    CC_YES
#define CC_NV_DefineSpace                   CC_YES
#define CC_NV_Extend                        CC_YES
#define CC_NV_GlobalWriteLock               CC_YES
#define CC_NV_Increment                     CC_YES
#define CC_NV_Read                          CC_YES
#define CC_NV_ReadLock                      CC_YES
#define CC_NV_ReadPublic                    CC_YES
#define CC_NV_SetBits                       CC_YES
#define CC_NV_UndefineSpace                 CC_YES
#define CC_NV_UndefineSpaceSpecial          CC_YES
#define CC_NV_Write                         CC_YES
#define CC_NV_WriteLock                     CC_YES
#define CC_ObjectChangeAuth                 CC_YES
#define CC_PCR_Allocate                     CC_YES
#define CC_PCR_Event                        CC_YES
#define CC_PCR_Extend                       CC_YES
#define CC_PCR_Read                         CC_YES
#define CC_PCR_Reset                        CC_YES
#define CC_PCR_SetAuthPolicy                CC_YES
#define CC_PCR_SetAuthValue                 CC_YES
#define CC_PP_Commands                      CC_YES
#define CC_PolicyAuthValue                  CC_YES
#define CC_PolicyAuthorize                  CC_YES
#define CC_PolicyAuthorizeNV                CC_YES
#define CC_PolicyCommandCode                CC_YES
#define CC_PolicyCounterTimer               CC_YES
#define CC_PolicyCpHash                     CC_YES
#define CC_PolicyDuplicationSelect          CC_YES
#define CC_PolicyGetDigest                  CC_YES
#define CC_PolicyLocality                   CC_YES
#define CC_PolicyNV                         CC_YES
#define CC_PolicyNameHash                   CC_YES
#define CC_PolicyNvWritten                  CC_YES
#define CC_PolicyOR                         CC_YES
#define CC_PolicyPCR                        CC_YES
#define CC_PolicyPassword                   CC_YES
#define CC_PolicyPhysicalPresence           CC_YES
#define CC_PolicyRestart                    CC_YES
#define CC_PolicySecret                     CC_YES
#define CC_PolicySigned                     CC_YES
#define CC_PolicyTemplate                   CC_YES
#define CC_PolicyTicket                     CC_YES
#define CC_Policy_AC_SendSelect             CC_YES
#define CC_Quote                            CC_YES
#define CC_RSA_Decrypt                      (CC_YES && ALG_RSA)
#define CC_RSA_Encrypt                      (CC_YES && ALG_RSA)
#define CC_ReadClock                        CC_YES
#define CC_ReadPublic                       CC_YES
#define CC_Rewrap                           CC_YES
#define CC_SelfTest                         CC_YES
#define CC_SequenceComplete                 CC_YES
#define CC_SequenceUpdate                   CC_YES
#define CC_SetAlgorithmSet                  CC_YES
#define CC_SetCommandCodeAuditStatus        CC_YES
#define CC_SetPrimaryPolicy                 CC_YES
#define CC_Shutdown                         CC_YES
#define CC_Sign                             CC_YES
#define CC_StartAuthSession                 CC_YES
#define CC_Startup                          CC_YES
#define CC_StirRandom                       CC_YES
#define CC_TestParms                        CC_YES
#define CC_Unseal                           CC_YES
#define CC_Vendor_TCG_Test                  CC_YES
#define CC_VerifySignature                  CC_YES
#define CC_ZGen_2Phase                      (CC_YES && ALG_ECC)

// Table 2:12 - Definition of TPM_CC Constants 
typedef UINT32                              TPM_CC;
#if         CC_NV_UndefineSpaceSpecial
#define TPM_CC_NV_UndefineSpaceSpecial      (TPM_CC)(0x0000011F)
#endif
#if         CC_EvictControl
#define TPM_CC_EvictControl                 (TPM_CC)(0x00000120)
#endif
#if         CC_HierarchyControl
#define TPM_CC_HierarchyControl             (TPM_CC)(0x00000121)
#endif
#if         CC_NV_UndefineSpace
#define TPM_CC_NV_UndefineSpace             (TPM_CC)(0x00000122)
#endif
#if         CC_ChangeEPS
#define TPM_CC_ChangeEPS                    (TPM_CC)(0x00000124)
#endif
#if         CC_ChangePPS
#define TPM_CC_ChangePPS                    (TPM_CC)(0x00000125)
#endif
#if         CC_Clear
#define TPM_CC_Clear                        (TPM_CC)(0x00000126)
#endif
#if         CC_ClearControl
#define TPM_CC_ClearControl                 (TPM_CC)(0x00000127)
#endif
#if         CC_ClockSet
#define TPM_CC_ClockSet                     (TPM_CC)(0x00000128)
#endif
#if         CC_HierarchyChangeAuth
#define TPM_CC_HierarchyChangeAuth          (TPM_CC)(0x00000129)
#endif
#if         CC_NV_DefineSpace
#define TPM_CC_NV_DefineSpace               (TPM_CC)(0x0000012A)
#endif
#if         CC_PCR_Allocate
#define TPM_CC_PCR_Allocate                 (TPM_CC)(0x0000012B)
#endif
#if         CC_PCR_SetAuthPolicy
#define TPM_CC_PCR_SetAuthPolicy            (TPM_CC)(0x0000012C)
#endif
#if         CC_PP_Commands
#define TPM_CC_PP_Commands                  (TPM_CC)(0x0000012D)
#endif
#if         CC_SetPrimaryPolicy
#define TPM_CC_SetPrimaryPolicy             (TPM_CC)(0x0000012E)
#endif
#if         CC_FieldUpgradeStart
#define TPM_CC_FieldUpgradeStart            (TPM_CC)(0x0000012F)
#endif
#if         CC_ClockRateAdjust
#define TPM_CC_ClockRateAdjust              (TPM_CC)(0x00000130)
#endif
#if         CC_CreatePrimary
#define TPM_CC_CreatePrimary                (TPM_CC)(0x00000131)
#endif
#if         CC_NV_GlobalWriteLock
#define TPM_CC_NV_GlobalWriteLock           (TPM_CC)(0x00000132)
#endif
#if         CC_GetCommandAuditDigest
#define TPM_CC_GetCommandAuditDigest        (TPM_CC)(0x00000133)
#endif
#if         CC_NV_Increment
#define TPM_CC_NV_Increment                 (TPM_CC)(0x00000134)
#endif
#if         CC_NV_SetBits
#define TPM_CC_NV_SetBits                   (TPM_CC)(0x00000135)
#endif
#if         CC_NV_Extend
#define TPM_CC_NV_Extend                    (TPM_CC)(0x00000136)
#endif
#if         CC_NV_Write
#define TPM_CC_NV_Write                     (TPM_CC)(0x00000137)
#endif
#if         CC_NV_WriteLock
#define TPM_CC_NV_WriteLock                 (TPM_CC)(0x00000138)
#endif
#if         CC_DictionaryAttackLockReset
#define TPM_CC_DictionaryAttackLockReset    (TPM_CC)(0x00000139)
#endif
#if         CC_DictionaryAttackParameters
#define TPM_CC_DictionaryAttackParameters   (TPM_CC)(0x0000013A)
#endif
#if         CC_NV_ChangeAuth
#define TPM_CC_NV_ChangeAuth                (TPM_CC)(0x0000013B)
#endif
#if         CC_PCR_Event
#define TPM_CC_PCR_Event                    (TPM_CC)(0x0000013C)
#endif
#if         CC_PCR_Reset
#define TPM_CC_PCR_Reset                    (TPM_CC)(0x0000013D)
#endif
#if         CC_SequenceComplete
#define TPM_CC_SequenceComplete             (TPM_CC)(0x0000013E)
#endif
#if         CC_SetAlgorithmSet
#define TPM_CC_SetAlgorithmSet              (TPM_CC)(0x0000013F)
#endif
#if         CC_SetCommandCodeAuditStatus
#define TPM_CC_SetCommandCodeAuditStatus    (TPM_CC)(0x00000140)
#endif
#if         CC_FieldUpgradeData
#define TPM_CC_FieldUpgradeData             (TPM_CC)(0x00000141)
#endif
#if         CC_IncrementalSelfTest
#define TPM_CC_IncrementalSelfTest          (TPM_CC)(0x00000142)
#endif
#if         CC_SelfTest
#define TPM_CC_SelfTest                     (TPM_CC)(0x00000143)
#endif
#if         CC_Startup
#define TPM_CC_Startup                      (TPM_CC)(0x00000144)
#endif
#if         CC_Shutdown
#define TPM_CC_Shutdown                     (TPM_CC)(0x00000145)
#endif
#if         CC_StirRandom
#define TPM_CC_StirRandom                   (TPM_CC)(0x00000146)
#endif
#if         CC_ActivateCredential
#define TPM_CC_ActivateCredential           (TPM_CC)(0x00000147)
#endif
#if         CC_Certify
#define TPM_CC_Certify                      (TPM_CC)(0x00000148)
#endif
#if         CC_PolicyNV
#define TPM_CC_PolicyNV                     (TPM_CC)(0x00000149)
#endif
#if         CC_CertifyCreation
#define TPM_CC_CertifyCreation              (TPM_CC)(0x0000014A)
#endif
#if         CC_Duplicate
#define TPM_CC_Duplicate                    (TPM_CC)(0x0000014B)
#endif
#if         CC_GetTime
#define TPM_CC_GetTime                      (TPM_CC)(0x0000014C)
#endif
#if         CC_GetSessionAuditDigest
#define TPM_CC_GetSessionAuditDigest        (TPM_CC)(0x0000014D)
#endif
#if         CC_NV_Read
#define TPM_CC_NV_Read                      (TPM_CC)(0x0000014E)
#endif
#if         CC_NV_ReadLock
#define TPM_CC_NV_ReadLock                  (TPM_CC)(0x0000014F)
#endif
#if         CC_ObjectChangeAuth
#define TPM_CC_ObjectChangeAuth             (TPM_CC)(0x00000150)
#endif
#if         CC_PolicySecret
#define TPM_CC_PolicySecret                 (TPM_CC)(0x00000151)
#endif
#if         CC_Rewrap
#define TPM_CC_Rewrap                       (TPM_CC)(0x00000152)
#endif
#if         CC_Create
#define TPM_CC_Create                       (TPM_CC)(0x00000153)
#endif
#if         CC_ECDH_ZGen
#define TPM_CC_ECDH_ZGen                    (TPM_CC)(0x00000154)
#endif
#if         CC_HMAC
#define TPM_CC_HMAC                         (TPM_CC)(0x00000155)
#endif
#if         CC_MAC
#define TPM_CC_MAC                          (TPM_CC)(0x00000155)
#endif
#if         CC_Import
#define TPM_CC_Import                       (TPM_CC)(0x00000156)
#endif
#if         CC_Load
#define TPM_CC_Load                         (TPM_CC)(0x00000157)
#endif
#if         CC_Quote
#define TPM_CC_Quote                        (TPM_CC)(0x00000158)
#endif
#if         CC_RSA_Decrypt
#define TPM_CC_RSA_Decrypt                  (TPM_CC)(0x00000159)
#endif
#if         CC_HMAC_Start
#define TPM_CC_HMAC_Start                   (TPM_CC)(0x0000015B)
#endif
#if         CC_MAC_Start
#define TPM_CC_MAC_Start                    (TPM_CC)(0x0000015B)
#endif
#if         CC_SequenceUpdate
#define TPM_CC_SequenceUpdate               (TPM_CC)(0x0000015C)
#endif
#if         CC_Sign
#define TPM_CC_Sign                         (TPM_CC)(0x0000015D)
#endif
#if         CC_Unseal
#define TPM_CC_Unseal                       (TPM_CC)(0x0000015E)
#endif
#if         CC_PolicySigned
#define TPM_CC_PolicySigned                 (TPM_CC)(0x00000160)
#endif
#if         CC_ContextLoad
#define TPM_CC_ContextLoad                  (TPM_CC)(0x00000161)
#endif
#if         CC_ContextSave
#define TPM_CC_ContextSave                  (TPM_CC)(0x00000162)
#endif
#if         CC_ECDH_KeyGen
#define TPM_CC_ECDH_KeyGen                  (TPM_CC)(0x00000163)
#endif
#if         CC_EncryptDecrypt
#define TPM_CC_EncryptDecrypt               (TPM_CC)(0x00000164)
#endif
#if         CC_FlushContext
#define TPM_CC_FlushContext                 (TPM_CC)(0x00000165)
#endif
#if         CC_LoadExternal
#define TPM_CC_LoadExternal                 (TPM_CC)(0x00000167)
#endif
#if         CC_MakeCredential
#define TPM_CC_MakeCredential               (TPM_CC)(0x00000168)
#endif
#if         CC_NV_ReadPublic
#define TPM_CC_NV_ReadPublic                (TPM_CC)(0x00000169)
#endif
#if         CC_PolicyAuthorize
#define TPM_CC_PolicyAuthorize              (TPM_CC)(0x0000016A)
#endif
#if         CC_PolicyAuthValue
#define TPM_CC_PolicyAuthValue              (TPM_CC)(0x0000016B)
#endif
#if         CC_PolicyCommandCode
#define TPM_CC_PolicyCommandCode            (TPM_CC)(0x0000016C)
#endif
#if         CC_PolicyCounterTimer
#define TPM_CC_PolicyCounterTimer           (TPM_CC)(0x0000016D)
#endif
#if         CC_PolicyCpHash
#define TPM_CC_PolicyCpHash                 (TPM_CC)(0x0000016E)
#endif
#if         CC_PolicyLocality
#define TPM_CC_PolicyLocality               (TPM_CC)(0x0000016F)
#endif
#if         CC_PolicyNameHash
#define TPM_CC_PolicyNameHash               (TPM_CC)(0x00000170)
#endif
#if         CC_PolicyOR
#define TPM_CC_PolicyOR                     (TPM_CC)(0x00000171)
#endif
#if         CC_PolicyTicket
#define TPM_CC_PolicyTicket                 (TPM_CC)(0x00000172)
#endif
#if         CC_ReadPublic
#define TPM_CC_ReadPublic                   (TPM_CC)(0x00000173)
#endif
#if         CC_RSA_Encrypt
#define TPM_CC_RSA_Encrypt                  (TPM_CC)(0x00000174)
#endif
#if         CC_StartAuthSession
#define TPM_CC_StartAuthSession             (TPM_CC)(0x00000176)
#endif
#if         CC_VerifySignature
#define TPM_CC_VerifySignature              (TPM_CC)(0x00000177)
#endif
#if         CC_ECC_Parameters
#define TPM_CC_ECC_Parameters               (TPM_CC)(0x00000178)
#endif
#if         CC_FirmwareRead
#define TPM_CC_FirmwareRead                 (TPM_CC)(0x00000179)
#endif
#if         CC_GetCapability
#define TPM_CC_GetCapability                (TPM_CC)(0x0000017A)
#endif
#if         CC_GetRandom
#define TPM_CC_GetRandom                    (TPM_CC)(0x0000017B)
#endif
#if         CC_GetTestResult
#define TPM_CC_GetTestResult                (TPM_CC)(0x0000017C)
#endif
#if         CC_Hash
#define TPM_CC_Hash                         (TPM_CC)(0x0000017D)
#endif
#if         CC_PCR_Read
#define TPM_CC_PCR_Read                     (TPM_CC)(0x0000017E)
#endif
#if         CC_PolicyPCR
#define TPM_CC_PolicyPCR                    (TPM_CC)(0x0000017F)
#endif
#if         CC_PolicyRestart
#define TPM_CC_PolicyRestart                (TPM_CC)(0x00000180)
#endif
#if         CC_ReadClock
#define TPM_CC_ReadClock                    (TPM_CC)(0x00000181)
#endif
#if         CC_PCR_Extend
#define TPM_CC_PCR_Extend                   (TPM_CC)(0x00000182)
#endif
#if         CC_PCR_SetAuthValue
#define TPM_CC_PCR_SetAuthValue             (TPM_CC)(0x00000183)
#endif
#if         CC_NV_Certify
#define TPM_CC_NV_Certify                   (TPM_CC)(0x00000184)
#endif
#if         CC_EventSequenceComplete
#define TPM_CC_EventSequenceComplete        (TPM_CC)(0x00000185)
#endif
#if         CC_HashSequenceStart
#define TPM_CC_HashSequenceStart            (TPM_CC)(0x00000186)
#endif
#if         CC_PolicyPhysicalPresence
#define TPM_CC_PolicyPhysicalPresence       (TPM_CC)(0x00000187)
#endif
#if         CC_PolicyDuplicationSelect
#define TPM_CC_PolicyDuplicationSelect      (TPM_CC)(0x00000188)
#endif
#if         CC_PolicyGetDigest
#define TPM_CC_PolicyGetDigest              (TPM_CC)(0x00000189)
#endif
#if         CC_TestParms
#define TPM_CC_TestParms                    (TPM_CC)(0x0000018A)
#endif
#if         CC_Commit
#define TPM_CC_Commit                       (TPM_CC)(0x0000018B)
#endif
#if         CC_PolicyPassword
#define TPM_CC_PolicyPassword               (TPM_CC)(0x0000018C)
#endif
#if         CC_ZGen_2Phase
#define TPM_CC_ZGen_2Phase                  (TPM_CC)(0x0000018D)
#endif
#if         CC_EC_Ephemeral
#define TPM_CC_EC_Ephemeral                 (TPM_CC)(0x0000018E)
#endif
#if         CC_PolicyNvWritten
#define TPM_CC_PolicyNvWritten              (TPM_CC)(0x0000018F)
#endif
#if         CC_PolicyTemplate
#define TPM_CC_PolicyTemplate               (TPM_CC)(0x00000190)
#endif
#if         CC_CreateLoaded
#define TPM_CC_CreateLoaded                 (TPM_CC)(0x00000191)
#endif
#if         CC_PolicyAuthorizeNV
#define TPM_CC_PolicyAuthorizeNV            (TPM_CC)(0x00000192)
#endif
#if         CC_EncryptDecrypt2
#define TPM_CC_EncryptDecrypt2              (TPM_CC)(0x00000193)
#endif
#if         CC_AC_GetCapability
#define TPM_CC_AC_GetCapability             (TPM_CC)(0x00000194)
#endif
#if         CC_AC_Send
#define TPM_CC_AC_Send                      (TPM_CC)(0x00000195)
#endif
#if         CC_Policy_AC_SendSelect
#define TPM_CC_Policy_AC_SendSelect         (TPM_CC)(0x00000196)
#endif
#define CC_VEND                             0x20000000
#if         CC_Vendor_TCG_Test
#define TPM_CC_Vendor_TCG_Test              (TPM_CC)(0x20000000)
#endif

// Additional values for benefit of code
#define TPM_CC_FIRST                        0x0000011F
#define TPM_CC_LAST                         0x00000196

    
#if COMPRESSED_LISTS
#define ADD_FILL            0
#else
#define ADD_FILL            1
#endif

// Size the array of library commands based on whether or not
// the array is packed (only defined commands) or dense
// (having entries for unimplemented commands)
#define LIBRARY_COMMAND_ARRAY_SIZE       (0      \
    + (ADD_FILL || CC_NV_UndefineSpaceSpecial)              /* 0x0000011F */       \
    + (ADD_FILL || CC_EvictControl)                         /* 0x00000120 */       \
    + (ADD_FILL || CC_HierarchyControl)                     /* 0x00000121 */       \
    + (ADD_FILL || CC_NV_UndefineSpace)                     /* 0x00000122 */       \
    +  ADD_FILL                                             /* 0x00000123 */       \
    + (ADD_FILL || CC_ChangeEPS)                            /* 0x00000124 */       \
    + (ADD_FILL || CC_ChangePPS)                            /* 0x00000125 */       \
    + (ADD_FILL || CC_Clear)                                /* 0x00000126 */       \
    + (ADD_FILL || CC_ClearControl)                         /* 0x00000127 */       \
    + (ADD_FILL || CC_ClockSet)                             /* 0x00000128 */       \
    + (ADD_FILL || CC_HierarchyChangeAuth)                  /* 0x00000129 */       \
    + (ADD_FILL || CC_NV_DefineSpace)                       /* 0x0000012A */       \
    + (ADD_FILL || CC_PCR_Allocate)                         /* 0x0000012B */       \
    + (ADD_FILL || CC_PCR_SetAuthPolicy)                    /* 0x0000012C */       \
    + (ADD_FILL || CC_PP_Commands)                          /* 0x0000012D */       \
    + (ADD_FILL || CC_SetPrimaryPolicy)                     /* 0x0000012E */       \
    + (ADD_FILL || CC_FieldUpgradeStart)                    /* 0x0000012F */       \
    + (ADD_FILL || CC_ClockRateAdjust)                      /* 0x00000130 */       \
    + (ADD_FILL || CC_CreatePrimary)                        /* 0x00000131 */       \
    + (ADD_FILL || CC_NV_GlobalWriteLock)                   /* 0x00000132 */       \
    + (ADD_FILL || CC_GetCommandAuditDigest)                /* 0x00000133 */       \
    + (ADD_FILL || CC_NV_Increment)                         /* 0x00000134 */       \
    + (ADD_FILL || CC_NV_SetBits)                           /* 0x00000135 */       \
    + (ADD_FILL || CC_NV_Extend)                            /* 0x00000136 */       \
    + (ADD_FILL || CC_NV_Write)                             /* 0x00000137 */       \
    + (ADD_FILL || CC_NV_WriteLock)                         /* 0x00000138 */       \
    + (ADD_FILL || CC_DictionaryAttackLockReset)            /* 0x00000139 */       \
    + (ADD_FILL || CC_DictionaryAttackParameters)           /* 0x0000013A */       \
    + (ADD_FILL || CC_NV_ChangeAuth)                        /* 0x0000013B */       \
    + (ADD_FILL || CC_PCR_Event)                            /* 0x0000013C */       \
    + (ADD_FILL || CC_PCR_Reset)                            /* 0x0000013D */       \
    + (ADD_FILL || CC_SequenceComplete)                     /* 0x0000013E */       \
    + (ADD_FILL || CC_SetAlgorithmSet)                      /* 0x0000013F */       \
    + (ADD_FILL || CC_SetCommandCodeAuditStatus)            /* 0x00000140 */       \
    + (ADD_FILL || CC_FieldUpgradeData)                     /* 0x00000141 */       \
    + (ADD_FILL || CC_IncrementalSelfTest)                  /* 0x00000142 */       \
    + (ADD_FILL || CC_SelfTest)                             /* 0x00000143 */       \
    + (ADD_FILL || CC_Startup)                              /* 0x00000144 */       \
    + (ADD_FILL || CC_Shutdown)                             /* 0x00000145 */       \
    + (ADD_FILL || CC_StirRandom)                           /* 0x00000146 */       \
    + (ADD_FILL || CC_ActivateCredential)                   /* 0x00000147 */       \
    + (ADD_FILL || CC_Certify)                              /* 0x00000148 */       \
    + (ADD_FILL || CC_PolicyNV)                             /* 0x00000149 */       \
    + (ADD_FILL || CC_CertifyCreation)                      /* 0x0000014A */       \
    + (ADD_FILL || CC_Duplicate)                            /* 0x0000014B */       \
    + (ADD_FILL || CC_GetTime)                              /* 0x0000014C */       \
    + (ADD_FILL || CC_GetSessionAuditDigest)                /* 0x0000014D */       \
    + (ADD_FILL || CC_NV_Read)                              /* 0x0000014E */       \
    + (ADD_FILL || CC_NV_ReadLock)                          /* 0x0000014F */       \
    + (ADD_FILL || CC_ObjectChangeAuth)                     /* 0x00000150 */       \
    + (ADD_FILL || CC_PolicySecret)                         /* 0x00000151 */       \
    + (ADD_FILL || CC_Rewrap)                               /* 0x00000152 */       \
    + (ADD_FILL || CC_Create)                               /* 0x00000153 */       \
    + (ADD_FILL || CC_ECDH_ZGen)                            /* 0x00000154 */       \
    + (ADD_FILL || CC_HMAC || CC_MAC)                       /* 0x00000155 */       \
    + (ADD_FILL || CC_Import)                               /* 0x00000156 */       \
    + (ADD_FILL || CC_Load)                                 /* 0x00000157 */       \
    + (ADD_FILL || CC_Quote)                                /* 0x00000158 */       \
    + (ADD_FILL || CC_RSA_Decrypt)                          /* 0x00000159 */       \
    +  ADD_FILL                                             /* 0x0000015A */       \
    + (ADD_FILL || CC_HMAC_Start || CC_MAC_Start)           /* 0x0000015B */       \
    + (ADD_FILL || CC_SequenceUpdate)                       /* 0x0000015C */       \
    + (ADD_FILL || CC_Sign)                                 /* 0x0000015D */       \
    + (ADD_FILL || CC_Unseal)                               /* 0x0000015E */       \
    +  ADD_FILL                                             /* 0x0000015F */       \
    + (ADD_FILL || CC_PolicySigned)                         /* 0x00000160 */       \
    + (ADD_FILL || CC_ContextLoad)                          /* 0x00000161 */       \
    + (ADD_FILL || CC_ContextSave)                          /* 0x00000162 */       \
    + (ADD_FILL || CC_ECDH_KeyGen)                          /* 0x00000163 */       \
    + (ADD_FILL || CC_EncryptDecrypt)                       /* 0x00000164 */       \
    + (ADD_FILL || CC_FlushContext)                         /* 0x00000165 */       \
    +  ADD_FILL                                             /* 0x00000166 */       \
    + (ADD_FILL || CC_LoadExternal)                         /* 0x00000167 */       \
    + (ADD_FILL || CC_MakeCredential)                       /* 0x00000168 */       \
    + (ADD_FILL || CC_NV_ReadPublic)                        /* 0x00000169 */       \
    + (ADD_FILL || CC_PolicyAuthorize)                      /* 0x0000016A */       \
    + (ADD_FILL || CC_PolicyAuthValue)                      /* 0x0000016B */       \
    + (ADD_FILL || CC_PolicyCommandCode)                    /* 0x0000016C */       \
    + (ADD_FILL || CC_PolicyCounterTimer)                   /* 0x0000016D */       \
    + (ADD_FILL || CC_PolicyCpHash)                         /* 0x0000016E */       \
    + (ADD_FILL || CC_PolicyLocality)                       /* 0x0000016F */       \
    + (ADD_FILL || CC_PolicyNameHash)                       /* 0x00000170 */       \
    + (ADD_FILL || CC_PolicyOR)                             /* 0x00000171 */       \
    + (ADD_FILL || CC_PolicyTicket)                         /* 0x00000172 */       \
    + (ADD_FILL || CC_ReadPublic)                           /* 0x00000173 */       \
    + (ADD_FILL || CC_RSA_Encrypt)                          /* 0x00000174 */       \
    +  ADD_FILL                                             /* 0x00000175 */       \
    + (ADD_FILL || CC_StartAuthSession)                     /* 0x00000176 */       \
    + (ADD_FILL || CC_VerifySignature)                      /* 0x00000177 */       \
    + (ADD_FILL || CC_ECC_Parameters)                       /* 0x00000178 */       \
    + (ADD_FILL || CC_FirmwareRead)                         /* 0x00000179 */       \
    + (ADD_FILL || CC_GetCapability)                        /* 0x0000017A */       \
    + (ADD_FILL || CC_GetRandom)                            /* 0x0000017B */       \
    + (ADD_FILL || CC_GetTestResult)                        /* 0x0000017C */       \
    + (ADD_FILL || CC_Hash)                                 /* 0x0000017D */       \
    + (ADD_FILL || CC_PCR_Read)                             /* 0x0000017E */       \
    + (ADD_FILL || CC_PolicyPCR)                            /* 0x0000017F */       \
    + (ADD_FILL || CC_PolicyRestart)                        /* 0x00000180 */       \
    + (ADD_FILL || CC_ReadClock)                            /* 0x00000181 */       \
    + (ADD_FILL || CC_PCR_Extend)                           /* 0x00000182 */       \
    + (ADD_FILL || CC_PCR_SetAuthValue)                     /* 0x00000183 */       \
    + (ADD_FILL || CC_NV_Certify)                           /* 0x00000184 */       \
    + (ADD_FILL || CC_EventSequenceComplete)                /* 0x00000185 */       \
    + (ADD_FILL || CC_HashSequenceStart)                    /* 0x00000186 */       \
    + (ADD_FILL || CC_PolicyPhysicalPresence)               /* 0x00000187 */       \
    + (ADD_FILL || CC_PolicyDuplicationSelect)              /* 0x00000188 */       \
    + (ADD_FILL || CC_PolicyGetDigest)                      /* 0x00000189 */       \
    + (ADD_FILL || CC_TestParms)                            /* 0x0000018A */       \
    + (ADD_FILL || CC_Commit)                               /* 0x0000018B */       \
    + (ADD_FILL || CC_PolicyPassword)                       /* 0x0000018C */       \
    + (ADD_FILL || CC_ZGen_2Phase)                          /* 0x0000018D */       \
    + (ADD_FILL || CC_EC_Ephemeral)                         /* 0x0000018E */       \
    + (ADD_FILL || CC_PolicyNvWritten)                      /* 0x0000018F */       \
    + (ADD_FILL || CC_PolicyTemplate)                       /* 0x00000190 */       \
    + (ADD_FILL || CC_CreateLoaded)                         /* 0x00000191 */       \
    + (ADD_FILL || CC_PolicyAuthorizeNV)                    /* 0x00000192 */       \
    + (ADD_FILL || CC_EncryptDecrypt2)                      /* 0x00000193 */       \
    + (ADD_FILL || CC_AC_GetCapability)                     /* 0x00000194 */       \
    + (ADD_FILL || CC_AC_Send)                              /* 0x00000195 */       \
    + (ADD_FILL || CC_Policy_AC_SendSelect)                 /* 0x00000196 */       \
    )

#define VENDOR_COMMAND_ARRAY_SIZE   (0 + CC_Vendor_TCG_Test)

#define COMMAND_COUNT       (LIBRARY_COMMAND_ARRAY_SIZE + VENDOR_COMMAND_ARRAY_SIZE)

#define HASH_COUNT          \
            (ALG_SHA1 + ALG_SHA256 + ALG_SHA384 + ALG_SHA512 + ALG_SM3_256)

#define MAX_HASH_BLOCK_SIZE \
            (MAX(ALG_SHA1    * SHA1_BLOCK_SIZE,                                    \
             MAX(ALG_SHA256  * SHA256_BLOCK_SIZE,                                  \
             MAX(ALG_SHA384  * SHA384_BLOCK_SIZE,                                  \
             MAX(ALG_SHA512  * SHA512_BLOCK_SIZE,                                  \
             MAX(ALG_SM3_256 * SM3_256_BLOCK_SIZE,                                 \
             0))))))

#define MAX_DIGEST_SIZE     \
            (MAX(ALG_SHA1    * SHA1_DIGEST_SIZE,                                   \
             MAX(ALG_SHA256  * SHA256_DIGEST_SIZE,                                 \
             MAX(ALG_SHA384  * SHA384_DIGEST_SIZE,                                 \
             MAX(ALG_SHA512  * SHA512_DIGEST_SIZE,                                 \
             MAX(ALG_SM3_256 * SM3_256_DIGEST_SIZE,                                \
             0))))))


#if MAX_DIGEST_SIZE == 0 || MAX_HASH_BLOCK_SIZE == 0
#error "Hash data not valid"
#endif

// Define the 2B structure that would hold any hash block
TPM2B_TYPE(MAX_HASH_BLOCK, MAX_HASH_BLOCK_SIZE);

// Following typedef is for some old code
typedef TPM2B_MAX_HASH_BLOCK    TPM2B_HASH_BLOCK;

/* AddSymmetricConstants */
#ifndef ALG_AES
#define ALG_AES                         NO
#endif
#ifndef MAX_AES_KEY_BITS
#define MAX_AES_KEY_BITS                0
#define MAX_AES_BLOCK_SIZE_BYTES        0
#endif
#ifndef ALG_CAMELLIA
#define ALG_CAMELLIA                    NO
#endif
#ifndef MAX_CAMELLIA_KEY_BITS
#define MAX_CAMELLIA_KEY_BITS           0
#define MAX_CAMELLIA_BLOCK_SIZE_BYTES   0
#endif
#ifndef ALG_SM4
#define ALG_SM4                         NO
#endif
#ifndef MAX_SM4_KEY_BITS
#define MAX_SM4_KEY_BITS                0
#define MAX_SM4_BLOCK_SIZE_BYTES        0
#endif
#ifndef ALG_TDES
#define ALG_TDES                        NO
#endif
#ifndef MAX_TDES_KEY_BITS
#define MAX_TDES_KEY_BITS               0
#define MAX_TDES_BLOCK_SIZE_BYTES       0
#endif
#define MAX_SYM_KEY_BITS                \
            (MAX(ALG_AES      * MAX_AES_KEY_BITS,                                  \
             MAX(ALG_CAMELLIA * MAX_CAMELLIA_KEY_BITS,                             \
             MAX(ALG_SM4      * MAX_SM4_KEY_BITS,                                  \
             MAX(ALG_TDES     * MAX_TDES_KEY_BITS,                                 \
             0)))))

#define MAX_SYM_KEY_BYTES               ((MAX_SYM_KEY_BITS + 7) / 8)

#define MAX_SYM_BLOCK_SIZE              \
            (MAX(ALG_AES      * MAX_AES_BLOCK_SIZE_BYTES,                          \
             MAX(ALG_CAMELLIA * MAX_CAMELLIA_BLOCK_SIZE_BYTES,                     \
             MAX(ALG_SM4      * MAX_SM4_BLOCK_SIZE_BYTES,                          \
             MAX(ALG_TDES     * MAX_TDES_BLOCK_SIZE_BYTES,                         \
             0)))))

#if MAX_SYM_KEY_BITS == 0 || MAX_SYM_BLOCK_SIZE == 0
#   error Bad size for MAX_SYM_KEY_BITS or MAX_SYM_BLOCK_SIZE
#endif

#endif  // _IMPLEMENTATION_H_
