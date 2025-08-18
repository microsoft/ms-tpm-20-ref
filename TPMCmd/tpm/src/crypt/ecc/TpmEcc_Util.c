//** Introduction
// This file contains utility functions to help using the external Math library
// for Ecc functions.
#include "Tpm.h"
#include "TpmEcc_Util_fp.h"

#if ALG_ECC

//***
// TpmEcc_PointFrom2B() Function to create a Crypt_Point structure from a 2B
// point. The target point is expected to have memory allocated and
// uninitialized. A TPMS_ECC_POINT is going to be two ECC values in the same
// buffer. The values are going to be the size of the modulus. They are in
// modular form.
//
// NOTE: This function considers both parameters optional because of use
// cases where points may not be specified in the calling function. If the
// initializer or point buffer is NULL, then NULL is returned. As a result, the
// only error detection when the initializer value is invalid is to return NULL
// in that error case as well. If a caller wants to handle that error case
// differently, then the caller must perform the correct validation before/after
// this function.
LIB_EXPORT Crypt_Point* TpmEcc_PointFrom2B(
    Crypt_Point*    ecP,  // OUT: the preallocated point structure
    TPMS_ECC_POINT* p     // IN: the number to convert
)
{
    if(p == NULL)
        return NULL;

    if(ecP != NULL)
    {
        return ExtEcc_PointFromBytes(
            ecP, p->x.t.buffer, p->x.t.size, p->y.t.buffer, p->y.t.size);
    }
    return ecP;  // will return NULL if ecP is NULL.
}

//*** TpmEcc_PointTo2B()
// This function converts a BIG_POINT into a TPMS_ECC_POINT. A TPMS_ECC_POINT
// contains two TPM2B_ECC_PARAMETER values. The maximum size of the parameters
// is dependent on the maximum EC key size used in an implementation.
// The presumption is that the TPMS_ECC_POINT is large enough to hold 2 TPM2B
// values, each as large as a MAX_ECC_PARAMETER_BYTES
LIB_EXPORT BOOL TpmEcc_PointTo2B(
    TPMS_ECC_POINT*       p,    // OUT: the converted 2B structure
    const Crypt_Point*    ecP,  // IN: the values to be converted
    const Crypt_EccCurve* E     // IN: curve descriptor for the point
)
{
    pAssert(p && ecP && E);
    TPM_ECC_CURVE curveId = ExtEcc_CurveGetCurveId(E);
    NUMBYTES      size    = CryptEccGetKeySizeForCurve(curveId);
    size                  = (UINT16)BITS_TO_BYTES(size);
    MemorySet(p, 0, sizeof(*p));
    p->x.t.size = size;
    p->y.t.size = size;
    return ExtEcc_PointToBytes(
        ecP, p->x.t.buffer, &p->x.t.size, p->y.t.buffer, &p->y.t.size);
}

#endif  // ALG_ECC
