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
// This file contains the math functions that are not implemented in the BnMath
// library (yet). These math functions will call the OpenSSL library to execute
// the operations. There is a difference between the internal format and the
// OpenSSL format. To call the OpenSSL function, a BIGNUM structure is created
// for each passed variable. The sizes in the bignum_t are copied and the 'd'
// pointer in the BIGNUM is set to point to the 'd' parameter of the bignum_t.
// On return, SetSizeOsslToTpm is used for each returned variable to make sure that
// the pointers are not changed. The size of the returned BIGGNUM is copied to
// bignum_t.

//** Includes and Defines
#include "Tpm.h"

#if MATH_LIB == OSSL

#include "TpmToOsslMath_fp.h"

//** Functions

//*** OsslToTpmBn()
// This function converts an OpenSSL BIGNUM to a TPM bignum. In this implementation
// it is assumed that OpenSSL used the same format for a big number as does the
// TPM -- an array of native-endian words in little-endian order.
//
// If the array allocated for the OpenSSL BIGNUM is not the space within the TPM
// bignum, then the data is copied. Otherwise, just the size field of the BIGNUM
// is copied.
void
OsslToTpmBn(
    bigNum          bn,
    BIGNUM          *osslBn
    )
{
    if(bn != NULL)
    {
        if((crypt_uword_t *)osslBn->d != bn->d)
        {
            int         i;
            pAssert((unsigned)osslBn->top <= BnGetAllocated(bn));
            for(i = 0; i < osslBn->top; i++)
                bn->d[i] = osslBn->d[i];
        }
        BnSetTop(bn, osslBn->top);
    }
}

//*** BigInitialized()
// This function initializes an OSSL BIGNUM from a TPM bignum.
BIGNUM *
BigInitialized(
    BIGNUM             *toInit,
    bigConst            initializer
    )
{
    if(toInit == NULL || initializer == NULL)
        return NULL;
    toInit->d = (BN_ULONG *)&initializer->d[0];
    toInit->dmax = initializer->allocated;
    toInit->top = initializer->size;
    toInit->neg = 0;
    toInit->flags = 0;
    return toInit;
}

#ifndef OSSL_DEBUG
#   define BIGNUM_PRINT(label, bn, eol)
#   define DEBUG_PRINT(x)
#else
#   define DEBUG_PRINT(x)   printf("%s", x)
#   define BIGNUM_PRINT(label, bn, eol) BIGNUM_print((label), (bn), (eol))
static
void BIGNUM_print(
    const char      *label,
    const BIGNUM    *a,
    BOOL             eol
    )
{
    BN_ULONG        *d;
    int              i;
    int              notZero = FALSE;

    if(label != NULL)
        printf("%s", label);
    if(a == NULL)
    {
        printf("NULL");
        goto done;
    }
    if (a->neg)
        printf("-");
    for(i = a->top, d = &a->d[i - 1]; i > 0; i--)
    {
        int         j;
        BN_ULONG    l = *d--;                
        for(j = BN_BITS2 - 8; j >= 0; j -= 8)
        {
            BYTE    b = (BYTE)((l >> j) & 0xFF);
            notZero = notZero || (b != 0);
            if(notZero)
                printf("%02x", b);
        }
        if(!notZero)
            printf("0");
    }
done:
    if(eol)
        printf("\n");
    return;
}
#endif

#if LIBRARY_COMPATIBILITY_CHECK
void
MathLibraryCompatibilityCheck(
    void 
    )
{
    OSSL_ENTER();
    BIGNUM          *osslTemp = BN_CTX_get(CTX);
    BN_VAR(tpmTemp, 64 * 8); // allocate some space for a test value
    crypt_uword_t           i;
    TPM2B_TYPE(TEST, 16);
    TPM2B_TEST              test = {{16, {0x0F, 0x0E, 0x0D, 0x0C, 
                                          0x0B, 0x0A, 0x09, 0x08, 
                                          0x07, 0x06, 0x05, 0x04, 
                                          0x03, 0x02, 0x01, 0x00}}};
    // Convert the test TPM2B to a bigNum
    BnFrom2B(tpmTemp, &test.b);
    // Convert the test TPM2B to an OpenSSL BIGNUM
    BN_bin2bn(test.t.buffer, test.t.size, osslTemp);
    // Make sure the values are consistent
    cAssert(osslTemp->top == (int)tpmTemp->size);
    for(i = 0; i < tpmTemp->size; i++)
        cAssert(osslTemp->d[0] == tpmTemp->d[0]);
    OSSL_LEAVE();
}
#endif

//*** BnModMult()
// Does multiply and divide returning the remainder of the divide.
LIB_EXPORT BOOL
BnModMult(
    bigNum              result,
    bigConst            op1,
    bigConst            op2,
    bigConst            modulus
    )
{
    OSSL_ENTER();
    BIG_INITIALIZED(bnResult, result);
    BIG_INITIALIZED(bnOp1, op1);
    BIG_INITIALIZED(bnOp2, op2);
    BIG_INITIALIZED(bnMod, modulus);
    BIG_VAR(bnTemp, (LARGEST_NUMBER_BITS * 4));
    BOOL                OK;
    pAssert(BnGetAllocated(result) >= BnGetSize(modulus));
    OK = BN_mul(bnTemp, bnOp1, bnOp2, CTX);
    OK = OK && BN_div(NULL, bnResult, bnTemp, bnMod, CTX);
    if(OK)
    {
        result->size = bnResult->top;
        OsslToTpmBn(result, bnResult);
    }
    OSSL_LEAVE();
    return OK;
}

//*** BnMult()
// Multiplies two numbers
LIB_EXPORT BOOL
BnMult(
    bigNum               result,
    bigConst             multiplicand,
    bigConst             multiplier
    )
{
    OSSL_ENTER();
    BN_VAR(temp, (LARGEST_NUMBER_BITS * 2));
    BIG_INITIALIZED(bnTemp, temp);
    BIG_INITIALIZED(bnA, multiplicand);
    BIG_INITIALIZED(bnB, multiplier);
    BOOL                OK;
    pAssert(result->allocated >=
            (BITS_TO_CRYPT_WORDS(BnSizeInBits(multiplicand)
                                 + BnSizeInBits(multiplier))));
    OK = BN_mul(bnTemp, bnA, bnB, CTX);
    if(OK)
    {
        OsslToTpmBn(temp, bnTemp);
        BnCopy(result, temp);
    }
    OSSL_LEAVE();
    return OK;
}

//*** BnDiv()
// This function divides two bigNum values. The function returns FALSE if
// there is an error in the operation.
LIB_EXPORT BOOL
BnDiv(
    bigNum               quotient,
    bigNum               remainder,
    bigConst             dividend,
    bigConst             divisor
    )
{
    OSSL_ENTER();
    BIG_INITIALIZED(bnQ, quotient);
    BIG_INITIALIZED(bnR, remainder);
    BIG_INITIALIZED(bnDend, dividend);
    BIG_INITIALIZED(bnSor, divisor);
    BOOL        OK;
    pAssert(!BnEqualZero(divisor));
    if(BnGetSize(dividend) < BnGetSize(divisor))
    {
        if(quotient)
            BnSetWord(quotient, 0);
        if(remainder)
            BnCopy(remainder, dividend);
        OK = TRUE;
    }
    else
    {
        pAssert((quotient == NULL)
                || (quotient->allocated >= (unsigned)(dividend->size 
                                                      - divisor->size)));
        pAssert((remainder == NULL)
                || (remainder->allocated >= divisor->size));
        OK = BN_div(bnQ, bnR, bnDend, bnSor, CTX);
        if(OK)
        {
            OsslToTpmBn(quotient, bnQ);
            OsslToTpmBn(remainder, bnR);
        }
    }
    DEBUG_PRINT("In BnDiv:\n");
    BIGNUM_PRINT("   bnDividend: ", bnDend, TRUE);
    BIGNUM_PRINT("    bnDivisor: ", bnSor, TRUE);
    BIGNUM_PRINT("   bnQuotient: ", bnQ, TRUE);
    BIGNUM_PRINT("  bnRemainder: ", bnR, TRUE);
    OSSL_LEAVE();
    return OK;
}

#if     ALG_RSA
//*** BnGcd()
// Get the greatest common divisor of two numbers
LIB_EXPORT BOOL
BnGcd(
    bigNum      gcd,            // OUT: the common divisor
    bigConst    number1,        // IN:
    bigConst    number2         // IN:
    )
{
    OSSL_ENTER();
    BIG_INITIALIZED(bnGcd, gcd);
    BIG_INITIALIZED(bn1, number1);
    BIG_INITIALIZED(bn2, number2);
    BOOL            OK;
    pAssert(gcd != NULL);
    OK = BN_gcd(bnGcd, bn1, bn2, CTX);
    if(OK)
    {
        OsslToTpmBn(gcd, bnGcd);
        gcd->size = bnGcd->top;
    }
    OSSL_LEAVE();
    return OK;
}

//***BnModExp()
// Do modular exponentiation using bigNum values. The conversion from a bignum_t to
// a bigNum is trivial as they are based on the same structure
LIB_EXPORT BOOL
BnModExp(
    bigNum               result,         // OUT: the result
    bigConst             number,         // IN: number to exponentiate
    bigConst             exponent,       // IN:
    bigConst             modulus         // IN:
    )
{
    OSSL_ENTER();
    BIG_INITIALIZED(bnResult, result);
    BIG_INITIALIZED(bnN, number);
    BIG_INITIALIZED(bnE, exponent);
    BIG_INITIALIZED(bnM, modulus);
    BOOL            OK;
//
    OK = BN_mod_exp(bnResult, bnN, bnE, bnM, CTX);
    if(OK)
    {
        OsslToTpmBn(result, bnResult);
    }
    OSSL_LEAVE();
    return OK;
}

//*** BnModInverse()
// Modular multiplicative inverse
LIB_EXPORT BOOL
BnModInverse(
    bigNum               result,
    bigConst             number,
    bigConst             modulus
    )
{
    OSSL_ENTER();
    BIG_INITIALIZED(bnResult, result);
    BIG_INITIALIZED(bnN, number);
    BIG_INITIALIZED(bnM, modulus);
    BOOL                OK;

    OK = (BN_mod_inverse(bnResult, bnN, bnM, CTX) != NULL);
    if(OK)
    {
        OsslToTpmBn(result, bnResult);
    }
    OSSL_LEAVE();
    return OK;
}
#endif // ALG_RSA

#if     ALG_ECC

//*** PointFromOssl()
// Function to copy the point result from an OSSL function to a bigNum
static BOOL
PointFromOssl(
    bigPoint         pOut,      // OUT: resulting point
    EC_POINT        *pIn,       // IN: the point to return
    bigCurve         E          // IN: the curve
    )
{
    BIGNUM         *x = NULL;
    BIGNUM         *y = NULL;
    BOOL            OK;
    BN_CTX_start(E->CTX);
//
    x = BN_CTX_get(E->CTX);
    y = BN_CTX_get(E->CTX);

    if(y == NULL)
        FAIL(FATAL_ERROR_ALLOCATION);
    // If this returns false, then the point is at infinity
    OK = EC_POINT_get_affine_coordinates_GFp(E->G, pIn, x, y, E->CTX);
    if(OK)
    {
        OsslToTpmBn(pOut->x, x);
        OsslToTpmBn(pOut->y, y);
        BnSetWord(pOut->z, 1);
    }
    else
        BnSetWord(pOut->z, 0);
    BN_CTX_end(E->CTX);
    return OK;
}

//*** EcPointInitialized()
// Allocate and initialize a point.
static EC_POINT *
EcPointInitialized(
    pointConst          initializer,
    bigCurve            E
    )
{
    BIG_INITIALIZED(bnX, (initializer != NULL) ? initializer->x : NULL);
    BIG_INITIALIZED(bnY, (initializer != NULL) ? initializer->y : NULL);

    EC_POINT            *P = (initializer != NULL && E != NULL) 
                                ? EC_POINT_new(E->G) : NULL;
    pAssert(E != NULL);
    if(P != NULL)
        EC_POINT_set_affine_coordinates_GFp(E->G, P, bnX, bnY, E->CTX);
    return P;
}

//*** BnCurveInitialize()
// This function initializes the OpenSSL group definition
//
// It is a fatal error if 'groupContext' is not provided.
// return type: bigCurve *
//      NULL        the TPM_ECC_CURVE is not valid
//      non-NULL    points to a structure in 'groupContext'
bigCurve
BnCurveInitialize(
    bigCurve          E,           // IN: curve structure to initialize
    TPM_ECC_CURVE     curveId      // IN: curve identifier
    )
{
    EC_GROUP                *group = NULL;
    EC_POINT                *P = NULL;
    const ECC_CURVE_DATA    *C = GetCurveData(curveId);
    BN_CTX                  *CTX = NULL;

    BIG_INITIALIZED(bnP, C != NULL ? C->prime : NULL);
    BIG_INITIALIZED(bnA, C != NULL ? C->a : NULL);
    BIG_INITIALIZED(bnB, C != NULL ? C->b : NULL);
    BIG_INITIALIZED(bnX, C != NULL ? C->base.x : NULL);
    BIG_INITIALIZED(bnY, C != NULL ? C->base.y : NULL);
    BIG_INITIALIZED(bnN, C != NULL ? C->order : NULL);
    BIG_INITIALIZED(bnH, C != NULL ? C->h : NULL);
    int                      OK = (C != NULL);
//
    OK = OK && ((CTX = OsslContextEnter()) != NULL);

    // initialize EC group, associate a generator point and initialize the point
    // from the parameter data
    // Create a group structure
    OK = OK && (group = EC_GROUP_new_curve_GFp(bnP, bnA, bnB, CTX)) != NULL;

    // Allocate a point in the group that will be used in setting the
    // generator. This is not needed after the generator is set.
    OK = OK && ((P = EC_POINT_new(group)) != NULL);
    // Need to use this in case Montgomery method is being used
    OK = OK
        && EC_POINT_set_affine_coordinates_GFp(group, P, bnX, bnY, CTX);
    // Now set the generator
    OK = OK && EC_GROUP_set_generator(group, P, bnN, bnH);

    if(P != NULL)
        EC_POINT_free(P);

    if(!OK && group != NULL)
    {
        EC_GROUP_free(group);
        group = NULL;
    }
    if(!OK && CTX != NULL)
    {
        OsslContextLeave(CTX);
        CTX = NULL;
    }

    E->G = group;
    E->CTX = CTX;
    E->C = C;

    return OK ? E : NULL;
}

//*** BnEccModMult()
// This function does a point multiply of the form R = [d]S
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL
BnEccModMult(
    bigPoint             R,         // OUT: computed point
    pointConst           S,         // IN: point to multiply by 'd' (optional)
    bigConst             d,         // IN: scalar for [d]S
    bigCurve             E
    )
{
    EC_POINT            *pR = EC_POINT_new(E->G);
    EC_POINT            *pS = EcPointInitialized(S, E);
    BIG_INITIALIZED(bnD, d);

    if(S == NULL)
        EC_POINT_mul(E->G, pR, bnD, NULL, NULL, E->CTX);
    else
        EC_POINT_mul(E->G, pR, NULL, pS, bnD, E->CTX);
    PointFromOssl(R, pR, E);
    EC_POINT_free(pR);
    EC_POINT_free(pS);
    return !BnEqualZero(R->z);
}

//*** BnEccModMult2()
// This function does a point multiply of the form R = [d]G + [u]Q
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL
BnEccModMult2(
    bigPoint             R,         // OUT: computed point
    pointConst           S,         // IN: optional point
    bigConst             d,         // IN: scalar for [d]S or [d]G
    pointConst           Q,         // IN: second point
    bigConst             u,         // IN: second scalar
    bigCurve             E          // IN: curve
    )
{
    EC_POINT            *pR = EC_POINT_new(E->G);
    EC_POINT            *pS = EcPointInitialized(S, E);
    BIG_INITIALIZED(bnD, d);
    EC_POINT            *pQ = EcPointInitialized(Q, E);
    BIG_INITIALIZED(bnU, u);

    if(S == NULL || S == (pointConst)&(AccessCurveData(E)->base))
        EC_POINT_mul(E->G, pR, bnD, pQ, bnU, E->CTX);
    else
    {
        const EC_POINT        *points[2];
        const BIGNUM          *scalars[2];
        points[0] = pS;
        points[1] = pQ;
        scalars[0] = bnD;
        scalars[1] = bnU;
        EC_POINTs_mul(E->G, pR, NULL, 2, points, scalars, E->CTX);
    }
    PointFromOssl(R, pR, E);
    EC_POINT_free(pR);
    EC_POINT_free(pS);
    EC_POINT_free(pQ);
    return !BnEqualZero(R->z);
}

//** BnEccAdd()
// This function does addition of two points.
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL
BnEccAdd(
    bigPoint             R,         // OUT: computed point
    pointConst           S,         // IN: point to multiply by 'd'
    pointConst           Q,         // IN: second point
    bigCurve             E          // IN: curve
    )
{
    EC_POINT            *pR = EC_POINT_new(E->G);
    EC_POINT            *pS = EcPointInitialized(S, E);
    EC_POINT            *pQ = EcPointInitialized(Q, E);
//
    EC_POINT_add(E->G, pR, pS, pQ, E->CTX);

    PointFromOssl(R, pR, E);
    EC_POINT_free(pR);
    EC_POINT_free(pS);
    EC_POINT_free(pQ);
    return !BnEqualZero(R->z);
}

#endif // ALG_ECC

#endif // MATHLIB OSSL