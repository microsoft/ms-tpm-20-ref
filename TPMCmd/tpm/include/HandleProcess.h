/*(Prototype)*/
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
/*(Auto)
    Created by TpmDispatch.pl version 03.0 October 4, 2015
    This file created on May  8, 2017, 10:36:21PM 
*/
#if defined CC_Startup && CC_Startup == YES
        case TPM_CC_Startup:
            *handleCount = 0;
            break;
#endif     // CC_Startup
#if defined CC_Shutdown && CC_Shutdown == YES
        case TPM_CC_Shutdown:
            *handleCount = 0;
            break;
#endif     // CC_Shutdown
#if defined CC_SelfTest && CC_SelfTest == YES
        case TPM_CC_SelfTest:
            *handleCount = 0;
            break;
#endif     // CC_SelfTest
#if defined CC_IncrementalSelfTest && CC_IncrementalSelfTest == YES
        case TPM_CC_IncrementalSelfTest:
            *handleCount = 0;
            break;
#endif     // CC_IncrementalSelfTest
#if defined CC_GetTestResult && CC_GetTestResult == YES
        case TPM_CC_GetTestResult:
            *handleCount = 0;
            break;
#endif     // CC_GetTestResult
#if defined CC_StartAuthSession && CC_StartAuthSession == YES
        case TPM_CC_StartAuthSession:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_ENTITY_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_StartAuthSession
#if defined CC_PolicyRestart && CC_PolicyRestart == YES
        case TPM_CC_PolicyRestart:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyRestart
#if defined CC_Create && CC_Create == YES
        case TPM_CC_Create:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Create
#if defined CC_Load && CC_Load == YES
        case TPM_CC_Load:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Load
#if defined CC_LoadExternal && CC_LoadExternal == YES
        case TPM_CC_LoadExternal:
            *handleCount = 0;
            break;
#endif     // CC_LoadExternal
#if defined CC_ReadPublic && CC_ReadPublic == YES
        case TPM_CC_ReadPublic:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ReadPublic
#if defined CC_ActivateCredential && CC_ActivateCredential == YES
        case TPM_CC_ActivateCredential:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_ActivateCredential
#if defined CC_MakeCredential && CC_MakeCredential == YES
        case TPM_CC_MakeCredential:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_MakeCredential
#if defined CC_Unseal && CC_Unseal == YES
        case TPM_CC_Unseal:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Unseal
#if defined CC_ObjectChangeAuth && CC_ObjectChangeAuth == YES
        case TPM_CC_ObjectChangeAuth:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_ObjectChangeAuth
#if defined CC_CreateLoaded && CC_CreateLoaded == YES
        case TPM_CC_CreateLoaded:
            *handleCount = 1;
            result = TPMI_DH_PARENT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_CreateLoaded
#if defined CC_Duplicate && CC_Duplicate == YES
        case TPM_CC_Duplicate:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_Duplicate
#if defined CC_Rewrap && CC_Rewrap == YES
        case TPM_CC_Rewrap:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_Rewrap
#if defined CC_Import && CC_Import == YES
        case TPM_CC_Import:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Import
#if defined CC_RSA_Encrypt && CC_RSA_Encrypt == YES
        case TPM_CC_RSA_Encrypt:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_RSA_Encrypt
#if defined CC_RSA_Decrypt && CC_RSA_Decrypt == YES
        case TPM_CC_RSA_Decrypt:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_RSA_Decrypt
#if defined CC_ECDH_KeyGen && CC_ECDH_KeyGen == YES
        case TPM_CC_ECDH_KeyGen:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ECDH_KeyGen
#if defined CC_ECDH_ZGen && CC_ECDH_ZGen == YES
        case TPM_CC_ECDH_ZGen:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ECDH_ZGen
#if defined CC_ECC_Parameters && CC_ECC_Parameters == YES
        case TPM_CC_ECC_Parameters:
            *handleCount = 0;
            break;
#endif     // CC_ECC_Parameters
#if defined CC_ZGen_2Phase && CC_ZGen_2Phase == YES
        case TPM_CC_ZGen_2Phase:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ZGen_2Phase
#if defined CC_EncryptDecrypt && CC_EncryptDecrypt == YES
        case TPM_CC_EncryptDecrypt:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_EncryptDecrypt
#if defined CC_EncryptDecrypt2 && CC_EncryptDecrypt2 == YES
        case TPM_CC_EncryptDecrypt2:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_EncryptDecrypt2
#if defined CC_Hash && CC_Hash == YES
        case TPM_CC_Hash:
            *handleCount = 0;
            break;
#endif     // CC_Hash
#if defined CC_HMAC && CC_HMAC == YES
        case TPM_CC_HMAC:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_HMAC
#if defined CC_MAC && CC_MAC == YES
        case TPM_CC_MAC:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_MAC
#if defined CC_GetRandom && CC_GetRandom == YES
        case TPM_CC_GetRandom:
            *handleCount = 0;
            break;
#endif     // CC_GetRandom
#if defined CC_StirRandom && CC_StirRandom == YES
        case TPM_CC_StirRandom:
            *handleCount = 0;
            break;
#endif     // CC_StirRandom
#if defined CC_HMAC_Start && CC_HMAC_Start == YES
        case TPM_CC_HMAC_Start:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_HMAC_Start
#if defined CC_MAC_Start && CC_MAC_Start == YES
        case TPM_CC_MAC_Start:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_MAC_Start
#if defined CC_HashSequenceStart && CC_HashSequenceStart == YES
        case TPM_CC_HashSequenceStart:
            *handleCount = 0;
            break;
#endif     // CC_HashSequenceStart
#if defined CC_SequenceUpdate && CC_SequenceUpdate == YES
        case TPM_CC_SequenceUpdate:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_SequenceUpdate
#if defined CC_SequenceComplete && CC_SequenceComplete == YES
        case TPM_CC_SequenceComplete:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_SequenceComplete
#if defined CC_EventSequenceComplete && CC_EventSequenceComplete == YES
        case TPM_CC_EventSequenceComplete:
            *handleCount = 2;
            result = TPMI_DH_PCR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_EventSequenceComplete
#if defined CC_Certify && CC_Certify == YES
        case TPM_CC_Certify:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_Certify
#if defined CC_CertifyCreation && CC_CertifyCreation == YES
        case TPM_CC_CertifyCreation:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_CertifyCreation
#if defined CC_Quote && CC_Quote == YES
        case TPM_CC_Quote:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Quote
#if defined CC_GetSessionAuditDigest && CC_GetSessionAuditDigest == YES
        case TPM_CC_GetSessionAuditDigest:
            *handleCount = 3;
            result = TPMI_RH_ENDORSEMENT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            result = TPMI_SH_HMAC_Unmarshal(&handles[2],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_3;
            break;
#endif     // CC_GetSessionAuditDigest
#if defined CC_GetCommandAuditDigest && CC_GetCommandAuditDigest == YES
        case TPM_CC_GetCommandAuditDigest:
            *handleCount = 2;
            result = TPMI_RH_ENDORSEMENT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_GetCommandAuditDigest
#if defined CC_GetTime && CC_GetTime == YES
        case TPM_CC_GetTime:
            *handleCount = 2;
            result = TPMI_RH_ENDORSEMENT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_GetTime
#if defined CC_Commit && CC_Commit == YES
        case TPM_CC_Commit:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Commit
#if defined CC_EC_Ephemeral && CC_EC_Ephemeral == YES
        case TPM_CC_EC_Ephemeral:
            *handleCount = 0;
            break;
#endif     // CC_EC_Ephemeral
#if defined CC_VerifySignature && CC_VerifySignature == YES
        case TPM_CC_VerifySignature:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_VerifySignature
#if defined CC_Sign && CC_Sign == YES
        case TPM_CC_Sign:
            *handleCount = 1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Sign
#if defined CC_SetCommandCodeAuditStatus && CC_SetCommandCodeAuditStatus == YES
        case TPM_CC_SetCommandCodeAuditStatus:
            *handleCount = 1;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_SetCommandCodeAuditStatus
#if defined CC_PCR_Extend && CC_PCR_Extend == YES
        case TPM_CC_PCR_Extend:
            *handleCount = 1;
            result = TPMI_DH_PCR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_Extend
#if defined CC_PCR_Event && CC_PCR_Event == YES
        case TPM_CC_PCR_Event:
            *handleCount = 1;
            result = TPMI_DH_PCR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_Event
#if defined CC_PCR_Read && CC_PCR_Read == YES
        case TPM_CC_PCR_Read:
            *handleCount = 0;
            break;
#endif     // CC_PCR_Read
#if defined CC_PCR_Allocate && CC_PCR_Allocate == YES
        case TPM_CC_PCR_Allocate:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_Allocate
#if defined CC_PCR_SetAuthPolicy && CC_PCR_SetAuthPolicy == YES
        case TPM_CC_PCR_SetAuthPolicy:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_SetAuthPolicy
#if defined CC_PCR_SetAuthValue && CC_PCR_SetAuthValue == YES
        case TPM_CC_PCR_SetAuthValue:
            *handleCount = 1;
            result = TPMI_DH_PCR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_SetAuthValue
#if defined CC_PCR_Reset && CC_PCR_Reset == YES
        case TPM_CC_PCR_Reset:
            *handleCount = 1;
            result = TPMI_DH_PCR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PCR_Reset
#if defined CC_PolicySigned && CC_PolicySigned == YES
        case TPM_CC_PolicySigned:
            *handleCount = 2;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_PolicySigned
#if defined CC_PolicySecret && CC_PolicySecret == YES
        case TPM_CC_PolicySecret:
            *handleCount = 2;
            result = TPMI_DH_ENTITY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_PolicySecret
#if defined CC_PolicyTicket && CC_PolicyTicket == YES
        case TPM_CC_PolicyTicket:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyTicket
#if defined CC_PolicyOR && CC_PolicyOR == YES
        case TPM_CC_PolicyOR:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyOR
#if defined CC_PolicyPCR && CC_PolicyPCR == YES
        case TPM_CC_PolicyPCR:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyPCR
#if defined CC_PolicyLocality && CC_PolicyLocality == YES
        case TPM_CC_PolicyLocality:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyLocality
#if defined CC_PolicyNV && CC_PolicyNV == YES
        case TPM_CC_PolicyNV:
            *handleCount = 3;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            result = TPMI_SH_POLICY_Unmarshal(&handles[2],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_3;
            break;
#endif     // CC_PolicyNV
#if defined CC_PolicyCounterTimer && CC_PolicyCounterTimer == YES
        case TPM_CC_PolicyCounterTimer:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyCounterTimer
#if defined CC_PolicyCommandCode && CC_PolicyCommandCode == YES
        case TPM_CC_PolicyCommandCode:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyCommandCode
#if defined CC_PolicyPhysicalPresence && CC_PolicyPhysicalPresence == YES
        case TPM_CC_PolicyPhysicalPresence:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyPhysicalPresence
#if defined CC_PolicyCpHash && CC_PolicyCpHash == YES
        case TPM_CC_PolicyCpHash:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyCpHash
#if defined CC_PolicyNameHash && CC_PolicyNameHash == YES
        case TPM_CC_PolicyNameHash:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyNameHash
#if defined CC_PolicyDuplicationSelect && CC_PolicyDuplicationSelect == YES
        case TPM_CC_PolicyDuplicationSelect:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyDuplicationSelect
#if defined CC_PolicyAuthorize && CC_PolicyAuthorize == YES
        case TPM_CC_PolicyAuthorize:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyAuthorize
#if defined CC_PolicyAuthValue && CC_PolicyAuthValue == YES
        case TPM_CC_PolicyAuthValue:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyAuthValue
#if defined CC_PolicyPassword && CC_PolicyPassword == YES
        case TPM_CC_PolicyPassword:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyPassword
#if defined CC_PolicyGetDigest && CC_PolicyGetDigest == YES
        case TPM_CC_PolicyGetDigest:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyGetDigest
#if defined CC_PolicyNvWritten && CC_PolicyNvWritten == YES
        case TPM_CC_PolicyNvWritten:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyNvWritten
#if defined CC_PolicyTemplate && CC_PolicyTemplate == YES
        case TPM_CC_PolicyTemplate:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PolicyTemplate
#if defined CC_PolicyAuthorizeNV && CC_PolicyAuthorizeNV == YES
        case TPM_CC_PolicyAuthorizeNV:
            *handleCount = 3;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            result = TPMI_SH_POLICY_Unmarshal(&handles[2],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_3;
            break;
#endif     // CC_PolicyAuthorizeNV
#if defined CC_CreatePrimary && CC_CreatePrimary == YES
        case TPM_CC_CreatePrimary:
            *handleCount = 1;
            result = TPMI_RH_HIERARCHY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_CreatePrimary
#if defined CC_HierarchyControl && CC_HierarchyControl == YES
        case TPM_CC_HierarchyControl:
            *handleCount = 1;
            result = TPMI_RH_HIERARCHY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_HierarchyControl
#if defined CC_SetPrimaryPolicy && CC_SetPrimaryPolicy == YES
        case TPM_CC_SetPrimaryPolicy:
            *handleCount = 1;
            result = TPMI_RH_HIERARCHY_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_SetPrimaryPolicy
#if defined CC_ChangePPS && CC_ChangePPS == YES
        case TPM_CC_ChangePPS:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ChangePPS
#if defined CC_ChangeEPS && CC_ChangeEPS == YES
        case TPM_CC_ChangeEPS:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ChangeEPS
#if defined CC_Clear && CC_Clear == YES
        case TPM_CC_Clear:
            *handleCount = 1;
            result = TPMI_RH_CLEAR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Clear
#if defined CC_ClearControl && CC_ClearControl == YES
        case TPM_CC_ClearControl:
            *handleCount = 1;
            result = TPMI_RH_CLEAR_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ClearControl
#if defined CC_HierarchyChangeAuth && CC_HierarchyChangeAuth == YES
        case TPM_CC_HierarchyChangeAuth:
            *handleCount = 1;
            result = TPMI_RH_HIERARCHY_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_HierarchyChangeAuth
#if defined CC_DictionaryAttackLockReset && CC_DictionaryAttackLockReset == YES
        case TPM_CC_DictionaryAttackLockReset:
            *handleCount = 1;
            result = TPMI_RH_LOCKOUT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_DictionaryAttackLockReset
#if defined CC_DictionaryAttackParameters && CC_DictionaryAttackParameters == YES
        case TPM_CC_DictionaryAttackParameters:
            *handleCount = 1;
            result = TPMI_RH_LOCKOUT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_DictionaryAttackParameters
#if defined CC_PP_Commands && CC_PP_Commands == YES
        case TPM_CC_PP_Commands:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_PP_Commands
#if defined CC_SetAlgorithmSet && CC_SetAlgorithmSet == YES
        case TPM_CC_SetAlgorithmSet:
            *handleCount = 1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_SetAlgorithmSet
#if defined CC_FieldUpgradeStart && CC_FieldUpgradeStart == YES
        case TPM_CC_FieldUpgradeStart:
            *handleCount = 2;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_FieldUpgradeStart
#if defined CC_FieldUpgradeData && CC_FieldUpgradeData == YES
        case TPM_CC_FieldUpgradeData:
            *handleCount = 0;
            break;
#endif     // CC_FieldUpgradeData
#if defined CC_FirmwareRead && CC_FirmwareRead == YES
        case TPM_CC_FirmwareRead:
            *handleCount = 0;
            break;
#endif     // CC_FirmwareRead
#if defined CC_ContextSave && CC_ContextSave == YES
        case TPM_CC_ContextSave:
            *handleCount = 1;
            result = TPMI_DH_CONTEXT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ContextSave
#if defined CC_ContextLoad && CC_ContextLoad == YES
        case TPM_CC_ContextLoad:
            *handleCount = 0;
            break;
#endif     // CC_ContextLoad
#if defined CC_FlushContext && CC_FlushContext == YES
        case TPM_CC_FlushContext:
            *handleCount = 0;
            break;
#endif     // CC_FlushContext
#if defined CC_EvictControl && CC_EvictControl == YES
        case TPM_CC_EvictControl:
            *handleCount = 2;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_EvictControl
#if defined CC_ReadClock && CC_ReadClock == YES
        case TPM_CC_ReadClock:
            *handleCount = 0;
            break;
#endif     // CC_ReadClock
#if defined CC_ClockSet && CC_ClockSet == YES
        case TPM_CC_ClockSet:
            *handleCount = 1;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ClockSet
#if defined CC_ClockRateAdjust && CC_ClockRateAdjust == YES
        case TPM_CC_ClockRateAdjust:
            *handleCount = 1;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_ClockRateAdjust
#if defined CC_GetCapability && CC_GetCapability == YES
        case TPM_CC_GetCapability:
            *handleCount = 0;
            break;
#endif     // CC_GetCapability
#if defined CC_TestParms && CC_TestParms == YES
        case TPM_CC_TestParms:
            *handleCount = 0;
            break;
#endif     // CC_TestParms
#if defined CC_NV_DefineSpace && CC_NV_DefineSpace == YES
        case TPM_CC_NV_DefineSpace:
            *handleCount = 1;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_NV_DefineSpace
#if defined CC_NV_UndefineSpace && CC_NV_UndefineSpace == YES
        case TPM_CC_NV_UndefineSpace:
            *handleCount = 2;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_UndefineSpace
#if defined CC_NV_UndefineSpaceSpecial && CC_NV_UndefineSpaceSpecial == YES
        case TPM_CC_NV_UndefineSpaceSpecial:
            *handleCount = 2;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_PLATFORM_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_UndefineSpaceSpecial
#if defined CC_NV_ReadPublic && CC_NV_ReadPublic == YES
        case TPM_CC_NV_ReadPublic:
            *handleCount = 1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_NV_ReadPublic
#if defined CC_NV_Write && CC_NV_Write == YES
        case TPM_CC_NV_Write:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_Write
#if defined CC_NV_Increment && CC_NV_Increment == YES
        case TPM_CC_NV_Increment:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_Increment
#if defined CC_NV_Extend && CC_NV_Extend == YES
        case TPM_CC_NV_Extend:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_Extend
#if defined CC_NV_SetBits && CC_NV_SetBits == YES
        case TPM_CC_NV_SetBits:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_SetBits
#if defined CC_NV_WriteLock && CC_NV_WriteLock == YES
        case TPM_CC_NV_WriteLock:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_WriteLock
#if defined CC_NV_GlobalWriteLock && CC_NV_GlobalWriteLock == YES
        case TPM_CC_NV_GlobalWriteLock:
            *handleCount = 1;
            result = TPMI_RH_PROVISION_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_NV_GlobalWriteLock
#if defined CC_NV_Read && CC_NV_Read == YES
        case TPM_CC_NV_Read:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_Read
#if defined CC_NV_ReadLock && CC_NV_ReadLock == YES
        case TPM_CC_NV_ReadLock:
            *handleCount = 2;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            break;
#endif     // CC_NV_ReadLock
#if defined CC_NV_ChangeAuth && CC_NV_ChangeAuth == YES
        case TPM_CC_NV_ChangeAuth:
            *handleCount = 1;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_NV_ChangeAuth
#if defined CC_NV_Certify && CC_NV_Certify == YES
        case TPM_CC_NV_Certify:
            *handleCount = 3;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            result = TPMI_RH_NV_INDEX_Unmarshal(&handles[2],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_3;
            break;
#endif     // CC_NV_Certify
#if defined CC_AC_GetCapability && CC_AC_GetCapability == YES
        case TPM_CC_AC_GetCapability:
            *handleCount = 1;
            result = TPMI_RH_AC_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_AC_GetCapability
#if defined CC_AC_Send && CC_AC_Send == YES
        case TPM_CC_AC_Send:
            *handleCount = 3;
            result = TPMI_DH_OBJECT_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            result = TPMI_RH_NV_AUTH_Unmarshal(&handles[1],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_2;
            result = TPMI_RH_AC_Unmarshal(&handles[2],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_3;
            break;
#endif     // CC_AC_Send
#if defined CC_Policy_AC_SendSelect && CC_Policy_AC_SendSelect == YES
        case TPM_CC_Policy_AC_SendSelect:
            *handleCount = 1;
            result = TPMI_SH_POLICY_Unmarshal(&handles[0],  handleBufferStart, bufferRemainingSize);
            if(result != TPM_RC_SUCCESS) 
                return result + TPM_RC_H + TPM_RC_1;
            break;
#endif     // CC_Policy_AC_SendSelect
#if defined CC_Vendor_TCG_Test && CC_Vendor_TCG_Test == YES
        case TPM_CC_Vendor_TCG_Test:
            *handleCount = 0;
            break;
#endif     // CC_Vendor_TCG_Test
