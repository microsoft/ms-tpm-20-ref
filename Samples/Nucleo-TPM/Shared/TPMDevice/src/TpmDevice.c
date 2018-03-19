#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "StmUtil.h"
#include <wolfssl/wolfcrypt/sha512.h>
#undef INLINE
#include "Tpm.h"
#include "TpmDevice.h"

volatile tpmOperation_t tpmOp = { 0 };
extern char tpmUnique[WC_SHA512_DIGEST_SIZE];

uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

#ifndef NDEBUG
#define TPM_RC_MAX_FM1 (TPM_RC)(RC_FMT1 + 0x03F)

typedef struct
{
    uint32_t index;
    char* str;
} lookup_t;

const lookup_t tpm_cc_table[] =
{
#if CC_NV_UndefineSpaceSpecial == YES
    {TPM_CC_NV_UndefineSpaceSpecial, "TPM_CC_NV_UndefineSpaceSpecial"},
#endif
#if CC_EvictControl == YES
    {TPM_CC_EvictControl, "TPM_CC_EvictControl"},
#endif
#if CC_HierarchyControl == YES
    {TPM_CC_HierarchyControl, "TPM_CC_HierarchyControl"},
#endif
#if CC_NV_UndefineSpace == YES
    {TPM_CC_NV_UndefineSpace, "TPM_CC_NV_UndefineSpace"},
#endif
#if CC_ChangeEPS == YES
    {TPM_CC_ChangeEPS, "TPM_CC_ChangeEPS"},
#endif
#if CC_ChangePPS == YES
    {TPM_CC_ChangePPS, "TPM_CC_ChangePPS"},
#endif
#if CC_Clear == YES
    {TPM_CC_Clear, "TPM_CC_Clear"},
#endif
#if CC_ClearControl == YES
    {TPM_CC_ClearControl, "TPM_CC_ClearControl"},
#endif
#if CC_ClockSet == YES
    {TPM_CC_ClockSet, "TPM_CC_ClockSet"},
#endif
#if CC_HierarchyChangeAuth == YES
    {TPM_CC_HierarchyChangeAuth, "TPM_CC_HierarchyChangeAuth"},
#endif
#if CC_NV_DefineSpace == YES
    {TPM_CC_NV_DefineSpace, "TPM_CC_NV_DefineSpace"},
#endif
#if CC_PCR_Allocate == YES
    {TPM_CC_PCR_Allocate, "TPM_CC_PCR_Allocate"},
#endif
#if CC_PCR_SetAuthPolicy == YES
    {TPM_CC_PCR_SetAuthPolicy, "TPM_CC_PCR_SetAuthPolicy"},
#endif
#if CC_PP_Commands == YES
    {TPM_CC_PP_Commands, "TPM_CC_PP_Commands"},
#endif
#if CC_SetPrimaryPolicy == YES
    {TPM_CC_SetPrimaryPolicy, "TPM_CC_SetPrimaryPolicy"},
#endif
#if CC_FieldUpgradeStart == YES
    {TPM_CC_FieldUpgradeStart, "TPM_CC_FieldUpgradeStart"},
#endif
#if CC_ClockRateAdjust == YES
    {TPM_CC_ClockRateAdjust, "TPM_CC_ClockRateAdjust"},
#endif
#if CC_CreatePrimary == YES
    {TPM_CC_CreatePrimary, "TPM_CC_CreatePrimary"},
#endif
#if CC_NV_GlobalWriteLock == YES
    {TPM_CC_NV_GlobalWriteLock, "TPM_CC_NV_GlobalWriteLock"},
#endif
#if CC_GetCommandAuditDigest == YES
    {TPM_CC_GetCommandAuditDigest, ""},
#endif
#if CC_NV_Increment == YES
    {TPM_CC_NV_Increment, "TPM_CC_NV_Increment"},
#endif
#if CC_NV_SetBits == YES
    {TPM_CC_NV_SetBits, "TPM_CC_NV_SetBits"},
#endif
#if CC_NV_Extend == YES
    {TPM_CC_NV_Extend, "TPM_CC_NV_Extend"},
#endif
#if CC_NV_Write == YES
    {TPM_CC_NV_Write, "TPM_CC_NV_Write"},
#endif
#if CC_NV_WriteLock == YES
    {TPM_CC_NV_WriteLock, "TPM_CC_NV_WriteLock"},
#endif
#if CC_DictionaryAttackLockReset == YES
    {TPM_CC_DictionaryAttackLockReset, "TPM_CC_DictionaryAttackLockReset"},
#endif
#if CC_DictionaryAttackParameters == YES
    {TPM_CC_DictionaryAttackParameters, "TPM_CC_DictionaryAttackParameters"},
#endif
#if CC_NV_ChangeAuth == YES
    {TPM_CC_NV_ChangeAuth, "TPM_CC_NV_ChangeAuth"},
#endif
#if CC_PCR_Event == YES
    {TPM_CC_PCR_Event, "TPM_CC_PCR_Event"},
#endif
#if CC_PCR_Reset == YES
    {TPM_CC_PCR_Reset, "TPM_CC_PCR_Reset"},
#endif
#if CC_SequenceComplete == YES
    {TPM_CC_SequenceComplete, "TPM_CC_SequenceComplete"},
#endif
#if CC_SetAlgorithmSet == YES
    {TPM_CC_SetAlgorithmSet, "TPM_CC_SetAlgorithmSet"},
#endif
#if CC_SetCommandCodeAuditStatus == YES
    {TPM_CC_SetCommandCodeAuditStatus, "TPM_CC_SetCommandCodeAuditStatus"},
#endif
#if CC_FieldUpgradeData == YES
    {TPM_CC_FieldUpgradeData, "TPM_CC_FieldUpgradeData"},
#endif
#if CC_IncrementalSelfTest == YES
    {TPM_CC_IncrementalSelfTest, "TPM_CC_FieldUpgradeData"},
#endif
#if CC_SelfTest == YES
    {TPM_CC_SelfTest, "TPM_CC_SelfTest"},
#endif
#if CC_Startup == YES
    {TPM_CC_Startup, "TPM_CC_Startup"},
#endif
#if CC_Shutdown == YES
    {TPM_CC_Shutdown, "TPM_CC_Shutdown"},
#endif
#if CC_StirRandom == YES
    {TPM_CC_StirRandom, ""},
#endif
#if CC_ActivateCredential == YES
    {TPM_CC_ActivateCredential, "TPM_CC_ActivateCredential"},
#endif
#if CC_Certify == YES
    {TPM_CC_Certify, "TPM_CC_Certify"},
#endif
#if CC_PolicyNV == YES
    {TPM_CC_PolicyNV, "TPM_CC_PolicyNV"},
#endif
#if CC_CertifyCreation == YES
    {TPM_CC_CertifyCreation, "TPM_CC_CertifyCreation"},
#endif
#if CC_Duplicate == YES
    {TPM_CC_Duplicate, "TPM_CC_Duplicate"},
#endif
#if CC_GetTime == YES
    {TPM_CC_GetTime, "TPM_CC_GetTime"},
#endif
#if CC_GetSessionAuditDigest == YES
    {TPM_CC_GetSessionAuditDigest, "TPM_CC_GetSessionAuditDigest"},
#endif
#if CC_NV_Read == YES
    {TPM_CC_NV_Read, "TPM_CC_NV_Read"},
#endif
#if CC_NV_ReadLock == YES
    {TPM_CC_NV_ReadLock, "TPM_CC_NV_ReadLock"},
#endif
#if CC_ObjectChangeAuth == YES
    {TPM_CC_ObjectChangeAuth, "TPM_CC_ObjectChangeAuth"},
#endif
#if CC_PolicySecret == YES
    {TPM_CC_PolicySecret, "TPM_CC_PolicySecret"},
#endif
#if CC_Rewrap == YES
    {TPM_CC_Rewrap, "TPM_CC_Rewrap"},
#endif
#if CC_Create == YES
    {TPM_CC_Create, "TPM_CC_Create"},
#endif
#if CC_ECDH_ZGen == YES
    {TPM_CC_ECDH_ZGen, "TPM_CC_ECDH_ZGen"},
#endif
#if CC_HMAC == YES
    {TPM_CC_HMAC, "TPM_CC_HMAC"},
#endif
#if CC_MAC == YES
    {TPM_CC_MAC, "TPM_CC_HMAC"},
#endif
#if CC_Import == YES
    {TPM_CC_Import, "TPM_CC_Import"},
#endif
#if CC_Load == YES
    {TPM_CC_Load, "TPM_CC_Load"},
#endif
#if CC_Quote == YES
    {TPM_CC_Quote, "TPM_CC_Quote"},
#endif
#if CC_RSA_Decrypt == YES
    {TPM_CC_RSA_Decrypt, "TPM_CC_RSA_Decrypt"},
#endif
#if CC_HMAC_Start == YES
    {TPM_CC_HMAC_Start, "TPM_CC_HMAC_Start"},
#endif
#if CC_MAC_Start == YES
    {TPM_CC_MAC_Start, "TPM_CC_HMAC_Start"},
#endif
#if CC_SequenceUpdate == YES
    {TPM_CC_SequenceUpdate, "TPM_CC_SequenceUpdate"},
#endif
#if CC_Sign == YES
    {TPM_CC_Sign, "TPM_CC_Sign"},
#endif
#if CC_Unseal == YES
    {TPM_CC_Unseal, "TPM_CC_Sign"},
#endif
#if CC_PolicySigned == YES
    {TPM_CC_PolicySigned, "TPM_CC_PolicySigned"},
#endif
#if CC_ContextLoad == YES
    {TPM_CC_ContextLoad, "TPM_CC_ContextLoad"},
#endif
#if CC_ContextSave == YES
    {TPM_CC_ContextSave, "TPM_CC_ContextSave"},
#endif
#if CC_ECDH_KeyGen == YES
    {TPM_CC_ECDH_KeyGen, "TPM_CC_ECDH_KeyGen"},
#endif
#if CC_EncryptDecrypt == YES
    {TPM_CC_EncryptDecrypt, "TPM_CC_EncryptDecrypt"},
#endif
#if CC_FlushContext == YES
    {TPM_CC_FlushContext, "TPM_CC_FlushContext"},
#endif
#if CC_LoadExternal == YES
    {TPM_CC_LoadExternal, ""},
#endif
#if CC_MakeCredential == YES
    {TPM_CC_MakeCredential, "TPM_CC_MakeCredential"},
#endif
#if CC_NV_ReadPublic == YES
    {TPM_CC_NV_ReadPublic, "TPM_CC_NV_ReadPublic"},
#endif
#if CC_PolicyAuthorize == YES
    {TPM_CC_PolicyAuthorize, "TPM_CC_PolicyAuthorize"},
#endif
#if CC_PolicyAuthValue == YES
    {TPM_CC_PolicyAuthValue, "TPM_CC_PolicyAuthValue"},
#endif
#if CC_PolicyCommandCode == YES
    {TPM_CC_PolicyCommandCode, "TPM_CC_PolicyCommandCode"},
#endif
#if CC_PolicyCounterTimer == YES
    {TPM_CC_PolicyCounterTimer, "TPM_CC_PolicyCounterTimer"},
#endif
#if CC_PolicyCpHash == YES
    {TPM_CC_PolicyCpHash, "TPM_CC_PolicyCounterTimer"},
#endif
#if CC_PolicyLocality == YES
    {TPM_CC_PolicyLocality, "TPM_CC_PolicyLocality"},
#endif
#if CC_PolicyNameHash == YES
    {TPM_CC_PolicyNameHash, "TPM_CC_PolicyNameHash"},
#endif
#if CC_PolicyOR == YES
    {TPM_CC_PolicyOR, "TPM_CC_PolicyOR"},
#endif
#if CC_PolicyTicket == YES
    {TPM_CC_PolicyTicket, "TPM_CC_PolicyTicket"},
#endif
#if CC_ReadPublic == YES
    {TPM_CC_ReadPublic, "TPM_CC_ReadPublic"},
#endif
#if CC_RSA_Encrypt == YES
    {TPM_CC_RSA_Encrypt, "TPM_CC_RSA_Encrypt"},
#endif
#if CC_StartAuthSession == YES
    {TPM_CC_StartAuthSession, "TPM_CC_StartAuthSession"},
#endif
#if CC_VerifySignature == YES
    {TPM_CC_VerifySignature, "TPM_CC_VerifySignature"},
#endif
#if CC_ECC_Parameters == YES
    {TPM_CC_ECC_Parameters, "TPM_CC_VerifySignature"},
#endif
#if CC_FirmwareRead == YES
    {TPM_CC_FirmwareRead, "TPM_CC_FirmwareRead"},
#endif
#if CC_GetCapability == YES
    {TPM_CC_GetCapability, "TPM_CC_GetCapability"},
#endif
#if CC_GetRandom == YES
    {TPM_CC_GetRandom, "TPM_CC_GetRandom"},
#endif
#if CC_GetTestResult == YES
    {TPM_CC_GetTestResult, "TPM_CC_GetTestResult"},
#endif
#if CC_Hash == YES
    {TPM_CC_Hash, "TPM_CC_Hash"},
#endif
#if CC_PCR_Read == YES
    {TPM_CC_PCR_Read, "TPM_CC_Hash"},
#endif
#if CC_PolicyPCR == YES
    {TPM_CC_PolicyPCR, "TPM_CC_PolicyPCR"},
#endif
#if CC_PolicyRestart == YES
    {TPM_CC_PolicyRestart, "TPM_CC_PolicyRestart"},
#endif
#if CC_ReadClock == YES
    {TPM_CC_ReadClock, "TPM_CC_ReadClock"},
#endif
#if CC_PCR_Extend == YES
    {TPM_CC_PCR_Extend, "TPM_CC_PCR_Extend"},
#endif
#if CC_PCR_SetAuthValue == YES
    {TPM_CC_PCR_SetAuthValue, "TPM_CC_PCR_SetAuthValue"},
#endif
#if CC_NV_Certify == YES
    {TPM_CC_NV_Certify, "TPM_CC_NV_Certify"},
#endif
#if CC_EventSequenceComplete == YES
    {TPM_CC_EventSequenceComplete, "TPM_CC_EventSequenceComplete"},
#endif
#if CC_HashSequenceStart == YES
    {TPM_CC_HashSequenceStart, "TPM_CC_EventSequenceComplete"},
#endif
#if CC_PolicyPhysicalPresence == YES
    {TPM_CC_PolicyPhysicalPresence, ""},
#endif
#if CC_PolicyDuplicationSelect == YES
    {TPM_CC_PolicyDuplicationSelect, "TPM_CC_PolicyDuplicationSelect"},
#endif
#if CC_PolicyGetDigest == YES
    {TPM_CC_PolicyGetDigest, "TPM_CC_PolicyGetDigest"},
#endif
#if CC_TestParms == YES
    {TPM_CC_TestParms, "TPM_CC_TestParms"},
#endif
#if CC_Commit == YES
    {TPM_CC_Commit, "TPM_CC_Commit"},
#endif
#if CC_PolicyPassword == YES
    {TPM_CC_PolicyPassword, "TPM_CC_PolicyPassword"},
#endif
#if CC_ZGen_2Phase == YES
    {TPM_CC_ZGen_2Phase, "TPM_CC_ZGen_2Phase"},
#endif
#if CC_EC_Ephemeral == YES
    {TPM_CC_EC_Ephemeral, "TPM_CC_EC_Ephemeral"},
#endif
#if CC_PolicyNvWritten == YES
    {TPM_CC_PolicyNvWritten, "TPM_CC_PolicyNvWritten"},
#endif
#if CC_PolicyTemplate == YES
    {TPM_CC_PolicyTemplate, "TPM_CC_PolicyTemplate"},
#endif
#if CC_CreateLoaded == YES
    {TPM_CC_CreateLoaded, ""},
#endif
#if CC_PolicyAuthorizeNV == YES
    {TPM_CC_PolicyAuthorizeNV, "TPM_CC_PolicyAuthorizeNV"},
#endif
#if CC_EncryptDecrypt2 == YES
    {TPM_CC_EncryptDecrypt2, "TPM_CC_EncryptDecrypt2"},
#endif
#if CC_AC_GetCapability == YES
    {TPM_CC_AC_GetCapability, "TPM_CC_AC_GetCapability"},
#endif
#if CC_AC_Send == YES
    {TPM_CC_AC_Send, "TPM_CC_AC_Send"},
#endif
#if CC_Policy_AC_SendSelect == YES
    {TPM_CC_Policy_AC_SendSelect, "TPM_CC_Policy_AC_SendSelect"},
#endif
    {(uint32_t)-1, NULL}
};

const lookup_t tpm_rc_globalCodes[] = {
    {TPM_RC_SUCCESS, "TPM_RC_SUCCESS"},
    {TPM_RC_BAD_TAG, "TPM_RC_BAD_TAG"},
    {(uint32_t)-1, NULL}
};

const lookup_t tpm_rc_formatZeroCodes[] = {
    {TPM_RC_INITIALIZE, "TPM_RC_INITIALIZE"},
    {TPM_RC_FAILURE, "TPM_RC_FAILURE"},
    {TPM_RC_SEQUENCE, "TPM_RC_SEQUENCE"},
    {TPM_RC_PRIVATE, "TPM_RC_PRIVATE"},
    {TPM_RC_HMAC, "TPM_RC_HMAC"},
    {TPM_RC_DISABLED, "TPM_RC_DISABLED"},
    {TPM_RC_EXCLUSIVE, "TPM_RC_EXCLUSIVE"},
    {TPM_RC_AUTH_TYPE, "TPM_RC_AUTH_TYPE"},
    {TPM_RC_AUTH_MISSING, "TPM_RC_AUTH_MISSING"},
    {TPM_RC_POLICY, "TPM_RC_POLICY"},
    {TPM_RC_PCR, "TPM_RC_PCR"},
    {TPM_RC_PCR_CHANGED, "TPM_RC_PCR_CHANGED"},
    {TPM_RC_UPGRADE, "TPM_RC_UPGRADE"},
    {TPM_RC_TOO_MANY_CONTEXTS, "TPM_RC_TOO_MANY_CONTEXTS"},
    {TPM_RC_AUTH_UNAVAILABLE, "TPM_RC_AUTH_UNAVAILABLE"},
    {TPM_RC_REBOOT, "TPM_RC_REBOOT"},
    {TPM_RC_UNBALANCED, "TPM_RC_UNBALANCED"},
    {TPM_RC_COMMAND_SIZE, "TPM_RC_COMMAND_SIZE"},
    {TPM_RC_COMMAND_CODE, "TPM_RC_COMMAND_CODE"},
    {TPM_RC_AUTHSIZE, "TPM_RC_AUTHSIZE"},
    {TPM_RC_AUTH_CONTEXT, "TPM_RC_AUTH_CONTEXT"},
    {TPM_RC_NV_RANGE, "TPM_RC_NV_RANGE"},
    {TPM_RC_NV_SIZE, "TPM_RC_NV_SIZE"},
    {TPM_RC_NV_LOCKED, "TPM_RC_NV_LOCKED"},
    {TPM_RC_NV_AUTHORIZATION, "TPM_RC_NV_AUTHORIZATION"},
    {TPM_RC_NV_UNINITIALIZED, "TPM_RC_NV_UNINITIALIZED"},
    {TPM_RC_NV_SPACE, "TPM_RC_NV_SPACE"},
    {TPM_RC_NV_DEFINED, "TPM_RC_NV_DEFINED"},
    {TPM_RC_BAD_CONTEXT, "TPM_RC_BAD_CONTEXT"},
    {TPM_RC_CPHASH, "TPM_RC_CPHASH"},
    {TPM_RC_PARENT, "TPM_RC_PARENT"},
    {TPM_RC_NEEDS_TEST, "TPM_RC_NEEDS_TEST"},
    {TPM_RC_NO_RESULT, "TPM_RC_NO_RESULT"},
    {TPM_RC_SENSITIVE, "TPM_RC_SENSITIVE"},
    {(uint32_t)-1, NULL}
};

const lookup_t tpm_rc_warningCodes[] = {
    {TPM_RC_CONTEXT_GAP, "TPM_RC_CONTEXT_GAP"},
    {TPM_RC_CONTEXT_GAP, "TPM_RC_CONTEXT_GAP"},
    {TPM_RC_OBJECT_MEMORY, "TPM_RC_OBJECT_MEMORY"},
    {TPM_RC_SESSION_MEMORY, "TPM_RC_SESSION_MEMORY"},
    {TPM_RC_MEMORY, "TPM_RC_MEMORY"},
    {TPM_RC_SESSION_HANDLES, "TPM_RC_SESSION_HANDLES"},
    {TPM_RC_OBJECT_HANDLES, "TPM_RC_OBJECT_HANDLES"},
    {TPM_RC_LOCALITY, "TPM_RC_LOCALITY"},
    {TPM_RC_YIELDED, "TPM_RC_YIELDED"},
    {TPM_RC_CANCELED, "TPM_RC_CANCELED"},
    {TPM_RC_TESTING, "TPM_RC_TESTING"},
    {TPM_RC_REFERENCE_H0, "TPM_RC_REFERENCE_H0"},
    {TPM_RC_REFERENCE_H1, "TPM_RC_REFERENCE_H1"},
    {TPM_RC_REFERENCE_H2, "TPM_RC_REFERENCE_H2"},
    {TPM_RC_REFERENCE_H3, "TPM_RC_REFERENCE_H3"},
    {TPM_RC_REFERENCE_H4, "TPM_RC_REFERENCE_H4"},
    {TPM_RC_REFERENCE_H5, "TPM_RC_REFERENCE_H5"},
    {TPM_RC_REFERENCE_H6, "TPM_RC_REFERENCE_H6"},
    {TPM_RC_REFERENCE_S0, "TPM_RC_REFERENCE_S0"},
    {TPM_RC_REFERENCE_S1, "TPM_RC_REFERENCE_S1"},
    {TPM_RC_REFERENCE_S2, "TPM_RC_REFERENCE_S2"},
    {TPM_RC_REFERENCE_S3, "TPM_RC_REFERENCE_S3"},
    {TPM_RC_REFERENCE_S4, "TPM_RC_REFERENCE_S4"},
    {TPM_RC_REFERENCE_S5, "TPM_RC_REFERENCE_S5"},
    {TPM_RC_REFERENCE_S6, "TPM_RC_REFERENCE_S6"},
    {TPM_RC_NV_RATE, "TPM_RC_NV_RATE"},
    {TPM_RC_LOCKOUT, "TPM_RC_LOCKOUT"},
    {TPM_RC_RETRY, "TPM_RC_RETRY"},
    {TPM_RC_NV_UNAVAILABLE, "TPM_RC_NV_UNAVAILABLE"},
    {(uint32_t)-1, NULL}
};

const lookup_t tpm_rc_formatCodes[] = {
    {TPM_RCS_ASYMMETRIC, "TPM_RCS_ASYMMETRIC"},
    {TPM_RC_ATTRIBUTES, "TPM_RC_ATTRIBUTES"},
    {TPM_RCS_ATTRIBUTES, "TPM_RCS_ATTRIBUTES"},
    {TPM_RC_HASH, "TPM_RC_HASH"},
    {TPM_RCS_HASH, "TPM_RCS_HASH"},
    {TPM_RC_VALUE, "TPM_RC_VALUE"},
    {TPM_RCS_VALUE, "TPM_RCS_VALUE"},
    {TPM_RC_HIERARCHY, "TPM_RC_HIERARCHY"},
    {TPM_RCS_HIERARCHY, "TPM_RCS_HIERARCHY"},
    {TPM_RC_KEY_SIZE, "TPM_RC_KEY_SIZE"},
    {TPM_RCS_KEY_SIZE, "TPM_RCS_KEY_SIZE"},
    {TPM_RC_MGF, "TPM_RC_MGF"},
    {TPM_RCS_MGF, "TPM_RCS_MGF"},
    {TPM_RC_MODE, "TPM_RC_MODE"},
    {TPM_RCS_MODE, "TPM_RCS_MODE"},
    {TPM_RC_TYPE, "TPM_RC_TYPE"},
    {TPM_RCS_TYPE, "TPM_RCS_TYPE"},
    {TPM_RC_HANDLE, "TPM_RC_HANDLE"},
    {TPM_RCS_HANDLE, "TPM_RCS_HANDLE"},
    {TPM_RC_KDF, "TPM_RC_KDF"},
    {TPM_RCS_KDF, "TPM_RCS_KDF"},
    {TPM_RC_RANGE, "TPM_RC_RANGE"},
    {TPM_RCS_RANGE, "TPM_RCS_RANGE"},
    {TPM_RC_AUTH_FAIL, "TPM_RC_AUTH_FAIL"},
    {TPM_RCS_AUTH_FAIL, "TPM_RCS_AUTH_FAIL"},
    {TPM_RC_NONCE, "TPM_RC_NONCE"},
    {TPM_RCS_NONCE, "TPM_RCS_NONCE"},
    {TPM_RC_PP, "TPM_RC_PP"},
    {TPM_RCS_PP, "TPM_RCS_PP"},
    {TPM_RC_SCHEME, "TPM_RC_SCHEME"},
    {TPM_RCS_SCHEME, "TPM_RCS_SCHEME"},
    {TPM_RC_SIZE, "TPM_RC_SIZE"},
    {TPM_RCS_SIZE, "TPM_RCS_SIZE"},
    {TPM_RC_SYMMETRIC, "TPM_RC_SYMMETRIC"},
    {TPM_RCS_SYMMETRIC, "TPM_RCS_SYMMETRIC"},
    {TPM_RC_TAG, "TPM_RC_TAG"},
    {TPM_RCS_TAG, "TPM_RCS_TAG"},
    {TPM_RC_SELECTOR, "TPM_RC_SELECTOR"},
    {TPM_RCS_SELECTOR, "TPM_RCS_SELECTOR"},
    {TPM_RC_INSUFFICIENT, "TPM_RC_INSUFFICIENT"},
    {TPM_RCS_INSUFFICIENT, "TPM_RCS_INSUFFICIENT"},
    {TPM_RC_SIGNATURE, "TPM_RC_SIGNATURE"},
    {TPM_RCS_SIGNATURE, "TPM_RCS_SIGNATURE"},
    {TPM_RC_KEY, "TPM_RC_KEY"},
    {TPM_RCS_KEY, "TPM_RCS_KEY"},
    {TPM_RC_POLICY_FAIL, "TPM_RC_POLICY_FAIL"},
    {TPM_RCS_POLICY_FAIL, "TPM_RCS_POLICY_FAIL"},
    {TPM_RC_INTEGRITY, "TPM_RC_INTEGRITY"},
    {TPM_RCS_INTEGRITY, "TPM_RCS_INTEGRITY"},
    {TPM_RC_TICKET, "TPM_RC_TICKET"},
    {TPM_RCS_TICKET, "TPM_RCS_TICKET"},
    {TPM_RC_RESERVED_BITS, "TPM_RC_RESERVED_BITS"},
    {TPM_RCS_RESERVED_BITS, "TPM_RCS_RESERVED_BITS"},
    {TPM_RC_BAD_AUTH, "TPM_RC_BAD_AUTH"},
    {TPM_RCS_BAD_AUTH, "TPM_RCS_BAD_AUTH"},
    {TPM_RC_EXPIRED, "TPM_RC_EXPIRED"},
    {TPM_RCS_EXPIRED, "TPM_RCS_EXPIRED"},
    {TPM_RC_POLICY_CC, "TPM_RC_POLICY_CC"},
    {TPM_RCS_POLICY_CC, "TPM_RCS_POLICY_CC"},
    {TPM_RC_BINDING, "TPM_RC_BINDING"},
    {TPM_RCS_BINDING, "TPM_RCS_BINDING"},
    {TPM_RC_CURVE, "TPM_RC_CURVE"},
    {TPM_RCS_CURVE, "TPM_RCS_CURVE"},
    {TPM_RC_ECC_POINT, "TPM_RC_ECC_POINT"},
    {TPM_RCS_ECC_POINT, "TPM_RCS_ECC_POINT"},
    {(uint32_t)-1, NULL}
};

char decodeBuf[100];
#else
char decodeBuf[6];
#endif

static char* TpmDecodeTPM_CC(uint8_t* in)
{
    TPM_CC cc = BYTE_ARRAY_TO_UINT32(in);
#ifndef NDEBUG
    uint32_t n;
    for(n = 0; ((tpm_cc_table[n].index != (uint32_t)-1) && (tpm_cc_table[n].index != cc)) ; n++ );
    if(tpm_cc_table[n].index != (uint32_t)-1)
    {
        sprintf(decodeBuf, "%s()", tpm_cc_table[n].str);
    }
    else
    {
#endif
        sprintf(decodeBuf, "0x%03x", (unsigned int)cc);
#ifndef NDEBUG
    }
#endif
    return decodeBuf;
}

static char* TpmDecodeTPM_RC(uint8_t* in)
{
    TPM_RC rc = BYTE_ARRAY_TO_UINT32(in);
#ifndef NDEBUG
    uint32_t n;
    uint32_t cursor = 0;

    for(n = 0; ((tpm_rc_globalCodes[n].index != (uint32_t)-1) && (tpm_rc_globalCodes[n].index != rc)) ; n++ );
    if(tpm_rc_globalCodes[n].index != (uint32_t)-1)
    {
        cursor = sprintf(decodeBuf, "{%s}", tpm_rc_globalCodes[n].str);
    }
    else if((rc & RC_FMT1) == RC_FMT1)
    {
        if(rc & TPM_RC_P)
        {
            cursor = sprintf(decodeBuf, "{RC_FMT1 | TPM_RC_P | TPM_RC_%X | ", (unsigned int)((rc & 0x00000f00) >> 8));
        }
        else if(rc & TPM_RC_S)
        {
            cursor = sprintf(decodeBuf, "{RC_FMT1 | TPM_RC_S | TPM_RC_%X | ", (unsigned int)((rc & 0x00000700) >> 8));
        }
        else
        {
            cursor = sprintf(decodeBuf, "{RC_FMT1 | TPM_RC_H | TPM_RC_%X | ", (unsigned int)((rc & 0x00000700) >> 8));
        }

        for(n = 0; ((tpm_rc_formatCodes[n].index != (uint32_t)-1) && (tpm_rc_formatCodes[n].index != (rc & TPM_RC_MAX_FM1))) ; n++ );
        if(tpm_rc_formatCodes[n].index != (uint32_t)-1)
        {
            cursor = sprintf(&decodeBuf[cursor], "%s}", tpm_rc_formatCodes[n].str);
        }
        else
        {
            cursor = 0;
        }
    }
    else if((rc & RC_WARN) == RC_WARN)
    {
        for(n = 0; ((tpm_rc_warningCodes[n].index != (uint32_t)-1) && (tpm_rc_warningCodes[n].index != rc)) ; n++ );
        if(tpm_rc_warningCodes[n].index != (uint32_t)-1)
        {
            cursor = sprintf(decodeBuf, "{RC_VER1 | RC_WARN | %s}", tpm_rc_warningCodes[n].str);
        }
    }
    else if((rc & RC_VER1) == RC_VER1)
    {
        for(n = 0; ((tpm_rc_formatZeroCodes[n].index != (uint32_t)-1) && (tpm_rc_formatZeroCodes[n].index != rc)) ; n++ );
        if(tpm_rc_formatZeroCodes[n].index != (uint32_t)-1)
        {
            cursor = sprintf(decodeBuf, "{RC_VER1 | %s}", tpm_rc_formatZeroCodes[n].str);
        }
    }

    if(cursor == 0)
    {
#endif
        sprintf(decodeBuf, "0x%03x", (unsigned int)rc);
        return decodeBuf;
#ifndef NDEBUG
    }
#endif
    return decodeBuf;
}

static bool TpmGenerateUnique(void)
{
    wc_Sha512 hash;
    struct
    {
        uint16_t mcuType;
        uint16_t mcuRev;
        uint16_t flashSize;
        unsigned char serial[12];
    } mcuInfo;

    ReadMcuInfo(mcuInfo.serial, &mcuInfo.flashSize, &mcuInfo.mcuType, &mcuInfo.mcuRev);

    if((wc_InitSha512(&hash)) ||
       (wc_Sha512Update(&hash, (const byte*)&mcuInfo, sizeof(mcuInfo))) ||
       (wc_Sha512Final(&hash, (byte*)tpmUnique)))
    {
        logError("Sha512 failed\r\n");
        return false;
    }
    wc_Sha512Free(&hash);

#ifndef NDEBUG
    uint8_t unique[WC_SHA512_DIGEST_SIZE] = {0};
    _plat__GetUnique(0, sizeof(unique), unique);
    dbgPrint("Generated tpmUnique");
    for(uint32_t n = 0; n < sizeof(unique); n++)
    {
        if(!(n % 16)) dbgPrintAppend("\r\n    ");
        dbgPrintAppend("%02x", ((unsigned int)(unique[n])));
    }
    dbgPrintAppend("\r\n");
#endif
    return true;
}

bool TpmInitializeDevice(void)
{
    int retVal = 0;

    tpmOp.receivingCmd = -1;
    TpmGenerateUnique();

    SetDutyCycleIndicator(FALSE);

    // Factory reset requested?
    if(BlueButtonTransitionDetected())
    {
        dbgPrint("Factory reset requested.\r\n");
        if((retVal = _plat__NVEnable((void*)1)) < 0)
        {
            logError("_plat__NVEnable(1) failed unrecoverable.")
        }
        dbgPrint("Waiting for the button to be released...\r\n");
        while(BlueButtonTransitionDetected() == 0);
    }
    else
    {
        if((retVal = _plat__NVEnable((void*)0)) < 0)
        {
            logError("_plat__NVEnable(0) failed unrecoverable.")
        }
    }


    if(retVal > 0)
    {
        dbgPrint("TPM_Manufacture(1) requested.\r\n");
        if((retVal = TPM_Manufacture(1)) != 0)
        {
            logError("TPM_Manufacture(1) failed.\r\n");
        }
    }

    dbgPrint("_plat__SetNvAvail().\r\n");
    _plat__SetNvAvail();
    dbgPrint("_plat__Signal_PowerOn().\r\n");
    if((retVal =_plat__Signal_PowerOn()) != 0)
    {
        logError("_plat__Signal_PowerOn() failed.\r\n");
    }
    dbgPrint("_plat__Signal_Reset().\r\n");
    if((retVal =_plat__Signal_Reset()) != 0)
    {
        logError("_plat__Signal_Reset() failed.\r\n");
    }
    return (retVal == 0);
}

bool TpmOperationsLoop(void)
{
    // Device reset
    if(tpmOp.flags.resetRequested == 1)
    {
        tpmOp.flags.resetRequested = 0;

        HAL_Delay(1);
        dbgPrint("Executing _plat__Signal_PowerOff()\r\n");
        _plat__Signal_PowerOff();
        PerformSystemReset();
        return false;
    }

    if(tpmOp.flags.powerOffRequested == 1)
    {
        tpmOp.flags.powerOffRequested = 0;
        dbgPrint("Executing _plat__Signal_PowerOff()\r\n");
        _plat__Signal_PowerOff();
        KillUSBLink();
        return false;
    }

    // Physical presence button (blue button on the Nucleo)
    int ppButton = BlueButtonTransitionDetected();
    if(ppButton > 0)
    {
        dbgPrint("Executing _plat__Signal_PhysicalPresenceOn().\r\n");
        _plat__Signal_PhysicalPresenceOn();
    }
    else if (ppButton < 0)
    {
        dbgPrint("Executing _plat__Signal_PhysicalPresenceOff().\r\n");
        _plat__Signal_PhysicalPresenceOff();
    }

    // Command processing
    if(tpmOp.flags.executionRequested == 1)
    {
        tpmOp.flags.executionRequested = 0;
        unsigned int rspLenTPM = sizeof(tpmOp.msgBuf) - sizeof(rspLenTPM);
        unsigned char* rspTPM = (unsigned char*)&tpmOp.msgBuf[sizeof(rspLenTPM)];

        itmPrintAppend(ITMCMDRSP, "//%s\r\nunsigned char CmdBuf[%d] = {", GetLogStamp(), tpmOp.cmdSize);
        for(uint32_t n = 0; n < tpmOp.cmdSize; n++)
        {
            if(n > 0) itmPrintAppend(ITMCMDRSP, ", ");
            if(!(n % 16)) itmPrintAppend(ITMCMDRSP, "\r\n");
            itmPrintAppend(ITMCMDRSP, "0x%02x", tpmOp.msgBuf[n]);
        }
        itmPrintAppend(ITMCMDRSP, "\r\n};\r\n");

        SetDutyCycleIndicator(TRUE);
        dbgPrint("Executing command %s\r\n", TpmDecodeTPM_CC((uint8_t*)&tpmOp.msgBuf[6]));
        time_t execStart = time(NULL);
        _plat__RunCommand((unsigned int)tpmOp.cmdSize, (unsigned char*)tpmOp.msgBuf, &rspLenTPM, &rspTPM);
        *((unsigned int*)tpmOp.msgBuf) = rspLenTPM;
        time_t execEnd = time(NULL);
        dbgPrint("Completion time %u'%u\" with ReturnCode %s\r\n", (unsigned int)(execEnd - execStart) / 60, (unsigned int)(execEnd - execStart) % 60, TpmDecodeTPM_RC(&rspTPM[6]));
        SetDutyCycleIndicator(FALSE);

        itmPrintAppend(ITMCMDRSP, "//%s\r\nunsigned char RspBuf[%d] = {", GetLogStamp(), tpmOp.cmdSize);
        for(uint32_t n = 0; n < rspLenTPM; n++)
        {
            if(n > 0) itmPrintAppend(ITMCMDRSP, ", ");
            if(!(n % 16)) itmPrintAppend(ITMCMDRSP, "\r\n");
            itmPrintAppend(ITMCMDRSP, "0x%02x", rspTPM[n]);
        }
        itmPrintAppend(ITMCMDRSP, "\r\n};\r\n");

        tpmOp.rspSize = sizeof(rspLenTPM) + rspLenTPM;
        tpmOp.cmdSize = 0;
        tpmOp.flags.responseRequested = 1;
    }

    if(tpmOp.flags.responseRequested == 1)
    {
        tpmOp.flags.responseRequested = 0;
        if(tpmOp.rspSize > 0)
        {
            uint32_t chunk = 0;
            while(CDC_Transmit_FS((unsigned char*)&tpmOp.msgBuf, 0) != 0); // Wake up the link
            while(CDC_Transmit_FS((unsigned char*)&tpmOp.msgBuf, 14) != 0); // Send the header which is the minimum size
            for(uint32_t n = 14; n < tpmOp.rspSize; n += chunk) // Send the rest in 16 byte increments
            {
                chunk = MIN(16, tpmOp.rspSize - n);
                while(CDC_Transmit_FS((unsigned char*)&tpmOp.msgBuf[n], chunk) != 0);
//                dbgPrint("Sent(%u)\r\n", (unsigned int)(n + chunk));
            }
            itmPrint(ITMSIGNAL, "Response(%d)\r\n", tpmOp.rspSize);
        }
    }

    return true;
}

void TpmConnectionReset(void)
{
    tpmOp.receivingCmd = -1;
    tpmOp.cmdSize = 0;
    tpmOp.rspSize = 0;
    memset((void*)tpmOp.msgBuf, 0x00, sizeof(tpmOp.msgBuf));
}

bool TpmSignalEvent(uint8_t* Buf, uint32_t *Len)
{
    // Pending inbound transfer
    if(tpmOp.receivingCmd > 0)
    {
        memcpy((void*)&tpmOp.msgBuf[tpmOp.cmdSize], (void*)Buf, *Len);
        tpmOp.cmdSize += *Len;
//        itmPrint(ITMSIGNAL, "Received(%d)\r\n", tpmOp.cmdSize);
        if(tpmOp.cmdSize >= tpmOp.receivingCmd)
        {
            itmPrint(ITMSIGNAL, "Received(%d)\r\n", tpmOp.cmdSize);
            tpmOp.receivingCmd = -1;
            tpmOp.flags.executionRequested = 1;
        }
    }
    else if(sizeof(signalWrapper_t) > *Len)
    {
        itmPrint(ITMSIGNAL, "Invalid frame received.\r\n");
        return false;
    }
    else
    {
        pSignalWrapper_t sig = (pSignalWrapper_t)Buf;
        if(sig->s.magic == SIGNALMAGIC)
        {
            pSignalPayload_t payload;
            switch(sig->s.signal)
            {
                case SignalNothing:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalNothing(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalNothing\r\n");
                    break;

                case SignalShutdown:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalShutdown(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalShutdown\r\n");
                    tpmOp.flags.powerOffRequested = 1;
                    break;

                case SignalReset:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalReset(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalReset\r\n");
                    tpmOp.flags.resetRequested = 1;
                    break;

                case SignalSetClock:
                    if((sig->s.dataSize != sizeof(unsigned int)) || (*Len != sizeof(signalWrapper_t) + sizeof(unsigned int)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalSetClock(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    payload = (pSignalPayload_t)&Buf[sizeof(signalWrapper_t)];
                    SetRealTimeClock(payload->SignalSetClockPayload.time);
                    itmPrint(ITMSIGNAL, "SignalSetClock(0x%08x)\r\n", payload->SignalSetClockPayload.time);
                    break;

                case SignalCancelOn:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalCancelOn(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalCancelOn\r\n");
                    _plat__SetCancel();
                    break;

                case SignalCancelOff:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalCancelOff(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalCancelOff\r\n");
                    _plat__ClearCancel();
                    break;

                case SignalCommand:
                    if((sig->s.dataSize == 0) ||
                       (*Len == sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalCommand(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    payload = (pSignalPayload_t)&Buf[sizeof(signalWrapper_t)];
                    unsigned int expected = sizeof(signalWrapper_t) + sizeof(unsigned int) * 2 + payload->SignalCommandPayload.cmdSize;
                    unsigned int maxAllowed = sizeof(tpmOp.msgBuf);
                    memset((unsigned char*)tpmOp.msgBuf, 0x00, sizeof(tpmOp.msgBuf));
                    tpmOp.rspSize = 0;
                    itmPrint(ITMSIGNAL, "SignalCommand(%d)\r\n", payload->SignalCommandPayload.cmdSize);

                    // Set the locality for the command
                    if(_plat__LocalityGet() != payload->SignalCommandPayload.locality)
                    {
                        _plat__LocalitySet(payload->SignalCommandPayload.locality);
                        itmPrint(ITMSIGNAL, "SetLocality(%d)\r\n", payload->SignalCommandPayload.locality);
                    }

                    if((*Len == expected) &&
                       (payload->SignalCommandPayload.cmdSize <= maxAllowed))
                    {
                        memcpy((void*)tpmOp.msgBuf, (void*)payload->SignalCommandPayload.cmd, payload->SignalCommandPayload.cmdSize);
                        tpmOp.cmdSize = payload->SignalCommandPayload.cmdSize;
                        tpmOp.flags.executionRequested = 1;
//                        itmPrint(ITMSIGNAL, "Received(%d)\r\n", tpmOp.cmdSize);
                    }
                    else if((*Len < expected) &&
                            (payload->SignalCommandPayload.cmdSize <= maxAllowed))
                    {
                        unsigned int dataSnip = *Len - (sizeof(signalWrapper_t) + sizeof(unsigned int) * 2);
                        memcpy((void*)tpmOp.msgBuf, (void*)payload->SignalCommandPayload.cmd, dataSnip);
                        tpmOp.receivingCmd = payload->SignalCommandPayload.cmdSize;
                        tpmOp.cmdSize = dataSnip;
//                        itmPrint(ITMSIGNAL, "Received(%d)\r\n", tpmOp.cmdSize);
                    }
                    else
                    {
                        logError("Invalid command size.\r\n");
                        return false;
                    }
                    break;

                case SignalResponse:
                    if((sig->s.dataSize != 0) || (*Len != sizeof(signalWrapper_t)))
                    {
                        itmPrint(ITMSIGNAL, "Invalid data size %u for SignalResponse(%u).\r\n", (unsigned int)*Len, (unsigned int)sig->s.dataSize);
                        return false;
                    }
                    itmPrint(ITMSIGNAL, "SignalResponse\r\n");
                    if(tpmOp.rspSize > 0)
                    {
                        tpmOp.flags.responseRequested = 1;
                    }
                    break;

                default:
                    itmPrint(ITMSIGNAL, "Unknown Signal %u received.\r\n", sig->s.signal);
                    return false;
                    break;
            }
        }
    }
    return true;
}
