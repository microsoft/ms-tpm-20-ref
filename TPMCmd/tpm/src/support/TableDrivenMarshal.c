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

#include <assert.h> 

#include "Tpm.h"
#include "Marshal.h"
#include "TableMarshal.h"

#if TABLE_DRIVEN_MARSHAL

extern ArrayMarshal_mst ArrayLookupTable[];

extern UINT16 MarshalLookupTable[];

typedef struct { int a; } External_Structure_t;

extern struct Exernal_Structure_t MarshalData;

#define IS_SUCCESS(UNMARSHAL_FUNCTION)                                              \
    (TPM_RC_SUCCESS == (result = (UNMARSHAL_FUNCTION)))

marshalIndex_t IntegerDispatch[] = {
    UINT8_MARSHAL_REF, UINT16_MARSHAL_REF, UINT32_MARSHAL_REF, UINT64_MARSHAL_REF,
     INT8_MARSHAL_REF,  INT16_MARSHAL_REF,  INT32_MARSHAL_REF,  INT64_MARSHAL_REF
};


#if 1
#define GetDescriptor(reference)                                                    \
    ((MarshalHeader_mst *)(((BYTE *)(&MarshalData)) + (reference & NULL_MASK)))
#else
static const MarshalHeader_mst *GetDescriptor(marshalIndex_t index)
{
    const MarshalHeader_mst    *mst = MarshalLookupTable[index & NULL_MASK];
    return mst;
}
#endif

#define GetUnionDescriptor(_index_)                                                 \
    ((UnionMarshal_mst *)GetDescriptor(_index_))
#define GetArrayDescriptor(_index_)                                                 \
    ((ArrayMarshal_mst *))ArrayLookupTable[_index_ & NULL_MASK])

//*** GetUnmarshaledInteger()
// Gets the unmarshaled value and normalizes it to a UIN32 for other 
// processing (comparisons and such).
static UINT32 GetUnmarshaledInteger(marshalIndex_t type, const void *target)
{
    int     size = (type & SIZE_MASK);
//
    if(size == FOUR_BYTES)
        return *((UINT32 *)target);
    if(type & IS_SIGNED)
    {
        if(size == TWO_BYTES)
            return (UINT32)*((int16_t *)target);
        return (UINT32)*((int8_t *)target);
    }
    if(size == TWO_BYTES)
        return (UINT32)*((UINT16 *)target);
    return (UINT32)*((UINT8 *)target);
}

static UINT32 GetSelector(void *structure, const UINT16 *values, 
                            UINT16 descriptor)
{
    uint                 sel = GET_ELEMENT_NUMBER(descriptor);
    // Get the offset of the value in the unmarshaled structure
    const UINT16        *entry = &values[(sel * 3)];
//
    return GetUnmarshaledInteger(GET_ELEMENT_SIZE(entry[0]), 
                        ((UINT8 *)structure) + entry[2]);
}

static TPM_RC UnmarshalBytes(UINT8 *target, int count, UINT8 **buffer, INT32 *size)
{
    if((*size -= count) >= 0)
    {
        memcpy(target, *buffer, count);
        *buffer += count;
        return TPM_RC_SUCCESS;
    }
    return TPM_RC_INSUFFICIENT;
}

//*** MarshalBytes()
// Marshal an array of bytes.
static UINT16 MarshalBytes(UINT8 *source, UINT8 **buffer, INT32 *size, int32_t count)
{
    if(buffer != NULL)
    {
        if(size != NULL && (size -= count) < 0)
            return 0;
        memcpy(*buffer, source, count);
        *buffer += count;
    }
    return (UINT16)count;
}

//*** ArrayUnmarshal()
// Unmarshal an array. The 'index' is of the form: 'type'_ARRAY_MARSHAL_INDEX.
static TPM_RC ArrayUnmarshal(UINT16 index, UINT8 *target, 
                           UINT8 **buffer, INT32 *size, UINT32 count)
{
    marshalIndex_t       which = ArrayLookupTable[index & NULL_MASK].type;
    UINT16               stride = ArrayLookupTable[index & NULL_MASK].stride;
    TPM_RC               result;
//
    if(stride == 1) // A byte array
        result = UnmarshalBytes(target, count, buffer, size);
    else
    {
        which |= index & NULL_FLAG;
        for(result = TPM_RC_SUCCESS; count > 0; target += stride, count--)
            if(!IS_SUCCESS(Unmarshal(which, target, buffer, size)))
                break;
    }
    return result;
}

//*** ArrayMarshal()
static UINT16 ArrayMarshal(UINT16 index, UINT8 *source,
                      UINT8 **buffer, INT32 *size, UINT32 count)
{
    marshalIndex_t      which = ArrayLookupTable[index & NULL_MASK].type;
    UINT16              stride = ArrayLookupTable[index & NULL_MASK].stride;
    UINT16              retVal;
//
    if(stride == 1) // A byte array
        return MarshalBytes(source, buffer, size, count);
    which |= index & NULL_FLAG;
    for(retVal = 0
        ; count > 0
        ; source += stride, count--)
        retVal += Marshal(which, source, buffer, size);

    return retVal;
}

//***UnmarshalUnion()
TPM_RC
UnmarshalUnion(
    UINT16               typeIndex,         // IN: the thing to unmarshal
    void                *target,            // IN: were the data goes to
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size,              // IN/OUT: the remaining size
    UINT32               selector
)
{
    int                  i;
    UnionMarshal_mst    *ut = GetUnionDescriptor(typeIndex);
    marshalIndex_t       selected;
//
    for(i = 0; i < ut->countOfselectors; i++)
    {
        if(selector == ut->selectors[i])
        {
            UINT8           *offset = ((UINT8 *)ut) + ut->offsetOfUnmarshalTypes;
            // Get the selected thing to unmarshal
            selected = ((marshalIndex_t *)offset)[i];
            if(ut->modifiers & IS_ARRAY_UNION)
                return UnmarshalBytes(target, selected, buffer, size);
            else
            {
                // Propagate NULL_FLAG if the null flag was
                // propagated to the structure containing the union
                selected |= (typeIndex & NULL_FLAG);
                return Unmarshal(selected, target, buffer, size);
            }
        }
    }
    // Didn't find the value.
    return TPM_RC_SELECTOR;
}

//*** MarshalUnion()
UINT16
MarshalUnion(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *source,            // IN: were the data comes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size,              // IN/OUT: the remaining size
    UINT32               selector           // IN: the union selector
)
{
    int                  i;
    UnionMarshal_mst    *ut = GetUnionDescriptor(typeIndex);
    marshalIndex_t       selected;
//
    for(i = 0; i < ut->countOfselectors; i++)
    {
        if(selector == ut->selectors[i])
        {
            UINT8           *offset = ((UINT8 *)ut) + ut->offsetOfUnmarshalTypes;
            // Get the selected thing to unmarshal
            selected = ((marshalIndex_t *)offset)[i];
            if(ut->modifiers & IS_ARRAY_UNION)
                return MarshalBytes(source, buffer, size, selected);
            else
                return Marshal(selected, source, buffer, size);
        }
    }
    if(size != NULL)
        *size = -1;
    return 0;
}

TPM_RC
UnmarshalInteger(
    int                  iSize, 
    void                *target, 
    UINT8               **buffer, 
    INT32               *size, 
    UINT32              *value
)
{
    int              bytes = (1 << (iSize & SIZE_MASK));
    if((*size -= bytes) >= 0)
    {
#define mb (*buffer)
        if(bytes == 4)
        {
            *((UINT32 *)target) = (UINT32)((((((mb[0] << 8) | mb[1]) << 8)
                                           | mb[2]) << 8) | mb[3]);
            *value = *((UINT32 *)target);
        }
        else if(bytes == 2)
        {
            *((UINT16 *)target) = (UINT16)((mb[0] << 8) | mb[1]);
            if(iSize & IS_SIGNED)
                *value = (UINT32)(*((INT16 *)target));
            else
                *value = (UINT32)(*((UINT16 *)target));
        }
        else if(bytes == 1)
        {
            *((UINT8*)target) = (UINT8)mb[0];
            if(iSize & IS_SIGNED)
                *value = (UINT32)(*((INT8 *)target));
            else
                *value = (UINT32)(*((UINT8 *)target));
        }
        else
        {
            *((UINT64 *)target) = (((UINT64)BYTE_ARRAY_TO_UINT32(mb)) << 32)
                + BYTE_ARRAY_TO_UINT32(&mb[4]);
        }
        *buffer += bytes;
        return TPM_RC_SUCCESS;
#undef mb
    }
    return TPM_RC_INSUFFICIENT;
}

//*** Unmarshal()
// This is the function that performs unmarshaling of different numbered types. Each
// TPM type has a number. The number is used to lookup the address of the data 
// structure that describes how to unmarshal that data type.
TPM_RC 
Unmarshal(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *target,            // IN: were the data goes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size               // IN/OUT: the remaining size
    )
{
    const MarshalHeader_mst     *sel;
    TPM_RC                       result;
//
#define _target    ((UINT8 *)target)
    sel = GetDescriptor(typeIndex);
    switch(sel->marshalType)
    {
        case UINT_MTYPE:
        {
            UINT32          dummy;
            return UnmarshalInteger(sel->modifiers, target, 
                                      buffer, size, &dummy);
        }
        case VALUES_MTYPE:
        {
            // This is the general-purpose structure that can handle things like
            // TPMI_DH_PARENT that has multiple ranges, multiple singles and a
            // 'null' value. When things cover a large range with holes in the range
            // they can be turned into multiple ranges.
            // Unmarshal the base type 
            UINT32                   val;
            if(IS_SUCCESS(UnmarshalInteger(sel->modifiers, target, 
                                           buffer, size, &val)))
            {
                ValuesMarshal_mst   *vmt = ((ValuesMarshal_mst *)sel);
                const UINT32        *check = vmt->values;
                if((vmt->modifiers & TAKES_NULL) && (val == *check++))
                {
                    if((typeIndex & NULL_FLAG) == 0)
                        result = (TPM_RC)(sel->errorCode);
                }
                else
                {
                    int               i;
                    for(i = vmt->ranges - 1; i >= 0; check = &check[2], i--)
                        if((UINT32)(val - check[0]) <= check[1])
                            break;
                    if(i < 0)
                    {
                        for(i = vmt->singles - 1; i >= 0; i--)
                            if(val == check[i])
                                break;
                    }
                    if(i < 0)
                        result = (TPM_RC)(sel->errorCode);
                }
            }
            break;
        }
        case TABLE_MTYPE:
        {
            UINT32                  val;
            // This is a table with or without bit checking. The bits will be 
            // conditionally set by the compiler if some feature is implemented.
            // When a value is matched in the list, the bit field can be checked to
            // see if the feature is implemented. This is useful for things like
            // key sizes where there sizes are optionally implemented.
            // Unmarshal the base type 
            if(IS_SUCCESS(UnmarshalInteger(sel->modifiers, target, 
                                            buffer, size, &val)))
            {
                TableMarshal_mst    *tmt = ((TableMarshal_mst *)sel);
                const UINT32        *check = tmt->values;
                if((tmt->modifiers & TAKES_NULL) && (val == *check++))
                {
                    if((typeIndex & NULL_FLAG) == 0)
                        result = (TPM_RC)(sel->errorCode);
                }
                else
                {
                    int               i;
                    for(i = tmt->singles - 1; i >= 0; i--)
                    {
                        if(val == check[i])
                        {
                            if((HAS_BITS & tmt->modifiers)
                               && (!IS_BIT_SET32(i, &(check[tmt->singles]))))
                                i = -1;
                            break;
                        }
                    }
                    if(i < 0)
                        result = (TPM_RC)(sel->errorCode);
                }
            }
            break;
        }
        case MIN_MAX_MTYPE:
        {

            UINT32               val;
            // A min-max has a range. It can have a bit-field that is indexed to the
            // min value (something that matches min has a bit at 0. This is useful 
            // for algorithms. The min-max define a range of algorithms to be checked
            // and the bit field can check to see if the algorithm in that range is 
            // allowed. 
            if(IS_SUCCESS(UnmarshalInteger(sel->modifiers, target, 
                                           buffer, size, &val)))
            {
                MinMaxMarshal_mst   *mmt = (MinMaxMarshal_mst *)sel;
                const UINT32        *check = mmt->values;
            //
                if((mmt->modifiers & TAKES_NULL) && (val == *check++))
                {
                    if((typeIndex & NULL_FLAG) == 0)
                        result = (TPM_RC)(mmt->errorCode);
                }
                else
                {
                    val -= *check;
                    if((val > check[1]) 
                       || ((mmt->modifiers & HAS_BITS) && 
                           !IS_BIT_SET32(val, &check[2])))
                        result = (TPM_RC)(mmt->errorCode);
                }
            }
            break;
        }
        case ATTRIBUTES_MTYPE:
        {
            //  This is used for TPMA values.
            UINT32                   mask;
            AttributesMarshal_mst   *amt = (AttributesMarshal_mst *)sel;
        //
            if(IS_SUCCESS(UnmarshalInteger(sel->modifiers, target, 
                                    buffer, size, &mask)))
            {
                if((mask & amt->attributeMask) != 0)
                    result = TPM_RC_RESERVED_BITS;
            }
            break;
        }
        case STRUCTURE_MTYPE:
        {
            // A structure (not a union). A structure has elements (one defined per
            // row). Three UINT16 values are used for each row. The first indicates
            // the type of the entry. They choices are: simple, union, or array. A
            // simple type can be a simple integer or another structure. It can also
            // be a specific "interface type." For example, when a structure entry is
            // a value that is used define the dimension of an array, the entry of 
            // the structure will reference a "synthetic" interface type, most often
            // a min-max value. If the type of the entry is union or array, then the
            // first value indicates which of the previous elements provides the union
            // selector or the array dimension. That previous entry is referenced in
            // the unmarshaled structure in memory (Not the marshaled buffer). The
            // previous entry indicates the location in the structure of the value. 
            // The second entry of each structure entry indicated the index of the 
            // type associated with the entry. This is an index into the array of
            // arrays or the union table (merged with the normal table in this 
            // implementation). The final entry is the offset in the unmarshaled 
            // structure where the value is located. This is the offsetof(STRUcTURE, 
            // element). This value is added to the input 'target' or 'source' value
            // to determine where the value goes.
            StructMarshal_mst   *mst = (StructMarshal_mst *)sel;
            int                  i;
            const UINT16        *value;
        //
            for(result = TPM_RC_SUCCESS, value = mst->values,  i = mst->elements
                ; (TPM_RC_SUCCESS == result) && (i > 0)
                ; value = &value[3], i--)
            {
                UINT16           descriptor = value[0];
                marshalIndex_t   index = value[1];
                UINT8           *offset = _target + value[2];
            //
                index |= ((ELEMENT_PROPAGATE & descriptor) 
                            << (NULL_SHIFT - PROPAGATE_SHIFT));
                switch(GET_ELEMENT_TYPE(descriptor))
                {
                    case SIMPLE_STYPE:
                    {
                        result = Unmarshal(index, offset, buffer, size);
                        break;
                    }
                    case UNION_STYPE:
                    {
                        UINT32               choice;
                    //
                        // Get the selector or array dimension value
                        choice = GetSelector(target, mst->values, descriptor);
                        result = UnmarshalUnion(index, offset, buffer, size, choice);
                        break;
                    }
                    case ARRAY_STYPE:
                    {
                        UINT32            dimension;
                    //
                        dimension = GetSelector(target, mst->values, descriptor);
                        result = ArrayUnmarshal(index, offset, buffer, 
                                                size, dimension);
                        break;
                    }
                    default:
                        result = TPM_RC_FAILURE;
                        break;
                }
            }
            break;
        }
        case TPM2B_MTYPE:
        {
            // A primitive TPM2B. A size and byte buffer. The single value (other than
            // the tag) references the synthetic 'interface' value for the size
            // parameter.
            Tpm2bMarshal_mst        *m2bt = (Tpm2bMarshal_mst *)sel;
            if(IS_SUCCESS(Unmarshal(m2bt->sizeIndex, target, buffer, size)))
                result = UnmarshalBytes(((TPM2B *)target)->buffer, 
                               *((UINT16 *)target), buffer, size);
            break;
        }
        case TPM2BS_MTYPE:
        {
            // This is used when a TPM2B contains a structure. 
            Tpm2bsMarshal_mst   *m2bst = (Tpm2bsMarshal_mst *)sel;
            INT32          count;
        //
            if(IS_SUCCESS(Unmarshal(m2bst->sizeIndex, target, buffer, size)))
            {
                count = (int32_t)*((UINT16 *)_target);
                if(count == 0)
                {
                    if(m2bst->modifiers & SIZE_EQUAL)
                        result = TPM_RC_SIZE;
                }
                else if((*size -= count) >= 0)
                {
                    marshalIndex_t  index = m2bst->dataIndex;
                //
                    index |= (m2bst->modifiers & PROPAGATE_NULL) 
                                    << (NULL_SHIFT - PROPAGATE_SHIFT);
                    if(IS_SUCCESS(Unmarshal(index,
                                           _target + (m2bst->modifiers & SIGNED_MASK), 
                                           buffer, &count)))
                    {
                        if(count != 0)
                            result = TPM_RC_SIZE;
                    }
                }
                else
                    result = TPM_RC_INSUFFICIENT;
            }
            break;
        }
        case LIST_MTYPE:
        {
            // Used for a list. A list is a qualified 32-bit 'count' value followed
            // by a type indicator.
            ListMarshal_mst     *mlt = (ListMarshal_mst *)sel;
            marshalIndex_t      index = mlt->arrayRef;
        //
            if(IS_SUCCESS(Unmarshal(mlt->sizeIndex, target, buffer, size)))
            {
                index |= (mlt->modifiers & PROPAGATE_NULL)
                            << (NULL_SHIFT - PROPAGATE_SHIFT);
                result = ArrayUnmarshal(index, 
                                        _target +(mlt->modifiers & SIGNED_MASK), 
                                        buffer, size,
                                        *((UINT32 *)target));
            }
            break;
        }
        case NULL_MTYPE:
            result = TPM_RC_SUCCESS;
            break;
        default:
        {
            result = TPM_RC_FAILURE;
            break;
        }
    }
    return result;
}

//*** Marshal()
// This is the function that drives marshaling of output. Because there is no 
// validation of the output, there is a lot less code.
UINT16 Marshal(
    UINT16               typeIndex,         // IN: the thing to marshal
    void                *source,            // IN: were the data comes from
    UINT8               **buffer,           // IN/OUT: the data source buffer
    INT32               *size               // IN/OUT: the remaining size
    )
{
#define _source  ((UINT8 *)source)

    const MarshalHeader_mst     *sel;
    UINT16                       retVal;
//
    sel = GetDescriptor(typeIndex);
    switch(sel->marshalType)
    {
        case VALUES_MTYPE:
        case UINT_MTYPE:
        case TABLE_MTYPE:
        case MIN_MAX_MTYPE:
        case ATTRIBUTES_MTYPE:
        {
#if BIG_ENDIAN_TPM
#define MM16    0
#define MM32    0
#define MM64    0
#else
// These flip the constant index values so that they count in reverse order when doing
// little-endian stuff
#define MM16    1
#define MM32    3
#define MM64    7
#endif
// Just change the name and cast the type of the input parameters for typing purposes
#define mb (*buffer)
#define _source ((UINT8 *)source)
            retVal = (1 << (sel->modifiers & SIZE_MASK));
            if(buffer != NULL)
            {
                if((size == NULL) || ((*size -= retVal) >= 0))
                {
                    if(retVal == 4)
                    {
                        mb[0 ^ MM32] = _source[0];
                        mb[1 ^ MM32] = _source[1];
                        mb[2 ^ MM32] = _source[2];
                        mb[3 ^ MM32] = _source[3];
                    }
                    else if(retVal == 2)
                    {
                        mb[0 ^ MM16] = _source[0];
                        mb[1 ^ MM16] = _source[1];
                    }
                    else if(retVal == 1)
                        mb[0] = _source[0];
                    else
                    {
                        mb[0 ^ MM64] = _source[0];
                        mb[1 ^ MM64] = _source[1];
                        mb[2 ^ MM64] = _source[2];
                        mb[3 ^ MM64] = _source[3];
                        mb[4 ^ MM64] = _source[4];
                        mb[5 ^ MM64] = _source[5];
                        mb[6 ^ MM64] = _source[6];
                        mb[7 ^ MM64] = _source[7];
                    }
                    *buffer += retVal;
                }
            }
            break;
        }
        case STRUCTURE_MTYPE:
        {
//#define _mst  ((StructMarshal_mst *)sel)
            StructMarshal_mst *mst = ((StructMarshal_mst *)sel);
            int              i;
            const UINT16  *value = mst->values;

        //
            for(retVal = 0, i = mst->elements; i > 0; value = &value[3], i--)
            {
                UINT16           des = value[0];
                marshalIndex_t   index = value[1];
                UINT8           *offset = _source + value[2];
            //
                switch(GET_ELEMENT_TYPE(des))
                {
                    case UNION_STYPE:
                    {
                        UINT32           choice; 
                    //
                        choice = GetSelector(source, mst->values, des);
                        retVal += MarshalUnion(index, offset, buffer, size, choice);
                        break;
                    }
                    case ARRAY_STYPE:
                    {
                        UINT32               count;
                    //
                        count = GetSelector(source, mst->values, des);
                        retVal += ArrayMarshal(index, offset, buffer, size, count);
                        break;
                    }
                    case SIMPLE_STYPE:
                    default:
                    {
                        // This is either another structure or a simple type
                        retVal += Marshal(index, offset, buffer, size);
                        break;
                    }
                }
            }
            break;
        }
        case TPM2B_MTYPE:
        {
            // Get the number of bytes being marshaled
            INT32         val = (int32_t)*((UINT16 *)source);
        //
            retVal = Marshal(UINT16_MARSHAL_REF, source, buffer, size);

            // This is a standard 2B with a byte buffer
            retVal += MarshalBytes(((TPM2B *)_source)->buffer, buffer, size, val);
            break;
        }
        case TPM2BS_MTYPE: // A structure in a TPM2B
        {
            Tpm2bsMarshal_mst       *m2bst = (Tpm2bsMarshal_mst *)sel;
            UINT8                   *offset;
            UINT16                   amount;
            UINT8                   *marshaledSize;
        //
            // Save the address of where the size should go
            marshaledSize = *buffer;

            // marshal the size (checks the space and advanced the pointer)
            retVal = Marshal(UINT16_MARSHAL_REF, source, buffer, size);

            // This gets the offsetof the structure to marshal. It was placed in the
            // modifiers byte because the offset from the start of the TPM2B to the
            // start of the structure is going to be less than 8 and the modifiers
            // byte isn't needed for anything else.
            offset = _source + (m2bst->modifiers & SIGNED_MASK);

            // Marshal the structure and get its size
            amount = Marshal(m2bst->dataIndex, offset, buffer, size);

            // put the size in the space used when the size was marshaled.
            if(buffer != NULL)
                UINT16_TO_BYTE_ARRAY(amount, marshaledSize);
            retVal += amount;
            break;
        }
        case LIST_MTYPE:
        {
            ListMarshal_mst *    mlt = ((ListMarshal_mst *)sel);
            UINT8               *offset = _source + (mlt->modifiers & SIGNED_MASK);
            retVal = Marshal(UINT32_MARSHAL_REF, source, buffer, size);
            retVal += ArrayMarshal((marshalIndex_t)(mlt->arrayRef), offset, 
                                   buffer, size, *((UINT32 *)source));
            break;
        }
        case NULL_MTYPE:
            retVal = 0;
            break;
       case ERROR_MTYPE:
       default:
        {
            if(size != NULL)
               *size = -1;
            retVal = 0;
            break;
        }
    }
    return retVal;

}

#endif // TABLE_DRIVEN_MARSHAL

//
