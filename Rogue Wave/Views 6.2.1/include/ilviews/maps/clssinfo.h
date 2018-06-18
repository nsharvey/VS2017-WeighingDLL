// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/clssinfo.h
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
// General Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Clssinfo_H
#define __Ilv_Maps_Clssinfo_H

#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif

typedef void (* IlvMapObjectWriter)(IlAny, IlvOutputFile&);
void ILVMAPSEXPORTED IlvNullMapWriter(IlAny, IlvOutputFile&);
typedef IlAny (* IlvMapObjectReader)(IlvInputFile&, IlAny);
IlAny ILVMAPSEXPORTED IlvNullMapReader(IlvInputFile& , IlAny);

// not documented
class ILVMAPSEXPORTED IlvMapClassInfo
: public IlvValuedClassInfo
{
private:
    IlvMapObjectReader _reader;
    IlvMapObjectWriter _writer;
protected:
    IlvMapClassInfo(const char*,
		    IlvClassInfo**,
		    IlvMapObjectReader,
		    IlvMapObjectWriter);
public:
    static IlvMapClassInfo* Create(const char*,
				   IlvClassInfo**,
				   IlvMapObjectReader,
				   IlvMapObjectWriter);
    virtual ~IlvMapClassInfo();

    void write(IlAny, IlvOutputFile&) const;
    void writeAsReference(IlAny, IlvOutputFile&) const;
    IlAny readObject(IlvInputFile&, IlAny) const;

    static IlAny ReadObject(const IlvMapClassInfo*,
			     IlvInputFile&,
			     IlAny);
    static IlAny ReadReference(const IlvMapClassInfo*,
				IlvInputFile&,
				IlAny);
    static IlvMapClassInfo* Get(const IlvMapClassInfo*,
				const char*);
};

#define IlvMapsDeclareIO(className)				\
private:							\
   static IlvClassInfo* _classinfo;				\
public:								\
   className(IlvInputFile&);					\
   inline static IlvMapClassInfo* ClassInfo()			\
	{ return (IlvMapClassInfo*)_classinfo; }		\
   inline static IlvClassInfo** ClassInfoRef()			\
	{ return &_classinfo; }					\
   virtual IlvMapClassInfo* getClassInfo() const;		\
   virtual void write(IlvOutputFile&) const

#define IlvMapsPreregisterIO(className)				\
IlvMapClassInfo* className::getClassInfo() const		\
  { return (IlvMapClassInfo*)_classinfo; }			\
IlAny _IlvReader_##className(IlvInputFile& file, IlAny a)	\
  { return new className(file); }				\
void _IlvWriter_##className(IlAny a, IlvOutputFile& file)	\
  { ((className*)a)->write(file); }				\
IlvClassInfo* className::_classinfo = 0

#define IlvMapsRegisterIO(className, superClass)		\
    if (!_classinfo)						\
      _classinfo = IlvMapClassInfo::Create(#className,		\
	superClass::ClassInfoRef(),				\
	_IlvReader_##className, _IlvWriter_##className)

/*
#define IlvMapsDeclareLazyIO(className)			\
private:						\
   static IlvClassInfo* _classinfo;			\
public:							\
   className(IlvInputFile&);				\
   static IlvMapClassInfo* ClassInfo();			\
   static IlvClassInfo** ClassInfoRef();		\
   virtual IlvMapClassInfo* getClassInfo() const;	\
   virtual void write(IlvOutputFile&) const

#define IlvMapsDefineIO(className, superClass)		\
IlvMapClassInfo* className::getClassInfo() const	\
	{ return ClassInfo(); }				\
IlvClassInfo** className::ClassInfoRef()		\
	{ ClassInfo(); return &_classinfo; }		\
IlAny _IlvReader_##className(IlvInputFile& f, IlAny a)	\
	{ return new className(f); }			\
void _IlvWriter_##className(IlAny a, IlvOutputFile& f)	\
	{ ((className*)a)->write(file); }		\
IlvMapClassInfo* className::ClassInfo()			\
    {							\
	if (!_classinfo) {				\
	_classinfo =					\
    IlvMapClassInfo::Create(#className,                 \
			    superClass::ClassInfoRef(),	\
			    _IlvReader_##className,	\
			    _IlvWriter_##className);	\
    return (IlvMapClassInfo*)_classinfo;		\
}							\
IlvClassInfo* className::_classinfo = 0
*/

#endif /* !__Ilv_Maps_Clssinfo_H */
