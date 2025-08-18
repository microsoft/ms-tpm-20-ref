//** Introduction

// This file contains the definitions needed for defining the internal bigNum
// structure.

// A bigNum is a pointer to a structure. The structure has three fields. The
// last field is and array (d) of crypt_uword_t. Each word is in machine format
// (big- or little-endian) with the words in ascending significance (i.e. words
// in little-endian order). This is the order that seems to be used in every
// big number library in the worlds, so...
//
// The first field in the structure (allocated) is the number of words in 'd'.
// This is the upper limit on the size of the number that can be held in the
// structure. This differs from libraries like OpenSSL as this is not intended
// to deal with numbers of arbitrary size; just numbers that are needed to deal
// with the algorithms that are defined in the TPM implementation.
//
// The second field in the structure (size) is the number of significant words
// in 'n'. When this number is zero, the number is zero. The word at used-1 should
// never be zero. All words between d[size] and d[allocated-1] should be zero.

//** Defines

#ifndef _BN_NUMBERS_H
#define _BN_NUMBERS_H
// TODO_RENAME_INC_FOLDER:private refers to the TPM_CoreLib private headers
#include <public/TpmAlgorithmDefines.h>
#include <public/GpMacros.h>  // required for TpmFail_fp.h
#include <public/Capabilities.h>
#include <public/TpmTypes.h>  // requires capabilities & GpMacros

// These are the basic big number formats. This is convertible to the library-
// specific format without too much difficulty. For the math performed using
// these numbers, the value is always positive.
#define BN_STRUCT_DEF(struct_type, count) \
    struct st_##struct_type##_t           \
    {                                     \
        crypt_uword_t allocated;          \
        crypt_uword_t size;               \
        crypt_uword_t d[count];           \
    }

typedef BN_STRUCT_DEF(bnroot, 1) bignum_t;

#ifndef bigNum
typedef bignum_t*       bigNum;
typedef const bignum_t* bigConst;
#endif  //bigNum

extern const bignum_t BnConstZero;

// The Functions to access the properties of a big number.
// Get number of allocated words
#define BnGetAllocated(x) (unsigned)((x)->allocated)

// Get number of words used
#define BnGetSize(x) ((x)->size)

// Get a pointer to the data array
#define BnGetArray(x) ((crypt_uword_t*)&((x)->d[0]))

// Get the nth word of a bigNum (zero-based)
#define BnGetWord(x, i) (crypt_uword_t)((x)->d[i])

// Some things that are done often.

// Test to see if a bignum_t is equal to zero
#define BnEqualZero(bn) (BnGetSize(bn) == 0)

// Test to see if a bignum_t is equal to a word type
#define BnEqualWord(bn, word) \
    ((BnGetSize(bn) == 1) && (BnGetWord(bn, 0) == (crypt_uword_t)word))

// Determine if a bigNum is even. A zero is even. Although the
// indication that a number is zero is that its size is zero,
// all words of the number are 0 so this test works on zero.
#define BnIsEven(n) ((BnGetWord(n, 0) & 1) == 0)

// The macros below are used to define bigNum values of the required
// size. The values are allocated on the stack so they can be
// treated like simple local values.

// This will call the initialization function for a defined bignum_t.
// This sets the allocated and used fields and clears the words of 'n'.
#define BN_INIT(name) \
    (bigNum) BnInit((bigNum) & (name), BYTES_TO_CRYPT_WORDS(sizeof(name.d)))

#define CRYPT_WORDS(bytes) BYTES_TO_CRYPT_WORDS(bytes)
#define MIN_ALLOC(bytes)   (CRYPT_WORDS(bytes) < 1 ? 1 : CRYPT_WORDS(bytes))
#define BN_CONST(name, bytes, initializer) \
    typedef const struct name##_type       \
    {                                      \
        crypt_uword_t allocated;           \
        crypt_uword_t size;                \
        crypt_uword_t d[MIN_ALLOC(bytes)]; \
    } name##_type;                         \
    name##_type name = {MIN_ALLOC(bytes), CRYPT_WORDS(bytes), {initializer}};

#define BN_STRUCT_ALLOCATION(bits) (BITS_TO_CRYPT_WORDS(bits) + 1)

// Create a structure of the correct size.
#define BN_STRUCT(struct_type, bits) \
    BN_STRUCT_DEF(struct_type, BN_STRUCT_ALLOCATION(bits))

// Define a bigNum type with a specific allocation
#define BN_TYPE(name, bits) typedef BN_STRUCT(name, bits) bn_##name##_t

// This creates a local bigNum variable of a specific size and
// initializes it from a TPM2B input parameter.
#define BN_INITIALIZED(name, bits, initializer) \
    BN_STRUCT(name, bits) name##_;              \
    bigNum name = TpmMath_IntFrom2B(BN_INIT(name##_), (const TPM2B*)initializer)

// Create a local variable that can hold a number with 'bits'
#define BN_VAR(name, bits)         \
    BN_STRUCT(name, bits) _##name; \
    bigNum name = BN_INIT(_##name)

// Create a type that can hold the largest number defined by the
// implementation.
#define BN_MAX(name) BN_VAR(name, LARGEST_NUMBER_BITS)
#define BN_MAX_INITIALIZED(name, initializer) \
    BN_INITIALIZED(name, LARGEST_NUMBER_BITS, initializer)

// A word size value is useful
#define BN_WORD(name) BN_VAR(name, RADIX_BITS)

// This is used to create a word-size bigNum and initialize it with
// an input parameter to a function.
#define BN_WORD_INITIALIZED(name, initial) \
    BN_STRUCT(name, RADIX_BITS) name##_;         \
    bigNum name = BnInitializeWord(        \
        (bigNum) & name##_, BN_STRUCT_ALLOCATION(RADIX_BITS), initial)

// ECC-Specific Values

// This is the format for a point. It is always in affine format. The Z value is
// carried as part of the point, primarily to simplify the interface to the support
// library. Rather than have the interface layer have to create space for the
// point each time it is used...
// The x, y, and z values are pointers to bigNum values and not in-line versions of
// the numbers. This is a relic of the days when there was no standard TPM format
// for the numbers
typedef struct _bn_point_t
{
    bigNum x;
    bigNum y;
    bigNum z;
} bn_point_t;

typedef bn_point_t*       bigPoint;
typedef const bn_point_t* pointConst;

typedef struct constant_point_t
{
    bigConst x;
    bigConst y;
    bigConst z;
} constant_point_t;

// coords points into x,y,z
// a bigPoint is a pointer to one of these structures, and
// therefore a pointer to bn_point_t (a coords).
// so bigPoint->coords->x->size is the size of x, and
// all 3 components are the same size.
#define BN_POINT_BUF(typename, bits)                 \
    struct bnpt_st_##typename##_t                    \
    {                                                \
        bn_point_t coords;                           \
        BN_STRUCT(typename##_x, MAX_ECC_KEY_BITS) x; \
        BN_STRUCT(typename##_y, MAX_ECC_KEY_BITS) y; \
        BN_STRUCT(typename##_z, MAX_ECC_KEY_BITS) z; \
    }

typedef BN_POINT_BUF(fullpoint, MAX_ECC_KEY_BITS) bn_fullpoint_t;

// TPMBN_ECC_CURVE_CONSTANTS
// =========================
// A cryptographic elliptic curve is a mathematical set (Group) of points that
// satisfy the group equation and are generated by linear multiples of some
// initial "generator" point (Gx,Gy).
//
// The TPM code supports ECC Curves that satisfy equations of the following
// form:
//
// (y^2 = x^3 + a*x + b) mod p
//
// A particular cryptographic curve is fully described by the following
// parameters:
//
// | Name    | Meaning                                                                             |
// | :------ | :---------------------------------------------------------------------------------- |
// | p       | curve prime                                                                         |
// | a, b    | equation coefficients                                                               |
// | (Gx,Gy) | X and Y coordinates of the generator point.                                         |
// | n       | the order (size) of the generated group.  n must be prime.                          |
// | h       | the cofactor of the group size to the full set of points for a particular equation. |
//
// The group of constants to describe a particular ECC Curve (such as NIST P256
// or P384) are contained in TPMBN_ECC_CURVE_CONSTANTS objects.  In the
// TpmBigNum library these constants are always stored in TPM's internal BN
// (bigNum) format.
//
// Other math libraries are expected to provide these as compile time constants
// in a format they can efficiently consume at runtime.

// Structure for the curve parameters. This is an analog to the
// TPMS_ALGORITHM_DETAIL_ECC
typedef struct
{
    TPM_ECC_CURVE    curveId;  // TPM Algorithm ID for this data
    bigConst         prime;    // a prime number
    bigConst         order;    // the order of the curve
    bigConst         h;        // cofactor
    bigConst         a;        // linear coefficient
    bigConst         b;        // constant term
    constant_point_t base;     // base point
} TPMBN_ECC_CURVE_CONSTANTS;

// Access macros for the TPMBN_ECC_CURVE_CONSTANTS structure. The parameter 'C' is a pointer
// to an TPMBN_ECC_CURVE_CONSTANTS structure. In some libraries, the curve structure E contains
// a pointer to an TPMBN_ECC_CURVE_CONSTANTS structure as well as some other bits. For those
// cases, the AccessCurveConstants function is used in the code to first get the pointer
// to the TPMBN_ECC_CURVE_CONSTANTS for access. In some cases, the function does nothing.
// AccessCurveConstants and these functions are all defined as inline so they can be optimized
// away in cases where they are no-ops.
TPM_INLINE bigConst BnCurveGetPrime(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->prime;
}
TPM_INLINE bigConst BnCurveGetOrder(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->order;
}
TPM_INLINE bigConst BnCurveGetCofactor(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->h;
}
TPM_INLINE bigConst BnCurveGet_a(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->a;
}
TPM_INLINE bigConst BnCurveGet_b(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->b;
}
TPM_INLINE pointConst BnCurveGetG(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return (pointConst) & (C->base);
}
TPM_INLINE bigConst BnCurveGetGx(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->base.x;
}
TPM_INLINE bigConst BnCurveGetGy(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->base.y;
}
TPM_INLINE TPM_ECC_CURVE BnCurveGetCurveId(const TPMBN_ECC_CURVE_CONSTANTS* C)
{
    return C->curveId;
}

// Convert bytes in initializers
// This is used for CryptEccData.c.
#define BIG_ENDIAN_BYTES_TO_UINT32(a, b, c, d) \
    (((UINT32)(a) << 24) + ((UINT32)(b) << 16) + ((UINT32)(c) << 8) + ((UINT32)(d)))

#define BIG_ENDIAN_BYTES_TO_UINT64(a, b, c, d, e, f, g, h)             \
    (((UINT64)(a) << 56) + ((UINT64)(b) << 48) + ((UINT64)(c) << 40)   \
     + ((UINT64)(d) << 32) + ((UINT64)(e) << 24) + ((UINT64)(f) << 16) \
     + ((UINT64)(g) << 8) + ((UINT64)(h)))

// These macros are used for data initialization of big number ECC constants
// These two macros combine a macro for data definition with a macro for
// structure initialization. The 'a' parameter is a macro that gives numbers to
// each of the bytes of the initializer and defines where each of the numberd
// bytes will show up in the final structure. The 'b' value is a structure that
// contains the requisite number of bytes in big endian order. S, the MJOIN
// and JOIND macros will combine a macro defining a data layout with a macro defining
// the data to be places. Generally, these macros will only need expansion when
// CryptEccData.c gets compiled.
#define JOINED(a, b) a b
#define MJOIN(a, b)  a b

#if RADIX_BYTES == 64
#  define B8_TO_BN(a, b, c, d, e, f, g, h)                                  \
      ((((((((((((((((UINT64)a) << 8) | (UINT64)b) << 8) | (UINT64)c) << 8) \
               | (UINT64)d)                                                 \
              << 8)                                                         \
             | (UINT64)e)                                                   \
            << 8)                                                           \
           | (UINT64)f)                                                     \
          << 8)                                                             \
         | (UINT64)g)                                                       \
        << 8)                                                               \
       | (UINT64)h)
#  define B1_TO_BN(a)                   B8_TO_BN(0, 0, 0, 0, 0, 0, 0, a)
#  define B2_TO_BN(a, b)                B8_TO_BN(0, 0, 0, 0, 0, 0, a, b)
#  define B3_TO_BN(a, b, c)             B8_TO_BN(0, 0, 0, 0, 0, a, b, c)
#  define B4_TO_BN(a, b, c, d)          B8_TO_BN(0, 0, 0, 0, a, b, c, d)
#  define B5_TO_BN(a, b, c, d, e)       B8_TO_BN(0, 0, 0, a, b, c, d, e)
#  define B6_TO_BN(a, b, c, d, e, f)    B8_TO_BN(0, 0, a, b, c, d, e, f)
#  define B7_TO_BN(a, b, c, d, e, f, g) B8_TO_BN(0, a, b, c, d, e, f, g)
#else
#  define B1_TO_BN(a)       B4_TO_BN(0, 0, 0, a)
#  define B2_TO_BN(a, b)    B4_TO_BN(0, 0, a, b)
#  define B3_TO_BN(a, b, c) B4_TO_BN(0, a, b, c)
#  define B4_TO_BN(a, b, c, d) \
      (((((((UINT32)a << 8) | (UINT32)b) << 8) | (UINT32)c) << 8) | (UINT32)d)
#  define B5_TO_BN(a, b, c, d, e)          B4_TO_BN(b, c, d, e), B1_TO_BN(a)
#  define B6_TO_BN(a, b, c, d, e, f)       B4_TO_BN(c, d, e, f), B2_TO_BN(a, b)
#  define B7_TO_BN(a, b, c, d, e, f, g)    B4_TO_BN(d, e, f, g), B3_TO_BN(a, b, c)
#  define B8_TO_BN(a, b, c, d, e, f, g, h) B4_TO_BN(e, f, g, h), B4_TO_BN(a, b, c, d)

#endif

#endif  // _BN_NUMBERS_H