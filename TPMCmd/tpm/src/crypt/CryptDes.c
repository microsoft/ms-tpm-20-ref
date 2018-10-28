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
//** Introduction
//
// This file contains the extra functions required for TDES.

//** Includes, Defines, and Typedefs
#include "Tpm.h"

#if     ALG_TDES


#define DES_NUM_WEAK 64
const UINT64 DesWeakKeys[DES_NUM_WEAK] = {
    0x0101010101010101, 0xFEFEFEFEFEFEFEFE, 0xE0E0E0E0F1F1F1F1, 0x1F1F1F1F0E0E0E0E,
    0x011F011F010E010E, 0x1F011F010E010E01, 0x01E001E001F101F1, 0xE001E001F101F101,
    0x01FE01FE01FE01FE, 0xFE01FE01FE01FE01, 0x1FE01FE00EF10EF1, 0xE01FE01FF10EF10E,
    0x1FFE1FFE0EFE0EFE, 0xFE1FFE1FFE0EFE0E, 0xE0FEE0FEF1FEF1FE, 0xFEE0FEE0FEF1FEF1,
    0x01011F1F01010E0E, 0x1F1F01010E0E0101, 0xE0E01F1FF1F10E0E, 0x0101E0E00101F1F1,
    0x1F1FE0E00E0EF1F1, 0xE0E0FEFEF1F1FEFE, 0x0101FEFE0101FEFE, 0x1F1FFEFE0E0EFEFE,
    0xE0FE011FF1FE010E, 0x011F1F01010E0E01, 0x1FE001FE0EF101FE, 0xE0FE1F01F1FE0E01,
    0x011FE0FE010EF1FE, 0x1FE0E01F0EF1F10E, 0xE0FEFEE0F1FEFEF1, 0x011FFEE0010EFEF1,
    0x1FE0FE010EF1FE01, 0xFE0101FEFE0101FE, 0x01E01FFE01F10EFE, 0x1FFE01E00EFE01F1,
    0xFE011FE0FE010EF1, 0xFE01E01FFE01F10E, 0x1FFEE0010EFEF101, 0xFE1F01E0FE0E01F1,
    0x01E0E00101F1F101, 0x1FFEFE1F0EFEFE0E, 0xFE1FE001FE0EF101, 0x01E0FE1F01F1FE0E,
    0xE00101E0F10101F1, 0xFE1F1FFEFE0E0EFE, 0x01FE1FE001FE0EF1, 0xE0011FFEF1010EFE,
    0xFEE0011FFEF1010E, 0x01FEE01F01FEF10E, 0xE001FE1FF101FE0E, 0xFEE01F01FEF10E01,
    0x01FEFE0101FEFE01, 0xE01F01FEF10E01FE, 0xFEE0E0FEFEF1F1FE, 0x1F01011F0E01010E,
    0xE01F1FE0F10E0EF1, 0xFEFE0101FEFE0101, 0x1F01E0FE0E01F1FE, 0xE01FFE01F10EFE01,
    0xFEFE1F1FFEFE0E0E, 0x1F01FEE00E01FEF1, 0xE0E00101F1F10101, 0xFEFEE0E0FEFEF1F1};


//*** CryptSetOddByteParity()
// This function sets the per byte parity of a 64-bit value. The least-significant
// bit is of each byte is replaced with the odd parity of the other 7 bits in the
// byte. With odd parity, no byte will ever be 0x00.
UINT64
CryptSetOddByteParity(
    UINT64          k
    )
{
#define PMASK 0x0101010101010101ULL
    UINT64          out;
    k |= PMASK;     // set the parity bit 
    out = k;
    k ^= k >> 4;
    k ^= k >> 2;
    k ^= k >> 1;
    k &= PMASK;     // odd parity extracted  
    out ^= k;       // out is now even parity because parity bit was already set
    out ^= PMASK;   // out is now even parity
    return out;
}


//*** CryptDesIsWeakKey()
// Check to see if a DES key is on the list of weak, semi-weak, or possibly weak 
// keys.
//  Return Type: BOOL
//      TRUE(1)         DES key is weak
//      FALSE(0)        DES key is not weak
static BOOL
CryptDesIsWeakKey(
    UINT64            k
    )
{
    int              i;
//
    for(i = 0; i < DES_NUM_WEAK; i++)
    {
        if(k == DesWeakKeys[i])
            return TRUE;
    }
    return FALSE;
}

//*** CryptDesValidateKey()
// Function to check to see if the input key is a valid DES key where the definition
// of valid is that none of the elements are on the list of weak, semi-weak, or
// possibly weak keys; and that for two keys, K1!=K2, and for three keys that
// K1!=K2 and K2!=K3.
BOOL
CryptDesValidateKey(
    TPM2B_SYM_KEY       *desKey     // IN: key to validate
    )
{
    UINT64               k[3];
    int                  i;
    int                  keys = (desKey->t.size + 7) / 8;
    BYTE                *pk = desKey->t.buffer;
    BOOL                 ok;
//
    // Note: 'keys' is the number of keys, not the maximum index for 'k'
    ok = ((keys == 2) || (keys == 3)) && ((desKey->t.size % 8) == 0);
    for(i = 0; ok && i < keys; pk += 8, i++)
    {
        k[i] = CryptSetOddByteParity(BYTE_ARRAY_TO_UINT64(pk));
        ok = !CryptDesIsWeakKey(k[i]);
    }
    ok = ok && k[0] != k[1];
    if(keys == 3)
        ok = ok && k[1] != k[2];
    return ok;
}

//*** CryptGenerateKeyDes()
// This function is used to create a DES key of the appropriate size. The key will
// have odd parity in the bytes.
TPM_RC
CryptGenerateKeyDes(
    TPMT_PUBLIC             *publicArea,        // IN/OUT: The public area template
                                                //     for the new key.
    TPMT_SENSITIVE          *sensitive,         // OUT: sensitive area
    RAND_STATE              *rand               // IN: the "entropy" source for
    )
{

    // Assume that the publicArea key size has been validated and is a supported
    // number of bits.
    sensitive->sensitive.sym.t.size =  
            BITS_TO_BYTES(publicArea->parameters.symDetail.sym.keyBits.sym);
    do
    {
        BYTE                    *pK = sensitive->sensitive.sym.t.buffer;
        int                      i = (sensitive->sensitive.sym.t.size + 7) / 8;
// Use the random number generator to generate the required number of bits
        if(DRBG_Generate(rand, pK, sensitive->sensitive.sym.t.size) == 0)
            return TPM_RC_NO_RESULT;
        for(; i > 0; pK += 8, i--)
        {
            UINT64      k = BYTE_ARRAY_TO_UINT64(pK);
            k = CryptSetOddByteParity(k);
            UINT64_TO_BYTE_ARRAY(k, pK);
        }
    } while(!CryptDesValidateKey(&sensitive->sensitive.sym));
    return TPM_RC_SUCCESS;
}

#endif
//***
