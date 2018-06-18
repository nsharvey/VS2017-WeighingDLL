// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/macros.h
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
// General purpose macro definitions for Rogue Wave Views Layout
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Macros_H
#define __Ilv_Layout_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif /* __Ilv_Macros_H */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvlayout.lib")
#endif

#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif /* __Ilv_Itf_Value_H */

#if defined(ILVGRLLIB)
#define ILVGRLEXPORTED ILVBASEEXPORTED
#define ILVGRLEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVGRLEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVGRLLIB */
#define ILVGRLEXPORTED ILVBASEIMPORTED
#define ILVGRLEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVGRLEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVGRLLIB */

#define IlvDECLAREINITGRLCLASS(m) IL_MODULEINIT(m, ILVGRLEXPORTED);
#define ILVGRLMODULEINIT(m)	IL_MODULEINIT(m, ILVGRLEXPORTED);

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvLayoutValueInterface : public IlvValueInterface
{
public:
    IlvDeclareLazyClassInfo();
};

// --------------------------------------------------------------------------
#define IlvLayoutVersion 100

// --------------------------------------------------------------------------
#define IlvDefineLazyLayoutClassInfo(classname, symbol) \
ILVPREDEFINECLASSINFOMEMBERS(classname);		\
IlvDefineLazyClassInfo(classname, symbol)

#define IlvLayoutPostRegisterClassWithoutAcc(classname, superclass) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
	IlvValuedClassInfo::Create(#classname,			\
				   &superclass::_classinfo,	\
				   0))

#define IlvLayoutPostRegisterClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
	IlvValuedClassInfo::Create(#classname,			\
				   &superclass::_classinfo,	\
				   classname::GetAccessors))

#endif /* !__Ilv_Layout_Macros_H */
