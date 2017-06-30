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

    Created by TpmStructures Version 2.7 Sept 13, 2016
    This file created on Apr  6, 2017, 08:39:16PM 

*/


#ifndef _TPM_TYPES_H_
#define _TPM_TYPES_H_
// Table 2:5 - Definition of Types for Documentation Clarity (TypedefTable)
typedef  UINT32             TPM_ALGORITHM_ID;
typedef  UINT32             TPM_MODIFIER_INDICATOR;
typedef  UINT32             TPM_AUTHORIZATION_SIZE;
typedef  UINT32             TPM_PARAMETER_SIZE;
typedef  UINT16             TPM_KEY_SIZE;
typedef  UINT16             TPM_KEY_BITS;

// Table 2:6 - Definition of TPM_SPEC Constants  (EnumTable)
typedef  UINT32             TPM_SPEC;
#define  SPEC_FAMILY             0x322E3000
#define  TPM_SPEC_FAMILY         (TPM_SPEC)(SPEC_FAMILY)
#define  SPEC_LEVEL              00
#define  TPM_SPEC_LEVEL          (TPM_SPEC)(SPEC_LEVEL)
#define  SPEC_VERSION            144
#define  TPM_SPEC_VERSION        (TPM_SPEC)(SPEC_VERSION)
#define  SPEC_YEAR               2017
#define  TPM_SPEC_YEAR           (TPM_SPEC)(SPEC_YEAR)
#define  SPEC_DAY_OF_YEAR        97
#define  TPM_SPEC_DAY_OF_YEAR    (TPM_SPEC)(SPEC_DAY_OF_YEAR)

// Table 2:7 - Definition of TPM_GENERATED Constants  (EnumTable)
typedef  UINT32             TPM_GENERATED;
#define  TPM_GENERATED_VALUE    (TPM_GENERATED)(0xFF544347)

// Table 2:16 - Definition of TPM_RC Constants  (EnumTable)
typedef  UINT32             TPM_RC;
#define  TPM_RC_SUCCESS              (TPM_RC)(0x000)
#define  TPM_RC_BAD_TAG              (TPM_RC)(0x01E)
#define  RC_VER1                     (TPM_RC)(0x100)
#define  TPM_RC_INITIALIZE           (TPM_RC)(RC_VER1+0x000)
#define  TPM_RC_FAILURE              (TPM_RC)(RC_VER1+0x001)
#define  TPM_RC_SEQUENCE             (TPM_RC)(RC_VER1+0x003)
#define  TPM_RC_PRIVATE              (TPM_RC)(RC_VER1+0x00B)
#define  TPM_RC_HMAC                 (TPM_RC)(RC_VER1+0x019)
#define  TPM_RC_DISABLED             (TPM_RC)(RC_VER1+0x020)
#define  TPM_RC_EXCLUSIVE            (TPM_RC)(RC_VER1+0x021)
#define  TPM_RC_AUTH_TYPE            (TPM_RC)(RC_VER1+0x024)
#define  TPM_RC_AUTH_MISSING         (TPM_RC)(RC_VER1+0x025)
#define  TPM_RC_POLICY               (TPM_RC)(RC_VER1+0x026)
#define  TPM_RC_PCR                  (TPM_RC)(RC_VER1+0x027)
#define  TPM_RC_PCR_CHANGED          (TPM_RC)(RC_VER1+0x028)
#define  TPM_RC_UPGRADE              (TPM_RC)(RC_VER1+0x02D)
#define  TPM_RC_TOO_MANY_CONTEXTS    (TPM_RC)(RC_VER1+0x02E)
#define  TPM_RC_AUTH_UNAVAILABLE     (TPM_RC)(RC_VER1+0x02F)
#define  TPM_RC_REBOOT               (TPM_RC)(RC_VER1+0x030)
#define  TPM_RC_UNBALANCED           (TPM_RC)(RC_VER1+0x031)
#define  TPM_RC_COMMAND_SIZE         (TPM_RC)(RC_VER1+0x042)
#define  TPM_RC_COMMAND_CODE         (TPM_RC)(RC_VER1+0x043)
#define  TPM_RC_AUTHSIZE             (TPM_RC)(RC_VER1+0x044)
#define  TPM_RC_AUTH_CONTEXT         (TPM_RC)(RC_VER1+0x045)
#define  TPM_RC_NV_RANGE             (TPM_RC)(RC_VER1+0x046)
#define  TPM_RC_NV_SIZE              (TPM_RC)(RC_VER1+0x047)
#define  TPM_RC_NV_LOCKED            (TPM_RC)(RC_VER1+0x048)
#define  TPM_RC_NV_AUTHORIZATION     (TPM_RC)(RC_VER1+0x049)
#define  TPM_RC_NV_UNINITIALIZED     (TPM_RC)(RC_VER1+0x04A)
#define  TPM_RC_NV_SPACE             (TPM_RC)(RC_VER1+0x04B)
#define  TPM_RC_NV_DEFINED           (TPM_RC)(RC_VER1+0x04C)
#define  TPM_RC_BAD_CONTEXT          (TPM_RC)(RC_VER1+0x050)
#define  TPM_RC_CPHASH               (TPM_RC)(RC_VER1+0x051)
#define  TPM_RC_PARENT               (TPM_RC)(RC_VER1+0x052)
#define  TPM_RC_NEEDS_TEST           (TPM_RC)(RC_VER1+0x053)
#define  TPM_RC_NO_RESULT            (TPM_RC)(RC_VER1+0x054)
#define  TPM_RC_SENSITIVE            (TPM_RC)(RC_VER1+0x055)
#define  RC_MAX_FM0                  (TPM_RC)(RC_VER1+0x07F)
#define  RC_FMT1                     (TPM_RC)(0x080)
#define  TPM_RC_ASYMMETRIC           (TPM_RC)(RC_FMT1+0x001)
#define  TPM_RCS_ASYMMETRIC          (TPM_RC)(RC_FMT1+0x001)
#define  TPM_RC_ATTRIBUTES           (TPM_RC)(RC_FMT1+0x002)
#define  TPM_RCS_ATTRIBUTES          (TPM_RC)(RC_FMT1+0x002)
#define  TPM_RC_HASH                 (TPM_RC)(RC_FMT1+0x003)
#define  TPM_RCS_HASH                (TPM_RC)(RC_FMT1+0x003)
#define  TPM_RC_VALUE                (TPM_RC)(RC_FMT1+0x004)
#define  TPM_RCS_VALUE               (TPM_RC)(RC_FMT1+0x004)
#define  TPM_RC_HIERARCHY            (TPM_RC)(RC_FMT1+0x005)
#define  TPM_RCS_HIERARCHY           (TPM_RC)(RC_FMT1+0x005)
#define  TPM_RC_KEY_SIZE             (TPM_RC)(RC_FMT1+0x007)
#define  TPM_RCS_KEY_SIZE            (TPM_RC)(RC_FMT1+0x007)
#define  TPM_RC_MGF                  (TPM_RC)(RC_FMT1+0x008)
#define  TPM_RCS_MGF                 (TPM_RC)(RC_FMT1+0x008)
#define  TPM_RC_MODE                 (TPM_RC)(RC_FMT1+0x009)
#define  TPM_RCS_MODE                (TPM_RC)(RC_FMT1+0x009)
#define  TPM_RC_TYPE                 (TPM_RC)(RC_FMT1+0x00A)
#define  TPM_RCS_TYPE                (TPM_RC)(RC_FMT1+0x00A)
#define  TPM_RC_HANDLE               (TPM_RC)(RC_FMT1+0x00B)
#define  TPM_RCS_HANDLE              (TPM_RC)(RC_FMT1+0x00B)
#define  TPM_RC_KDF                  (TPM_RC)(RC_FMT1+0x00C)
#define  TPM_RCS_KDF                 (TPM_RC)(RC_FMT1+0x00C)
#define  TPM_RC_RANGE                (TPM_RC)(RC_FMT1+0x00D)
#define  TPM_RCS_RANGE               (TPM_RC)(RC_FMT1+0x00D)
#define  TPM_RC_AUTH_FAIL            (TPM_RC)(RC_FMT1+0x00E)
#define  TPM_RCS_AUTH_FAIL           (TPM_RC)(RC_FMT1+0x00E)
#define  TPM_RC_NONCE                (TPM_RC)(RC_FMT1+0x00F)
#define  TPM_RCS_NONCE               (TPM_RC)(RC_FMT1+0x00F)
#define  TPM_RC_PP                   (TPM_RC)(RC_FMT1+0x010)
#define  TPM_RCS_PP                  (TPM_RC)(RC_FMT1+0x010)
#define  TPM_RC_SCHEME               (TPM_RC)(RC_FMT1+0x012)
#define  TPM_RCS_SCHEME              (TPM_RC)(RC_FMT1+0x012)
#define  TPM_RC_SIZE                 (TPM_RC)(RC_FMT1+0x015)
#define  TPM_RCS_SIZE                (TPM_RC)(RC_FMT1+0x015)
#define  TPM_RC_SYMMETRIC            (TPM_RC)(RC_FMT1+0x016)
#define  TPM_RCS_SYMMETRIC           (TPM_RC)(RC_FMT1+0x016)
#define  TPM_RC_TAG                  (TPM_RC)(RC_FMT1+0x017)
#define  TPM_RCS_TAG                 (TPM_RC)(RC_FMT1+0x017)
#define  TPM_RC_SELECTOR             (TPM_RC)(RC_FMT1+0x018)
#define  TPM_RCS_SELECTOR            (TPM_RC)(RC_FMT1+0x018)
#define  TPM_RC_INSUFFICIENT         (TPM_RC)(RC_FMT1+0x01A)
#define  TPM_RCS_INSUFFICIENT        (TPM_RC)(RC_FMT1+0x01A)
#define  TPM_RC_SIGNATURE            (TPM_RC)(RC_FMT1+0x01B)
#define  TPM_RCS_SIGNATURE           (TPM_RC)(RC_FMT1+0x01B)
#define  TPM_RC_KEY                  (TPM_RC)(RC_FMT1+0x01C)
#define  TPM_RCS_KEY                 (TPM_RC)(RC_FMT1+0x01C)
#define  TPM_RC_POLICY_FAIL          (TPM_RC)(RC_FMT1+0x01D)
#define  TPM_RCS_POLICY_FAIL         (TPM_RC)(RC_FMT1+0x01D)
#define  TPM_RC_INTEGRITY            (TPM_RC)(RC_FMT1+0x01F)
#define  TPM_RCS_INTEGRITY           (TPM_RC)(RC_FMT1+0x01F)
#define  TPM_RC_TICKET               (TPM_RC)(RC_FMT1+0x020)
#define  TPM_RCS_TICKET              (TPM_RC)(RC_FMT1+0x020)
#define  TPM_RC_RESERVED_BITS        (TPM_RC)(RC_FMT1+0x021)
#define  TPM_RCS_RESERVED_BITS       (TPM_RC)(RC_FMT1+0x021)
#define  TPM_RC_BAD_AUTH             (TPM_RC)(RC_FMT1+0x022)
#define  TPM_RCS_BAD_AUTH            (TPM_RC)(RC_FMT1+0x022)
#define  TPM_RC_EXPIRED              (TPM_RC)(RC_FMT1+0x023)
#define  TPM_RCS_EXPIRED             (TPM_RC)(RC_FMT1+0x023)
#define  TPM_RC_POLICY_CC            (TPM_RC)(RC_FMT1+0x024)
#define  TPM_RCS_POLICY_CC           (TPM_RC)(RC_FMT1+0x024)
#define  TPM_RC_BINDING              (TPM_RC)(RC_FMT1+0x025)
#define  TPM_RCS_BINDING             (TPM_RC)(RC_FMT1+0x025)
#define  TPM_RC_CURVE                (TPM_RC)(RC_FMT1+0x026)
#define  TPM_RCS_CURVE               (TPM_RC)(RC_FMT1+0x026)
#define  TPM_RC_ECC_POINT            (TPM_RC)(RC_FMT1+0x027)
#define  TPM_RCS_ECC_POINT           (TPM_RC)(RC_FMT1+0x027)
#define  RC_WARN                     (TPM_RC)(0x900)
#define  TPM_RC_CONTEXT_GAP          (TPM_RC)(RC_WARN+0x001)
#define  TPM_RC_OBJECT_MEMORY        (TPM_RC)(RC_WARN+0x002)
#define  TPM_RC_SESSION_MEMORY       (TPM_RC)(RC_WARN+0x003)
#define  TPM_RC_MEMORY               (TPM_RC)(RC_WARN+0x004)
#define  TPM_RC_SESSION_HANDLES      (TPM_RC)(RC_WARN+0x005)
#define  TPM_RC_OBJECT_HANDLES       (TPM_RC)(RC_WARN+0x006)
#define  TPM_RC_LOCALITY             (TPM_RC)(RC_WARN+0x007)
#define  TPM_RC_YIELDED              (TPM_RC)(RC_WARN+0x008)
#define  TPM_RC_CANCELED             (TPM_RC)(RC_WARN+0x009)
#define  TPM_RC_TESTING              (TPM_RC)(RC_WARN+0x00A)
#define  TPM_RC_REFERENCE_H0         (TPM_RC)(RC_WARN+0x010)
#define  TPM_RC_REFERENCE_H1         (TPM_RC)(RC_WARN+0x011)
#define  TPM_RC_REFERENCE_H2         (TPM_RC)(RC_WARN+0x012)
#define  TPM_RC_REFERENCE_H3         (TPM_RC)(RC_WARN+0x013)
#define  TPM_RC_REFERENCE_H4         (TPM_RC)(RC_WARN+0x014)
#define  TPM_RC_REFERENCE_H5         (TPM_RC)(RC_WARN+0x015)
#define  TPM_RC_REFERENCE_H6         (TPM_RC)(RC_WARN+0x016)
#define  TPM_RC_REFERENCE_S0         (TPM_RC)(RC_WARN+0x018)
#define  TPM_RC_REFERENCE_S1         (TPM_RC)(RC_WARN+0x019)
#define  TPM_RC_REFERENCE_S2         (TPM_RC)(RC_WARN+0x01A)
#define  TPM_RC_REFERENCE_S3         (TPM_RC)(RC_WARN+0x01B)
#define  TPM_RC_REFERENCE_S4         (TPM_RC)(RC_WARN+0x01C)
#define  TPM_RC_REFERENCE_S5         (TPM_RC)(RC_WARN+0x01D)
#define  TPM_RC_REFERENCE_S6         (TPM_RC)(RC_WARN+0x01E)
#define  TPM_RC_NV_RATE              (TPM_RC)(RC_WARN+0x020)
#define  TPM_RC_LOCKOUT              (TPM_RC)(RC_WARN+0x021)
#define  TPM_RC_RETRY                (TPM_RC)(RC_WARN+0x022)
#define  TPM_RC_NV_UNAVAILABLE       (TPM_RC)(RC_WARN+0x023)
#define  TPM_RC_NOT_USED             (TPM_RC)(RC_WARN+0x7F)
#define  TPM_RC_H                    (TPM_RC)(0x000)
#define  TPM_RC_P                    (TPM_RC)(0x040)
#define  TPM_RC_S                    (TPM_RC)(0x800)
#define  TPM_RC_1                    (TPM_RC)(0x100)
#define  TPM_RC_2                    (TPM_RC)(0x200)
#define  TPM_RC_3                    (TPM_RC)(0x300)
#define  TPM_RC_4                    (TPM_RC)(0x400)
#define  TPM_RC_5                    (TPM_RC)(0x500)
#define  TPM_RC_6                    (TPM_RC)(0x600)
#define  TPM_RC_7                    (TPM_RC)(0x700)
#define  TPM_RC_8                    (TPM_RC)(0x800)
#define  TPM_RC_9                    (TPM_RC)(0x900)
#define  TPM_RC_A                    (TPM_RC)(0xA00)
#define  TPM_RC_B                    (TPM_RC)(0xB00)
#define  TPM_RC_C                    (TPM_RC)(0xC00)
#define  TPM_RC_D                    (TPM_RC)(0xD00)
#define  TPM_RC_E                    (TPM_RC)(0xE00)
#define  TPM_RC_F                    (TPM_RC)(0xF00)
#define  TPM_RC_N_MASK               (TPM_RC)(0xF00)

// Table 2:17 - Definition of TPM_CLOCK_ADJUST Constants  (EnumTable)
typedef  INT8               TPM_CLOCK_ADJUST;
#define  TPM_CLOCK_COARSE_SLOWER    (TPM_CLOCK_ADJUST)(-3)
#define  TPM_CLOCK_MEDIUM_SLOWER    (TPM_CLOCK_ADJUST)(-2)
#define  TPM_CLOCK_FINE_SLOWER      (TPM_CLOCK_ADJUST)(-1)
#define  TPM_CLOCK_NO_CHANGE        (TPM_CLOCK_ADJUST)(0)
#define  TPM_CLOCK_FINE_FASTER      (TPM_CLOCK_ADJUST)(1)
#define  TPM_CLOCK_MEDIUM_FASTER    (TPM_CLOCK_ADJUST)(2)
#define  TPM_CLOCK_COARSE_FASTER    (TPM_CLOCK_ADJUST)(3)

// Table 2:18 - Definition of TPM_EO Constants  (EnumTable)
typedef  UINT16             TPM_EO;
#define  TPM_EO_EQ             (TPM_EO)(0x0000)
#define  TPM_EO_NEQ            (TPM_EO)(0x0001)
#define  TPM_EO_SIGNED_GT      (TPM_EO)(0x0002)
#define  TPM_EO_UNSIGNED_GT    (TPM_EO)(0x0003)
#define  TPM_EO_SIGNED_LT      (TPM_EO)(0x0004)
#define  TPM_EO_UNSIGNED_LT    (TPM_EO)(0x0005)
#define  TPM_EO_SIGNED_GE      (TPM_EO)(0x0006)
#define  TPM_EO_UNSIGNED_GE    (TPM_EO)(0x0007)
#define  TPM_EO_SIGNED_LE      (TPM_EO)(0x0008)
#define  TPM_EO_UNSIGNED_LE    (TPM_EO)(0x0009)
#define  TPM_EO_BITSET         (TPM_EO)(0x000A)
#define  TPM_EO_BITCLEAR       (TPM_EO)(0x000B)

// Table 2:19 - Definition of TPM_ST Constants  (EnumTable)
typedef  UINT16             TPM_ST;
#define  TPM_ST_RSP_COMMAND             (TPM_ST)(0x00C4)
#define  TPM_ST_NULL                    (TPM_ST)(0X8000)
#define  TPM_ST_NO_SESSIONS             (TPM_ST)(0x8001)
#define  TPM_ST_SESSIONS                (TPM_ST)(0x8002)
#define  TPM_ST_ATTEST_NV               (TPM_ST)(0x8014)
#define  TPM_ST_ATTEST_COMMAND_AUDIT    (TPM_ST)(0x8015)
#define  TPM_ST_ATTEST_SESSION_AUDIT    (TPM_ST)(0x8016)
#define  TPM_ST_ATTEST_CERTIFY          (TPM_ST)(0x8017)
#define  TPM_ST_ATTEST_QUOTE            (TPM_ST)(0x8018)
#define  TPM_ST_ATTEST_TIME             (TPM_ST)(0x8019)
#define  TPM_ST_ATTEST_CREATION         (TPM_ST)(0x801A)
#define  TPM_ST_CREATION                (TPM_ST)(0x8021)
#define  TPM_ST_VERIFIED                (TPM_ST)(0x8022)
#define  TPM_ST_AUTH_SECRET             (TPM_ST)(0x8023)
#define  TPM_ST_HASHCHECK               (TPM_ST)(0x8024)
#define  TPM_ST_AUTH_SIGNED             (TPM_ST)(0x8025)
#define  TPM_ST_FU_MANIFEST             (TPM_ST)(0x8029)

// Table 2:20 - Definition of TPM_SU Constants  (EnumTable)
typedef  UINT16             TPM_SU;
#define  TPM_SU_CLEAR    (TPM_SU)(0x0000)
#define  TPM_SU_STATE    (TPM_SU)(0x0001)

// Table 2:21 - Definition of TPM_SE Constants  (EnumTable)
typedef  UINT8              TPM_SE;
#define  TPM_SE_HMAC      (TPM_SE)(0x00)
#define  TPM_SE_POLICY    (TPM_SE)(0x01)
#define  TPM_SE_TRIAL     (TPM_SE)(0x03)

// Table 2:22 - Definition of TPM_CAP Constants (EnumTable)
typedef  UINT32             TPM_CAP;
#define  TPM_CAP_FIRST              (TPM_CAP)(0x00000000)
#define  TPM_CAP_ALGS               (TPM_CAP)(0x00000000)
#define  TPM_CAP_HANDLES            (TPM_CAP)(0x00000001)
#define  TPM_CAP_COMMANDS           (TPM_CAP)(0x00000002)
#define  TPM_CAP_PP_COMMANDS        (TPM_CAP)(0x00000003)
#define  TPM_CAP_AUDIT_COMMANDS     (TPM_CAP)(0x00000004)
#define  TPM_CAP_PCRS               (TPM_CAP)(0x00000005)
#define  TPM_CAP_TPM_PROPERTIES     (TPM_CAP)(0x00000006)
#define  TPM_CAP_PCR_PROPERTIES     (TPM_CAP)(0x00000007)
#define  TPM_CAP_ECC_CURVES         (TPM_CAP)(0x00000008)
#define  TPM_CAP_AUTH_POLICIES      (TPM_CAP)(0x00000009)
#define  TPM_CAP_LAST               (TPM_CAP)(0x00000009)
#define  TPM_CAP_VENDOR_PROPERTY    (TPM_CAP)(0x00000100)

// Table 2:23 - Definition of TPM_PT Constants  (EnumTable)
typedef  UINT32             TPM_PT;
#define  TPM_PT_NONE                   (TPM_PT)(0x00000000)
#define  PT_GROUP                      (TPM_PT)(0x00000100)
#define  PT_FIXED                      (TPM_PT)(PT_GROUP*1)
#define  TPM_PT_FAMILY_INDICATOR       (TPM_PT)(PT_FIXED+0)
#define  TPM_PT_LEVEL                  (TPM_PT)(PT_FIXED+1)
#define  TPM_PT_REVISION               (TPM_PT)(PT_FIXED+2)
#define  TPM_PT_DAY_OF_YEAR            (TPM_PT)(PT_FIXED+3)
#define  TPM_PT_YEAR                   (TPM_PT)(PT_FIXED+4)
#define  TPM_PT_MANUFACTURER           (TPM_PT)(PT_FIXED+5)
#define  TPM_PT_VENDOR_STRING_1        (TPM_PT)(PT_FIXED+6)
#define  TPM_PT_VENDOR_STRING_2        (TPM_PT)(PT_FIXED+7)
#define  TPM_PT_VENDOR_STRING_3        (TPM_PT)(PT_FIXED+8)
#define  TPM_PT_VENDOR_STRING_4        (TPM_PT)(PT_FIXED+9)
#define  TPM_PT_VENDOR_TPM_TYPE        (TPM_PT)(PT_FIXED+10)
#define  TPM_PT_FIRMWARE_VERSION_1     (TPM_PT)(PT_FIXED+11)
#define  TPM_PT_FIRMWARE_VERSION_2     (TPM_PT)(PT_FIXED+12)
#define  TPM_PT_INPUT_BUFFER           (TPM_PT)(PT_FIXED+13)
#define  TPM_PT_HR_TRANSIENT_MIN       (TPM_PT)(PT_FIXED+14)
#define  TPM_PT_HR_PERSISTENT_MIN      (TPM_PT)(PT_FIXED+15)
#define  TPM_PT_HR_LOADED_MIN          (TPM_PT)(PT_FIXED+16)
#define  TPM_PT_ACTIVE_SESSIONS_MAX    (TPM_PT)(PT_FIXED+17)
#define  TPM_PT_PCR_COUNT              (TPM_PT)(PT_FIXED+18)
#define  TPM_PT_PCR_SELECT_MIN         (TPM_PT)(PT_FIXED+19)
#define  TPM_PT_CONTEXT_GAP_MAX        (TPM_PT)(PT_FIXED+20)
#define  TPM_PT_NV_COUNTERS_MAX        (TPM_PT)(PT_FIXED+22)
#define  TPM_PT_NV_INDEX_MAX           (TPM_PT)(PT_FIXED+23)
#define  TPM_PT_MEMORY                 (TPM_PT)(PT_FIXED+24)
#define  TPM_PT_CLOCK_UPDATE           (TPM_PT)(PT_FIXED+25)
#define  TPM_PT_CONTEXT_HASH           (TPM_PT)(PT_FIXED+26)
#define  TPM_PT_CONTEXT_SYM            (TPM_PT)(PT_FIXED+27)
#define  TPM_PT_CONTEXT_SYM_SIZE       (TPM_PT)(PT_FIXED+28)
#define  TPM_PT_ORDERLY_COUNT          (TPM_PT)(PT_FIXED+29)
#define  TPM_PT_MAX_COMMAND_SIZE       (TPM_PT)(PT_FIXED+30)
#define  TPM_PT_MAX_RESPONSE_SIZE      (TPM_PT)(PT_FIXED+31)
#define  TPM_PT_MAX_DIGEST             (TPM_PT)(PT_FIXED+32)
#define  TPM_PT_MAX_OBJECT_CONTEXT     (TPM_PT)(PT_FIXED+33)
#define  TPM_PT_MAX_SESSION_CONTEXT    (TPM_PT)(PT_FIXED+34)
#define  TPM_PT_PS_FAMILY_INDICATOR    (TPM_PT)(PT_FIXED+35)
#define  TPM_PT_PS_LEVEL               (TPM_PT)(PT_FIXED+36)
#define  TPM_PT_PS_REVISION            (TPM_PT)(PT_FIXED+37)
#define  TPM_PT_PS_DAY_OF_YEAR         (TPM_PT)(PT_FIXED+38)
#define  TPM_PT_PS_YEAR                (TPM_PT)(PT_FIXED+39)
#define  TPM_PT_SPLIT_MAX              (TPM_PT)(PT_FIXED+40)
#define  TPM_PT_TOTAL_COMMANDS         (TPM_PT)(PT_FIXED+41)
#define  TPM_PT_LIBRARY_COMMANDS       (TPM_PT)(PT_FIXED+42)
#define  TPM_PT_VENDOR_COMMANDS        (TPM_PT)(PT_FIXED+43)
#define  TPM_PT_NV_BUFFER_MAX          (TPM_PT)(PT_FIXED+44)
#define  TPM_PT_MODES                  (TPM_PT)(PT_FIXED+45)
#define  TPM_PT_MAX_CAP_BUFFER         (TPM_PT)(PT_FIXED+46)
#define  PT_VAR                        (TPM_PT)(PT_GROUP*2)
#define  TPM_PT_PERMANENT              (TPM_PT)(PT_VAR+0)
#define  TPM_PT_STARTUP_CLEAR          (TPM_PT)(PT_VAR+1)
#define  TPM_PT_HR_NV_INDEX            (TPM_PT)(PT_VAR+2)
#define  TPM_PT_HR_LOADED              (TPM_PT)(PT_VAR+3)
#define  TPM_PT_HR_LOADED_AVAIL        (TPM_PT)(PT_VAR+4)
#define  TPM_PT_HR_ACTIVE              (TPM_PT)(PT_VAR+5)
#define  TPM_PT_HR_ACTIVE_AVAIL        (TPM_PT)(PT_VAR+6)
#define  TPM_PT_HR_TRANSIENT_AVAIL     (TPM_PT)(PT_VAR+7)
#define  TPM_PT_HR_PERSISTENT          (TPM_PT)(PT_VAR+8)
#define  TPM_PT_HR_PERSISTENT_AVAIL    (TPM_PT)(PT_VAR+9)
#define  TPM_PT_NV_COUNTERS            (TPM_PT)(PT_VAR+10)
#define  TPM_PT_NV_COUNTERS_AVAIL      (TPM_PT)(PT_VAR+11)
#define  TPM_PT_ALGORITHM_SET          (TPM_PT)(PT_VAR+12)
#define  TPM_PT_LOADED_CURVES          (TPM_PT)(PT_VAR+13)
#define  TPM_PT_LOCKOUT_COUNTER        (TPM_PT)(PT_VAR+14)
#define  TPM_PT_MAX_AUTH_FAIL          (TPM_PT)(PT_VAR+15)
#define  TPM_PT_LOCKOUT_INTERVAL       (TPM_PT)(PT_VAR+16)
#define  TPM_PT_LOCKOUT_RECOVERY       (TPM_PT)(PT_VAR+17)
#define  TPM_PT_NV_WRITE_RECOVERY      (TPM_PT)(PT_VAR+18)
#define  TPM_PT_AUDIT_COUNTER_0        (TPM_PT)(PT_VAR+19)
#define  TPM_PT_AUDIT_COUNTER_1        (TPM_PT)(PT_VAR+20)

// Table 2:24 - Definition of TPM_PT_PCR Constants  (EnumTable)
typedef  UINT32             TPM_PT_PCR;
#define  TPM_PT_PCR_FIRST           (TPM_PT_PCR)(0x00000000)
#define  TPM_PT_PCR_SAVE            (TPM_PT_PCR)(0x00000000)
#define  TPM_PT_PCR_EXTEND_L0       (TPM_PT_PCR)(0x00000001)
#define  TPM_PT_PCR_RESET_L0        (TPM_PT_PCR)(0x00000002)
#define  TPM_PT_PCR_EXTEND_L1       (TPM_PT_PCR)(0x00000003)
#define  TPM_PT_PCR_RESET_L1        (TPM_PT_PCR)(0x00000004)
#define  TPM_PT_PCR_EXTEND_L2       (TPM_PT_PCR)(0x00000005)
#define  TPM_PT_PCR_RESET_L2        (TPM_PT_PCR)(0x00000006)
#define  TPM_PT_PCR_EXTEND_L3       (TPM_PT_PCR)(0x00000007)
#define  TPM_PT_PCR_RESET_L3        (TPM_PT_PCR)(0x00000008)
#define  TPM_PT_PCR_EXTEND_L4       (TPM_PT_PCR)(0x00000009)
#define  TPM_PT_PCR_RESET_L4        (TPM_PT_PCR)(0x0000000A)
#define  TPM_PT_PCR_NO_INCREMENT    (TPM_PT_PCR)(0x00000011)
#define  TPM_PT_PCR_DRTM_RESET      (TPM_PT_PCR)(0x00000012)
#define  TPM_PT_PCR_POLICY          (TPM_PT_PCR)(0x00000013)
#define  TPM_PT_PCR_AUTH            (TPM_PT_PCR)(0x00000014)
#define  TPM_PT_PCR_LAST            (TPM_PT_PCR)(0x00000014)

// Table 2:25 - Definition of TPM_PS Constants  (EnumTable)
typedef  UINT32             TPM_PS;
#define  TPM_PS_MAIN              (TPM_PS)(0x00000000)
#define  TPM_PS_PC                (TPM_PS)(0x00000001)
#define  TPM_PS_PDA               (TPM_PS)(0x00000002)
#define  TPM_PS_CELL_PHONE        (TPM_PS)(0x00000003)
#define  TPM_PS_SERVER            (TPM_PS)(0x00000004)
#define  TPM_PS_PERIPHERAL        (TPM_PS)(0x00000005)
#define  TPM_PS_TSS               (TPM_PS)(0x00000006)
#define  TPM_PS_STORAGE           (TPM_PS)(0x00000007)
#define  TPM_PS_AUTHENTICATION    (TPM_PS)(0x00000008)
#define  TPM_PS_EMBEDDED          (TPM_PS)(0x00000009)
#define  TPM_PS_HARDCOPY          (TPM_PS)(0x0000000A)
#define  TPM_PS_INFRASTRUCTURE    (TPM_PS)(0x0000000B)
#define  TPM_PS_VIRTUALIZATION    (TPM_PS)(0x0000000C)
#define  TPM_PS_TNC               (TPM_PS)(0x0000000D)
#define  TPM_PS_MULTI_TENANT      (TPM_PS)(0x0000000E)
#define  TPM_PS_TC                (TPM_PS)(0x0000000F)

// Table 2:26 - Definition of Types for Handles (TypedefTable)
typedef  UINT32             TPM_HANDLE;

// Table 2:27 - Definition of TPM_HT Constants  (EnumTable)
typedef  UINT8              TPM_HT;
#define  TPM_HT_PCR               (TPM_HT)(0x00)
#define  TPM_HT_NV_INDEX          (TPM_HT)(0x01)
#define  TPM_HT_HMAC_SESSION      (TPM_HT)(0x02)
#define  TPM_HT_LOADED_SESSION    (TPM_HT)(0x02)
#define  TPM_HT_POLICY_SESSION    (TPM_HT)(0x03)
#define  TPM_HT_SAVED_SESSION     (TPM_HT)(0x03)
#define  TPM_HT_PERMANENT         (TPM_HT)(0x40)
#define  TPM_HT_TRANSIENT         (TPM_HT)(0x80)
#define  TPM_HT_PERSISTENT        (TPM_HT)(0x81)
#define  TPM_HT_AC                (TPM_HT)(0x90)

// Table 2:28 - Definition of TPM_RH Constants  (EnumTable)
typedef  TPM_HANDLE         TPM_RH;
#define  TPM_RH_FIRST          (TPM_RH)(0x40000000)
#define  TPM_RH_SRK            (TPM_RH)(0x40000000)
#define  TPM_RH_OWNER          (TPM_RH)(0x40000001)
#define  TPM_RH_REVOKE         (TPM_RH)(0x40000002)
#define  TPM_RH_TRANSPORT      (TPM_RH)(0x40000003)
#define  TPM_RH_OPERATOR       (TPM_RH)(0x40000004)
#define  TPM_RH_ADMIN          (TPM_RH)(0x40000005)
#define  TPM_RH_EK             (TPM_RH)(0x40000006)
#define  TPM_RH_NULL           (TPM_RH)(0x40000007)
#define  TPM_RH_UNASSIGNED     (TPM_RH)(0x40000008)
#define  TPM_RS_PW             (TPM_RH)(0x40000009)
#define  TPM_RH_LOCKOUT        (TPM_RH)(0x4000000A)
#define  TPM_RH_ENDORSEMENT    (TPM_RH)(0x4000000B)
#define  TPM_RH_PLATFORM       (TPM_RH)(0x4000000C)
#define  TPM_RH_PLATFORM_NV    (TPM_RH)(0x4000000D)
#define  TPM_RH_AUTH_00        (TPM_RH)(0x40000010)
#define  TPM_RH_AUTH_FF        (TPM_RH)(0x4000010F)
#define  TPM_RH_LAST           (TPM_RH)(0x4000010F)

// Table 2:29 - Definition of TPM_HC Constants  (EnumTable)
typedef  TPM_HANDLE         TPM_HC;
#define  HR_HANDLE_MASK          (TPM_HC)(0x00FFFFFF)
#define  HR_RANGE_MASK           (TPM_HC)(0xFF000000)
#define  HR_SHIFT                (TPM_HC)(24)
#define  HR_PCR                  (TPM_HC)((TPM_HT_PCR<<HR_SHIFT))
#define  HR_HMAC_SESSION         (TPM_HC)((TPM_HT_HMAC_SESSION<<HR_SHIFT))
#define  HR_POLICY_SESSION       (TPM_HC)((TPM_HT_POLICY_SESSION<<HR_SHIFT))
#define  HR_TRANSIENT            (TPM_HC)((TPM_HT_TRANSIENT<<HR_SHIFT))
#define  HR_PERSISTENT           (TPM_HC)((TPM_HT_PERSISTENT<<HR_SHIFT))
#define  HR_NV_INDEX             (TPM_HC)((TPM_HT_NV_INDEX<<HR_SHIFT))
#define  HR_PERMANENT            (TPM_HC)((TPM_HT_PERMANENT<<HR_SHIFT))
#define  PCR_FIRST               (TPM_HC)((HR_PCR+0))
#define  PCR_LAST                (TPM_HC)((PCR_FIRST+IMPLEMENTATION_PCR-1))
#define  HMAC_SESSION_FIRST      (TPM_HC)((HR_HMAC_SESSION+0))
#define  HMAC_SESSION_LAST       \
    (TPM_HC)((HMAC_SESSION_FIRST + MAX_ACTIVE_SESSIONS-1))
#define  LOADED_SESSION_FIRST    (TPM_HC)(HMAC_SESSION_FIRST)
#define  LOADED_SESSION_LAST     (TPM_HC)(HMAC_SESSION_LAST)
#define  POLICY_SESSION_FIRST    (TPM_HC)((HR_POLICY_SESSION+0))
#define  POLICY_SESSION_LAST     \
    (TPM_HC)((POLICY_SESSION_FIRST + MAX_ACTIVE_SESSIONS-1))
#define  TRANSIENT_FIRST         (TPM_HC)((HR_TRANSIENT+0))
#define  ACTIVE_SESSION_FIRST    (TPM_HC)(POLICY_SESSION_FIRST)
#define  ACTIVE_SESSION_LAST     (TPM_HC)(POLICY_SESSION_LAST)
#define  TRANSIENT_LAST          (TPM_HC)((TRANSIENT_FIRST+MAX_LOADED_OBJECTS-1))
#define  PERSISTENT_FIRST        (TPM_HC)((HR_PERSISTENT+0))
#define  PERSISTENT_LAST         (TPM_HC)((PERSISTENT_FIRST+0x00FFFFFF))
#define  PLATFORM_PERSISTENT     (TPM_HC)((PERSISTENT_FIRST+0x00800000))
#define  NV_INDEX_FIRST          (TPM_HC)((HR_NV_INDEX+0))
#define  NV_INDEX_LAST           (TPM_HC)((NV_INDEX_FIRST+0x00FFFFFF))
#define  PERMANENT_FIRST         (TPM_HC)(TPM_RH_FIRST)
#define  PERMANENT_LAST          (TPM_HC)(TPM_RH_LAST)
#define  HR_NV_AC                (TPM_HC)(((TPM_HT_NV_INDEX<<HR_SHIFT)+0xD00000))
#define  NV_AC_FIRST             (TPM_HC)((HR_NV_AC+0))
#define  NV_AC_LAST              (TPM_HC)((HR_NV_AC+0x0000FFFF))
#define  HR_AC                   (TPM_HC)((TPM_HT_AC<<HR_SHIFT))
#define  AC_FIRST                (TPM_HC)((HR_AC+0))
#define  AC_LAST                 (TPM_HC)((HR_AC+0x0000FFFF))

// Table 2:30 - Definition of TPMA_ALGORITHM Bits (BitsTable)
typedef struct {
    unsigned    asymmetric         : 1 ;
    unsigned    symmetric          : 1 ;
    unsigned    hash               : 1 ;
    unsigned    object             : 1 ;
    unsigned    Reserved_at_bit_4  : 4 ;
    unsigned    signing            : 1 ;
    unsigned    encrypting         : 1 ;
    unsigned    method             : 1 ;
    unsigned    Reserved_at_bit_11 : 21;
} TPMA_ALGORITHM;

#define IsAlgorithm_asymmetric(attribute)                  \
        ((attribute.asymmetric) != 0)
#define IsAlgorithm_symmetric(attribute)                   \
        ((attribute.symmetric) != 0)
#define IsAlgorithm_hash(attribute)                        \
        ((attribute.hash) != 0)
#define IsAlgorithm_object(attribute)                      \
        ((attribute.object) != 0)
#define IsAlgorithm_signing(attribute)                     \
        ((attribute.signing) != 0)
#define IsAlgorithm_encrypting(attribute)                  \
        ((attribute.encrypting) != 0)
#define IsAlgorithm_method(attribute)                      \
        ((attribute.method) != 0)

// Table 2:31 - Definition of TPMA_OBJECT Bits (BitsTable)
typedef struct {
    unsigned    Reserved_at_bit_0      : 1 ;
    unsigned    fixedTPM               : 1 ;
    unsigned    stClear                : 1 ;
    unsigned    Reserved_at_bit_3      : 1 ;
    unsigned    fixedParent            : 1 ;
    unsigned    sensitiveDataOrigin    : 1 ;
    unsigned    userWithAuth           : 1 ;
    unsigned    adminWithPolicy        : 1 ;
    unsigned    Reserved_at_bit_8      : 2 ;
    unsigned    noDA                   : 1 ;
    unsigned    encryptedDuplication   : 1 ;
    unsigned    Reserved_at_bit_12     : 4 ;
    unsigned    restricted             : 1 ;
    unsigned    decrypt                : 1 ;
    unsigned    sign                   : 1 ;
    unsigned    Reserved_at_bit_19     : 13;
} TPMA_OBJECT;

#define IsObject_fixedTPM(attribute)                       \
        ((attribute.fixedTPM) != 0)
#define IsObject_stClear(attribute)                        \
        ((attribute.stClear) != 0)
#define IsObject_fixedParent(attribute)                    \
        ((attribute.fixedParent) != 0)
#define IsObject_sensitiveDataOrigin(attribute)            \
        ((attribute.sensitiveDataOrigin) != 0)
#define IsObject_userWithAuth(attribute)                   \
        ((attribute.userWithAuth) != 0)
#define IsObject_adminWithPolicy(attribute)                \
        ((attribute.adminWithPolicy) != 0)
#define IsObject_noDA(attribute)                           \
        ((attribute.noDA) != 0)
#define IsObject_encryptedDuplication(attribute)           \
        ((attribute.encryptedDuplication) != 0)
#define IsObject_restricted(attribute)                     \
        ((attribute.restricted) != 0)
#define IsObject_decrypt(attribute)                        \
        ((attribute.decrypt) != 0)
#define IsObject_sign(attribute)                           \
        ((attribute.sign) != 0)
#define IsObject_sign(attribute)                           \
        ((attribute.sign) != 0)

// Table 2:32 - Definition of TPMA_SESSION Bits  (BitsTable)
typedef struct {
    unsigned    continueSession   : 1 ;
    unsigned    auditExclusive    : 1 ;
    unsigned    auditReset        : 1 ;
    unsigned    Reserved_at_bit_3 : 2 ;
    unsigned    decrypt           : 1 ;
    unsigned    encrypt           : 1 ;
    unsigned    audit             : 1 ;
} TPMA_SESSION;

#define IsSession_continueSession(attribute)               \
        ((attribute.continueSession) != 0)
#define IsSession_auditExclusive(attribute)                \
        ((attribute.auditExclusive) != 0)
#define IsSession_auditReset(attribute)                    \
        ((attribute.auditReset) != 0)
#define IsSession_decrypt(attribute)                       \
        ((attribute.decrypt) != 0)
#define IsSession_encrypt(attribute)                       \
        ((attribute.encrypt) != 0)
#define IsSession_audit(attribute)                         \
        ((attribute.audit) != 0)

// Table 2:33 - Definition of TPMA_LOCALITY Bits  (BitsTable)
typedef struct {
    unsigned    TPM_LOC_ZERO    : 1 ;
    unsigned    TPM_LOC_ONE     : 1 ;
    unsigned    TPM_LOC_TWO     : 1 ;
    unsigned    TPM_LOC_THREE   : 1 ;
    unsigned    TPM_LOC_FOUR    : 1 ;
    unsigned    Extended        : 3 ;
} TPMA_LOCALITY;

#define IsLocality_TPM_LOC_ZERO(attribute)                 \
        ((attribute.TPM_LOC_ZERO) != 0)
#define IsLocality_TPM_LOC_ONE(attribute)                  \
        ((attribute.TPM_LOC_ONE) != 0)
#define IsLocality_TPM_LOC_TWO(attribute)                  \
        ((attribute.TPM_LOC_TWO) != 0)
#define IsLocality_TPM_LOC_THREE(attribute)                \
        ((attribute.TPM_LOC_THREE) != 0)
#define IsLocality_TPM_LOC_FOUR(attribute)                 \
        ((attribute.TPM_LOC_FOUR) != 0)

// Table 2:34 - Definition of TPMA_PERMANENT Bits  (BitsTable)
typedef struct {
    unsigned    ownerAuthSet         : 1 ;
    unsigned    endorsementAuthSet   : 1 ;
    unsigned    lockoutAuthSet       : 1 ;
    unsigned    Reserved_at_bit_3    : 5 ;
    unsigned    disableClear         : 1 ;
    unsigned    inLockout            : 1 ;
    unsigned    tpmGeneratedEPS      : 1 ;
    unsigned    Reserved_at_bit_11   : 21;
} TPMA_PERMANENT;

#define IsPermanent_ownerAuthSet(attribute)                \
        ((attribute.ownerAuthSet) != 0)
#define IsPermanent_endorsementAuthSet(attribute)          \
        ((attribute.endorsementAuthSet) != 0)
#define IsPermanent_lockoutAuthSet(attribute)              \
        ((attribute.lockoutAuthSet) != 0)
#define IsPermanent_disableClear(attribute)                \
        ((attribute.disableClear) != 0)
#define IsPermanent_inLockout(attribute)                   \
        ((attribute.inLockout) != 0)
#define IsPermanent_tpmGeneratedEPS(attribute)             \
        ((attribute.tpmGeneratedEPS) != 0)

// Table 2:35 - Definition of TPMA_STARTUP_CLEAR Bits  (BitsTable)
typedef struct {
    unsigned    phEnable          : 1 ;
    unsigned    shEnable          : 1 ;
    unsigned    ehEnable          : 1 ;
    unsigned    phEnableNV        : 1 ;
    unsigned    Reserved_at_bit_4 : 27;
    unsigned    orderly           : 1 ;
} TPMA_STARTUP_CLEAR;

#define IsStartupClear_phEnable(attribute)                 \
        ((attribute.phEnable) != 0)
#define IsStartupClear_shEnable(attribute)                 \
        ((attribute.shEnable) != 0)
#define IsStartupClear_ehEnable(attribute)                 \
        ((attribute.ehEnable) != 0)
#define IsStartupClear_phEnableNV(attribute)               \
        ((attribute.phEnableNV) != 0)
#define IsStartupClear_orderly(attribute)                  \
        ((attribute.orderly) != 0)

// Table 2:36 - Definition of TPMA_MEMORY Bits  (BitsTable)
typedef struct {
    unsigned    sharedRAM           : 1 ;
    unsigned    sharedNV            : 1 ;
    unsigned    objectCopiedToRam   : 1 ;
    unsigned    Reserved_at_bit_3   : 29;
} TPMA_MEMORY;

#define IsMemory_sharedRAM(attribute)                      \
        ((attribute.sharedRAM) != 0)
#define IsMemory_sharedNV(attribute)                       \
        ((attribute.sharedNV) != 0)
#define IsMemory_objectCopiedToRam(attribute)              \
        ((attribute.objectCopiedToRam) != 0)

// Table 2:37 - Definition of TPMA_CC Bits  (BitsTable)
typedef struct {
    unsigned    commandIndex       : 16;
    unsigned    Reserved_at_bit_16 : 6 ;
    unsigned    nv                 : 1 ;
    unsigned    extensive          : 1 ;
    unsigned    flushed            : 1 ;
    unsigned    cHandles           : 3 ;
    unsigned    rHandle            : 1 ;
    unsigned    V                  : 1 ;
    unsigned    Res                : 2 ;
} TPMA_CC;

#define IsCc_nv(attribute)                                 \
        ((attribute.nv) != 0)
#define IsCc_extensive(attribute)                          \
        ((attribute.extensive) != 0)
#define IsCc_flushed(attribute)                            \
        ((attribute.flushed) != 0)
#define IsCc_rHandle(attribute)                            \
        ((attribute.rHandle) != 0)
#define IsCc_V(attribute)                                  \
        ((attribute.V) != 0)

// Table 2:38 - Definition of TPMA_MODES Bits  (BitsTable)
typedef struct {
    unsigned    FIPS_140_2        : 1 ;
    unsigned    Reserved_at_bit_1 : 31;
} TPMA_MODES;

#define IsModes_FIPS_140_2(attribute)                      \
        ((attribute.FIPS_140_2) != 0)

// Table 2:39 - Definition of TPMI_YES_NO Type (InterfaceTable)
typedef  BYTE               TPMI_YES_NO;

// Table 2:40 - Definition of TPMI_DH_OBJECT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_OBJECT;

// Table 2:41 - Definition of TPMI_DH_PARENT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_PARENT;

// Table 2:42 - Definition of TPMI_DH_PERSISTENT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_PERSISTENT;

// Table 2:43 - Definition of TPMI_DH_ENTITY Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_ENTITY;

// Table 2:44 - Definition of TPMI_DH_PCR Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_PCR;

// Table 2:45 - Definition of TPMI_SH_AUTH_SESSION Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_SH_AUTH_SESSION;

// Table 2:46 - Definition of TPMI_SH_HMAC Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_SH_HMAC;

// Table 2:47 - Definition of TPMI_SH_POLICY Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_SH_POLICY;

// Table 2:48 - Definition of TPMI_DH_CONTEXT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_DH_CONTEXT;

// Table 2:49 - Definition of TPMI_RH_HIERARCHY Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_HIERARCHY;

// Table 2:50 - Definition of TPMI_RH_ENABLES Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_ENABLES;

// Table 2:51 - Definition of TPMI_RH_HIERARCHY_AUTH Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_HIERARCHY_AUTH;

// Table 2:52 - Definition of TPMI_RH_PLATFORM Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_PLATFORM;

// Table 2:53 - Definition of TPMI_RH_OWNER Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_OWNER;

// Table 2:54 - Definition of TPMI_RH_ENDORSEMENT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_ENDORSEMENT;

// Table 2:55 - Definition of TPMI_RH_PROVISION Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_PROVISION;

// Table 2:56 - Definition of TPMI_RH_CLEAR Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_CLEAR;

// Table 2:57 - Definition of TPMI_RH_NV_AUTH Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_NV_AUTH;

// Table 2:58 - Definition of TPMI_RH_LOCKOUT Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_LOCKOUT;

// Table 2:59 - Definition of TPMI_RH_NV_INDEX Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_NV_INDEX;

// Table 2:60 - Definition of TPMI_RH_AC Type  (InterfaceTable)
typedef  TPM_HANDLE         TPMI_RH_AC;

// Table 2:61 - Definition of TPMI_ALG_HASH Type  (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_HASH;

// Table 2:62 - Definition of TPMI_ALG_ASYM Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_ASYM;

// Table 2:63 - Definition of TPMI_ALG_SYM Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_SYM;

// Table 2:64 - Definition of TPMI_ALG_SYM_OBJECT Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_SYM_OBJECT;

// Table 2:65 - Definition of TPMI_ALG_SYM_MODE Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_SYM_MODE;

// Table 2:66 - Definition of TPMI_ALG_KDF Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_KDF;

// Table 2:67 - Definition of TPMI_ALG_SIG_SCHEME Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_SIG_SCHEME;

// Table 2:68 - Definition of TPMI_ECC_KEY_EXCHANGE Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ECC_KEY_EXCHANGE;

// Table 2:69 - Definition of TPMI_ST_COMMAND_TAG Type (InterfaceTable)
typedef  TPM_ST             TPMI_ST_COMMAND_TAG;

// Table 2:70 - Definition of TPMI_ALG_MAC_SCHEME Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_MAC_SCHEME;

// Table 2:70 - Definition of TPMI_ALG_CIPHER_MODE Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_CIPHER_MODE;

// Table 2:70 - Definition of TPMS_EMPTY Structure  (StructuresTable)
typedef BYTE TPMS_EMPTY;

// Table 2:71 - Definition of TPMS_ALGORITHM_DESCRIPTION Structure  (StructuresTable)
typedef struct {
    TPM_ALG_ID              alg;
    TPMA_ALGORITHM          attributes;
} TPMS_ALGORITHM_DESCRIPTION;

// Table 2:72 - Definition of TPMU_HA Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_SHA1
    BYTE                    sha1[SHA1_DIGEST_SIZE];
#endif   // TPM_ALG_SHA1
#ifdef      TPM_ALG_SHA256
    BYTE                    sha256[SHA256_DIGEST_SIZE];
#endif   // TPM_ALG_SHA256
#ifdef      TPM_ALG_SHA384
    BYTE                    sha384[SHA384_DIGEST_SIZE];
#endif   // TPM_ALG_SHA384
#ifdef      TPM_ALG_SHA512
    BYTE                    sha512[SHA512_DIGEST_SIZE];
#endif   // TPM_ALG_SHA512
#ifdef      TPM_ALG_SM3_256
    BYTE                    sm3_256[SM3_256_DIGEST_SIZE];
#endif   // TPM_ALG_SM3_256
} TPMU_HA;

// Table 2:73 - Definition of TPMT_HA Structure  (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hashAlg;
    TPMU_HA                 digest;
} TPMT_HA;

// Table 2:74 - Definition of TPM2B_DIGEST Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMU_HA)];
    }            t;
    TPM2B        b;
} TPM2B_DIGEST;

// Table 2:75 - Definition of TPM2B_DATA Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMT_HA)];
    }            t;
    TPM2B        b;
} TPM2B_DATA;

// Table 2:76 - Definition of Types for TPM2B_NONCE (TypedefTable)
typedef  TPM2B_DIGEST       TPM2B_NONCE;

// Table 2:77 - Definition of Types for TPM2B_AUTH (TypedefTable)
typedef  TPM2B_DIGEST       TPM2B_AUTH;

// Table 2:78 - Definition of Types for TPM2B_OPERAND (TypedefTable)
typedef  TPM2B_DIGEST       TPM2B_OPERAND;

// Table 2:79 - Definition of TPM2B_EVENT Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[1024];
    }            t;
    TPM2B        b;
} TPM2B_EVENT;

// Table 2:80 - Definition of TPM2B_MAX_BUFFER Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_DIGEST_BUFFER];
    }            t;
    TPM2B        b;
} TPM2B_MAX_BUFFER;

// Table 2:81 - Definition of TPM2B_MAX_NV_BUFFER Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_NV_BUFFER_SIZE];
    }            t;
    TPM2B        b;
} TPM2B_MAX_NV_BUFFER;

// Table 2:82 - Definition of TPM2B_TIMEOUT Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(UINT64)];
    }            t;
    TPM2B        b;
} TPM2B_TIMEOUT;

// Table 2:83 - Definition of TPM2B_IV Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_SYM_BLOCK_SIZE];
    }            t;
    TPM2B        b;
} TPM2B_IV;

// Table 2:84 - Definition of TPMU_NAME Union  (StructuresTable)
typedef union {
    TPMT_HA                 digest;
    TPM_HANDLE              handle;
} TPMU_NAME;

// Table 2:85 - Definition of TPM2B_NAME Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    name[sizeof(TPMU_NAME)];
    }            t;
    TPM2B        b;
} TPM2B_NAME;

// Table 2:86 - Definition of TPMS_PCR_SELECT Structure (StructuresTable)
typedef struct {
    UINT8                   sizeofSelect;
    BYTE                    pcrSelect[PCR_SELECT_MAX];
} TPMS_PCR_SELECT;

// Table 2:87 - Definition of TPMS_PCR_SELECTION Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hash;
    UINT8                   sizeofSelect;
    BYTE                    pcrSelect[PCR_SELECT_MAX];
} TPMS_PCR_SELECTION;

// Table 2:90 - Definition of TPMT_TK_CREATION Structure (StructuresTable)
typedef struct {
    TPM_ST                  tag;
    TPMI_RH_HIERARCHY       hierarchy;
    TPM2B_DIGEST            digest;
} TPMT_TK_CREATION;

// Table 2:91 - Definition of TPMT_TK_VERIFIED Structure (StructuresTable)
typedef struct {
    TPM_ST                  tag;
    TPMI_RH_HIERARCHY       hierarchy;
    TPM2B_DIGEST            digest;
} TPMT_TK_VERIFIED;

// Table 2:92 - Definition of TPMT_TK_AUTH Structure (StructuresTable)
typedef struct {
    TPM_ST                  tag;
    TPMI_RH_HIERARCHY       hierarchy;
    TPM2B_DIGEST            digest;
} TPMT_TK_AUTH;

// Table 2:93 - Definition of TPMT_TK_HASHCHECK Structure (StructuresTable)
typedef struct {
    TPM_ST                  tag;
    TPMI_RH_HIERARCHY       hierarchy;
    TPM2B_DIGEST            digest;
} TPMT_TK_HASHCHECK;

// Table 2:94 - Definition of TPMS_ALG_PROPERTY Structure  (StructuresTable)
typedef struct {
    TPM_ALG_ID              alg;
    TPMA_ALGORITHM          algProperties;
} TPMS_ALG_PROPERTY;

// Table 2:95 - Definition of TPMS_TAGGED_PROPERTY Structure  (StructuresTable)
typedef struct {
    TPM_PT                  property;
    UINT32                  value;
} TPMS_TAGGED_PROPERTY;

// Table 2:96 - Definition of TPMS_TAGGED_PCR_SELECT Structure  (StructuresTable)
typedef struct {
    TPM_PT_PCR              tag;
    UINT8                   sizeofSelect;
    BYTE                    pcrSelect[PCR_SELECT_MAX];
} TPMS_TAGGED_PCR_SELECT;

// Table 2:97 - Definition of TPMS_TAGGED_POLICY Structure  (StructuresTable)
typedef struct {
    TPM_HANDLE              handle;
    TPMT_HA                 policyHash;
} TPMS_TAGGED_POLICY;

// Table 2:98 - Definition of TPML_CC Structure (StructuresTable)
typedef struct {
    UINT32                  count;
    TPM_CC                  commandCodes[MAX_CAP_CC];
} TPML_CC;

// Table 2:99 - Definition of TPML_CCA Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMA_CC                 commandAttributes[MAX_CAP_CC];
} TPML_CCA;

// Table 2:100 - Definition of TPML_ALG Structure (StructuresTable)
typedef struct {
    UINT32                  count;
    TPM_ALG_ID              algorithms[MAX_ALG_LIST_SIZE];
} TPML_ALG;

// Table 2:101 - Definition of TPML_HANDLE Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPM_HANDLE              handle[MAX_CAP_HANDLES];
} TPML_HANDLE;

// Table 2:102 - Definition of TPML_DIGEST Structure (StructuresTable)
typedef struct {
    UINT32                  count;
    TPM2B_DIGEST            digests[8];
} TPML_DIGEST;

// Table 2:103 - Definition of TPML_DIGEST_VALUES Structure (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMT_HA                 digests[HASH_COUNT];
} TPML_DIGEST_VALUES;

// Table 2:104 - Definition of TPML_PCR_SELECTION Structure (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMS_PCR_SELECTION      pcrSelections[HASH_COUNT];
} TPML_PCR_SELECTION;

// Table 2:105 - Definition of TPML_ALG_PROPERTY Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMS_ALG_PROPERTY       algProperties[MAX_CAP_ALGS];
} TPML_ALG_PROPERTY;

// Table 2:106 - Definition of TPML_TAGGED_TPM_PROPERTY Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMS_TAGGED_PROPERTY    tpmProperty[MAX_TPM_PROPERTIES];
} TPML_TAGGED_TPM_PROPERTY;

// Table 2:107 - Definition of TPML_TAGGED_PCR_PROPERTY Structure  (StructuresTable)
typedef struct {
    UINT32                    count;
    TPMS_TAGGED_PCR_SELECT    pcrProperty[MAX_PCR_PROPERTIES];
} TPML_TAGGED_PCR_PROPERTY;

// Table 2:108 - Definition of TPML_ECC_CURVE Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPM_ECC_CURVE           eccCurves[MAX_ECC_CURVES];
} TPML_ECC_CURVE;

// Table 2:109 - Definition of TPML_TAGGED_POLICY Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMS_TAGGED_POLICY      policies[MAX_TAGGED_POLICIES];
} TPML_TAGGED_POLICY;

// Table 2:110 - Definition of TPMU_CAPABILITIES Union  (StructuresTable)
typedef union {
    TPML_ALG_PROPERTY           algorithms;
    TPML_HANDLE                 handles;
    TPML_CCA                    command;
    TPML_CC                     ppCommands;
    TPML_CC                     auditCommands;
    TPML_PCR_SELECTION          assignedPCR;
    TPML_TAGGED_TPM_PROPERTY    tpmProperties;
    TPML_TAGGED_PCR_PROPERTY    pcrProperties;
#ifdef      TPM_ALG_ECC
    TPML_ECC_CURVE              eccCurves;
#endif   // TPM_ALG_ECC
    TPML_TAGGED_POLICY          authPolicies;
} TPMU_CAPABILITIES;

// Table 2:111 - Definition of TPMS_CAPABILITY_DATA Structure  (StructuresTable)
typedef struct {
    TPM_CAP                 capability;
    TPMU_CAPABILITIES       data;
} TPMS_CAPABILITY_DATA;

// Table 2:112 - Definition of TPMS_CLOCK_INFO Structure (StructuresTable)
typedef struct {
    UINT64                  clock;
    UINT32                  resetCount;
    UINT32                  restartCount;
    TPMI_YES_NO             safe;
} TPMS_CLOCK_INFO;

// Table 2:113 - Definition of TPMS_TIME_INFO Structure (StructuresTable)
typedef struct {
    UINT64                  time;
    TPMS_CLOCK_INFO         clockInfo;
} TPMS_TIME_INFO;

// Table 2:114 - Definition of TPMS_TIME_ATTEST_INFO Structure  (StructuresTable)
typedef struct {
    TPMS_TIME_INFO          time;
    UINT64                  firmwareVersion;
} TPMS_TIME_ATTEST_INFO;

// Table 2:115 - Definition of TPMS_CERTIFY_INFO Structure  (StructuresTable)
typedef struct {
    TPM2B_NAME              name;
    TPM2B_NAME              qualifiedName;
} TPMS_CERTIFY_INFO;

// Table 2:116 - Definition of TPMS_QUOTE_INFO Structure  (StructuresTable)
typedef struct {
    TPML_PCR_SELECTION      pcrSelect;
    TPM2B_DIGEST            pcrDigest;
} TPMS_QUOTE_INFO;

// Table 2:117 - Definition of TPMS_COMMAND_AUDIT_INFO Structure  (StructuresTable)
typedef struct {
    UINT64                  auditCounter;
    TPM_ALG_ID              digestAlg;
    TPM2B_DIGEST            auditDigest;
    TPM2B_DIGEST            commandDigest;
} TPMS_COMMAND_AUDIT_INFO;

// Table 2:118 - Definition of TPMS_SESSION_AUDIT_INFO Structure  (StructuresTable)
typedef struct {
    TPMI_YES_NO             exclusiveSession;
    TPM2B_DIGEST            sessionDigest;
} TPMS_SESSION_AUDIT_INFO;

// Table 2:119 - Definition of TPMS_CREATION_INFO Structure  (StructuresTable)
typedef struct {
    TPM2B_NAME              objectName;
    TPM2B_DIGEST            creationHash;
} TPMS_CREATION_INFO;

// Table 2:120 - Definition of TPMS_NV_CERTIFY_INFO Structure  (StructuresTable)
typedef struct {
    TPM2B_NAME              indexName;
    UINT16                  offset;
    TPM2B_MAX_NV_BUFFER     nvContents;
} TPMS_NV_CERTIFY_INFO;

// Table 2:121 - Definition of TPMI_ST_ATTEST Type  (InterfaceTable)
typedef  TPM_ST             TPMI_ST_ATTEST;

// Table 2:122 - Definition of TPMU_ATTEST Union  (StructuresTable)
typedef union {
    TPMS_CERTIFY_INFO          certify;
    TPMS_CREATION_INFO         creation;
    TPMS_QUOTE_INFO            quote;
    TPMS_COMMAND_AUDIT_INFO    commandAudit;
    TPMS_SESSION_AUDIT_INFO    sessionAudit;
    TPMS_TIME_ATTEST_INFO      time;
    TPMS_NV_CERTIFY_INFO       nv;
} TPMU_ATTEST;

// Table 2:123 - Definition of TPMS_ATTEST Structure  (StructuresTable)
typedef struct {
    TPM_GENERATED           magic;
    TPMI_ST_ATTEST          type;
    TPM2B_NAME              qualifiedSigner;
    TPM2B_DATA              extraData;
    TPMS_CLOCK_INFO         clockInfo;
    UINT64                  firmwareVersion;
    TPMU_ATTEST             attested;
} TPMS_ATTEST;

// Table 2:124 - Definition of TPM2B_ATTEST Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    attestationData[sizeof(TPMS_ATTEST)];
    }            t;
    TPM2B        b;
} TPM2B_ATTEST;

// Table 2:125 - Definition of TPMS_AUTH_COMMAND Structure  (StructuresTable)
typedef struct {
    TPMI_SH_AUTH_SESSION     sessionHandle;
    TPM2B_NONCE              nonce;
    TPMA_SESSION             sessionAttributes;
    TPM2B_AUTH               hmac;
} TPMS_AUTH_COMMAND;

// Table 2:126 - Definition of TPMS_AUTH_RESPONSE Structure  (StructuresTable)
typedef struct {
    TPM2B_NONCE             nonce;
    TPMA_SESSION            sessionAttributes;
    TPM2B_AUTH              hmac;
} TPMS_AUTH_RESPONSE;

// Table 2:127 - Definition of TPMI_TDES_KEY_BITS Type (InterfaceTable)
typedef  TPM_KEY_BITS       TPMI_TDES_KEY_BITS;

// Table 2:127 - Definition of TPMI_AES_KEY_BITS Type (InterfaceTable)
typedef  TPM_KEY_BITS       TPMI_AES_KEY_BITS;

// Table 2:127 - Definition of TPMI_SM4_KEY_BITS Type (InterfaceTable)
typedef  TPM_KEY_BITS       TPMI_SM4_KEY_BITS;

// Table 2:127 - Definition of TPMI_CAMELLIA_KEY_BITS Type (InterfaceTable)
typedef  TPM_KEY_BITS       TPMI_CAMELLIA_KEY_BITS;

// Table 2:128 - Definition of TPMU_SYM_KEY_BITS Union (StructuresTable)
typedef union {
#ifdef      TPM_ALG_TDES
    TPMI_TDES_KEY_BITS        tdes;
#endif   // TPM_ALG_TDES
#ifdef      TPM_ALG_AES
    TPMI_AES_KEY_BITS         aes;
#endif   // TPM_ALG_AES
#ifdef      TPM_ALG_SM4
    TPMI_SM4_KEY_BITS         sm4;
#endif   // TPM_ALG_SM4
#ifdef      TPM_ALG_CAMELLIA
    TPMI_CAMELLIA_KEY_BITS    camellia;
#endif   // TPM_ALG_CAMELLIA
    TPM_KEY_BITS              sym;
#ifdef      TPM_ALG_XOR
    TPMI_ALG_HASH             xor;
#endif   // TPM_ALG_XOR
} TPMU_SYM_KEY_BITS;

// Table 2:129 - Definition of TPMU_SYM_MODE Union (StructuresTable)
typedef union {
#ifdef      TPM_ALG_TDES
    TPMI_ALG_SYM_MODE       tdes;
#endif   // TPM_ALG_TDES
#ifdef      TPM_ALG_AES
    TPMI_ALG_SYM_MODE       aes;
#endif   // TPM_ALG_AES
#ifdef      TPM_ALG_SM4
    TPMI_ALG_SYM_MODE       sm4;
#endif   // TPM_ALG_SM4
#ifdef      TPM_ALG_CAMELLIA
    TPMI_ALG_SYM_MODE       camellia;
#endif   // TPM_ALG_CAMELLIA
    TPMI_ALG_SYM_MODE       sym;
} TPMU_SYM_MODE;

// Table 2:131 - Definition of TPMT_SYM_DEF Structure (StructuresTable)
typedef struct {
    TPMI_ALG_SYM            algorithm;
    TPMU_SYM_KEY_BITS       keyBits;
    TPMU_SYM_MODE           mode;
} TPMT_SYM_DEF;

// Table 2:132 - Definition of TPMT_SYM_DEF_OBJECT Structure (StructuresTable)
typedef struct {
    TPMI_ALG_SYM_OBJECT     algorithm;
    TPMU_SYM_KEY_BITS       keyBits;
    TPMU_SYM_MODE           mode;
} TPMT_SYM_DEF_OBJECT;

// Table 2:133 - Definition of TPM2B_SYM_KEY Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_SYM_KEY_BYTES];
    }            t;
    TPM2B        b;
} TPM2B_SYM_KEY;

// Table 2:134 - Definition of TPMS_SYMCIPHER_PARMS Structure (StructuresTable)
typedef struct {
    TPMT_SYM_DEF_OBJECT     sym;
} TPMS_SYMCIPHER_PARMS;

// Table 2:135 - Definition of TPM2B_LABEL Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[LABEL_MAX_BUFFER];
    }            t;
    TPM2B        b;
} TPM2B_LABEL;

// Table 2:136 - Definition of TPMS_DERIVE Structure (StructuresTable)
typedef struct {
    TPM2B_LABEL             label;
    TPM2B_LABEL             context;
} TPMS_DERIVE;

// Table 2:137 - Definition of TPM2B_DERIVE Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMS_DERIVE)];
    }            t;
    TPM2B        b;
} TPM2B_DERIVE;

// Table 2:138 - Definition of TPMU_SENSITIVE_CREATE Union  (StructuresTable)
typedef union {
    BYTE                    create[MAX_SYM_DATA];
    TPMS_DERIVE             derive;
} TPMU_SENSITIVE_CREATE;

// Table 2:139 - Definition of TPM2B_SENSITIVE_DATA Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMU_SENSITIVE_CREATE)];
    }            t;
    TPM2B        b;
} TPM2B_SENSITIVE_DATA;

// Table 2:140 - Definition of TPMS_SENSITIVE_CREATE Structure  (StructuresTable)
typedef struct {
    TPM2B_AUTH              userAuth;
    TPM2B_SENSITIVE_DATA    data;
} TPMS_SENSITIVE_CREATE;

// Table 2:141 - Definition of TPM2B_SENSITIVE_CREATE Structure  (StructuresTable)
typedef struct {
    UINT16                   size;
    TPMS_SENSITIVE_CREATE    sensitive;
} TPM2B_SENSITIVE_CREATE;

// Table 2:142 - Definition of TPMS_SCHEME_HASH Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hashAlg;
} TPMS_SCHEME_HASH;

// Table 2:143 - Definition of TPMS_SCHEME_ECDAA Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hashAlg;
    UINT16                  count;
} TPMS_SCHEME_ECDAA;

// Table 2:144 - Definition of TPMI_ALG_KEYEDHASH_SCHEME Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_KEYEDHASH_SCHEME;

// Table 2:145 - Definition of Types for HMAC_SIG_SCHEME (TypedefTable)
typedef  TPMS_SCHEME_HASH    TPMS_SCHEME_HMAC;

// Table 2:146 - Definition of TPMS_SCHEME_XOR Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hashAlg;
    TPMI_ALG_KDF            kdf;
} TPMS_SCHEME_XOR;

// Table 2:147 - Definition of TPMU_SCHEME_KEYEDHASH Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_HMAC
    TPMS_SCHEME_HMAC        hmac;
#endif   // TPM_ALG_HMAC
#ifdef      TPM_ALG_XOR
    TPMS_SCHEME_XOR         xor;
#endif   // TPM_ALG_XOR
} TPMU_SCHEME_KEYEDHASH;

// Table 2:148 - Definition of TPMT_KEYEDHASH_SCHEME Structure (StructuresTable)
typedef struct {
    TPMI_ALG_KEYEDHASH_SCHEME     scheme;
    TPMU_SCHEME_KEYEDHASH         details;
} TPMT_KEYEDHASH_SCHEME;

// Table 2:149 - Definition of Types for RSA Signature Schemes  (TypedefTable)
typedef  TPMS_SCHEME_HASH    TPMS_SIG_SCHEME_RSASSA;
typedef  TPMS_SCHEME_HASH    TPMS_SIG_SCHEME_RSAPSS;

// Table 2:150 - Definition of Types for ECC Signature Schemes  (TypedefTable)
typedef  TPMS_SCHEME_HASH     TPMS_SIG_SCHEME_ECDSA;
typedef  TPMS_SCHEME_HASH     TPMS_SIG_SCHEME_SM2;
typedef  TPMS_SCHEME_HASH     TPMS_SIG_SCHEME_ECSCHNORR;
typedef  TPMS_SCHEME_ECDAA    TPMS_SIG_SCHEME_ECDAA;

// Table 2:151 - Definition of TPMU_SIG_SCHEME Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_ECC
    TPMS_SIG_SCHEME_ECDAA        ecdaa;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_RSASSA
    TPMS_SIG_SCHEME_RSASSA       rsassa;
#endif   // TPM_ALG_RSASSA
#ifdef      TPM_ALG_RSAPSS
    TPMS_SIG_SCHEME_RSAPSS       rsapss;
#endif   // TPM_ALG_RSAPSS
#ifdef      TPM_ALG_ECDSA
    TPMS_SIG_SCHEME_ECDSA        ecdsa;
#endif   // TPM_ALG_ECDSA
#ifdef      TPM_ALG_SM2
    TPMS_SIG_SCHEME_SM2          sm2;
#endif   // TPM_ALG_SM2
#ifdef      TPM_ALG_ECSCHNORR
    TPMS_SIG_SCHEME_ECSCHNORR    ecschnorr;
#endif   // TPM_ALG_ECSCHNORR
#ifdef      TPM_ALG_HMAC
    TPMS_SCHEME_HMAC             hmac;
#endif   // TPM_ALG_HMAC
    TPMS_SCHEME_HASH             any;
} TPMU_SIG_SCHEME;

// Table 2:152 - Definition of TPMT_SIG_SCHEME Structure (StructuresTable)
typedef struct {
    TPMI_ALG_SIG_SCHEME     scheme;
    TPMU_SIG_SCHEME         details;
} TPMT_SIG_SCHEME;

// Table 2:153 - Definition of Types for Encryption Schemes (TypedefTable)
typedef  TPMS_SCHEME_HASH    TPMS_ENC_SCHEME_OAEP;
typedef  TPMS_EMPTY          TPMS_ENC_SCHEME_RSAES;

// Table 2:154 - Definition of Types for ECC Key Exchange (TypedefTable)
typedef  TPMS_SCHEME_HASH    TPMS_KEY_SCHEME_ECDH;
typedef  TPMS_SCHEME_HASH    TPMS_KEY_SCHEME_ECMQV;

// Table 2:155 - Definition of Types for KDF Schemes (TypedefTable)
typedef  TPMS_SCHEME_HASH    TPMS_SCHEME_MGF1;
typedef  TPMS_SCHEME_HASH    TPMS_SCHEME_KDF1_SP800_56A;
typedef  TPMS_SCHEME_HASH    TPMS_SCHEME_KDF2;
typedef  TPMS_SCHEME_HASH    TPMS_SCHEME_KDF1_SP800_108;

// Table 2:156 - Definition of TPMU_KDF_SCHEME Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_MGF1
    TPMS_SCHEME_MGF1              mgf1;
#endif   // TPM_ALG_MGF1
#ifdef      TPM_ALG_KDF1_SP800_56A
    TPMS_SCHEME_KDF1_SP800_56A    kdf1_sp800_56a;
#endif   // TPM_ALG_KDF1_SP800_56A
#ifdef      TPM_ALG_KDF2
    TPMS_SCHEME_KDF2              kdf2;
#endif   // TPM_ALG_KDF2
#ifdef      TPM_ALG_KDF1_SP800_108
    TPMS_SCHEME_KDF1_SP800_108    kdf1_sp800_108;
#endif   // TPM_ALG_KDF1_SP800_108
} TPMU_KDF_SCHEME;

// Table 2:157 - Definition of TPMT_KDF_SCHEME Structure (StructuresTable)
typedef struct {
    TPMI_ALG_KDF            scheme;
    TPMU_KDF_SCHEME         details;
} TPMT_KDF_SCHEME;

// Table 2:158 - Definition of TPMI_ALG_ASYM_SCHEME Type  (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_ASYM_SCHEME;

// Table 2:159 - Definition of TPMU_ASYM_SCHEME Union (StructuresTable)
typedef union {
#ifdef      TPM_ALG_ECDH
    TPMS_KEY_SCHEME_ECDH         ecdh;
#endif   // TPM_ALG_ECDH
#ifdef      TPM_ALG_ECMQV
    TPMS_KEY_SCHEME_ECMQV        ecmqv;
#endif   // TPM_ALG_ECMQV
#ifdef      TPM_ALG_ECC
    TPMS_SIG_SCHEME_ECDAA        ecdaa;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_RSASSA
    TPMS_SIG_SCHEME_RSASSA       rsassa;
#endif   // TPM_ALG_RSASSA
#ifdef      TPM_ALG_RSAPSS
    TPMS_SIG_SCHEME_RSAPSS       rsapss;
#endif   // TPM_ALG_RSAPSS
#ifdef      TPM_ALG_ECDSA
    TPMS_SIG_SCHEME_ECDSA        ecdsa;
#endif   // TPM_ALG_ECDSA
#ifdef      TPM_ALG_SM2
    TPMS_SIG_SCHEME_SM2          sm2;
#endif   // TPM_ALG_SM2
#ifdef      TPM_ALG_ECSCHNORR
    TPMS_SIG_SCHEME_ECSCHNORR    ecschnorr;
#endif   // TPM_ALG_ECSCHNORR
#ifdef      TPM_ALG_RSAES
    TPMS_ENC_SCHEME_RSAES        rsaes;
#endif   // TPM_ALG_RSAES
#ifdef      TPM_ALG_OAEP
    TPMS_ENC_SCHEME_OAEP         oaep;
#endif   // TPM_ALG_OAEP
    TPMS_SCHEME_HASH             anySig;
} TPMU_ASYM_SCHEME;

// Table 2:160 - Definition of TPMT_ASYM_SCHEME Structure  (StructuresTable)
typedef struct {
    TPMI_ALG_ASYM_SCHEME     scheme;
    TPMU_ASYM_SCHEME         details;
} TPMT_ASYM_SCHEME;

// Table 2:161 - Definition of TPMI_ALG_RSA_SCHEME Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_RSA_SCHEME;

// Table 2:162 - Definition of TPMT_RSA_SCHEME Structure (StructuresTable)
typedef struct {
    TPMI_ALG_RSA_SCHEME     scheme;
    TPMU_ASYM_SCHEME        details;
} TPMT_RSA_SCHEME;

// Table 2:163 - Definition of TPMI_ALG_RSA_DECRYPT Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_RSA_DECRYPT;

// Table 2:164 - Definition of TPMT_RSA_DECRYPT Structure (StructuresTable)
typedef struct {
    TPMI_ALG_RSA_DECRYPT     scheme;
    TPMU_ASYM_SCHEME         details;
} TPMT_RSA_DECRYPT;

// Table 2:165 - Definition of TPM2B_PUBLIC_KEY_RSA Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_RSA_KEY_BYTES];
    }            t;
    TPM2B        b;
} TPM2B_PUBLIC_KEY_RSA;

// Table 2:166 - Definition of TPMI_RSA_KEY_BITS Type (InterfaceTable)
typedef  TPM_KEY_BITS       TPMI_RSA_KEY_BITS;

// Table 2:167 - Definition of TPM2B_PRIVATE_KEY_RSA Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_RSA_KEY_BYTES/2];
    }            t;
    TPM2B        b;
} TPM2B_PRIVATE_KEY_RSA;

// Table 2:168 - Definition of TPM2B_ECC_PARAMETER Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_ECC_KEY_BYTES];
    }            t;
    TPM2B        b;
} TPM2B_ECC_PARAMETER;

// Table 2:169 - Definition of TPMS_ECC_POINT Structure (StructuresTable)
typedef struct {
    TPM2B_ECC_PARAMETER     x;
    TPM2B_ECC_PARAMETER     y;
} TPMS_ECC_POINT;

// Table 2:170 - Definition of TPM2B_ECC_POINT Structure (StructuresTable)
typedef struct {
    UINT16                  size;
    TPMS_ECC_POINT          point;
} TPM2B_ECC_POINT;

// Table 2:171 - Definition of TPMI_ALG_ECC_SCHEME Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_ECC_SCHEME;

// Table 2:172 - Definition of TPMI_ECC_CURVE Type (InterfaceTable)
typedef  TPM_ECC_CURVE      TPMI_ECC_CURVE;

// Table 2:173 - Definition of TPMT_ECC_SCHEME Structure (StructuresTable)
typedef struct {
    TPMI_ALG_ECC_SCHEME     scheme;
    TPMU_ASYM_SCHEME        details;
} TPMT_ECC_SCHEME;

// Table 2:174 - Definition of TPMS_ALGORITHM_DETAIL_ECC Structure  (StructuresTable)
typedef struct {
    TPM_ECC_CURVE           curveID;
    UINT16                  keySize;
    TPMT_KDF_SCHEME         kdf;
    TPMT_ECC_SCHEME         sign;
    TPM2B_ECC_PARAMETER     p;
    TPM2B_ECC_PARAMETER     a;
    TPM2B_ECC_PARAMETER     b;
    TPM2B_ECC_PARAMETER     gX;
    TPM2B_ECC_PARAMETER     gY;
    TPM2B_ECC_PARAMETER     n;
    TPM2B_ECC_PARAMETER     h;
} TPMS_ALGORITHM_DETAIL_ECC;

// Table 2:175 - Definition of TPMS_SIGNATURE_RSA Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hash;
    TPM2B_PUBLIC_KEY_RSA    sig;
} TPMS_SIGNATURE_RSA;

// Table 2:176 - Definition of Types for Signature  (TypedefTable)
typedef  TPMS_SIGNATURE_RSA    TPMS_SIGNATURE_RSASSA;
typedef  TPMS_SIGNATURE_RSA    TPMS_SIGNATURE_RSAPSS;

// Table 2:177 - Definition of TPMS_SIGNATURE_ECC Structure (StructuresTable)
typedef struct {
    TPMI_ALG_HASH           hash;
    TPM2B_ECC_PARAMETER     signatureR;
    TPM2B_ECC_PARAMETER     signatureS;
} TPMS_SIGNATURE_ECC;

// Table 2:178 - Definition of Types for TPMS_SIGNATURE_ECC (TypedefTable)
typedef  TPMS_SIGNATURE_ECC    TPMS_SIGNATURE_ECDAA;
typedef  TPMS_SIGNATURE_ECC    TPMS_SIGNATURE_ECDSA;
typedef  TPMS_SIGNATURE_ECC    TPMS_SIGNATURE_SM2;
typedef  TPMS_SIGNATURE_ECC    TPMS_SIGNATURE_ECSCHNORR;

// Table 2:179 - Definition of TPMU_SIGNATURE Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_ECC
    TPMS_SIGNATURE_ECDAA        ecdaa;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_RSA
    TPMS_SIGNATURE_RSASSA       rsassa;
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_RSA
    TPMS_SIGNATURE_RSAPSS       rsapss;
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_ECC
    TPMS_SIGNATURE_ECDSA        ecdsa;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_ECC
    TPMS_SIGNATURE_SM2          sm2;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_ECC
    TPMS_SIGNATURE_ECSCHNORR    ecschnorr;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_HMAC
    TPMT_HA                     hmac;
#endif   // TPM_ALG_HMAC
    TPMS_SCHEME_HASH            any;
} TPMU_SIGNATURE;

// Table 2:180 - Definition of TPMT_SIGNATURE Structure (StructuresTable)
typedef struct {
    TPMI_ALG_SIG_SCHEME     sigAlg;
    TPMU_SIGNATURE          signature;
} TPMT_SIGNATURE;

// Table 2:181 - Definition of TPMU_ENCRYPTED_SECRET Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_ECC
    BYTE                    ecc[sizeof(TPMS_ECC_POINT)];
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_RSA
    BYTE                    rsa[MAX_RSA_KEY_BYTES];
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_SYMCIPHER
    BYTE                    symmetric[sizeof(TPM2B_DIGEST)];
#endif   // TPM_ALG_SYMCIPHER
#ifdef      TPM_ALG_KEYEDHASH
    BYTE                    keyedHash[sizeof(TPM2B_DIGEST)];
#endif   // TPM_ALG_KEYEDHASH
} TPMU_ENCRYPTED_SECRET;

// Table 2:182 - Definition of TPM2B_ENCRYPTED_SECRET Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    secret[sizeof(TPMU_ENCRYPTED_SECRET)];
    }            t;
    TPM2B        b;
} TPM2B_ENCRYPTED_SECRET;

// Table 2:183 - Definition of TPMI_ALG_PUBLIC Type (InterfaceTable)
typedef  TPM_ALG_ID         TPMI_ALG_PUBLIC;

// Table 2:184 - Definition of TPMU_PUBLIC_ID Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_KEYEDHASH
    TPM2B_DIGEST            keyedHash;
#endif   // TPM_ALG_KEYEDHASH
#ifdef      TPM_ALG_SYMCIPHER
    TPM2B_DIGEST            sym;
#endif   // TPM_ALG_SYMCIPHER
#ifdef      TPM_ALG_RSA
    TPM2B_PUBLIC_KEY_RSA    rsa;
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_ECC
    TPMS_ECC_POINT          ecc;
#endif   // TPM_ALG_ECC
    TPMS_DERIVE             derive;
} TPMU_PUBLIC_ID;

// Table 2:185 - Definition of TPMS_KEYEDHASH_PARMS Structure (StructuresTable)
typedef struct {
    TPMT_KEYEDHASH_SCHEME     scheme;
} TPMS_KEYEDHASH_PARMS;

// Table 2:186 - Definition of TPMS_ASYM_PARMS Structure  (StructuresTable)
typedef struct {
    TPMT_SYM_DEF_OBJECT     symmetric;
    TPMT_ASYM_SCHEME        scheme;
} TPMS_ASYM_PARMS;

// Table 2:187 - Definition of TPMS_RSA_PARMS Structure (StructuresTable)
typedef struct {
    TPMT_SYM_DEF_OBJECT     symmetric;
    TPMT_RSA_SCHEME         scheme;
    TPMI_RSA_KEY_BITS       keyBits;
    UINT32                  exponent;
} TPMS_RSA_PARMS;

// Table 2:188 - Definition of TPMS_ECC_PARMS Structure (StructuresTable)
typedef struct {
    TPMT_SYM_DEF_OBJECT     symmetric;
    TPMT_ECC_SCHEME         scheme;
    TPMI_ECC_CURVE          curveID;
    TPMT_KDF_SCHEME         kdf;
} TPMS_ECC_PARMS;

// Table 2:189 - Definition of TPMU_PUBLIC_PARMS Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_KEYEDHASH
    TPMS_KEYEDHASH_PARMS    keyedHashDetail;
#endif   // TPM_ALG_KEYEDHASH
#ifdef      TPM_ALG_SYMCIPHER
    TPMS_SYMCIPHER_PARMS    symDetail;
#endif   // TPM_ALG_SYMCIPHER
#ifdef      TPM_ALG_RSA
    TPMS_RSA_PARMS          rsaDetail;
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_ECC
    TPMS_ECC_PARMS          eccDetail;
#endif   // TPM_ALG_ECC
    TPMS_ASYM_PARMS         asymDetail;
} TPMU_PUBLIC_PARMS;

// Table 2:190 - Definition of TPMT_PUBLIC_PARMS Structure (StructuresTable)
typedef struct {
    TPMI_ALG_PUBLIC         type;
    TPMU_PUBLIC_PARMS       parameters;
} TPMT_PUBLIC_PARMS;

// Table 2:191 - Definition of TPMT_PUBLIC Structure (StructuresTable)
typedef struct {
    TPMI_ALG_PUBLIC         type;
    TPMI_ALG_HASH           nameAlg;
    TPMA_OBJECT             objectAttributes;
    TPM2B_DIGEST            authPolicy;
    TPMU_PUBLIC_PARMS       parameters;
    TPMU_PUBLIC_ID          unique;
} TPMT_PUBLIC;

// Table 2:192 - Definition of TPM2B_PUBLIC Structure (StructuresTable)
typedef struct {
    UINT16                  size;
    TPMT_PUBLIC             publicArea;
} TPM2B_PUBLIC;

// Table 2:193 - Definition of TPM2B_TEMPLATE Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMT_PUBLIC)];
    }            t;
    TPM2B        b;
} TPM2B_TEMPLATE;

// Table 2:194 - Definition of TPM2B_PRIVATE_VENDOR_SPECIFIC Structure (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[PRIVATE_VENDOR_SPECIFIC_BYTES];
    }            t;
    TPM2B        b;
} TPM2B_PRIVATE_VENDOR_SPECIFIC;

// Table 2:195 - Definition of TPMU_SENSITIVE_COMPOSITE Union  (StructuresTable)
typedef union {
#ifdef      TPM_ALG_RSA
    TPM2B_PRIVATE_KEY_RSA            rsa;
#endif   // TPM_ALG_RSA
#ifdef      TPM_ALG_ECC
    TPM2B_ECC_PARAMETER              ecc;
#endif   // TPM_ALG_ECC
#ifdef      TPM_ALG_KEYEDHASH
    TPM2B_SENSITIVE_DATA             bits;
#endif   // TPM_ALG_KEYEDHASH
#ifdef      TPM_ALG_SYMCIPHER
    TPM2B_SYM_KEY                    sym;
#endif   // TPM_ALG_SYMCIPHER
    TPM2B_PRIVATE_VENDOR_SPECIFIC    any;
} TPMU_SENSITIVE_COMPOSITE;

// Table 2:196 - Definition of TPMT_SENSITIVE Structure (StructuresTable)
typedef struct {
    TPMI_ALG_PUBLIC             sensitiveType;
    TPM2B_AUTH                  authValue;
    TPM2B_DIGEST                seedValue;
    TPMU_SENSITIVE_COMPOSITE    sensitive;
} TPMT_SENSITIVE;

// Table 2:197 - Definition of TPM2B_SENSITIVE Structure  (StructuresTable)
typedef struct {
    UINT16                  size;
    TPMT_SENSITIVE          sensitiveArea;
} TPM2B_SENSITIVE;

// Table 2:198 - Definition of _PRIVATE Structure  (StructuresTable)
typedef struct {
    TPM2B_DIGEST            integrityOuter;
    TPM2B_DIGEST            integrityInner;
    TPM2B_SENSITIVE         sensitive;
} _PRIVATE;

// Table 2:199 - Definition of TPM2B_PRIVATE Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(_PRIVATE)];
    }            t;
    TPM2B        b;
} TPM2B_PRIVATE;

// Table 2:200 - Definition of TPMS_ID_OBJECT Structure  (StructuresTable)
typedef struct {
    TPM2B_DIGEST            integrityHMAC;
    TPM2B_DIGEST            encIdentity;
} TPMS_ID_OBJECT;

// Table 2:201 - Definition of TPM2B_ID_OBJECT Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    credential[sizeof(TPMS_ID_OBJECT)];
    }            t;
    TPM2B        b;
} TPM2B_ID_OBJECT;

// Table 2:202 - Definition of TPM_NV_INDEX Bits  (BitsTable)
typedef struct {
    unsigned    index   : 24;
    unsigned    RH_NV   : 8 ;
} TPM_NV_INDEX;


// Table 2:203 - Definition of TPM_NT Constants (EnumTable)
typedef  UINT32             TPM_NT;
#define  TPM_NT_ORDINARY    (TPM_NT)(0x0)
#define  TPM_NT_COUNTER     (TPM_NT)(0x1)
#define  TPM_NT_BITS        (TPM_NT)(0x2)
#define  TPM_NT_EXTEND      (TPM_NT)(0x4)
#define  TPM_NT_PIN_FAIL    (TPM_NT)(0x8)
#define  TPM_NT_PIN_PASS    (TPM_NT)(0x9)

// Table 2:204 - Definition of TPMS_NV_PIN_COUNTER_PARAMETERS Structure (StructuresTable)
typedef struct {
    UINT32                  pinCount;
    UINT32                  pinLimit;
} TPMS_NV_PIN_COUNTER_PARAMETERS;

// Table 2:205 - Definition of TPMA_NV Bits (BitsTable)
typedef struct {
    unsigned    TPMA_NV_PPWRITE          : 1 ;
    unsigned    TPMA_NV_OWNERWRITE       : 1 ;
    unsigned    TPMA_NV_AUTHWRITE        : 1 ;
    unsigned    TPMA_NV_POLICYWRITE      : 1 ;
    unsigned    TPM_NT                   : 4 ;
    unsigned    Reserved_at_bit_8        : 2 ;
    unsigned    TPMA_NV_POLICY_DELETE    : 1 ;
    unsigned    TPMA_NV_WRITELOCKED      : 1 ;
    unsigned    TPMA_NV_WRITEALL         : 1 ;
    unsigned    TPMA_NV_WRITEDEFINE      : 1 ;
    unsigned    TPMA_NV_WRITE_STCLEAR    : 1 ;
    unsigned    TPMA_NV_GLOBALLOCK       : 1 ;
    unsigned    TPMA_NV_PPREAD           : 1 ;
    unsigned    TPMA_NV_OWNERREAD        : 1 ;
    unsigned    TPMA_NV_AUTHREAD         : 1 ;
    unsigned    TPMA_NV_POLICYREAD       : 1 ;
    unsigned    Reserved_at_bit_20       : 5 ;
    unsigned    TPMA_NV_NO_DA            : 1 ;
    unsigned    TPMA_NV_ORDERLY          : 1 ;
    unsigned    TPMA_NV_CLEAR_STCLEAR    : 1 ;
    unsigned    TPMA_NV_READLOCKED       : 1 ;
    unsigned    TPMA_NV_WRITTEN          : 1 ;
    unsigned    TPMA_NV_PLATFORMCREATE   : 1 ;
    unsigned    TPMA_NV_READ_STCLEAR     : 1 ;
} TPMA_NV;

#define IsNv_TPMA_NV_PPWRITE(attribute)                    \
        ((attribute.TPMA_NV_PPWRITE) != 0)
#define IsNv_TPMA_NV_OWNERWRITE(attribute)                 \
        ((attribute.TPMA_NV_OWNERWRITE) != 0)
#define IsNv_TPMA_NV_AUTHWRITE(attribute)                  \
        ((attribute.TPMA_NV_AUTHWRITE) != 0)
#define IsNv_TPMA_NV_POLICYWRITE(attribute)                \
        ((attribute.TPMA_NV_POLICYWRITE) != 0)
#define IsNv_TPMA_NV_POLICY_DELETE(attribute)              \
        ((attribute.TPMA_NV_POLICY_DELETE) != 0)
#define IsNv_TPMA_NV_WRITELOCKED(attribute)                \
        ((attribute.TPMA_NV_WRITELOCKED) != 0)
#define IsNv_TPMA_NV_WRITEALL(attribute)                   \
        ((attribute.TPMA_NV_WRITEALL) != 0)
#define IsNv_TPMA_NV_WRITEDEFINE(attribute)                \
        ((attribute.TPMA_NV_WRITEDEFINE) != 0)
#define IsNv_TPMA_NV_WRITE_STCLEAR(attribute)              \
        ((attribute.TPMA_NV_WRITE_STCLEAR) != 0)
#define IsNv_TPMA_NV_GLOBALLOCK(attribute)                 \
        ((attribute.TPMA_NV_GLOBALLOCK) != 0)
#define IsNv_TPMA_NV_PPREAD(attribute)                     \
        ((attribute.TPMA_NV_PPREAD) != 0)
#define IsNv_TPMA_NV_OWNERREAD(attribute)                  \
        ((attribute.TPMA_NV_OWNERREAD) != 0)
#define IsNv_TPMA_NV_AUTHREAD(attribute)                   \
        ((attribute.TPMA_NV_AUTHREAD) != 0)
#define IsNv_TPMA_NV_POLICYREAD(attribute)                 \
        ((attribute.TPMA_NV_POLICYREAD) != 0)
#define IsNv_TPMA_NV_NO_DA(attribute)                      \
        ((attribute.TPMA_NV_NO_DA) != 0)
#define IsNv_TPMA_NV_ORDERLY(attribute)                    \
        ((attribute.TPMA_NV_ORDERLY) != 0)
#define IsNv_TPMA_NV_CLEAR_STCLEAR(attribute)              \
        ((attribute.TPMA_NV_CLEAR_STCLEAR) != 0)
#define IsNv_TPMA_NV_READLOCKED(attribute)                 \
        ((attribute.TPMA_NV_READLOCKED) != 0)
#define IsNv_TPMA_NV_WRITTEN(attribute)                    \
        ((attribute.TPMA_NV_WRITTEN) != 0)
#define IsNv_TPMA_NV_PLATFORMCREATE(attribute)             \
        ((attribute.TPMA_NV_PLATFORMCREATE) != 0)
#define IsNv_TPMA_NV_READ_STCLEAR(attribute)               \
        ((attribute.TPMA_NV_READ_STCLEAR) != 0)

// Table 2:206 - Definition of TPMS_NV_PUBLIC Structure (StructuresTable)
typedef struct {
    TPMI_RH_NV_INDEX        nvIndex;
    TPMI_ALG_HASH           nameAlg;
    TPMA_NV                 attributes;
    TPM2B_DIGEST            authPolicy;
    UINT16                  dataSize;
} TPMS_NV_PUBLIC;

// Table 2:207 - Definition of TPM2B_NV_PUBLIC Structure (StructuresTable)
typedef struct {
    UINT16                  size;
    TPMS_NV_PUBLIC          nvPublic;
} TPM2B_NV_PUBLIC;

// Table 2:208 - Definition of TPM2B_CONTEXT_SENSITIVE Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[MAX_CONTEXT_SIZE];
    }            t;
    TPM2B        b;
} TPM2B_CONTEXT_SENSITIVE;

// Table 2:209 - Definition of TPMS_CONTEXT_DATA Structure  (StructuresTable)
typedef struct {
    TPM2B_DIGEST               integrity;
    TPM2B_CONTEXT_SENSITIVE    encrypted;
} TPMS_CONTEXT_DATA;

// Table 2:210 - Definition of TPM2B_CONTEXT_DATA Structure  (StructuresTable)
typedef union {
    struct {
        UINT16                  size;
        BYTE                    buffer[sizeof(TPMS_CONTEXT_DATA)];
    }            t;
    TPM2B        b;
} TPM2B_CONTEXT_DATA;

// Table 2:211 - Definition of TPMS_CONTEXT Structure (StructuresTable)
typedef struct {
    UINT64                  sequence;
    TPMI_DH_CONTEXT         savedHandle;
    TPMI_RH_HIERARCHY       hierarchy;
    TPM2B_CONTEXT_DATA      contextBlob;
} TPMS_CONTEXT;

// Table 2:213 - Definition of TPMS_CREATION_DATA Structure  (StructuresTable)
typedef struct {
    TPML_PCR_SELECTION      pcrSelect;
    TPM2B_DIGEST            pcrDigest;
    TPMA_LOCALITY           locality;
    TPM_ALG_ID              parentNameAlg;
    TPM2B_NAME              parentName;
    TPM2B_NAME              parentQualifiedName;
    TPM2B_DATA              outsideInfo;
} TPMS_CREATION_DATA;

// Table 2:214 - Definition of TPM2B_CREATION_DATA Structure  (StructuresTable)
typedef struct {
    UINT16                  size;
    TPMS_CREATION_DATA      creationData;
} TPM2B_CREATION_DATA;

// Table 2:215 - Definition of TPM_AT Constants (EnumTable)
typedef  UINT32             TPM_AT;
#define  TPM_AT_ANY      (TPM_AT)(0x00000000)
#define  TPM_AT_ERROR    (TPM_AT)(0x00000001)
#define  TPM_AT_PV1      (TPM_AT)(0x00000002)
#define  TPM_AT_VEND     (TPM_AT)(0x80000000)

// Table 2:216 - Definition of TPM_AE Constants  (EnumTable)
typedef  UINT32             TPM_AE;
#define  TPM_AE_NONE    (TPM_AE)(0x00000000)

// Table 2:217 - Definition of TPMS_AC_OUTPUT Structure  (StructuresTable)
typedef struct {
    TPM_AT                  tag;
    UINT32                  data;
} TPMS_AC_OUTPUT;

// Table 2:218 - Definition of TPML_AC_CAPABILITIES Structure  (StructuresTable)
typedef struct {
    UINT32                  count;
    TPMS_AC_OUTPUT          acCapabilities[MAX_AC_CAPABILITIES];
} TPML_AC_CAPABILITIES;


#endif    //  _TPM_TYPES_H_
