// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/macros.h
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
// Rogue Wave Views - Maps add-on.
// Defines useful macros 
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Macros_H
#define __Ilv_Maps_Macros_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Gcontext_H)
#  include <ilviews/base/gcontext.h>
#endif

// export / import macros for ViewsMaps
#if defined(ILVMAPSLIB)
#  define ILVMAPSEXPORTED ILVBASEEXPORTED
#  define ILVMAPSEXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#  define ILVMAPSEXPORTEDVAR(type) ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVMAPSLIB */
#  define ILVMAPSEXPORTED ILVBASEIMPORTED
#  define ILVMAPSEXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#  define ILVMAPSEXPORTEDVAR(type) ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVMAPSLIB */

#define ILVMAPS_BEGINMODULEINITDEF(m) IL_BEGINMODULEINITDEF(maps##m) 
#define ILVMAPS_ENDMODULEINITDEF(m) IL_ENDMODULEINITDEF(maps##m)
#define ILVMAPS_BEGINMODULETERMDEF(m) IL_BEGINMODULETERMDEF(maps##m)
#define ILVMAPS_ENDMODULETERMDEF(m) IL_ENDMODULETERMDEF(maps##m)

#define IlvMapsIcFriend(m, exportStatement)			\
   friend exportStatement void IL_MODINIT(maps##m)();\
   friend exportStatement void IL_MODTERM(maps##m)()

#define ILVMAPSMODULEINIT(m) IL_MODULEINIT(maps##m, ILVMAPSEXPORTED)
#define ILVMAPSMODULETERM(m) IL_MODULETERM(maps##m, ILVMAPSEXPORTED)

#define ILVMAPS_MODINIT(m) IL_MODINIT(maps##m)

// full definition of non abstract projection initialization
#define ILVMAPS_DEFPROJECTION(classname,      \
			      superclass,     \
			      projname,       \
			      proj4name,      \
			      accessorLister) \
IlvProjectionClassInfo* classname::getClassInfo() const		\
{ return (IlvProjectionClassInfo*) _classInfo; }		\
IlvClassInfo* classname::_classInfo = 0;			\
static IlvProjection* _##classname##_reader(IlvInputFile& f)	\
{ return new classname(f); }					\
static IlvProjection* _##classname##_parser(IlStringHashTable* s)\
{ return new classname(s); }					\
static IlvProjection* _##classname##_constructor()		\
{ return new classname(); }					\
IlvProjection* classname::copy() const				\
{ return new classname(*this); }				\
IlvMapsDefineAccessorCallbacks(classname, accessorLister)	\
static void  _##classname##_accessorInitializer()		\
{IlvMapsRegisterAccessors(classname, accessorLister)}		\
ILVMAPS_BEGINMODULEINITDEF(classname)				\
  classname::_classInfo = IlvProjectionClassInfo::Create(#classname,\
	superclass::ClassInfoRef(),				\
	_##classname##_reader,					\
	_##classname##_parser,					\
	_##classname##_constructor,				\
	_##classname##_accessorInitializer,			\
	projname,						\
	proj4name);						\
	classname::Init();					\
ILVMAPS_ENDMODULEINITDEF(classname)

// Declaration of some key class members
#define ILVMAPS_DECLMANDATORYPROJMEMBERS(classname)		\
public:								\
    virtual IlvProjectionClassInfo* getClassInfo() const;	\
    static IlvClassInfo** ClassInfoRef() { return &_classInfo; }\
    static IlvProjectionClassInfo* ClassInfo()			\
	{ return (IlvProjectionClassInfo*)_classInfo; }		\
    classname(IlvInputFile&);					\
    classname(const classname&);				\
    classname(IlStringHashTable* );				\
    virtual IlvProjection* copy() const;			\
private:							\
    static IlvClassInfo* _classInfo;				\
    static void Init();						\
    static void Finalize();					\
    IlvMapsIcFriend(classname, ILVMAPSEXPORTED)

#define IlvMapsDeclareProjectionIO(className)			\
public:								\
   virtual IlvProjectionClassInfo* getClassInfo() const;	\
   static IlvClassInfo** ClassInfoRef() { return &_classInfo; }	\
   static IlvProjectionClassInfo* ClassInfo()			\
   { return (IlvProjectionClassInfo*)_classInfo; }		\
   static IlvClassInfo* _classInfo;				\
   virtual IlvProjection* copy() const;				\
   className(const className&);					\
   friend class _##className##_InitModuleClass;			\
public:								\
   className(IlvInputFile&)

#define IlvMapsInitProjectionIO(className)	\
class _##className##_InitModuleClass {		\
 public:					\
    _##className##_InitModuleClass()		\
    { if(! _Done) { _Done = IlTrue; init(); }}	\
 protected:					\
    static void init();				\
    static IlBoolean _Done;			\
};						\
static _##className##_InitModuleClass _##className##_InitModuleInstance

inline void IlvMapsEmptyStatement() {}

#define IlvMapsDefineProjectionIO(className,			\
				  superClassName,		\
                                  projectionName,		\
                                  constructorStatement,		\
				  initializationStatement)	\
static IlvProjection* _##className##_reader(IlvInputFile& f)    \
{ return new className(f); }					\
static IlvProjection* _##className##_constructor()		\
{ return constructorStatement; }				\
IlBoolean _##className##_InitModuleClass::_Done = IlFalse;	\
IlvProjection* className::copy() const				\
{ return new className(*this); }				\
void _##className##_InitModuleClass::init() {			\
    className::_classInfo =					\
    IlvProjectionClassInfo::Create(#className,			\
                               superClassName::ClassInfoRef(),	\
                               _##className##_reader,		\
                               _##className##_constructor,	\
			       projectionName);			\
  initializationStatement;					\
}								\
IlvProjectionClassInfo* className::getClassInfo() const		\
{ return (IlvProjectionClassInfo*)_classInfo; }			\
IlvClassInfo* className::_classInfo = 0

#define IlvMapsDefineBasicProjectionIO(className,               \
				       superClassName,          \
                                       projectionName,          \
                                       constructorStatement,    \
				       initializationStatement) \
className::className(IlvInputFile& f)                           \
:superClassName(f) {}                                           \
IlvMapsDefineProjectionIO(className,                            \
			  superClassName,                       \
                          projectionName,                       \
                          constructorStatement,                 \
			  initializationStatement)

// Accessor oriented macros
#define IlvDefineAccessorCallback(C,S,TYPE,NAME,READ,WRITE)	\
static IlBoolean _##NAME##_setter(IlvProjection* abstractP,	\
  const IlvValue& val) {					\
  C* p = (C*)abstractP;						\
  WRITE								\
}								\
static void _##NAME##_getter(const IlvProjection* abstractP,	\
  IlvValue& val) {						\
  C* p = (C*)abstractP;						\
  READ								\
}
#define IlvMapsDefineAccessorCallbacks(C,LISTER)		\
  LISTER(C, DUMMY, IlvDefineAccessorCallback)
#define IlvMapsRegisterAccessor(C,S,TYPE,NAME,READ,WRITE)	\
C::ClassInfo()->addAccessor(IlvGetSymbol(#NAME),		\
			    IlvValue##TYPE##Type,		\
                            &_##NAME##_getter,			\
                            &_##NAME##_setter);
#define IlvMapsRegisterAccessors(C, LISTER)			\
  LISTER(C, DUMMY, IlvMapsRegisterAccessor)

#if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
#  define ILVMAPS_SPARC_5_5
#endif
#if defined(IL_STD) || defined(ILVMAPS_SPARC_5_5)
#  define ILVMAPS_STD_STREAM
#endif
#if !defined(__hpux)
#  define MAPS_ENDL endl
#else  /* HPUX */
#  define MAPS_ENDL '\n'
#endif /* HPUX */

#endif /* !__Ilv_Maps_Macros_H */
