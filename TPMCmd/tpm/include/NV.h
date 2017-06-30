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

//** Index Type Definitions

// These definitions allow the same code to be used pre and post 1.21. The main
// action is to redefine the index type values from the bit values.
// Use TPM_NT_ORDINARY to indicate if the TPM_NT type is defined

#ifndef    _NV_H_
#define    _NV_H_

#ifdef     TPM_NT_ORDINARY
#   define NV_ATTRIBUTES_TO_TYPE(attributes) (attributes.TPM_NT)
#else
#   define NV_ATTRIBUTES_TO_TYPE(attributes)        \
        (   attributes.TPMA_NV_COUNTER              \
        +   (attributes.TPMA_NV_BITS << 1)          \
        +   (attributes.TPMA_NV_EXTEND << 2)        \
        )
#endif

//** Attribute Macros
// These macros are used to isolate the differences in the way that the index type
// changed in version 1.21 of the specification
#ifdef TPM_NT_ORDINARY
#   define  IsNvOrdinaryIndex(attributes) (attributes.TPM_NT == TPM_NT_ORDINARY)
#else
#   define IsNvOrdinaryIndex(attributes)                                    \
            ((attributes.TPMA_NV_COUNTER == CLEAR)                          \
            && (attributes.TPMA_NV_BITS == CLEAR)                           \
            && (attributes.TPMA_NV_EXTEND == CLEAR)
#   define TPM_NT_ORDINARY  (0)
#endif

#ifdef  TPM_NT_COUNTER
#   define  IsNvCounterIndex(attributes) (attributes.TPM_NT == TPM_NT_COUNTER)
#else
#   define IsNvCounterIndex(attributes) (attributes.TPMA_NV_COUNTER == SET)
#   define  TPM_NT_COUNTER  (1)
#endif

#ifdef  TPM_NT_BITS
#   define  IsNvBitsIndex(attributes) (attributes.TPM_NT == TPM_NT_BITS)
#else
#   define  IsNvBitsIndex(attributes) (attributes.TPMA_NV_BITS == SET)
#   define  TPM_NT_BITS (2)
#endif

#ifdef  TPM_NT_EXTEND
#   define  IsNvExtendIndex(attributes) (attributes.TPM_NT == TPM_NT_EXTEND)
#else
#   define IsNvExtendIndex(attributes) (attributes.TPMA_NV_EXTEND == SET)
#   define  TPM_NT_EXTEND   (4)
#endif

#ifdef TPM_NT_PIN_PASS
#   define  IsNvPinPassIndex(attributes) (attributes.TPM_NT == TPM_NT_PIN_PASS)
#endif

#ifdef TPM_NT_PIN_FAIL
#   define  IsNvPinFailIndex(attributes) (attributes.TPM_NT == TPM_NT_PIN_FAIL)
#endif

typedef struct {
    UINT32      size;
    TPM_HANDLE  handle;
} NV_ENTRY_HEADER;

#define NV_EVICT_OBJECT_SIZE        \
     (sizeof(UINT32)  + sizeof(TPM_HANDLE) + sizeof(OBJECT))

#define NV_INDEX_COUNTER_SIZE       \
    (sizeof(UINT32) + sizeof(NV_INDEX) + sizeof(UINT64))

#define NV_RAM_INDEX_COUNTER_SIZE   \
    (sizeof(NV_RAM_HEADER) + sizeof(UINT64))

typedef struct {
    UINT32          size;
    TPM_HANDLE      handle;
    TPMA_NV         attributes;
} NV_RAM_HEADER;

// Defines the end-of-list marker for NV. The list terminator is
// a UINT32 of zero, followed by the current value of s_maxCounter which is a
// 64-bit value. The structure is defined as an array of 3 UINT32 values so that
// there is no padding between the  UINT32 list end marker and the UIT64m maxCounter
// value.
typedef UINT32 NV_LIST_TERMINATOR[3];

//** Orderly RAM Values
// The following defines are for accessing orderly RAM values.

// This is the initialize for the RAM reference iterator.
#define     NV_RAM_REF_INIT         0
// This is the starting address of the RAM space used for orderly data
#define     RAM_ORDERLY_START               \
                (&s_indexOrderlyRam[0])
// This is the offset within NV that is used to save the orderly data on an
// orderly shutdown.
#define     NV_ORDERLY_START                \
                (NV_INDEX_RAM_DATA)
// This is the end of the orderly RAM space. It is actually the first byte after the
// last byte of orderly RAM data
#define     RAM_ORDERLY_END                 \
                (RAM_ORDERLY_START + sizeof(s_indexOrderlyRam))
// This is the end of the orderly space in NV memory. As with RAM_ORDERLY_END, it is
// actually the offset of the first byte after the end of the NV orderly data.
#define     NV_ORDERLY_END                  \
                (NV_ORDERLY_START + sizeof(s_indexOrderlyRam))

// Macro to check that an orderly RAM address is with range.
#define ORDERLY_RAM_ADDRESS_OK(start, offset)       \
        ((start >= RAM_ORDERLY_START) && ((start + offset - 1) < RAM_ORDERLY_END))


#define RETURN_IF_NV_IS_NOT_AVAILABLE               \
{                                                   \
    if(g_NvStatus != TPM_RC_SUCCESS)                \
        return g_NvStatus;                          \
}

// Routinely have to clear the orderly flag and fail if the
// NV is not available so that it can be cleared.
#define RETURN_IF_ORDERLY                           \
{                                                   \
    if(NvClearOrderly() != TPM_RC_SUCCESS)          \
        return g_NvStatus;                          \
}
 
#define NV_IS_AVAILABLE     (g_NvStatus == TPM_RC_SUCCESS)

#define IS_ORDERLY(value)   (value < SU_DA_USED_VALUE)

#define NV_IS_ORDERLY       (IS_ORDERLY(gp.orderlyState))

// Macro to set the NV UPDATE_TYPE. This deals with the fact that the update is
// possibly a combination of UT_NV and UT_ORDERLY.
#define SET_NV_UPDATE(type)     g_updateNV |= (type)
    
#endif  // _NV_H_