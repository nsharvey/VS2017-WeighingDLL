// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/util.h
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
// Declaration of general purposes functions
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Util_H
#define __Ilv_Maps_Util_H

#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if defined(ILVSTD)
#  include <iostream>
#  include <fstream>
ILVSTDUSE
#else
#  include <iostream.h>
#  include <fstream.h>
#endif

// --------------------------------------------------------------------------
ostream*  IlvMapsOutStream(const char*);
istream*  IlvMapsInStream(const char*);
ofstream* IlvMapsOutFStream(const char*);
ifstream* IlvMapsInFStream(const char*);

class ILVMAPSEXPORTED IlvCoordinate;
ILVMAPSEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvCoordinate& p);
ILVMAPSEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvCoordinate& p);

#endif /* !__Ilv_Maps_Util_H */
