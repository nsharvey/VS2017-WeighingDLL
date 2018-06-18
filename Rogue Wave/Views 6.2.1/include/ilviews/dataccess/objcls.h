// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/objcls.h
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
// Declaration of the IliClassInfo class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Objcls_H
#define __Ili_Objcls_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

class ILV_INF_EXPORTED IliCollectable;

typedef IliCollectable*
(*IliTypeReader) (IL_STDPREF istream&);

typedef IliCollectable*
(*IliDTypeReader) (IlvDisplay*,IL_STDPREF istream&);

typedef IliCollectable*
(*IliTypeDuplicator) (const IliCollectable&);

class ILV_INF_EXPORTED IliClassInfo {
public:
  ~IliClassInfo();

  const char* getName() const { return _classname; }
  const IliClassInfo* getSuperClass () const { return _super; }
  IliTypeReader getReader () const { return _reader; }
  IliDTypeReader getDReader () const { return _dReader; }
  IliTypeDuplicator getDuplicator () const { return _duplicator; }

  const char* getCompatName() const { return _compatClassname; }
  void setCompatName(const char* name) { _compatClassname = name; }

  IlBoolean isSubtypeOf (const char*) const;
  IlBoolean isSubtypeOf (const IliClassInfo*) const;

  static IliClassInfo* Find (const char* classname);
  static IliClassInfo* Create(const char* cname,
			      const char* parent,
			      IliTypeReader r,
			      IliTypeDuplicator d);
  static IliClassInfo* Create(const char* cname,
			      const char* parent,
			      IliDTypeReader r,
			      IliTypeDuplicator d);
  static void AtInit ();
  static void AtExit ();
protected:
  IliClassInfo (const char* cname,
		const char* parent,
		IliTypeReader r,
		IliTypeDuplicator d);
  IliClassInfo (const char* cname,
		const char* parent,
		IliDTypeReader r,
		IliTypeDuplicator d);
  IliString _classname;
  IliString _compatClassname;
  const IliClassInfo* _super;
  IliTypeReader _reader;
  IliDTypeReader _dReader;
  IliTypeDuplicator _duplicator;
  static IlvStringHashTable* _allTypes;
  friend class IliModuleCLASS(IliClassInfo);
};

#define IliCommonDeclareTypeInfo(classname) \
  static IliClassInfo* _classinfo; \
  virtual const IliClassInfo* classInfo () const; \
  static const IliClassInfo* ClassInfo (); \
  virtual IliCollectable* copy () const; \
  virtual IlBoolean isEqual (const IliCollectable*) const; \
  int operator != (const classname& o) { return (!operator == (o)); } \
  static IliCollectable* Duplicate (const IliCollectable&);

#define IliDeclareTypeInfo(classname) \
  IliCommonDeclareTypeInfo(classname) \
  static IliCollectable* Read (IL_STDPREF istream&)

#define IliDeclareDTypeInfo(classname) \
  IliCommonDeclareTypeInfo(classname) \
  static IliCollectable* Read (IlvDisplay*,IL_STDPREF istream&)

#define ILI_NIENTE

#define IliDeclareTypeInit_exp(mode,classname) \
  IliModuleDECL_exp(ILI_NIENTE mode,classname)

#define IliDeclareTypeInit(classname) \
  IliModuleDECL(classname)

////////////////////////////////
#if 0
#define IliCommonRegisterClass(classname,superclass,compat_2,init,finalize) \
  IliModuleDEF(classname, \
	         classname :: _classinfo = \
	           IliClassInfo::Create((const char*)ILVSTRING(classname), \
				    (const char*)ILVSTRING(superclass), \
				    & classname :: Read, \
				    & classname :: Duplicate); \
		  if (compat_2) \
		     classname :: _classinfo->setCompatName(compat_2); \
		  init , \
		  /* delete classname :: _classinfo*/; \
		  /* classname :: _classinfo = 0 */; \
		  finalize \
		 ) \

#define IliCommonCodeClassInfoClass(classname) \
IliCollectable* classname :: Duplicate (const IliCollectable& o) { \
		      return new classname ((const classname&)o); } \
const IliClassInfo* classname :: classInfo () const { return _classinfo; } \
const IliClassInfo* classname :: ClassInfo () { return _classinfo; } \
IliCollectable* classname :: copy () const { return new classname(*this); } \
IlBoolean classname :: isEqual (const IliCollectable* o) const { \
  if (o != 0 && o->classInfo() == classInfo()) { \
    if (classname :: operator == ((const classname&)*o)) return IlTrue; \
    else return IlFalse; } \
  else return IlFalse; \
} \
IliClassInfo* classname :: _classinfo = 0 /* */

#define IliRegisterClass(classname,superclass) \
  IliCollectable* classname :: Read (IL_STDPREF istream& is) { \
	      return new classname (is); } \
  IliCommonRegisterClass(classname,superclass,NULL, ;, ;)

#define IliRegisterClassCompat(classname,superclass,compat_1) \
IliClassInfoCodeNoDisplay(classname); \
IliClassInfoCompatInitialize(classname,superclass,compat_1)


#define IliRegisterDClass(classname,superclass) \
  IliCollectable* classname :: Read (IlvDisplay* dpy,IL_STDPREF istream& is) {\
	      return new classname (dpy, is); } \
  IliCommonRegisterClass(classname,superclass,NULL, ;, ;)

#define IliRegisterDClassCompat(classname,superclass,compat_3) \
  IliCollectable* classname :: Read (IlvDisplay* dpy,IL_STDPREF istream& is) {\
	      return new classname (dpy, is); } \
  IliCommonRegisterClass(classname,superclass,compat_3, ;, ;)



#define IliRegisterDClassEx(classname,superclass,init,finalize) \
  IliCollectable* classname :: Read (IlvDisplay* dpy,IL_STDPREF istream& is) {\
	      return new classname (dpy, is); } \
  IliCommonRegisterClass(classname, superclass, NULL, init, finalize)

#define IliRegisterDClassExCompat(classname,superclass,compat_4,init,finalize) \
  IliCollectable* classname :: Read (IlvDisplay* dpy,IL_STDPREF istream& is) {\
	      return new classname (dpy, is); } \
  IliCommonRegisterClass(classname,superclass,compat_4,init,finalize)

#endif /// if 0


// --------------------------------------------------------------------------
// ClassInfo code
// --------------------------------------------------------------------------
#define IliClassInfoCommonCode(classname) \
IliCollectable* classname :: Duplicate (const IliCollectable& o) { \
		      return new classname ((const classname&)o); } \
const IliClassInfo* classname :: classInfo () const { return _classinfo; } \
const IliClassInfo* classname :: ClassInfo () { return _classinfo; } \
IliCollectable* classname :: copy () const { return new classname(*this); } \
IlBoolean classname :: isEqual (const IliCollectable* o) const { \
  if (o != 0 && o->classInfo() == classInfo()) { \
    if (classname :: operator == ((const classname&)*o)) return IlTrue; \
    else return IlFalse; } \
  else return IlFalse; \
} \
IliClassInfo* classname :: _classinfo = 0 

#define IliClassInfoCodeNoDisplay(classname) \
  IliCollectable* classname :: Read (IL_STDPREF istream& is) { \
	      return new classname (is); } \
  IliClassInfoCommonCode(classname)

#define IliClassInfoCodeDisplay(classname) \
  IliCollectable* classname :: Read (IlvDisplay* d,IL_STDPREF istream& is) { \
	      return new classname (d,is); } \
  IliClassInfoCommonCode(classname)

// --------------------------------------------------------------------------
// Initialize classInfo
// --------------------------------------------------------------------------
#define IliClassInfoCommonInitialize(classname,superclass) \
  classname :: _classinfo = \
  IliClassInfo::Create((const char*)ILVSTRING(classname), \
		       (const char*)ILVSTRING(superclass), \
		       & classname :: Read, \
		       & classname :: Duplicate)

#define IliClassInfoCompatInitialize(classname,compat_2) \
  classname :: _classinfo->setCompatName(compat_2)

IliModuleDECL_exp(ILV_INF_EXPORTED,IliClassInfo);

#endif


