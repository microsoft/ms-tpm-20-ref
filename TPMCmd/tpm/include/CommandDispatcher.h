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
    This file created on Apr 10, 2017, 04:58:00PM 
*/
#if defined CC_Startup && CC_Startup == YES
        case TPM_CC_Startup:
        {
            // Buffer for input parameters
            Startup_In *in = 
                (Startup_In *) MemoryGetActionInputBuffer(sizeof(Startup_In));
            result = TPM_SU_Unmarshal(&in->startupType, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Startup_startupType;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Startup action routine
            result = TPM2_Startup(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Startup == YES
#if defined CC_Shutdown && CC_Shutdown == YES
        case TPM_CC_Shutdown:
        {
            // Buffer for input parameters
            Shutdown_In *in = 
                (Shutdown_In *) MemoryGetActionInputBuffer(sizeof(Shutdown_In));
            result = TPM_SU_Unmarshal(&in->shutdownType, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Shutdown_shutdownType;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Shutdown action routine
            result = TPM2_Shutdown(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Shutdown == YES
#if defined CC_SelfTest && CC_SelfTest == YES
        case TPM_CC_SelfTest:
        {
            // Buffer for input parameters
            SelfTest_In *in = 
                (SelfTest_In *) MemoryGetActionInputBuffer(sizeof(SelfTest_In));
            result = TPMI_YES_NO_Unmarshal(&in->fullTest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SelfTest_fullTest;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SelfTest action routine
            result = TPM2_SelfTest(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SelfTest == YES
#if defined CC_IncrementalSelfTest && CC_IncrementalSelfTest == YES
        case TPM_CC_IncrementalSelfTest:
        {
            // Buffer for input parameters
            IncrementalSelfTest_In *in = 
                (IncrementalSelfTest_In *) MemoryGetActionInputBuffer(sizeof(IncrementalSelfTest_In));
            // Buffer for output parameters
            IncrementalSelfTest_Out *out = 
                (IncrementalSelfTest_Out *) MemoryGetActionOutputBuffer(sizeof(IncrementalSelfTest_Out));

            result = TPML_ALG_Unmarshal(&in->toTest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_IncrementalSelfTest_toTest;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_IncrementalSelfTest action routine
            result = TPM2_IncrementalSelfTest(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(IncrementalSelfTest_Out);
            *respParmSize += TPML_ALG_Marshal(&out->toDoList, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_IncrementalSelfTest == YES
#if defined CC_GetTestResult && CC_GetTestResult == YES
        case TPM_CC_GetTestResult:
        {
            // Buffer for output parameters
            GetTestResult_Out *out = 
                (GetTestResult_Out *) MemoryGetActionOutputBuffer(sizeof(GetTestResult_Out));

            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetTestResult action routine
            result = TPM2_GetTestResult(out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetTestResult_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, &responseBuffer, &rSize);
            *respParmSize += TPM_RC_Marshal(&out->testResult, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetTestResult == YES
#if defined CC_StartAuthSession && CC_StartAuthSession == YES
        case TPM_CC_StartAuthSession:
        {
            // Buffer for input parameters
            StartAuthSession_In *in = 
                (StartAuthSession_In *) MemoryGetActionInputBuffer(sizeof(StartAuthSession_In));
            // Buffer for output parameters
            StartAuthSession_Out *out = 
                (StartAuthSession_Out *) MemoryGetActionOutputBuffer(sizeof(StartAuthSession_Out));

            in->tpmKey = handles[0];
            in->bind = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceCaller, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_nonceCaller;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->encryptedSalt, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_encryptedSalt;
            result = TPM_SE_Unmarshal(&in->sessionType, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_sessionType;
            result = TPMT_SYM_DEF_Unmarshal(&in->symmetric, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_symmetric;
            result = TPMI_ALG_HASH_Unmarshal(&in->authHash, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_authHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_StartAuthSession action routine
            result = TPM2_StartAuthSession(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(StartAuthSession_Out);
            *responseHandleSize += TPMI_SH_AUTH_SESSION_Marshal(&out->sessionHandle, &responseHandle, &rSize);
            *respParmSize += TPM2B_NONCE_Marshal(&out->nonceTPM, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_StartAuthSession == YES
#if defined CC_PolicyRestart && CC_PolicyRestart == YES
        case TPM_CC_PolicyRestart:
        {
            // Buffer for input parameters
            PolicyRestart_In *in = 
                (PolicyRestart_In *) MemoryGetActionInputBuffer(sizeof(PolicyRestart_In));
            in->sessionHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyRestart action routine
            result = TPM2_PolicyRestart(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyRestart == YES
#if defined CC_Create && CC_Create == YES
        case TPM_CC_Create:
        {
            // Buffer for input parameters
            Create_In *in = 
                (Create_In *) MemoryGetActionInputBuffer(sizeof(Create_In));
            // Buffer for output parameters
            Create_Out *out = 
                (Create_Out *) MemoryGetActionOutputBuffer(sizeof(Create_Out));

            in->parentHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_inSensitive;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_inPublic;
            result = TPM2B_DATA_Unmarshal(&in->outsideInfo, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_outsideInfo;
            result = TPML_PCR_SELECTION_Unmarshal(&in->creationPCR, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_creationPCR;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Create action routine
            result = TPM2_Create(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Create_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, &responseBuffer, &rSize);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, &responseBuffer, &rSize);
            *respParmSize += TPM2B_CREATION_DATA_Marshal(&out->creationData, &responseBuffer, &rSize);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->creationHash, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_CREATION_Marshal(&out->creationTicket, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Create == YES
#if defined CC_Load && CC_Load == YES
        case TPM_CC_Load:
        {
            // Buffer for input parameters
            Load_In *in = 
                (Load_In *) MemoryGetActionInputBuffer(sizeof(Load_In));
            // Buffer for output parameters
            Load_Out *out = 
                (Load_Out *) MemoryGetActionOutputBuffer(sizeof(Load_Out));

            in->parentHandle = handles[0];
            result = TPM2B_PRIVATE_Unmarshal(&in->inPrivate, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Load_inPrivate;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Load_inPublic;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Load action routine
            result = TPM2_Load(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Load_Out);
            *responseHandleSize += TPM_HANDLE_Marshal(&out->objectHandle, &responseHandle, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Load == YES
#if defined CC_LoadExternal && CC_LoadExternal == YES
        case TPM_CC_LoadExternal:
        {
            // Buffer for input parameters
            LoadExternal_In *in = 
                (LoadExternal_In *) MemoryGetActionInputBuffer(sizeof(LoadExternal_In));
            // Buffer for output parameters
            LoadExternal_Out *out = 
                (LoadExternal_Out *) MemoryGetActionOutputBuffer(sizeof(LoadExternal_Out));

            result = TPM2B_SENSITIVE_Unmarshal(&in->inPrivate, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_inPrivate;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_inPublic;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_LoadExternal action routine
            result = TPM2_LoadExternal(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(LoadExternal_Out);
            *responseHandleSize += TPM_HANDLE_Marshal(&out->objectHandle, &responseHandle, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_LoadExternal == YES
#if defined CC_ReadPublic && CC_ReadPublic == YES
        case TPM_CC_ReadPublic:
        {
            // Buffer for input parameters
            ReadPublic_In *in = 
                (ReadPublic_In *) MemoryGetActionInputBuffer(sizeof(ReadPublic_In));
            // Buffer for output parameters
            ReadPublic_Out *out = 
                (ReadPublic_Out *) MemoryGetActionOutputBuffer(sizeof(ReadPublic_Out));

            in->objectHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ReadPublic action routine
            result = TPM2_ReadPublic(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ReadPublic_Out);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, &responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, &responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->qualifiedName, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ReadPublic == YES
#if defined CC_ActivateCredential && CC_ActivateCredential == YES
        case TPM_CC_ActivateCredential:
        {
            // Buffer for input parameters
            ActivateCredential_In *in = 
                (ActivateCredential_In *) MemoryGetActionInputBuffer(sizeof(ActivateCredential_In));
            // Buffer for output parameters
            ActivateCredential_Out *out = 
                (ActivateCredential_Out *) MemoryGetActionOutputBuffer(sizeof(ActivateCredential_Out));

            in->activateHandle = handles[0];
            in->keyHandle = handles[1];
            result = TPM2B_ID_OBJECT_Unmarshal(&in->credentialBlob, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ActivateCredential_credentialBlob;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->secret, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ActivateCredential_secret;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ActivateCredential action routine
            result = TPM2_ActivateCredential(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ActivateCredential_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->certInfo, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ActivateCredential == YES
#if defined CC_MakeCredential && CC_MakeCredential == YES
        case TPM_CC_MakeCredential:
        {
            // Buffer for input parameters
            MakeCredential_In *in = 
                (MakeCredential_In *) MemoryGetActionInputBuffer(sizeof(MakeCredential_In));
            // Buffer for output parameters
            MakeCredential_Out *out = 
                (MakeCredential_Out *) MemoryGetActionOutputBuffer(sizeof(MakeCredential_Out));

            in->handle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->credential, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MakeCredential_credential;
            result = TPM2B_NAME_Unmarshal(&in->objectName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MakeCredential_objectName;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_MakeCredential action routine
            result = TPM2_MakeCredential(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MakeCredential_Out);
            *respParmSize += TPM2B_ID_OBJECT_Marshal(&out->credentialBlob, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->secret, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_MakeCredential == YES
#if defined CC_Unseal && CC_Unseal == YES
        case TPM_CC_Unseal:
        {
            // Buffer for input parameters
            Unseal_In *in = 
                (Unseal_In *) MemoryGetActionInputBuffer(sizeof(Unseal_In));
            // Buffer for output parameters
            Unseal_Out *out = 
                (Unseal_Out *) MemoryGetActionOutputBuffer(sizeof(Unseal_Out));

            in->itemHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Unseal action routine
            result = TPM2_Unseal(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Unseal_Out);
            *respParmSize += TPM2B_SENSITIVE_DATA_Marshal(&out->outData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Unseal == YES
#if defined CC_ObjectChangeAuth && CC_ObjectChangeAuth == YES
        case TPM_CC_ObjectChangeAuth:
        {
            // Buffer for input parameters
            ObjectChangeAuth_In *in = 
                (ObjectChangeAuth_In *) MemoryGetActionInputBuffer(sizeof(ObjectChangeAuth_In));
            // Buffer for output parameters
            ObjectChangeAuth_Out *out = 
                (ObjectChangeAuth_Out *) MemoryGetActionOutputBuffer(sizeof(ObjectChangeAuth_Out));

            in->objectHandle = handles[0];
            in->parentHandle = handles[1];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ObjectChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ObjectChangeAuth action routine
            result = TPM2_ObjectChangeAuth(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ObjectChangeAuth_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ObjectChangeAuth == YES
#if defined CC_CreateLoaded && CC_CreateLoaded == YES
        case TPM_CC_CreateLoaded:
        {
            // Buffer for input parameters
            CreateLoaded_In *in = 
                (CreateLoaded_In *) MemoryGetActionInputBuffer(sizeof(CreateLoaded_In));
            // Buffer for output parameters
            CreateLoaded_Out *out = 
                (CreateLoaded_Out *) MemoryGetActionOutputBuffer(sizeof(CreateLoaded_Out));

            in->parentHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreateLoaded_inSensitive;
            result = TPM2B_TEMPLATE_Unmarshal(&in->inPublic, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreateLoaded_inPublic;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_CreateLoaded action routine
            result = TPM2_CreateLoaded(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CreateLoaded_Out);
            *responseHandleSize += TPM_HANDLE_Marshal(&out->objectHandle, &responseHandle, &rSize);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, &responseBuffer, &rSize);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, &responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_CreateLoaded == YES
#if defined CC_Duplicate && CC_Duplicate == YES
        case TPM_CC_Duplicate:
        {
            // Buffer for input parameters
            Duplicate_In *in = 
                (Duplicate_In *) MemoryGetActionInputBuffer(sizeof(Duplicate_In));
            // Buffer for output parameters
            Duplicate_Out *out = 
                (Duplicate_Out *) MemoryGetActionOutputBuffer(sizeof(Duplicate_Out));

            in->objectHandle = handles[0];
            in->newParentHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->encryptionKeyIn, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Duplicate_encryptionKeyIn;
            result = TPMT_SYM_DEF_OBJECT_Unmarshal(&in->symmetricAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Duplicate_symmetricAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Duplicate action routine
            result = TPM2_Duplicate(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Duplicate_Out);
            *respParmSize += TPM2B_DATA_Marshal(&out->encryptionKeyOut, &responseBuffer, &rSize);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->duplicate, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->outSymSeed, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Duplicate == YES
#if defined CC_Rewrap && CC_Rewrap == YES
        case TPM_CC_Rewrap:
        {
            // Buffer for input parameters
            Rewrap_In *in = 
                (Rewrap_In *) MemoryGetActionInputBuffer(sizeof(Rewrap_In));
            // Buffer for output parameters
            Rewrap_Out *out = 
                (Rewrap_Out *) MemoryGetActionOutputBuffer(sizeof(Rewrap_Out));

            in->oldParent = handles[0];
            in->newParent = handles[1];
            result = TPM2B_PRIVATE_Unmarshal(&in->inDuplicate, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_inDuplicate;
            result = TPM2B_NAME_Unmarshal(&in->name, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_name;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->inSymSeed, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_inSymSeed;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Rewrap action routine
            result = TPM2_Rewrap(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Rewrap_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outDuplicate, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->outSymSeed, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Rewrap == YES
#if defined CC_Import && CC_Import == YES
        case TPM_CC_Import:
        {
            // Buffer for input parameters
            Import_In *in = 
                (Import_In *) MemoryGetActionInputBuffer(sizeof(Import_In));
            // Buffer for output parameters
            Import_Out *out = 
                (Import_Out *) MemoryGetActionOutputBuffer(sizeof(Import_Out));

            in->parentHandle = handles[0];
            result = TPM2B_DATA_Unmarshal(&in->encryptionKey, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_encryptionKey;
            result = TPM2B_PUBLIC_Unmarshal(&in->objectPublic, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_objectPublic;
            result = TPM2B_PRIVATE_Unmarshal(&in->duplicate, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_duplicate;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->inSymSeed, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_inSymSeed;
            result = TPMT_SYM_DEF_OBJECT_Unmarshal(&in->symmetricAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_symmetricAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Import action routine
            result = TPM2_Import(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Import_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Import == YES
#if defined CC_RSA_Encrypt && CC_RSA_Encrypt == YES
        case TPM_CC_RSA_Encrypt:
        {
            // Buffer for input parameters
            RSA_Encrypt_In *in = 
                (RSA_Encrypt_In *) MemoryGetActionInputBuffer(sizeof(RSA_Encrypt_In));
            // Buffer for output parameters
            RSA_Encrypt_Out *out = 
                (RSA_Encrypt_Out *) MemoryGetActionOutputBuffer(sizeof(RSA_Encrypt_Out));

            in->keyHandle = handles[0];
            result = TPM2B_PUBLIC_KEY_RSA_Unmarshal(&in->message, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_message;
            result = TPMT_RSA_DECRYPT_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_inScheme;
            result = TPM2B_DATA_Unmarshal(&in->label, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_label;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_RSA_Encrypt action routine
            result = TPM2_RSA_Encrypt(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(RSA_Encrypt_Out);
            *respParmSize += TPM2B_PUBLIC_KEY_RSA_Marshal(&out->outData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_RSA_Encrypt == YES
#if defined CC_RSA_Decrypt && CC_RSA_Decrypt == YES
        case TPM_CC_RSA_Decrypt:
        {
            // Buffer for input parameters
            RSA_Decrypt_In *in = 
                (RSA_Decrypt_In *) MemoryGetActionInputBuffer(sizeof(RSA_Decrypt_In));
            // Buffer for output parameters
            RSA_Decrypt_Out *out = 
                (RSA_Decrypt_Out *) MemoryGetActionOutputBuffer(sizeof(RSA_Decrypt_Out));

            in->keyHandle = handles[0];
            result = TPM2B_PUBLIC_KEY_RSA_Unmarshal(&in->cipherText, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_cipherText;
            result = TPMT_RSA_DECRYPT_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_inScheme;
            result = TPM2B_DATA_Unmarshal(&in->label, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_label;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_RSA_Decrypt action routine
            result = TPM2_RSA_Decrypt(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(RSA_Decrypt_Out);
            *respParmSize += TPM2B_PUBLIC_KEY_RSA_Marshal(&out->message, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_RSA_Decrypt == YES
#if defined CC_ECDH_KeyGen && CC_ECDH_KeyGen == YES
        case TPM_CC_ECDH_KeyGen:
        {
            // Buffer for input parameters
            ECDH_KeyGen_In *in = 
                (ECDH_KeyGen_In *) MemoryGetActionInputBuffer(sizeof(ECDH_KeyGen_In));
            // Buffer for output parameters
            ECDH_KeyGen_Out *out = 
                (ECDH_KeyGen_Out *) MemoryGetActionOutputBuffer(sizeof(ECDH_KeyGen_Out));

            in->keyHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ECDH_KeyGen action routine
            result = TPM2_ECDH_KeyGen(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECDH_KeyGen_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->zPoint, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->pubPoint, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECDH_KeyGen == YES
#if defined CC_ECDH_ZGen && CC_ECDH_ZGen == YES
        case TPM_CC_ECDH_ZGen:
        {
            // Buffer for input parameters
            ECDH_ZGen_In *in = 
                (ECDH_ZGen_In *) MemoryGetActionInputBuffer(sizeof(ECDH_ZGen_In));
            // Buffer for output parameters
            ECDH_ZGen_Out *out = 
                (ECDH_ZGen_Out *) MemoryGetActionOutputBuffer(sizeof(ECDH_ZGen_Out));

            in->keyHandle = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->inPoint, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ECDH_ZGen_inPoint;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ECDH_ZGen action routine
            result = TPM2_ECDH_ZGen(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECDH_ZGen_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outPoint, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECDH_ZGen == YES
#if defined CC_ECC_Parameters && CC_ECC_Parameters == YES
        case TPM_CC_ECC_Parameters:
        {
            // Buffer for input parameters
            ECC_Parameters_In *in = 
                (ECC_Parameters_In *) MemoryGetActionInputBuffer(sizeof(ECC_Parameters_In));
            // Buffer for output parameters
            ECC_Parameters_Out *out = 
                (ECC_Parameters_Out *) MemoryGetActionOutputBuffer(sizeof(ECC_Parameters_Out));

            result = TPMI_ECC_CURVE_Unmarshal(&in->curveID, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ECC_Parameters_curveID;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ECC_Parameters action routine
            result = TPM2_ECC_Parameters(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECC_Parameters_Out);
            *respParmSize += TPMS_ALGORITHM_DETAIL_ECC_Marshal(&out->parameters, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECC_Parameters == YES
#if defined CC_ZGen_2Phase && CC_ZGen_2Phase == YES
        case TPM_CC_ZGen_2Phase:
        {
            // Buffer for input parameters
            ZGen_2Phase_In *in = 
                (ZGen_2Phase_In *) MemoryGetActionInputBuffer(sizeof(ZGen_2Phase_In));
            // Buffer for output parameters
            ZGen_2Phase_Out *out = 
                (ZGen_2Phase_Out *) MemoryGetActionOutputBuffer(sizeof(ZGen_2Phase_Out));

            in->keyA = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->inQsB, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inQsB;
            result = TPM2B_ECC_POINT_Unmarshal(&in->inQeB, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inQeB;
            result = TPMI_ECC_KEY_EXCHANGE_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inScheme;
            result = UINT16_Unmarshal(&in->counter, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_counter;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ZGen_2Phase action routine
            result = TPM2_ZGen_2Phase(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ZGen_2Phase_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outZ1, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outZ2, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ZGen_2Phase == YES
#if defined CC_EncryptDecrypt && CC_EncryptDecrypt == YES
        case TPM_CC_EncryptDecrypt:
        {
            // Buffer for input parameters
            EncryptDecrypt_In *in = 
                (EncryptDecrypt_In *) MemoryGetActionInputBuffer(sizeof(EncryptDecrypt_In));
            // Buffer for output parameters
            EncryptDecrypt_Out *out = 
                (EncryptDecrypt_Out *) MemoryGetActionOutputBuffer(sizeof(EncryptDecrypt_Out));

            in->keyHandle = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->decrypt, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_decrypt;
            result = TPMI_ALG_CIPHER_MODE_Unmarshal(&in->mode, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_mode;
            result = TPM2B_IV_Unmarshal(&in->ivIn, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_ivIn;
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->inData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_inData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_EncryptDecrypt action routine
            result = TPM2_EncryptDecrypt(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EncryptDecrypt_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, &responseBuffer, &rSize);
            *respParmSize += TPM2B_IV_Marshal(&out->ivOut, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_EncryptDecrypt == YES
#if defined CC_EncryptDecrypt2 && CC_EncryptDecrypt2 == YES
        case TPM_CC_EncryptDecrypt2:
        {
            // Buffer for input parameters
            EncryptDecrypt2_In *in = 
                (EncryptDecrypt2_In *) MemoryGetActionInputBuffer(sizeof(EncryptDecrypt2_In));
            // Buffer for output parameters
            EncryptDecrypt2_Out *out = 
                (EncryptDecrypt2_Out *) MemoryGetActionOutputBuffer(sizeof(EncryptDecrypt2_Out));

            in->keyHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->inData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_inData;
            result = TPMI_YES_NO_Unmarshal(&in->decrypt, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_decrypt;
            result = TPMI_ALG_CIPHER_MODE_Unmarshal(&in->mode, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_mode;
            result = TPM2B_IV_Unmarshal(&in->ivIn, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_ivIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_EncryptDecrypt2 action routine
            result = TPM2_EncryptDecrypt2(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EncryptDecrypt2_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, &responseBuffer, &rSize);
            *respParmSize += TPM2B_IV_Marshal(&out->ivOut, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_EncryptDecrypt2 == YES
#if defined CC_Hash && CC_Hash == YES
        case TPM_CC_Hash:
        {
            // Buffer for input parameters
            Hash_In *in = 
                (Hash_In *) MemoryGetActionInputBuffer(sizeof(Hash_In));
            // Buffer for output parameters
            Hash_Out *out = 
                (Hash_Out *) MemoryGetActionOutputBuffer(sizeof(Hash_Out));

            result = TPM2B_MAX_BUFFER_Unmarshal(&in->data, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_data;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_hashAlg;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Hash action routine
            result = TPM2_Hash(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Hash_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outHash, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_HASHCHECK_Marshal(&out->validation, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Hash == YES
#if defined CC_HMAC && CC_HMAC == YES
        case TPM_CC_HMAC:
        {
            // Buffer for input parameters
            HMAC_In *in = 
                (HMAC_In *) MemoryGetActionInputBuffer(sizeof(HMAC_In));
            // Buffer for output parameters
            HMAC_Out *out = 
                (HMAC_Out *) MemoryGetActionOutputBuffer(sizeof(HMAC_Out));

            in->handle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_buffer;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_HMAC action routine
            result = TPM2_HMAC(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HMAC_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outHMAC, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_HMAC == YES
#if defined CC_MAC && CC_MAC == YES
        case TPM_CC_MAC:
        {
            // Buffer for input parameters
            MAC_In *in = 
                (MAC_In *) MemoryGetActionInputBuffer(sizeof(MAC_In));
            // Buffer for output parameters
            MAC_Out *out = 
                (MAC_Out *) MemoryGetActionOutputBuffer(sizeof(MAC_Out));

            in->handle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_buffer;
            result = TPMI_ALG_MAC_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_MAC action routine
            result = TPM2_MAC(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MAC_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outMAC, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_MAC == YES
#if defined CC_GetRandom && CC_GetRandom == YES
        case TPM_CC_GetRandom:
        {
            // Buffer for input parameters
            GetRandom_In *in = 
                (GetRandom_In *) MemoryGetActionInputBuffer(sizeof(GetRandom_In));
            // Buffer for output parameters
            GetRandom_Out *out = 
                (GetRandom_Out *) MemoryGetActionOutputBuffer(sizeof(GetRandom_Out));

            result = UINT16_Unmarshal(&in->bytesRequested, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetRandom_bytesRequested;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetRandom action routine
            result = TPM2_GetRandom(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetRandom_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->randomBytes, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetRandom == YES
#if defined CC_StirRandom && CC_StirRandom == YES
        case TPM_CC_StirRandom:
        {
            // Buffer for input parameters
            StirRandom_In *in = 
                (StirRandom_In *) MemoryGetActionInputBuffer(sizeof(StirRandom_In));
            result = TPM2B_SENSITIVE_DATA_Unmarshal(&in->inData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StirRandom_inData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_StirRandom action routine
            result = TPM2_StirRandom(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_StirRandom == YES
#if defined CC_HMAC_Start && CC_HMAC_Start == YES
        case TPM_CC_HMAC_Start:
        {
            // Buffer for input parameters
            HMAC_Start_In *in = 
                (HMAC_Start_In *) MemoryGetActionInputBuffer(sizeof(HMAC_Start_In));
            // Buffer for output parameters
            HMAC_Start_Out *out = 
                (HMAC_Start_Out *) MemoryGetActionOutputBuffer(sizeof(HMAC_Start_Out));

            in->handle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_Start_auth;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_Start_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_HMAC_Start action routine
            result = TPM2_HMAC_Start(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HMAC_Start_Out);
            *responseHandleSize += TPMI_DH_OBJECT_Marshal(&out->sequenceHandle, &responseHandle, &rSize);
        }
        break;
#endif     // CC_HMAC_Start == YES
#if defined CC_MAC_Start && CC_MAC_Start == YES
        case TPM_CC_MAC_Start:
        {
            // Buffer for input parameters
            MAC_Start_In *in = 
                (MAC_Start_In *) MemoryGetActionInputBuffer(sizeof(MAC_Start_In));
            // Buffer for output parameters
            MAC_Start_Out *out = 
                (MAC_Start_Out *) MemoryGetActionOutputBuffer(sizeof(MAC_Start_Out));

            in->handle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_Start_auth;
            result = TPMI_ALG_MAC_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_Start_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_MAC_Start action routine
            result = TPM2_MAC_Start(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MAC_Start_Out);
            *responseHandleSize += TPMI_DH_OBJECT_Marshal(&out->sequenceHandle, &responseHandle, &rSize);
        }
        break;
#endif     // CC_MAC_Start == YES
#if defined CC_HashSequenceStart && CC_HashSequenceStart == YES
        case TPM_CC_HashSequenceStart:
        {
            // Buffer for input parameters
            HashSequenceStart_In *in = 
                (HashSequenceStart_In *) MemoryGetActionInputBuffer(sizeof(HashSequenceStart_In));
            // Buffer for output parameters
            HashSequenceStart_Out *out = 
                (HashSequenceStart_Out *) MemoryGetActionOutputBuffer(sizeof(HashSequenceStart_Out));

            result = TPM2B_AUTH_Unmarshal(&in->auth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HashSequenceStart_auth;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HashSequenceStart_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_HashSequenceStart action routine
            result = TPM2_HashSequenceStart(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HashSequenceStart_Out);
            *responseHandleSize += TPMI_DH_OBJECT_Marshal(&out->sequenceHandle, &responseHandle, &rSize);
        }
        break;
#endif     // CC_HashSequenceStart == YES
#if defined CC_SequenceUpdate && CC_SequenceUpdate == YES
        case TPM_CC_SequenceUpdate:
        {
            // Buffer for input parameters
            SequenceUpdate_In *in = 
                (SequenceUpdate_In *) MemoryGetActionInputBuffer(sizeof(SequenceUpdate_In));
            in->sequenceHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceUpdate_buffer;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SequenceUpdate action routine
            result = TPM2_SequenceUpdate(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SequenceUpdate == YES
#if defined CC_SequenceComplete && CC_SequenceComplete == YES
        case TPM_CC_SequenceComplete:
        {
            // Buffer for input parameters
            SequenceComplete_In *in = 
                (SequenceComplete_In *) MemoryGetActionInputBuffer(sizeof(SequenceComplete_In));
            // Buffer for output parameters
            SequenceComplete_Out *out = 
                (SequenceComplete_Out *) MemoryGetActionOutputBuffer(sizeof(SequenceComplete_Out));

            in->sequenceHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceComplete_buffer;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceComplete_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SequenceComplete action routine
            result = TPM2_SequenceComplete(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(SequenceComplete_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->result, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_HASHCHECK_Marshal(&out->validation, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_SequenceComplete == YES
#if defined CC_EventSequenceComplete && CC_EventSequenceComplete == YES
        case TPM_CC_EventSequenceComplete:
        {
            // Buffer for input parameters
            EventSequenceComplete_In *in = 
                (EventSequenceComplete_In *) MemoryGetActionInputBuffer(sizeof(EventSequenceComplete_In));
            // Buffer for output parameters
            EventSequenceComplete_Out *out = 
                (EventSequenceComplete_Out *) MemoryGetActionOutputBuffer(sizeof(EventSequenceComplete_Out));

            in->pcrHandle = handles[0];
            in->sequenceHandle = handles[1];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EventSequenceComplete_buffer;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_EventSequenceComplete action routine
            result = TPM2_EventSequenceComplete(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EventSequenceComplete_Out);
            *respParmSize += TPML_DIGEST_VALUES_Marshal(&out->results, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_EventSequenceComplete == YES
#if defined CC_Certify && CC_Certify == YES
        case TPM_CC_Certify:
        {
            // Buffer for input parameters
            Certify_In *in = 
                (Certify_In *) MemoryGetActionInputBuffer(sizeof(Certify_In));
            // Buffer for output parameters
            Certify_Out *out = 
                (Certify_Out *) MemoryGetActionOutputBuffer(sizeof(Certify_Out));

            in->objectHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Certify_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Certify_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Certify action routine
            result = TPM2_Certify(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Certify_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Certify == YES
#if defined CC_CertifyCreation && CC_CertifyCreation == YES
        case TPM_CC_CertifyCreation:
        {
            // Buffer for input parameters
            CertifyCreation_In *in = 
                (CertifyCreation_In *) MemoryGetActionInputBuffer(sizeof(CertifyCreation_In));
            // Buffer for output parameters
            CertifyCreation_Out *out = 
                (CertifyCreation_Out *) MemoryGetActionOutputBuffer(sizeof(CertifyCreation_Out));

            in->signHandle = handles[0];
            in->objectHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_qualifyingData;
            result = TPM2B_DIGEST_Unmarshal(&in->creationHash, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_creationHash;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_inScheme;
            result = TPMT_TK_CREATION_Unmarshal(&in->creationTicket, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_creationTicket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_CertifyCreation action routine
            result = TPM2_CertifyCreation(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CertifyCreation_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_CertifyCreation == YES
#if defined CC_Quote && CC_Quote == YES
        case TPM_CC_Quote:
        {
            // Buffer for input parameters
            Quote_In *in = 
                (Quote_In *) MemoryGetActionInputBuffer(sizeof(Quote_In));
            // Buffer for output parameters
            Quote_Out *out = 
                (Quote_Out *) MemoryGetActionOutputBuffer(sizeof(Quote_Out));

            in->signHandle = handles[0];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_inScheme;
            result = TPML_PCR_SELECTION_Unmarshal(&in->PCRselect, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_PCRselect;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Quote action routine
            result = TPM2_Quote(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Quote_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->quoted, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Quote == YES
#if defined CC_GetSessionAuditDigest && CC_GetSessionAuditDigest == YES
        case TPM_CC_GetSessionAuditDigest:
        {
            // Buffer for input parameters
            GetSessionAuditDigest_In *in = 
                (GetSessionAuditDigest_In *) MemoryGetActionInputBuffer(sizeof(GetSessionAuditDigest_In));
            // Buffer for output parameters
            GetSessionAuditDigest_Out *out = 
                (GetSessionAuditDigest_Out *) MemoryGetActionOutputBuffer(sizeof(GetSessionAuditDigest_Out));

            in->privacyAdminHandle = handles[0];
            in->signHandle = handles[1];
            in->sessionHandle = handles[2];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetSessionAuditDigest_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetSessionAuditDigest_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetSessionAuditDigest action routine
            result = TPM2_GetSessionAuditDigest(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetSessionAuditDigest_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->auditInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetSessionAuditDigest == YES
#if defined CC_GetCommandAuditDigest && CC_GetCommandAuditDigest == YES
        case TPM_CC_GetCommandAuditDigest:
        {
            // Buffer for input parameters
            GetCommandAuditDigest_In *in = 
                (GetCommandAuditDigest_In *) MemoryGetActionInputBuffer(sizeof(GetCommandAuditDigest_In));
            // Buffer for output parameters
            GetCommandAuditDigest_Out *out = 
                (GetCommandAuditDigest_Out *) MemoryGetActionOutputBuffer(sizeof(GetCommandAuditDigest_Out));

            in->privacyHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCommandAuditDigest_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCommandAuditDigest_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetCommandAuditDigest action routine
            result = TPM2_GetCommandAuditDigest(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetCommandAuditDigest_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->auditInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetCommandAuditDigest == YES
#if defined CC_GetTime && CC_GetTime == YES
        case TPM_CC_GetTime:
        {
            // Buffer for input parameters
            GetTime_In *in = 
                (GetTime_In *) MemoryGetActionInputBuffer(sizeof(GetTime_In));
            // Buffer for output parameters
            GetTime_Out *out = 
                (GetTime_Out *) MemoryGetActionOutputBuffer(sizeof(GetTime_Out));

            in->privacyAdminHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetTime_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetTime_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetTime action routine
            result = TPM2_GetTime(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetTime_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->timeInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetTime == YES
#if defined CC_Commit && CC_Commit == YES
        case TPM_CC_Commit:
        {
            // Buffer for input parameters
            Commit_In *in = 
                (Commit_In *) MemoryGetActionInputBuffer(sizeof(Commit_In));
            // Buffer for output parameters
            Commit_Out *out = 
                (Commit_Out *) MemoryGetActionOutputBuffer(sizeof(Commit_Out));

            in->signHandle = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->P1, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_P1;
            result = TPM2B_SENSITIVE_DATA_Unmarshal(&in->s2, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_s2;
            result = TPM2B_ECC_PARAMETER_Unmarshal(&in->y2, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_y2;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Commit action routine
            result = TPM2_Commit(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Commit_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->K, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->L, &responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->E, &responseBuffer, &rSize);
            *respParmSize += UINT16_Marshal(&out->counter, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Commit == YES
#if defined CC_EC_Ephemeral && CC_EC_Ephemeral == YES
        case TPM_CC_EC_Ephemeral:
        {
            // Buffer for input parameters
            EC_Ephemeral_In *in = 
                (EC_Ephemeral_In *) MemoryGetActionInputBuffer(sizeof(EC_Ephemeral_In));
            // Buffer for output parameters
            EC_Ephemeral_Out *out = 
                (EC_Ephemeral_Out *) MemoryGetActionOutputBuffer(sizeof(EC_Ephemeral_Out));

            result = TPMI_ECC_CURVE_Unmarshal(&in->curveID, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EC_Ephemeral_curveID;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_EC_Ephemeral action routine
            result = TPM2_EC_Ephemeral(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EC_Ephemeral_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->Q, &responseBuffer, &rSize);
            *respParmSize += UINT16_Marshal(&out->counter, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_EC_Ephemeral == YES
#if defined CC_VerifySignature && CC_VerifySignature == YES
        case TPM_CC_VerifySignature:
        {
            // Buffer for input parameters
            VerifySignature_In *in = 
                (VerifySignature_In *) MemoryGetActionInputBuffer(sizeof(VerifySignature_In));
            // Buffer for output parameters
            VerifySignature_Out *out = 
                (VerifySignature_Out *) MemoryGetActionOutputBuffer(sizeof(VerifySignature_Out));

            in->keyHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->digest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_VerifySignature_digest;
            result = TPMT_SIGNATURE_Unmarshal(&in->signature, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_VerifySignature_signature;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_VerifySignature action routine
            result = TPM2_VerifySignature(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(VerifySignature_Out);
            *respParmSize += TPMT_TK_VERIFIED_Marshal(&out->validation, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_VerifySignature == YES
#if defined CC_Sign && CC_Sign == YES
        case TPM_CC_Sign:
        {
            // Buffer for input parameters
            Sign_In *in = 
                (Sign_In *) MemoryGetActionInputBuffer(sizeof(Sign_In));
            // Buffer for output parameters
            Sign_Out *out = 
                (Sign_Out *) MemoryGetActionOutputBuffer(sizeof(Sign_Out));

            in->keyHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->digest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_digest;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_inScheme;
            result = TPMT_TK_HASHCHECK_Unmarshal(&in->validation, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_validation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Sign action routine
            result = TPM2_Sign(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Sign_Out);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Sign == YES
#if defined CC_SetCommandCodeAuditStatus && CC_SetCommandCodeAuditStatus == YES
        case TPM_CC_SetCommandCodeAuditStatus:
        {
            // Buffer for input parameters
            SetCommandCodeAuditStatus_In *in = 
                (SetCommandCodeAuditStatus_In *) MemoryGetActionInputBuffer(sizeof(SetCommandCodeAuditStatus_In));
            in->auth = handles[0];
            result = TPMI_ALG_HASH_Unmarshal(&in->auditAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_auditAlg;
            result = TPML_CC_Unmarshal(&in->setList, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_setList;
            result = TPML_CC_Unmarshal(&in->clearList, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_clearList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SetCommandCodeAuditStatus action routine
            result = TPM2_SetCommandCodeAuditStatus(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetCommandCodeAuditStatus == YES
#if defined CC_PCR_Extend && CC_PCR_Extend == YES
        case TPM_CC_PCR_Extend:
        {
            // Buffer for input parameters
            PCR_Extend_In *in = 
                (PCR_Extend_In *) MemoryGetActionInputBuffer(sizeof(PCR_Extend_In));
            in->pcrHandle = handles[0];
            result = TPML_DIGEST_VALUES_Unmarshal(&in->digests, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Extend_digests;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_Extend action routine
            result = TPM2_PCR_Extend(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_Extend == YES
#if defined CC_PCR_Event && CC_PCR_Event == YES
        case TPM_CC_PCR_Event:
        {
            // Buffer for input parameters
            PCR_Event_In *in = 
                (PCR_Event_In *) MemoryGetActionInputBuffer(sizeof(PCR_Event_In));
            // Buffer for output parameters
            PCR_Event_Out *out = 
                (PCR_Event_Out *) MemoryGetActionOutputBuffer(sizeof(PCR_Event_Out));

            in->pcrHandle = handles[0];
            result = TPM2B_EVENT_Unmarshal(&in->eventData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Event_eventData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_Event action routine
            result = TPM2_PCR_Event(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Event_Out);
            *respParmSize += TPML_DIGEST_VALUES_Marshal(&out->digests, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Event == YES
#if defined CC_PCR_Read && CC_PCR_Read == YES
        case TPM_CC_PCR_Read:
        {
            // Buffer for input parameters
            PCR_Read_In *in = 
                (PCR_Read_In *) MemoryGetActionInputBuffer(sizeof(PCR_Read_In));
            // Buffer for output parameters
            PCR_Read_Out *out = 
                (PCR_Read_Out *) MemoryGetActionOutputBuffer(sizeof(PCR_Read_Out));

            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrSelectionIn, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Read_pcrSelectionIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_Read action routine
            result = TPM2_PCR_Read(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Read_Out);
            *respParmSize += UINT32_Marshal(&out->pcrUpdateCounter, &responseBuffer, &rSize);
            *respParmSize += TPML_PCR_SELECTION_Marshal(&out->pcrSelectionOut, &responseBuffer, &rSize);
            *respParmSize += TPML_DIGEST_Marshal(&out->pcrValues, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Read == YES
#if defined CC_PCR_Allocate && CC_PCR_Allocate == YES
        case TPM_CC_PCR_Allocate:
        {
            // Buffer for input parameters
            PCR_Allocate_In *in = 
                (PCR_Allocate_In *) MemoryGetActionInputBuffer(sizeof(PCR_Allocate_In));
            // Buffer for output parameters
            PCR_Allocate_Out *out = 
                (PCR_Allocate_Out *) MemoryGetActionOutputBuffer(sizeof(PCR_Allocate_Out));

            in->authHandle = handles[0];
            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrAllocation, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Allocate_pcrAllocation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_Allocate action routine
            result = TPM2_PCR_Allocate(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Allocate_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->allocationSuccess, &responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->maxPCR, &responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->sizeNeeded, &responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->sizeAvailable, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Allocate == YES
#if defined CC_PCR_SetAuthPolicy && CC_PCR_SetAuthPolicy == YES
        case TPM_CC_PCR_SetAuthPolicy:
        {
            // Buffer for input parameters
            PCR_SetAuthPolicy_In *in = 
                (PCR_SetAuthPolicy_In *) MemoryGetActionInputBuffer(sizeof(PCR_SetAuthPolicy_In));
            in->authHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->authPolicy, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_authPolicy;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_hashAlg;
            result = TPMI_DH_PCR_Unmarshal(&in->pcrNum, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_pcrNum;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_SetAuthPolicy action routine
            result = TPM2_PCR_SetAuthPolicy(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_SetAuthPolicy == YES
#if defined CC_PCR_SetAuthValue && CC_PCR_SetAuthValue == YES
        case TPM_CC_PCR_SetAuthValue:
        {
            // Buffer for input parameters
            PCR_SetAuthValue_In *in = 
                (PCR_SetAuthValue_In *) MemoryGetActionInputBuffer(sizeof(PCR_SetAuthValue_In));
            in->pcrHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->auth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthValue_auth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_SetAuthValue action routine
            result = TPM2_PCR_SetAuthValue(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_SetAuthValue == YES
#if defined CC_PCR_Reset && CC_PCR_Reset == YES
        case TPM_CC_PCR_Reset:
        {
            // Buffer for input parameters
            PCR_Reset_In *in = 
                (PCR_Reset_In *) MemoryGetActionInputBuffer(sizeof(PCR_Reset_In));
            in->pcrHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PCR_Reset action routine
            result = TPM2_PCR_Reset(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_Reset == YES
#if defined CC_PolicySigned && CC_PolicySigned == YES
        case TPM_CC_PolicySigned:
        {
            // Buffer for input parameters
            PolicySigned_In *in = 
                (PolicySigned_In *) MemoryGetActionInputBuffer(sizeof(PolicySigned_In));
            // Buffer for output parameters
            PolicySigned_Out *out = 
                (PolicySigned_Out *) MemoryGetActionOutputBuffer(sizeof(PolicySigned_Out));

            in->authObject = handles[0];
            in->policySession = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceTPM, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_nonceTPM;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_policyRef;
            result = INT32_Unmarshal(&in->expiration, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_expiration;
            result = TPMT_SIGNATURE_Unmarshal(&in->auth, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_auth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicySigned action routine
            result = TPM2_PolicySigned(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicySigned_Out);
            *respParmSize += TPM2B_TIMEOUT_Marshal(&out->timeout, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_AUTH_Marshal(&out->policyTicket, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicySigned == YES
#if defined CC_PolicySecret && CC_PolicySecret == YES
        case TPM_CC_PolicySecret:
        {
            // Buffer for input parameters
            PolicySecret_In *in = 
                (PolicySecret_In *) MemoryGetActionInputBuffer(sizeof(PolicySecret_In));
            // Buffer for output parameters
            PolicySecret_Out *out = 
                (PolicySecret_Out *) MemoryGetActionOutputBuffer(sizeof(PolicySecret_Out));

            in->authHandle = handles[0];
            in->policySession = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceTPM, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_nonceTPM;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_policyRef;
            result = INT32_Unmarshal(&in->expiration, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_expiration;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicySecret action routine
            result = TPM2_PolicySecret(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicySecret_Out);
            *respParmSize += TPM2B_TIMEOUT_Marshal(&out->timeout, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_AUTH_Marshal(&out->policyTicket, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicySecret == YES
#if defined CC_PolicyTicket && CC_PolicyTicket == YES
        case TPM_CC_PolicyTicket:
        {
            // Buffer for input parameters
            PolicyTicket_In *in = 
                (PolicyTicket_In *) MemoryGetActionInputBuffer(sizeof(PolicyTicket_In));
            in->policySession = handles[0];
            result = TPM2B_TIMEOUT_Unmarshal(&in->timeout, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_timeout;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_policyRef;
            result = TPM2B_NAME_Unmarshal(&in->authName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_authName;
            result = TPMT_TK_AUTH_Unmarshal(&in->ticket, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_ticket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyTicket action routine
            result = TPM2_PolicyTicket(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyTicket == YES
#if defined CC_PolicyOR && CC_PolicyOR == YES
        case TPM_CC_PolicyOR:
        {
            // Buffer for input parameters
            PolicyOR_In *in = 
                (PolicyOR_In *) MemoryGetActionInputBuffer(sizeof(PolicyOR_In));
            in->policySession = handles[0];
            result = TPML_DIGEST_Unmarshal(&in->pHashList, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyOR_pHashList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyOR action routine
            result = TPM2_PolicyOR(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyOR == YES
#if defined CC_PolicyPCR && CC_PolicyPCR == YES
        case TPM_CC_PolicyPCR:
        {
            // Buffer for input parameters
            PolicyPCR_In *in = 
                (PolicyPCR_In *) MemoryGetActionInputBuffer(sizeof(PolicyPCR_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->pcrDigest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyPCR_pcrDigest;
            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrs, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyPCR_pcrs;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyPCR action routine
            result = TPM2_PolicyPCR(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPCR == YES
#if defined CC_PolicyLocality && CC_PolicyLocality == YES
        case TPM_CC_PolicyLocality:
        {
            // Buffer for input parameters
            PolicyLocality_In *in = 
                (PolicyLocality_In *) MemoryGetActionInputBuffer(sizeof(PolicyLocality_In));
            in->policySession = handles[0];
            result = TPMA_LOCALITY_Unmarshal(&in->locality, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyLocality_locality;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyLocality action routine
            result = TPM2_PolicyLocality(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyLocality == YES
#if defined CC_PolicyNV && CC_PolicyNV == YES
        case TPM_CC_PolicyNV:
        {
            // Buffer for input parameters
            PolicyNV_In *in = 
                (PolicyNV_In *) MemoryGetActionInputBuffer(sizeof(PolicyNV_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            in->policySession = handles[2];
            result = TPM2B_OPERAND_Unmarshal(&in->operandB, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_operandB;
            result = UINT16_Unmarshal(&in->offset, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_offset;
            result = TPM_EO_Unmarshal(&in->operation, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_operation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyNV action routine
            result = TPM2_PolicyNV(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNV == YES
#if defined CC_PolicyCounterTimer && CC_PolicyCounterTimer == YES
        case TPM_CC_PolicyCounterTimer:
        {
            // Buffer for input parameters
            PolicyCounterTimer_In *in = 
                (PolicyCounterTimer_In *) MemoryGetActionInputBuffer(sizeof(PolicyCounterTimer_In));
            in->policySession = handles[0];
            result = TPM2B_OPERAND_Unmarshal(&in->operandB, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_operandB;
            result = UINT16_Unmarshal(&in->offset, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_offset;
            result = TPM_EO_Unmarshal(&in->operation, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_operation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyCounterTimer action routine
            result = TPM2_PolicyCounterTimer(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCounterTimer == YES
#if defined CC_PolicyCommandCode && CC_PolicyCommandCode == YES
        case TPM_CC_PolicyCommandCode:
        {
            // Buffer for input parameters
            PolicyCommandCode_In *in = 
                (PolicyCommandCode_In *) MemoryGetActionInputBuffer(sizeof(PolicyCommandCode_In));
            in->policySession = handles[0];
            result = TPM_CC_Unmarshal(&in->code, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCommandCode_code;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyCommandCode action routine
            result = TPM2_PolicyCommandCode(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCommandCode == YES
#if defined CC_PolicyPhysicalPresence && CC_PolicyPhysicalPresence == YES
        case TPM_CC_PolicyPhysicalPresence:
        {
            // Buffer for input parameters
            PolicyPhysicalPresence_In *in = 
                (PolicyPhysicalPresence_In *) MemoryGetActionInputBuffer(sizeof(PolicyPhysicalPresence_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyPhysicalPresence action routine
            result = TPM2_PolicyPhysicalPresence(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPhysicalPresence == YES
#if defined CC_PolicyCpHash && CC_PolicyCpHash == YES
        case TPM_CC_PolicyCpHash:
        {
            // Buffer for input parameters
            PolicyCpHash_In *in = 
                (PolicyCpHash_In *) MemoryGetActionInputBuffer(sizeof(PolicyCpHash_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCpHash_cpHashA;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyCpHash action routine
            result = TPM2_PolicyCpHash(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCpHash == YES
#if defined CC_PolicyNameHash && CC_PolicyNameHash == YES
        case TPM_CC_PolicyNameHash:
        {
            // Buffer for input parameters
            PolicyNameHash_In *in = 
                (PolicyNameHash_In *) MemoryGetActionInputBuffer(sizeof(PolicyNameHash_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->nameHash, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNameHash_nameHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyNameHash action routine
            result = TPM2_PolicyNameHash(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNameHash == YES
#if defined CC_PolicyDuplicationSelect && CC_PolicyDuplicationSelect == YES
        case TPM_CC_PolicyDuplicationSelect:
        {
            // Buffer for input parameters
            PolicyDuplicationSelect_In *in = 
                (PolicyDuplicationSelect_In *) MemoryGetActionInputBuffer(sizeof(PolicyDuplicationSelect_In));
            in->policySession = handles[0];
            result = TPM2B_NAME_Unmarshal(&in->objectName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_objectName;
            result = TPM2B_NAME_Unmarshal(&in->newParentName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_newParentName;
            result = TPMI_YES_NO_Unmarshal(&in->includeObject, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_includeObject;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyDuplicationSelect action routine
            result = TPM2_PolicyDuplicationSelect(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyDuplicationSelect == YES
#if defined CC_PolicyAuthorize && CC_PolicyAuthorize == YES
        case TPM_CC_PolicyAuthorize:
        {
            // Buffer for input parameters
            PolicyAuthorize_In *in = 
                (PolicyAuthorize_In *) MemoryGetActionInputBuffer(sizeof(PolicyAuthorize_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->approvedPolicy, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_approvedPolicy;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_policyRef;
            result = TPM2B_NAME_Unmarshal(&in->keySign, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_keySign;
            result = TPMT_TK_VERIFIED_Unmarshal(&in->checkTicket, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_checkTicket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyAuthorize action routine
            result = TPM2_PolicyAuthorize(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthorize == YES
#if defined CC_PolicyAuthValue && CC_PolicyAuthValue == YES
        case TPM_CC_PolicyAuthValue:
        {
            // Buffer for input parameters
            PolicyAuthValue_In *in = 
                (PolicyAuthValue_In *) MemoryGetActionInputBuffer(sizeof(PolicyAuthValue_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyAuthValue action routine
            result = TPM2_PolicyAuthValue(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthValue == YES
#if defined CC_PolicyPassword && CC_PolicyPassword == YES
        case TPM_CC_PolicyPassword:
        {
            // Buffer for input parameters
            PolicyPassword_In *in = 
                (PolicyPassword_In *) MemoryGetActionInputBuffer(sizeof(PolicyPassword_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyPassword action routine
            result = TPM2_PolicyPassword(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPassword == YES
#if defined CC_PolicyGetDigest && CC_PolicyGetDigest == YES
        case TPM_CC_PolicyGetDigest:
        {
            // Buffer for input parameters
            PolicyGetDigest_In *in = 
                (PolicyGetDigest_In *) MemoryGetActionInputBuffer(sizeof(PolicyGetDigest_In));
            // Buffer for output parameters
            PolicyGetDigest_Out *out = 
                (PolicyGetDigest_Out *) MemoryGetActionOutputBuffer(sizeof(PolicyGetDigest_Out));

            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyGetDigest action routine
            result = TPM2_PolicyGetDigest(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicyGetDigest_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->policyDigest, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicyGetDigest == YES
#if defined CC_PolicyNvWritten && CC_PolicyNvWritten == YES
        case TPM_CC_PolicyNvWritten:
        {
            // Buffer for input parameters
            PolicyNvWritten_In *in = 
                (PolicyNvWritten_In *) MemoryGetActionInputBuffer(sizeof(PolicyNvWritten_In));
            in->policySession = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->writtenSet, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNvWritten_writtenSet;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyNvWritten action routine
            result = TPM2_PolicyNvWritten(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNvWritten == YES
#if defined CC_PolicyTemplate && CC_PolicyTemplate == YES
        case TPM_CC_PolicyTemplate:
        {
            // Buffer for input parameters
            PolicyTemplate_In *in = 
                (PolicyTemplate_In *) MemoryGetActionInputBuffer(sizeof(PolicyTemplate_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->templateHash, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTemplate_templateHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyTemplate action routine
            result = TPM2_PolicyTemplate(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyTemplate == YES
#if defined CC_PolicyAuthorizeNV && CC_PolicyAuthorizeNV == YES
        case TPM_CC_PolicyAuthorizeNV:
        {
            // Buffer for input parameters
            PolicyAuthorizeNV_In *in = 
                (PolicyAuthorizeNV_In *) MemoryGetActionInputBuffer(sizeof(PolicyAuthorizeNV_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            in->policySession = handles[2];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PolicyAuthorizeNV action routine
            result = TPM2_PolicyAuthorizeNV(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthorizeNV == YES
#if defined CC_CreatePrimary && CC_CreatePrimary == YES
        case TPM_CC_CreatePrimary:
        {
            // Buffer for input parameters
            CreatePrimary_In *in = 
                (CreatePrimary_In *) MemoryGetActionInputBuffer(sizeof(CreatePrimary_In));
            // Buffer for output parameters
            CreatePrimary_Out *out = 
                (CreatePrimary_Out *) MemoryGetActionOutputBuffer(sizeof(CreatePrimary_Out));

            in->primaryHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_inSensitive;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_inPublic;
            result = TPM2B_DATA_Unmarshal(&in->outsideInfo, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_outsideInfo;
            result = TPML_PCR_SELECTION_Unmarshal(&in->creationPCR, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_creationPCR;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_CreatePrimary action routine
            result = TPM2_CreatePrimary(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CreatePrimary_Out);
            *responseHandleSize += TPM_HANDLE_Marshal(&out->objectHandle, &responseHandle, &rSize);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, &responseBuffer, &rSize);
            *respParmSize += TPM2B_CREATION_DATA_Marshal(&out->creationData, &responseBuffer, &rSize);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->creationHash, &responseBuffer, &rSize);
            *respParmSize += TPMT_TK_CREATION_Marshal(&out->creationTicket, &responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_CreatePrimary == YES
#if defined CC_HierarchyControl && CC_HierarchyControl == YES
        case TPM_CC_HierarchyControl:
        {
            // Buffer for input parameters
            HierarchyControl_In *in = 
                (HierarchyControl_In *) MemoryGetActionInputBuffer(sizeof(HierarchyControl_In));
            in->authHandle = handles[0];
            result = TPMI_RH_ENABLES_Unmarshal(&in->enable, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyControl_enable;
            result = TPMI_YES_NO_Unmarshal(&in->state, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyControl_state;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_HierarchyControl action routine
            result = TPM2_HierarchyControl(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_HierarchyControl == YES
#if defined CC_SetPrimaryPolicy && CC_SetPrimaryPolicy == YES
        case TPM_CC_SetPrimaryPolicy:
        {
            // Buffer for input parameters
            SetPrimaryPolicy_In *in = 
                (SetPrimaryPolicy_In *) MemoryGetActionInputBuffer(sizeof(SetPrimaryPolicy_In));
            in->authHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->authPolicy, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetPrimaryPolicy_authPolicy;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetPrimaryPolicy_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SetPrimaryPolicy action routine
            result = TPM2_SetPrimaryPolicy(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetPrimaryPolicy == YES
#if defined CC_ChangePPS && CC_ChangePPS == YES
        case TPM_CC_ChangePPS:
        {
            // Buffer for input parameters
            ChangePPS_In *in = 
                (ChangePPS_In *) MemoryGetActionInputBuffer(sizeof(ChangePPS_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ChangePPS action routine
            result = TPM2_ChangePPS(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ChangePPS == YES
#if defined CC_ChangeEPS && CC_ChangeEPS == YES
        case TPM_CC_ChangeEPS:
        {
            // Buffer for input parameters
            ChangeEPS_In *in = 
                (ChangeEPS_In *) MemoryGetActionInputBuffer(sizeof(ChangeEPS_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ChangeEPS action routine
            result = TPM2_ChangeEPS(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ChangeEPS == YES
#if defined CC_Clear && CC_Clear == YES
        case TPM_CC_Clear:
        {
            // Buffer for input parameters
            Clear_In *in = 
                (Clear_In *) MemoryGetActionInputBuffer(sizeof(Clear_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Clear action routine
            result = TPM2_Clear(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Clear == YES
#if defined CC_ClearControl && CC_ClearControl == YES
        case TPM_CC_ClearControl:
        {
            // Buffer for input parameters
            ClearControl_In *in = 
                (ClearControl_In *) MemoryGetActionInputBuffer(sizeof(ClearControl_In));
            in->auth = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->disable, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClearControl_disable;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ClearControl action routine
            result = TPM2_ClearControl(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClearControl == YES
#if defined CC_HierarchyChangeAuth && CC_HierarchyChangeAuth == YES
        case TPM_CC_HierarchyChangeAuth:
        {
            // Buffer for input parameters
            HierarchyChangeAuth_In *in = 
                (HierarchyChangeAuth_In *) MemoryGetActionInputBuffer(sizeof(HierarchyChangeAuth_In));
            in->authHandle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_HierarchyChangeAuth action routine
            result = TPM2_HierarchyChangeAuth(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_HierarchyChangeAuth == YES
#if defined CC_DictionaryAttackLockReset && CC_DictionaryAttackLockReset == YES
        case TPM_CC_DictionaryAttackLockReset:
        {
            // Buffer for input parameters
            DictionaryAttackLockReset_In *in = 
                (DictionaryAttackLockReset_In *) MemoryGetActionInputBuffer(sizeof(DictionaryAttackLockReset_In));
            in->lockHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_DictionaryAttackLockReset action routine
            result = TPM2_DictionaryAttackLockReset(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_DictionaryAttackLockReset == YES
#if defined CC_DictionaryAttackParameters && CC_DictionaryAttackParameters == YES
        case TPM_CC_DictionaryAttackParameters:
        {
            // Buffer for input parameters
            DictionaryAttackParameters_In *in = 
                (DictionaryAttackParameters_In *) MemoryGetActionInputBuffer(sizeof(DictionaryAttackParameters_In));
            in->lockHandle = handles[0];
            result = UINT32_Unmarshal(&in->newMaxTries, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_newMaxTries;
            result = UINT32_Unmarshal(&in->newRecoveryTime, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_newRecoveryTime;
            result = UINT32_Unmarshal(&in->lockoutRecovery, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_lockoutRecovery;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_DictionaryAttackParameters action routine
            result = TPM2_DictionaryAttackParameters(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_DictionaryAttackParameters == YES
#if defined CC_PP_Commands && CC_PP_Commands == YES
        case TPM_CC_PP_Commands:
        {
            // Buffer for input parameters
            PP_Commands_In *in = 
                (PP_Commands_In *) MemoryGetActionInputBuffer(sizeof(PP_Commands_In));
            in->auth = handles[0];
            result = TPML_CC_Unmarshal(&in->setList, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PP_Commands_setList;
            result = TPML_CC_Unmarshal(&in->clearList, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PP_Commands_clearList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_PP_Commands action routine
            result = TPM2_PP_Commands(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PP_Commands == YES
#if defined CC_SetAlgorithmSet && CC_SetAlgorithmSet == YES
        case TPM_CC_SetAlgorithmSet:
        {
            // Buffer for input parameters
            SetAlgorithmSet_In *in = 
                (SetAlgorithmSet_In *) MemoryGetActionInputBuffer(sizeof(SetAlgorithmSet_In));
            in->authHandle = handles[0];
            result = UINT32_Unmarshal(&in->algorithmSet, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetAlgorithmSet_algorithmSet;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_SetAlgorithmSet action routine
            result = TPM2_SetAlgorithmSet(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetAlgorithmSet == YES
#if defined CC_FieldUpgradeStart && CC_FieldUpgradeStart == YES
        case TPM_CC_FieldUpgradeStart:
        {
            // Buffer for input parameters
            FieldUpgradeStart_In *in = 
                (FieldUpgradeStart_In *) MemoryGetActionInputBuffer(sizeof(FieldUpgradeStart_In));
            in->authorization = handles[0];
            in->keyHandle = handles[1];
            result = TPM2B_DIGEST_Unmarshal(&in->fuDigest, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeStart_fuDigest;
            result = TPMT_SIGNATURE_Unmarshal(&in->manifestSignature, &parm_buffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeStart_manifestSignature;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_FieldUpgradeStart action routine
            result = TPM2_FieldUpgradeStart(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_FieldUpgradeStart == YES
#if defined CC_FieldUpgradeData && CC_FieldUpgradeData == YES
        case TPM_CC_FieldUpgradeData:
        {
            // Buffer for input parameters
            FieldUpgradeData_In *in = 
                (FieldUpgradeData_In *) MemoryGetActionInputBuffer(sizeof(FieldUpgradeData_In));
            // Buffer for output parameters
            FieldUpgradeData_Out *out = 
                (FieldUpgradeData_Out *) MemoryGetActionOutputBuffer(sizeof(FieldUpgradeData_Out));

            result = TPM2B_MAX_BUFFER_Unmarshal(&in->fuData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeData_fuData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_FieldUpgradeData action routine
            result = TPM2_FieldUpgradeData(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(FieldUpgradeData_Out);
            *respParmSize += TPMT_HA_Marshal(&out->nextDigest, &responseBuffer, &rSize);
            *respParmSize += TPMT_HA_Marshal(&out->firstDigest, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_FieldUpgradeData == YES
#if defined CC_FirmwareRead && CC_FirmwareRead == YES
        case TPM_CC_FirmwareRead:
        {
            // Buffer for input parameters
            FirmwareRead_In *in = 
                (FirmwareRead_In *) MemoryGetActionInputBuffer(sizeof(FirmwareRead_In));
            // Buffer for output parameters
            FirmwareRead_Out *out = 
                (FirmwareRead_Out *) MemoryGetActionOutputBuffer(sizeof(FirmwareRead_Out));

            result = UINT32_Unmarshal(&in->sequenceNumber, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FirmwareRead_sequenceNumber;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_FirmwareRead action routine
            result = TPM2_FirmwareRead(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(FirmwareRead_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->fuData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_FirmwareRead == YES
#if defined CC_ContextSave && CC_ContextSave == YES
        case TPM_CC_ContextSave:
        {
            // Buffer for input parameters
            ContextSave_In *in = 
                (ContextSave_In *) MemoryGetActionInputBuffer(sizeof(ContextSave_In));
            // Buffer for output parameters
            ContextSave_Out *out = 
                (ContextSave_Out *) MemoryGetActionOutputBuffer(sizeof(ContextSave_Out));

            in->saveHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ContextSave action routine
            result = TPM2_ContextSave(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ContextSave_Out);
            *respParmSize += TPMS_CONTEXT_Marshal(&out->context, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ContextSave == YES
#if defined CC_ContextLoad && CC_ContextLoad == YES
        case TPM_CC_ContextLoad:
        {
            // Buffer for input parameters
            ContextLoad_In *in = 
                (ContextLoad_In *) MemoryGetActionInputBuffer(sizeof(ContextLoad_In));
            // Buffer for output parameters
            ContextLoad_Out *out = 
                (ContextLoad_Out *) MemoryGetActionOutputBuffer(sizeof(ContextLoad_Out));

            result = TPMS_CONTEXT_Unmarshal(&in->context, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ContextLoad_context;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ContextLoad action routine
            result = TPM2_ContextLoad(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ContextLoad_Out);
            *responseHandleSize += TPMI_DH_CONTEXT_Marshal(&out->loadedHandle, &responseHandle, &rSize);
        }
        break;
#endif     // CC_ContextLoad == YES
#if defined CC_FlushContext && CC_FlushContext == YES
        case TPM_CC_FlushContext:
        {
            // Buffer for input parameters
            FlushContext_In *in = 
                (FlushContext_In *) MemoryGetActionInputBuffer(sizeof(FlushContext_In));
            result = TPMI_DH_CONTEXT_Unmarshal(&in->flushHandle, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FlushContext_flushHandle;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_FlushContext action routine
            result = TPM2_FlushContext(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_FlushContext == YES
#if defined CC_EvictControl && CC_EvictControl == YES
        case TPM_CC_EvictControl:
        {
            // Buffer for input parameters
            EvictControl_In *in = 
                (EvictControl_In *) MemoryGetActionInputBuffer(sizeof(EvictControl_In));
            in->auth = handles[0];
            in->objectHandle = handles[1];
            result = TPMI_DH_PERSISTENT_Unmarshal(&in->persistentHandle, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EvictControl_persistentHandle;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_EvictControl action routine
            result = TPM2_EvictControl(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_EvictControl == YES
#if defined CC_ReadClock && CC_ReadClock == YES
        case TPM_CC_ReadClock:
        {
            // Buffer for output parameters
            ReadClock_Out *out = 
                (ReadClock_Out *) MemoryGetActionOutputBuffer(sizeof(ReadClock_Out));

            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ReadClock action routine
            result = TPM2_ReadClock(out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ReadClock_Out);
            *respParmSize += TPMS_TIME_INFO_Marshal(&out->currentTime, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_ReadClock == YES
#if defined CC_ClockSet && CC_ClockSet == YES
        case TPM_CC_ClockSet:
        {
            // Buffer for input parameters
            ClockSet_In *in = 
                (ClockSet_In *) MemoryGetActionInputBuffer(sizeof(ClockSet_In));
            in->auth = handles[0];
            result = UINT64_Unmarshal(&in->newTime, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClockSet_newTime;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ClockSet action routine
            result = TPM2_ClockSet(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClockSet == YES
#if defined CC_ClockRateAdjust && CC_ClockRateAdjust == YES
        case TPM_CC_ClockRateAdjust:
        {
            // Buffer for input parameters
            ClockRateAdjust_In *in = 
                (ClockRateAdjust_In *) MemoryGetActionInputBuffer(sizeof(ClockRateAdjust_In));
            in->auth = handles[0];
            result = TPM_CLOCK_ADJUST_Unmarshal(&in->rateAdjust, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClockRateAdjust_rateAdjust;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_ClockRateAdjust action routine
            result = TPM2_ClockRateAdjust(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClockRateAdjust == YES
#if defined CC_GetCapability && CC_GetCapability == YES
        case TPM_CC_GetCapability:
        {
            // Buffer for input parameters
            GetCapability_In *in = 
                (GetCapability_In *) MemoryGetActionInputBuffer(sizeof(GetCapability_In));
            // Buffer for output parameters
            GetCapability_Out *out = 
                (GetCapability_Out *) MemoryGetActionOutputBuffer(sizeof(GetCapability_Out));

            result = TPM_CAP_Unmarshal(&in->capability, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_capability;
            result = UINT32_Unmarshal(&in->property, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_property;
            result = UINT32_Unmarshal(&in->propertyCount, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_propertyCount;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_GetCapability action routine
            result = TPM2_GetCapability(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetCapability_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->moreData, &responseBuffer, &rSize);
            *respParmSize += TPMS_CAPABILITY_DATA_Marshal(&out->capabilityData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetCapability == YES
#if defined CC_TestParms && CC_TestParms == YES
        case TPM_CC_TestParms:
        {
            // Buffer for input parameters
            TestParms_In *in = 
                (TestParms_In *) MemoryGetActionInputBuffer(sizeof(TestParms_In));
            result = TPMT_PUBLIC_PARMS_Unmarshal(&in->parameters, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_TestParms_parameters;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_TestParms action routine
            result = TPM2_TestParms(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_TestParms == YES
#if defined CC_NV_DefineSpace && CC_NV_DefineSpace == YES
        case TPM_CC_NV_DefineSpace:
        {
            // Buffer for input parameters
            NV_DefineSpace_In *in = 
                (NV_DefineSpace_In *) MemoryGetActionInputBuffer(sizeof(NV_DefineSpace_In));
            in->authHandle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_DefineSpace_auth;
            result = TPM2B_NV_PUBLIC_Unmarshal(&in->publicInfo, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_DefineSpace_publicInfo;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_DefineSpace action routine
            result = TPM2_NV_DefineSpace(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_DefineSpace == YES
#if defined CC_NV_UndefineSpace && CC_NV_UndefineSpace == YES
        case TPM_CC_NV_UndefineSpace:
        {
            // Buffer for input parameters
            NV_UndefineSpace_In *in = 
                (NV_UndefineSpace_In *) MemoryGetActionInputBuffer(sizeof(NV_UndefineSpace_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_UndefineSpace action routine
            result = TPM2_NV_UndefineSpace(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_UndefineSpace == YES
#if defined CC_NV_UndefineSpaceSpecial && CC_NV_UndefineSpaceSpecial == YES
        case TPM_CC_NV_UndefineSpaceSpecial:
        {
            // Buffer for input parameters
            NV_UndefineSpaceSpecial_In *in = 
                (NV_UndefineSpaceSpecial_In *) MemoryGetActionInputBuffer(sizeof(NV_UndefineSpaceSpecial_In));
            in->nvIndex = handles[0];
            in->platform = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_UndefineSpaceSpecial action routine
            result = TPM2_NV_UndefineSpaceSpecial(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_UndefineSpaceSpecial == YES
#if defined CC_NV_ReadPublic && CC_NV_ReadPublic == YES
        case TPM_CC_NV_ReadPublic:
        {
            // Buffer for input parameters
            NV_ReadPublic_In *in = 
                (NV_ReadPublic_In *) MemoryGetActionInputBuffer(sizeof(NV_ReadPublic_In));
            // Buffer for output parameters
            NV_ReadPublic_Out *out = 
                (NV_ReadPublic_Out *) MemoryGetActionOutputBuffer(sizeof(NV_ReadPublic_Out));

            in->nvIndex = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_ReadPublic action routine
            result = TPM2_NV_ReadPublic(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_ReadPublic_Out);
            *respParmSize += TPM2B_NV_PUBLIC_Marshal(&out->nvPublic, &responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->nvName, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_ReadPublic == YES
#if defined CC_NV_Write && CC_NV_Write == YES
        case TPM_CC_NV_Write:
        {
            // Buffer for input parameters
            NV_Write_In *in = 
                (NV_Write_In *) MemoryGetActionInputBuffer(sizeof(NV_Write_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = TPM2B_MAX_NV_BUFFER_Unmarshal(&in->data, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Write_data;
            result = UINT16_Unmarshal(&in->offset, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Write_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_Write action routine
            result = TPM2_NV_Write(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Write == YES
#if defined CC_NV_Increment && CC_NV_Increment == YES
        case TPM_CC_NV_Increment:
        {
            // Buffer for input parameters
            NV_Increment_In *in = 
                (NV_Increment_In *) MemoryGetActionInputBuffer(sizeof(NV_Increment_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_Increment action routine
            result = TPM2_NV_Increment(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Increment == YES
#if defined CC_NV_Extend && CC_NV_Extend == YES
        case TPM_CC_NV_Extend:
        {
            // Buffer for input parameters
            NV_Extend_In *in = 
                (NV_Extend_In *) MemoryGetActionInputBuffer(sizeof(NV_Extend_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = TPM2B_MAX_NV_BUFFER_Unmarshal(&in->data, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Extend_data;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_Extend action routine
            result = TPM2_NV_Extend(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Extend == YES
#if defined CC_NV_SetBits && CC_NV_SetBits == YES
        case TPM_CC_NV_SetBits:
        {
            // Buffer for input parameters
            NV_SetBits_In *in = 
                (NV_SetBits_In *) MemoryGetActionInputBuffer(sizeof(NV_SetBits_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = UINT64_Unmarshal(&in->bits, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_SetBits_bits;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_SetBits action routine
            result = TPM2_NV_SetBits(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_SetBits == YES
#if defined CC_NV_WriteLock && CC_NV_WriteLock == YES
        case TPM_CC_NV_WriteLock:
        {
            // Buffer for input parameters
            NV_WriteLock_In *in = 
                (NV_WriteLock_In *) MemoryGetActionInputBuffer(sizeof(NV_WriteLock_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_WriteLock action routine
            result = TPM2_NV_WriteLock(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_WriteLock == YES
#if defined CC_NV_GlobalWriteLock && CC_NV_GlobalWriteLock == YES
        case TPM_CC_NV_GlobalWriteLock:
        {
            // Buffer for input parameters
            NV_GlobalWriteLock_In *in = 
                (NV_GlobalWriteLock_In *) MemoryGetActionInputBuffer(sizeof(NV_GlobalWriteLock_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_GlobalWriteLock action routine
            result = TPM2_NV_GlobalWriteLock(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_GlobalWriteLock == YES
#if defined CC_NV_Read && CC_NV_Read == YES
        case TPM_CC_NV_Read:
        {
            // Buffer for input parameters
            NV_Read_In *in = 
                (NV_Read_In *) MemoryGetActionInputBuffer(sizeof(NV_Read_In));
            // Buffer for output parameters
            NV_Read_Out *out = 
                (NV_Read_Out *) MemoryGetActionOutputBuffer(sizeof(NV_Read_Out));

            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = UINT16_Unmarshal(&in->size, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Read_size;
            result = UINT16_Unmarshal(&in->offset, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Read_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_Read action routine
            result = TPM2_NV_Read(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_Read_Out);
            *respParmSize += TPM2B_MAX_NV_BUFFER_Marshal(&out->data, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_Read == YES
#if defined CC_NV_ReadLock && CC_NV_ReadLock == YES
        case TPM_CC_NV_ReadLock:
        {
            // Buffer for input parameters
            NV_ReadLock_In *in = 
                (NV_ReadLock_In *) MemoryGetActionInputBuffer(sizeof(NV_ReadLock_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_ReadLock action routine
            result = TPM2_NV_ReadLock(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_ReadLock == YES
#if defined CC_NV_ChangeAuth && CC_NV_ChangeAuth == YES
        case TPM_CC_NV_ChangeAuth:
        {
            // Buffer for input parameters
            NV_ChangeAuth_In *in = 
                (NV_ChangeAuth_In *) MemoryGetActionInputBuffer(sizeof(NV_ChangeAuth_In));
            in->nvIndex = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_ChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_ChangeAuth action routine
            result = TPM2_NV_ChangeAuth(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_ChangeAuth == YES
#if defined CC_NV_Certify && CC_NV_Certify == YES
        case TPM_CC_NV_Certify:
        {
            // Buffer for input parameters
            NV_Certify_In *in = 
                (NV_Certify_In *) MemoryGetActionInputBuffer(sizeof(NV_Certify_In));
            // Buffer for output parameters
            NV_Certify_Out *out = 
                (NV_Certify_Out *) MemoryGetActionOutputBuffer(sizeof(NV_Certify_Out));

            in->signHandle = handles[0];
            in->authHandle = handles[1];
            in->nvIndex = handles[2];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, &parm_buffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_inScheme;
            result = UINT16_Unmarshal(&in->size, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_size;
            result = UINT16_Unmarshal(&in->offset, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_NV_Certify action routine
            result = TPM2_NV_Certify(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_Certify_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, &responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_Certify == YES
#if defined CC_AC_GetCapability && CC_AC_GetCapability == YES
        case TPM_CC_AC_GetCapability:
        {
            // Buffer for input parameters
            AC_GetCapability_In *in = 
                (AC_GetCapability_In *) MemoryGetActionInputBuffer(sizeof(AC_GetCapability_In));
            // Buffer for output parameters
            AC_GetCapability_Out *out = 
                (AC_GetCapability_Out *) MemoryGetActionOutputBuffer(sizeof(AC_GetCapability_Out));

            in->ac = handles[0];
            result = TPM_AT_Unmarshal(&in->capability, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_GetCapability_capability;
            result = UINT32_Unmarshal(&in->count, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_GetCapability_count;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_AC_GetCapability action routine
            result = TPM2_AC_GetCapability(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(AC_GetCapability_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->moreData, &responseBuffer, &rSize);
            *respParmSize += TPML_AC_CAPABILITIES_Marshal(&out->capabilitiesData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_AC_GetCapability == YES
#if defined CC_AC_Send && CC_AC_Send == YES
        case TPM_CC_AC_Send:
        {
            // Buffer for input parameters
            AC_Send_In *in = 
                (AC_Send_In *) MemoryGetActionInputBuffer(sizeof(AC_Send_In));
            // Buffer for output parameters
            AC_Send_Out *out = 
                (AC_Send_Out *) MemoryGetActionOutputBuffer(sizeof(AC_Send_Out));

            in->sendObject = handles[0];
            in->authHandle = handles[1];
            in->ac = handles[2];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->acDataIn, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_Send_acDataIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_AC_Send action routine
            result = TPM2_AC_Send(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(AC_Send_Out);
            *respParmSize += TPMS_AC_OUTPUT_Marshal(&out->acDataOut, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_AC_Send == YES
#if defined CC_Policy_AC_SendSelect && CC_Policy_AC_SendSelect == YES
        case TPM_CC_Policy_AC_SendSelect:
        {
            // Buffer for input parameters
            Policy_AC_SendSelect_In *in = 
                (Policy_AC_SendSelect_In *) MemoryGetActionInputBuffer(sizeof(Policy_AC_SendSelect_In));
            in->policySession = handles[0];
            result = TPM2B_NAME_Unmarshal(&in->objectName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_objectName;
            result = TPM2B_NAME_Unmarshal(&in->authHandleName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_authHandleName;
            result = TPM2B_NAME_Unmarshal(&in->acName, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_acName;
            result = TPMI_YES_NO_Unmarshal(&in->includeObject, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_includeObject;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Policy_AC_SendSelect action routine
            result = TPM2_Policy_AC_SendSelect(in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Policy_AC_SendSelect == YES
#if defined CC_Vendor_TCG_Test && CC_Vendor_TCG_Test == YES
        case TPM_CC_Vendor_TCG_Test:
        {
            // Buffer for input parameters
            Vendor_TCG_Test_In *in = 
                (Vendor_TCG_Test_In *) MemoryGetActionInputBuffer(sizeof(Vendor_TCG_Test_In));
            // Buffer for output parameters
            Vendor_TCG_Test_Out *out = 
                (Vendor_TCG_Test_Out *) MemoryGetActionOutputBuffer(sizeof(Vendor_TCG_Test_Out));

            result = TPM2B_DATA_Unmarshal(&in->inputData, &parm_buffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Vendor_TCG_Test_inputData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;

            // TPM2_Vendor_TCG_Test action routine
            result = TPM2_Vendor_TCG_Test(in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Vendor_TCG_Test_Out);
            *respParmSize += TPM2B_DATA_Marshal(&out->outputData, &responseBuffer, &rSize);
        }
        break;
#endif     // CC_Vendor_TCG_Test == YES
