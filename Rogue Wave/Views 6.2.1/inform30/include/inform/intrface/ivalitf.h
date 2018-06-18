// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/intrface/ivalitf.h
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
#ifndef __Ili_Compat_Ivalitf_H
#define __Ili_Compat_Ivalitf_H

#include <ilviews/dataccess/intrface/ivalitf.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwJsUtil           IliJsUtil
#define IlvSwEnumDescr        IliEnumDescr
#define IlvSwDeclareEnumEx    IliDeclareEnumEx
#define IlvSwDeclareEnum      IliDeclareEnum
#define IlvSwDefineEnum       IliDefineEnum
#define IlvSwNmReturn         IliNmReturn
#define IlvSwTAG              IliTAG
#define IlvSwENDTAG           IliENDTAG
#define IlvSwVAR_VALNAME      IliVAR_VALNAME
#define IlvSwDECLARE_VALNAME  IliDECLARE_VALNAME
#define IlvSwDECLARE_ACCESSOR IliDECLARE_ACCESSOR
#define IlvSwGUARD_VAL        IliGUARD_VAL
#define IlvSwGUARD_GETDESCR   IliGUARD_GETDESCR
#define IlvSwGUARD_QUERYVAL   IliGUARD_QUERYVAL
#define IlvSwGUARD_APPLYVAL   IliGUARD_APPLYVAL
#define IlvSwRefCountedValueInterface IliRefCountedValueInterface
#define IlvSwClassItf IliClassItf
#define IlvSwValueVariantTypeClass IliValueVariantTypeClass
#define IlvSwValueVariantType IliValueVariantType
#define IlvSwITFDYNCAST IliITFDYNCAST
#define IlvSwValueItf IliValueItf
#define IlvSwDecimalItf IliDecimalItf
#define IlvSwDataAccessItf IliDataAccessItf
#define IlvSwObserverItf IliObserverItf
#define IlvSwObserverClassItf IliObserverClassItf
#define IlvSwValueEnumTypeClass IliValueEnumTypeClass
#endif

#endif



