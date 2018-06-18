// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/vsession.h
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
// Declaration of the IliSession class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Vsession_H
#define __Ili_Vsession_H

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ili_Value_H
#  include <ilviews/dataccess/value.h>
#endif

class ILV_INF_EXPORTED IliSession : public IliRefCounted {
public:
  IliSession ();
  IliSession (const IliSession&);

  static void EmitUnquotedBinaryLiteral(IliString&, const IliBinary&);
  static void EmitByte(IliByte b, char& c1, char& c2);

  static IlBoolean ParseByte(IliByte& b, char c1, char c2);
  static IlBoolean ParseUnquotedBinaryLiteral(const char* src,IlUInt len,
					      IliBinary& dest);

  /* Other */

  virtual void emitBinaryLiteral (IliString&, const IliBinary&) const;
  virtual void emitDate (IliString&, IliDate) const;
  virtual void emitTime (IliString&, IliTime) const;

protected:
  virtual ~IliSession ();
};

#endif
