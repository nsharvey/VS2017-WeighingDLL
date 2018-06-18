// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/collect.h
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
// Declaration of the IliCollectable and IliCollection classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Collect_H
#define __Ili_Collect_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Objcls_H
#  include <ilviews/dataccess/objcls.h>
#endif

#ifndef __Ili_Alloc_H
#  include <ilviews/dataccess/alloc.h>
#endif

typedef int (*IliCollectCompare) (IliCollectable*,IliCollectable*,IlAny);

// --------------------------------------------------------------------------
// IliCollectable
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliCollectable {
public:
  IliCollectable () {}
  IliCollectable (const IliCollectable&) {}
  IliCollectable (IL_STDPREF istream&) {}
  virtual ~IliCollectable ();

  IliDeclareTypeInfo(IliCollectable);
  virtual void write (IL_STDPREF ostream&) const;
  int operator == (const IliCollectable&) const;

  ILI_MLK_DECL();
};

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliCollectable);

// --------------------------------------------------------------------------
// IliCollection
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliCollection {
public:
  IliCollection (IlInt initialCapacity = 0);
  IliCollection (const IliCollection&);
  virtual ~IliCollection ();

  int operator == (const IliCollection&) const;
  inline int operator != (const IliCollection& o) const;

  enum IliCollectionConstant {
    IliCollectionNotFound = -1,
    IliCollectionIncrement = 16
  };

  void readPoly (IL_STDPREF istream&);
  void readPoly (IlvDisplay*,IL_STDPREF istream&);
  void readMono (IL_STDPREF istream&, const IliClassInfo*);
  void readMono (IlvDisplay*,IL_STDPREF istream&, const IliClassInfo*);

  void writePoly (IL_STDPREF ostream&) const;
  void writeMono (IL_STDPREF ostream&) const;

  void appendPoly (const IliCollection&);
  void appendMono (const IliCollection&, const IliClassInfo*);

  IlBoolean isEmpty () const;
  inline IlInt count () const;
  inline IlInt capacity () const;
  void setCapacity (IlInt);

  IlBoolean contains (const IliCollectable*) const;
  IlInt indexOf (const IliCollectable*) const;
  const IliCollectable* at (IlInt i) const;
  IliCollectable* at (IlInt i);

  IlInt append (IliCollectable*);
  IlBoolean prepend (IliCollectable*);
  IlBoolean insert (IlInt, IliCollectable*);
  IlBoolean set (IlInt, IliCollectable*);

  IlBoolean insertSorted (IliCollectable*, IliCollectCompare, IlAny = 0);
  void sort (IliCollectCompare, IlAny = 0);

  IlBoolean push (IliCollectable* c);
  IliCollectable* pop ();
  IliCollectable* top ();

  void clearAll ();
  void deleteAll ();

  IlBoolean clearAt (IlInt);
  IlBoolean deleteAt (IlInt);

  IlBoolean clearItem (IliCollectable*);
  IlBoolean deleteItem (IliCollectable*);

  ILI_MLK_DECL();
protected:
  IliCollection& operator = (const IliCollection&) { return *this; }

  IliCollectable **_items;
  IlInt _count;
  IlInt _capacity;
};

// --

inline int
IliCollection::operator != (const IliCollection& o) const {
  return (!(operator == (o)));
}

inline IlInt
IliCollection::count () const {
  return _count;
}

inline IlInt
IliCollection::capacity () const {
  return _capacity;
}

// --

#define IliDeclareCollection(zzexp,C,E) \
class ILV_##zzexp##_EXPORTED C: public IliCollection { \
public: \
  C (IlInt initcap = 0) : IliCollection(initcap) {} \
  C (const C& c) : IliCollection(c) {} \
  void read (IL_STDPREF istream& is) { readMono(is, IliClassInfo::Find(ILVSTRING(E))); } \
  void read (IlvDisplay* dpy,IL_STDPREF istream& is) { \
    readMono(dpy, is, IliClassInfo::Find(ILVSTRING(E))); } \
  void write (IL_STDPREF ostream& os) const { writeMono(os); } \
  int operator == (const C& c) const { return IliCollection::operator == (c); } \
  int operator != (const C& o) const { return (!(operator == (o))); } \
  const E* at (IlInt i) const { return (const E*)IliCollection::at(i); } \
  E* at (IlInt i) { return (E*)IliCollection::at(i); } \
  IlInt append (E* e)  { return IliCollection::append(e); } \
  IlBoolean prepend (E* e) { return IliCollection::prepend(e); } \
  IlBoolean insert (IlInt i, E* e) { return IliCollection::insert(i, e); } \
  IlBoolean set (IlInt i, E* e) { return IliCollection::set(i, e); } \
  IlBoolean push (E* e) { return IliCollection::push(e); } \
  E* pop () { return (E*)IliCollection::pop(); } \
  E* top () { return (E*)IliCollection::top(); } \
}

#endif
