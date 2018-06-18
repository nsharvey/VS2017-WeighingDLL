// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/genbase.h
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
// Declaration of automatic inspector classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Genbase_H)
#define __IlvSt_Inspectors_Genbase_H

// --------------------------------------------------------------------------
// Includes

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_String_H)
#  include <ilviews/base/string.h>
#endif
#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif

class ILVDSPEXPORTED IlArray;

#if defined(ILVSTLIB)
#define ILVINSPEXPORTEDDEF	    ILVBASEEXPORTED
#define ILVINSPEXPORTEDFUNC(type)   ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVINSPEXPORTEDDEF	    ILVBASEIMPORTED
#define ILVINSPEXPORTEDFUNC(type)   ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVINSPCLASS		    ILVINSPEXPORTEDDEF
#define ILVINSPEXPORTEDVAR(type)    ILVINSPEXPORTEDDEF type
#define IlvDECLAREINITINSPCLASS(m)  IL_MODULEINIT(m, ILVINSPCLASS);

// --------------------------------------------------------------------------
// String macros
#define ILVI_VALID_STRING(str) (str ? str : IlString::EmptyCString)

#if !defined( __Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif

// --------------------------------------------------------------------------
// Macros used to define an IlvStObject derived class

#define IlvDeclareInspClassInfo() \
    IlvDeclareClassInfo();        \
    IlvStDeclareDownCasting()

#define IlvStInspClassInfoValue(classname, superclass) \
IlvClassInfo::Create(#classname,  &superclass::_classinfo)

// -----------------------------------
#if defined(IlvDECLAREINITCLASS)
#define IlvStInspPreRegisterRootClass(classname)                        \
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }    \
IlAny classname::downCast(const IlvClassInfo* classInfo)                \
    { return (classInfo == classname::ClassInfo() ? (IlAny)this : 0); } \
const IlAny classname::downCast(const IlvClassInfo* classInfo) const    \
    { return (classInfo == classname::ClassInfo() ? (IlAny)this : 0); } \
IlvClassInfo* classname::_classinfo = 0

#define IlvStInspPreRegisterClass(classname, superclass)	     \
IlvStDefineCast(classname, superclass)                               \
IlvClassInfo* classname::getClassInfo() const { return _classinfo; } \
IlvClassInfo* classname::_classinfo = 0

#define IlvStInspPreRegisterAbstractClass(classname, superclass)     \
IlvStDefineCast(classname, superclass)                               \
IlvClassInfo* classname::getClassInfo() const { return _classinfo; } \
IlvClassInfo* classname::_classinfo = 0

#define ILV_INSP_DEFINEINITCLASS(mod, exp) ILVDEFINEINITCLASS(mod, exp)
#define IlvStInspPreRegisterSymbol(symb, value) IlSymbol* symb = 0
#define IlvStInspPostRegisterSymbol(symb, value) symb = IlGetSymbol(value)

#define IlvStInspRegisterRootClass(classname) \
classname::_classinfo = IlvClassInfo::Create(#classname,  0)

#define IlvStInspRegisterClass(classname, superclass) \
classname::_classinfo = IlvStInspClassInfoValue(classname, superclass)

#else // !IlvDECLAREINITCLASS
#define IlvStInspPreRegisterRootClass(classname)		       \
IlAny classname::downCast(const IlvClassInfo* classInfo)               \
    { return (classInfo == classname::ClassInfo()? (IlAny)this : 0); } \
const IlAny classname::downCast(const IlvClassInfo* classInfo) const   \
    { return (classInfo == classname::ClassInfo()? (IlAny)this : 0); } \
IlvClassInfo* classname::_classinfo = IlvClassInfo::Create(#classname,  0)

#define IlvStInspPreRegisterClass(classname, superclass) \
IlvStDefineCast(classname, superclass)                   \
IlvClassInfo* classname::_classinfo =                    \
  IlvStInspClassInfoValue(classname, superclass)

#define IlvStInspPreRegisterAbstractClass(classname, superclass) \
IlvStDefineCast(classname, superclass)                           \
IlvClassInfo* classname::_classinfo =                            \
  IlvStInspClassInfoValue(classname, superclass)

#define ILV_INSP_DEFINEINITCLASS(mod, exp) exp
#define IlvStInspPreRegisterSymbol(symb, value) \
IlSymbol* symb = IlGetSymbol(value)
#define IlvStInspPostRegisterSymbol(symb, value)

#define IlvStInspRegisterClass(classname, superclass)
#define IlvStInspRegisterRootClass(classname)

#endif // IlvDECLAREINITCLASS

#define IlvRegisterInspAbstractClass(classname, superclass) \
ILVDEFINECLASSINFOMEMBERS(classname,			    \
IlvClassInfo::Create(#classname, superclass::ClassInfo())); \
IlvStDefineCast(classname, superclass)


#define IlvPostRegisterInspClass(classname, superclass)	      \
ILVPOSTDEFINECLASSINFOMEMBERS(classname,		      \
		IlvClassInfo::Create(#classname,              \
				     superclass::ClassInfo()))

#define IlvPreRegisterInspClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname);   \
IlvStDefineCast(classname, superclass)

#define IlvPreRegisterInspAbstractClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname);           \
IlvStDefineCast(classname, superclass)

#define ILVI_DOWNCAST(classname, obj) \
((classname*)IlvStObject::DownCast(classname::ClassInfo(), obj))
#define ILVI_CONSTDOWNCAST(classname, obj) \
((const classname*)IlvStObject::ConstDownCast(classname::ClassInfo(), obj))

// --------------------------------------------------------------------------
// Scaning memory leaks / already deleted objects
// --------------------------------------------------------------------------
#ifdef ILVALLOCCHECK
#define ILVI_NEW new(__FILE__, __LINE__)
#define ILVI_DELETE(x) IlvStObject::Delete(__FILE__, __LINE__, x)
#define ILVI_ASSERTVALID(x) IlvStObject::IsValid(x)
#define ILVI_ASSERTVALID_OR_NULL(x) if (x) ILVI_ASSERTVALID(x)
#else
#define ILVI_NEW new
#define ILVI_DELETE(x) delete (x);
#define ILVI_ASSERTVALID(x) ILVST_ASSERT(x)
#if defined(ILVDEBUG) && defined(_WINDOWS)
#define ILVI_ASSERTVALID_OR_NULL(x) if (x) ILVI_ASSERTVALID(x)
#else
#define ILVI_ASSERTVALID_OR_NULL(x)
#endif
#endif

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_genbase)
#endif /* !__IlvSt_Inspectors_Genbase_H */
