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
#ifndef _Table_Marshal_Data_
#define _Table_Marshal_Data_


// The datatype descriptions for each type if needed in addition to the
// default types.
typedef const struct TPM_ECC_CURVE_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPM_ECC_CURVE_mst;
typedef const struct TPM_CLOCK_ADJUST_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPM_CLOCK_ADJUST_mst;
typedef const struct TPM_EO_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPM_EO_mst;
typedef const struct TPM_SU_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPM_SU_mst;
typedef const struct TPM_SE_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[3];
} TPM_SE_mst;
typedef const struct TPM_CAP_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[3];
} TPM_CAP_mst;
typedef const struct TPMI_YES_NO_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_YES_NO_mst;
typedef const struct TPMI_DH_OBJECT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[5];
} TPMI_DH_OBJECT_mst;
typedef const struct TPMI_DH_PARENT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[8];
} TPMI_DH_PARENT_mst;
typedef const struct TPMI_DH_PERSISTENT_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPMI_DH_PERSISTENT_mst;
typedef const struct TPMI_DH_ENTITY_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[15];
} TPMI_DH_ENTITY_mst;
typedef const struct TPMI_DH_PCR_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[3];
} TPMI_DH_PCR_mst;
typedef const struct TPMI_SH_AUTH_SESSION_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[5];
} TPMI_SH_AUTH_SESSION_mst;
typedef const struct TPMI_SH_HMAC_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPMI_SH_HMAC_mst;
typedef const struct TPMI_SH_POLICY_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPMI_SH_POLICY_mst;
typedef const struct TPMI_DH_CONTEXT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[6];
} TPMI_DH_CONTEXT_mst;
typedef const struct TPMI_DH_SAVED_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[7];
} TPMI_DH_SAVED_mst;
typedef const struct TPMI_RH_HIERARCHY_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[4];
} TPMI_RH_HIERARCHY_mst;
typedef const struct TPMI_RH_ENABLES_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[5];
} TPMI_RH_ENABLES_mst;
typedef const struct TPMI_RH_HIERARCHY_AUTH_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[4];
} TPMI_RH_HIERARCHY_AUTH_mst;
typedef const struct TPMI_RH_PLATFORM_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[1];
} TPMI_RH_PLATFORM_mst;
typedef const struct TPMI_RH_OWNER_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_RH_OWNER_mst;
typedef const struct TPMI_RH_ENDORSEMENT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_RH_ENDORSEMENT_mst;
typedef const struct TPMI_RH_PROVISION_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_RH_PROVISION_mst;
typedef const struct TPMI_RH_CLEAR_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_RH_CLEAR_mst;
typedef const struct TPMI_RH_NV_AUTH_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[4];
} TPMI_RH_NV_AUTH_mst;
typedef const struct TPMI_RH_LOCKOUT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[1];
} TPMI_RH_LOCKOUT_mst;
typedef const struct TPMI_RH_NV_INDEX_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPMI_RH_NV_INDEX_mst;
typedef const struct TPMI_RH_AC_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} TPMI_RH_AC_mst;
typedef const struct TPMI_ALG_HASH_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[5];
} TPMI_ALG_HASH_mst;
typedef const struct TPMI_ALG_ASYM_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[5];
} TPMI_ALG_ASYM_mst;
typedef const struct TPMI_ALG_SYM_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[5];
} TPMI_ALG_SYM_mst;
typedef const struct TPMI_ALG_SYM_OBJECT_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[5];
} TPMI_ALG_SYM_OBJECT_mst;
typedef const struct TPMI_ALG_SYM_MODE_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_SYM_MODE_mst;
typedef const struct TPMI_ALG_KDF_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_KDF_mst;
typedef const struct TPMI_ALG_SIG_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_SIG_SCHEME_mst;
typedef const struct TPMI_ECC_KEY_EXCHANGE_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ECC_KEY_EXCHANGE_mst;
typedef const struct TPMI_ST_COMMAND_TAG_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_ST_COMMAND_TAG_mst;
typedef const struct TPMI_ALG_MAC_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[5];
} TPMI_ALG_MAC_SCHEME_mst;
typedef const struct TPMI_ALG_CIPHER_MODE_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_CIPHER_MODE_mst;
typedef const struct TPMS_EMPTY_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[3];
} TPMS_EMPTY_mst;
typedef const struct TPMS_ALGORITHM_DESCRIPTION_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_ALGORITHM_DESCRIPTION_mst;
typedef struct TPMU_HA_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[9];
    UINT16        marshalingTypes[9];
} TPMU_HA_mst;
typedef const struct TPMT_HA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_HA_mst;
typedef const struct TPMS_PCR_SELECT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_PCR_SELECT_mst;
typedef const struct TPMS_PCR_SELECTION_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMS_PCR_SELECTION_mst;
typedef const struct TPMT_TK_CREATION_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_TK_CREATION_mst;
typedef const struct TPMT_TK_VERIFIED_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_TK_VERIFIED_mst;
typedef const struct TPMT_TK_AUTH_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_TK_AUTH_mst;
typedef const struct TPMT_TK_HASHCHECK_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_TK_HASHCHECK_mst;
typedef const struct TPMS_ALG_PROPERTY_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_ALG_PROPERTY_mst;
typedef const struct TPMS_TAGGED_PROPERTY_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_TAGGED_PROPERTY_mst;
typedef const struct TPMS_TAGGED_PCR_SELECT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMS_TAGGED_PCR_SELECT_mst;
typedef const struct TPMS_TAGGED_POLICY_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_TAGGED_POLICY_mst;
typedef struct TPMU_CAPABILITIES_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[10];
    UINT16        marshalingTypes[10];
} TPMU_CAPABILITIES_mst;
typedef const struct TPMS_CAPABILITY_DATA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_CAPABILITY_DATA_mst;
typedef const struct TPMS_CLOCK_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_CLOCK_INFO_mst;
typedef const struct TPMS_TIME_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_TIME_INFO_mst;
typedef const struct TPMS_TIME_ATTEST_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_TIME_ATTEST_INFO_mst;
typedef const struct TPMS_CERTIFY_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_CERTIFY_INFO_mst;
typedef const struct TPMS_QUOTE_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_QUOTE_INFO_mst;
typedef const struct TPMS_COMMAND_AUDIT_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_COMMAND_AUDIT_INFO_mst;
typedef const struct TPMS_SESSION_AUDIT_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_SESSION_AUDIT_INFO_mst;
typedef const struct TPMS_CREATION_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_CREATION_INFO_mst;
typedef const struct TPMS_NV_CERTIFY_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMS_NV_CERTIFY_INFO_mst;
typedef const struct TPMS_NV_DIGEST_CERTIFY_INFO_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_NV_DIGEST_CERTIFY_INFO_mst;
typedef const struct TPMI_ST_ATTEST_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         ranges;
    UINT8         singles;
    UINT32        values[3];
} TPMI_ST_ATTEST_mst;
typedef struct TPMU_ATTEST_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[8];
    UINT16        marshalingTypes[8];
} TPMU_ATTEST_mst;
typedef const struct TPMS_ATTEST_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[21];
} TPMS_ATTEST_mst;
typedef const struct TPMS_AUTH_COMMAND_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_AUTH_COMMAND_mst;
typedef const struct TPMS_AUTH_RESPONSE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMS_AUTH_RESPONSE_mst;
typedef const struct TPMI_TDES_KEY_BITS_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[3];
} TPMI_TDES_KEY_BITS_mst;
typedef const struct TPMI_AES_KEY_BITS_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[4];
} TPMI_AES_KEY_BITS_mst;
typedef const struct TPMI_SM4_KEY_BITS_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} TPMI_SM4_KEY_BITS_mst;
typedef const struct TPMI_CAMELLIA_KEY_BITS_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[4];
} TPMI_CAMELLIA_KEY_BITS_mst;
typedef struct TPMU_SYM_KEY_BITS_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[6];
    UINT16        marshalingTypes[6];
} TPMU_SYM_KEY_BITS_mst;
typedef struct TPMU_SYM_MODE_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[6];
    UINT16        marshalingTypes[6];
} TPMU_SYM_MODE_mst;
typedef const struct TPMT_SYM_DEF_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_SYM_DEF_mst;
typedef const struct TPMT_SYM_DEF_OBJECT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMT_SYM_DEF_OBJECT_mst;
typedef const struct TPMS_SYMCIPHER_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[3];
} TPMS_SYMCIPHER_PARMS_mst;
typedef const struct TPMS_DERIVE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_DERIVE_mst;
typedef const struct TPMS_SENSITIVE_CREATE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_SENSITIVE_CREATE_mst;
typedef const struct TPMS_SCHEME_HASH_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[3];
} TPMS_SCHEME_HASH_mst;
typedef const struct TPMS_SCHEME_ECDAA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_SCHEME_ECDAA_mst;
typedef const struct TPMI_ALG_KEYEDHASH_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_KEYEDHASH_SCHEME_mst;
typedef const struct TPMS_SCHEME_XOR_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_SCHEME_XOR_mst;
typedef struct TPMU_SCHEME_KEYEDHASH_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[3];
    UINT16        marshalingTypes[3];
} TPMU_SCHEME_KEYEDHASH_mst;
typedef const struct TPMT_KEYEDHASH_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_KEYEDHASH_SCHEME_mst;
typedef struct TPMU_SIG_SCHEME_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[8];
    UINT16        marshalingTypes[8];
} TPMU_SIG_SCHEME_mst;
typedef const struct TPMT_SIG_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_SIG_SCHEME_mst;
typedef struct TPMU_KDF_SCHEME_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[5];
    UINT16        marshalingTypes[5];
} TPMU_KDF_SCHEME_mst;
typedef const struct TPMT_KDF_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_KDF_SCHEME_mst;
typedef const struct TPMI_ALG_ASYM_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_ASYM_SCHEME_mst;
typedef struct TPMU_ASYM_SCHEME_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[11];
    UINT16        marshalingTypes[11];
} TPMU_ASYM_SCHEME_mst;
typedef const struct TPMT_ASYM_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_ASYM_SCHEME_mst;
typedef const struct TPMI_ALG_RSA_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_RSA_SCHEME_mst;
typedef const struct TPMT_RSA_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_RSA_SCHEME_mst;
typedef const struct TPMI_ALG_RSA_DECRYPT_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_RSA_DECRYPT_mst;
typedef const struct TPMT_RSA_DECRYPT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_RSA_DECRYPT_mst;
typedef const struct TPMI_RSA_KEY_BITS_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[5];
} TPMI_RSA_KEY_BITS_mst;
typedef const struct TPMS_ECC_POINT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_ECC_POINT_mst;
typedef const struct TPMI_ALG_ECC_SCHEME_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_ECC_SCHEME_mst;
typedef const struct TPMI_ECC_CURVE_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[3];
} TPMI_ECC_CURVE_mst;
typedef const struct TPMT_ECC_SCHEME_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_ECC_SCHEME_mst;
typedef const struct TPMS_ALGORITHM_DETAIL_ECC_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[33];
} TPMS_ALGORITHM_DETAIL_ECC_mst;
typedef const struct TPMS_SIGNATURE_RSA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_SIGNATURE_RSA_mst;
typedef const struct TPMS_SIGNATURE_ECC_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} TPMS_SIGNATURE_ECC_mst;
typedef struct TPMU_SIGNATURE_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[8];
    UINT16        marshalingTypes[8];
} TPMU_SIGNATURE_mst;
typedef const struct TPMT_SIGNATURE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_SIGNATURE_mst;
typedef struct TPMU_ENCRYPTED_SECRET_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[4];
    UINT16        marshalingTypes[4];
} TPMU_ENCRYPTED_SECRET_mst;
typedef const struct TPMI_ALG_PUBLIC_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[4];
} TPMI_ALG_PUBLIC_mst;
typedef struct TPMU_PUBLIC_ID_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[4];
    UINT16        marshalingTypes[4];
} TPMU_PUBLIC_ID_mst;
typedef const struct TPMS_KEYEDHASH_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[3];
} TPMS_KEYEDHASH_PARMS_mst;
typedef const struct TPMS_ASYM_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_ASYM_PARMS_mst;
typedef const struct TPMS_RSA_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_RSA_PARMS_mst;
typedef const struct TPMS_ECC_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_ECC_PARMS_mst;
typedef struct TPMU_PUBLIC_PARMS_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[4];
    UINT16        marshalingTypes[4];
} TPMU_PUBLIC_PARMS_mst;
typedef const struct TPMT_PUBLIC_PARMS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMT_PUBLIC_PARMS_mst;
typedef const struct TPMT_PUBLIC_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[18];
} TPMT_PUBLIC_mst;
typedef struct TPMU_SENSITIVE_COMPOSITE_mst
{
    BYTE            countOfselectors;
    BYTE            modifiers;
    UINT16        offsetOfUnmarshalTypes;
    UINT32        selectors[4];
    UINT16        marshalingTypes[4];
} TPMU_SENSITIVE_COMPOSITE_mst;
typedef const struct TPMT_SENSITIVE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMT_SENSITIVE_mst;
typedef const struct _PRIVATE_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[9];
} _PRIVATE_mst;
typedef const struct TPMS_ID_OBJECT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_ID_OBJECT_mst;
typedef const struct TPMS_NV_PIN_COUNTER_PARAMETERS_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_NV_PIN_COUNTER_PARAMETERS_mst;
typedef const struct TPMS_NV_PUBLIC_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[15];
} TPMS_NV_PUBLIC_mst;
typedef const struct TPMS_CONTEXT_DATA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_CONTEXT_DATA_mst;
typedef const struct TPMS_CONTEXT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[12];
} TPMS_CONTEXT_mst;
typedef const struct TPMS_CREATION_DATA_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[21];
} TPMS_CREATION_DATA_mst;
typedef const struct TPM_AT_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[4];
} TPM_AT_mst;
typedef const struct TPMS_AC_OUTPUT_mst
{
    UINT8     marshalType;
    UINT8     elements;
    UINT16    values[6];
} TPMS_AC_OUTPUT_mst;
typedef const struct Type02_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type02_mst;
typedef const struct Type03_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type03_mst;
typedef const struct Type04_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type04_mst;
typedef const struct Type06_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type06_mst;
typedef const struct Type08_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type08_mst;
typedef const struct Type10_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[1];
} Type10_mst;
typedef const struct Type11_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[1];
} Type11_mst;
typedef const struct Type12_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[2];
} Type12_mst;
typedef const struct Type13_mst {
    UINT8         marshalType;
    UINT8         modifiers;
    UINT8         errorCode;
    UINT8         entries;
    UINT32        values[1];
} Type13_mst;
typedef const struct Type15_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type15_mst;
typedef const struct Type17_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type17_mst;
typedef const struct Type18_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type18_mst;
typedef const struct Type19_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type19_mst;
typedef const struct Type20_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type20_mst;
typedef const struct Type22_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type22_mst;
typedef const struct Type23_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type23_mst;
typedef const struct Type24_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type24_mst;
typedef const struct Type25_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type25_mst;
typedef const struct Type26_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type26_mst;
typedef const struct Type28_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type28_mst;
typedef const struct Type29_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type29_mst;
typedef const struct Type32_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type32_mst;
typedef const struct Type33_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type33_mst;
typedef const struct Type34_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type34_mst;
typedef const struct Type37_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type37_mst;
typedef const struct Type40_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type40_mst;
typedef const struct Type41_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type41_mst;
typedef const struct Type43_mst {
    UINT8       marshalType;
    UINT8       modifiers;
    UINT8       errorCode;
    UINT32      values[2];
} Type43_mst;

// Defines for array lookup
#define UINT8_ARRAY_MARSHAL_INDEX                   0   // 0x00
#define TPM_CC_ARRAY_MARSHAL_INDEX                  1   // 0x01
#define TPMA_CC_ARRAY_MARSHAL_INDEX                 2   // 0x02
#define TPM_ALG_ID_ARRAY_MARSHAL_INDEX              3   // 0x03
#define TPM_HANDLE_ARRAY_MARSHAL_INDEX              4   // 0x04
#define TPM2B_DIGEST_ARRAY_MARSHAL_INDEX            5   // 0x05
#define TPMT_HA_ARRAY_MARSHAL_INDEX                 6   // 0x06
#define TPMS_PCR_SELECTION_ARRAY_MARSHAL_INDEX      7   // 0x07
#define TPMS_ALG_PROPERTY_ARRAY_MARSHAL_INDEX       8   // 0x08
#define TPMS_TAGGED_PROPERTY_ARRAY_MARSHAL_INDEX    9   // 0x09
#define TPMS_TAGGED_PCR_SELECT_ARRAY_MARSHAL_INDEX  10  // 0x0A
#define TPM_ECC_CURVE_ARRAY_MARSHAL_INDEX           11  // 0x0B
#define TPMS_TAGGED_POLICY_ARRAY_MARSHAL_INDEX      12  // 0x0C
#define TPMS_AC_OUTPUT_ARRAY_MARSHAL_INDEX          13  // 0x0D


// The defines to connect a typename to an index in the MarshalLookupTable
#define UINT8_MARSHAL_INDEX                         0   // 0x00
#define BYTE_MARSHAL_INDEX                          UINT8_MARSHAL_INDEX
#define TPM_HT_MARSHAL_INDEX                        UINT8_MARSHAL_INDEX
#define TPMA_LOCALITY_MARSHAL_INDEX                 UINT8_MARSHAL_INDEX
#define UINT16_MARSHAL_INDEX                        1   // 0x01
#define TPM_KEY_SIZE_MARSHAL_INDEX                  UINT16_MARSHAL_INDEX
#define TPM_KEY_BITS_MARSHAL_INDEX                  UINT16_MARSHAL_INDEX
#define TPM_ALG_ID_MARSHAL_INDEX                    UINT16_MARSHAL_INDEX
#define TPM_ST_MARSHAL_INDEX                        UINT16_MARSHAL_INDEX
#define UINT32_MARSHAL_INDEX                        2   // 0x02
#define TPM_ALGORITHM_ID_MARSHAL_INDEX              UINT32_MARSHAL_INDEX
#define TPM_MODIFIER_INDICATOR_MARSHAL_INDEX        UINT32_MARSHAL_INDEX
#define TPM_AUTHORIZATION_SIZE_MARSHAL_INDEX        UINT32_MARSHAL_INDEX
#define TPM_PARAMETER_SIZE_MARSHAL_INDEX            UINT32_MARSHAL_INDEX
#define TPM_SPEC_MARSHAL_INDEX                      UINT32_MARSHAL_INDEX
#define TPM_GENERATED_MARSHAL_INDEX                 UINT32_MARSHAL_INDEX
#define TPM_CC_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPM_RC_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPM_PT_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPM_PT_PCR_MARSHAL_INDEX                    UINT32_MARSHAL_INDEX
#define TPM_PS_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPM_HANDLE_MARSHAL_INDEX                    UINT32_MARSHAL_INDEX
#define TPM_RH_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPM_HC_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define TPMA_PERMANENT_MARSHAL_INDEX                UINT32_MARSHAL_INDEX
#define TPMA_STARTUP_CLEAR_MARSHAL_INDEX            UINT32_MARSHAL_INDEX
#define TPMA_MEMORY_MARSHAL_INDEX                   UINT32_MARSHAL_INDEX
#define TPMA_CC_MARSHAL_INDEX                       UINT32_MARSHAL_INDEX
#define TPMA_MODES_MARSHAL_INDEX                    UINT32_MARSHAL_INDEX
#define TPMA_X509_KEY_USAGE_MARSHAL_INDEX           UINT32_MARSHAL_INDEX
#define TPM_NV_INDEX_MARSHAL_INDEX                  UINT32_MARSHAL_INDEX
#define TPM_AE_MARSHAL_INDEX                        UINT32_MARSHAL_INDEX
#define UINT64_MARSHAL_INDEX                        3   // 0x03
#define INT8_MARSHAL_INDEX                          4   // 0x04
#define INT16_MARSHAL_INDEX                         5   // 0x05
#define INT32_MARSHAL_INDEX                         6   // 0x06
#define INT64_MARSHAL_INDEX                         7   // 0x07
#define UINT0_MARSHAL_INDEX                         8   // 0x08
#define TPM_ECC_CURVE_MARSHAL_INDEX                 9   // 0x09
#define TPM_CLOCK_ADJUST_MARSHAL_INDEX              10  // 0x0A
#define TPM_EO_MARSHAL_INDEX                        11  // 0x0B
#define TPM_SU_MARSHAL_INDEX                        12  // 0x0C
#define TPM_SE_MARSHAL_INDEX                        13  // 0x0D
#define TPM_CAP_MARSHAL_INDEX                       14  // 0x0E
#define TPMA_ALGORITHM_MARSHAL_INDEX                15  // 0x0F
#define TPMA_OBJECT_MARSHAL_INDEX                   16  // 0x10
#define TPMA_SESSION_MARSHAL_INDEX                  17  // 0x11
#define TPMI_YES_NO_MARSHAL_INDEX                   18  // 0x12
#define TPMI_DH_OBJECT_MARSHAL_INDEX                19  // 0x13
#define TPMI_DH_PARENT_MARSHAL_INDEX                20  // 0x14
#define TPMI_DH_PERSISTENT_MARSHAL_INDEX            21  // 0x15
#define TPMI_DH_ENTITY_MARSHAL_INDEX                22  // 0x16
#define TPMI_DH_PCR_MARSHAL_INDEX                   23  // 0x17
#define TPMI_SH_AUTH_SESSION_MARSHAL_INDEX          24  // 0x18
#define TPMI_SH_HMAC_MARSHAL_INDEX                  25  // 0x19
#define TPMI_SH_POLICY_MARSHAL_INDEX                26  // 0x1A
#define TPMI_DH_CONTEXT_MARSHAL_INDEX               27  // 0x1B
#define TPMI_DH_SAVED_MARSHAL_INDEX                 28  // 0x1C
#define TPMI_RH_HIERARCHY_MARSHAL_INDEX             29  // 0x1D
#define TPMI_RH_ENABLES_MARSHAL_INDEX               30  // 0x1E
#define TPMI_RH_HIERARCHY_AUTH_MARSHAL_INDEX        31  // 0x1F
#define TPMI_RH_PLATFORM_MARSHAL_INDEX              32  // 0x20
#define TPMI_RH_OWNER_MARSHAL_INDEX                 33  // 0x21
#define TPMI_RH_ENDORSEMENT_MARSHAL_INDEX           34  // 0x22
#define TPMI_RH_PROVISION_MARSHAL_INDEX             35  // 0x23
#define TPMI_RH_CLEAR_MARSHAL_INDEX                 36  // 0x24
#define TPMI_RH_NV_AUTH_MARSHAL_INDEX               37  // 0x25
#define TPMI_RH_LOCKOUT_MARSHAL_INDEX               38  // 0x26
#define TPMI_RH_NV_INDEX_MARSHAL_INDEX              39  // 0x27
#define TPMI_RH_AC_MARSHAL_INDEX                    40  // 0x28
#define TPMI_ALG_HASH_MARSHAL_INDEX                 41  // 0x29
#define TPMI_ALG_ASYM_MARSHAL_INDEX                 42  // 0x2A
#define TPMI_ALG_SYM_MARSHAL_INDEX                  43  // 0x2B
#define TPMI_ALG_SYM_OBJECT_MARSHAL_INDEX           44  // 0x2C
#define TPMI_ALG_SYM_MODE_MARSHAL_INDEX             45  // 0x2D
#define TPMI_ALG_KDF_MARSHAL_INDEX                  46  // 0x2E
#define TPMI_ALG_SIG_SCHEME_MARSHAL_INDEX           47  // 0x2F
#define TPMI_ECC_KEY_EXCHANGE_MARSHAL_INDEX         48  // 0x30
#define TPMI_ST_COMMAND_TAG_MARSHAL_INDEX           49  // 0x31
#define TPMI_ALG_MAC_SCHEME_MARSHAL_INDEX           50  // 0x32
#define TPMI_ALG_CIPHER_MODE_MARSHAL_INDEX          51  // 0x33
#define TPMS_EMPTY_MARSHAL_INDEX                    52  // 0x34
#define TPMS_ENC_SCHEME_RSAES_MARSHAL_INDEX         TPMS_EMPTY_MARSHAL_INDEX
#define TPMS_ALGORITHM_DESCRIPTION_MARSHAL_INDEX    53  // 0x35
#define TPMU_HA_MARSHAL_INDEX                       54  // 0x36
#define TPMT_HA_MARSHAL_INDEX                       55  // 0x37
#define TPM2B_DIGEST_MARSHAL_INDEX                  56  // 0x38
#define TPM2B_NONCE_MARSHAL_INDEX                   TPM2B_DIGEST_MARSHAL_INDEX
#define TPM2B_AUTH_MARSHAL_INDEX                    TPM2B_DIGEST_MARSHAL_INDEX
#define TPM2B_OPERAND_MARSHAL_INDEX                 TPM2B_DIGEST_MARSHAL_INDEX
#define TPM2B_DATA_MARSHAL_INDEX                    57  // 0x39
#define TPM2B_EVENT_MARSHAL_INDEX                   58  // 0x3A
#define TPM2B_MAX_BUFFER_MARSHAL_INDEX              59  // 0x3B
#define TPM2B_MAX_NV_BUFFER_MARSHAL_INDEX           60  // 0x3C
#define TPM2B_TIMEOUT_MARSHAL_INDEX                 61  // 0x3D
#define TPM2B_IV_MARSHAL_INDEX                      62  // 0x3E
#define NULL_UNION_MARSHAL_INDEX                    63  // 0x3F
#define TPMU_NAME_MARSHAL_INDEX                     NULL_UNION_MARSHAL_INDEX
#define TPMU_SENSITIVE_CREATE_MARSHAL_INDEX         NULL_UNION_MARSHAL_INDEX
#define TPM2B_NAME_MARSHAL_INDEX                    64  // 0x40
#define TPMS_PCR_SELECT_MARSHAL_INDEX               65  // 0x41
#define TPMS_PCR_SELECTION_MARSHAL_INDEX            66  // 0x42
#define TPMT_TK_CREATION_MARSHAL_INDEX              67  // 0x43
#define TPMT_TK_VERIFIED_MARSHAL_INDEX              68  // 0x44
#define TPMT_TK_AUTH_MARSHAL_INDEX                  69  // 0x45
#define TPMT_TK_HASHCHECK_MARSHAL_INDEX             70  // 0x46
#define TPMS_ALG_PROPERTY_MARSHAL_INDEX             71  // 0x47
#define TPMS_TAGGED_PROPERTY_MARSHAL_INDEX          72  // 0x48
#define TPMS_TAGGED_PCR_SELECT_MARSHAL_INDEX        73  // 0x49
#define TPMS_TAGGED_POLICY_MARSHAL_INDEX            74  // 0x4A
#define TPML_CC_MARSHAL_INDEX                       75  // 0x4B
#define TPML_CCA_MARSHAL_INDEX                      76  // 0x4C
#define TPML_ALG_MARSHAL_INDEX                      77  // 0x4D
#define TPML_HANDLE_MARSHAL_INDEX                   78  // 0x4E
#define TPML_DIGEST_MARSHAL_INDEX                   79  // 0x4F
#define TPML_DIGEST_VALUES_MARSHAL_INDEX            80  // 0x50
#define TPML_PCR_SELECTION_MARSHAL_INDEX            81  // 0x51
#define TPML_ALG_PROPERTY_MARSHAL_INDEX             82  // 0x52
#define TPML_TAGGED_TPM_PROPERTY_MARSHAL_INDEX      83  // 0x53
#define TPML_TAGGED_PCR_PROPERTY_MARSHAL_INDEX      84  // 0x54
#define TPML_ECC_CURVE_MARSHAL_INDEX                85  // 0x55
#define TPML_TAGGED_POLICY_MARSHAL_INDEX            86  // 0x56
#define TPMU_CAPABILITIES_MARSHAL_INDEX             87  // 0x57
#define TPMS_CAPABILITY_DATA_MARSHAL_INDEX          88  // 0x58
#define TPMS_CLOCK_INFO_MARSHAL_INDEX               89  // 0x59
#define TPMS_TIME_INFO_MARSHAL_INDEX                90  // 0x5A
#define TPMS_TIME_ATTEST_INFO_MARSHAL_INDEX         91  // 0x5B
#define TPMS_CERTIFY_INFO_MARSHAL_INDEX             92  // 0x5C
#define TPMS_QUOTE_INFO_MARSHAL_INDEX               93  // 0x5D
#define TPMS_COMMAND_AUDIT_INFO_MARSHAL_INDEX       94  // 0x5E
#define TPMS_SESSION_AUDIT_INFO_MARSHAL_INDEX       95  // 0x5F
#define TPMS_CREATION_INFO_MARSHAL_INDEX            96  // 0x60
#define TPMS_NV_CERTIFY_INFO_MARSHAL_INDEX          97  // 0x61
#define TPMS_NV_DIGEST_CERTIFY_INFO_MARSHAL_INDEX   98  // 0x62
#define TPMI_ST_ATTEST_MARSHAL_INDEX                99  // 0x63
#define TPMU_ATTEST_MARSHAL_INDEX                   100 // 0x64
#define TPMS_ATTEST_MARSHAL_INDEX                   101 // 0x65
#define TPM2B_ATTEST_MARSHAL_INDEX                  102 // 0x66
#define TPMS_AUTH_COMMAND_MARSHAL_INDEX             103 // 0x67
#define TPMS_AUTH_RESPONSE_MARSHAL_INDEX            104 // 0x68
#define TPMI_TDES_KEY_BITS_MARSHAL_INDEX            105 // 0x69
#define TPMI_AES_KEY_BITS_MARSHAL_INDEX             106 // 0x6A
#define TPMI_SM4_KEY_BITS_MARSHAL_INDEX             107 // 0x6B
#define TPMI_CAMELLIA_KEY_BITS_MARSHAL_INDEX        108 // 0x6C
#define TPMU_SYM_KEY_BITS_MARSHAL_INDEX             109 // 0x6D
#define TPMU_SYM_MODE_MARSHAL_INDEX                 110 // 0x6E
#define TPMT_SYM_DEF_MARSHAL_INDEX                  111 // 0x6F
#define TPMT_SYM_DEF_OBJECT_MARSHAL_INDEX           112 // 0x70
#define TPM2B_SYM_KEY_MARSHAL_INDEX                 113 // 0x71
#define TPMS_SYMCIPHER_PARMS_MARSHAL_INDEX          114 // 0x72
#define TPM2B_LABEL_MARSHAL_INDEX                   115 // 0x73
#define TPMS_DERIVE_MARSHAL_INDEX                   116 // 0x74
#define TPM2B_DERIVE_MARSHAL_INDEX                  117 // 0x75
#define TPM2B_SENSITIVE_DATA_MARSHAL_INDEX          118 // 0x76
#define TPMS_SENSITIVE_CREATE_MARSHAL_INDEX         119 // 0x77
#define TPM2B_SENSITIVE_CREATE_MARSHAL_INDEX        120 // 0x78
#define TPMS_SCHEME_HASH_MARSHAL_INDEX              121 // 0x79
#define TPMS_SCHEME_HMAC_MARSHAL_INDEX              TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SIG_SCHEME_RSASSA_MARSHAL_INDEX        TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SIG_SCHEME_RSAPSS_MARSHAL_INDEX        TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SIG_SCHEME_ECDSA_MARSHAL_INDEX         TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SIG_SCHEME_SM2_MARSHAL_INDEX           TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SIG_SCHEME_ECSCHNORR_MARSHAL_INDEX     TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_ENC_SCHEME_OAEP_MARSHAL_INDEX          TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_KEY_SCHEME_ECDH_MARSHAL_INDEX          TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_KEY_SCHEME_ECMQV_MARSHAL_INDEX         TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SCHEME_MGF1_MARSHAL_INDEX              TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SCHEME_KDF1_SP800_56A_MARSHAL_INDEX    TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SCHEME_KDF2_MARSHAL_INDEX              TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SCHEME_KDF1_SP800_108_MARSHAL_INDEX    TPMS_SCHEME_HASH_MARSHAL_INDEX
#define TPMS_SCHEME_ECDAA_MARSHAL_INDEX             122 // 0x7A
#define TPMS_SIG_SCHEME_ECDAA_MARSHAL_INDEX         TPMS_SCHEME_ECDAA_MARSHAL_INDEX
#define TPMI_ALG_KEYEDHASH_SCHEME_MARSHAL_INDEX     123 // 0x7B
#define TPMS_SCHEME_XOR_MARSHAL_INDEX               124 // 0x7C
#define TPMU_SCHEME_KEYEDHASH_MARSHAL_INDEX         125 // 0x7D
#define TPMT_KEYEDHASH_SCHEME_MARSHAL_INDEX         126 // 0x7E
#define TPMU_SIG_SCHEME_MARSHAL_INDEX               127 // 0x7F
#define TPMT_SIG_SCHEME_MARSHAL_INDEX               128 // 0x80
#define TPMU_KDF_SCHEME_MARSHAL_INDEX               129 // 0x81
#define TPMT_KDF_SCHEME_MARSHAL_INDEX               130 // 0x82
#define TPMI_ALG_ASYM_SCHEME_MARSHAL_INDEX          131 // 0x83
#define TPMU_ASYM_SCHEME_MARSHAL_INDEX              132 // 0x84
#define TPMT_ASYM_SCHEME_MARSHAL_INDEX              133 // 0x85
#define TPMI_ALG_RSA_SCHEME_MARSHAL_INDEX           134 // 0x86
#define TPMT_RSA_SCHEME_MARSHAL_INDEX               135 // 0x87
#define TPMI_ALG_RSA_DECRYPT_MARSHAL_INDEX          136 // 0x88
#define TPMT_RSA_DECRYPT_MARSHAL_INDEX              137 // 0x89
#define TPM2B_PUBLIC_KEY_RSA_MARSHAL_INDEX          138 // 0x8A
#define TPMI_RSA_KEY_BITS_MARSHAL_INDEX             139 // 0x8B
#define TPM2B_PRIVATE_KEY_RSA_MARSHAL_INDEX         140 // 0x8C
#define TPM2B_ECC_PARAMETER_MARSHAL_INDEX           141 // 0x8D
#define TPMS_ECC_POINT_MARSHAL_INDEX                142 // 0x8E
#define TPM2B_ECC_POINT_MARSHAL_INDEX               143 // 0x8F
#define TPMI_ALG_ECC_SCHEME_MARSHAL_INDEX           144 // 0x90
#define TPMI_ECC_CURVE_MARSHAL_INDEX                145 // 0x91
#define TPMT_ECC_SCHEME_MARSHAL_INDEX               146 // 0x92
#define TPMS_ALGORITHM_DETAIL_ECC_MARSHAL_INDEX     147 // 0x93
#define TPMS_SIGNATURE_RSA_MARSHAL_INDEX            148 // 0x94
#define TPMS_SIGNATURE_RSASSA_MARSHAL_INDEX         TPMS_SIGNATURE_RSA_MARSHAL_INDEX
#define TPMS_SIGNATURE_RSAPSS_MARSHAL_INDEX         TPMS_SIGNATURE_RSA_MARSHAL_INDEX
#define TPMS_SIGNATURE_ECC_MARSHAL_INDEX            149 // 0x95
#define TPMS_SIGNATURE_ECDAA_MARSHAL_INDEX          TPMS_SIGNATURE_ECC_MARSHAL_INDEX
#define TPMS_SIGNATURE_ECDSA_MARSHAL_INDEX          TPMS_SIGNATURE_ECC_MARSHAL_INDEX
#define TPMS_SIGNATURE_SM2_MARSHAL_INDEX            TPMS_SIGNATURE_ECC_MARSHAL_INDEX
#define TPMS_SIGNATURE_ECSCHNORR_MARSHAL_INDEX      TPMS_SIGNATURE_ECC_MARSHAL_INDEX
#define TPMU_SIGNATURE_MARSHAL_INDEX                150 // 0x96
#define TPMT_SIGNATURE_MARSHAL_INDEX                151 // 0x97
#define TPMU_ENCRYPTED_SECRET_MARSHAL_INDEX         152 // 0x98
#define TPM2B_ENCRYPTED_SECRET_MARSHAL_INDEX        153 // 0x99
#define TPMI_ALG_PUBLIC_MARSHAL_INDEX               154 // 0x9A
#define TPMU_PUBLIC_ID_MARSHAL_INDEX                155 // 0x9B
#define TPMS_KEYEDHASH_PARMS_MARSHAL_INDEX          156 // 0x9C
#define TPMS_ASYM_PARMS_MARSHAL_INDEX               157 // 0x9D
#define TPMS_RSA_PARMS_MARSHAL_INDEX                158 // 0x9E
#define TPMS_ECC_PARMS_MARSHAL_INDEX                159 // 0x9F
#define TPMU_PUBLIC_PARMS_MARSHAL_INDEX             160 // 0xA0
#define TPMT_PUBLIC_PARMS_MARSHAL_INDEX             161 // 0xA1
#define TPMT_PUBLIC_MARSHAL_INDEX                   162 // 0xA2
#define TPM2B_PUBLIC_MARSHAL_INDEX                  163 // 0xA3
#define TPM2B_TEMPLATE_MARSHAL_INDEX                164 // 0xA4
#define TPM2B_PRIVATE_VENDOR_SPECIFIC_MARSHAL_INDEX 165 // 0xA5
#define TPMU_SENSITIVE_COMPOSITE_MARSHAL_INDEX      166 // 0xA6
#define TPMT_SENSITIVE_MARSHAL_INDEX                167 // 0xA7
#define TPM2B_SENSITIVE_MARSHAL_INDEX               168 // 0xA8
#define _PRIVATE_MARSHAL_INDEX                      169 // 0xA9
#define TPM2B_PRIVATE_MARSHAL_INDEX                 170 // 0xAA
#define TPMS_ID_OBJECT_MARSHAL_INDEX                171 // 0xAB
#define TPM2B_ID_OBJECT_MARSHAL_INDEX               172 // 0xAC
#define TPMS_NV_PIN_COUNTER_PARAMETERS_MARSHAL_INDEX    173 // 0xAD
#define TPMA_NV_MARSHAL_INDEX                       174 // 0xAE
#define TPMS_NV_PUBLIC_MARSHAL_INDEX                175 // 0xAF
#define TPM2B_NV_PUBLIC_MARSHAL_INDEX               176 // 0xB0
#define TPM2B_CONTEXT_SENSITIVE_MARSHAL_INDEX       177 // 0xB1
#define TPMS_CONTEXT_DATA_MARSHAL_INDEX             178 // 0xB2
#define TPM2B_CONTEXT_DATA_MARSHAL_INDEX            179 // 0xB3
#define TPMS_CONTEXT_MARSHAL_INDEX                  180 // 0xB4
#define TPMS_CREATION_DATA_MARSHAL_INDEX            181 // 0xB5
#define TPM2B_CREATION_DATA_MARSHAL_INDEX           182 // 0xB6
#define TPM_AT_MARSHAL_INDEX                        183 // 0xB7
#define TPMS_AC_OUTPUT_MARSHAL_INDEX                184 // 0xB8
#define TPML_AC_CAPABILITIES_MARSHAL_INDEX          185 // 0xB9
#define Type00_MARSHAL_INDEX                        186 // 0xBA
#define Type01_MARSHAL_INDEX                        187 // 0xBB
#define Type02_MARSHAL_INDEX                        188 // 0xBC
#define Type03_MARSHAL_INDEX                        189 // 0xBD
#define Type04_MARSHAL_INDEX                        190 // 0xBE
#define Type05_MARSHAL_INDEX                        191 // 0xBF
#define Type06_MARSHAL_INDEX                        192 // 0xC0
#define Type07_MARSHAL_INDEX                        193 // 0xC1
#define Type08_MARSHAL_INDEX                        194 // 0xC2
#define Type09_MARSHAL_INDEX                        Type08_MARSHAL_INDEX
#define Type14_MARSHAL_INDEX                        Type08_MARSHAL_INDEX
#define Type10_MARSHAL_INDEX                        195 // 0xC3
#define Type11_MARSHAL_INDEX                        196 // 0xC4
#define Type12_MARSHAL_INDEX                        197 // 0xC5
#define Type13_MARSHAL_INDEX                        198 // 0xC6
#define Type15_MARSHAL_INDEX                        199 // 0xC7
#define Type16_MARSHAL_INDEX                        Type15_MARSHAL_INDEX
#define Type17_MARSHAL_INDEX                        200 // 0xC8
#define Type18_MARSHAL_INDEX                        201 // 0xC9
#define Type19_MARSHAL_INDEX                        202 // 0xCA
#define Type20_MARSHAL_INDEX                        203 // 0xCB
#define Type21_MARSHAL_INDEX                        Type20_MARSHAL_INDEX
#define Type22_MARSHAL_INDEX                        204 // 0xCC
#define Type23_MARSHAL_INDEX                        205 // 0xCD
#define Type24_MARSHAL_INDEX                        206 // 0xCE
#define Type25_MARSHAL_INDEX                        207 // 0xCF
#define Type26_MARSHAL_INDEX                        208 // 0xD0
#define Type27_MARSHAL_INDEX                        209 // 0xD1
#define Type28_MARSHAL_INDEX                        210 // 0xD2
#define Type29_MARSHAL_INDEX                        211 // 0xD3
#define Type30_MARSHAL_INDEX                        212 // 0xD4
#define Type31_MARSHAL_INDEX                        213 // 0xD5
#define Type32_MARSHAL_INDEX                        214 // 0xD6
#define Type33_MARSHAL_INDEX                        215 // 0xD7
#define Type34_MARSHAL_INDEX                        216 // 0xD8
#define Type35_MARSHAL_INDEX                        217 // 0xD9
#define Type36_MARSHAL_INDEX                        218 // 0xDA
#define Type37_MARSHAL_INDEX                        219 // 0xDB
#define Type38_MARSHAL_INDEX                        220 // 0xDC
#define Type39_MARSHAL_INDEX                        221 // 0xDD
#define Type40_MARSHAL_INDEX                        222 // 0xDE
#define Type41_MARSHAL_INDEX                        223 // 0xDF
#define Type42_MARSHAL_INDEX                        224 // 0xE0
#define Type43_MARSHAL_INDEX                        225 // 0xE1


//#defines to change calling sequence for code using marshaling
#define UINT8_Unmarshal(target, buffer, size)                                       \
    Unmarshal(UINT8_MARSHAL_INDEX, (target), (buffer), (size))
#define UINT8_Marshal(source, buffer, size)                                         \
    Marshal(UINT8_MARSHAL_INDEX, (source), (buffer), (size))
#define BYTE_Unmarshal(target, buffer, size)                                        \
    Unmarshal(UINT8_MARSHAL_INDEX, (target), (buffer), (size))
#define BYTE_Marshal(source, buffer, size)                                          \
    Marshal(UINT8_MARSHAL_INDEX, (source), (buffer), (size))
#define INT8_Unmarshal(target, buffer, size)                                        \
    Unmarshal(INT8_MARSHAL_INDEX, (target), (buffer), (size))
#define INT8_Marshal(source, buffer, size)                                          \
    Marshal(INT8_MARSHAL_INDEX, (source), (buffer), (size))
#define UINT16_Unmarshal(target, buffer, size)                                      \
    Unmarshal(UINT16_MARSHAL_INDEX, (target), (buffer), (size))
#define UINT16_Marshal(source, buffer, size)                                        \
    Marshal(UINT16_MARSHAL_INDEX, (source), (buffer), (size))
#define INT16_Unmarshal(target, buffer, size)                                       \
    Unmarshal(INT16_MARSHAL_INDEX, (target), (buffer), (size))
#define INT16_Marshal(source, buffer, size)                                         \
    Marshal(INT16_MARSHAL_INDEX, (source), (buffer), (size))
#define UINT32_Unmarshal(target, buffer, size)                                      \
    Unmarshal(UINT32_MARSHAL_INDEX, (target), (buffer), (size))
#define UINT32_Marshal(source, buffer, size)                                        \
    Marshal(UINT32_MARSHAL_INDEX, (source), (buffer), (size))
#define INT32_Unmarshal(target, buffer, size)                                       \
    Unmarshal(INT32_MARSHAL_INDEX, (target), (buffer), (size))
#define INT32_Marshal(source, buffer, size)                                         \
    Marshal(INT32_MARSHAL_INDEX, (source), (buffer), (size))
#define UINT64_Unmarshal(target, buffer, size)                                      \
    Unmarshal(UINT64_MARSHAL_INDEX, (target), (buffer), (size))
#define UINT64_Marshal(source, buffer, size)                                        \
    Marshal(UINT64_MARSHAL_INDEX, (source), (buffer), (size))
#define INT64_Unmarshal(target, buffer, size)                                       \
    Unmarshal(INT64_MARSHAL_INDEX, (target), (buffer), (size))
#define INT64_Marshal(source, buffer, size)                                         \
    Marshal(INT64_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_ALGORITHM_ID_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPM_ALGORITHM_ID_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_ALGORITHM_ID_Marshal(source, buffer, size)                              \
    Marshal(TPM_ALGORITHM_ID_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_MODIFIER_INDICATOR_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPM_MODIFIER_INDICATOR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_MODIFIER_INDICATOR_Marshal(source, buffer, size)                        \
    Marshal(TPM_MODIFIER_INDICATOR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_AUTHORIZATION_SIZE_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPM_AUTHORIZATION_SIZE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_AUTHORIZATION_SIZE_Marshal(source, buffer, size)                        \
    Marshal(TPM_AUTHORIZATION_SIZE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_PARAMETER_SIZE_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPM_PARAMETER_SIZE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_PARAMETER_SIZE_Marshal(source, buffer, size)                            \
    Marshal(TPM_PARAMETER_SIZE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_KEY_SIZE_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPM_KEY_SIZE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_KEY_SIZE_Marshal(source, buffer, size)                                  \
    Marshal(TPM_KEY_SIZE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_KEY_BITS_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPM_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_KEY_BITS_Marshal(source, buffer, size)                                  \
    Marshal(TPM_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_GENERATED_Marshal(source, buffer, size)                                 \
    Marshal(TPM_GENERATED_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_ALG_ID_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM_ALG_ID_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_ALG_ID_Marshal(source, buffer, size)                                    \
    Marshal(TPM_ALG_ID_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_ECC_CURVE_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPM_ECC_CURVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_ECC_CURVE_Marshal(source, buffer, size)                                 \
    Marshal(TPM_ECC_CURVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_CC_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_CC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_CC_Marshal(source, buffer, size)                                        \
    Marshal(TPM_CC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_RC_Marshal(source, buffer, size)                                        \
    Marshal(TPM_RC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_CLOCK_ADJUST_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPM_CLOCK_ADJUST_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_EO_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_EO_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_EO_Marshal(source, buffer, size)                                        \
    Marshal(TPM_EO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_ST_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_ST_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_ST_Marshal(source, buffer, size)                                        \
    Marshal(TPM_ST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_SU_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_SU_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_SE_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_SE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_CAP_Unmarshal(target, buffer, size)                                     \
    Unmarshal(TPM_CAP_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_CAP_Marshal(source, buffer, size)                                       \
    Marshal(TPM_CAP_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_PT_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_PT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_PT_Marshal(source, buffer, size)                                        \
    Marshal(TPM_PT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_PT_PCR_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM_PT_PCR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_PT_PCR_Marshal(source, buffer, size)                                    \
    Marshal(TPM_PT_PCR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_PS_Marshal(source, buffer, size)                                        \
    Marshal(TPM_PS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_HANDLE_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM_HANDLE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_HANDLE_Marshal(source, buffer, size)                                    \
    Marshal(TPM_HANDLE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_HT_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_HT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_HT_Marshal(source, buffer, size)                                        \
    Marshal(TPM_HT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_RH_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_RH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_RH_Marshal(source, buffer, size)                                        \
    Marshal(TPM_RH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_HC_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_HC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_HC_Marshal(source, buffer, size)                                        \
    Marshal(TPM_HC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_ALGORITHM_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMA_ALGORITHM_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMA_ALGORITHM_Marshal(source, buffer, size)                                \
    Marshal(TPMA_ALGORITHM_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_OBJECT_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPMA_OBJECT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMA_OBJECT_Marshal(source, buffer, size)                                   \
    Marshal(TPMA_OBJECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_SESSION_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPMA_SESSION_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMA_SESSION_Marshal(source, buffer, size)                                  \
    Marshal(TPMA_SESSION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_LOCALITY_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPMA_LOCALITY_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMA_LOCALITY_Marshal(source, buffer, size)                                 \
    Marshal(TPMA_LOCALITY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_PERMANENT_Marshal(source, buffer, size)                                \
    Marshal(TPMA_PERMANENT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_STARTUP_CLEAR_Marshal(source, buffer, size)                            \
    Marshal(TPMA_STARTUP_CLEAR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_MEMORY_Marshal(source, buffer, size)                                   \
    Marshal(TPMA_MEMORY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_CC_Marshal(source, buffer, size)                                       \
    Marshal(TPMA_CC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_MODES_Marshal(source, buffer, size)                                    \
    Marshal(TPMA_MODES_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMA_X509_KEY_USAGE_Marshal(source, buffer, size)                           \
    Marshal(TPMA_X509_KEY_USAGE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_YES_NO_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPMI_YES_NO_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_YES_NO_Marshal(source, buffer, size)                                   \
    Marshal(TPMI_YES_NO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_OBJECT_Unmarshal(target, buffer, size, flag)                        \
    Unmarshal(TPMI_DH_OBJECT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),      \
      (buffer), (size))
#define TPMI_DH_OBJECT_Marshal(source, buffer, size)                                \
    Marshal(TPMI_DH_OBJECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_PARENT_Unmarshal(target, buffer, size, flag)                        \
    Unmarshal(TPMI_DH_PARENT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),      \
      (buffer), (size))
#define TPMI_DH_PARENT_Marshal(source, buffer, size)                                \
    Marshal(TPMI_DH_PARENT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_PERSISTENT_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMI_DH_PERSISTENT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_DH_PERSISTENT_Marshal(source, buffer, size)                            \
    Marshal(TPMI_DH_PERSISTENT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_ENTITY_Unmarshal(target, buffer, size, flag)                        \
    Unmarshal(TPMI_DH_ENTITY_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),      \
      (buffer), (size))
#define TPMI_DH_PCR_Unmarshal(target, buffer, size, flag)                           \
    Unmarshal(TPMI_DH_PCR_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),         \
      (buffer), (size))
#define TPMI_SH_AUTH_SESSION_Unmarshal(target, buffer, size, flag)                  \
    Unmarshal(TPMI_SH_AUTH_SESSION_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),\
      (buffer), (size))
#define TPMI_SH_AUTH_SESSION_Marshal(source, buffer, size)                          \
    Marshal(TPMI_SH_AUTH_SESSION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_SH_HMAC_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPMI_SH_HMAC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_SH_HMAC_Marshal(source, buffer, size)                                  \
    Marshal(TPMI_SH_HMAC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_SH_POLICY_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMI_SH_POLICY_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_SH_POLICY_Marshal(source, buffer, size)                                \
    Marshal(TPMI_SH_POLICY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_CONTEXT_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMI_DH_CONTEXT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_DH_CONTEXT_Marshal(source, buffer, size)                               \
    Marshal(TPMI_DH_CONTEXT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_DH_SAVED_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPMI_DH_SAVED_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_DH_SAVED_Marshal(source, buffer, size)                                 \
    Marshal(TPMI_DH_SAVED_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_RH_HIERARCHY_Unmarshal(target, buffer, size, flag)                     \
    Unmarshal(TPMI_RH_HIERARCHY_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),   \
      (buffer), (size))
#define TPMI_RH_HIERARCHY_Marshal(source, buffer, size)                             \
    Marshal(TPMI_RH_HIERARCHY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_RH_ENABLES_Unmarshal(target, buffer, size, flag)                       \
    Unmarshal(TPMI_RH_ENABLES_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),     \
      (buffer), (size))
#define TPMI_RH_ENABLES_Marshal(source, buffer, size)                               \
    Marshal(TPMI_RH_ENABLES_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_RH_HIERARCHY_AUTH_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPMI_RH_HIERARCHY_AUTH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_PLATFORM_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMI_RH_PLATFORM_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_OWNER_Unmarshal(target, buffer, size, flag)                         \
    Unmarshal(TPMI_RH_OWNER_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),       \
      (buffer), (size))
#define TPMI_RH_ENDORSEMENT_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_RH_ENDORSEMENT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_RH_PROVISION_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMI_RH_PROVISION_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_CLEAR_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPMI_RH_CLEAR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_NV_AUTH_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMI_RH_NV_AUTH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_LOCKOUT_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMI_RH_LOCKOUT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_NV_INDEX_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMI_RH_NV_INDEX_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RH_NV_INDEX_Marshal(source, buffer, size)                              \
    Marshal(TPMI_RH_NV_INDEX_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_RH_AC_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPMI_RH_AC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_ALG_HASH_Unmarshal(target, buffer, size, flag)                         \
    Unmarshal(TPMI_ALG_HASH_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),       \
      (buffer), (size))
#define TPMI_ALG_HASH_Marshal(source, buffer, size)                                 \
    Marshal(TPMI_ALG_HASH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_ASYM_Unmarshal(target, buffer, size, flag)                         \
    Unmarshal(TPMI_ALG_ASYM_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),       \
      (buffer), (size))
#define TPMI_ALG_ASYM_Marshal(source, buffer, size)                                 \
    Marshal(TPMI_ALG_ASYM_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_SYM_Unmarshal(target, buffer, size, flag)                          \
    Unmarshal(TPMI_ALG_SYM_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),        \
      (buffer), (size))
#define TPMI_ALG_SYM_Marshal(source, buffer, size)                                  \
    Marshal(TPMI_ALG_SYM_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_SYM_OBJECT_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_ALG_SYM_OBJECT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_ALG_SYM_OBJECT_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ALG_SYM_OBJECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_SYM_MODE_Unmarshal(target, buffer, size, flag)                     \
    Unmarshal(TPMI_ALG_SYM_MODE_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),   \
      (buffer), (size))
#define TPMI_ALG_SYM_MODE_Marshal(source, buffer, size)                             \
    Marshal(TPMI_ALG_SYM_MODE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_KDF_Unmarshal(target, buffer, size, flag)                          \
    Unmarshal(TPMI_ALG_KDF_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),        \
      (buffer), (size))
#define TPMI_ALG_KDF_Marshal(source, buffer, size)                                  \
    Marshal(TPMI_ALG_KDF_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_SIG_SCHEME_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_ALG_SIG_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_ALG_SIG_SCHEME_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ALG_SIG_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ECC_KEY_EXCHANGE_Unmarshal(target, buffer, size, flag)                 \
    Unmarshal(TPMI_ECC_KEY_EXCHANGE_MARSHAL_INDEX | (flag ? NULL_FLAG : 0),         \
      (target), (buffer), (size))
#define TPMI_ECC_KEY_EXCHANGE_Marshal(source, buffer, size)                         \
    Marshal(TPMI_ECC_KEY_EXCHANGE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ST_COMMAND_TAG_Unmarshal(target, buffer, size)                         \
    Unmarshal(TPMI_ST_COMMAND_TAG_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_ST_COMMAND_TAG_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ST_COMMAND_TAG_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_MAC_SCHEME_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_ALG_MAC_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_ALG_MAC_SCHEME_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ALG_MAC_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_CIPHER_MODE_Unmarshal(target, buffer, size, flag)                  \
    Unmarshal(TPMI_ALG_CIPHER_MODE_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),\
      (buffer), (size))
#define TPMI_ALG_CIPHER_MODE_Marshal(source, buffer, size)                          \
    Marshal(TPMI_ALG_CIPHER_MODE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_EMPTY_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPMS_EMPTY_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_EMPTY_Marshal(source, buffer, size)                                    \
    Marshal(TPMS_EMPTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ALGORITHM_DESCRIPTION_Marshal(source, buffer, size)                    \
    Marshal(TPMS_ALGORITHM_DESCRIPTION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_HA_Unmarshal(target, buffer, size, selector)                           \
    UnmarshalUnion(TPMU_HA_MARSHAL_INDEX, (target), (buffer), (size), (selector))
#define TPMU_HA_Marshal(source, buffer, size, selector)                             \
    MarshalUnion(TPMU_HA_MARSHAL_INDEX, (target), (buffer), (size), (selector))
#define TPMT_HA_Unmarshal(target, buffer, size, flag)                               \
    Unmarshal(TPMT_HA_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), (buffer),   \
      (size))
#define TPMT_HA_Marshal(source, buffer, size)                                       \
    Marshal(TPMT_HA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_DIGEST_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPM2B_DIGEST_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_DIGEST_Marshal(source, buffer, size)                                  \
    Marshal(TPM2B_DIGEST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_DATA_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM2B_DATA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_DATA_Marshal(source, buffer, size)                                    \
    Marshal(TPM2B_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_NONCE_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPM2B_NONCE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_NONCE_Marshal(source, buffer, size)                                   \
    Marshal(TPM2B_NONCE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_AUTH_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM2B_AUTH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_AUTH_Marshal(source, buffer, size)                                    \
    Marshal(TPM2B_AUTH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_OPERAND_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPM2B_OPERAND_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_OPERAND_Marshal(source, buffer, size)                                 \
    Marshal(TPM2B_OPERAND_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_EVENT_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPM2B_EVENT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_EVENT_Marshal(source, buffer, size)                                   \
    Marshal(TPM2B_EVENT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_MAX_BUFFER_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPM2B_MAX_BUFFER_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_MAX_BUFFER_Marshal(source, buffer, size)                              \
    Marshal(TPM2B_MAX_BUFFER_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_MAX_NV_BUFFER_Unmarshal(target, buffer, size)                         \
    Unmarshal(TPM2B_MAX_NV_BUFFER_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_MAX_NV_BUFFER_Marshal(source, buffer, size)                           \
    Marshal(TPM2B_MAX_NV_BUFFER_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_TIMEOUT_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPM2B_TIMEOUT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_TIMEOUT_Marshal(source, buffer, size)                                 \
    Marshal(TPM2B_TIMEOUT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_IV_Unmarshal(target, buffer, size)                                    \
    Unmarshal(TPM2B_IV_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_IV_Marshal(source, buffer, size)                                      \
    Marshal(TPM2B_IV_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_NAME_Unmarshal(target, buffer, size)                                  \
    Unmarshal(TPM2B_NAME_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_NAME_Marshal(source, buffer, size)                                    \
    Marshal(TPM2B_NAME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_PCR_SELECT_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMS_PCR_SELECT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_PCR_SELECT_Marshal(source, buffer, size)                               \
    Marshal(TPMS_PCR_SELECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_PCR_SELECTION_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMS_PCR_SELECTION_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_PCR_SELECTION_Marshal(source, buffer, size)                            \
    Marshal(TPMS_PCR_SELECTION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_TK_CREATION_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMT_TK_CREATION_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_TK_CREATION_Marshal(source, buffer, size)                              \
    Marshal(TPMT_TK_CREATION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_TK_VERIFIED_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMT_TK_VERIFIED_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_TK_VERIFIED_Marshal(source, buffer, size)                              \
    Marshal(TPMT_TK_VERIFIED_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_TK_AUTH_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPMT_TK_AUTH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_TK_AUTH_Marshal(source, buffer, size)                                  \
    Marshal(TPMT_TK_AUTH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_TK_HASHCHECK_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMT_TK_HASHCHECK_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_TK_HASHCHECK_Marshal(source, buffer, size)                             \
    Marshal(TPMT_TK_HASHCHECK_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ALG_PROPERTY_Marshal(source, buffer, size)                             \
    Marshal(TPMS_ALG_PROPERTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_TAGGED_PROPERTY_Marshal(source, buffer, size)                          \
    Marshal(TPMS_TAGGED_PROPERTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_TAGGED_PCR_SELECT_Marshal(source, buffer, size)                        \
    Marshal(TPMS_TAGGED_PCR_SELECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_TAGGED_POLICY_Marshal(source, buffer, size)                            \
    Marshal(TPMS_TAGGED_POLICY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_CC_Unmarshal(target, buffer, size)                                     \
    Unmarshal(TPML_CC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPML_CC_Marshal(source, buffer, size)                                       \
    Marshal(TPML_CC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_CCA_Marshal(source, buffer, size)                                      \
    Marshal(TPML_CCA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_ALG_Unmarshal(target, buffer, size)                                    \
    Unmarshal(TPML_ALG_MARSHAL_INDEX, (target), (buffer), (size))
#define TPML_ALG_Marshal(source, buffer, size)                                      \
    Marshal(TPML_ALG_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_HANDLE_Marshal(source, buffer, size)                                   \
    Marshal(TPML_HANDLE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_DIGEST_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPML_DIGEST_MARSHAL_INDEX, (target), (buffer), (size))
#define TPML_DIGEST_Marshal(source, buffer, size)                                   \
    Marshal(TPML_DIGEST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_DIGEST_VALUES_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPML_DIGEST_VALUES_MARSHAL_INDEX, (target), (buffer), (size))
#define TPML_DIGEST_VALUES_Marshal(source, buffer, size)                            \
    Marshal(TPML_DIGEST_VALUES_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_PCR_SELECTION_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPML_PCR_SELECTION_MARSHAL_INDEX, (target), (buffer), (size))
#define TPML_PCR_SELECTION_Marshal(source, buffer, size)                            \
    Marshal(TPML_PCR_SELECTION_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_ALG_PROPERTY_Marshal(source, buffer, size)                             \
    Marshal(TPML_ALG_PROPERTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_TAGGED_TPM_PROPERTY_Marshal(source, buffer, size)                      \
    Marshal(TPML_TAGGED_TPM_PROPERTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_TAGGED_PCR_PROPERTY_Marshal(source, buffer, size)                      \
    Marshal(TPML_TAGGED_PCR_PROPERTY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_ECC_CURVE_Marshal(source, buffer, size)                                \
    Marshal(TPML_ECC_CURVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_TAGGED_POLICY_Marshal(source, buffer, size)                            \
    Marshal(TPML_TAGGED_POLICY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_CAPABILITIES_Marshal(source, buffer, size, selector)                   \
    MarshalUnion(TPMU_CAPABILITIES_MARSHAL_INDEX, (target), (buffer), (size),       \
      (selector))
#define TPMS_CAPABILITY_DATA_Marshal(source, buffer, size)                          \
    Marshal(TPMS_CAPABILITY_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CLOCK_INFO_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMS_CLOCK_INFO_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_CLOCK_INFO_Marshal(source, buffer, size)                               \
    Marshal(TPMS_CLOCK_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_TIME_INFO_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMS_TIME_INFO_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_TIME_INFO_Marshal(source, buffer, size)                                \
    Marshal(TPMS_TIME_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_TIME_ATTEST_INFO_Marshal(source, buffer, size)                         \
    Marshal(TPMS_TIME_ATTEST_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CERTIFY_INFO_Marshal(source, buffer, size)                             \
    Marshal(TPMS_CERTIFY_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_QUOTE_INFO_Marshal(source, buffer, size)                               \
    Marshal(TPMS_QUOTE_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_COMMAND_AUDIT_INFO_Marshal(source, buffer, size)                       \
    Marshal(TPMS_COMMAND_AUDIT_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SESSION_AUDIT_INFO_Marshal(source, buffer, size)                       \
    Marshal(TPMS_SESSION_AUDIT_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CREATION_INFO_Marshal(source, buffer, size)                            \
    Marshal(TPMS_CREATION_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_NV_CERTIFY_INFO_Marshal(source, buffer, size)                          \
    Marshal(TPMS_NV_CERTIFY_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_NV_DIGEST_CERTIFY_INFO_Marshal(source, buffer, size)                   \
    Marshal(TPMS_NV_DIGEST_CERTIFY_INFO_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ST_ATTEST_Marshal(source, buffer, size)                                \
    Marshal(TPMI_ST_ATTEST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_ATTEST_Marshal(source, buffer, size, selector)                         \
    MarshalUnion(TPMU_ATTEST_MARSHAL_INDEX, (target), (buffer), (size), (selector))
#define TPMS_ATTEST_Marshal(source, buffer, size)                                   \
    Marshal(TPMS_ATTEST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_ATTEST_Marshal(source, buffer, size)                                  \
    Marshal(TPM2B_ATTEST_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_AUTH_COMMAND_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMS_AUTH_COMMAND_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_AUTH_RESPONSE_Marshal(source, buffer, size)                            \
    Marshal(TPMS_AUTH_RESPONSE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_TDES_KEY_BITS_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMI_TDES_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_TDES_KEY_BITS_Marshal(source, buffer, size)                            \
    Marshal(TPMI_TDES_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_AES_KEY_BITS_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMI_AES_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_AES_KEY_BITS_Marshal(source, buffer, size)                             \
    Marshal(TPMI_AES_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_SM4_KEY_BITS_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMI_SM4_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_SM4_KEY_BITS_Marshal(source, buffer, size)                             \
    Marshal(TPMI_SM4_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_CAMELLIA_KEY_BITS_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPMI_CAMELLIA_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_CAMELLIA_KEY_BITS_Marshal(source, buffer, size)                        \
    Marshal(TPMI_CAMELLIA_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_SYM_KEY_BITS_Unmarshal(target, buffer, size, selector)                 \
    UnmarshalUnion(TPMU_SYM_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size),     \
      (selector))
#define TPMU_SYM_KEY_BITS_Marshal(source, buffer, size, selector)                   \
    MarshalUnion(TPMU_SYM_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size),       \
      (selector))
#define TPMU_SYM_MODE_Unmarshal(target, buffer, size, selector)                     \
    UnmarshalUnion(TPMU_SYM_MODE_MARSHAL_INDEX, (target), (buffer), (size),         \
      (selector))
#define TPMU_SYM_MODE_Marshal(source, buffer, size, selector)                       \
    MarshalUnion(TPMU_SYM_MODE_MARSHAL_INDEX, (target), (buffer), (size),           \
      (selector))
#define TPMT_SYM_DEF_Unmarshal(target, buffer, size, flag)                          \
    Unmarshal(TPMT_SYM_DEF_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),        \
      (buffer), (size))
#define TPMT_SYM_DEF_Marshal(source, buffer, size)                                  \
    Marshal(TPMT_SYM_DEF_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_SYM_DEF_OBJECT_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMT_SYM_DEF_OBJECT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMT_SYM_DEF_OBJECT_Marshal(source, buffer, size)                           \
    Marshal(TPMT_SYM_DEF_OBJECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_SYM_KEY_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPM2B_SYM_KEY_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_SYM_KEY_Marshal(source, buffer, size)                                 \
    Marshal(TPM2B_SYM_KEY_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SYMCIPHER_PARMS_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_SYMCIPHER_PARMS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SYMCIPHER_PARMS_Marshal(source, buffer, size)                          \
    Marshal(TPMS_SYMCIPHER_PARMS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_LABEL_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPM2B_LABEL_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_LABEL_Marshal(source, buffer, size)                                   \
    Marshal(TPM2B_LABEL_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_DERIVE_Unmarshal(target, buffer, size)                                 \
    Unmarshal(TPMS_DERIVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_DERIVE_Marshal(source, buffer, size)                                   \
    Marshal(TPMS_DERIVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_DERIVE_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPM2B_DERIVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_DERIVE_Marshal(source, buffer, size)                                  \
    Marshal(TPM2B_DERIVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_SENSITIVE_DATA_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPM2B_SENSITIVE_DATA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_SENSITIVE_DATA_Marshal(source, buffer, size)                          \
    Marshal(TPM2B_SENSITIVE_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SENSITIVE_CREATE_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_SENSITIVE_CREATE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_SENSITIVE_CREATE_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPM2B_SENSITIVE_CREATE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_HASH_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMS_SCHEME_HASH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_HASH_Marshal(source, buffer, size)                              \
    Marshal(TPMS_SCHEME_HASH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_ECDAA_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMS_SCHEME_ECDAA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_ECDAA_Marshal(source, buffer, size)                             \
    Marshal(TPMS_SCHEME_ECDAA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_KEYEDHASH_SCHEME_Unmarshal(target, buffer, size, flag)             \
    Unmarshal(TPMI_ALG_KEYEDHASH_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0),     \
      (target), (buffer), (size))
#define TPMI_ALG_KEYEDHASH_SCHEME_Marshal(source, buffer, size)                     \
    Marshal(TPMI_ALG_KEYEDHASH_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_HMAC_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMS_SCHEME_HMAC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_HMAC_Marshal(source, buffer, size)                              \
    Marshal(TPMS_SCHEME_HMAC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_XOR_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMS_SCHEME_XOR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_XOR_Marshal(source, buffer, size)                               \
    Marshal(TPMS_SCHEME_XOR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_SCHEME_KEYEDHASH_Unmarshal(target, buffer, size, selector)             \
    UnmarshalUnion(TPMU_SCHEME_KEYEDHASH_MARSHAL_INDEX, (target), (buffer), (size), \
      (selector))
#define TPMU_SCHEME_KEYEDHASH_Marshal(source, buffer, size, selector)               \
    MarshalUnion(TPMU_SCHEME_KEYEDHASH_MARSHAL_INDEX, (target), (buffer), (size),   \
      (selector))
#define TPMT_KEYEDHASH_SCHEME_Unmarshal(target, buffer, size, flag)                 \
    Unmarshal(TPMT_KEYEDHASH_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0),         \
      (target), (buffer), (size))
#define TPMT_KEYEDHASH_SCHEME_Marshal(source, buffer, size)                         \
    Marshal(TPMT_KEYEDHASH_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_RSASSA_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPMS_SIG_SCHEME_RSASSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_RSASSA_Marshal(source, buffer, size)                        \
    Marshal(TPMS_SIG_SCHEME_RSASSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_RSAPSS_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPMS_SIG_SCHEME_RSAPSS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_RSAPSS_Marshal(source, buffer, size)                        \
    Marshal(TPMS_SIG_SCHEME_RSAPSS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_ECDSA_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_SIG_SCHEME_ECDSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_ECDSA_Marshal(source, buffer, size)                         \
    Marshal(TPMS_SIG_SCHEME_ECDSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_SM2_Unmarshal(target, buffer, size)                         \
    Unmarshal(TPMS_SIG_SCHEME_SM2_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_SM2_Marshal(source, buffer, size)                           \
    Marshal(TPMS_SIG_SCHEME_SM2_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_ECSCHNORR_Unmarshal(target, buffer, size)                   \
    Unmarshal(TPMS_SIG_SCHEME_ECSCHNORR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_ECSCHNORR_Marshal(source, buffer, size)                     \
    Marshal(TPMS_SIG_SCHEME_ECSCHNORR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIG_SCHEME_ECDAA_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_SIG_SCHEME_ECDAA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIG_SCHEME_ECDAA_Marshal(source, buffer, size)                         \
    Marshal(TPMS_SIG_SCHEME_ECDAA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_SIG_SCHEME_Unmarshal(target, buffer, size, selector)                   \
    UnmarshalUnion(TPMU_SIG_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),       \
      (selector))
#define TPMU_SIG_SCHEME_Marshal(source, buffer, size, selector)                     \
    MarshalUnion(TPMU_SIG_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),         \
      (selector))
#define TPMT_SIG_SCHEME_Unmarshal(target, buffer, size, flag)                       \
    Unmarshal(TPMT_SIG_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),     \
      (buffer), (size))
#define TPMT_SIG_SCHEME_Marshal(source, buffer, size)                               \
    Marshal(TPMT_SIG_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ENC_SCHEME_OAEP_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_ENC_SCHEME_OAEP_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_ENC_SCHEME_OAEP_Marshal(source, buffer, size)                          \
    Marshal(TPMS_ENC_SCHEME_OAEP_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ENC_SCHEME_RSAES_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_ENC_SCHEME_RSAES_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_ENC_SCHEME_RSAES_Marshal(source, buffer, size)                         \
    Marshal(TPMS_ENC_SCHEME_RSAES_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_KEY_SCHEME_ECDH_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_KEY_SCHEME_ECDH_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_KEY_SCHEME_ECDH_Marshal(source, buffer, size)                          \
    Marshal(TPMS_KEY_SCHEME_ECDH_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_KEY_SCHEME_ECMQV_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_KEY_SCHEME_ECMQV_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_KEY_SCHEME_ECMQV_Marshal(source, buffer, size)                         \
    Marshal(TPMS_KEY_SCHEME_ECMQV_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_MGF1_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMS_SCHEME_MGF1_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_MGF1_Marshal(source, buffer, size)                              \
    Marshal(TPMS_SCHEME_MGF1_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_KDF1_SP800_56A_Unmarshal(target, buffer, size)                  \
    Unmarshal(TPMS_SCHEME_KDF1_SP800_56A_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_KDF1_SP800_56A_Marshal(source, buffer, size)                    \
    Marshal(TPMS_SCHEME_KDF1_SP800_56A_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_KDF2_Unmarshal(target, buffer, size)                            \
    Unmarshal(TPMS_SCHEME_KDF2_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_KDF2_Marshal(source, buffer, size)                              \
    Marshal(TPMS_SCHEME_KDF2_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SCHEME_KDF1_SP800_108_Unmarshal(target, buffer, size)                  \
    Unmarshal(TPMS_SCHEME_KDF1_SP800_108_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SCHEME_KDF1_SP800_108_Marshal(source, buffer, size)                    \
    Marshal(TPMS_SCHEME_KDF1_SP800_108_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_KDF_SCHEME_Unmarshal(target, buffer, size, selector)                   \
    UnmarshalUnion(TPMU_KDF_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),       \
      (selector))
#define TPMU_KDF_SCHEME_Marshal(source, buffer, size, selector)                     \
    MarshalUnion(TPMU_KDF_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),         \
      (selector))
#define TPMT_KDF_SCHEME_Unmarshal(target, buffer, size, flag)                       \
    Unmarshal(TPMT_KDF_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),     \
      (buffer), (size))
#define TPMT_KDF_SCHEME_Marshal(source, buffer, size)                               \
    Marshal(TPMT_KDF_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_ASYM_SCHEME_Unmarshal(target, buffer, size, flag)                  \
    Unmarshal(TPMI_ALG_ASYM_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),\
      (buffer), (size))
#define TPMI_ALG_ASYM_SCHEME_Marshal(source, buffer, size)                          \
    Marshal(TPMI_ALG_ASYM_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_ASYM_SCHEME_Unmarshal(target, buffer, size, selector)                  \
    UnmarshalUnion(TPMU_ASYM_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),      \
      (selector))
#define TPMU_ASYM_SCHEME_Marshal(source, buffer, size, selector)                    \
    MarshalUnion(TPMU_ASYM_SCHEME_MARSHAL_INDEX, (target), (buffer), (size),        \
      (selector))
#define TPMI_ALG_RSA_SCHEME_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_ALG_RSA_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_ALG_RSA_SCHEME_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ALG_RSA_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_RSA_SCHEME_Unmarshal(target, buffer, size, flag)                       \
    Unmarshal(TPMT_RSA_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),     \
      (buffer), (size))
#define TPMT_RSA_SCHEME_Marshal(source, buffer, size)                               \
    Marshal(TPMT_RSA_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_RSA_DECRYPT_Unmarshal(target, buffer, size, flag)                  \
    Unmarshal(TPMI_ALG_RSA_DECRYPT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),\
      (buffer), (size))
#define TPMI_ALG_RSA_DECRYPT_Marshal(source, buffer, size)                          \
    Marshal(TPMI_ALG_RSA_DECRYPT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_RSA_DECRYPT_Unmarshal(target, buffer, size, flag)                      \
    Unmarshal(TPMT_RSA_DECRYPT_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),    \
      (buffer), (size))
#define TPMT_RSA_DECRYPT_Marshal(source, buffer, size)                              \
    Marshal(TPMT_RSA_DECRYPT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_PUBLIC_KEY_RSA_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPM2B_PUBLIC_KEY_RSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_PUBLIC_KEY_RSA_Marshal(source, buffer, size)                          \
    Marshal(TPM2B_PUBLIC_KEY_RSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_RSA_KEY_BITS_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMI_RSA_KEY_BITS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_RSA_KEY_BITS_Marshal(source, buffer, size)                             \
    Marshal(TPMI_RSA_KEY_BITS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_PRIVATE_KEY_RSA_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPM2B_PRIVATE_KEY_RSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_PRIVATE_KEY_RSA_Marshal(source, buffer, size)                         \
    Marshal(TPM2B_PRIVATE_KEY_RSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_ECC_PARAMETER_Unmarshal(target, buffer, size)                         \
    Unmarshal(TPM2B_ECC_PARAMETER_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_ECC_PARAMETER_Marshal(source, buffer, size)                           \
    Marshal(TPM2B_ECC_PARAMETER_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ECC_POINT_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMS_ECC_POINT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_ECC_POINT_Marshal(source, buffer, size)                                \
    Marshal(TPMS_ECC_POINT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_ECC_POINT_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPM2B_ECC_POINT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_ECC_POINT_Marshal(source, buffer, size)                               \
    Marshal(TPM2B_ECC_POINT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_ECC_SCHEME_Unmarshal(target, buffer, size, flag)                   \
    Unmarshal(TPMI_ALG_ECC_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target), \
      (buffer), (size))
#define TPMI_ALG_ECC_SCHEME_Marshal(source, buffer, size)                           \
    Marshal(TPMI_ALG_ECC_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ECC_CURVE_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMI_ECC_CURVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_ECC_CURVE_Marshal(source, buffer, size)                                \
    Marshal(TPMI_ECC_CURVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_ECC_SCHEME_Unmarshal(target, buffer, size, flag)                       \
    Unmarshal(TPMT_ECC_SCHEME_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),     \
      (buffer), (size))
#define TPMT_ECC_SCHEME_Marshal(source, buffer, size)                               \
    Marshal(TPMT_ECC_SCHEME_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ALGORITHM_DETAIL_ECC_Marshal(source, buffer, size)                     \
    Marshal(TPMS_ALGORITHM_DETAIL_ECC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_RSA_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMS_SIGNATURE_RSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_RSA_Marshal(source, buffer, size)                            \
    Marshal(TPMS_SIGNATURE_RSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_RSASSA_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_SIGNATURE_RSASSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_RSASSA_Marshal(source, buffer, size)                         \
    Marshal(TPMS_SIGNATURE_RSASSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_RSAPSS_Unmarshal(target, buffer, size)                       \
    Unmarshal(TPMS_SIGNATURE_RSAPSS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_RSAPSS_Marshal(source, buffer, size)                         \
    Marshal(TPMS_SIGNATURE_RSAPSS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_ECC_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMS_SIGNATURE_ECC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_ECC_Marshal(source, buffer, size)                            \
    Marshal(TPMS_SIGNATURE_ECC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_ECDAA_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_SIGNATURE_ECDAA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_ECDAA_Marshal(source, buffer, size)                          \
    Marshal(TPMS_SIGNATURE_ECDAA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_ECDSA_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_SIGNATURE_ECDSA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_ECDSA_Marshal(source, buffer, size)                          \
    Marshal(TPMS_SIGNATURE_ECDSA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_SM2_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPMS_SIGNATURE_SM2_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_SM2_Marshal(source, buffer, size)                            \
    Marshal(TPMS_SIGNATURE_SM2_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_SIGNATURE_ECSCHNORR_Unmarshal(target, buffer, size)                    \
    Unmarshal(TPMS_SIGNATURE_ECSCHNORR_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_SIGNATURE_ECSCHNORR_Marshal(source, buffer, size)                      \
    Marshal(TPMS_SIGNATURE_ECSCHNORR_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_SIGNATURE_Unmarshal(target, buffer, size, selector)                    \
    UnmarshalUnion(TPMU_SIGNATURE_MARSHAL_INDEX, (target), (buffer), (size),        \
      (selector))
#define TPMU_SIGNATURE_Marshal(source, buffer, size, selector)                      \
    MarshalUnion(TPMU_SIGNATURE_MARSHAL_INDEX, (target), (buffer), (size),          \
      (selector))
#define TPMT_SIGNATURE_Unmarshal(target, buffer, size, flag)                        \
    Unmarshal(TPMT_SIGNATURE_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),      \
      (buffer), (size))
#define TPMT_SIGNATURE_Marshal(source, buffer, size)                                \
    Marshal(TPMT_SIGNATURE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_ENCRYPTED_SECRET_Unmarshal(target, buffer, size, selector)             \
    UnmarshalUnion(TPMU_ENCRYPTED_SECRET_MARSHAL_INDEX, (target), (buffer), (size), \
      (selector))
#define TPMU_ENCRYPTED_SECRET_Marshal(source, buffer, size, selector)               \
    MarshalUnion(TPMU_ENCRYPTED_SECRET_MARSHAL_INDEX, (target), (buffer), (size),   \
      (selector))
#define TPM2B_ENCRYPTED_SECRET_Unmarshal(target, buffer, size)                      \
    Unmarshal(TPM2B_ENCRYPTED_SECRET_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_ENCRYPTED_SECRET_Marshal(source, buffer, size)                        \
    Marshal(TPM2B_ENCRYPTED_SECRET_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMI_ALG_PUBLIC_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPMI_ALG_PUBLIC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMI_ALG_PUBLIC_Marshal(source, buffer, size)                               \
    Marshal(TPMI_ALG_PUBLIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_PUBLIC_ID_Unmarshal(target, buffer, size, selector)                    \
    UnmarshalUnion(TPMU_PUBLIC_ID_MARSHAL_INDEX, (target), (buffer), (size),        \
      (selector))
#define TPMU_PUBLIC_ID_Marshal(source, buffer, size, selector)                      \
    MarshalUnion(TPMU_PUBLIC_ID_MARSHAL_INDEX, (target), (buffer), (size),          \
      (selector))
#define TPMS_KEYEDHASH_PARMS_Unmarshal(target, buffer, size)                        \
    Unmarshal(TPMS_KEYEDHASH_PARMS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_KEYEDHASH_PARMS_Marshal(source, buffer, size)                          \
    Marshal(TPMS_KEYEDHASH_PARMS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_RSA_PARMS_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMS_RSA_PARMS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_RSA_PARMS_Marshal(source, buffer, size)                                \
    Marshal(TPMS_RSA_PARMS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_ECC_PARMS_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMS_ECC_PARMS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_ECC_PARMS_Marshal(source, buffer, size)                                \
    Marshal(TPMS_ECC_PARMS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_PUBLIC_PARMS_Unmarshal(target, buffer, size, selector)                 \
    UnmarshalUnion(TPMU_PUBLIC_PARMS_MARSHAL_INDEX, (target), (buffer), (size),     \
      (selector))
#define TPMU_PUBLIC_PARMS_Marshal(source, buffer, size, selector)                   \
    MarshalUnion(TPMU_PUBLIC_PARMS_MARSHAL_INDEX, (target), (buffer), (size),       \
      (selector))
#define TPMT_PUBLIC_PARMS_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMT_PUBLIC_PARMS_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_PUBLIC_PARMS_Marshal(source, buffer, size)                             \
    Marshal(TPMT_PUBLIC_PARMS_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMT_PUBLIC_Unmarshal(target, buffer, size, flag)                           \
    Unmarshal(TPMT_PUBLIC_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),         \
      (buffer), (size))
#define TPMT_PUBLIC_Marshal(source, buffer, size)                                   \
    Marshal(TPMT_PUBLIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_PUBLIC_Unmarshal(target, buffer, size, flag)                          \
    Unmarshal(TPM2B_PUBLIC_MARSHAL_INDEX | (flag ? NULL_FLAG : 0), (target),        \
      (buffer), (size))
#define TPM2B_PUBLIC_Marshal(source, buffer, size)                                  \
    Marshal(TPM2B_PUBLIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_TEMPLATE_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPM2B_TEMPLATE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_TEMPLATE_Marshal(source, buffer, size)                                \
    Marshal(TPM2B_TEMPLATE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_PRIVATE_VENDOR_SPECIFIC_Unmarshal(target, buffer, size)               \
    Unmarshal(TPM2B_PRIVATE_VENDOR_SPECIFIC_MARSHAL_INDEX, (target), (buffer),      \
      (size))
#define TPM2B_PRIVATE_VENDOR_SPECIFIC_Marshal(source, buffer, size)                 \
    Marshal(TPM2B_PRIVATE_VENDOR_SPECIFIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMU_SENSITIVE_COMPOSITE_Unmarshal(target, buffer, size, selector)          \
    UnmarshalUnion(TPMU_SENSITIVE_COMPOSITE_MARSHAL_INDEX, (target), (buffer),      \
      (size), (selector))
#define TPMU_SENSITIVE_COMPOSITE_Marshal(source, buffer, size, selector)            \
    MarshalUnion(TPMU_SENSITIVE_COMPOSITE_MARSHAL_INDEX, (target), (buffer), (size),\
      (selector))
#define TPMT_SENSITIVE_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMT_SENSITIVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMT_SENSITIVE_Marshal(source, buffer, size)                                \
    Marshal(TPMT_SENSITIVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_SENSITIVE_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPM2B_SENSITIVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_SENSITIVE_Marshal(source, buffer, size)                               \
    Marshal(TPM2B_SENSITIVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_PRIVATE_Unmarshal(target, buffer, size)                               \
    Unmarshal(TPM2B_PRIVATE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_PRIVATE_Marshal(source, buffer, size)                                 \
    Marshal(TPM2B_PRIVATE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_ID_OBJECT_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPM2B_ID_OBJECT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_ID_OBJECT_Marshal(source, buffer, size)                               \
    Marshal(TPM2B_ID_OBJECT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_NV_INDEX_Marshal(source, buffer, size)                                  \
    Marshal(TPM_NV_INDEX_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_NV_PIN_COUNTER_PARAMETERS_Unmarshal(target, buffer, size)              \
    Unmarshal(TPMS_NV_PIN_COUNTER_PARAMETERS_MARSHAL_INDEX, (target), (buffer),     \
      (size))
#define TPMS_NV_PIN_COUNTER_PARAMETERS_Marshal(source, buffer, size)                \
    Marshal(TPMS_NV_PIN_COUNTER_PARAMETERS_MARSHAL_INDEX, (source), (buffer),       \
      (size))
#define TPMA_NV_Unmarshal(target, buffer, size)                                     \
    Unmarshal(TPMA_NV_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMA_NV_Marshal(source, buffer, size)                                       \
    Marshal(TPMA_NV_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_NV_PUBLIC_Unmarshal(target, buffer, size)                              \
    Unmarshal(TPMS_NV_PUBLIC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_NV_PUBLIC_Marshal(source, buffer, size)                                \
    Marshal(TPMS_NV_PUBLIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_NV_PUBLIC_Unmarshal(target, buffer, size)                             \
    Unmarshal(TPM2B_NV_PUBLIC_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_NV_PUBLIC_Marshal(source, buffer, size)                               \
    Marshal(TPM2B_NV_PUBLIC_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_CONTEXT_SENSITIVE_Unmarshal(target, buffer, size)                     \
    Unmarshal(TPM2B_CONTEXT_SENSITIVE_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_CONTEXT_SENSITIVE_Marshal(source, buffer, size)                       \
    Marshal(TPM2B_CONTEXT_SENSITIVE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CONTEXT_DATA_Unmarshal(target, buffer, size)                           \
    Unmarshal(TPMS_CONTEXT_DATA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_CONTEXT_DATA_Marshal(source, buffer, size)                             \
    Marshal(TPMS_CONTEXT_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_CONTEXT_DATA_Unmarshal(target, buffer, size)                          \
    Unmarshal(TPM2B_CONTEXT_DATA_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM2B_CONTEXT_DATA_Marshal(source, buffer, size)                            \
    Marshal(TPM2B_CONTEXT_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CONTEXT_Unmarshal(target, buffer, size)                                \
    Unmarshal(TPMS_CONTEXT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPMS_CONTEXT_Marshal(source, buffer, size)                                  \
    Marshal(TPMS_CONTEXT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_CREATION_DATA_Marshal(source, buffer, size)                            \
    Marshal(TPMS_CREATION_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM2B_CREATION_DATA_Marshal(source, buffer, size)                           \
    Marshal(TPM2B_CREATION_DATA_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_AT_Unmarshal(target, buffer, size)                                      \
    Unmarshal(TPM_AT_MARSHAL_INDEX, (target), (buffer), (size))
#define TPM_AT_Marshal(source, buffer, size)                                        \
    Marshal(TPM_AT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPM_AE_Marshal(source, buffer, size)                                        \
    Marshal(TPM_AE_MARSHAL_INDEX, (source), (buffer), (size))
#define TPMS_AC_OUTPUT_Marshal(source, buffer, size)                                \
    Marshal(TPMS_AC_OUTPUT_MARSHAL_INDEX, (source), (buffer), (size))
#define TPML_AC_CAPABILITIES_Marshal(source, buffer, size)                          \
    Marshal(TPML_AC_CAPABILITIES_MARSHAL_INDEX, (source), (buffer), (size))


#endif // _Table_Marshal_Data_
