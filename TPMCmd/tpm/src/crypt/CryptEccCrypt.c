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
//** Includes and Defines
#include "Tpm.h"

#if CC_ECC_Encrypt || CC_ECC_Encrypt

//** Functions

//*** CryptEccSelectScheme()
// This function is used by TPM2_ECC_Decrypt and TPM2_ECC_Encrypt.  It sets scheme
// either the input scheme or the key scheme. If they key scheme is not TPM_ALG_NULL
// then the input scheme must be TPM_ALG_NULL or the same as the key scheme. If
// not, then the function returns FALSE.
//  Return Type: BOOL
//      TRUE        'scheme' is set
//      FALSE       'scheme' is not valid (it may have been changed).
BOOL
CryptEccSelectScheme(
    OBJECT              *key,           //IN: key containing default scheme
    TPMT_KDF_SCHEME     *scheme         // IN: a decrypt scheme
)
{
    TPMT_KDF_SCHEME    *keyScheme = &key->publicArea.parameters.eccDetail.kdf;

    // Get sign object pointer
    if(scheme->scheme == TPM_ALG_NULL)
        *scheme = *keyScheme;
    if(keyScheme->scheme == TPM_ALG_NULL)
        keyScheme = scheme;
    return (scheme->scheme != TPM_ALG_NULL &&
                (keyScheme->scheme == scheme->scheme
            && keyScheme->details.anyKdf.hashAlg == scheme->details.anyKdf.hashAlg));
}



//*** CryptEccEncrypt()
//This function performs ECC-based data obfuscation. The only scheme that is currently
// supported is MGF1 based. See Part 1, Annex D for details.
//  Return Type: TPM_RC
//      TPM_RC_CURVE            unsupported curve
//      TPM_RC_HASH             hash not allowed
//      TPM_RC_SCHEME           'scheme' is not supported
//      TPM_RC_NO_RESULT        internal error in big number processing
LIB_EXPORT TPM_RC
CryptEccEncrypt(
    OBJECT                  *key,           // IN: public key of recipient
    TPMT_KDF_SCHEME         *scheme,        // IN: scheme to use.
    TPM2B_MAX_BUFFER        *plainText,     // IN: the text to obfuscate
    TPMS_ECC_POINT          *c1,            // OUT: public ephemeral key
    TPM2B_MAX_BUFFER        *c2,            // OUT: obfuscated text
    TPM2B_DIGEST            *c3             // OUT: digest of ephemeral key
                                            //      and plainText
)
{
    CURVE_INITIALIZED(E, key->publicArea.parameters.eccDetail.curveID);
    POINT_INITIALIZED(PB, &key->publicArea.unique.ecc);
    POINT_VAR(Px, MAX_ECC_KEY_BITS);
    TPMS_ECC_POINT          p2;
    ECC_NUM(D);
    TPM2B_TYPE(2ECC, MAX_ECC_KEY_BYTES * 2);
    TPM2B_2ECC              z;
    int                     i;
    HASH_STATE              hashState;
    TPM_RC                  retVal = TPM_RC_SUCCESS;
    //
#if defined DEBUG_ECC_ENCRYPT && DEBUG_ECC_ENCRYPT == YES
    RND_DEBUG           dbg;
    // This value is one less than the value from the reference so that it
    // will become the correct value after having one added
    TPM2B_ECC_PARAMETER k = {24, {
        0x38, 0x4F, 0x30, 0x35, 0x30, 0x73, 0xAE, 0xEC,
        0xE7, 0xA1, 0x65, 0x43, 0x30, 0xA9, 0x62, 0x04,
        0xD3, 0x79, 0x82, 0xA3, 0xE1, 0x5B, 0x2C, 0xB4}};
    RND_DEBUG_Instantiate(&dbg, &k.b);
#   define RANDOM      (RAND_STATE *)&dbg

#else
#   define RANDOM      NULL
#endif
    if (E == NULL)
        ERROR_RETURN(TPM_RC_CURVE);
    if (TPM_ALG_KDF2 != scheme->scheme)
        ERROR_RETURN(TPM_RC_SCHEME);
    // generate an ephemeral key from a random k
    if (!BnEccGenerateKeyPair(D, Px, E, RANDOM)
        // C1 is the public part of the ephemeral key
        || !BnPointTo2B(c1, Px, E)
        // Compute P2
        || (BnPointMult(Px, PB, D, NULL, NULL, E) != TPM_RC_SUCCESS)
        || !BnPointTo2B(&p2, Px, E))
        ERROR_RETURN(TPM_RC_NO_RESULT);

    //Compute the C3 value hash(x2 || M || y2)
    if (0 == CryptHashStart(&hashState, scheme->details.mgf1.hashAlg))
        ERROR_RETURN(TPM_RC_HASH);
    CryptDigestUpdate2B(&hashState, &p2.x.b);
    CryptDigestUpdate2B(&hashState, &plainText->b);
    CryptDigestUpdate2B(&hashState, &p2.y.b);
    c3->t.size = CryptHashEnd(&hashState, sizeof(c3->t.buffer), c3->t.buffer);

    MemoryCopy2B(&z.b, &p2.x.b, sizeof(z.t.buffer));
    MemoryConcat2B(&z.b, &p2.y.b, sizeof(z.t.buffer));
    // Generate the mask value from MGF1 and put it in the return buffer
    c2->t.size = CryptMGF_KDF(plainText->t.size, c2->t.buffer,
                           scheme->details.mgf1.hashAlg, z.t.size, z.t.buffer, 1);
    // XOR the plainText into the generated mask to create the obfuscated data
    for (i = 0; i < plainText->t.size; i++)
        c2->t.buffer[i] ^= plainText->t.buffer[i];
Exit:
    CURVE_FREE(E);
    return retVal;
}

//*** CryptEccDecrypt()
// This function performs ECC decryption and integrity check of the input data.
//  Return Type: TPM_RC
//      TPM_RC_CURVE            unsupported curve
//      TPM_RC_HASH             hash not allowed
//      TPM_RC_SCHEME           'scheme' is not supported
//      TPM_RC_NO_RESULT        internal error in big number processing
//      TPM_RC_VALUE            C3 did not match hash of recovered data
LIB_EXPORT TPM_RC
CryptEccDecrypt(
    OBJECT                  *key,           // IN: key used for data recovery
    TPMT_KDF_SCHEME         *scheme,        // IN: scheme to use.
    TPM2B_MAX_BUFFER        *plainText,     // OUT: the recovered text
    TPMS_ECC_POINT          *c1,            // IN: public ephemeral key
    TPM2B_MAX_BUFFER        *c2,            // IN: obfuscated text
    TPM2B_DIGEST            *c3             // IN: digest of ephemeral key
                                            //      and plainText
)
{
    CURVE_INITIALIZED(E, key->publicArea.parameters.eccDetail.curveID);
    ECC_INITIALIZED(D, &key->sensitive.sensitive.ecc.b);
    POINT_INITIALIZED(C1, c1);
    TPMS_ECC_POINT          p2;
    TPM2B_TYPE(2ECC, MAX_ECC_KEY_BYTES * 2);
    TPM2B_DIGEST            check;
    TPM2B_2ECC              z;
    int                     i;
    HASH_STATE              hashState;
    TPM_RC                  retVal = TPM_RC_SUCCESS;
 //
    if (E == NULL)
        ERROR_RETURN(TPM_RC_CURVE);
    if (TPM_ALG_KDF2 != scheme->scheme)
        ERROR_RETURN(TPM_RC_SCHEME);
    // Generate the Z value
    BnPointMult(C1, C1, D, NULL, NULL, E);
    BnPointTo2B(&p2, C1, E);

    // Start the hash to check the algorithm
    if (0 == CryptHashStart(&hashState, scheme->details.mgf1.hashAlg))
        ERROR_RETURN(TPM_RC_HASH);
    CryptDigestUpdate2B(&hashState, &p2.x.b);

    MemoryCopy2B(&z.b, &p2.x.b, sizeof(z.t.buffer));
    MemoryConcat2B(&z.b, &p2.y.b, sizeof(z.t.buffer));

    // Generate the mask
    plainText->t.size = CryptMGF_KDF(c2->t.size, plainText->t.buffer,
                                  scheme->details.mgf1.hashAlg, z.t.size,
                                  z.t.buffer, 1);
    // XOR the obfuscated data into the generated mask to create the plainText data
    for (i = 0; i < plainText->t.size; i++)
        plainText->t.buffer[i] ^= c2->t.buffer[i];

    // Complete the hash and verify the data
    CryptDigestUpdate2B(&hashState, &plainText->b);
    CryptDigestUpdate2B(&hashState, &p2.y.b);
    check.t.size = CryptHashEnd(&hashState, sizeof(check.t.buffer), check.t.buffer);
    if (!MemoryEqual2B(&check.b, &c3->b))
        ERROR_RETURN(TPM_RC_VALUE);
Exit:
    CURVE_FREE(E);
    return retVal;
}


#endif  // CC_ECC_Encrypt || CC_ECC_Encrypt
