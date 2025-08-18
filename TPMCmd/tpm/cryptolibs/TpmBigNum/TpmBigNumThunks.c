//** Introduction
// This file contains BN Thunks between the MathInterfaceLibrary types and the
// bignum_t types.

#include "TpmBigNum.h"

// Note - these were moved out of TPM_INLINE to build correctly on GCC.  On MSVC
// link time code generation correctly handles the inline versions, but
// it isn't portable to GCC.

// ***************************************************************************
// Library Level Functions
// ***************************************************************************

// Called when system is initializing to allow math libraries to perform
// startup actions.
LIB_EXPORT int ExtMath_LibInit(void)
{
    return BnSupportLibInit();
}

#if LIBRARY_COMPATIBILITY_CHECK
//** MathLibraryCompatibililtyCheck()
// This function is only used during development to make sure that the library
// that is being referenced is using the same size of data structures as the TPM.
LIB_EXPORT BOOL ExtMath_Debug_CompatibilityCheck(void)
{
    return BnMathLibraryCompatibilityCheck();
}
#endif

// ***************************************************************************
// Integer/Number Functions (non-ECC)
// ***************************************************************************
// #################
// type initializers
// #################
LIB_EXPORT Crypt_Int* ExtMath_Initialize_Int(Crypt_Int* var, NUMBYTES bitCount)
{
    return (Crypt_Int*)BnInit((bigNum)var, BN_STRUCT_ALLOCATION(bitCount));
}

// #################
// Buffer Converters
// #################
LIB_EXPORT Crypt_Int* ExtMath_IntFromBytes(
    Crypt_Int* buffer, const BYTE* input, NUMBYTES byteCount)
{
    return (Crypt_Int*)BnFromBytes((bigNum)buffer, input, byteCount);
}

LIB_EXPORT BOOL ExtMath_IntToBytes(
    const Crypt_Int* value, BYTE* output, NUMBYTES* pByteCount)
{
    return BnToBytes((bigConst)value, output, pByteCount);
}

LIB_EXPORT Crypt_Int* ExtMath_SetWord(Crypt_Int* n, crypt_uword_t w)
{
    return (Crypt_Int*)BnSetWord((bigNum)n, w);
}
// #################
// Copy Functions
// #################
LIB_EXPORT BOOL ExtMath_Copy(Crypt_Int* out, const Crypt_Int* in)
{
    return BnCopy((bigNum)out, (bigConst)in);
}

// ###############################
// Ordinary Arithmetic, writ large
// ###############################

//** ExtMath_Multiply()
// Multiplies two numbers and returns the result
LIB_EXPORT BOOL ExtMath_Multiply(
    Crypt_Int* result, const Crypt_Int* multiplicand, const Crypt_Int* multiplier)
{
    return BnMult((bigNum)result, (bigConst)multiplicand, (bigConst)multiplier);
}

//** ExtMath_Divide()
// This function divides two Crypt_Int* values. The function returns FALSE if there is
// an error in the operation. Quotient may be null, in which case this function returns
// only the remainder.
LIB_EXPORT BOOL ExtMath_Divide(Crypt_Int*       quotient,
                               Crypt_Int*       remainder,
                               const Crypt_Int* dividend,
                               const Crypt_Int* divisor)
{
    return BnDiv(
        (bigNum)quotient, (bigNum)remainder, (bigConst)dividend, (bigConst)divisor);
}

#if ALG_RSA
//** ExtMath_GCD()
// Get the greatest common divisor of two numbers. This function is only needed
// when the TPM implements RSA.
LIB_EXPORT BOOL ExtMath_GCD(
    Crypt_Int* gcd, const Crypt_Int* number1, const Crypt_Int* number2)
{
    return BnGcd((bigNum)gcd, (bigConst)number1, (bigConst)number2);
}
#endif  // ALG_RSA

//*** ExtMath_Add()
// This function adds two Crypt_Int* values. This function always returns TRUE.
LIB_EXPORT BOOL ExtMath_Add(
    Crypt_Int* result, const Crypt_Int* op1, const Crypt_Int* op2)
{
    return BnAdd((bigNum)result, (bigConst)op1, (bigConst)op2);
}

//*** ExtMath_AddWord()
// This function adds a word value to a Crypt_Int*. This function always returns TRUE.
LIB_EXPORT BOOL ExtMath_AddWord(
    Crypt_Int* result, const Crypt_Int* op, crypt_uword_t word)
{
    return BnAddWord((bigNum)result, (bigConst)op, word);
}

//*** ExtMath_Subtract()
// This function does subtraction of two Crypt_Int* values and returns result = op1 - op2
// when op1 is greater than op2. If op2 is greater than op1, then a fault is
// generated. This function always returns TRUE.
LIB_EXPORT BOOL ExtMath_Subtract(
    Crypt_Int* result, const Crypt_Int* op1, const Crypt_Int* op2)
{
    return BnSub((bigNum)result, (bigConst)op1, (bigConst)op2);
}

//*** ExtMath_SubtractWord()
// This function subtracts a word value from a Crypt_Int*. This function always
// returns TRUE.
LIB_EXPORT BOOL ExtMath_SubtractWord(
    Crypt_Int* result, const Crypt_Int* op, crypt_uword_t word)
{
    return BnSubWord((bigNum)result, (bigConst)op, word);
}

// ###############################
// Modular Arithmetic, writ large
// ###############################
// define Mod in terms of Divide
LIB_EXPORT BOOL ExtMath_Mod(Crypt_Int* valueAndResult, const Crypt_Int* modulus)
{
    return ExtMath_Divide(NULL, valueAndResult, valueAndResult, modulus);
}

//** ExtMath_ModMult()
// Does 'op1' * 'op2' and divide by 'modulus' returning the remainder of the divide.
LIB_EXPORT BOOL ExtMath_ModMult(Crypt_Int*       result,
                                const Crypt_Int* op1,
                                const Crypt_Int* op2,
                                const Crypt_Int* modulus)
{
    return BnModMult((bigNum)result, (bigConst)op1, (bigConst)op2, (bigConst)modulus);
}

#if ALG_RSA
//** ExtMath_ModExp()
// Do modular exponentiation using Crypt_Int* values. This function is only needed
// when the TPM implements RSA.
LIB_EXPORT BOOL ExtMath_ModExp(Crypt_Int*       result,
                               const Crypt_Int* number,
                               const Crypt_Int* exponent,
                               const Crypt_Int* modulus)
{
    return BnModExp(
        (bigNum)result, (bigConst)number, (bigConst)exponent, (bigConst)modulus);
}
#endif  // ALG_RSA

//** ExtMath_ModInverse()
// Modular multiplicative inverse.
LIB_EXPORT BOOL ExtMath_ModInverse(
    Crypt_Int* result, const Crypt_Int* number, const Crypt_Int* modulus)
{
    return BnModInverse((bigNum)result, (bigConst)number, (bigConst)modulus);
}

//*** ExtMath_ModWord()
// This function does modular division of a big number when the modulus is a
// word value.
LIB_EXPORT crypt_word_t ExtMath_ModWord(const Crypt_Int* numerator,
                                        crypt_word_t     modulus)
{
    return BnModWord((bigConst)numerator, modulus);
}

// ###############################
// Queries
// ###############################

//*** ExtMath_UnsignedCmp()
// This function performs a comparison of op1 to op2. The compare is approximately
// constant time if the size of the values used in the compare is consistent
// across calls (from the same line in the calling code).
//  Return Type: int
//      < 0             op1 is less than op2
//      0               op1 is equal to op2
//      > 0             op1 is greater than op2
LIB_EXPORT int ExtMath_UnsignedCmp(const Crypt_Int* op1, const Crypt_Int* op2)
{
    return BnUnsignedCmp((bigConst)op1, (bigConst)op2);
}

//*** ExtMath_UnsignedCmpWord()
// Compare a Crypt_Int* to a crypt_uword_t.
//  Return Type: int
//      -1              op1 is less that word
//      0               op1 is equal to word
//      1               op1 is greater than word
LIB_EXPORT int ExtMath_UnsignedCmpWord(const Crypt_Int* op1, crypt_uword_t word)
{
    return BnUnsignedCmpWord((bigConst)op1, word);
}

LIB_EXPORT BOOL ExtMath_IsEqualWord(const Crypt_Int* bn, crypt_uword_t word)
{
    return BnEqualWord((bigConst)bn, word);
}

LIB_EXPORT BOOL ExtMath_IsZero(const Crypt_Int* op1)
{
    return BnEqualZero((bigConst)op1);
}

//*** ExtMath_MostSigBitNum()
// This function returns the number of the MSb of a Crypt_Int* value.
//  Return Type: int
//      -1              the word was zero or 'bn' was NULL
//      n               the bit number of the most significant bit in the word
LIB_EXPORT int ExtMath_MostSigBitNum(const Crypt_Int* bn)
{
    return BnMsb((bigConst)bn);
}

LIB_EXPORT uint32_t ExtMath_GetLeastSignificant32bits(const Crypt_Int* bn)
{
    MUST_BE(RADIX_BITS >= 32);
#if RADIX_BITS == 32
    return BnGetWord(bn, 0);
#else
    // RADIX_BITS must be > 32 by MUST_BE above.
    return (uint32_t)(BnGetWord(bn, 0) & 0xFFFFFFFF);
#endif
}

//*** ExtMath_SizeInBits()
// This function returns the number of bits required to hold a number. It is one
// greater than the Msb.
LIB_EXPORT unsigned ExtMath_SizeInBits(const Crypt_Int* n)
{
    return BnSizeInBits((bigConst)n);
}

// ###############################
// Bitwise Operations
// ###############################

LIB_EXPORT BOOL ExtMath_SetBit(Crypt_Int* bn, unsigned int bitNum)
{
    return BnSetBit((bigNum)bn, bitNum);
}

// This function is used to check to see if a bit is SET in a bigNum_t. The 0th bit
//*** ExtMath_TestBit()
// is the LSb of d[0].
//  Return Type: BOOL
//      TRUE(1)         the bit is set
//      FALSE(0)        the bit is not set or the number is out of range
LIB_EXPORT BOOL ExtMath_TestBit(Crypt_Int*   bn,     // IN: number to check
                                unsigned int bitNum  // IN: bit to test
)
{
    return BnTestBit((bigNum)bn, bitNum);
}

//***ExtMath_MaskBits()
// This function is used to mask off high order bits of a big number.
// The returned value will have no more than 'maskBit' bits
// set.
// Note: There is a requirement that unused words of a bigNum_t are set to zero.
//  Return Type: BOOL
//      TRUE(1)         result masked
//      FALSE(0)        the input was not as large as the mask
LIB_EXPORT BOOL ExtMath_MaskBits(
    Crypt_Int*    bn,      // IN/OUT: number to mask
    crypt_uword_t maskBit  // IN: the bit number for the mask.
)
{
    return BnMaskBits((bigNum)bn, maskBit);
}

//*** ExtMath_ShiftRight()
// This function will shift a Crypt_Int* to the right by the shiftAmount.
// This function always returns TRUE.
LIB_EXPORT BOOL ExtMath_ShiftRight(
    Crypt_Int* result, const Crypt_Int* toShift, uint32_t shiftAmount)
{
    return BnShiftRight((bigNum)result, (bigConst)toShift, shiftAmount);
}

// ***************************************************************************
// ECC Functions
// ***************************************************************************
// ##################
// Point initializers
// ##################
LIB_EXPORT Crypt_Point* ExtEcc_Initialize_Point(Crypt_Point* point, NUMBYTES bitCount)
{
    // Since we define the structure, we know that BN_POINT_BUFs are a bn_point_t followed by bignums.
    // and that the size is always the MAX_ECC_KEY_SIZE
    // tell the individual bignums how large they are:
    bn_fullpoint_t* pBuf = (bn_fullpoint_t*)point;
    BnInit((bigNum) & (pBuf->x), BN_STRUCT_ALLOCATION(bitCount));
    BnInit((bigNum) & (pBuf->y), BN_STRUCT_ALLOCATION(bitCount));
    BnInit((bigNum) & (pBuf->z), BN_STRUCT_ALLOCATION(bitCount));

    // now feed the addresses of those coordinates to the bn_point_t structure
    bn_point_t* bnPoint = (bn_point_t*)point;
    BnInitializePoint(
        bnPoint, (bigNum) & (pBuf->x), (bigNum) & (pBuf->y), (bigNum) & (pBuf->z));
    return point;
}

// ##################
// Curve initializers
// ##################
LIB_EXPORT const Crypt_EccCurve* ExtEcc_CurveInitialize(Crypt_EccCurve* E,
                                                        TPM_ECC_CURVE   curveId)
{
    return BnCurveInitialize((bigCurveData*)E, curveId);
}

// #################
// Curve DESTRUCTOR
// #################
// WARNING: Not guaranteed to be called in presence of LONGJMP.
LIB_EXPORT void ExtEcc_CurveFree(const Crypt_EccCurve* E)
{
    BnCurveFree((bigCurveData*)E);
}

// #################
// Buffer Converters
// #################
//*** BnPointFromBytes()
// Function to create a BIG_POINT structure from a 2B point.
// A point is going to be two ECC values in the same buffer. The values are going
// to be the size of the modulus.  They are in modular form.
LIB_EXPORT Crypt_Point* ExtEcc_PointFromBytes(Crypt_Point* point,
                                              const BYTE*  x,
                                              NUMBYTES     nBytesX,
                                              const BYTE*  y,
                                              NUMBYTES     nBytesY)
{
    return (Crypt_Point*)BnPointFromBytes((bigPoint)point, x, nBytesX, y, nBytesY);
}

LIB_EXPORT BOOL ExtEcc_PointToBytes(
    const Crypt_Point* point, BYTE* x, NUMBYTES* pBytesX, BYTE* y, NUMBYTES* pBytesY)
{
    return BnPointToBytes((pointConst)point, x, pBytesX, y, pBytesY);
}

// ####################
// ECC Point Operations
// ####################
//** ExtEcc_PointMultiply()
// This function does a point multiply of the form R = [d]S. A return of FALSE
// indicates that the result was the point at infinity. This function is only needed
// if the TPM supports ECC.
LIB_EXPORT BOOL ExtEcc_PointMultiply(
    Crypt_Point* R, const Crypt_Point* S, const Crypt_Int* d, const Crypt_EccCurve* E)
{
    return BnEccModMult((bigPoint)R, (pointConst)S, (bigConst)d, (bigCurveData*)E);
}

//** ExtEcc_PointMultiplyAndAdd()
// This function does a point multiply of the form R = [d]S + [u]Q. A return of
// FALSE indicates that the result was the point at infinity. This function is only
// needed if the TPM supports ECC.
LIB_EXPORT BOOL ExtEcc_PointMultiplyAndAdd(Crypt_Point*          R,
                                           const Crypt_Point*    S,
                                           const Crypt_Int*      d,
                                           const Crypt_Point*    Q,
                                           const Crypt_Int*      u,
                                           const Crypt_EccCurve* E)
{
    return BnEccModMult2((bigPoint)R,
                         (pointConst)S,
                         (bigConst)d,
                         (pointConst)Q,
                         (bigConst)u,
                         (bigCurveData*)E);
}

LIB_EXPORT BOOL ExtEcc_PointAdd(Crypt_Point*          R,
                                const Crypt_Point*    S,
                                const Crypt_Point*    Q,
                                const Crypt_EccCurve* E)
{
    return BnEccAdd((bigPoint)R, (pointConst)S, (pointConst)Q, (bigCurveData*)E);
}

// #####################
// ECC Point Information
// #####################
LIB_EXPORT BOOL ExtEcc_IsPointOnCurve(const Crypt_Point* Q, const Crypt_EccCurve* E)
{
    return BnIsPointOnCurve((pointConst)Q, AccessCurveConstants(E));
}

LIB_EXPORT const Crypt_Int* ExtEcc_PointX(const Crypt_Point* point)
{
    return (const Crypt_Int*)(((pointConst)point)->x);
}

LIB_EXPORT BOOL ExtEcc_IsInfinityPoint(const Crypt_Point* point)
{
    return BnEqualZero(((pointConst)point)->z);
}

// #####################
// ECC Curve Information
// #####################
LIB_EXPORT const Crypt_Int* ExtEcc_CurveGetPrime(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGetPrime(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGetOrder(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGetOrder(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGetCofactor(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGetCofactor(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGet_a(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGet_a(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGet_b(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGet_b(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Point* ExtEcc_CurveGetG(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Point*)BnCurveGetG(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGetGx(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGetGx(BnGetCurveData(curveId));
}

LIB_EXPORT const Crypt_Int* ExtEcc_CurveGetGy(TPM_ECC_CURVE curveId)
{
    return (const Crypt_Int*)BnCurveGetGy(BnGetCurveData(curveId));
}

LIB_EXPORT TPM_ECC_CURVE ExtEcc_CurveGetCurveId(const Crypt_EccCurve* E)
{
    return BnCurveGetCurveId(AccessCurveConstants(E));
}
