// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/datatype.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
#ifndef __Ili_Compat_Datatype_H
#define __Ili_Compat_Datatype_H

#include <ilviews/dataccess/datatype.h>

#ifdef ILICOMPAT_20
#  define IliObjectDatatype IliPointerTypeClass
#endif

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDatatype IliDatatype
#define IlvSwNullType IliNullType
#define IlvSwStringType IliStringType
#define IlvSwLongStringType IliLongStringType
#define IlvSwBooleanType IliBooleanType
#define IlvSwByteType IliByteType
#define IlvSwIntegerType IliIntegerType
#define IlvSwFloatType IliFloatType
#define IlvSwDoubleType IliDoubleType
#define IlvSwDecimalType IliDecimalType
#define IlvSwDateType IliDateType
#define IlvSwTimeType IliTimeType
#define IlvSwBinaryType IliBinaryType
#define IlvSwLongBinaryType IliLongBinaryType
#define IlvSwAnyType IliAnyType
#define IlvSwDatatypeType IliDatatypeType
#define IlvSwBitmapType IliBitmapType
#define IlvSwNTS IliNTS
#define IlvSwByte IliByte
#define IlvSwValueRecord IliValueRecord
#define IlvSwBinary IliBinary
#define IlvSwDatatypeReader IliDatatypeReader
#define IlvSwDatatypeCallback IliDatatypeCallback
#define IlvSwDatatypePtr IliDatatypePtr
#define IlvSwDatatypeCollection IliDatatypeCollection
#define IlvSwObjectDatatype IliPointerTypeClass
#define IlvSwStructuredTypeClass IliStructuredTypeClass
#define IlvSwTableTypeClass IliTableTypeClass
#define IlvSwObjectTypeClass IliObjectTypeClass
#define IlvSwBinaryTypeClass IliBinaryTypeClass
#define IlvSwReferenceTypeClass IliReferenceTypeClass
#define IlvSwDatatypeTypeClass IliDatatypeTypeClass
#endif

#endif




