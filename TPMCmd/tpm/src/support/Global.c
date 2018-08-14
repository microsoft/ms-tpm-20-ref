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
//** Description
// This file will instance the TPM variables that are not stack allocated. The
// descriptions for these variables are in Global.h.

//** Includes and Defines
#define GLOBAL_C
#include "Tpm.h"

//** __IGNORE_STATE__
// This macro value is used to delimit values that are only used within the scope of
// a single TPM command. For a virtualized TPM, this would be state that does not
// need to be preserved between commands. This is not a lot of data and it may not
// be necessary to exclude this data.

//** Global Data Values

// These values are visible across multiple modules.
BOOL                 g_phEnable;

const UINT16         g_rcIndex[15] = {TPM_RC_1, TPM_RC_2, TPM_RC_3, TPM_RC_4,
                                      TPM_RC_5, TPM_RC_6, TPM_RC_7, TPM_RC_8,
                                      TPM_RC_9, TPM_RC_A, TPM_RC_B, TPM_RC_C,
                                      TPM_RC_D, TPM_RC_E, TPM_RC_F
};

TPM_HANDLE           g_exclusiveAuditSession;

UINT64               g_time;

#if CLOCK_STOPS
CLOCK_NONCE          g_timeEpoch;
#endif

BOOL                 g_pcrReConfig;

TPMI_DH_OBJECT       g_DRTMHandle;

BOOL                 g_DrtmPreStartup;

BOOL                 g_StartupLocality3;

#if USE_DA_USED
BOOL                 g_daUsed;
#endif

BOOL                 g_powerWasLost;

BOOL                 g_clearOrderly;

TPM_SU               g_prevOrderlyState;

UPDATE_TYPE          g_updateNV;

BOOL                 g_nvOk;

TPM_RC               g_NvStatus;

TPM2B_AUTH           g_platformUniqueDetails;

ALGORITHM_VECTOR     g_implementedAlgorithms;
ALGORITHM_VECTOR     g_toTest;

CRYPTO_SELF_TEST_STATE    g_cryptoSelfTestState;    // This structure contains the 
                                                    // cryptographic self-test 
#if SIMULATION
BOOL                 g_forceFailureMode;
#endif
BOOL                 g_inFailureMode;

STATE_CLEAR_DATA     gc;

STATE_RESET_DATA     gr;

PERSISTENT_DATA      gp;

ORDERLY_DATA         go;

//** Private Values
//*** Used in SessionProcess.c
#ifndef __IGNORE_STATE__        // DO NOT DEFINE THIS VALUE
// These values do not need to be retained between commands.
TPM_HANDLE           s_sessionHandles[MAX_SESSION_NUM];
TPMA_SESSION         s_attributes[MAX_SESSION_NUM];
TPM_HANDLE           s_associatedHandles[MAX_SESSION_NUM];
TPM2B_NONCE          s_nonceCaller[MAX_SESSION_NUM];
TPM2B_AUTH           s_inputAuthValues[MAX_SESSION_NUM];
SESSION             *s_usedSessions[MAX_SESSION_NUM];
UINT32               s_encryptSessionIndex;
UINT32               s_decryptSessionIndex;
UINT32               s_auditSessionIndex;
#endif  // __IGNORE_STATE__

BOOL                 s_DAPendingOnNV;

#if CC_GetCommandAuditDigest
TPM2B_DIGEST         s_cpHashForCommandAudit;
#endif

//*** Used in DA.c
#if !ACCUMULATE_SELF_HEAL_TIMER
UINT64               s_selfHealTimer;
UINT64               s_lockoutTimer;
#endif // !ACCUMULATE_SELF_HEAL_TIMER

//*** Used in NV.c
UINT64               s_maxCounter;
NV_REF               s_evictNvEnd;
BYTE                 s_indexOrderlyRam[RAM_INDEX_SPACE];
#ifndef __IGNORE_STATE__        // DO NOT DEFINE THIS VALUE
NV_INDEX             s_cachedNvIndex;
NV_REF               s_cachedNvRef;
BYTE                *s_cachedNvRamRef;
#endif // __IGNORE_STATE__

//*** Used in Object.c
OBJECT              s_objects[MAX_LOADED_OBJECTS];

//*** Used in PCR.c
PCR                  s_pcrs[IMPLEMENTATION_PCR];

//*** Used in Session.c
SESSION_SLOT         s_sessions[MAX_LOADED_SESSIONS];
UINT32               s_oldestSavedSession;
int                  s_freeSessionSlots;

//*** Used in MemoryLib.c
#ifndef __IGNORE_STATE__        // DO NOT DEFINE THIS VALUE
UINT64   s_actionIoBuffer[768];      // action I/O buffer
UINT32   s_actionIoAllocation;       // number of UIN64 allocated for in
#endif

//*** used in TpmFail.c
UINT32               s_failFunction;
UINT32               s_failLine;
UINT32               s_failCode;

//*** Used in CryptRand.c
// This is the state used when the library uses a random number generator.
// A special function is installed for the library to call. That function
// picks up the state from this location and uses it for the generation
// of the random number.
RAND_STATE           *s_random;


//*** Used in Manufacture.c
// The values is here rather than in the simulator or platform files in order
// to make it easier to find the TPM state. This is significant when trying to do
// TPM virtualization when the TPM state has to be moved along with virtual machine
// with which it is associated.
BOOL                 g_manufactured = FALSE;

//*** Used in Power.c
// This is here for the same reason that g_manufactured is here. Both of these
// values can be provided by the actual platform-specific code or by hardware
// indications.
BOOL                 g_initialized;

//*** Purpose-specific String Constants
// These string constants are shared across functions to make sure that they 
// are all using consistent sting values.
TPM2B_STRING(PRIMARY_OBJECT_CREATION, "Primary Object Creation");
TPM2B_STRING(CFB_KEY, "CFB");
TPM2B_STRING(CONTEXT_KEY, "CONTEXT");
TPM2B_STRING(INTEGRITY_KEY, "INTEGRITY");
TPM2B_STRING(SECRET_KEY, "SECRET");
TPM2B_STRING(SESSION_KEY, "ATH");
TPM2B_STRING(STORAGE_KEY, "STORAGE");
TPM2B_STRING(XOR_KEY, "XOR");
TPM2B_STRING(COMMIT_STRING, "ECDAA Commit");
TPM2B_STRING(DUPLICATE_STRING, "DUPLICATE");
TPM2B_STRING(IDENTITY_STRING, "IDENTITY");
TPM2B_STRING(OBFUSCATE_STRING, "OBFUSCATE");
#if SELF_TEST
TPM2B_STRING(OAEP_TEST_STRING, "OAEP Test Value");
#endif // SELF_TEST
