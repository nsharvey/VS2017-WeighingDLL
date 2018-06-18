// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/magic.h
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
//
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Magic_H
#define __Ilv31_Variable_Magic_H

// macros to be used
#define ILVV_MAGIC_DECL(datmtype,datmid) \
static datmtype& datmid()

// destroys automatically if not in shared lib
#define ILVV_MAGIC_DEF(classid,datmtype,datmid) \
datmtype& classid::datmid(){ \
   static datmtype _##datmid; \
   return _##datmid; \
}

// does not destroy automatically. interesting if the order of destruction
// is important
#define ILVV_SMAGIC_DEF(classid,datmtype,datmid) \
datmtype& classid::datmid(){ \
   static datmtype* _##datmid=new datmtype(); \
   return* _##datmid; \
}

#define ILVV_DESTRUCTOR_CLASS(classid,datmid) \
classid##__##datmid##__##MagicDestructor

#define ILVV_DESTRUCTOR_DATUM(classid,datmid) \
classid##__##datmid##__##MagicDestructorDatum

// these are compatible ONLY with SMAGIC
#define ILVV_MAGIC_FREE_DECL(classid,datmid) \
class ILVV_DESTRUCTOR_CLASS(classid,datmid) \
{ \
public: \
  ILVV_DESTRUCTOR_CLASS(classid,datmid)(); \
  ~ILVV_DESTRUCTOR_CLASS(classid,datmid)(); \
}; \
static ILVV_DESTRUCTOR_CLASS(classid,datmid) ILVV_DESTRUCTOR_DATUM(classid,datmid)

// cannot destroy directly the address, compilers do not like it
#define ILVV_MAGIC_FREE_DEF(classid,datmtype,datmid) \
ILVV_DESTRUCTOR_CLASS(classid,datmid)::ILVV_DESTRUCTOR_CLASS(classid,datmid)(){} \
ILVV_DESTRUCTOR_CLASS(classid,datmid)::~ILVV_DESTRUCTOR_CLASS(classid,datmid)(){ \
  static IlvvBoolean made=IlvvFalse; \
  if (!made){ \
    datmtype* datum=&classid::datmid(); \
    delete datum; \
    made=IlvvTrue; \
  } \
}

#endif
