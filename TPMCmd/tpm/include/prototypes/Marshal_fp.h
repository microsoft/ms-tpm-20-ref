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
 *    Created by TpmMarshal.pl version 2.1 September 17, 2015
 *    This file created on Sep 27, 2016, 04:02:56 PM
 
    Processed by TpmReferencesAndReturns Version 1.2, July 27, 2015
    Date: Sep 27, 2016 Time: 04:02:57 PM

*/

#ifndef    _MARSHAL_FP_H
#define    _MARSHAL_FP_H



// Table 2:3 - Definition of Base Types (BaseTypes)
//   UINT8 definition from table 2:3
TPM_RC
UINT8_Unmarshal(UINT8 *target, BYTE **buffer, INT32 *size);
UINT16
UINT8_Marshal(UINT8 *source, BYTE **buffer, INT32 *size);

//   BYTE definition from table 2:3
#define BYTE_Unmarshal(target, buffer, size) \
            UINT8_Unmarshal((UINT8 *)(target), buffer, size)
#define BYTE_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)
//   INT8 definition from table 2:3
#define INT8_Unmarshal(target, buffer, size) \
            UINT8_Unmarshal((UINT8 *)(target), buffer, size)
#define INT8_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)
//   UINT16 definition from table 2:3
TPM_RC
UINT16_Unmarshal(UINT16 *target, BYTE **buffer, INT32 *size);
UINT16
UINT16_Marshal(UINT16 *source, BYTE **buffer, INT32 *size);

//   INT16 definition from table 2:3
#define INT16_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define INT16_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)
//   UINT32 definition from table 2:3
TPM_RC
UINT32_Unmarshal(UINT32 *target, BYTE **buffer, INT32 *size);
UINT16
UINT32_Marshal(UINT32 *source, BYTE **buffer, INT32 *size);

//   INT32 definition from table 2:3
#define INT32_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define INT32_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)
//   UINT64 definition from table 2:3
TPM_RC
UINT64_Unmarshal(UINT64 *target, BYTE **buffer, INT32 *size);
UINT16
UINT64_Marshal(UINT64 *source, BYTE **buffer, INT32 *size);

//   INT64 definition from table 2:3
#define INT64_Unmarshal(target, buffer, size) \
            UINT64_Unmarshal((UINT64 *)(target), buffer, size)
#define INT64_Marshal(source, buffer, size) \
            UINT64_Marshal((UINT64 *)(source), buffer, size)


// Table 2:4 - Defines for Logic Values (DefinesTable)


// Table 2:5 - Definition of Types for Documentation Clarity (TypesTable)
//   UINT32 definition from table 2:5
#define TPM_ALGORITHM_ID_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_ALGORITHM_ID_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)
//   UINT32 definition from table 2:5
#define TPM_MODIFIER_INDICATOR_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_MODIFIER_INDICATOR_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)
//   UINT32 definition from table 2:5
#define TPM_AUTHORIZATION_SIZE_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_AUTHORIZATION_SIZE_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)
//   UINT32 definition from table 2:5
#define TPM_PARAMETER_SIZE_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_PARAMETER_SIZE_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)
//   UINT16 definition from table 2:5
#define TPM_KEY_SIZE_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define TPM_KEY_SIZE_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)
//   UINT16 definition from table 2:5
#define TPM_KEY_BITS_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define TPM_KEY_BITS_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)


// Table 2:6 - Definition of TPM_SPEC Constants  (ConstantsTable)
#define TPM_SPEC_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_SPEC_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:7 - Definition of TPM_GENERATED Constants  (ConstantsTable)
#define TPM_GENERATED_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_GENERATED_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:9 - Definition of TPM_ALG_ID Constants  (ConstantsTable)
#define TPM_ALG_ID_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define TPM_ALG_ID_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)


// Table 2:10 - Definition of TPM_ECC_CURVE Constants  (ConstantsTable)
#if         ALG_ECC
#define TPM_ECC_CURVE_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define TPM_ECC_CURVE_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)
#endif // ALG_ECC


// Table 2:12 - Definition of TPM_CC Constants  (ConstantsTable)
#define TPM_CC_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_CC_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:16 - Definition of TPM_RC Constants  (ConstantsTable)
#define TPM_RC_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_RC_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:17 - Definition of TPM_CLOCK_ADJUST Constants  (ConstantsTable)
TPM_RC
TPM_CLOCK_ADJUST_Unmarshal(TPM_CLOCK_ADJUST *target, BYTE **buffer, INT32 *size);

#define TPM_CLOCK_ADJUST_Marshal(source, buffer, size) \
            INT8_Marshal((INT8 *)(source), buffer, size)


// Table 2:18 - Definition of TPM_EO Constants  (ConstantsTable)
TPM_RC
TPM_EO_Unmarshal(TPM_EO *target, BYTE **buffer, INT32 *size);

#define TPM_EO_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)


// Table 2:19 - Definition of TPM_ST Constants  (ConstantsTable)
#define TPM_ST_Unmarshal(target, buffer, size) \
            UINT16_Unmarshal((UINT16 *)(target), buffer, size)
#define TPM_ST_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)


// Table 2:20 - Definition of TPM_SU Constants  (ConstantsTable)
TPM_RC
TPM_SU_Unmarshal(TPM_SU *target, BYTE **buffer, INT32 *size);

#define TPM_SU_Marshal(source, buffer, size) \
            UINT16_Marshal((UINT16 *)(source), buffer, size)


// Table 2:21 - Definition of TPM_SE Constants  (ConstantsTable)
TPM_RC
TPM_SE_Unmarshal(TPM_SE *target, BYTE **buffer, INT32 *size);

#define TPM_SE_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)


// Table 2:22 - Definition of TPM_CAP Constants (ConstantsTable)
TPM_RC
TPM_CAP_Unmarshal(TPM_CAP *target, BYTE **buffer, INT32 *size);

#define TPM_CAP_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:23 - Definition of TPM_PT Constants  (ConstantsTable)
#define TPM_PT_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_PT_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:24 - Definition of TPM_PT_PCR Constants  (ConstantsTable)
#define TPM_PT_PCR_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_PT_PCR_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:25 - Definition of TPM_PS Constants  (ConstantsTable)
#define TPM_PS_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_PS_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:26 - Definition of Types for Handles (TypesTable)
//   UINT32 definition from table 2:26
#define TPM_HANDLE_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_HANDLE_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:27 - Definition of TPM_HT Constants  (ConstantsTable)
#define TPM_HT_Unmarshal(target, buffer, size) \
            UINT8_Unmarshal((UINT8 *)(target), buffer, size)
#define TPM_HT_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)


// Table 2:28 - Definition of TPM_RH Constants  (ConstantsTable)
#define TPM_RH_Unmarshal(target, buffer, size) \
            TPM_HANDLE_Unmarshal((TPM_HANDLE *)(target), buffer, size)
#define TPM_RH_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:29 - Definition of TPM_HC Constants  (ConstantsTable)
#define TPM_HC_Unmarshal(target, buffer, size) \
            TPM_HANDLE_Unmarshal((TPM_HANDLE *)(target), buffer, size)
#define TPM_HC_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:30 - Definition of TPMA_ALGORITHM Bits (BitsTable)
TPM_RC
TPMA_ALGORITHM_Unmarshal(TPMA_ALGORITHM *target, BYTE **buffer, INT32 *size);

#define TPMA_ALGORITHM_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:31 - Definition of TPMA_OBJECT Bits (BitsTable)
TPM_RC
TPMA_OBJECT_Unmarshal(TPMA_OBJECT *target, BYTE **buffer, INT32 *size);

#define TPMA_OBJECT_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:32 - Definition of TPMA_SESSION Bits  (BitsTable)
TPM_RC
TPMA_SESSION_Unmarshal(TPMA_SESSION *target, BYTE **buffer, INT32 *size);

#define TPMA_SESSION_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)


// Table 2:33 - Definition of TPMA_LOCALITY Bits  (BitsTable)
#define TPMA_LOCALITY_Unmarshal(target, buffer, size) \
            UINT8_Unmarshal((UINT8 *)(target), buffer, size)
#define TPMA_LOCALITY_Marshal(source, buffer, size) \
            UINT8_Marshal((UINT8 *)(source), buffer, size)


// Table 2:34 - Definition of TPMA_PERMANENT Bits  (BitsTable)
TPM_RC
TPMA_PERMANENT_Unmarshal(TPMA_PERMANENT *target, BYTE **buffer, INT32 *size);

#define TPMA_PERMANENT_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:35 - Definition of TPMA_STARTUP_CLEAR Bits  (BitsTable)
TPM_RC
TPMA_STARTUP_CLEAR_Unmarshal(TPMA_STARTUP_CLEAR *target, BYTE **buffer, INT32 *size);

#define TPMA_STARTUP_CLEAR_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:36 - Definition of TPMA_MEMORY Bits  (BitsTable)
TPM_RC
TPMA_MEMORY_Unmarshal(TPMA_MEMORY *target, BYTE **buffer, INT32 *size);

#define TPMA_MEMORY_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:37 - Definition of TPMA_CC Bits  (BitsTable)
TPM_RC
TPMA_CC_Unmarshal(TPMA_CC *target, BYTE **buffer, INT32 *size);

#define TPMA_CC_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:38 - Definition of TPMA_MODES Bits  (BitsTable)
TPM_RC
TPMA_MODES_Unmarshal(TPMA_MODES *target, BYTE **buffer, INT32 *size);

#define TPMA_MODES_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:39 - Definition of TPMI_YES_NO Type (TypeTable)
TPM_RC
TPMI_YES_NO_Unmarshal(TPMI_YES_NO *target, BYTE **buffer, INT32 *size);

#define TPMI_YES_NO_Marshal(source, buffer, size) \
            BYTE_Marshal((BYTE *)(source), buffer, size)


// Table 2:40 - Definition of TPMI_DH_OBJECT Type  (TypeTable)
TPM_RC
TPMI_DH_OBJECT_Unmarshal(TPMI_DH_OBJECT *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_DH_OBJECT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:41 - Definition of TPMI_DH_PARENT Type  (TypeTable)
TPM_RC
TPMI_DH_PARENT_Unmarshal(TPMI_DH_PARENT *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_DH_PARENT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:42 - Definition of TPMI_DH_PERSISTENT Type  (TypeTable)
TPM_RC
TPMI_DH_PERSISTENT_Unmarshal(TPMI_DH_PERSISTENT *target, BYTE **buffer, INT32 *size);

#define TPMI_DH_PERSISTENT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:43 - Definition of TPMI_DH_ENTITY Type  (TypeTable)
TPM_RC
TPMI_DH_ENTITY_Unmarshal(TPMI_DH_ENTITY *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_DH_ENTITY_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:44 - Definition of TPMI_DH_PCR Type  (TypeTable)
TPM_RC
TPMI_DH_PCR_Unmarshal(TPMI_DH_PCR *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_DH_PCR_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:45 - Definition of TPMI_SH_AUTH_SESSION Type  (TypeTable)
TPM_RC
TPMI_SH_AUTH_SESSION_Unmarshal(TPMI_SH_AUTH_SESSION *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_SH_AUTH_SESSION_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:46 - Definition of TPMI_SH_HMAC Type  (TypeTable)
TPM_RC
TPMI_SH_HMAC_Unmarshal(TPMI_SH_HMAC *target, BYTE **buffer, INT32 *size);

#define TPMI_SH_HMAC_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:47 - Definition of TPMI_SH_POLICY Type  (TypeTable)
TPM_RC
TPMI_SH_POLICY_Unmarshal(TPMI_SH_POLICY *target, BYTE **buffer, INT32 *size);

#define TPMI_SH_POLICY_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:48 - Definition of TPMI_DH_CONTEXT Type  (TypeTable)
TPM_RC
TPMI_DH_CONTEXT_Unmarshal(TPMI_DH_CONTEXT *target, BYTE **buffer, INT32 *size);

#define TPMI_DH_CONTEXT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:49 - Definition of TPMI_RH_HIERARCHY Type  (TypeTable)
TPM_RC
TPMI_RH_HIERARCHY_Unmarshal(TPMI_RH_HIERARCHY *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_RH_HIERARCHY_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:50 - Definition of TPMI_RH_ENABLES Type  (TypeTable)
TPM_RC
TPMI_RH_ENABLES_Unmarshal(TPMI_RH_ENABLES *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_RH_ENABLES_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:51 - Definition of TPMI_RH_HIERARCHY_AUTH Type  (TypeTable)
TPM_RC
TPMI_RH_HIERARCHY_AUTH_Unmarshal(TPMI_RH_HIERARCHY_AUTH *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_HIERARCHY_AUTH_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:52 - Definition of TPMI_RH_PLATFORM Type  (TypeTable)
TPM_RC
TPMI_RH_PLATFORM_Unmarshal(TPMI_RH_PLATFORM *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_PLATFORM_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:53 - Definition of TPMI_RH_OWNER Type  (TypeTable)
TPM_RC
TPMI_RH_OWNER_Unmarshal(TPMI_RH_OWNER *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_RH_OWNER_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:54 - Definition of TPMI_RH_ENDORSEMENT Type  (TypeTable)
TPM_RC
TPMI_RH_ENDORSEMENT_Unmarshal(TPMI_RH_ENDORSEMENT *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_RH_ENDORSEMENT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:55 - Definition of TPMI_RH_PROVISION Type  (TypeTable)
TPM_RC
TPMI_RH_PROVISION_Unmarshal(TPMI_RH_PROVISION *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_PROVISION_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:56 - Definition of TPMI_RH_CLEAR Type  (TypeTable)
TPM_RC
TPMI_RH_CLEAR_Unmarshal(TPMI_RH_CLEAR *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_CLEAR_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:57 - Definition of TPMI_RH_NV_AUTH Type  (TypeTable)
TPM_RC
TPMI_RH_NV_AUTH_Unmarshal(TPMI_RH_NV_AUTH *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_NV_AUTH_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:58 - Definition of TPMI_RH_LOCKOUT Type  (TypeTable)
TPM_RC
TPMI_RH_LOCKOUT_Unmarshal(TPMI_RH_LOCKOUT *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_LOCKOUT_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:59 - Definition of TPMI_RH_NV_INDEX Type  (TypeTable)
TPM_RC
TPMI_RH_NV_INDEX_Unmarshal(TPMI_RH_NV_INDEX *target, BYTE **buffer, INT32 *size);

#define TPMI_RH_NV_INDEX_Marshal(source, buffer, size) \
            TPM_HANDLE_Marshal((TPM_HANDLE *)(source), buffer, size)


// Table 2:60 - Definition of TPMI_ALG_HASH Type  (TypeTable)
TPM_RC
TPMI_ALG_HASH_Unmarshal(TPMI_ALG_HASH *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_HASH_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:61 - Definition of TPMI_ALG_ASYM Type (TypeTable)
TPM_RC
TPMI_ALG_ASYM_Unmarshal(TPMI_ALG_ASYM *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_ASYM_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:62 - Definition of TPMI_ALG_SYM Type (TypeTable)
TPM_RC
TPMI_ALG_SYM_Unmarshal(TPMI_ALG_SYM *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_SYM_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:63 - Definition of TPMI_ALG_SYM_OBJECT Type (TypeTable)
TPM_RC
TPMI_ALG_SYM_OBJECT_Unmarshal(TPMI_ALG_SYM_OBJECT *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_SYM_OBJECT_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:64 - Definition of TPMI_ALG_SYM_MODE Type (TypeTable)
TPM_RC
TPMI_ALG_SYM_MODE_Unmarshal(TPMI_ALG_SYM_MODE *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_SYM_MODE_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:65 - Definition of TPMI_ALG_KDF Type (TypeTable)
TPM_RC
TPMI_ALG_KDF_Unmarshal(TPMI_ALG_KDF *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_KDF_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:66 - Definition of TPMI_ALG_SIG_SCHEME Type (TypeTable)
TPM_RC
TPMI_ALG_SIG_SCHEME_Unmarshal(TPMI_ALG_SIG_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_SIG_SCHEME_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:67 - Definition of TPMI_ECC_KEY_EXCHANGE Type (TypeTable)
#if         ALG_ECC
TPM_RC
TPMI_ECC_KEY_EXCHANGE_Unmarshal(TPMI_ECC_KEY_EXCHANGE *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ECC_KEY_EXCHANGE_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)
#endif // ALG_ECC


// Table 2:68 - Definition of TPMI_ST_COMMAND_TAG Type (TypeTable)
TPM_RC
TPMI_ST_COMMAND_TAG_Unmarshal(TPMI_ST_COMMAND_TAG *target, BYTE **buffer, INT32 *size);

#define TPMI_ST_COMMAND_TAG_Marshal(source, buffer, size) \
            TPM_ST_Marshal((TPM_ST *)(source), buffer, size)
TPM_RC
TPMS_EMPTY_Unmarshal(TPMS_EMPTY *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_EMPTY_Marshal(TPMS_EMPTY *source, BYTE **buffer, INT32 *size);


// Table 2:70 - Definition of TPMS_ALGORITHM_DESCRIPTION Structure  (StructureTable)
TPM_RC
TPMS_ALGORITHM_DESCRIPTION_Unmarshal(TPMS_ALGORITHM_DESCRIPTION *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ALGORITHM_DESCRIPTION_Marshal(TPMS_ALGORITHM_DESCRIPTION *source, BYTE **buffer, INT32 *size);


// Table 2:71 - Definition of TPMU_HA Union  (UnionTable)
TPM_RC
TPMU_HA_Unmarshal(TPMU_HA *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_HA_Marshal(TPMU_HA *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:72 - Definition of TPMT_HA Structure  (StructureTable)
TPM_RC
TPMT_HA_Unmarshal(TPMT_HA *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_HA_Marshal(TPMT_HA *source, BYTE **buffer, INT32 *size);


// Table 2:73 - Definition of TPM2B_DIGEST Structure (StructureTable)
TPM_RC
TPM2B_DIGEST_Unmarshal(TPM2B_DIGEST *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_DIGEST_Marshal(TPM2B_DIGEST *source, BYTE **buffer, INT32 *size);


// Table 2:74 - Definition of TPM2B_DATA Structure (StructureTable)
TPM_RC
TPM2B_DATA_Unmarshal(TPM2B_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_DATA_Marshal(TPM2B_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:75 - Definition of Types for TPM2B_NONCE (TypesTable)
//   TPM2B_DIGEST definition from table 2:75
#define TPM2B_NONCE_Unmarshal(target, buffer, size) \
            TPM2B_DIGEST_Unmarshal((TPM2B_DIGEST *)(target), buffer, size)
#define TPM2B_NONCE_Marshal(source, buffer, size) \
            TPM2B_DIGEST_Marshal((TPM2B_DIGEST *)(source), buffer, size)


// Table 2:76 - Definition of Types for TPM2B_AUTH (TypesTable)
//   TPM2B_DIGEST definition from table 2:76
#define TPM2B_AUTH_Unmarshal(target, buffer, size) \
            TPM2B_DIGEST_Unmarshal((TPM2B_DIGEST *)(target), buffer, size)
#define TPM2B_AUTH_Marshal(source, buffer, size) \
            TPM2B_DIGEST_Marshal((TPM2B_DIGEST *)(source), buffer, size)


// Table 2:77 - Definition of Types for TPM2B_OPERAND (TypesTable)
//   TPM2B_DIGEST definition from table 2:77
#define TPM2B_OPERAND_Unmarshal(target, buffer, size) \
            TPM2B_DIGEST_Unmarshal((TPM2B_DIGEST *)(target), buffer, size)
#define TPM2B_OPERAND_Marshal(source, buffer, size) \
            TPM2B_DIGEST_Marshal((TPM2B_DIGEST *)(source), buffer, size)


// Table 2:78 - Definition of TPM2B_EVENT Structure (StructureTable)
TPM_RC
TPM2B_EVENT_Unmarshal(TPM2B_EVENT *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_EVENT_Marshal(TPM2B_EVENT *source, BYTE **buffer, INT32 *size);


// Table 2:79 - Definition of TPM2B_MAX_BUFFER Structure (StructureTable)
TPM_RC
TPM2B_MAX_BUFFER_Unmarshal(TPM2B_MAX_BUFFER *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_MAX_BUFFER_Marshal(TPM2B_MAX_BUFFER *source, BYTE **buffer, INT32 *size);


// Table 2:80 - Definition of TPM2B_MAX_NV_BUFFER Structure (StructureTable)
TPM_RC
TPM2B_MAX_NV_BUFFER_Unmarshal(TPM2B_MAX_NV_BUFFER *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_MAX_NV_BUFFER_Marshal(TPM2B_MAX_NV_BUFFER *source, BYTE **buffer, INT32 *size);


// Table 2:81 - Definition of Types for TPM2B_TIMEOUT (TypesTable)
//   TPM2B_DIGEST definition from table 2:81
#define TPM2B_TIMEOUT_Unmarshal(target, buffer, size) \
            TPM2B_DIGEST_Unmarshal((TPM2B_DIGEST *)(target), buffer, size)
#define TPM2B_TIMEOUT_Marshal(source, buffer, size) \
            TPM2B_DIGEST_Marshal((TPM2B_DIGEST *)(source), buffer, size)


// Table 2:82 - Definition of TPM2B_IV Structure  (StructureTable)
TPM_RC
TPM2B_IV_Unmarshal(TPM2B_IV *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_IV_Marshal(TPM2B_IV *source, BYTE **buffer, INT32 *size);


// Table 2:83 - Definition of TPMU_NAME Union  (UnionTable)


// Table 2:84 - Definition of TPM2B_NAME Structure (StructureTable)
TPM_RC
TPM2B_NAME_Unmarshal(TPM2B_NAME *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_NAME_Marshal(TPM2B_NAME *source, BYTE **buffer, INT32 *size);


// Table 2:85 - Definition of TPMS_PCR_SELECT Structure (StructureTable)
TPM_RC
TPMS_PCR_SELECT_Unmarshal(TPMS_PCR_SELECT *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_PCR_SELECT_Marshal(TPMS_PCR_SELECT *source, BYTE **buffer, INT32 *size);


// Table 2:86 - Definition of TPMS_PCR_SELECTION Structure (StructureTable)
TPM_RC
TPMS_PCR_SELECTION_Unmarshal(TPMS_PCR_SELECTION *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_PCR_SELECTION_Marshal(TPMS_PCR_SELECTION *source, BYTE **buffer, INT32 *size);


// Table 2:89 - Definition of TPMT_TK_CREATION Structure (StructureTable)
TPM_RC
TPMT_TK_CREATION_Unmarshal(TPMT_TK_CREATION *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_TK_CREATION_Marshal(TPMT_TK_CREATION *source, BYTE **buffer, INT32 *size);


// Table 2:90 - Definition of TPMT_TK_VERIFIED Structure (StructureTable)
TPM_RC
TPMT_TK_VERIFIED_Unmarshal(TPMT_TK_VERIFIED *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_TK_VERIFIED_Marshal(TPMT_TK_VERIFIED *source, BYTE **buffer, INT32 *size);


// Table 2:91 - Definition of TPMT_TK_AUTH Structure (StructureTable)
TPM_RC
TPMT_TK_AUTH_Unmarshal(TPMT_TK_AUTH *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_TK_AUTH_Marshal(TPMT_TK_AUTH *source, BYTE **buffer, INT32 *size);


// Table 2:92 - Definition of TPMT_TK_HASHCHECK Structure (StructureTable)
TPM_RC
TPMT_TK_HASHCHECK_Unmarshal(TPMT_TK_HASHCHECK *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_TK_HASHCHECK_Marshal(TPMT_TK_HASHCHECK *source, BYTE **buffer, INT32 *size);


// Table 2:93 - Definition of TPMS_ALG_PROPERTY Structure  (StructureTable)
TPM_RC
TPMS_ALG_PROPERTY_Unmarshal(TPMS_ALG_PROPERTY *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ALG_PROPERTY_Marshal(TPMS_ALG_PROPERTY *source, BYTE **buffer, INT32 *size);


// Table 2:94 - Definition of TPMS_TAGGED_PROPERTY Structure  (StructureTable)
TPM_RC
TPMS_TAGGED_PROPERTY_Unmarshal(TPMS_TAGGED_PROPERTY *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_TAGGED_PROPERTY_Marshal(TPMS_TAGGED_PROPERTY *source, BYTE **buffer, INT32 *size);


// Table 2:95 - Definition of TPMS_TAGGED_PCR_SELECT Structure  (StructureTable)
TPM_RC
TPMS_TAGGED_PCR_SELECT_Unmarshal(TPMS_TAGGED_PCR_SELECT *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_TAGGED_PCR_SELECT_Marshal(TPMS_TAGGED_PCR_SELECT *source, BYTE **buffer, INT32 *size);


// Table 2:96 - Definition of TPMS_TAGGED_POLICY Structure  (StructureTable)
TPM_RC
TPMS_TAGGED_POLICY_Unmarshal(TPMS_TAGGED_POLICY *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_TAGGED_POLICY_Marshal(TPMS_TAGGED_POLICY *source, BYTE **buffer, INT32 *size);


// Table 2:97 - Definition of TPML_CC Structure (StructureTable)
TPM_RC
TPML_CC_Unmarshal(TPML_CC *target, BYTE **buffer, INT32 *size);
UINT16
TPML_CC_Marshal(TPML_CC *source, BYTE **buffer, INT32 *size);


// Table 2:98 - Definition of TPML_CCA Structure  (StructureTable)
TPM_RC
TPML_CCA_Unmarshal(TPML_CCA *target, BYTE **buffer, INT32 *size);
UINT16
TPML_CCA_Marshal(TPML_CCA *source, BYTE **buffer, INT32 *size);


// Table 2:99 - Definition of TPML_ALG Structure (StructureTable)
TPM_RC
TPML_ALG_Unmarshal(TPML_ALG *target, BYTE **buffer, INT32 *size);
UINT16
TPML_ALG_Marshal(TPML_ALG *source, BYTE **buffer, INT32 *size);


// Table 2:100 - Definition of TPML_HANDLE Structure  (StructureTable)
TPM_RC
TPML_HANDLE_Unmarshal(TPML_HANDLE *target, BYTE **buffer, INT32 *size);
UINT16
TPML_HANDLE_Marshal(TPML_HANDLE *source, BYTE **buffer, INT32 *size);


// Table 2:101 - Definition of TPML_DIGEST Structure (StructureTable)
TPM_RC
TPML_DIGEST_Unmarshal(TPML_DIGEST *target, BYTE **buffer, INT32 *size);
UINT16
TPML_DIGEST_Marshal(TPML_DIGEST *source, BYTE **buffer, INT32 *size);


// Table 2:102 - Definition of TPML_DIGEST_VALUES Structure (StructureTable)
TPM_RC
TPML_DIGEST_VALUES_Unmarshal(TPML_DIGEST_VALUES *target, BYTE **buffer, INT32 *size);
UINT16
TPML_DIGEST_VALUES_Marshal(TPML_DIGEST_VALUES *source, BYTE **buffer, INT32 *size);


// Table 2:103 - Definition of TPML_PCR_SELECTION Structure (StructureTable)
TPM_RC
TPML_PCR_SELECTION_Unmarshal(TPML_PCR_SELECTION *target, BYTE **buffer, INT32 *size);
UINT16
TPML_PCR_SELECTION_Marshal(TPML_PCR_SELECTION *source, BYTE **buffer, INT32 *size);


// Table 2:104 - Definition of TPML_ALG_PROPERTY Structure  (StructureTable)
TPM_RC
TPML_ALG_PROPERTY_Unmarshal(TPML_ALG_PROPERTY *target, BYTE **buffer, INT32 *size);
UINT16
TPML_ALG_PROPERTY_Marshal(TPML_ALG_PROPERTY *source, BYTE **buffer, INT32 *size);


// Table 2:105 - Definition of TPML_TAGGED_TPM_PROPERTY Structure  (StructureTable)
TPM_RC
TPML_TAGGED_TPM_PROPERTY_Unmarshal(TPML_TAGGED_TPM_PROPERTY *target, BYTE **buffer, INT32 *size);
UINT16
TPML_TAGGED_TPM_PROPERTY_Marshal(TPML_TAGGED_TPM_PROPERTY *source, BYTE **buffer, INT32 *size);


// Table 2:106 - Definition of TPML_TAGGED_PCR_PROPERTY Structure  (StructureTable)
TPM_RC
TPML_TAGGED_PCR_PROPERTY_Unmarshal(TPML_TAGGED_PCR_PROPERTY *target, BYTE **buffer, INT32 *size);
UINT16
TPML_TAGGED_PCR_PROPERTY_Marshal(TPML_TAGGED_PCR_PROPERTY *source, BYTE **buffer, INT32 *size);


// Table 2:107 - Definition of TPML_ECC_CURVE Structure  (StructureTable)
#if         ALG_ECC
TPM_RC
TPML_ECC_CURVE_Unmarshal(TPML_ECC_CURVE *target, BYTE **buffer, INT32 *size);
UINT16
TPML_ECC_CURVE_Marshal(TPML_ECC_CURVE *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:108 - Definition of TPML_TAGGED_POLICY Structure  (StructureTable)
TPM_RC
TPML_TAGGED_POLICY_Unmarshal(TPML_TAGGED_POLICY *target, BYTE **buffer, INT32 *size);
UINT16
TPML_TAGGED_POLICY_Marshal(TPML_TAGGED_POLICY *source, BYTE **buffer, INT32 *size);


// Table 2:109 - Definition of TPMU_CAPABILITIES Union  (UnionTable)
TPM_RC
TPMU_CAPABILITIES_Unmarshal(TPMU_CAPABILITIES *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_CAPABILITIES_Marshal(TPMU_CAPABILITIES *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:110 - Definition of TPMS_CAPABILITY_DATA Structure  (StructureTable)
TPM_RC
TPMS_CAPABILITY_DATA_Unmarshal(TPMS_CAPABILITY_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CAPABILITY_DATA_Marshal(TPMS_CAPABILITY_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:111 - Definition of TPMS_CLOCK_INFO Structure (StructureTable)
TPM_RC
TPMS_CLOCK_INFO_Unmarshal(TPMS_CLOCK_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CLOCK_INFO_Marshal(TPMS_CLOCK_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:112 - Definition of TPMS_TIME_INFO Structure (StructureTable)
TPM_RC
TPMS_TIME_INFO_Unmarshal(TPMS_TIME_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_TIME_INFO_Marshal(TPMS_TIME_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:113 - Definition of TPMS_TIME_ATTEST_INFO Structure  (StructureTable)
TPM_RC
TPMS_TIME_ATTEST_INFO_Unmarshal(TPMS_TIME_ATTEST_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_TIME_ATTEST_INFO_Marshal(TPMS_TIME_ATTEST_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:114 - Definition of TPMS_CERTIFY_INFO Structure  (StructureTable)
TPM_RC
TPMS_CERTIFY_INFO_Unmarshal(TPMS_CERTIFY_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CERTIFY_INFO_Marshal(TPMS_CERTIFY_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:115 - Definition of TPMS_QUOTE_INFO Structure  (StructureTable)
TPM_RC
TPMS_QUOTE_INFO_Unmarshal(TPMS_QUOTE_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_QUOTE_INFO_Marshal(TPMS_QUOTE_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:116 - Definition of TPMS_COMMAND_AUDIT_INFO Structure  (StructureTable)
TPM_RC
TPMS_COMMAND_AUDIT_INFO_Unmarshal(TPMS_COMMAND_AUDIT_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_COMMAND_AUDIT_INFO_Marshal(TPMS_COMMAND_AUDIT_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:117 - Definition of TPMS_SESSION_AUDIT_INFO Structure  (StructureTable)
TPM_RC
TPMS_SESSION_AUDIT_INFO_Unmarshal(TPMS_SESSION_AUDIT_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SESSION_AUDIT_INFO_Marshal(TPMS_SESSION_AUDIT_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:118 - Definition of TPMS_CREATION_INFO Structure  (StructureTable)
TPM_RC
TPMS_CREATION_INFO_Unmarshal(TPMS_CREATION_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CREATION_INFO_Marshal(TPMS_CREATION_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:119 - Definition of TPMS_NV_CERTIFY_INFO Structure  (StructureTable)
TPM_RC
TPMS_NV_CERTIFY_INFO_Unmarshal(TPMS_NV_CERTIFY_INFO *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_NV_CERTIFY_INFO_Marshal(TPMS_NV_CERTIFY_INFO *source, BYTE **buffer, INT32 *size);


// Table 2:120 - Definition of TPMI_ST_ATTEST Type  (TypeTable)
#define TPMI_ST_ATTEST_Unmarshal(target, buffer, size) \
            TPM_ST_Unmarshal((TPM_ST *)(target), buffer, size)
#define TPMI_ST_ATTEST_Marshal(source, buffer, size) \
            TPM_ST_Marshal((TPM_ST *)(source), buffer, size)


// Table 2:121 - Definition of TPMU_ATTEST Union  (UnionTable)
TPM_RC
TPMU_ATTEST_Unmarshal(TPMU_ATTEST *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_ATTEST_Marshal(TPMU_ATTEST *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:122 - Definition of TPMS_ATTEST Structure  (StructureTable)
TPM_RC
TPMS_ATTEST_Unmarshal(TPMS_ATTEST *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ATTEST_Marshal(TPMS_ATTEST *source, BYTE **buffer, INT32 *size);


// Table 2:123 - Definition of TPM2B_ATTEST Structure  (StructureTable)
TPM_RC
TPM2B_ATTEST_Unmarshal(TPM2B_ATTEST *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ATTEST_Marshal(TPM2B_ATTEST *source, BYTE **buffer, INT32 *size);


// Table 2:124 - Definition of TPMS_AUTH_COMMAND Structure  (StructureTable)
TPM_RC
TPMS_AUTH_COMMAND_Unmarshal(TPMS_AUTH_COMMAND *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_AUTH_COMMAND_Marshal(TPMS_AUTH_COMMAND *source, BYTE **buffer, INT32 *size);


// Table 2:125 - Definition of TPMS_AUTH_RESPONSE Structure  (StructureTable)
TPM_RC
TPMS_AUTH_RESPONSE_Unmarshal(TPMS_AUTH_RESPONSE *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_AUTH_RESPONSE_Marshal(TPMS_AUTH_RESPONSE *source, BYTE **buffer, INT32 *size);


// Table 2:126 - Definition of TPMI_TDES_KEY_BITS Type (TypeTable)
#if         ALG_TDES
TPM_RC
TPMI_TDES_KEY_BITS_Unmarshal(TPMI_TDES_KEY_BITS *target, BYTE **buffer, INT32 *size);

#define TPMI_TDES_KEY_BITS_Marshal(source, buffer, size) \
            TPM_KEY_BITS_Marshal((TPM_KEY_BITS *)(source), buffer, size)
#endif // ALG_TDES


// Table 2:126 - Definition of TPMI_AES_KEY_BITS Type (TypeTable)
#if         ALG_AES
TPM_RC
TPMI_AES_KEY_BITS_Unmarshal(TPMI_AES_KEY_BITS *target, BYTE **buffer, INT32 *size);

#define TPMI_AES_KEY_BITS_Marshal(source, buffer, size) \
            TPM_KEY_BITS_Marshal((TPM_KEY_BITS *)(source), buffer, size)
#endif // ALG_AES


// Table 2:126 - Definition of TPMI_SM4_KEY_BITS Type (TypeTable)
#if         ALG_SM4
TPM_RC
TPMI_SM4_KEY_BITS_Unmarshal(TPMI_SM4_KEY_BITS *target, BYTE **buffer, INT32 *size);

#define TPMI_SM4_KEY_BITS_Marshal(source, buffer, size) \
            TPM_KEY_BITS_Marshal((TPM_KEY_BITS *)(source), buffer, size)
#endif // ALG_SM4


// Table 2:126 - Definition of TPMI_CAMELLIA_KEY_BITS Type (TypeTable)
#if         ALG_CAMELLIA
TPM_RC
TPMI_CAMELLIA_KEY_BITS_Unmarshal(TPMI_CAMELLIA_KEY_BITS *target, BYTE **buffer, INT32 *size);

#define TPMI_CAMELLIA_KEY_BITS_Marshal(source, buffer, size) \
            TPM_KEY_BITS_Marshal((TPM_KEY_BITS *)(source), buffer, size)
#endif // ALG_CAMELLIA


// Table 2:127 - Definition of TPMU_SYM_KEY_BITS Union (UnionTable)
TPM_RC
TPMU_SYM_KEY_BITS_Unmarshal(TPMU_SYM_KEY_BITS *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SYM_KEY_BITS_Marshal(TPMU_SYM_KEY_BITS *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:128 - Definition of TPMU_SYM_MODE Union (UnionTable)
TPM_RC
TPMU_SYM_MODE_Unmarshal(TPMU_SYM_MODE *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SYM_MODE_Marshal(TPMU_SYM_MODE *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:130 - Definition of TPMT_SYM_DEF Structure (StructureTable)
TPM_RC
TPMT_SYM_DEF_Unmarshal(TPMT_SYM_DEF *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_SYM_DEF_Marshal(TPMT_SYM_DEF *source, BYTE **buffer, INT32 *size);


// Table 2:131 - Definition of TPMT_SYM_DEF_OBJECT Structure (StructureTable)
TPM_RC
TPMT_SYM_DEF_OBJECT_Unmarshal(TPMT_SYM_DEF_OBJECT *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_SYM_DEF_OBJECT_Marshal(TPMT_SYM_DEF_OBJECT *source, BYTE **buffer, INT32 *size);


// Table 2:132 - Definition of TPM2B_SYM_KEY Structure (StructureTable)
TPM_RC
TPM2B_SYM_KEY_Unmarshal(TPM2B_SYM_KEY *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SYM_KEY_Marshal(TPM2B_SYM_KEY *source, BYTE **buffer, INT32 *size);


// Table 2:133 - Definition of TPMS_SYMCIPHER_PARMS Structure (StructureTable)
#define TPMS_SYMCIPHER_PARMS_Unmarshal(target, buffer, size) \
            TPMT_SYM_DEF_OBJECT_Unmarshal((TPMT_SYM_DEF_OBJECT *)&((target)->sym), buffer, size, 0)
#define TPMS_SYMCIPHER_PARMS_Marshal(source, buffer, size) \
            TPMT_SYM_DEF_OBJECT_Marshal((TPMT_SYM_DEF_OBJECT *)&((source)->sym), buffer, size)


// Table 2:134 - Definition of TPM2B_LABEL Structure (StructureTable)
TPM_RC
TPM2B_LABEL_Unmarshal(TPM2B_LABEL *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_LABEL_Marshal(TPM2B_LABEL *source, BYTE **buffer, INT32 *size);


// Table 2:135 - Definition of TPMS_DERIVE Structure (StructureTable)
TPM_RC
TPMS_DERIVE_Unmarshal(TPMS_DERIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_DERIVE_Marshal(TPMS_DERIVE *source, BYTE **buffer, INT32 *size);


// Table 2:136 - Definition of TPM2B_DERIVE Structure (StructureTable)
TPM_RC
TPM2B_DERIVE_Unmarshal(TPM2B_DERIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_DERIVE_Marshal(TPM2B_DERIVE *source, BYTE **buffer, INT32 *size);


// Table 2:137 - Definition of TPMU_SENSITIVE_CREATE Union  (UnionTable)


// Table 2:138 - Definition of TPM2B_SENSITIVE_DATA Structure (StructureTable)
TPM_RC
TPM2B_SENSITIVE_DATA_Unmarshal(TPM2B_SENSITIVE_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SENSITIVE_DATA_Marshal(TPM2B_SENSITIVE_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:139 - Definition of TPMS_SENSITIVE_CREATE Structure  (StructureTable)
TPM_RC
TPMS_SENSITIVE_CREATE_Unmarshal(TPMS_SENSITIVE_CREATE *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SENSITIVE_CREATE_Marshal(TPMS_SENSITIVE_CREATE *source, BYTE **buffer, INT32 *size);


// Table 2:140 - Definition of TPM2B_SENSITIVE_CREATE Structure  (StructureTable)
#ifdef UT_BYTE_TPM2B_SENSITIVE_CREATE
TPM_RC
TPM2B_SENSITIVE_CREATE_Unmarshal(TPM2B_SENSITIVE_CREATE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SENSITIVE_CREATE_Marshal(TPM2B_SENSITIVE_CREATE *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_SENSITIVE_CREATE_Unmarshal(TPM2B_SENSITIVE_CREATE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SENSITIVE_CREATE_Marshal(TPM2B_SENSITIVE_CREATE *source, BYTE **buffer, INT32 *size);

#endif


// Table 2:141 - Definition of TPMS_SCHEME_HASH Structure (StructureTable)
#define TPMS_SCHEME_HASH_Unmarshal(target, buffer, size) \
            TPMI_ALG_HASH_Unmarshal((TPMI_ALG_HASH *)&((target)->hashAlg), buffer, size, 0)
#define TPMS_SCHEME_HASH_Marshal(source, buffer, size) \
            TPMI_ALG_HASH_Marshal((TPMI_ALG_HASH *)&((source)->hashAlg), buffer, size)


// Table 2:142 - Definition of TPMS_SCHEME_ECDAA Structure (StructureTable)
#if         ALG_ECC
TPM_RC
TPMS_SCHEME_ECDAA_Unmarshal(TPMS_SCHEME_ECDAA *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SCHEME_ECDAA_Marshal(TPMS_SCHEME_ECDAA *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:143 - Definition of TPMI_ALG_KEYEDHASH_SCHEME Type (TypeTable)
TPM_RC
TPMI_ALG_KEYEDHASH_SCHEME_Unmarshal(TPMI_ALG_KEYEDHASH_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_KEYEDHASH_SCHEME_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:144 - Definition of Types for HMAC_SIG_SCHEME (TypesTable)
//   TPMS_SCHEME_HASH definition from table 2:144
#define TPMS_SCHEME_HMAC_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SCHEME_HMAC_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)


// Table 2:145 - Definition of TPMS_SCHEME_XOR Structure (StructureTable)
TPM_RC
TPMS_SCHEME_XOR_Unmarshal(TPMS_SCHEME_XOR *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SCHEME_XOR_Marshal(TPMS_SCHEME_XOR *source, BYTE **buffer, INT32 *size);


// Table 2:146 - Definition of TPMU_SCHEME_KEYEDHASH Union  (UnionTable)
TPM_RC
TPMU_SCHEME_KEYEDHASH_Unmarshal(TPMU_SCHEME_KEYEDHASH *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SCHEME_KEYEDHASH_Marshal(TPMU_SCHEME_KEYEDHASH *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:147 - Definition of TPMT_KEYEDHASH_SCHEME Structure (StructureTable)
TPM_RC
TPMT_KEYEDHASH_SCHEME_Unmarshal(TPMT_KEYEDHASH_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_KEYEDHASH_SCHEME_Marshal(TPMT_KEYEDHASH_SCHEME *source, BYTE **buffer, INT32 *size);


// Table 2:148 - Definition of Types for RSA Signature Schemes  (TypesTable)
#if         ALG_RSA
//   TPMS_SCHEME_HASH definition from table 2:148
#if         ALG_RSA
#define TPMS_SIG_SCHEME_RSASSA_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SIG_SCHEME_RSASSA_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_RSA
//   TPMS_SCHEME_HASH definition from table 2:148
#if         ALG_RSA
#define TPMS_SIG_SCHEME_RSAPSS_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SIG_SCHEME_RSAPSS_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_RSA
#endif // ALG_RSA


// Table 2:149 - Definition of Types for ECC Signature Schemes  (TypesTable)
#if         ALG_ECC
//   TPMS_SCHEME_HASH definition from table 2:149
#if         ALG_ECC
#define TPMS_SIG_SCHEME_ECDSA_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SIG_SCHEME_ECDSA_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SCHEME_HASH definition from table 2:149
#if         ALG_ECC
#define TPMS_SIG_SCHEME_SM2_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SIG_SCHEME_SM2_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SCHEME_HASH definition from table 2:149
#if         ALG_ECC
#define TPMS_SIG_SCHEME_ECSCHNORR_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SIG_SCHEME_ECSCHNORR_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SCHEME_ECDAA definition from table 2:149
#if         ALG_ECC
#define TPMS_SIG_SCHEME_ECDAA_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_ECDAA_Unmarshal((TPMS_SCHEME_ECDAA *)(target), buffer, size)
#define TPMS_SIG_SCHEME_ECDAA_Marshal(source, buffer, size) \
            TPMS_SCHEME_ECDAA_Marshal((TPMS_SCHEME_ECDAA *)(source), buffer, size)
#endif // ALG_ECC
#endif // ALG_ECC


// Table 2:150 - Definition of TPMU_SIG_SCHEME Union  (UnionTable)
TPM_RC
TPMU_SIG_SCHEME_Unmarshal(TPMU_SIG_SCHEME *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SIG_SCHEME_Marshal(TPMU_SIG_SCHEME *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:151 - Definition of TPMT_SIG_SCHEME Structure (StructureTable)
TPM_RC
TPMT_SIG_SCHEME_Unmarshal(TPMT_SIG_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_SIG_SCHEME_Marshal(TPMT_SIG_SCHEME *source, BYTE **buffer, INT32 *size);


// Table 2:152 - Definition of Types for Encryption Schemes (TypesTable)
#if         ALG_RSA
//   TPMS_SCHEME_HASH definition from table 2:152
#if         ALG_RSA
#define TPMS_ENC_SCHEME_OAEP_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_ENC_SCHEME_OAEP_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_RSA
//   TPMS_EMPTY definition from table 2:152
#if         ALG_RSA
#define TPMS_ENC_SCHEME_RSAES_Unmarshal(target, buffer, size) \
            TPMS_EMPTY_Unmarshal((TPMS_EMPTY *)(target), buffer, size)
#define TPMS_ENC_SCHEME_RSAES_Marshal(source, buffer, size) \
            TPMS_EMPTY_Marshal((TPMS_EMPTY *)(source), buffer, size)
#endif // ALG_RSA
#endif // ALG_RSA


// Table 2:153 - Definition of Types for ECC Key Exchange (TypesTable)
#if         ALG_ECC
//   TPMS_SCHEME_HASH definition from table 2:153
#if         ALG_ECC
#define TPMS_KEY_SCHEME_ECDH_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_KEY_SCHEME_ECDH_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SCHEME_HASH definition from table 2:153
#if         ALG_ECC
#define TPMS_KEY_SCHEME_ECMQV_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_KEY_SCHEME_ECMQV_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
#endif // ALG_ECC
#endif // ALG_ECC


// Table 2:154 - Definition of Types for KDF Schemes (TypesTable)
//   TPMS_SCHEME_HASH definition from table 2:154
#define TPMS_SCHEME_MGF1_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SCHEME_MGF1_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
//   TPMS_SCHEME_HASH definition from table 2:154
#define TPMS_SCHEME_KDF1_SP800_56A_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SCHEME_KDF1_SP800_56A_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
//   TPMS_SCHEME_HASH definition from table 2:154
#define TPMS_SCHEME_KDF2_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SCHEME_KDF2_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)
//   TPMS_SCHEME_HASH definition from table 2:154
#define TPMS_SCHEME_KDF1_SP800_108_Unmarshal(target, buffer, size) \
            TPMS_SCHEME_HASH_Unmarshal((TPMS_SCHEME_HASH *)(target), buffer, size)
#define TPMS_SCHEME_KDF1_SP800_108_Marshal(source, buffer, size) \
            TPMS_SCHEME_HASH_Marshal((TPMS_SCHEME_HASH *)(source), buffer, size)


// Table 2:155 - Definition of TPMU_KDF_SCHEME Union  (UnionTable)
TPM_RC
TPMU_KDF_SCHEME_Unmarshal(TPMU_KDF_SCHEME *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_KDF_SCHEME_Marshal(TPMU_KDF_SCHEME *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:156 - Definition of TPMT_KDF_SCHEME Structure (StructureTable)
TPM_RC
TPMT_KDF_SCHEME_Unmarshal(TPMT_KDF_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_KDF_SCHEME_Marshal(TPMT_KDF_SCHEME *source, BYTE **buffer, INT32 *size);


// Table 2:157 - Definition of TPMI_ALG_ASYM_SCHEME Type  (TypeTable)
TPM_RC
TPMI_ALG_ASYM_SCHEME_Unmarshal(TPMI_ALG_ASYM_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_ASYM_SCHEME_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:158 - Definition of TPMU_ASYM_SCHEME Union (UnionTable)
TPM_RC
TPMU_ASYM_SCHEME_Unmarshal(TPMU_ASYM_SCHEME *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_ASYM_SCHEME_Marshal(TPMU_ASYM_SCHEME *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:159 - Definition of TPMT_ASYM_SCHEME Structure  (StructureTable)
TPM_RC
TPMT_ASYM_SCHEME_Unmarshal(TPMT_ASYM_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_ASYM_SCHEME_Marshal(TPMT_ASYM_SCHEME *source, BYTE **buffer, INT32 *size);


// Table 2:160 - Definition of TPMI_ALG_RSA_SCHEME Type (TypeTable)
#if         ALG_RSA
TPM_RC
TPMI_ALG_RSA_SCHEME_Unmarshal(TPMI_ALG_RSA_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_RSA_SCHEME_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)
#endif // ALG_RSA


// Table 2:161 - Definition of TPMT_RSA_SCHEME Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPMT_RSA_SCHEME_Unmarshal(TPMT_RSA_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_RSA_SCHEME_Marshal(TPMT_RSA_SCHEME *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:162 - Definition of TPMI_ALG_RSA_DECRYPT Type (TypeTable)
#if         ALG_RSA
TPM_RC
TPMI_ALG_RSA_DECRYPT_Unmarshal(TPMI_ALG_RSA_DECRYPT *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_RSA_DECRYPT_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)
#endif // ALG_RSA


// Table 2:163 - Definition of TPMT_RSA_DECRYPT Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPMT_RSA_DECRYPT_Unmarshal(TPMT_RSA_DECRYPT *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_RSA_DECRYPT_Marshal(TPMT_RSA_DECRYPT *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:164 - Definition of TPM2B_PUBLIC_KEY_RSA Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPM2B_PUBLIC_KEY_RSA_Unmarshal(TPM2B_PUBLIC_KEY_RSA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_PUBLIC_KEY_RSA_Marshal(TPM2B_PUBLIC_KEY_RSA *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:165 - Definition of TPMI_RSA_KEY_BITS Type (TypeTable)
#if         ALG_RSA
TPM_RC
TPMI_RSA_KEY_BITS_Unmarshal(TPMI_RSA_KEY_BITS *target, BYTE **buffer, INT32 *size);

#define TPMI_RSA_KEY_BITS_Marshal(source, buffer, size) \
            TPM_KEY_BITS_Marshal((TPM_KEY_BITS *)(source), buffer, size)
#endif // ALG_RSA


// Table 2:166 - Definition of TPM2B_PRIVATE_KEY_RSA Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPM2B_PRIVATE_KEY_RSA_Unmarshal(TPM2B_PRIVATE_KEY_RSA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_PRIVATE_KEY_RSA_Marshal(TPM2B_PRIVATE_KEY_RSA *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:167 - Definition of TPM2B_ECC_PARAMETER Structure (StructureTable)
TPM_RC
TPM2B_ECC_PARAMETER_Unmarshal(TPM2B_ECC_PARAMETER *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ECC_PARAMETER_Marshal(TPM2B_ECC_PARAMETER *source, BYTE **buffer, INT32 *size);


// Table 2:168 - Definition of TPMS_ECC_POINT Structure (StructureTable)
#if         ALG_ECC
TPM_RC
TPMS_ECC_POINT_Unmarshal(TPMS_ECC_POINT *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ECC_POINT_Marshal(TPMS_ECC_POINT *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:169 - Definition of TPM2B_ECC_POINT Structure (StructureTable)
#if         ALG_ECC
#ifdef UT_BYTE_TPM2B_ECC_POINT
TPM_RC
TPM2B_ECC_POINT_Unmarshal(TPM2B_ECC_POINT *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ECC_POINT_Marshal(TPM2B_ECC_POINT *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_ECC_POINT_Unmarshal(TPM2B_ECC_POINT *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ECC_POINT_Marshal(TPM2B_ECC_POINT *source, BYTE **buffer, INT32 *size);

#endif
#endif // ALG_ECC


// Table 2:170 - Definition of TPMI_ALG_ECC_SCHEME Type (TypeTable)
#if         ALG_ECC
TPM_RC
TPMI_ALG_ECC_SCHEME_Unmarshal(TPMI_ALG_ECC_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);

#define TPMI_ALG_ECC_SCHEME_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)
#endif // ALG_ECC


// Table 2:171 - Definition of TPMI_ECC_CURVE Type (TypeTable)
#if         ALG_ECC
TPM_RC
TPMI_ECC_CURVE_Unmarshal(TPMI_ECC_CURVE *target, BYTE **buffer, INT32 *size);

#define TPMI_ECC_CURVE_Marshal(source, buffer, size) \
            TPM_ECC_CURVE_Marshal((TPM_ECC_CURVE *)(source), buffer, size)
#endif // ALG_ECC


// Table 2:172 - Definition of TPMT_ECC_SCHEME Structure (StructureTable)
#if         ALG_ECC
TPM_RC
TPMT_ECC_SCHEME_Unmarshal(TPMT_ECC_SCHEME *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_ECC_SCHEME_Marshal(TPMT_ECC_SCHEME *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:173 - Definition of TPMS_ALGORITHM_DETAIL_ECC Structure  (StructureTable)
#if         ALG_ECC
TPM_RC
TPMS_ALGORITHM_DETAIL_ECC_Unmarshal(TPMS_ALGORITHM_DETAIL_ECC *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ALGORITHM_DETAIL_ECC_Marshal(TPMS_ALGORITHM_DETAIL_ECC *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:174 - Definition of TPMS_SIGNATURE_RSA Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPMS_SIGNATURE_RSA_Unmarshal(TPMS_SIGNATURE_RSA *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SIGNATURE_RSA_Marshal(TPMS_SIGNATURE_RSA *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:175 - Definition of Types for Signature  (TypesTable)
#if         ALG_RSA
//   TPMS_SIGNATURE_RSA definition from table 2:175
#if         ALG_RSA
#define TPMS_SIGNATURE_RSASSA_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_RSA_Unmarshal((TPMS_SIGNATURE_RSA *)(target), buffer, size)
#define TPMS_SIGNATURE_RSASSA_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_RSA_Marshal((TPMS_SIGNATURE_RSA *)(source), buffer, size)
#endif // ALG_RSA
//   TPMS_SIGNATURE_RSA definition from table 2:175
#if         ALG_RSA
#define TPMS_SIGNATURE_RSAPSS_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_RSA_Unmarshal((TPMS_SIGNATURE_RSA *)(target), buffer, size)
#define TPMS_SIGNATURE_RSAPSS_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_RSA_Marshal((TPMS_SIGNATURE_RSA *)(source), buffer, size)
#endif // ALG_RSA
#endif // ALG_RSA


// Table 2:176 - Definition of TPMS_SIGNATURE_ECC Structure (StructureTable)
#if         ALG_ECC
TPM_RC
TPMS_SIGNATURE_ECC_Unmarshal(TPMS_SIGNATURE_ECC *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_SIGNATURE_ECC_Marshal(TPMS_SIGNATURE_ECC *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:177 - Definition of Types for TPMS_SIGNATURE_ECC (TypesTable)
#if         ALG_ECC
//   TPMS_SIGNATURE_ECC definition from table 2:177
#if         ALG_ECC
#define TPMS_SIGNATURE_ECDAA_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_ECC_Unmarshal((TPMS_SIGNATURE_ECC *)(target), buffer, size)
#define TPMS_SIGNATURE_ECDAA_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_ECC_Marshal((TPMS_SIGNATURE_ECC *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SIGNATURE_ECC definition from table 2:177
#if         ALG_ECC
#define TPMS_SIGNATURE_ECDSA_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_ECC_Unmarshal((TPMS_SIGNATURE_ECC *)(target), buffer, size)
#define TPMS_SIGNATURE_ECDSA_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_ECC_Marshal((TPMS_SIGNATURE_ECC *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SIGNATURE_ECC definition from table 2:177
#if         ALG_ECC
#define TPMS_SIGNATURE_SM2_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_ECC_Unmarshal((TPMS_SIGNATURE_ECC *)(target), buffer, size)
#define TPMS_SIGNATURE_SM2_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_ECC_Marshal((TPMS_SIGNATURE_ECC *)(source), buffer, size)
#endif // ALG_ECC
//   TPMS_SIGNATURE_ECC definition from table 2:177
#if         ALG_ECC
#define TPMS_SIGNATURE_ECSCHNORR_Unmarshal(target, buffer, size) \
            TPMS_SIGNATURE_ECC_Unmarshal((TPMS_SIGNATURE_ECC *)(target), buffer, size)
#define TPMS_SIGNATURE_ECSCHNORR_Marshal(source, buffer, size) \
            TPMS_SIGNATURE_ECC_Marshal((TPMS_SIGNATURE_ECC *)(source), buffer, size)
#endif // ALG_ECC
#endif // ALG_ECC


// Table 2:178 - Definition of TPMU_SIGNATURE Union  (UnionTable)
TPM_RC
TPMU_SIGNATURE_Unmarshal(TPMU_SIGNATURE *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SIGNATURE_Marshal(TPMU_SIGNATURE *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:179 - Definition of TPMT_SIGNATURE Structure (StructureTable)
TPM_RC
TPMT_SIGNATURE_Unmarshal(TPMT_SIGNATURE *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_SIGNATURE_Marshal(TPMT_SIGNATURE *source, BYTE **buffer, INT32 *size);


// Table 2:180 - Definition of TPMU_ENCRYPTED_SECRET Union  (UnionTable)
TPM_RC
TPMU_ENCRYPTED_SECRET_Unmarshal(TPMU_ENCRYPTED_SECRET *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_ENCRYPTED_SECRET_Marshal(TPMU_ENCRYPTED_SECRET *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:181 - Definition of TPM2B_ENCRYPTED_SECRET Structure (StructureTable)
TPM_RC
TPM2B_ENCRYPTED_SECRET_Unmarshal(TPM2B_ENCRYPTED_SECRET *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ENCRYPTED_SECRET_Marshal(TPM2B_ENCRYPTED_SECRET *source, BYTE **buffer, INT32 *size);


// Table 2:182 - Definition of TPMI_ALG_PUBLIC Type (TypeTable)
TPM_RC
TPMI_ALG_PUBLIC_Unmarshal(TPMI_ALG_PUBLIC *target, BYTE **buffer, INT32 *size);

#define TPMI_ALG_PUBLIC_Marshal(source, buffer, size) \
            TPM_ALG_ID_Marshal((TPM_ALG_ID *)(source), buffer, size)


// Table 2:183 - Definition of TPMU_PUBLIC_ID Union  (UnionTable)
TPM_RC
TPMU_PUBLIC_ID_Unmarshal(TPMU_PUBLIC_ID *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_PUBLIC_ID_Marshal(TPMU_PUBLIC_ID *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:184 - Definition of TPMS_KEYEDHASH_PARMS Structure (StructureTable)
#define TPMS_KEYEDHASH_PARMS_Unmarshal(target, buffer, size) \
            TPMT_KEYEDHASH_SCHEME_Unmarshal((TPMT_KEYEDHASH_SCHEME *)&((target)->scheme), buffer, size, 1)
#define TPMS_KEYEDHASH_PARMS_Marshal(source, buffer, size) \
            TPMT_KEYEDHASH_SCHEME_Marshal((TPMT_KEYEDHASH_SCHEME *)&((source)->scheme), buffer, size)


// Table 2:185 - Definition of TPMS_ASYM_PARMS Structure  (StructureTable)
TPM_RC
TPMS_ASYM_PARMS_Unmarshal(TPMS_ASYM_PARMS *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ASYM_PARMS_Marshal(TPMS_ASYM_PARMS *source, BYTE **buffer, INT32 *size);


// Table 2:186 - Definition of TPMS_RSA_PARMS Structure (StructureTable)
#if         ALG_RSA
TPM_RC
TPMS_RSA_PARMS_Unmarshal(TPMS_RSA_PARMS *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_RSA_PARMS_Marshal(TPMS_RSA_PARMS *source, BYTE **buffer, INT32 *size);

#endif // ALG_RSA


// Table 2:187 - Definition of TPMS_ECC_PARMS Structure (StructureTable)
#if         ALG_ECC
TPM_RC
TPMS_ECC_PARMS_Unmarshal(TPMS_ECC_PARMS *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ECC_PARMS_Marshal(TPMS_ECC_PARMS *source, BYTE **buffer, INT32 *size);

#endif // ALG_ECC


// Table 2:188 - Definition of TPMU_PUBLIC_PARMS Union  (UnionTable)
TPM_RC
TPMU_PUBLIC_PARMS_Unmarshal(TPMU_PUBLIC_PARMS *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_PUBLIC_PARMS_Marshal(TPMU_PUBLIC_PARMS *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:189 - Definition of TPMT_PUBLIC_PARMS Structure (StructureTable)
TPM_RC
TPMT_PUBLIC_PARMS_Unmarshal(TPMT_PUBLIC_PARMS *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_PUBLIC_PARMS_Marshal(TPMT_PUBLIC_PARMS *source, BYTE **buffer, INT32 *size);


// Table 2:190 - Definition of TPMT_PUBLIC Structure (StructureTable)
TPM_RC
TPMT_PUBLIC_Unmarshal(TPMT_PUBLIC *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPMT_PUBLIC_Marshal(TPMT_PUBLIC *source, BYTE **buffer, INT32 *size);


// Table 2:191 - Definition of TPM2B_PUBLIC Structure (StructureTable)
#ifdef UT_BYTE_TPM2B_PUBLIC
TPM_RC
TPM2B_PUBLIC_Unmarshal(TPM2B_PUBLIC *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_PUBLIC_Marshal(TPM2B_PUBLIC *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_PUBLIC_Unmarshal(TPM2B_PUBLIC *target, BYTE **buffer, INT32 *size, BOOL flag);
UINT16
TPM2B_PUBLIC_Marshal(TPM2B_PUBLIC *source, BYTE **buffer, INT32 *size);

#endif


// Table 2:192 - Definition of TPM2B_TEMPLATE Structure (StructureTable)
TPM_RC
TPM2B_TEMPLATE_Unmarshal(TPM2B_TEMPLATE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_TEMPLATE_Marshal(TPM2B_TEMPLATE *source, BYTE **buffer, INT32 *size);


// Table 2:193 - Definition of TPM2B_PRIVATE_VENDOR_SPECIFIC Structure (StructureTable)
TPM_RC
TPM2B_PRIVATE_VENDOR_SPECIFIC_Unmarshal(TPM2B_PRIVATE_VENDOR_SPECIFIC *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_PRIVATE_VENDOR_SPECIFIC_Marshal(TPM2B_PRIVATE_VENDOR_SPECIFIC *source, BYTE **buffer, INT32 *size);


// Table 2:194 - Definition of TPMU_SENSITIVE_COMPOSITE Union  (UnionTable)
TPM_RC
TPMU_SENSITIVE_COMPOSITE_Unmarshal(TPMU_SENSITIVE_COMPOSITE *target, BYTE **buffer, INT32 *size, UINT32 selector);
UINT16
TPMU_SENSITIVE_COMPOSITE_Marshal(TPMU_SENSITIVE_COMPOSITE *source, BYTE **buffer, INT32 *size, UINT32 selector);


// Table 2:195 - Definition of TPMT_SENSITIVE Structure (StructureTable)
TPM_RC
TPMT_SENSITIVE_Unmarshal(TPMT_SENSITIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPMT_SENSITIVE_Marshal(TPMT_SENSITIVE *source, BYTE **buffer, INT32 *size);


// Table 2:196 - Definition of TPM2B_SENSITIVE Structure  (StructureTable)
#ifdef UT_BYTE_TPM2B_SENSITIVE
TPM_RC
TPM2B_SENSITIVE_Unmarshal(TPM2B_SENSITIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SENSITIVE_Marshal(TPM2B_SENSITIVE *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_SENSITIVE_Unmarshal(TPM2B_SENSITIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_SENSITIVE_Marshal(TPM2B_SENSITIVE *source, BYTE **buffer, INT32 *size);

#endif


// Table 2:197 - Definition of _PRIVATE Structure  (StructureTable)
TPM_RC
_PRIVATE_Unmarshal(_PRIVATE *target, BYTE **buffer, INT32 *size);
UINT16
_PRIVATE_Marshal(_PRIVATE *source, BYTE **buffer, INT32 *size);


// Table 2:198 - Definition of TPM2B_PRIVATE Structure  (StructureTable)
TPM_RC
TPM2B_PRIVATE_Unmarshal(TPM2B_PRIVATE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_PRIVATE_Marshal(TPM2B_PRIVATE *source, BYTE **buffer, INT32 *size);


// Table 2:199 - Definition of TPMS_ID_OBJECT Structure  (StructureTable)
TPM_RC
TPMS_ID_OBJECT_Unmarshal(TPMS_ID_OBJECT *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_ID_OBJECT_Marshal(TPMS_ID_OBJECT *source, BYTE **buffer, INT32 *size);


// Table 2:200 - Definition of TPM2B_ID_OBJECT Structure  (StructureTable)
TPM_RC
TPM2B_ID_OBJECT_Unmarshal(TPM2B_ID_OBJECT *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_ID_OBJECT_Marshal(TPM2B_ID_OBJECT *source, BYTE **buffer, INT32 *size);


// Table 2:201 - Definition of TPM_NV_INDEX Bits  (BitsTable)
#define TPM_NV_INDEX_Unmarshal(target, buffer, size) \
            UINT32_Unmarshal((UINT32 *)(target), buffer, size)
#define TPM_NV_INDEX_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:203 - Definition of TPMS_NV_PIN_COUNTER_PARAMETERS Structure (StructureTable)
TPM_RC
TPMS_NV_PIN_COUNTER_PARAMETERS_Unmarshal(TPMS_NV_PIN_COUNTER_PARAMETERS *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_NV_PIN_COUNTER_PARAMETERS_Marshal(TPMS_NV_PIN_COUNTER_PARAMETERS *source, BYTE **buffer, INT32 *size);


// Table 2:204 - Definition of TPMA_NV Bits (BitsTable)
TPM_RC
TPMA_NV_Unmarshal(TPMA_NV *target, BYTE **buffer, INT32 *size);

#define TPMA_NV_Marshal(source, buffer, size) \
            UINT32_Marshal((UINT32 *)(source), buffer, size)


// Table 2:205 - Definition of TPMS_NV_PUBLIC Structure (StructureTable)
TPM_RC
TPMS_NV_PUBLIC_Unmarshal(TPMS_NV_PUBLIC *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_NV_PUBLIC_Marshal(TPMS_NV_PUBLIC *source, BYTE **buffer, INT32 *size);


// Table 2:206 - Definition of TPM2B_NV_PUBLIC Structure (StructureTable)
#ifdef UT_BYTE_TPM2B_NV_PUBLIC
TPM_RC
TPM2B_NV_PUBLIC_Unmarshal(TPM2B_NV_PUBLIC *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_NV_PUBLIC_Marshal(TPM2B_NV_PUBLIC *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_NV_PUBLIC_Unmarshal(TPM2B_NV_PUBLIC *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_NV_PUBLIC_Marshal(TPM2B_NV_PUBLIC *source, BYTE **buffer, INT32 *size);

#endif


// Table 2:207 - Definition of TPM2B_CONTEXT_SENSITIVE Structure  (StructureTable)
TPM_RC
TPM2B_CONTEXT_SENSITIVE_Unmarshal(TPM2B_CONTEXT_SENSITIVE *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_CONTEXT_SENSITIVE_Marshal(TPM2B_CONTEXT_SENSITIVE *source, BYTE **buffer, INT32 *size);


// Table 2:208 - Definition of TPMS_CONTEXT_DATA Structure  (StructureTable)
TPM_RC
TPMS_CONTEXT_DATA_Unmarshal(TPMS_CONTEXT_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CONTEXT_DATA_Marshal(TPMS_CONTEXT_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:209 - Definition of TPM2B_CONTEXT_DATA Structure  (StructureTable)
TPM_RC
TPM2B_CONTEXT_DATA_Unmarshal(TPM2B_CONTEXT_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_CONTEXT_DATA_Marshal(TPM2B_CONTEXT_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:210 - Definition of TPMS_CONTEXT Structure (StructureTable)
TPM_RC
TPMS_CONTEXT_Unmarshal(TPMS_CONTEXT *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CONTEXT_Marshal(TPMS_CONTEXT *source, BYTE **buffer, INT32 *size);


// Table 2:212 - Definition of TPMS_CREATION_DATA Structure  (StructureTable)
TPM_RC
TPMS_CREATION_DATA_Unmarshal(TPMS_CREATION_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPMS_CREATION_DATA_Marshal(TPMS_CREATION_DATA *source, BYTE **buffer, INT32 *size);


// Table 2:213 - Definition of TPM2B_CREATION_DATA Structure  (StructureTable)
#ifdef UT_BYTE_TPM2B_CREATION_DATA
TPM_RC
TPM2B_CREATION_DATA_Unmarshal(TPM2B_CREATION_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_CREATION_DATA_Marshal(TPM2B_CREATION_DATA *source, BYTE **buffer, INT32 *size);

#else
TPM_RC
TPM2B_CREATION_DATA_Unmarshal(TPM2B_CREATION_DATA *target, BYTE **buffer, INT32 *size);
UINT16
TPM2B_CREATION_DATA_Marshal(TPM2B_CREATION_DATA *source, BYTE **buffer, INT32 *size);

#endif
// Array Marshal/Unmarshal for BYTE
TPM_RC
BYTE_Array_Unmarshal(BYTE *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
BYTE_Array_Marshal(BYTE *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPM2B_DIGEST
TPM_RC
TPM2B_DIGEST_Array_Unmarshal(TPM2B_DIGEST *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPM2B_DIGEST_Array_Marshal(TPM2B_DIGEST *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMA_CC
TPM_RC
TPMA_CC_Array_Unmarshal(TPMA_CC *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMA_CC_Array_Marshal(TPMA_CC *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMS_ALG_PROPERTY
TPM_RC
TPMS_ALG_PROPERTY_Array_Unmarshal(TPMS_ALG_PROPERTY *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMS_ALG_PROPERTY_Array_Marshal(TPMS_ALG_PROPERTY *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMS_PCR_SELECTION
TPM_RC
TPMS_PCR_SELECTION_Array_Unmarshal(TPMS_PCR_SELECTION *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMS_PCR_SELECTION_Array_Marshal(TPMS_PCR_SELECTION *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMS_TAGGED_PCR_SELECT
TPM_RC
TPMS_TAGGED_PCR_SELECT_Array_Unmarshal(TPMS_TAGGED_PCR_SELECT *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMS_TAGGED_PCR_SELECT_Array_Marshal(TPMS_TAGGED_PCR_SELECT *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMS_TAGGED_POLICY
TPM_RC
TPMS_TAGGED_POLICY_Array_Unmarshal(TPMS_TAGGED_POLICY *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMS_TAGGED_POLICY_Array_Marshal(TPMS_TAGGED_POLICY *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMS_TAGGED_PROPERTY
TPM_RC
TPMS_TAGGED_PROPERTY_Array_Unmarshal(TPMS_TAGGED_PROPERTY *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPMS_TAGGED_PROPERTY_Array_Marshal(TPMS_TAGGED_PROPERTY *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPMT_HA
TPM_RC
TPMT_HA_Array_Unmarshal(TPMT_HA *target, BYTE **buffer, INT32 *size, BOOL flag, INT32 count);
UINT16
TPMT_HA_Array_Marshal(TPMT_HA *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPM_ALG_ID
TPM_RC
TPM_ALG_ID_Array_Unmarshal(TPM_ALG_ID *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPM_ALG_ID_Array_Marshal(TPM_ALG_ID *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPM_CC
TPM_RC
TPM_CC_Array_Unmarshal(TPM_CC *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPM_CC_Array_Marshal(TPM_CC *source, BYTE **buffer, INT32 *size, INT32 count);

// Array Marshal/Unmarshal for TPM_ECC_CURVE
#if         ALG_ECC
TPM_RC
TPM_ECC_CURVE_Array_Unmarshal(TPM_ECC_CURVE *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPM_ECC_CURVE_Array_Marshal(TPM_ECC_CURVE *source, BYTE **buffer, INT32 *size, INT32 count);

#endif // ALG_ECC
// Array Marshal/Unmarshal for TPM_HANDLE
TPM_RC
TPM_HANDLE_Array_Unmarshal(TPM_HANDLE *target, BYTE **buffer, INT32 *size, INT32 count);
UINT16
TPM_HANDLE_Array_Marshal(TPM_HANDLE *source, BYTE **buffer, INT32 *size, INT32 count);

#endif // _MARSHAL_FP_H
