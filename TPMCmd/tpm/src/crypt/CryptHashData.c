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
 *  Created by TpmStructures; Version 3.0 June 16, 2017
 *  Date: Jun 16, 2018  Time: 08:35:57PM
 */

#include "Tpm.h"

const HASH_INFO   g_hashData[HASH_COUNT + 1] = {
#if  ALG_SHA1
    {TPM_ALG_SHA1,    SHA1_DIGEST_SIZE,   SHA1_BLOCK_SIZE,   
    SHA1_DER_SIZE,   {SHA1_DER}},
#endif
#if  ALG_SHA256
    {TPM_ALG_SHA256,    SHA256_DIGEST_SIZE,   SHA256_BLOCK_SIZE,   
    SHA256_DER_SIZE,   {SHA256_DER}},
#endif
#if  ALG_SHA384
    {TPM_ALG_SHA384,    SHA384_DIGEST_SIZE,   SHA384_BLOCK_SIZE,   
    SHA384_DER_SIZE,   {SHA384_DER}},
#endif
#if  ALG_SHA512
    {TPM_ALG_SHA512,    SHA512_DIGEST_SIZE,   SHA512_BLOCK_SIZE,   
    SHA512_DER_SIZE,   {SHA512_DER}},
#endif
#if  ALG_SM3_256
    {TPM_ALG_SM3_256,    SM3_256_DIGEST_SIZE,   SM3_256_BLOCK_SIZE,   
    SM3_256_DER_SIZE,   {SM3_256_DER}},
#endif
        {TPM_ALG_NULL,0,0,0,{0}}
    };

