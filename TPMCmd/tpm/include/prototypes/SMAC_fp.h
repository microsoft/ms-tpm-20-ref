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
    This file created on Feb  2, 2017, 05:17:05PM 

*/

#ifdef TPM_CC_SMAC // Command must be defined
#ifndef _SMAC_H
#define _SMAC_H

// Input structure definition
typedef struct {
    TPMI_DH_OBJECT            keyHandle;
    TPM2B_MAX_BUFFER          inData;
    TPMI_YES_NO               lastBlock;
    TPMI_ALG_SYM_MODE_MAC     mode;
    TPM2B_IV                  ivIn;
} SMAC_In;

// Output structure definition
typedef struct {
    TPM2B_IV                  outMAC_IV;
} SMAC_Out;

// Response code modifiers
#define    RC_SMAC_keyHandle     (TPM_RC_H + TPM_RC_1)
#define    RC_SMAC_inData        (TPM_RC_P + TPM_RC_1)
#define    RC_SMAC_lastBlock     (TPM_RC_P + TPM_RC_2)
#define    RC_SMAC_mode          (TPM_RC_P + TPM_RC_3)
#define    RC_SMAC_ivIn          (TPM_RC_P + TPM_RC_4)

// Function prototype
TPM_RC
TPM2_SMAC(
    SMAC_In *in,
    SMAC_Out *out
);


#endif  // _SMAC_H
#endif  // TPM_CC_SMAC
