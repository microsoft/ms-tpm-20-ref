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

//** Introduction
//
// This file contains the implementation of the symmetric block cipher modes
// allowed for a TPM. These functions only use the single block encryption functions
// of the selected symmetric crypto library.

//** Includes, Defines, and Typedefs
#include "Tpm.h"

union tpmCryptKeySchedule_t {
#ifdef TPM_ALG_AES
    tpmKeyScheduleAES           AES;
#endif
#ifdef TPM_ALG_SM4
    tpmKeyScheduleSM4           SM4;
#endif
#ifdef TPM_ALG_CAMELLIA
    tpmKeyScheduleCAMELLIA      CAMELLIA;
#endif
 
#ifdef TPM_ALG_TDES
    tpmKeyScheduleTDES          TDES[3];
#endif
#if SYMMETRIC_ALIGNMENT == 8
    uint64_t            alignment;
#else
    uint32_t            alignment;
#endif
};


// Each block cipher within a library is expected to conform to the same calling 
// conventions with three parameters ('keySchedule', 'in', and 'out') in the same
// order. That means that all algorithms would use the same order of the same 
// parameters. The code is written assuming the ('keySchedule', 'in', and 'out') 
// order. However, if the library uses a different order, the order can be changed
// with a SWIZZLE macro that puts the parameters in the correct order.
// Note that all algorithms have to use the same order and number of parameters
// because the code to build the calling list is common for each call to encrypt 
// or decrypt with the algorithm chosen by setting a function pointer to select
// the algorithm that is used.

#   define ENCRYPT(keySchedule, in, out)                \
      encrypt(SWIZZLE(keySchedule, in, out))

#   define DECRYPT(keySchedule, in, out)                \
      decrypt(SWIZZLE(keySchedule, in, out))


// Note that the macros rely on 'encrypt' as local values in the
// functions that use these macros. Those parameters are set by the macro that 
// set the key schedule to be used for the call.


#define ENCRYPT_CASE(ALG)                                                   \
    case TPM_ALG_##ALG:                                                     \
        TpmCryptSetEncryptKey##ALG(key, keySizeInBits, &keySchedule.ALG);   \
        encrypt = (TpmCryptSetSymKeyCall_t)TpmCryptEncrypt##ALG;            \
        break;
#define DECRYPT_CASE(ALG)                                                   \
    case TPM_ALG_##ALG:                                                     \
        TpmCryptSetDecryptKey##ALG(key, keySizeInBits, &keySchedule.ALG);   \
        decrypt = (TpmCryptSetSymKeyCall_t)TpmCryptDecrypt##ALG;            \
        break;

#ifdef TPM_ALG_AES
#define ENCRYPT_CASE_AES    ENCRYPT_CASE(AES)
#define DECRYPT_CASE_AES    DECRYPT_CASE(AES)
#else
#define ENCRYPT_CASE_AES
#define DECRYPT_CASE_AES
#endif
#ifdef TPM_ALG_SM4
#define ENCRYPT_CASE_SM4    ENCRYPT_CASE(SM4)
#define DECRYPT_CASE_SM4    DECRYPT_CASE(SM4)
#else
#define ENCRYPT_CASE_SM4
#define DECRYPT_CASE_SM4
#endif
#ifdef TPM_ALG_CAMELLIA
#define ENCRYPT_CASE_CAMELLIA    ENCRYPT_CASE(CAMELLIA)
#define DECRYPT_CASE_CAMELLIA    DECRYPT_CASE(CAMELLIA)
#else
#define ENCRYPT_CASE_CAMELLIA
#define DECRYPT_CASE_CAMELLIA
#endif
#ifdef TPM_ALG_TDES
#define ENCRYPT_CASE_TDES    ENCRYPT_CASE(TDES)
#define DECRYPT_CASE_TDES    DECRYPT_CASE(TDES)
#else
#define ENCRYPT_CASE_TDES
#define DECRYPT_CASE_TDES
#endif

// For each algorithm the case will either be defined or null.
#define     SELECT(direction)                               \
    switch(algorithm)                                       \
    {                                                       \
        direction##_CASE_AES                                \
        direction##_CASE_SM4                                \
        direction##_CASE_CAMELLIA                           \
        direction##_CASE_TDES                               \
        default:                                            \
            return TPM_RC_FAILURE;                          \
    }

//** Obligatory Initialization Functions
//
//*** CryptSymInit()
// This function is called to do _TPM_Init processing
BOOL
CryptSymInit(
    void
    )
{
    return TRUE;
}

//*** CryptSymStartup()
// This function is called to do TPM2_Startup() processing
BOOL
CryptSymStartup(
    void
    )
{
    return TRUE;
}

//** Data Access Functions

//*** CryptGetSymmetricBlockSize()
// This function returns the block size of the algorithm.
// return type: INT16
//   <= 0     cipher not supported
//   > 0      the cipher block size in bytes
LIB_EXPORT INT16
CryptGetSymmetricBlockSize(
    TPM_ALG_ID      symmetricAlg,   // IN: the symmetric algorithm
    UINT16          keySizeInBits   // IN: the key size
    )
{
    switch(symmetricAlg)
    {
#ifdef TPM_ALG_AES
        case TPM_ALG_AES:
            switch(keySizeInBits)
            {
                case 128:
                    return AES_128_BLOCK_SIZE_BYTES;
                case 192:
                    return AES_192_BLOCK_SIZE_BYTES;
                case 256:
                    return AES_256_BLOCK_SIZE_BYTES;
                default:
                    break;
            }
            break;
#endif
#ifdef TPM_ALG_SM4
        case TPM_ALG_SM4:
            switch(keySizeInBits)
            {
                case 128:
                    return SM4_128_BLOCK_SIZE_BYTES;
                default:
                    break;
            }
#endif
#ifdef TPM_ALG_CAMELLIA
        case TPM_ALG_CAMELLIA:
            switch(keySizeInBits)
            {
                case 128:
                    return CAMELLIA_128_BLOCK_SIZE_BYTES;
                case 192:
                    return CAMELLIA_192_BLOCK_SIZE_BYTES;
                case 256:
                    return CAMELLIA_256_BLOCK_SIZE_BYTES;
                default:
                    break;
            }
#endif
#ifdef TPM_ALG_TDES
        case TPM_ALG_TDES:
            switch(keySizeInBits)
            {
                case 128:
                    return TDES_128_BLOCK_SIZE_BYTES;
                case 192:
                    return TDES_192_BLOCK_SIZE_BYTES;
                default:
                    break;
            }
#endif
        default:
            break;
    }
    return 0;
}

//** Symmetric Encryption
// This function performs symmetric encryption based on the mode.
// return type: TPM_RC
//      TPM_RC_SUCCESS      if success
//      TPM_RC_SIZE         'dSize' is not a multiple of the block size for an
//                          algorithm that requires it
//      TPM_RC_FAILURE      Fatal error
LIB_EXPORT TPM_RC
CryptSymmetricEncrypt(
    BYTE                *dOut,          // OUT:
    TPM_ALG_ID           algorithm,     // IN: the symmetric algorithm
    UINT16               keySizeInBits, // IN: key size in bits
    const BYTE          *key,           // IN: key buffer. The size of this buffer
                                        //     in bytes is (keySizeInBits + 7) / 8
    TPM2B_IV            *ivInOut,       // IN/OUT: IV for decryption.
    TPM_ALG_ID           mode,          // IN: Mode to use
    INT32                dSize,         // IN: data size (may need to be a
                                        //     multiple of the blockSize)
    const BYTE          *dIn            // IN: data buffer
    )
{
    BYTE                *pIv;
    int                  i;
    BYTE                 tmp[MAX_SYM_BLOCK_SIZE];
    BYTE                *pT;
    tpmCryptKeySchedule_t        keySchedule;
    INT16                blockSize;
    TpmCryptSetSymKeyCall_t        encrypt;
    BYTE                *iv;
    BYTE                 defaultIv[MAX_SYM_BLOCK_SIZE] = {0};
//
    pAssert(dOut != NULL && key != NULL && dIn != NULL);
    if(dSize == 0)
        return TPM_RC_SUCCESS;

    TEST(algorithm);
    blockSize = CryptGetSymmetricBlockSize(algorithm, keySizeInBits);
    if(blockSize == 0)
        return TPM_RC_FAILURE;
    // If the iv is provided, then it is expected to be block sized. In some cases,
    // the caller is providing an array of 0's that is equal to [MAX_SYM_BLOCK_SIZE]
    // with no knowledge of the actual block size. This function will set it.
    if((ivInOut != NULL) && (mode != ALG_ECB_VALUE))
    {
        ivInOut->t.size = blockSize;
        iv = ivInOut->t.buffer;
    }
    else
        iv = defaultIv;
    pIv = iv;

    // Create encrypt key schedule and set the encryption function pointer.

    SELECT(ENCRYPT);

    switch(mode)
    {
#ifdef TPM_ALG_CTR
        case TPM_ALG_CTR:
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the current value of the IV(counter)
                ENCRYPT(&keySchedule, iv, tmp);

                //increment the counter (counter is big-endian so start at end)
                for(i = blockSize - 1; i >= 0; i--)
                    if((iv[i] += 1) != 0)
                        break;

                // XOR the encrypted counter value with input and put into output
                pT = tmp;
                for(i = (dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    *dOut++ = *dIn++ ^ *pT++;
            }
            break;
#endif
#ifdef TPM_ALG_OFB
        case TPM_ALG_OFB:
            // This is written so that dIn and dOut may be the same
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the current value of the "IV"
                ENCRYPT(&keySchedule, iv, iv);

                // XOR the encrypted IV into dIn to create the cipher text (dOut)
                pIv = iv;
                for(i = (dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    *dOut++ = (*pIv++ ^ *dIn++);
            }
            break;
#endif
#ifdef TPM_ALG_CBC
        case TPM_ALG_CBC:
            // For CBC the data size must be an even multiple of the
            // cipher block size
            if((dSize % blockSize) != 0)
                return TPM_RC_SIZE;
            // XOR the data block into the IV, encrypt the IV into the IV
            // and then copy the IV to the output
            for(; dSize > 0; dSize -= blockSize)
            {
                pIv = iv;
                for(i = blockSize; i > 0; i--)
                    *pIv++ ^= *dIn++;
                ENCRYPT(&keySchedule, iv, iv);
                pIv = iv;
                for(i = blockSize; i > 0; i--)
                    *dOut++ = *pIv++;
            }
            break;
#endif
        // CFB is not optional
        case TPM_ALG_CFB:
            // Encrypt the IV into the IV, XOR in the data, and copy to output
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the current value of the IV
                ENCRYPT(&keySchedule, iv, iv);
                pIv = iv;
                for(i = (int)(dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    // XOR the data into the IV to create the cipher text
                    // and put into the output
                    *dOut++ = *pIv++ ^= *dIn++;
            }
            // If the inner loop (i loop) was smaller than blockSize, then dSize
            // would have been smaller than blockSize and it is now negative. If
            // it is negative, then it indicates how many bytes are needed to pad
            // out the IV for the next round.
            for(; dSize < 0; dSize++)
                *pIv++ = 0;
            break;
#ifdef TPM_ALG_ECB
        case TPM_ALG_ECB:
            // For ECB the data size must be an even multiple of the
            // cipher block size
            if((dSize % blockSize) != 0)
                return TPM_RC_SIZE;
            // Encrypt the input block to the output block
            for(; dSize > 0; dSize -= blockSize)
            {
                ENCRYPT(&keySchedule, dIn, dOut);
                dIn = &dIn[blockSize];
                dOut = &dOut[blockSize];
            }
            break;
#endif
        default:
            return TPM_RC_FAILURE;
    }
    return TPM_RC_SUCCESS;
}

//*** CryptSymmetricDecrypt()
// This function performs symmetric decryption based on the mode.
// return type: TPM_RC
//      TPM_RC_FAILURE      A fatal error
//      TPM_RC_SUCCESS      if success
//      TPM_RCS_SIZE        'dSize' is not a multiple of the block size for an
//                          algorithm that requires it
LIB_EXPORT TPM_RC
CryptSymmetricDecrypt(
    BYTE                *dOut,          // OUT: decrypted data
    TPM_ALG_ID           algorithm,     // IN: the symmetric algorithm
    UINT16               keySizeInBits, // IN: key size in bits
    const BYTE          *key,           // IN: key buffer. The size of this buffer
                                        //     in bytes is (keySizeInBits + 7) / 8
    TPM2B_IV            *ivInOut,       // IN/OUT: IV for decryption.
    TPM_ALG_ID           mode,          // IN: Mode to use
    INT32                dSize,         // IN: data size (may need to be a
                                        //     multiple of the blockSize)
    const BYTE          *dIn            // IN: data buffer
    )
{
    BYTE                *pIv;
    int                  i;
    BYTE                 tmp[MAX_SYM_BLOCK_SIZE];
    BYTE                *pT;
    tpmCryptKeySchedule_t        keySchedule;
    INT16                blockSize;
    BYTE                *iv;
    TpmCryptSetSymKeyCall_t        encrypt;
    TpmCryptSetSymKeyCall_t        decrypt;
    BYTE                 defaultIv[MAX_SYM_BLOCK_SIZE] = {0};

    // These are used but the compiler can't tell because they are initialized
    // in case statements and it can't tell if they are always initialized
    // when needed, so... Comment these out if the compiler can tell or doesn't
    // care that these are initialized before use.
    encrypt = NULL;
    decrypt = NULL;

    pAssert(dOut != NULL && key != NULL && dIn != NULL);
    if(dSize == 0)
        return TPM_RC_SUCCESS;

    TEST(algorithm);
    blockSize = CryptGetSymmetricBlockSize(algorithm, keySizeInBits);
    // If the iv is provided, then it is expected to be block sized. In some cases,
    // the caller is providing an array of 0's that is equal to [MAX_SYM_BLOCK_SIZE]
    // with no knowledge of the actual block size. This function will set it.
    if((ivInOut != NULL) && (mode != ALG_ECB_VALUE))
    {
        ivInOut->t.size = blockSize;
        iv = ivInOut->t.buffer;
    }
    else
        iv = defaultIv;

    pIv = iv;
    // Use the mode to select the key schedule to create. Encrypt always uses the
    // encryption schedule. Depending on the mode, decryption might use either
    // the decryption or encryption schedule.
    switch(mode)
    {
#if defined TPM_ALG_CBC || defined TPM_ALG_ECB
        case ALG_CBC_VALUE: // decrypt = decrypt
        case ALG_ECB_VALUE:
            // For ECB and CBC, the data size must be an even multiple of the
            // cipher block size
            if((dSize % blockSize) != 0)
                return TPM_RC_SIZE;
            SELECT(DECRYPT);
            break;
#endif
        default:
            // For the remaining stream ciphers, use encryption to decrypt
            SELECT(ENCRYPT);
            break;
    }
    // Now do the mode-dependent decryption
    switch(mode)
    {
#ifdef TPM_ALG_CBC
        case TPM_ALG_CBC:
            // Copy the input data to a temp buffer, decrypt the buffer into the
            // output, XOR in the IV, and copy the temp buffer to the IV and repeat.
            for(; dSize > 0; dSize -= blockSize)
            {
                pT = tmp;
                for(i = blockSize; i > 0; i--)
                    *pT++ = *dIn++;
                DECRYPT(&keySchedule, tmp, dOut);
                pIv = iv;
                pT = tmp;
                for(i = blockSize; i > 0; i--)
                {
                    *dOut++ ^= *pIv;
                    *pIv++ = *pT++;
                }
            }
            break;
#endif
        case TPM_ALG_CFB:
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the IV into the temp buffer
                ENCRYPT(&keySchedule, iv, tmp);
                pT = tmp;
                pIv = iv;
                for(i = (dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    // Copy the current cipher text to IV, XOR
                    // with the temp buffer and put into the output
                    *dOut++ = *pT++ ^ (*pIv++ = *dIn++);
            }
            // If the inner loop (i loop) was smaller than blockSize, then dSize
            // would have been smaller than blockSize and it is now negative
            // If it is negative, then it indicates how may fill bytes
            // are needed to pad out the IV for the next round.
            for(; dSize < 0; dSize++)
                *pIv++ = 0;

            break;
#ifdef TPM_ALG_CTR
        case TPM_ALG_CTR:
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the current value of the IV(counter)
                ENCRYPT(&keySchedule, iv, tmp);

                //increment the counter (counter is big-endian so start at end)
                for(i = blockSize - 1; i >= 0; i--)
                    if((iv[i] += 1) != 0)
                        break;
                // XOR the encrypted counter value with input and put into output
                pT = tmp;
                for(i = (dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    *dOut++ = *dIn++ ^ *pT++;
            }
            break;
#endif
#ifdef TPM_ALG_ECB
        case TPM_ALG_ECB:
            for(; dSize > 0; dSize -= blockSize)
            {
                DECRYPT(&keySchedule, dIn, dOut);
                dIn = &dIn[blockSize];
                dOut = &dOut[blockSize];
            }
            break;
#endif
#ifdef TPM_ALG_OFB
        case TPM_ALG_OFB:
            // This is written so that dIn and dOut may be the same
            for(; dSize > 0; dSize -= blockSize)
            {
                // Encrypt the current value of the "IV"
                ENCRYPT(&keySchedule, iv, iv);

                // XOR the encrypted IV into dIn to create the cipher text (dOut)
                pIv = iv;
                for(i = (dSize < blockSize) ? dSize : blockSize; i > 0; i--)
                    *dOut++ = (*pIv++ ^ *dIn++);
            }
            break;
#endif
        default:
            return TPM_RC_FAILURE;
    }
    return TPM_RC_SUCCESS;
}

//*** CryptSymKeyValidate()
// Validate that a provided symmetric key meets the requirements of the TPM
// return type: TPM_RC
//  TPM_RC_KEY_SIZE         Key size specifiers do not match
//  TPM_RC_KEY              Key is not allowed
TPM_RC
CryptSymKeyValidate(
    TPMT_SYM_DEF_OBJECT *symDef,
    TPM2B_SYM_KEY       *key
    )
{
    if(key->t.size != BITS_TO_BYTES(symDef->keyBits.sym))
        return TPM_RCS_KEY_SIZE;
#ifdef TPM_ALG_TDES
    if(symDef->algorithm == TPM_ALG_TDES && !CryptDesValidateKey(key))
        return TPM_RCS_KEY;
#endif // TPM_ALG_TDES
    return TPM_RC_SUCCESS;
}


