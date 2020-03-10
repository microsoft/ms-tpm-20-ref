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
 *  Created by TpmPrototypes; Version 3.0 July 18, 2017
 *  Date: Feb 28, 2020  Time: 03:04:48PM
 */

#ifndef    _CRYPT_ECC_CRYPT_FP_H_
#define    _CRYPT_ECC_CRYPT_FP_H_

#if CC_ECC_Encrypt || CC_ECC_Encrypt

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
);

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
);

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
);
#endif  // CC_ECC_Encrypt || CC_ECC_Encrypt

#endif  // _CRYPT_ECC_CRYPT_FP_H_
