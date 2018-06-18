// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intset.h
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
// Declaration of the IliIntSet class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Intset_H
#define __Ili_Intset_H

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

class ILV_INF_EXPORTED IliIntSet {
public:
  IliIntSet () {}
  ~IliIntSet () {}

  IlInt count () const;

  IlBoolean contains (IlInt) const;
  IlBoolean contains (const IliIntSet&) const;
  int operator == (const IliIntSet&) const;

  void add (IlInt);
  void remove (IlInt);
  void empty ();

protected:
  IlvHashTable _hash;
};

#endif




