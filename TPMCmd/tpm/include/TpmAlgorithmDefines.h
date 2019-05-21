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
/*(Auto-generated)
 *  Created by TpmStructures; Version 4.4 Mar 26, 2019
 *  Date: Apr  7, 2019  Time: 06:58:55PM
 */

#ifndef _TPM_ALGORITHM_DEFINES_H_
#define _TPM_ALGORITHM_DEFINES_H_

// Table 2:3 - Definition of Base Types
// Base Types are in BaseTypes.h


// Table 2:4 - Defines for Logic Values


// Table 0:1 - Defines for Processor Values


// Table 0:3 - Defines for Key Size Constants


// Table 0:4 - Defines for Implemented Curves

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


// Table 0:2 - Defines for Implemented Algorithms


// Table 1:2 - Definition of TPM_ALG_ID Constants
typedef UINT16                          TPM_ALG_ID;
#define TYPE_OF_TPM_ALG_ID              UINT16
#define     ALG_ERROR_VALUE             0x0000
#define TPM_ALG_ERROR                   (TPM_ALG_ID)(ALG_ERROR_VALUE)
#define     ALG_RSA_VALUE               0x0001
#define TPM_ALG_RSA                     (TPM_ALG_ID)(ALG_RSA_VALUE)
#define     ALG_TDES_VALUE              0x0003
#define TPM_ALG_TDES                    (TPM_ALG_ID)(ALG_TDES_VALUE)
#define     ALG_SHA_VALUE               0x0004
#define TPM_ALG_SHA                     (TPM_ALG_ID)(ALG_SHA_VALUE)
#define     ALG_SHA1_VALUE              0x0004
#define TPM_ALG_SHA1                    (TPM_ALG_ID)(ALG_SHA1_VALUE)
#define     ALG_HMAC_VALUE              0x0005
#define TPM_ALG_HMAC                    (TPM_ALG_ID)(ALG_HMAC_VALUE)
#define     ALG_AES_VALUE               0x0006
#define TPM_ALG_AES                     (TPM_ALG_ID)(ALG_AES_VALUE)
#define     ALG_MGF1_VALUE              0x0007
#define TPM_ALG_MGF1                    (TPM_ALG_ID)(ALG_MGF1_VALUE)
#define     ALG_KEYEDHASH_VALUE         0x0008
#define TPM_ALG_KEYEDHASH               (TPM_ALG_ID)(ALG_KEYEDHASH_VALUE)
#define     ALG_XOR_VALUE               0x000A
#define TPM_ALG_XOR                     (TPM_ALG_ID)(ALG_XOR_VALUE)
#define     ALG_SHA256_VALUE            0x000B
#define TPM_ALG_SHA256                  (TPM_ALG_ID)(ALG_SHA256_VALUE)
#define     ALG_SHA384_VALUE            0x000C
#define TPM_ALG_SHA384                  (TPM_ALG_ID)(ALG_SHA384_VALUE)
#define     ALG_SHA512_VALUE            0x000D
#define TPM_ALG_SHA512                  (TPM_ALG_ID)(ALG_SHA512_VALUE)
#define     ALG_NULL_VALUE              0x0010
#define TPM_ALG_NULL                    (TPM_ALG_ID)(ALG_NULL_VALUE)
#define     ALG_SM3_256_VALUE           0x0012
#define TPM_ALG_SM3_256                 (TPM_ALG_ID)(ALG_SM3_256_VALUE)
#define     ALG_SM4_VALUE               0x0013
#define TPM_ALG_SM4                     (TPM_ALG_ID)(ALG_SM4_VALUE)
#define     ALG_RSASSA_VALUE            0x0014
#define TPM_ALG_RSASSA                  (TPM_ALG_ID)(ALG_RSASSA_VALUE)
#define     ALG_RSAES_VALUE             0x0015
#define TPM_ALG_RSAES                   (TPM_ALG_ID)(ALG_RSAES_VALUE)
#define     ALG_RSAPSS_VALUE            0x0016
#define TPM_ALG_RSAPSS                  (TPM_ALG_ID)(ALG_RSAPSS_VALUE)
#define     ALG_OAEP_VALUE              0x0017
#define TPM_ALG_OAEP                    (TPM_ALG_ID)(ALG_OAEP_VALUE)
#define     ALG_ECDSA_VALUE             0x0018
#define TPM_ALG_ECDSA                   (TPM_ALG_ID)(ALG_ECDSA_VALUE)
#define     ALG_ECDH_VALUE              0x0019
#define TPM_ALG_ECDH                    (TPM_ALG_ID)(ALG_ECDH_VALUE)
#define     ALG_ECDAA_VALUE             0x001A
#define TPM_ALG_ECDAA                   (TPM_ALG_ID)(ALG_ECDAA_VALUE)
#define     ALG_SM2_VALUE               0x001B
#define TPM_ALG_SM2                     (TPM_ALG_ID)(ALG_SM2_VALUE)
#define     ALG_ECSCHNORR_VALUE         0x001C
#define TPM_ALG_ECSCHNORR               (TPM_ALG_ID)(ALG_ECSCHNORR_VALUE)
#define     ALG_ECMQV_VALUE             0x001D
#define TPM_ALG_ECMQV                   (TPM_ALG_ID)(ALG_ECMQV_VALUE)
#define     ALG_KDF1_SP800_56A_VALUE    0x0020
#define TPM_ALG_KDF1_SP800_56A          (TPM_ALG_ID)(ALG_KDF1_SP800_56A_VALUE)
#define     ALG_KDF2_VALUE              0x0021
#define TPM_ALG_KDF2                    (TPM_ALG_ID)(ALG_KDF2_VALUE)
#define     ALG_KDF1_SP800_108_VALUE    0x0022
#define TPM_ALG_KDF1_SP800_108          (TPM_ALG_ID)(ALG_KDF1_SP800_108_VALUE)
#define     ALG_ECC_VALUE               0x0023
#define TPM_ALG_ECC                     (TPM_ALG_ID)(ALG_ECC_VALUE)
#define     ALG_SYMCIPHER_VALUE         0x0025
#define TPM_ALG_SYMCIPHER               (TPM_ALG_ID)(ALG_SYMCIPHER_VALUE)
#define     ALG_CAMELLIA_VALUE          0x0026
#define TPM_ALG_CAMELLIA                (TPM_ALG_ID)(ALG_CAMELLIA_VALUE)
#define     ALG_SHA3_256_VALUE          0x0027
#define TPM_ALG_SHA3_256                (TPM_ALG_ID)(ALG_SHA3_256_VALUE)
#define     ALG_SHA3_384_VALUE          0x0028
#define TPM_ALG_SHA3_384                (TPM_ALG_ID)(ALG_SHA3_384_VALUE)
#define     ALG_SHA3_512_VALUE          0x0029
#define TPM_ALG_SHA3_512                (TPM_ALG_ID)(ALG_SHA3_512_VALUE)
#define     ALG_CMAC_VALUE              0x003F
#define TPM_ALG_CMAC                    (TPM_ALG_ID)(ALG_CMAC_VALUE)
#define     ALG_CTR_VALUE               0x0040
#define TPM_ALG_CTR                     (TPM_ALG_ID)(ALG_CTR_VALUE)
#define     ALG_OFB_VALUE               0x0041
#define TPM_ALG_OFB                     (TPM_ALG_ID)(ALG_OFB_VALUE)
#define     ALG_CBC_VALUE               0x0042
#define TPM_ALG_CBC                     (TPM_ALG_ID)(ALG_CBC_VALUE)
#define     ALG_CFB_VALUE               0x0043
#define TPM_ALG_CFB                     (TPM_ALG_ID)(ALG_CFB_VALUE)
#define     ALG_ECB_VALUE               0x0044
#define TPM_ALG_ECB                     (TPM_ALG_ID)(ALG_ECB_VALUE)
// Values derived from Table 1:2
#define     ALG_FIRST_VALUE             0x0001
#define TPM_ALG_FIRST                   (TPM_ALG_ID)(ALG_FIRST_VALUE)
#define     ALG_LAST_VALUE              0x0044
#define TPM_ALG_LAST                    (TPM_ALG_ID)(ALG_LAST_VALUE)


// Table 1:3 - Definition of TPM_ECC_CURVE Constants
typedef UINT16              TPM_ECC_CURVE;
#define TYPE_OF_TPM_ECC_CURVE   UINT16
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


// Table 1:13 - Defines for SHA256 Hash Values
#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE   64


// Table 1:14 - Defines for SHA384 Hash Values
#define SHA384_DIGEST_SIZE  48
#define SHA384_BLOCK_SIZE   128


// Table 1:15 - Defines for SHA512 Hash Values
#define SHA512_DIGEST_SIZE  64
#define SHA512_BLOCK_SIZE   128


// Table 1:16 - Defines for SM3_256 Hash Values
#define SM3_256_DIGEST_SIZE     32
#define SM3_256_BLOCK_SIZE      64


// Table 1:16 - Defines for SHA3_256 Hash Values
#define SHA3_256_DIGEST_SIZE    32
#define SHA3_256_BLOCK_SIZE     136


// Table 1:16 - Defines for SHA3_384 Hash Values
#define SHA3_384_DIGEST_SIZE    48
#define SHA3_384_BLOCK_SIZE     104


// Table 1:16 - Defines for SHA3_512 Hash Values
#define SHA3_512_DIGEST_SIZE    64
#define SHA3_512_BLOCK_SIZE     72


// Table 1:00 - Defines for RSA Asymmetric Cipher Algorithm Constants
#define RSA_KEY_SIZES_BITS          \
            (1024 * RSA_1024),  (2048 * RSA_2048), (3072 * RSA_3072),              \
             (4096 * RSA_4096)
#if   RSA_4096
#   define RSA_MAX_KEY_SIZE_BITS    4096
#elif RSA_3072
#   define RSA_MAX_KEY_SIZE_BITS    3072
#elif RSA_2048
#   define RSA_MAX_KEY_SIZE_BITS    2048
#elif RSA_1024
#   define RSA_MAX_KEY_SIZE_BITS    1024
#else
#   define RSA_MAX_KEY_SIZE_BITS    0
#endif
#define MAX_RSA_KEY_BITS            RSA_MAX_KEY_SIZE_BITS
#define MAX_RSA_KEY_BYTES           ((RSA_MAX_KEY_SIZE_BITS + 7) / 8)


// Table 1:17 - Defines for AES Symmetric Cipher Algorithm Constants
#define AES_KEY_SIZES_BITS          \
            (128 * AES_128), (192 * AES_192), (256 * AES_256)
#if   AES_256
#   define AES_MAX_KEY_SIZE_BITS    256
#elif AES_192
#   define AES_MAX_KEY_SIZE_BITS    192
#elif AES_128
#   define AES_MAX_KEY_SIZE_BITS    128
#else
#   define AES_MAX_KEY_SIZE_BITS    0
#endif
#define MAX_AES_KEY_BITS            AES_MAX_KEY_SIZE_BITS
#define MAX_AES_KEY_BYTES           ((AES_MAX_KEY_SIZE_BITS + 7) / 8)
#define AES_128_BLOCK_SIZE_BYTES    (AES_128 * 16)
#define AES_192_BLOCK_SIZE_BYTES    (AES_192 * 16)
#define AES_256_BLOCK_SIZE_BYTES    (AES_256 * 16)
#define AES_BLOCK_SIZES             \
            AES_128_BLOCK_SIZE_BYTES, AES_192_BLOCK_SIZE_BYTES,                    \
            AES_256_BLOCK_SIZE_BYTES
#if   ALG_AES
#   define AES_MAX_BLOCK_SIZE       16
#else
#   define AES_MAX_BLOCK_SIZE       0
#endif
#define MAX_AES_BLOCK_SIZE_BYTES    AES_MAX_BLOCK_SIZE


// Table 1:18 - Defines for SM4 Symmetric Cipher Algorithm Constants
#define SM4_KEY_SIZES_BITS          (128 * SM4_128)
#if   SM4_128
#   define SM4_MAX_KEY_SIZE_BITS    128
#else
#   define SM4_MAX_KEY_SIZE_BITS    0
#endif
#define MAX_SM4_KEY_BITS            SM4_MAX_KEY_SIZE_BITS
#define MAX_SM4_KEY_BYTES           ((SM4_MAX_KEY_SIZE_BITS + 7) / 8)
#define SM4_128_BLOCK_SIZE_BYTES    (SM4_128 * 16)
#define SM4_BLOCK_SIZES             SM4_128_BLOCK_SIZE_BYTES
#if   ALG_SM4
#   define SM4_MAX_BLOCK_SIZE       16
#else
#   define SM4_MAX_BLOCK_SIZE       0
#endif
#define MAX_SM4_BLOCK_SIZE_BYTES    SM4_MAX_BLOCK_SIZE


// Table 1:19 - Defines for CAMELLIA Symmetric Cipher Algorithm Constants
#define CAMELLIA_KEY_SIZES_BITS         \
            (128 * CAMELLIA_128), (192 * CAMELLIA_192), (256 * CAMELLIA_256)
#if   CAMELLIA_256
#   define CAMELLIA_MAX_KEY_SIZE_BITS   256
#elif CAMELLIA_192
#   define CAMELLIA_MAX_KEY_SIZE_BITS   192
#elif CAMELLIA_128
#   define CAMELLIA_MAX_KEY_SIZE_BITS   128
#else
#   define CAMELLIA_MAX_KEY_SIZE_BITS   0
#endif
#define MAX_CAMELLIA_KEY_BITS           CAMELLIA_MAX_KEY_SIZE_BITS
#define MAX_CAMELLIA_KEY_BYTES          ((CAMELLIA_MAX_KEY_SIZE_BITS + 7) / 8)
#define CAMELLIA_128_BLOCK_SIZE_BYTES   (CAMELLIA_128 * 16)
#define CAMELLIA_192_BLOCK_SIZE_BYTES   (CAMELLIA_192 * 16)
#define CAMELLIA_256_BLOCK_SIZE_BYTES   (CAMELLIA_256 * 16)
#define CAMELLIA_BLOCK_SIZES            \
            CAMELLIA_128_BLOCK_SIZE_BYTES, CAMELLIA_192_BLOCK_SIZE_BYTES,          \
            CAMELLIA_256_BLOCK_SIZE_BYTES
#if   ALG_CAMELLIA
#   define CAMELLIA_MAX_BLOCK_SIZE      16
#else
#   define CAMELLIA_MAX_BLOCK_SIZE      0
#endif
#define MAX_CAMELLIA_BLOCK_SIZE_BYTES   CAMELLIA_MAX_BLOCK_SIZE


// Table 1:17 - Defines for TDES Symmetric Cipher Algorithm Constants
#define TDES_KEY_SIZES_BITS         (128 * TDES_128), (192 * TDES_192)
#if   TDES_192
#   define TDES_MAX_KEY_SIZE_BITS   192
#elif TDES_128
#   define TDES_MAX_KEY_SIZE_BITS   128
#else
#   define TDES_MAX_KEY_SIZE_BITS   0
#endif
#define MAX_TDES_KEY_BITS           TDES_MAX_KEY_SIZE_BITS
#define MAX_TDES_KEY_BYTES          ((TDES_MAX_KEY_SIZE_BITS + 7) / 8)
#define TDES_128_BLOCK_SIZE_BYTES   (TDES_128 * 8)
#define TDES_192_BLOCK_SIZE_BYTES   (TDES_192 * 8)
#define TDES_BLOCK_SIZES            \
            TDES_128_BLOCK_SIZE_BYTES, TDES_192_BLOCK_SIZE_BYTES
#if   ALG_TDES
#   define TDES_MAX_BLOCK_SIZE      8
#else
#   define TDES_MAX_BLOCK_SIZE      0
#endif
#define MAX_TDES_BLOCK_SIZE_BYTES   TDES_MAX_BLOCK_SIZE


// Table 0:5 - Defines for Implemented Commands


// Table 2:12 - Definition of TPM_CC Constants
typedef UINT32                              TPM_CC;
#define TYPE_OF_TPM_CC                      UINT32
#define TPM_CC_NV_UndefineSpaceSpecial      (TPM_CC)(0x0000011F)
#define TPM_CC_EvictControl                 (TPM_CC)(0x00000120)
#define TPM_CC_HierarchyControl             (TPM_CC)(0x00000121)
#define TPM_CC_NV_UndefineSpace             (TPM_CC)(0x00000122)
#define TPM_CC_ChangeEPS                    (TPM_CC)(0x00000124)
#define TPM_CC_ChangePPS                    (TPM_CC)(0x00000125)
#define TPM_CC_Clear                        (TPM_CC)(0x00000126)
#define TPM_CC_ClearControl                 (TPM_CC)(0x00000127)
#define TPM_CC_ClockSet                     (TPM_CC)(0x00000128)
#define TPM_CC_HierarchyChangeAuth          (TPM_CC)(0x00000129)
#define TPM_CC_NV_DefineSpace               (TPM_CC)(0x0000012A)
#define TPM_CC_PCR_Allocate                 (TPM_CC)(0x0000012B)
#define TPM_CC_PCR_SetAuthPolicy            (TPM_CC)(0x0000012C)
#define TPM_CC_PP_Commands                  (TPM_CC)(0x0000012D)
#define TPM_CC_SetPrimaryPolicy             (TPM_CC)(0x0000012E)
#define TPM_CC_FieldUpgradeStart            (TPM_CC)(0x0000012F)
#define TPM_CC_ClockRateAdjust              (TPM_CC)(0x00000130)
#define TPM_CC_CreatePrimary                (TPM_CC)(0x00000131)
#define TPM_CC_NV_GlobalWriteLock           (TPM_CC)(0x00000132)
#define TPM_CC_GetCommandAuditDigest        (TPM_CC)(0x00000133)
#define TPM_CC_NV_Increment                 (TPM_CC)(0x00000134)
#define TPM_CC_NV_SetBits                   (TPM_CC)(0x00000135)
#define TPM_CC_NV_Extend                    (TPM_CC)(0x00000136)
#define TPM_CC_NV_Write                     (TPM_CC)(0x00000137)
#define TPM_CC_NV_WriteLock                 (TPM_CC)(0x00000138)
#define TPM_CC_DictionaryAttackLockReset    (TPM_CC)(0x00000139)
#define TPM_CC_DictionaryAttackParameters   (TPM_CC)(0x0000013A)
#define TPM_CC_NV_ChangeAuth                (TPM_CC)(0x0000013B)
#define TPM_CC_PCR_Event                    (TPM_CC)(0x0000013C)
#define TPM_CC_PCR_Reset                    (TPM_CC)(0x0000013D)
#define TPM_CC_SequenceComplete             (TPM_CC)(0x0000013E)
#define TPM_CC_SetAlgorithmSet              (TPM_CC)(0x0000013F)
#define TPM_CC_SetCommandCodeAuditStatus    (TPM_CC)(0x00000140)
#define TPM_CC_FieldUpgradeData             (TPM_CC)(0x00000141)
#define TPM_CC_IncrementalSelfTest          (TPM_CC)(0x00000142)
#define TPM_CC_SelfTest                     (TPM_CC)(0x00000143)
#define TPM_CC_Startup                      (TPM_CC)(0x00000144)
#define TPM_CC_Shutdown                     (TPM_CC)(0x00000145)
#define TPM_CC_StirRandom                   (TPM_CC)(0x00000146)
#define TPM_CC_ActivateCredential           (TPM_CC)(0x00000147)
#define TPM_CC_Certify                      (TPM_CC)(0x00000148)
#define TPM_CC_PolicyNV                     (TPM_CC)(0x00000149)
#define TPM_CC_CertifyCreation              (TPM_CC)(0x0000014A)
#define TPM_CC_Duplicate                    (TPM_CC)(0x0000014B)
#define TPM_CC_GetTime                      (TPM_CC)(0x0000014C)
#define TPM_CC_GetSessionAuditDigest        (TPM_CC)(0x0000014D)
#define TPM_CC_NV_Read                      (TPM_CC)(0x0000014E)
#define TPM_CC_NV_ReadLock                  (TPM_CC)(0x0000014F)
#define TPM_CC_ObjectChangeAuth             (TPM_CC)(0x00000150)
#define TPM_CC_PolicySecret                 (TPM_CC)(0x00000151)
#define TPM_CC_Rewrap                       (TPM_CC)(0x00000152)
#define TPM_CC_Create                       (TPM_CC)(0x00000153)
#define TPM_CC_ECDH_ZGen                    (TPM_CC)(0x00000154)
#define TPM_CC_HMAC                         (TPM_CC)(0x00000155)
#define TPM_CC_MAC                          (TPM_CC)(0x00000155)
#define TPM_CC_Import                       (TPM_CC)(0x00000156)
#define TPM_CC_Load                         (TPM_CC)(0x00000157)
#define TPM_CC_Quote                        (TPM_CC)(0x00000158)
#define TPM_CC_RSA_Decrypt                  (TPM_CC)(0x00000159)
#define TPM_CC_HMAC_Start                   (TPM_CC)(0x0000015B)
#define TPM_CC_MAC_Start                    (TPM_CC)(0x0000015B)
#define TPM_CC_SequenceUpdate               (TPM_CC)(0x0000015C)
#define TPM_CC_Sign                         (TPM_CC)(0x0000015D)
#define TPM_CC_Unseal                       (TPM_CC)(0x0000015E)
#define TPM_CC_PolicySigned                 (TPM_CC)(0x00000160)
#define TPM_CC_ContextLoad                  (TPM_CC)(0x00000161)
#define TPM_CC_ContextSave                  (TPM_CC)(0x00000162)
#define TPM_CC_ECDH_KeyGen                  (TPM_CC)(0x00000163)
#define TPM_CC_EncryptDecrypt               (TPM_CC)(0x00000164)
#define TPM_CC_FlushContext                 (TPM_CC)(0x00000165)
#define TPM_CC_LoadExternal                 (TPM_CC)(0x00000167)
#define TPM_CC_MakeCredential               (TPM_CC)(0x00000168)
#define TPM_CC_NV_ReadPublic                (TPM_CC)(0x00000169)
#define TPM_CC_PolicyAuthorize              (TPM_CC)(0x0000016A)
#define TPM_CC_PolicyAuthValue              (TPM_CC)(0x0000016B)
#define TPM_CC_PolicyCommandCode            (TPM_CC)(0x0000016C)
#define TPM_CC_PolicyCounterTimer           (TPM_CC)(0x0000016D)
#define TPM_CC_PolicyCpHash                 (TPM_CC)(0x0000016E)
#define TPM_CC_PolicyLocality               (TPM_CC)(0x0000016F)
#define TPM_CC_PolicyNameHash               (TPM_CC)(0x00000170)
#define TPM_CC_PolicyOR                     (TPM_CC)(0x00000171)
#define TPM_CC_PolicyTicket                 (TPM_CC)(0x00000172)
#define TPM_CC_ReadPublic                   (TPM_CC)(0x00000173)
#define TPM_CC_RSA_Encrypt                  (TPM_CC)(0x00000174)
#define TPM_CC_StartAuthSession             (TPM_CC)(0x00000176)
#define TPM_CC_VerifySignature              (TPM_CC)(0x00000177)
#define TPM_CC_ECC_Parameters               (TPM_CC)(0x00000178)
#define TPM_CC_FirmwareRead                 (TPM_CC)(0x00000179)
#define TPM_CC_GetCapability                (TPM_CC)(0x0000017A)
#define TPM_CC_GetRandom                    (TPM_CC)(0x0000017B)
#define TPM_CC_GetTestResult                (TPM_CC)(0x0000017C)
#define TPM_CC_Hash                         (TPM_CC)(0x0000017D)
#define TPM_CC_PCR_Read                     (TPM_CC)(0x0000017E)
#define TPM_CC_PolicyPCR                    (TPM_CC)(0x0000017F)
#define TPM_CC_PolicyRestart                (TPM_CC)(0x00000180)
#define TPM_CC_ReadClock                    (TPM_CC)(0x00000181)
#define TPM_CC_PCR_Extend                   (TPM_CC)(0x00000182)
#define TPM_CC_PCR_SetAuthValue             (TPM_CC)(0x00000183)
#define TPM_CC_NV_Certify                   (TPM_CC)(0x00000184)
#define TPM_CC_EventSequenceComplete        (TPM_CC)(0x00000185)
#define TPM_CC_HashSequenceStart            (TPM_CC)(0x00000186)
#define TPM_CC_PolicyPhysicalPresence       (TPM_CC)(0x00000187)
#define TPM_CC_PolicyDuplicationSelect      (TPM_CC)(0x00000188)
#define TPM_CC_PolicyGetDigest              (TPM_CC)(0x00000189)
#define TPM_CC_TestParms                    (TPM_CC)(0x0000018A)
#define TPM_CC_Commit                       (TPM_CC)(0x0000018B)
#define TPM_CC_PolicyPassword               (TPM_CC)(0x0000018C)
#define TPM_CC_ZGen_2Phase                  (TPM_CC)(0x0000018D)
#define TPM_CC_EC_Ephemeral                 (TPM_CC)(0x0000018E)
#define TPM_CC_PolicyNvWritten              (TPM_CC)(0x0000018F)
#define TPM_CC_PolicyTemplate               (TPM_CC)(0x00000190)
#define TPM_CC_CreateLoaded                 (TPM_CC)(0x00000191)
#define TPM_CC_PolicyAuthorizeNV            (TPM_CC)(0x00000192)
#define TPM_CC_EncryptDecrypt2              (TPM_CC)(0x00000193)
#define TPM_CC_AC_GetCapability             (TPM_CC)(0x00000194)
#define TPM_CC_AC_Send                      (TPM_CC)(0x00000195)
#define TPM_CC_Policy_AC_SendSelect         (TPM_CC)(0x00000196)
#define TPM_CC_CertifyX509                  (TPM_CC)(0x00000197)
#define CC_VEND                             0x20000000
#define TPM_CC_Vendor_TCG_Test              (TPM_CC)(0x20000000)

// Additional values for benefit of code
#define TPM_CC_FIRST                        0x0000011F
#define TPM_CC_LAST                         0x00000197

   
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
    + (ADD_FILL || CC_CertifyX509)                          /* 0x00000197 */       \
    )

#define VENDOR_COMMAND_ARRAY_SIZE   (0 + CC_Vendor_TCG_Test)

#define COMMAND_COUNT       (LIBRARY_COMMAND_ARRAY_SIZE + VENDOR_COMMAND_ARRAY_SIZE)

#define HASH_COUNT          \
            (ALG_SHA1     + ALG_SHA256   + ALG_SHA384   + ALG_SHA3_256 +           \
             ALG_SHA3_384 + ALG_SHA3_512 + ALG_SHA512   + ALG_SM3_256)

#define MAX_HASH_BLOCK_SIZE \
            (MAX(ALG_SHA1     * SHA1_BLOCK_SIZE,                                   \
             MAX(ALG_SHA256   * SHA256_BLOCK_SIZE,                                 \
             MAX(ALG_SHA384   * SHA384_BLOCK_SIZE,                                 \
             MAX(ALG_SHA3_256 * SHA3_256_BLOCK_SIZE,                               \
             MAX(ALG_SHA3_384 * SHA3_384_BLOCK_SIZE,                               \
             MAX(ALG_SHA3_512 * SHA3_512_BLOCK_SIZE,                               \
             MAX(ALG_SHA512   * SHA512_BLOCK_SIZE,                                 \
             MAX(ALG_SM3_256  * SM3_256_BLOCK_SIZE,                                \
             0)))))))))

#define MAX_DIGEST_SIZE     \
            (MAX(ALG_SHA1     * SHA1_DIGEST_SIZE,                                  \
             MAX(ALG_SHA256   * SHA256_DIGEST_SIZE,                                \
             MAX(ALG_SHA384   * SHA384_DIGEST_SIZE,                                \
             MAX(ALG_SHA3_256 * SHA3_256_DIGEST_SIZE,                              \
             MAX(ALG_SHA3_384 * SHA3_384_DIGEST_SIZE,                              \
             MAX(ALG_SHA3_512 * SHA3_512_DIGEST_SIZE,                              \
             MAX(ALG_SHA512   * SHA512_DIGEST_SIZE,                                \
             MAX(ALG_SM3_256  * SM3_256_DIGEST_SIZE,                               \
             0)))))))))


#if MAX_DIGEST_SIZE == 0 || MAX_HASH_BLOCK_SIZE == 0
#error "Hash data not valid"
#endif

// Define the 2B structure that would hold any hash block
TPM2B_TYPE(MAX_HASH_BLOCK, MAX_HASH_BLOCK_SIZE);

// Following typedef is for some old code
typedef TPM2B_MAX_HASH_BLOCK    TPM2B_HASH_BLOCK;

/* Additional symmetric constants */
#define MAX_SYM_KEY_BITS        \
            (MAX(AES_MAX_KEY_SIZE_BITS,      MAX(CAMELLIA_MAX_KEY_SIZE_BITS,       \
             MAX(SM4_MAX_KEY_SIZE_BITS,      MAX(TDES_MAX_KEY_SIZE_BITS,           \
             0)))))

#define MAX_SYM_KEY_BYTES       ((MAX_SYM_KEY_BITS + 7) / 8)

#define MAX_SYM_BLOCK_SIZE      \
            (MAX(AES_MAX_BLOCK_SIZE,      MAX(CAMELLIA_MAX_BLOCK_SIZE,             \
             MAX(SM4_MAX_BLOCK_SIZE,      MAX(TDES_MAX_BLOCK_SIZE,                 \
             0)))))

#if MAX_SYM_KEY_BITS == 0 || MAX_SYM_BLOCK_SIZE == 0
#   error Bad size for MAX_SYM_KEY_BITS or MAX_SYM_BLOCK
#endif


#endif // _TPM_ALGORITHM_DEFINES_H_
