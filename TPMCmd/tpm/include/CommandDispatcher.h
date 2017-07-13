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
/*(Auto)
 *  Created by TpmDispatch; Version 4.0 July 8,2017
 *  Date: Jul  9, 2017  Time: 12:33:32AM
 */
#if CC_Startup
        case TPM_CC_Startup:
        {
            // Buffer for input parameters
            Startup_In *in = (Startup_In *) 
                         MemoryGetInBuffer(sizeof(Startup_In));
            result = TPM_SU_Unmarshal(&in->startupType, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Startup_startupType;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Startup action routine
            result = TPM2_Startup (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Startup 
#if CC_Shutdown
        case TPM_CC_Shutdown:
        {
            // Buffer for input parameters
            Shutdown_In *in = (Shutdown_In *) 
                         MemoryGetInBuffer(sizeof(Shutdown_In));
            result = TPM_SU_Unmarshal(&in->shutdownType, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Shutdown_shutdownType;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Shutdown action routine
            result = TPM2_Shutdown (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Shutdown 
#if CC_SelfTest
        case TPM_CC_SelfTest:
        {
            // Buffer for input parameters
            SelfTest_In *in = (SelfTest_In *) 
                         MemoryGetInBuffer(sizeof(SelfTest_In));
            result = TPMI_YES_NO_Unmarshal(&in->fullTest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SelfTest_fullTest;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SelfTest action routine
            result = TPM2_SelfTest (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SelfTest 
#if CC_IncrementalSelfTest
        case TPM_CC_IncrementalSelfTest:
        {
            // Buffer for input parameters
            IncrementalSelfTest_In *in = (IncrementalSelfTest_In *) 
                         MemoryGetInBuffer(sizeof(IncrementalSelfTest_In));
            // Buffer for output parameters
            IncrementalSelfTest_Out *out = (IncrementalSelfTest_Out *) 
                        MemoryGetOutBuffer(sizeof(IncrementalSelfTest_Out));

            result = TPML_ALG_Unmarshal(&in->toTest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_IncrementalSelfTest_toTest;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_IncrementalSelfTest action routine
            result = TPM2_IncrementalSelfTest (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(IncrementalSelfTest_Out);
            *respParmSize += TPML_ALG_Marshal(&out->toDoList, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_IncrementalSelfTest 
#if CC_GetTestResult
        case TPM_CC_GetTestResult:
        {
            // Buffer for output parameters
            GetTestResult_Out *out = (GetTestResult_Out *) 
                        MemoryGetOutBuffer(sizeof(GetTestResult_Out));

            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetTestResult action routine
            result = TPM2_GetTestResult (out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetTestResult_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM_RC_Marshal(&out->testResult, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetTestResult 
#if CC_StartAuthSession
        case TPM_CC_StartAuthSession:
        {
            // Buffer for input parameters
            StartAuthSession_In *in = (StartAuthSession_In *) 
                         MemoryGetInBuffer(sizeof(StartAuthSession_In));
            // Buffer for output parameters
            StartAuthSession_Out *out = (StartAuthSession_Out *) 
                        MemoryGetOutBuffer(sizeof(StartAuthSession_Out));

            in->tpmKey = handles[0];
            in->bind = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceCaller, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_nonceCaller;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->encryptedSalt, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_encryptedSalt;
            result = TPM_SE_Unmarshal(&in->sessionType, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_sessionType;
            result = TPMT_SYM_DEF_Unmarshal(&in->symmetric, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_symmetric;
            result = TPMI_ALG_HASH_Unmarshal(&in->authHash, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StartAuthSession_authHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_StartAuthSession action routine
            result = TPM2_StartAuthSession (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(StartAuthSession_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->sessionHandle;
            *respParmSize += TPM2B_NONCE_Marshal(&out->nonceTPM, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_StartAuthSession 
#if CC_PolicyRestart
        case TPM_CC_PolicyRestart:
        {
            // Buffer for input parameters
            PolicyRestart_In *in = (PolicyRestart_In *) 
                         MemoryGetInBuffer(sizeof(PolicyRestart_In));
            in->sessionHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyRestart action routine
            result = TPM2_PolicyRestart (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyRestart 
#if CC_Create
        case TPM_CC_Create:
        {
            // Buffer for input parameters
            Create_In *in = (Create_In *) 
                         MemoryGetInBuffer(sizeof(Create_In));
            // Buffer for output parameters
            Create_Out *out = (Create_Out *) 
                        MemoryGetOutBuffer(sizeof(Create_Out));

            in->parentHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_inSensitive;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_inPublic;
            result = TPM2B_DATA_Unmarshal(&in->outsideInfo, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_outsideInfo;
            result = TPML_PCR_SELECTION_Unmarshal(&in->creationPCR, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Create_creationPCR;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Create action routine
            result = TPM2_Create (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Create_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_CREATION_DATA_Marshal(&out->creationData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->creationHash, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_CREATION_Marshal(&out->creationTicket, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Create 
#if CC_Load
        case TPM_CC_Load:
        {
            // Buffer for input parameters
            Load_In *in = (Load_In *) 
                         MemoryGetInBuffer(sizeof(Load_In));
            // Buffer for output parameters
            Load_Out *out = (Load_Out *) 
                        MemoryGetOutBuffer(sizeof(Load_Out));

            in->parentHandle = handles[0];
            result = TPM2B_PRIVATE_Unmarshal(&in->inPrivate, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Load_inPrivate;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Load_inPublic;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Load action routine
            result = TPM2_Load (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Load_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->objectHandle;
            *respParmSize += TPM2B_NAME_Marshal(&out->name, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Load 
#if CC_LoadExternal
        case TPM_CC_LoadExternal:
        {
            // Buffer for input parameters
            LoadExternal_In *in = (LoadExternal_In *) 
                         MemoryGetInBuffer(sizeof(LoadExternal_In));
            // Buffer for output parameters
            LoadExternal_Out *out = (LoadExternal_Out *) 
                        MemoryGetOutBuffer(sizeof(LoadExternal_Out));

            result = TPM2B_SENSITIVE_Unmarshal(&in->inPrivate, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_inPrivate;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_inPublic;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_LoadExternal_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_LoadExternal action routine
            result = TPM2_LoadExternal (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(LoadExternal_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->objectHandle;
            *respParmSize += TPM2B_NAME_Marshal(&out->name, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_LoadExternal 
#if CC_ReadPublic
        case TPM_CC_ReadPublic:
        {
            // Buffer for input parameters
            ReadPublic_In *in = (ReadPublic_In *) 
                         MemoryGetInBuffer(sizeof(ReadPublic_In));
            // Buffer for output parameters
            ReadPublic_Out *out = (ReadPublic_Out *) 
                        MemoryGetOutBuffer(sizeof(ReadPublic_Out));

            in->objectHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ReadPublic action routine
            result = TPM2_ReadPublic (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ReadPublic_Out);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->qualifiedName, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ReadPublic 
#if CC_ActivateCredential
        case TPM_CC_ActivateCredential:
        {
            // Buffer for input parameters
            ActivateCredential_In *in = (ActivateCredential_In *) 
                         MemoryGetInBuffer(sizeof(ActivateCredential_In));
            // Buffer for output parameters
            ActivateCredential_Out *out = (ActivateCredential_Out *) 
                        MemoryGetOutBuffer(sizeof(ActivateCredential_Out));

            in->activateHandle = handles[0];
            in->keyHandle = handles[1];
            result = TPM2B_ID_OBJECT_Unmarshal(&in->credentialBlob, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ActivateCredential_credentialBlob;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->secret, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ActivateCredential_secret;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ActivateCredential action routine
            result = TPM2_ActivateCredential (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ActivateCredential_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->certInfo, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ActivateCredential 
#if CC_MakeCredential
        case TPM_CC_MakeCredential:
        {
            // Buffer for input parameters
            MakeCredential_In *in = (MakeCredential_In *) 
                         MemoryGetInBuffer(sizeof(MakeCredential_In));
            // Buffer for output parameters
            MakeCredential_Out *out = (MakeCredential_Out *) 
                        MemoryGetOutBuffer(sizeof(MakeCredential_Out));

            in->handle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->credential, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MakeCredential_credential;
            result = TPM2B_NAME_Unmarshal(&in->objectName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MakeCredential_objectName;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_MakeCredential action routine
            result = TPM2_MakeCredential (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MakeCredential_Out);
            *respParmSize += TPM2B_ID_OBJECT_Marshal(&out->credentialBlob, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->secret, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_MakeCredential 
#if CC_Unseal
        case TPM_CC_Unseal:
        {
            // Buffer for input parameters
            Unseal_In *in = (Unseal_In *) 
                         MemoryGetInBuffer(sizeof(Unseal_In));
            // Buffer for output parameters
            Unseal_Out *out = (Unseal_Out *) 
                        MemoryGetOutBuffer(sizeof(Unseal_Out));

            in->itemHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Unseal action routine
            result = TPM2_Unseal (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Unseal_Out);
            *respParmSize += TPM2B_SENSITIVE_DATA_Marshal(&out->outData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Unseal 
#if CC_ObjectChangeAuth
        case TPM_CC_ObjectChangeAuth:
        {
            // Buffer for input parameters
            ObjectChangeAuth_In *in = (ObjectChangeAuth_In *) 
                         MemoryGetInBuffer(sizeof(ObjectChangeAuth_In));
            // Buffer for output parameters
            ObjectChangeAuth_Out *out = (ObjectChangeAuth_Out *) 
                        MemoryGetOutBuffer(sizeof(ObjectChangeAuth_Out));

            in->objectHandle = handles[0];
            in->parentHandle = handles[1];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ObjectChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ObjectChangeAuth action routine
            result = TPM2_ObjectChangeAuth (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ObjectChangeAuth_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ObjectChangeAuth 
#if CC_CreateLoaded
        case TPM_CC_CreateLoaded:
        {
            // Buffer for input parameters
            CreateLoaded_In *in = (CreateLoaded_In *) 
                         MemoryGetInBuffer(sizeof(CreateLoaded_In));
            // Buffer for output parameters
            CreateLoaded_Out *out = (CreateLoaded_Out *) 
                        MemoryGetOutBuffer(sizeof(CreateLoaded_Out));

            in->parentHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreateLoaded_inSensitive;
            result = TPM2B_TEMPLATE_Unmarshal(&in->inPublic, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreateLoaded_inPublic;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_CreateLoaded action routine
            result = TPM2_CreateLoaded (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CreateLoaded_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->objectHandle;
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_CreateLoaded 
#if CC_Duplicate
        case TPM_CC_Duplicate:
        {
            // Buffer for input parameters
            Duplicate_In *in = (Duplicate_In *) 
                         MemoryGetInBuffer(sizeof(Duplicate_In));
            // Buffer for output parameters
            Duplicate_Out *out = (Duplicate_Out *) 
                        MemoryGetOutBuffer(sizeof(Duplicate_Out));

            in->objectHandle = handles[0];
            in->newParentHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->encryptionKeyIn, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Duplicate_encryptionKeyIn;
            result = TPMT_SYM_DEF_OBJECT_Unmarshal(&in->symmetricAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Duplicate_symmetricAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Duplicate action routine
            result = TPM2_Duplicate (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Duplicate_Out);
            *respParmSize += TPM2B_DATA_Marshal(&out->encryptionKeyOut, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->duplicate, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->outSymSeed, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Duplicate 
#if CC_Rewrap
        case TPM_CC_Rewrap:
        {
            // Buffer for input parameters
            Rewrap_In *in = (Rewrap_In *) 
                         MemoryGetInBuffer(sizeof(Rewrap_In));
            // Buffer for output parameters
            Rewrap_Out *out = (Rewrap_Out *) 
                        MemoryGetOutBuffer(sizeof(Rewrap_Out));

            in->oldParent = handles[0];
            in->newParent = handles[1];
            result = TPM2B_PRIVATE_Unmarshal(&in->inDuplicate, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_inDuplicate;
            result = TPM2B_NAME_Unmarshal(&in->name, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_name;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->inSymSeed, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Rewrap_inSymSeed;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Rewrap action routine
            result = TPM2_Rewrap (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Rewrap_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outDuplicate, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ENCRYPTED_SECRET_Marshal(&out->outSymSeed, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Rewrap 
#if CC_Import
        case TPM_CC_Import:
        {
            // Buffer for input parameters
            Import_In *in = (Import_In *) 
                         MemoryGetInBuffer(sizeof(Import_In));
            // Buffer for output parameters
            Import_Out *out = (Import_Out *) 
                        MemoryGetOutBuffer(sizeof(Import_Out));

            in->parentHandle = handles[0];
            result = TPM2B_DATA_Unmarshal(&in->encryptionKey, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_encryptionKey;
            result = TPM2B_PUBLIC_Unmarshal(&in->objectPublic, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_objectPublic;
            result = TPM2B_PRIVATE_Unmarshal(&in->duplicate, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_duplicate;
            result = TPM2B_ENCRYPTED_SECRET_Unmarshal(&in->inSymSeed, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_inSymSeed;
            result = TPMT_SYM_DEF_OBJECT_Unmarshal(&in->symmetricAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Import_symmetricAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Import action routine
            result = TPM2_Import (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Import_Out);
            *respParmSize += TPM2B_PRIVATE_Marshal(&out->outPrivate, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Import 
#if CC_RSA_Encrypt
        case TPM_CC_RSA_Encrypt:
        {
            // Buffer for input parameters
            RSA_Encrypt_In *in = (RSA_Encrypt_In *) 
                         MemoryGetInBuffer(sizeof(RSA_Encrypt_In));
            // Buffer for output parameters
            RSA_Encrypt_Out *out = (RSA_Encrypt_Out *) 
                        MemoryGetOutBuffer(sizeof(RSA_Encrypt_Out));

            in->keyHandle = handles[0];
            result = TPM2B_PUBLIC_KEY_RSA_Unmarshal(&in->message, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_message;
            result = TPMT_RSA_DECRYPT_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_inScheme;
            result = TPM2B_DATA_Unmarshal(&in->label, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Encrypt_label;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_RSA_Encrypt action routine
            result = TPM2_RSA_Encrypt (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(RSA_Encrypt_Out);
            *respParmSize += TPM2B_PUBLIC_KEY_RSA_Marshal(&out->outData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_RSA_Encrypt 
#if CC_RSA_Decrypt
        case TPM_CC_RSA_Decrypt:
        {
            // Buffer for input parameters
            RSA_Decrypt_In *in = (RSA_Decrypt_In *) 
                         MemoryGetInBuffer(sizeof(RSA_Decrypt_In));
            // Buffer for output parameters
            RSA_Decrypt_Out *out = (RSA_Decrypt_Out *) 
                        MemoryGetOutBuffer(sizeof(RSA_Decrypt_Out));

            in->keyHandle = handles[0];
            result = TPM2B_PUBLIC_KEY_RSA_Unmarshal(&in->cipherText, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_cipherText;
            result = TPMT_RSA_DECRYPT_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_inScheme;
            result = TPM2B_DATA_Unmarshal(&in->label, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_RSA_Decrypt_label;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_RSA_Decrypt action routine
            result = TPM2_RSA_Decrypt (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(RSA_Decrypt_Out);
            *respParmSize += TPM2B_PUBLIC_KEY_RSA_Marshal(&out->message, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_RSA_Decrypt 
#if CC_ECDH_KeyGen
        case TPM_CC_ECDH_KeyGen:
        {
            // Buffer for input parameters
            ECDH_KeyGen_In *in = (ECDH_KeyGen_In *) 
                         MemoryGetInBuffer(sizeof(ECDH_KeyGen_In));
            // Buffer for output parameters
            ECDH_KeyGen_Out *out = (ECDH_KeyGen_Out *) 
                        MemoryGetOutBuffer(sizeof(ECDH_KeyGen_Out));

            in->keyHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ECDH_KeyGen action routine
            result = TPM2_ECDH_KeyGen (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECDH_KeyGen_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->zPoint, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->pubPoint, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECDH_KeyGen 
#if CC_ECDH_ZGen
        case TPM_CC_ECDH_ZGen:
        {
            // Buffer for input parameters
            ECDH_ZGen_In *in = (ECDH_ZGen_In *) 
                         MemoryGetInBuffer(sizeof(ECDH_ZGen_In));
            // Buffer for output parameters
            ECDH_ZGen_Out *out = (ECDH_ZGen_Out *) 
                        MemoryGetOutBuffer(sizeof(ECDH_ZGen_Out));

            in->keyHandle = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->inPoint, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ECDH_ZGen_inPoint;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ECDH_ZGen action routine
            result = TPM2_ECDH_ZGen (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECDH_ZGen_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outPoint, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECDH_ZGen 
#if CC_ECC_Parameters
        case TPM_CC_ECC_Parameters:
        {
            // Buffer for input parameters
            ECC_Parameters_In *in = (ECC_Parameters_In *) 
                         MemoryGetInBuffer(sizeof(ECC_Parameters_In));
            // Buffer for output parameters
            ECC_Parameters_Out *out = (ECC_Parameters_Out *) 
                        MemoryGetOutBuffer(sizeof(ECC_Parameters_Out));

            result = TPMI_ECC_CURVE_Unmarshal(&in->curveID, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ECC_Parameters_curveID;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ECC_Parameters action routine
            result = TPM2_ECC_Parameters (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ECC_Parameters_Out);
            *respParmSize += TPMS_ALGORITHM_DETAIL_ECC_Marshal(&out->parameters, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ECC_Parameters 
#if CC_ZGen_2Phase
        case TPM_CC_ZGen_2Phase:
        {
            // Buffer for input parameters
            ZGen_2Phase_In *in = (ZGen_2Phase_In *) 
                         MemoryGetInBuffer(sizeof(ZGen_2Phase_In));
            // Buffer for output parameters
            ZGen_2Phase_Out *out = (ZGen_2Phase_Out *) 
                        MemoryGetOutBuffer(sizeof(ZGen_2Phase_Out));

            in->keyA = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->inQsB, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inQsB;
            result = TPM2B_ECC_POINT_Unmarshal(&in->inQeB, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inQeB;
            result = TPMI_ECC_KEY_EXCHANGE_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_inScheme;
            result = UINT16_Unmarshal(&in->counter, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ZGen_2Phase_counter;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ZGen_2Phase action routine
            result = TPM2_ZGen_2Phase (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ZGen_2Phase_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outZ1, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->outZ2, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ZGen_2Phase 
#if CC_EncryptDecrypt
        case TPM_CC_EncryptDecrypt:
        {
            // Buffer for input parameters
            EncryptDecrypt_In *in = (EncryptDecrypt_In *) 
                         MemoryGetInBuffer(sizeof(EncryptDecrypt_In));
            // Buffer for output parameters
            EncryptDecrypt_Out *out = (EncryptDecrypt_Out *) 
                        MemoryGetOutBuffer(sizeof(EncryptDecrypt_Out));

            in->keyHandle = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->decrypt, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_decrypt;
            result = TPMI_ALG_CIPHER_MODE_Unmarshal(&in->mode, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_mode;
            result = TPM2B_IV_Unmarshal(&in->ivIn, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_ivIn;
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->inData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt_inData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_EncryptDecrypt action routine
            result = TPM2_EncryptDecrypt (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EncryptDecrypt_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_IV_Marshal(&out->ivOut, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_EncryptDecrypt 
#if CC_EncryptDecrypt2
        case TPM_CC_EncryptDecrypt2:
        {
            // Buffer for input parameters
            EncryptDecrypt2_In *in = (EncryptDecrypt2_In *) 
                         MemoryGetInBuffer(sizeof(EncryptDecrypt2_In));
            // Buffer for output parameters
            EncryptDecrypt2_Out *out = (EncryptDecrypt2_Out *) 
                        MemoryGetOutBuffer(sizeof(EncryptDecrypt2_Out));

            in->keyHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->inData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_inData;
            result = TPMI_YES_NO_Unmarshal(&in->decrypt, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_decrypt;
            result = TPMI_ALG_CIPHER_MODE_Unmarshal(&in->mode, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_mode;
            result = TPM2B_IV_Unmarshal(&in->ivIn, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EncryptDecrypt2_ivIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_EncryptDecrypt2 action routine
            result = TPM2_EncryptDecrypt2 (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EncryptDecrypt2_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->outData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_IV_Marshal(&out->ivOut, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_EncryptDecrypt2 
#if CC_Hash
        case TPM_CC_Hash:
        {
            // Buffer for input parameters
            Hash_In *in = (Hash_In *) 
                         MemoryGetInBuffer(sizeof(Hash_In));
            // Buffer for output parameters
            Hash_Out *out = (Hash_Out *) 
                        MemoryGetOutBuffer(sizeof(Hash_Out));

            result = TPM2B_MAX_BUFFER_Unmarshal(&in->data, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_data;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_hashAlg;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Hash_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Hash action routine
            result = TPM2_Hash (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Hash_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outHash, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_HASHCHECK_Marshal(&out->validation, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Hash 
#if CC_HMAC
        case TPM_CC_HMAC:
        {
            // Buffer for input parameters
            HMAC_In *in = (HMAC_In *) 
                         MemoryGetInBuffer(sizeof(HMAC_In));
            // Buffer for output parameters
            HMAC_Out *out = (HMAC_Out *) 
                        MemoryGetOutBuffer(sizeof(HMAC_Out));

            in->handle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_buffer;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_HMAC action routine
            result = TPM2_HMAC (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HMAC_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outHMAC, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_HMAC 
#if CC_MAC
        case TPM_CC_MAC:
        {
            // Buffer for input parameters
            MAC_In *in = (MAC_In *) 
                         MemoryGetInBuffer(sizeof(MAC_In));
            // Buffer for output parameters
            MAC_Out *out = (MAC_Out *) 
                        MemoryGetOutBuffer(sizeof(MAC_Out));

            in->handle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_buffer;
            result = TPMI_ALG_MAC_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_MAC action routine
            result = TPM2_MAC (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MAC_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->outMAC, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_MAC 
#if CC_GetRandom
        case TPM_CC_GetRandom:
        {
            // Buffer for input parameters
            GetRandom_In *in = (GetRandom_In *) 
                         MemoryGetInBuffer(sizeof(GetRandom_In));
            // Buffer for output parameters
            GetRandom_Out *out = (GetRandom_Out *) 
                        MemoryGetOutBuffer(sizeof(GetRandom_Out));

            result = UINT16_Unmarshal(&in->bytesRequested, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetRandom_bytesRequested;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetRandom action routine
            result = TPM2_GetRandom (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetRandom_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->randomBytes, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetRandom 
#if CC_StirRandom
        case TPM_CC_StirRandom:
        {
            // Buffer for input parameters
            StirRandom_In *in = (StirRandom_In *) 
                         MemoryGetInBuffer(sizeof(StirRandom_In));
            result = TPM2B_SENSITIVE_DATA_Unmarshal(&in->inData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_StirRandom_inData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_StirRandom action routine
            result = TPM2_StirRandom (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_StirRandom 
#if CC_HMAC_Start
        case TPM_CC_HMAC_Start:
        {
            // Buffer for input parameters
            HMAC_Start_In *in = (HMAC_Start_In *) 
                         MemoryGetInBuffer(sizeof(HMAC_Start_In));
            // Buffer for output parameters
            HMAC_Start_Out *out = (HMAC_Start_Out *) 
                        MemoryGetOutBuffer(sizeof(HMAC_Start_Out));

            in->handle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_Start_auth;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HMAC_Start_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_HMAC_Start action routine
            result = TPM2_HMAC_Start (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HMAC_Start_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->sequenceHandle;
        }
        break;
#endif     // CC_HMAC_Start 
#if CC_MAC_Start
        case TPM_CC_MAC_Start:
        {
            // Buffer for input parameters
            MAC_Start_In *in = (MAC_Start_In *) 
                         MemoryGetInBuffer(sizeof(MAC_Start_In));
            // Buffer for output parameters
            MAC_Start_Out *out = (MAC_Start_Out *) 
                        MemoryGetOutBuffer(sizeof(MAC_Start_Out));

            in->handle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_Start_auth;
            result = TPMI_ALG_MAC_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_MAC_Start_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_MAC_Start action routine
            result = TPM2_MAC_Start (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(MAC_Start_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->sequenceHandle;
        }
        break;
#endif     // CC_MAC_Start 
#if CC_HashSequenceStart
        case TPM_CC_HashSequenceStart:
        {
            // Buffer for input parameters
            HashSequenceStart_In *in = (HashSequenceStart_In *) 
                         MemoryGetInBuffer(sizeof(HashSequenceStart_In));
            // Buffer for output parameters
            HashSequenceStart_Out *out = (HashSequenceStart_Out *) 
                        MemoryGetOutBuffer(sizeof(HashSequenceStart_Out));

            result = TPM2B_AUTH_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HashSequenceStart_auth;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HashSequenceStart_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_HashSequenceStart action routine
            result = TPM2_HashSequenceStart (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(HashSequenceStart_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->sequenceHandle;
        }
        break;
#endif     // CC_HashSequenceStart 
#if CC_SequenceUpdate
        case TPM_CC_SequenceUpdate:
        {
            // Buffer for input parameters
            SequenceUpdate_In *in = (SequenceUpdate_In *) 
                         MemoryGetInBuffer(sizeof(SequenceUpdate_In));
            in->sequenceHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceUpdate_buffer;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SequenceUpdate action routine
            result = TPM2_SequenceUpdate (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SequenceUpdate 
#if CC_SequenceComplete
        case TPM_CC_SequenceComplete:
        {
            // Buffer for input parameters
            SequenceComplete_In *in = (SequenceComplete_In *) 
                         MemoryGetInBuffer(sizeof(SequenceComplete_In));
            // Buffer for output parameters
            SequenceComplete_Out *out = (SequenceComplete_Out *) 
                        MemoryGetOutBuffer(sizeof(SequenceComplete_Out));

            in->sequenceHandle = handles[0];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceComplete_buffer;
            result = TPMI_RH_HIERARCHY_Unmarshal(&in->hierarchy, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SequenceComplete_hierarchy;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SequenceComplete action routine
            result = TPM2_SequenceComplete (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(SequenceComplete_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->result, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_HASHCHECK_Marshal(&out->validation, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_SequenceComplete 
#if CC_EventSequenceComplete
        case TPM_CC_EventSequenceComplete:
        {
            // Buffer for input parameters
            EventSequenceComplete_In *in = (EventSequenceComplete_In *) 
                         MemoryGetInBuffer(sizeof(EventSequenceComplete_In));
            // Buffer for output parameters
            EventSequenceComplete_Out *out = (EventSequenceComplete_Out *) 
                        MemoryGetOutBuffer(sizeof(EventSequenceComplete_Out));

            in->pcrHandle = handles[0];
            in->sequenceHandle = handles[1];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->buffer, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EventSequenceComplete_buffer;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_EventSequenceComplete action routine
            result = TPM2_EventSequenceComplete (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EventSequenceComplete_Out);
            *respParmSize += TPML_DIGEST_VALUES_Marshal(&out->results, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_EventSequenceComplete 
#if CC_Certify
        case TPM_CC_Certify:
        {
            // Buffer for input parameters
            Certify_In *in = (Certify_In *) 
                         MemoryGetInBuffer(sizeof(Certify_In));
            // Buffer for output parameters
            Certify_Out *out = (Certify_Out *) 
                        MemoryGetOutBuffer(sizeof(Certify_Out));

            in->objectHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Certify_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Certify_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Certify action routine
            result = TPM2_Certify (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Certify_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Certify 
#if CC_CertifyCreation
        case TPM_CC_CertifyCreation:
        {
            // Buffer for input parameters
            CertifyCreation_In *in = (CertifyCreation_In *) 
                         MemoryGetInBuffer(sizeof(CertifyCreation_In));
            // Buffer for output parameters
            CertifyCreation_Out *out = (CertifyCreation_Out *) 
                        MemoryGetOutBuffer(sizeof(CertifyCreation_Out));

            in->signHandle = handles[0];
            in->objectHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_qualifyingData;
            result = TPM2B_DIGEST_Unmarshal(&in->creationHash, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_creationHash;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_inScheme;
            result = TPMT_TK_CREATION_Unmarshal(&in->creationTicket, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CertifyCreation_creationTicket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_CertifyCreation action routine
            result = TPM2_CertifyCreation (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CertifyCreation_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_CertifyCreation 
#if CC_Quote
        case TPM_CC_Quote:
        {
            // Buffer for input parameters
            Quote_In *in = (Quote_In *) 
                         MemoryGetInBuffer(sizeof(Quote_In));
            // Buffer for output parameters
            Quote_Out *out = (Quote_Out *) 
                        MemoryGetOutBuffer(sizeof(Quote_Out));

            in->signHandle = handles[0];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_inScheme;
            result = TPML_PCR_SELECTION_Unmarshal(&in->PCRselect, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Quote_PCRselect;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Quote action routine
            result = TPM2_Quote (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Quote_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->quoted, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Quote 
#if CC_GetSessionAuditDigest
        case TPM_CC_GetSessionAuditDigest:
        {
            // Buffer for input parameters
            GetSessionAuditDigest_In *in = (GetSessionAuditDigest_In *) 
                         MemoryGetInBuffer(sizeof(GetSessionAuditDigest_In));
            // Buffer for output parameters
            GetSessionAuditDigest_Out *out = (GetSessionAuditDigest_Out *) 
                        MemoryGetOutBuffer(sizeof(GetSessionAuditDigest_Out));

            in->privacyAdminHandle = handles[0];
            in->signHandle = handles[1];
            in->sessionHandle = handles[2];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetSessionAuditDigest_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetSessionAuditDigest_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetSessionAuditDigest action routine
            result = TPM2_GetSessionAuditDigest (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetSessionAuditDigest_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->auditInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetSessionAuditDigest 
#if CC_GetCommandAuditDigest
        case TPM_CC_GetCommandAuditDigest:
        {
            // Buffer for input parameters
            GetCommandAuditDigest_In *in = (GetCommandAuditDigest_In *) 
                         MemoryGetInBuffer(sizeof(GetCommandAuditDigest_In));
            // Buffer for output parameters
            GetCommandAuditDigest_Out *out = (GetCommandAuditDigest_Out *) 
                        MemoryGetOutBuffer(sizeof(GetCommandAuditDigest_Out));

            in->privacyHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCommandAuditDigest_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCommandAuditDigest_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetCommandAuditDigest action routine
            result = TPM2_GetCommandAuditDigest (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetCommandAuditDigest_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->auditInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetCommandAuditDigest 
#if CC_GetTime
        case TPM_CC_GetTime:
        {
            // Buffer for input parameters
            GetTime_In *in = (GetTime_In *) 
                         MemoryGetInBuffer(sizeof(GetTime_In));
            // Buffer for output parameters
            GetTime_Out *out = (GetTime_Out *) 
                        MemoryGetOutBuffer(sizeof(GetTime_Out));

            in->privacyAdminHandle = handles[0];
            in->signHandle = handles[1];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetTime_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetTime_inScheme;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetTime action routine
            result = TPM2_GetTime (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetTime_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->timeInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetTime 
#if CC_Commit
        case TPM_CC_Commit:
        {
            // Buffer for input parameters
            Commit_In *in = (Commit_In *) 
                         MemoryGetInBuffer(sizeof(Commit_In));
            // Buffer for output parameters
            Commit_Out *out = (Commit_Out *) 
                        MemoryGetOutBuffer(sizeof(Commit_Out));

            in->signHandle = handles[0];
            result = TPM2B_ECC_POINT_Unmarshal(&in->P1, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_P1;
            result = TPM2B_SENSITIVE_DATA_Unmarshal(&in->s2, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_s2;
            result = TPM2B_ECC_PARAMETER_Unmarshal(&in->y2, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Commit_y2;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Commit action routine
            result = TPM2_Commit (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Commit_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->K, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->L, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->E, 
                                          responseBuffer, &rSize);
            *respParmSize += UINT16_Marshal(&out->counter, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Commit 
#if CC_EC_Ephemeral
        case TPM_CC_EC_Ephemeral:
        {
            // Buffer for input parameters
            EC_Ephemeral_In *in = (EC_Ephemeral_In *) 
                         MemoryGetInBuffer(sizeof(EC_Ephemeral_In));
            // Buffer for output parameters
            EC_Ephemeral_Out *out = (EC_Ephemeral_Out *) 
                        MemoryGetOutBuffer(sizeof(EC_Ephemeral_Out));

            result = TPMI_ECC_CURVE_Unmarshal(&in->curveID, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EC_Ephemeral_curveID;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_EC_Ephemeral action routine
            result = TPM2_EC_Ephemeral (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(EC_Ephemeral_Out);
            *respParmSize += TPM2B_ECC_POINT_Marshal(&out->Q, 
                                          responseBuffer, &rSize);
            *respParmSize += UINT16_Marshal(&out->counter, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_EC_Ephemeral 
#if CC_VerifySignature
        case TPM_CC_VerifySignature:
        {
            // Buffer for input parameters
            VerifySignature_In *in = (VerifySignature_In *) 
                         MemoryGetInBuffer(sizeof(VerifySignature_In));
            // Buffer for output parameters
            VerifySignature_Out *out = (VerifySignature_Out *) 
                        MemoryGetOutBuffer(sizeof(VerifySignature_Out));

            in->keyHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->digest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_VerifySignature_digest;
            result = TPMT_SIGNATURE_Unmarshal(&in->signature, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_VerifySignature_signature;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_VerifySignature action routine
            result = TPM2_VerifySignature (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(VerifySignature_Out);
            *respParmSize += TPMT_TK_VERIFIED_Marshal(&out->validation, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_VerifySignature 
#if CC_Sign
        case TPM_CC_Sign:
        {
            // Buffer for input parameters
            Sign_In *in = (Sign_In *) 
                         MemoryGetInBuffer(sizeof(Sign_In));
            // Buffer for output parameters
            Sign_Out *out = (Sign_Out *) 
                        MemoryGetOutBuffer(sizeof(Sign_Out));

            in->keyHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->digest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_digest;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_inScheme;
            result = TPMT_TK_HASHCHECK_Unmarshal(&in->validation, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Sign_validation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Sign action routine
            result = TPM2_Sign (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Sign_Out);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Sign 
#if CC_SetCommandCodeAuditStatus
        case TPM_CC_SetCommandCodeAuditStatus:
        {
            // Buffer for input parameters
            SetCommandCodeAuditStatus_In *in = (SetCommandCodeAuditStatus_In *) 
                         MemoryGetInBuffer(sizeof(SetCommandCodeAuditStatus_In));
            in->auth = handles[0];
            result = TPMI_ALG_HASH_Unmarshal(&in->auditAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_auditAlg;
            result = TPML_CC_Unmarshal(&in->setList, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_setList;
            result = TPML_CC_Unmarshal(&in->clearList, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetCommandCodeAuditStatus_clearList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SetCommandCodeAuditStatus action routine
            result = TPM2_SetCommandCodeAuditStatus (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetCommandCodeAuditStatus 
#if CC_PCR_Extend
        case TPM_CC_PCR_Extend:
        {
            // Buffer for input parameters
            PCR_Extend_In *in = (PCR_Extend_In *) 
                         MemoryGetInBuffer(sizeof(PCR_Extend_In));
            in->pcrHandle = handles[0];
            result = TPML_DIGEST_VALUES_Unmarshal(&in->digests, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Extend_digests;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_Extend action routine
            result = TPM2_PCR_Extend (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_Extend 
#if CC_PCR_Event
        case TPM_CC_PCR_Event:
        {
            // Buffer for input parameters
            PCR_Event_In *in = (PCR_Event_In *) 
                         MemoryGetInBuffer(sizeof(PCR_Event_In));
            // Buffer for output parameters
            PCR_Event_Out *out = (PCR_Event_Out *) 
                        MemoryGetOutBuffer(sizeof(PCR_Event_Out));

            in->pcrHandle = handles[0];
            result = TPM2B_EVENT_Unmarshal(&in->eventData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Event_eventData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_Event action routine
            result = TPM2_PCR_Event (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Event_Out);
            *respParmSize += TPML_DIGEST_VALUES_Marshal(&out->digests, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Event 
#if CC_PCR_Read
        case TPM_CC_PCR_Read:
        {
            // Buffer for input parameters
            PCR_Read_In *in = (PCR_Read_In *) 
                         MemoryGetInBuffer(sizeof(PCR_Read_In));
            // Buffer for output parameters
            PCR_Read_Out *out = (PCR_Read_Out *) 
                        MemoryGetOutBuffer(sizeof(PCR_Read_Out));

            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrSelectionIn, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Read_pcrSelectionIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_Read action routine
            result = TPM2_PCR_Read (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Read_Out);
            *respParmSize += UINT32_Marshal(&out->pcrUpdateCounter, 
                                          responseBuffer, &rSize);
            *respParmSize += TPML_PCR_SELECTION_Marshal(&out->pcrSelectionOut, 
                                          responseBuffer, &rSize);
            *respParmSize += TPML_DIGEST_Marshal(&out->pcrValues, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Read 
#if CC_PCR_Allocate
        case TPM_CC_PCR_Allocate:
        {
            // Buffer for input parameters
            PCR_Allocate_In *in = (PCR_Allocate_In *) 
                         MemoryGetInBuffer(sizeof(PCR_Allocate_In));
            // Buffer for output parameters
            PCR_Allocate_Out *out = (PCR_Allocate_Out *) 
                        MemoryGetOutBuffer(sizeof(PCR_Allocate_Out));

            in->authHandle = handles[0];
            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrAllocation, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_Allocate_pcrAllocation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_Allocate action routine
            result = TPM2_PCR_Allocate (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PCR_Allocate_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->allocationSuccess, 
                                          responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->maxPCR, 
                                          responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->sizeNeeded, 
                                          responseBuffer, &rSize);
            *respParmSize += UINT32_Marshal(&out->sizeAvailable, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PCR_Allocate 
#if CC_PCR_SetAuthPolicy
        case TPM_CC_PCR_SetAuthPolicy:
        {
            // Buffer for input parameters
            PCR_SetAuthPolicy_In *in = (PCR_SetAuthPolicy_In *) 
                         MemoryGetInBuffer(sizeof(PCR_SetAuthPolicy_In));
            in->authHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->authPolicy, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_authPolicy;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_hashAlg;
            result = TPMI_DH_PCR_Unmarshal(&in->pcrNum, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthPolicy_pcrNum;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_SetAuthPolicy action routine
            result = TPM2_PCR_SetAuthPolicy (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_SetAuthPolicy 
#if CC_PCR_SetAuthValue
        case TPM_CC_PCR_SetAuthValue:
        {
            // Buffer for input parameters
            PCR_SetAuthValue_In *in = (PCR_SetAuthValue_In *) 
                         MemoryGetInBuffer(sizeof(PCR_SetAuthValue_In));
            in->pcrHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PCR_SetAuthValue_auth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_SetAuthValue action routine
            result = TPM2_PCR_SetAuthValue (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_SetAuthValue 
#if CC_PCR_Reset
        case TPM_CC_PCR_Reset:
        {
            // Buffer for input parameters
            PCR_Reset_In *in = (PCR_Reset_In *) 
                         MemoryGetInBuffer(sizeof(PCR_Reset_In));
            in->pcrHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PCR_Reset action routine
            result = TPM2_PCR_Reset (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PCR_Reset 
#if CC_PolicySigned
        case TPM_CC_PolicySigned:
        {
            // Buffer for input parameters
            PolicySigned_In *in = (PolicySigned_In *) 
                         MemoryGetInBuffer(sizeof(PolicySigned_In));
            // Buffer for output parameters
            PolicySigned_Out *out = (PolicySigned_Out *) 
                        MemoryGetOutBuffer(sizeof(PolicySigned_Out));

            in->authObject = handles[0];
            in->policySession = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceTPM, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_nonceTPM;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_policyRef;
            result = INT32_Unmarshal(&in->expiration, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_expiration;
            result = TPMT_SIGNATURE_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySigned_auth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicySigned action routine
            result = TPM2_PolicySigned (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicySigned_Out);
            *respParmSize += TPM2B_TIMEOUT_Marshal(&out->timeout, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_AUTH_Marshal(&out->policyTicket, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicySigned 
#if CC_PolicySecret
        case TPM_CC_PolicySecret:
        {
            // Buffer for input parameters
            PolicySecret_In *in = (PolicySecret_In *) 
                         MemoryGetInBuffer(sizeof(PolicySecret_In));
            // Buffer for output parameters
            PolicySecret_Out *out = (PolicySecret_Out *) 
                        MemoryGetOutBuffer(sizeof(PolicySecret_Out));

            in->authHandle = handles[0];
            in->policySession = handles[1];
            result = TPM2B_NONCE_Unmarshal(&in->nonceTPM, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_nonceTPM;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_policyRef;
            result = INT32_Unmarshal(&in->expiration, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicySecret_expiration;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicySecret action routine
            result = TPM2_PolicySecret (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicySecret_Out);
            *respParmSize += TPM2B_TIMEOUT_Marshal(&out->timeout, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_AUTH_Marshal(&out->policyTicket, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicySecret 
#if CC_PolicyTicket
        case TPM_CC_PolicyTicket:
        {
            // Buffer for input parameters
            PolicyTicket_In *in = (PolicyTicket_In *) 
                         MemoryGetInBuffer(sizeof(PolicyTicket_In));
            in->policySession = handles[0];
            result = TPM2B_TIMEOUT_Unmarshal(&in->timeout, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_timeout;
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_cpHashA;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_policyRef;
            result = TPM2B_NAME_Unmarshal(&in->authName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_authName;
            result = TPMT_TK_AUTH_Unmarshal(&in->ticket, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTicket_ticket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyTicket action routine
            result = TPM2_PolicyTicket (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyTicket 
#if CC_PolicyOR
        case TPM_CC_PolicyOR:
        {
            // Buffer for input parameters
            PolicyOR_In *in = (PolicyOR_In *) 
                         MemoryGetInBuffer(sizeof(PolicyOR_In));
            in->policySession = handles[0];
            result = TPML_DIGEST_Unmarshal(&in->pHashList, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyOR_pHashList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyOR action routine
            result = TPM2_PolicyOR (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyOR 
#if CC_PolicyPCR
        case TPM_CC_PolicyPCR:
        {
            // Buffer for input parameters
            PolicyPCR_In *in = (PolicyPCR_In *) 
                         MemoryGetInBuffer(sizeof(PolicyPCR_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->pcrDigest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyPCR_pcrDigest;
            result = TPML_PCR_SELECTION_Unmarshal(&in->pcrs, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyPCR_pcrs;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyPCR action routine
            result = TPM2_PolicyPCR (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPCR 
#if CC_PolicyLocality
        case TPM_CC_PolicyLocality:
        {
            // Buffer for input parameters
            PolicyLocality_In *in = (PolicyLocality_In *) 
                         MemoryGetInBuffer(sizeof(PolicyLocality_In));
            in->policySession = handles[0];
            result = TPMA_LOCALITY_Unmarshal(&in->locality, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyLocality_locality;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyLocality action routine
            result = TPM2_PolicyLocality (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyLocality 
#if CC_PolicyNV
        case TPM_CC_PolicyNV:
        {
            // Buffer for input parameters
            PolicyNV_In *in = (PolicyNV_In *) 
                         MemoryGetInBuffer(sizeof(PolicyNV_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            in->policySession = handles[2];
            result = TPM2B_OPERAND_Unmarshal(&in->operandB, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_operandB;
            result = UINT16_Unmarshal(&in->offset, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_offset;
            result = TPM_EO_Unmarshal(&in->operation, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNV_operation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyNV action routine
            result = TPM2_PolicyNV (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNV 
#if CC_PolicyCounterTimer
        case TPM_CC_PolicyCounterTimer:
        {
            // Buffer for input parameters
            PolicyCounterTimer_In *in = (PolicyCounterTimer_In *) 
                         MemoryGetInBuffer(sizeof(PolicyCounterTimer_In));
            in->policySession = handles[0];
            result = TPM2B_OPERAND_Unmarshal(&in->operandB, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_operandB;
            result = UINT16_Unmarshal(&in->offset, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_offset;
            result = TPM_EO_Unmarshal(&in->operation, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCounterTimer_operation;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyCounterTimer action routine
            result = TPM2_PolicyCounterTimer (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCounterTimer 
#if CC_PolicyCommandCode
        case TPM_CC_PolicyCommandCode:
        {
            // Buffer for input parameters
            PolicyCommandCode_In *in = (PolicyCommandCode_In *) 
                         MemoryGetInBuffer(sizeof(PolicyCommandCode_In));
            in->policySession = handles[0];
            result = TPM_CC_Unmarshal(&in->code, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCommandCode_code;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyCommandCode action routine
            result = TPM2_PolicyCommandCode (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCommandCode 
#if CC_PolicyPhysicalPresence
        case TPM_CC_PolicyPhysicalPresence:
        {
            // Buffer for input parameters
            PolicyPhysicalPresence_In *in = (PolicyPhysicalPresence_In *) 
                         MemoryGetInBuffer(sizeof(PolicyPhysicalPresence_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyPhysicalPresence action routine
            result = TPM2_PolicyPhysicalPresence (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPhysicalPresence 
#if CC_PolicyCpHash
        case TPM_CC_PolicyCpHash:
        {
            // Buffer for input parameters
            PolicyCpHash_In *in = (PolicyCpHash_In *) 
                         MemoryGetInBuffer(sizeof(PolicyCpHash_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->cpHashA, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyCpHash_cpHashA;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyCpHash action routine
            result = TPM2_PolicyCpHash (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyCpHash 
#if CC_PolicyNameHash
        case TPM_CC_PolicyNameHash:
        {
            // Buffer for input parameters
            PolicyNameHash_In *in = (PolicyNameHash_In *) 
                         MemoryGetInBuffer(sizeof(PolicyNameHash_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->nameHash, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNameHash_nameHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyNameHash action routine
            result = TPM2_PolicyNameHash (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNameHash 
#if CC_PolicyDuplicationSelect
        case TPM_CC_PolicyDuplicationSelect:
        {
            // Buffer for input parameters
            PolicyDuplicationSelect_In *in = (PolicyDuplicationSelect_In *) 
                         MemoryGetInBuffer(sizeof(PolicyDuplicationSelect_In));
            in->policySession = handles[0];
            result = TPM2B_NAME_Unmarshal(&in->objectName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_objectName;
            result = TPM2B_NAME_Unmarshal(&in->newParentName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_newParentName;
            result = TPMI_YES_NO_Unmarshal(&in->includeObject, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyDuplicationSelect_includeObject;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyDuplicationSelect action routine
            result = TPM2_PolicyDuplicationSelect (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyDuplicationSelect 
#if CC_PolicyAuthorize
        case TPM_CC_PolicyAuthorize:
        {
            // Buffer for input parameters
            PolicyAuthorize_In *in = (PolicyAuthorize_In *) 
                         MemoryGetInBuffer(sizeof(PolicyAuthorize_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->approvedPolicy, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_approvedPolicy;
            result = TPM2B_NONCE_Unmarshal(&in->policyRef, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_policyRef;
            result = TPM2B_NAME_Unmarshal(&in->keySign, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_keySign;
            result = TPMT_TK_VERIFIED_Unmarshal(&in->checkTicket, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyAuthorize_checkTicket;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyAuthorize action routine
            result = TPM2_PolicyAuthorize (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthorize 
#if CC_PolicyAuthValue
        case TPM_CC_PolicyAuthValue:
        {
            // Buffer for input parameters
            PolicyAuthValue_In *in = (PolicyAuthValue_In *) 
                         MemoryGetInBuffer(sizeof(PolicyAuthValue_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyAuthValue action routine
            result = TPM2_PolicyAuthValue (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthValue 
#if CC_PolicyPassword
        case TPM_CC_PolicyPassword:
        {
            // Buffer for input parameters
            PolicyPassword_In *in = (PolicyPassword_In *) 
                         MemoryGetInBuffer(sizeof(PolicyPassword_In));
            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyPassword action routine
            result = TPM2_PolicyPassword (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyPassword 
#if CC_PolicyGetDigest
        case TPM_CC_PolicyGetDigest:
        {
            // Buffer for input parameters
            PolicyGetDigest_In *in = (PolicyGetDigest_In *) 
                         MemoryGetInBuffer(sizeof(PolicyGetDigest_In));
            // Buffer for output parameters
            PolicyGetDigest_Out *out = (PolicyGetDigest_Out *) 
                        MemoryGetOutBuffer(sizeof(PolicyGetDigest_Out));

            in->policySession = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyGetDigest action routine
            result = TPM2_PolicyGetDigest (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(PolicyGetDigest_Out);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->policyDigest, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_PolicyGetDigest 
#if CC_PolicyNvWritten
        case TPM_CC_PolicyNvWritten:
        {
            // Buffer for input parameters
            PolicyNvWritten_In *in = (PolicyNvWritten_In *) 
                         MemoryGetInBuffer(sizeof(PolicyNvWritten_In));
            in->policySession = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->writtenSet, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyNvWritten_writtenSet;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyNvWritten action routine
            result = TPM2_PolicyNvWritten (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyNvWritten 
#if CC_PolicyTemplate
        case TPM_CC_PolicyTemplate:
        {
            // Buffer for input parameters
            PolicyTemplate_In *in = (PolicyTemplate_In *) 
                         MemoryGetInBuffer(sizeof(PolicyTemplate_In));
            in->policySession = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->templateHash, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PolicyTemplate_templateHash;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyTemplate action routine
            result = TPM2_PolicyTemplate (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyTemplate 
#if CC_PolicyAuthorizeNV
        case TPM_CC_PolicyAuthorizeNV:
        {
            // Buffer for input parameters
            PolicyAuthorizeNV_In *in = (PolicyAuthorizeNV_In *) 
                         MemoryGetInBuffer(sizeof(PolicyAuthorizeNV_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            in->policySession = handles[2];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PolicyAuthorizeNV action routine
            result = TPM2_PolicyAuthorizeNV (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PolicyAuthorizeNV 
#if CC_CreatePrimary
        case TPM_CC_CreatePrimary:
        {
            // Buffer for input parameters
            CreatePrimary_In *in = (CreatePrimary_In *) 
                         MemoryGetInBuffer(sizeof(CreatePrimary_In));
            // Buffer for output parameters
            CreatePrimary_Out *out = (CreatePrimary_Out *) 
                        MemoryGetOutBuffer(sizeof(CreatePrimary_Out));

            in->primaryHandle = handles[0];
            result = TPM2B_SENSITIVE_CREATE_Unmarshal(&in->inSensitive, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_inSensitive;
            result = TPM2B_PUBLIC_Unmarshal(&in->inPublic, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_inPublic;
            result = TPM2B_DATA_Unmarshal(&in->outsideInfo, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_outsideInfo;
            result = TPML_PCR_SELECTION_Unmarshal(&in->creationPCR, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_CreatePrimary_creationPCR;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_CreatePrimary action routine
            result = TPM2_CreatePrimary (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(CreatePrimary_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->objectHandle;
            *respParmSize += TPM2B_PUBLIC_Marshal(&out->outPublic, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_CREATION_DATA_Marshal(&out->creationData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_DIGEST_Marshal(&out->creationHash, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_TK_CREATION_Marshal(&out->creationTicket, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->name, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_CreatePrimary 
#if CC_HierarchyControl
        case TPM_CC_HierarchyControl:
        {
            // Buffer for input parameters
            HierarchyControl_In *in = (HierarchyControl_In *) 
                         MemoryGetInBuffer(sizeof(HierarchyControl_In));
            in->authHandle = handles[0];
            result = TPMI_RH_ENABLES_Unmarshal(&in->enable, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyControl_enable;
            result = TPMI_YES_NO_Unmarshal(&in->state, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyControl_state;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_HierarchyControl action routine
            result = TPM2_HierarchyControl (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_HierarchyControl 
#if CC_SetPrimaryPolicy
        case TPM_CC_SetPrimaryPolicy:
        {
            // Buffer for input parameters
            SetPrimaryPolicy_In *in = (SetPrimaryPolicy_In *) 
                         MemoryGetInBuffer(sizeof(SetPrimaryPolicy_In));
            in->authHandle = handles[0];
            result = TPM2B_DIGEST_Unmarshal(&in->authPolicy, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetPrimaryPolicy_authPolicy;
            result = TPMI_ALG_HASH_Unmarshal(&in->hashAlg, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetPrimaryPolicy_hashAlg;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SetPrimaryPolicy action routine
            result = TPM2_SetPrimaryPolicy (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetPrimaryPolicy 
#if CC_ChangePPS
        case TPM_CC_ChangePPS:
        {
            // Buffer for input parameters
            ChangePPS_In *in = (ChangePPS_In *) 
                         MemoryGetInBuffer(sizeof(ChangePPS_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ChangePPS action routine
            result = TPM2_ChangePPS (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ChangePPS 
#if CC_ChangeEPS
        case TPM_CC_ChangeEPS:
        {
            // Buffer for input parameters
            ChangeEPS_In *in = (ChangeEPS_In *) 
                         MemoryGetInBuffer(sizeof(ChangeEPS_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ChangeEPS action routine
            result = TPM2_ChangeEPS (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ChangeEPS 
#if CC_Clear
        case TPM_CC_Clear:
        {
            // Buffer for input parameters
            Clear_In *in = (Clear_In *) 
                         MemoryGetInBuffer(sizeof(Clear_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Clear action routine
            result = TPM2_Clear (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Clear 
#if CC_ClearControl
        case TPM_CC_ClearControl:
        {
            // Buffer for input parameters
            ClearControl_In *in = (ClearControl_In *) 
                         MemoryGetInBuffer(sizeof(ClearControl_In));
            in->auth = handles[0];
            result = TPMI_YES_NO_Unmarshal(&in->disable, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClearControl_disable;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ClearControl action routine
            result = TPM2_ClearControl (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClearControl 
#if CC_HierarchyChangeAuth
        case TPM_CC_HierarchyChangeAuth:
        {
            // Buffer for input parameters
            HierarchyChangeAuth_In *in = (HierarchyChangeAuth_In *) 
                         MemoryGetInBuffer(sizeof(HierarchyChangeAuth_In));
            in->authHandle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_HierarchyChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_HierarchyChangeAuth action routine
            result = TPM2_HierarchyChangeAuth (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_HierarchyChangeAuth 
#if CC_DictionaryAttackLockReset
        case TPM_CC_DictionaryAttackLockReset:
        {
            // Buffer for input parameters
            DictionaryAttackLockReset_In *in = (DictionaryAttackLockReset_In *) 
                         MemoryGetInBuffer(sizeof(DictionaryAttackLockReset_In));
            in->lockHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_DictionaryAttackLockReset action routine
            result = TPM2_DictionaryAttackLockReset (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_DictionaryAttackLockReset 
#if CC_DictionaryAttackParameters
        case TPM_CC_DictionaryAttackParameters:
        {
            // Buffer for input parameters
            DictionaryAttackParameters_In *in = (DictionaryAttackParameters_In *) 
                         MemoryGetInBuffer(sizeof(DictionaryAttackParameters_In));
            in->lockHandle = handles[0];
            result = UINT32_Unmarshal(&in->newMaxTries, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_newMaxTries;
            result = UINT32_Unmarshal(&in->newRecoveryTime, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_newRecoveryTime;
            result = UINT32_Unmarshal(&in->lockoutRecovery, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_DictionaryAttackParameters_lockoutRecovery;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_DictionaryAttackParameters action routine
            result = TPM2_DictionaryAttackParameters (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_DictionaryAttackParameters 
#if CC_PP_Commands
        case TPM_CC_PP_Commands:
        {
            // Buffer for input parameters
            PP_Commands_In *in = (PP_Commands_In *) 
                         MemoryGetInBuffer(sizeof(PP_Commands_In));
            in->auth = handles[0];
            result = TPML_CC_Unmarshal(&in->setList, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PP_Commands_setList;
            result = TPML_CC_Unmarshal(&in->clearList, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_PP_Commands_clearList;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_PP_Commands action routine
            result = TPM2_PP_Commands (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_PP_Commands 
#if CC_SetAlgorithmSet
        case TPM_CC_SetAlgorithmSet:
        {
            // Buffer for input parameters
            SetAlgorithmSet_In *in = (SetAlgorithmSet_In *) 
                         MemoryGetInBuffer(sizeof(SetAlgorithmSet_In));
            in->authHandle = handles[0];
            result = UINT32_Unmarshal(&in->algorithmSet, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_SetAlgorithmSet_algorithmSet;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_SetAlgorithmSet action routine
            result = TPM2_SetAlgorithmSet (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_SetAlgorithmSet 
#if CC_FieldUpgradeStart
        case TPM_CC_FieldUpgradeStart:
        {
            // Buffer for input parameters
            FieldUpgradeStart_In *in = (FieldUpgradeStart_In *) 
                         MemoryGetInBuffer(sizeof(FieldUpgradeStart_In));
            in->authorization = handles[0];
            in->keyHandle = handles[1];
            result = TPM2B_DIGEST_Unmarshal(&in->fuDigest, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeStart_fuDigest;
            result = TPMT_SIGNATURE_Unmarshal(&in->manifestSignature, 
                                   paramBuffer, paramBufferSize, FALSE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeStart_manifestSignature;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_FieldUpgradeStart action routine
            result = TPM2_FieldUpgradeStart (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_FieldUpgradeStart 
#if CC_FieldUpgradeData
        case TPM_CC_FieldUpgradeData:
        {
            // Buffer for input parameters
            FieldUpgradeData_In *in = (FieldUpgradeData_In *) 
                         MemoryGetInBuffer(sizeof(FieldUpgradeData_In));
            // Buffer for output parameters
            FieldUpgradeData_Out *out = (FieldUpgradeData_Out *) 
                        MemoryGetOutBuffer(sizeof(FieldUpgradeData_Out));

            result = TPM2B_MAX_BUFFER_Unmarshal(&in->fuData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FieldUpgradeData_fuData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_FieldUpgradeData action routine
            result = TPM2_FieldUpgradeData (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(FieldUpgradeData_Out);
            *respParmSize += TPMT_HA_Marshal(&out->nextDigest, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_HA_Marshal(&out->firstDigest, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_FieldUpgradeData 
#if CC_FirmwareRead
        case TPM_CC_FirmwareRead:
        {
            // Buffer for input parameters
            FirmwareRead_In *in = (FirmwareRead_In *) 
                         MemoryGetInBuffer(sizeof(FirmwareRead_In));
            // Buffer for output parameters
            FirmwareRead_Out *out = (FirmwareRead_Out *) 
                        MemoryGetOutBuffer(sizeof(FirmwareRead_Out));

            result = UINT32_Unmarshal(&in->sequenceNumber, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FirmwareRead_sequenceNumber;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_FirmwareRead action routine
            result = TPM2_FirmwareRead (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(FirmwareRead_Out);
            *respParmSize += TPM2B_MAX_BUFFER_Marshal(&out->fuData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_FirmwareRead 
#if CC_ContextSave
        case TPM_CC_ContextSave:
        {
            // Buffer for input parameters
            ContextSave_In *in = (ContextSave_In *) 
                         MemoryGetInBuffer(sizeof(ContextSave_In));
            // Buffer for output parameters
            ContextSave_Out *out = (ContextSave_Out *) 
                        MemoryGetOutBuffer(sizeof(ContextSave_Out));

            in->saveHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ContextSave action routine
            result = TPM2_ContextSave (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ContextSave_Out);
            *respParmSize += TPMS_CONTEXT_Marshal(&out->context, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ContextSave 
#if CC_ContextLoad
        case TPM_CC_ContextLoad:
        {
            // Buffer for input parameters
            ContextLoad_In *in = (ContextLoad_In *) 
                         MemoryGetInBuffer(sizeof(ContextLoad_In));
            // Buffer for output parameters
            ContextLoad_Out *out = (ContextLoad_Out *) 
                        MemoryGetOutBuffer(sizeof(ContextLoad_Out));

            result = TPMS_CONTEXT_Unmarshal(&in->context, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ContextLoad_context;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ContextLoad action routine
            result = TPM2_ContextLoad (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ContextLoad_Out);
            // Copy the response handle (don't unmarshal)
            command->handles[command->handleNum++] = out->loadedHandle;
        }
        break;
#endif     // CC_ContextLoad 
#if CC_FlushContext
        case TPM_CC_FlushContext:
        {
            // Buffer for input parameters
            FlushContext_In *in = (FlushContext_In *) 
                         MemoryGetInBuffer(sizeof(FlushContext_In));
            result = TPMI_DH_CONTEXT_Unmarshal(&in->flushHandle, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_FlushContext_flushHandle;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_FlushContext action routine
            result = TPM2_FlushContext (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_FlushContext 
#if CC_EvictControl
        case TPM_CC_EvictControl:
        {
            // Buffer for input parameters
            EvictControl_In *in = (EvictControl_In *) 
                         MemoryGetInBuffer(sizeof(EvictControl_In));
            in->auth = handles[0];
            in->objectHandle = handles[1];
            result = TPMI_DH_PERSISTENT_Unmarshal(&in->persistentHandle, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_EvictControl_persistentHandle;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_EvictControl action routine
            result = TPM2_EvictControl (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_EvictControl 
#if CC_ReadClock
        case TPM_CC_ReadClock:
        {
            // Buffer for output parameters
            ReadClock_Out *out = (ReadClock_Out *) 
                        MemoryGetOutBuffer(sizeof(ReadClock_Out));

            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ReadClock action routine
            result = TPM2_ReadClock (out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(ReadClock_Out);
            *respParmSize += TPMS_TIME_INFO_Marshal(&out->currentTime, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_ReadClock 
#if CC_ClockSet
        case TPM_CC_ClockSet:
        {
            // Buffer for input parameters
            ClockSet_In *in = (ClockSet_In *) 
                         MemoryGetInBuffer(sizeof(ClockSet_In));
            in->auth = handles[0];
            result = UINT64_Unmarshal(&in->newTime, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClockSet_newTime;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ClockSet action routine
            result = TPM2_ClockSet (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClockSet 
#if CC_ClockRateAdjust
        case TPM_CC_ClockRateAdjust:
        {
            // Buffer for input parameters
            ClockRateAdjust_In *in = (ClockRateAdjust_In *) 
                         MemoryGetInBuffer(sizeof(ClockRateAdjust_In));
            in->auth = handles[0];
            result = TPM_CLOCK_ADJUST_Unmarshal(&in->rateAdjust, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_ClockRateAdjust_rateAdjust;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_ClockRateAdjust action routine
            result = TPM2_ClockRateAdjust (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_ClockRateAdjust 
#if CC_GetCapability
        case TPM_CC_GetCapability:
        {
            // Buffer for input parameters
            GetCapability_In *in = (GetCapability_In *) 
                         MemoryGetInBuffer(sizeof(GetCapability_In));
            // Buffer for output parameters
            GetCapability_Out *out = (GetCapability_Out *) 
                        MemoryGetOutBuffer(sizeof(GetCapability_Out));

            result = TPM_CAP_Unmarshal(&in->capability, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_capability;
            result = UINT32_Unmarshal(&in->property, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_property;
            result = UINT32_Unmarshal(&in->propertyCount, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_GetCapability_propertyCount;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_GetCapability action routine
            result = TPM2_GetCapability (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(GetCapability_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->moreData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMS_CAPABILITY_DATA_Marshal(&out->capabilityData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_GetCapability 
#if CC_TestParms
        case TPM_CC_TestParms:
        {
            // Buffer for input parameters
            TestParms_In *in = (TestParms_In *) 
                         MemoryGetInBuffer(sizeof(TestParms_In));
            result = TPMT_PUBLIC_PARMS_Unmarshal(&in->parameters, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_TestParms_parameters;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_TestParms action routine
            result = TPM2_TestParms (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_TestParms 
#if CC_NV_DefineSpace
        case TPM_CC_NV_DefineSpace:
        {
            // Buffer for input parameters
            NV_DefineSpace_In *in = (NV_DefineSpace_In *) 
                         MemoryGetInBuffer(sizeof(NV_DefineSpace_In));
            in->authHandle = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->auth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_DefineSpace_auth;
            result = TPM2B_NV_PUBLIC_Unmarshal(&in->publicInfo, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_DefineSpace_publicInfo;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_DefineSpace action routine
            result = TPM2_NV_DefineSpace (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_DefineSpace 
#if CC_NV_UndefineSpace
        case TPM_CC_NV_UndefineSpace:
        {
            // Buffer for input parameters
            NV_UndefineSpace_In *in = (NV_UndefineSpace_In *) 
                         MemoryGetInBuffer(sizeof(NV_UndefineSpace_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_UndefineSpace action routine
            result = TPM2_NV_UndefineSpace (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_UndefineSpace 
#if CC_NV_UndefineSpaceSpecial
        case TPM_CC_NV_UndefineSpaceSpecial:
        {
            // Buffer for input parameters
            NV_UndefineSpaceSpecial_In *in = (NV_UndefineSpaceSpecial_In *) 
                         MemoryGetInBuffer(sizeof(NV_UndefineSpaceSpecial_In));
            in->nvIndex = handles[0];
            in->platform = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_UndefineSpaceSpecial action routine
            result = TPM2_NV_UndefineSpaceSpecial (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_UndefineSpaceSpecial 
#if CC_NV_ReadPublic
        case TPM_CC_NV_ReadPublic:
        {
            // Buffer for input parameters
            NV_ReadPublic_In *in = (NV_ReadPublic_In *) 
                         MemoryGetInBuffer(sizeof(NV_ReadPublic_In));
            // Buffer for output parameters
            NV_ReadPublic_Out *out = (NV_ReadPublic_Out *) 
                        MemoryGetOutBuffer(sizeof(NV_ReadPublic_Out));

            in->nvIndex = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_ReadPublic action routine
            result = TPM2_NV_ReadPublic (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_ReadPublic_Out);
            *respParmSize += TPM2B_NV_PUBLIC_Marshal(&out->nvPublic, 
                                          responseBuffer, &rSize);
            *respParmSize += TPM2B_NAME_Marshal(&out->nvName, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_ReadPublic 
#if CC_NV_Write
        case TPM_CC_NV_Write:
        {
            // Buffer for input parameters
            NV_Write_In *in = (NV_Write_In *) 
                         MemoryGetInBuffer(sizeof(NV_Write_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = TPM2B_MAX_NV_BUFFER_Unmarshal(&in->data, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Write_data;
            result = UINT16_Unmarshal(&in->offset, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Write_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_Write action routine
            result = TPM2_NV_Write (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Write 
#if CC_NV_Increment
        case TPM_CC_NV_Increment:
        {
            // Buffer for input parameters
            NV_Increment_In *in = (NV_Increment_In *) 
                         MemoryGetInBuffer(sizeof(NV_Increment_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_Increment action routine
            result = TPM2_NV_Increment (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Increment 
#if CC_NV_Extend
        case TPM_CC_NV_Extend:
        {
            // Buffer for input parameters
            NV_Extend_In *in = (NV_Extend_In *) 
                         MemoryGetInBuffer(sizeof(NV_Extend_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = TPM2B_MAX_NV_BUFFER_Unmarshal(&in->data, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Extend_data;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_Extend action routine
            result = TPM2_NV_Extend (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_Extend 
#if CC_NV_SetBits
        case TPM_CC_NV_SetBits:
        {
            // Buffer for input parameters
            NV_SetBits_In *in = (NV_SetBits_In *) 
                         MemoryGetInBuffer(sizeof(NV_SetBits_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = UINT64_Unmarshal(&in->bits, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_SetBits_bits;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_SetBits action routine
            result = TPM2_NV_SetBits (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_SetBits 
#if CC_NV_WriteLock
        case TPM_CC_NV_WriteLock:
        {
            // Buffer for input parameters
            NV_WriteLock_In *in = (NV_WriteLock_In *) 
                         MemoryGetInBuffer(sizeof(NV_WriteLock_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_WriteLock action routine
            result = TPM2_NV_WriteLock (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_WriteLock 
#if CC_NV_GlobalWriteLock
        case TPM_CC_NV_GlobalWriteLock:
        {
            // Buffer for input parameters
            NV_GlobalWriteLock_In *in = (NV_GlobalWriteLock_In *) 
                         MemoryGetInBuffer(sizeof(NV_GlobalWriteLock_In));
            in->authHandle = handles[0];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_GlobalWriteLock action routine
            result = TPM2_NV_GlobalWriteLock (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_GlobalWriteLock 
#if CC_NV_Read
        case TPM_CC_NV_Read:
        {
            // Buffer for input parameters
            NV_Read_In *in = (NV_Read_In *) 
                         MemoryGetInBuffer(sizeof(NV_Read_In));
            // Buffer for output parameters
            NV_Read_Out *out = (NV_Read_Out *) 
                        MemoryGetOutBuffer(sizeof(NV_Read_Out));

            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            result = UINT16_Unmarshal(&in->size, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Read_size;
            result = UINT16_Unmarshal(&in->offset, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Read_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_Read action routine
            result = TPM2_NV_Read (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_Read_Out);
            *respParmSize += TPM2B_MAX_NV_BUFFER_Marshal(&out->data, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_Read 
#if CC_NV_ReadLock
        case TPM_CC_NV_ReadLock:
        {
            // Buffer for input parameters
            NV_ReadLock_In *in = (NV_ReadLock_In *) 
                         MemoryGetInBuffer(sizeof(NV_ReadLock_In));
            in->authHandle = handles[0];
            in->nvIndex = handles[1];
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_ReadLock action routine
            result = TPM2_NV_ReadLock (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_ReadLock 
#if CC_NV_ChangeAuth
        case TPM_CC_NV_ChangeAuth:
        {
            // Buffer for input parameters
            NV_ChangeAuth_In *in = (NV_ChangeAuth_In *) 
                         MemoryGetInBuffer(sizeof(NV_ChangeAuth_In));
            in->nvIndex = handles[0];
            result = TPM2B_AUTH_Unmarshal(&in->newAuth, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_ChangeAuth_newAuth;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_ChangeAuth action routine
            result = TPM2_NV_ChangeAuth (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_NV_ChangeAuth 
#if CC_NV_Certify
        case TPM_CC_NV_Certify:
        {
            // Buffer for input parameters
            NV_Certify_In *in = (NV_Certify_In *) 
                         MemoryGetInBuffer(sizeof(NV_Certify_In));
            // Buffer for output parameters
            NV_Certify_Out *out = (NV_Certify_Out *) 
                        MemoryGetOutBuffer(sizeof(NV_Certify_Out));

            in->signHandle = handles[0];
            in->authHandle = handles[1];
            in->nvIndex = handles[2];
            result = TPM2B_DATA_Unmarshal(&in->qualifyingData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_qualifyingData;
            result = TPMT_SIG_SCHEME_Unmarshal(&in->inScheme, 
                                   paramBuffer, paramBufferSize, TRUE);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_inScheme;
            result = UINT16_Unmarshal(&in->size, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_size;
            result = UINT16_Unmarshal(&in->offset, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_NV_Certify_offset;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_NV_Certify action routine
            result = TPM2_NV_Certify (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(NV_Certify_Out);
            *respParmSize += TPM2B_ATTEST_Marshal(&out->certifyInfo, 
                                          responseBuffer, &rSize);
            *respParmSize += TPMT_SIGNATURE_Marshal(&out->signature, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_NV_Certify 
#if CC_AC_GetCapability
        case TPM_CC_AC_GetCapability:
        {
            // Buffer for input parameters
            AC_GetCapability_In *in = (AC_GetCapability_In *) 
                         MemoryGetInBuffer(sizeof(AC_GetCapability_In));
            // Buffer for output parameters
            AC_GetCapability_Out *out = (AC_GetCapability_Out *) 
                        MemoryGetOutBuffer(sizeof(AC_GetCapability_Out));

            in->ac = handles[0];
            result = TPM_AT_Unmarshal(&in->capability, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_GetCapability_capability;
            result = UINT32_Unmarshal(&in->count, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_GetCapability_count;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_AC_GetCapability action routine
            result = TPM2_AC_GetCapability (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(AC_GetCapability_Out);
            *respParmSize += TPMI_YES_NO_Marshal(&out->moreData, 
                                          responseBuffer, &rSize);
            *respParmSize += TPML_AC_CAPABILITIES_Marshal(&out->capabilitiesData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_AC_GetCapability 
#if CC_AC_Send
        case TPM_CC_AC_Send:
        {
            // Buffer for input parameters
            AC_Send_In *in = (AC_Send_In *) 
                         MemoryGetInBuffer(sizeof(AC_Send_In));
            // Buffer for output parameters
            AC_Send_Out *out = (AC_Send_Out *) 
                        MemoryGetOutBuffer(sizeof(AC_Send_Out));

            in->sendObject = handles[0];
            in->authHandle = handles[1];
            in->ac = handles[2];
            result = TPM2B_MAX_BUFFER_Unmarshal(&in->acDataIn, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_AC_Send_acDataIn;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_AC_Send action routine
            result = TPM2_AC_Send (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(AC_Send_Out);
            *respParmSize += TPMS_AC_OUTPUT_Marshal(&out->acDataOut, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_AC_Send 
#if CC_Policy_AC_SendSelect
        case TPM_CC_Policy_AC_SendSelect:
        {
            // Buffer for input parameters
            Policy_AC_SendSelect_In *in = (Policy_AC_SendSelect_In *) 
                         MemoryGetInBuffer(sizeof(Policy_AC_SendSelect_In));
            in->policySession = handles[0];
            result = TPM2B_NAME_Unmarshal(&in->objectName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_objectName;
            result = TPM2B_NAME_Unmarshal(&in->authHandleName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_authHandleName;
            result = TPM2B_NAME_Unmarshal(&in->acName, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_acName;
            result = TPMI_YES_NO_Unmarshal(&in->includeObject, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Policy_AC_SendSelect_includeObject;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Policy_AC_SendSelect action routine
            result = TPM2_Policy_AC_SendSelect (in);
            if(result != TPM_RC_SUCCESS) 
                return result;
        }
        break;
#endif     // CC_Policy_AC_SendSelect 
#if CC_Vendor_TCG_Test
        case TPM_CC_Vendor_TCG_Test:
        {
            // Buffer for input parameters
            Vendor_TCG_Test_In *in = (Vendor_TCG_Test_In *) 
                         MemoryGetInBuffer(sizeof(Vendor_TCG_Test_In));
            // Buffer for output parameters
            Vendor_TCG_Test_Out *out = (Vendor_TCG_Test_Out *) 
                        MemoryGetOutBuffer(sizeof(Vendor_TCG_Test_Out));

            result = TPM2B_DATA_Unmarshal(&in->inputData, 
                                   paramBuffer, paramBufferSize);
            if(result != TPM_RC_SUCCESS) 
                return result + RC_Vendor_TCG_Test_inputData;
            if(*paramBufferSize != 0) 
                return TPM_RC_SIZE;
    // TPM2_Vendor_TCG_Test action routine
            result = TPM2_Vendor_TCG_Test (in, out);
            if(result != TPM_RC_SUCCESS) 
                return result;
            rSize = sizeof(Vendor_TCG_Test_Out);
            *respParmSize += TPM2B_DATA_Marshal(&out->outputData, 
                                          responseBuffer, &rSize);
        }
        break;
#endif     // CC_Vendor_TCG_Test 
