// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/macros.h
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
// Declaration of Document / view macros
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Macros_H)
#define __Ilv_Appframe_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvappframe.lib")
#endif

// --------------------------------------------------------------------------
// Compiling DocView DLL
// --------------------------------------------------------------------------
#if defined(ILVDVLIB)
#  define ILVDVEXPORTED ILVBASEEXPORTED
#  define ILVDVEXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#  define ILVDVEXPORTEDVAR(type) ILVBASEEXPORTEDFUNCTION(type)
#endif /* !ILVDVLIB */

#if !defined(ILVDVEXPORTED)
#  define ILVDVEXPORTED ILVBASEIMPORTED
#  define ILVDVEXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#  define ILVDVEXPORTEDVAR(type) ILVBASEIMPORTEDFUNCTION(type)
#endif /* ILVDVEXPORTED */

// Static initialization macros
#define ILVDVMODULEINIT(m) IL_MODULEINIT(m, ILVDVEXPORTED)
#define ILVDVMODULETERM(m) IL_MODULETERM(m, ILVDVEXPORTED)

#define ILVDVCLASS ILVDVEXPORTED

#define IlvDECLAREINITDVCLASS(m)  IL_MODULEINIT(dv_##m, ILVDVEXPORTED);

#if 0
#if defined(ILVDVBUILDLIBS)
  #if !defined(ILVDLL)
    #define ILVDLL
  #endif
  #if !defined(IL_BUILDINGMODULE)
    #define IL_BUILDINGMODULE
  #endif

  // --------------------------- MicroSoft Visual C/C++
  #if defined(_MSC_VER) && defined(WIN32)
    #define ILVDVEXPORTED		    _declspec(dllexport)
    #define ILVDVEXPORTEDFUNCTION(type)	    ILVDVEXPORTED type
    #define ILVDVEXPORTEDVAR(type)	    ILVDVEXPORTED type
    #define ILVDVCLASS			    ILVDVEXPORTED
    #define ILVDVEXPORTEDFUNC(type)	    ILVDVEXPORTED type
    #pragma warning(disable : 4251)
  #endif /* MicroSoft Visual C/C++ */

// --------------------------------------------------------------------------
// Compiling a DocView DLL Application
// --------------------------------------------------------------------------

#elif defined(IL_BUILDINGMODULE)
  // --------------------------- MicroSoft Visual C/C++
  #if defined(_MSC_VER) && defined(WIN32)
    #define ILVDVEXPORTED                _declspec(dllimport)
    #define ILVDVEXPORTEDVAR(type)       ILVDVEXPORTED type
    #define ILVDVCLASS			 ILVDVEXPORTED
    #define ILVDVEXPORTEDFUNC(type)	 ILVDVEXPORTED type

    #define DVAPPEXPORTED		_declspec(dllexport)
    #define DVAPPEXPORTEDFUNCTION(type) DVAPPEXPORTED type
    #define DVAPPEXPORTEDVAR(type)	DVAPPEXPORTED type
    #define DVAPPCLASS			DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNC(type)	DVAPPEXPORTED type
    #pragma warning(disable : 4251)

  #else /* Not MicroSoft Visual C/C++ */
    #define ILVDVEXPORTED                
    #define ILVDVEXPORTEDVAR(type)       type
    #define ILVDVCLASS			 
    #define ILVDVEXPORTEDFUNC(type)	 type

    #define DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNCTION(type) type
    #define DVAPPEXPORTEDVAR(type)	type
    #define DVAPPCLASS			
    #define DVAPPEXPORTEDFUNC(type)	type
  #endif /* Not MicroSoft Visual C/C++ */

// --------------------------------------------------------------------------
// Compiling a DocView Application
// --------------------------------------------------------------------------

#else /* !ILVDV_COMPILING_DLL && !ILVDVDLL */
    #define ILVDVEXPORTED
    #define ILTEXPORTEDFUNCTION(type)    type
    #define ILVDVEXPORTEDVAR(type)       type
    #define ILVDVCLASS			 ILVDVEXPORTED
    #define ILVDVEXPORTEDFUNC(type)	 ILVDVEXPORTED type

    #define DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNCTION(type) type
    #define DVAPPEXPORTEDVAR(type)	type
    #define DVAPPCLASS
    #define DVAPPEXPORTEDFUNC(type)	type
#endif /* !ILVDV_COMPILING_DLL && !ILVDVDLL */

#define IlvDECLAREINITDVCLASS(m)  IL_MODULEINIT(dv_##m, ILVDVCLASS);
#endif

// --------------------------------------------------------------------------
// Declaration of DVAPPxxxx macros
// --------------------------------------------------------------------------

#if defined(IL_BUILDINGMODULE)
  // --------------------------- MicroSoft Visual C/C++
  #if defined(_MSC_VER) && defined(WIN32)
    #define DVAPPEXPORTED		_declspec(dllexport)
    #define DVAPPEXPORTEDFUNCTION(type) DVAPPEXPORTED type
    #define DVAPPEXPORTEDVAR(type)	DVAPPEXPORTED type
    #define DVAPPCLASS			DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNC(type)	DVAPPEXPORTED type
    #pragma warning(disable : 4251)

  #else /* Not MicroSoft Visual C/C++ */
    #define DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNCTION(type) type
    #define DVAPPEXPORTEDVAR(type)	type
    #define DVAPPCLASS			
    #define DVAPPEXPORTEDFUNC(type)	type
  #endif /* Not MicroSoft Visual C/C++ */
#else /* !ILVDV_COMPILING_DLL && !ILVDVDLL */
    #define DVAPPEXPORTED
    #define DVAPPEXPORTEDFUNCTION(type) type
    #define DVAPPEXPORTEDVAR(type)	type
    #define DVAPPCLASS
    #define DVAPPEXPORTEDFUNC(type)	type
#endif /* !ILVDV_COMPILING_DLL && !ILVDVDLL */

// --------------------------------------------------------------------------
// Includes


#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined( __Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__IlvDv_Clssinfo_H)
#include <ilviews/appframe/clssinfo.h>
#endif

class IlvDvDynClassInfo;
// --------------------------------------------------------------------------
// Macros used to define an IlvDvSerializable derived class

#define IlvDvDeclareClassInfo() \
    IlvDeclareClassInfo(); \
    IlvDvDeclareDownCasting()

#define IlvDvDeclareDynCreate()					\
    IlvDeclareClassInfo();					\
    virtual IlvDvDynClassInfo* getDynClassInfo() const		\
	{ return DynClassInfo(); }				\
    static  IlvDvDynClassInfo* DynClassInfo()			\
	{ return (IlvDvDynClassInfo*)_classinfo; }		\
    IlvDvDeclareDownCasting();					\
public: static IlvDvSerializable* Builder()

#define IlvDvClassInfoValue(classname, superclass)		\
IlvClassInfo::Create(#classname, superclass::ClassPtr())

		    // -----------------------------------
#if 1 || defined(ILVBUILDLIBS)

#define IlvDvPreRegisterDynClass(classname, superclass)			\
IlvDvDefineCast(classname, superclass)					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvSerializable* classname::Builder() { return new classname; }	\
IlvClassInfo* classname::_classinfo = 0

#define IlvDvPreRegisterRootDynClass(classname, superclass)		\
IlvDvDefineRootCast(classname)						\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvSerializable* classname::Builder() { return new classname; }	\
IlvClassInfo* classname::_classinfo = 0

#define IlvDvPreRegisterAbstractClass(classname, superclass)		\
IlvDvDefineCast(classname, superclass)					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvClassInfo* classname::_classinfo = 0

#define IlvDvDefineInitClass(mod, exp) ILVDEFINEINITCLASS(mod, exp)
#define IlvDvPreRegisterSymbol(symb, value) IlSymbol* symb = 0
#define IlvDvPostRegisterSymbol(symb, value) symb = IlGetSymbol(value)

#else  /* !IlvDECLAREINITCLASS */

#define IlvDvPreRegisterDynClass(classname, superclass)			\
IlvDvDefineCast(classname, superclass);					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvSerializable* classname::Builder() { return new classname; }	\
IlvClassInfo* classname::_classinfo =					\
	IlvDvDynClassInfo::Create(#classname, superclass::ClassPtr(),	\
				  classname::Builder)

#define IlvDvPreRegisterRootDynClass(classname, superclass)		\
IlvDvDefineRootCast(classname);						\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvSerializable* classname::Builder() { return new classname; }	\
IlvClassInfo* classname::_classinfo =					\
	lvDvDynClassInfo::Create(#classname, 0, classname::Builder)

#define IlvDvPreRegisterAbstractClass(classname, superclass)		\
IlvDvDefineCast(classname, superclass);					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvClassInfo* classname::_classinfo =					\
       IlvDvDynClassInfo::Create(#classname, superclass::ClassPtr(), 0)

#define IlvDvDefineInitClass(mod, exp) exp
#define IlvDvPreRegisterSymbol(symb, value) \
IlSymbol* symb = IlGetSymbol(value)
#define IlvDvPostRegisterSymbol(symb, value)

#endif /* IlvDECLAREINITCLASS */
		    // -----------------------------------

#define IlvDvPostRegisterDynClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
	    IlvDvDynClassInfo::Create(#classname,		\
				      superclass::ClassPtr(),	\
				      classname::Builder))
#define IlvDvPostRegisterRootDynClass(classname)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
	    IlvDvDynClassInfo::Create(#classname,		\
				      0, classname::Builder))
#define IlvDvPostRegisterAbstractClass(classname, sclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
IlvDvDynClassInfo::Create(#classname, sclass::ClassPtr(), 0))

#define IlvDvDownCast(classname, obj) \
((classname*)IlvDvSerializable::DownCast(classname::ClassInfo(), obj))
#define IlvDvConstDownCast(classname, obj) \
((const classname*)IlvDvSerializable::ConstDownCast(classname::ClassInfo(), \
						    obj))

// --------------------------------------------------------------------------
// Scaning memory leaks / already deleted objects
// --------------------------------------------------------------------------
#ifdef ILVALLOCCHECK
#define ILVDV_NEW new(__FILE__, __LINE__)
#define ILVDV_DELETE(x) IlvDvSerializable::Delete(__FILE__, __LINE__, x)
#define ILVDV_ASSERTVALID(x) IlvDvSerializable::IsValid(x)
#define ILVDV_ASSERTVALID_OR_NULL(x) if (x) ILVDV_ASSERTVALID(x)
#else
#define ILVDV_NEW new
#define ILVDV_DELETE(x) delete (x);
#define ILVDV_ASSERTVALID(x) ILVST_ASSERT(x)
#if defined(ILVDEBUG) && defined(WINDOWS)
#define ILVDV_ASSERTVALID_OR_NULL(x) if (x) ILVDV_ASSERTVALID(x)
#else
#define ILVDV_ASSERTVALID_OR_NULL(x)
#endif
#endif

// --------------------------------------------------------------------------
// Assert macros
#if defined(ILVDEBUG) && defined(WINDOWS)
    #undef NDEBUG
    #include <assert.h>
    #define IlvDvAssert(exp) assert(exp)
    #define IlvDvTrace(exp)
#else 
    #define IlvDvAssert(exp)
    #define IlvDvTrace(exp)
#endif

// --------------------------------------------------------------------------
// Casting macros
#define IlvDvDeclareDownCasting() \
public: \
    virtual IlAny downCast(const IlvClassInfo* classInfo); \
    virtual const void* downCast(const IlvClassInfo* classInfo) const

#define IlvDvDefineCast(classname, superclass)				\
IlAny classname::downCast(const IlvClassInfo* classInfo)		\
{ return (classname::ClassInfo() == classInfo) ?			\
	(IlAny)this : (IlAny)superclass::downCast(classInfo); }	\
const void* classname::downCast(const IlvClassInfo* classInfo) const	\
{ return (classname::ClassInfo() == classInfo) ?			\
	(IlAny)this : (IlAny)superclass::downCast(classInfo); }

#define IlvDvDefineRootCast(classname)					\
IlAny classname::downCast(const IlvClassInfo* classInfo)		\
{ return (classname::ClassInfo() == classInfo)? (IlAny)this : 0; }	\
const void* classname::downCast(const IlvClassInfo* classInfo) const	\
{ return (classname::ClassInfo() == classInfo)? (IlAny)this : 0; }

// --------------------------------------------------------------------------
// Registering class macros
#define IlvDvPreRegisterRootClass(classname)				\
IlvDvDefineRootCast(classname)						\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvClassInfo* classname::_classinfo = 0

#if 1 || defined(ILVBUILDLIBS)
#define IlvDvPreRegisterClass(classname, superclassname) \
IlvDvDefineCast(classname, superclassname) \
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvClassInfo* classname::_classinfo = 0
#else  /* !ILVBUILDLIBS */
#define IlvDvPreRegisterClass(classname, super) \
IlvDvDefineCast(classname, super) \
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvClassInfo* classname::_classinfo = IlvPropClassInfo::Create(#classname, \
					                 super::ClassPtr())
#endif /* !ILVBUILDLIBS */

#define IlvDvPostRegisterRootClass(classname)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,	\
			      IlvPropClassInfo::Create(#classname, 0))

#define IlvDvPostRegisterClass(classname, super)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
	IlvPropClassInfo::Create(#classname, super::ClassPtr()))

// --------------------------------------------------------------------------
// Flag operations
inline IlUInt
IlvDvSetFlag(IlUInt flag, IlUInt flagToModifiy, IlBoolean set = IlTrue)
{
    if (set) {
	if (!(flag & flagToModifiy))
	    flag |= flagToModifiy;
    } else {
	if (flag & flagToModifiy)
	    flag ^= flagToModifiy;
    }
    return flag;
}

inline IlBoolean
IlvDvIsFlagSet(IlUInt flag, IlUInt flagToTest)
{
    return (flag & flagToTest) ? IlTrue : IlFalse;
}

#define ILVNOSCRIPT

#endif /* !__Ilv_Appframe_Macros_H */
