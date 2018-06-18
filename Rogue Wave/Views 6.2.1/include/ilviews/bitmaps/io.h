// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/io.h
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
// Declaration of bitmap input/output utilities in IlogViews
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Io_H
#define __Ilv_Bitmaps_Io_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

// Pre Views-3.1 bitmap reader registration
typedef IlvBitmap* (* IlvBitmapReader)(IlvDisplay*, ILVSTDPREF istream&);
IL_DEFINEFPTRTOANYCAST(IlvBitmapReader);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvRegisterBitmapReader(IlvBitmapReader reader, const char* extension);
ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvUnregisterBitmapReader(const char* extension);
ILVDSPEXPORTEDFUNCTION(IlvBitmap*)
IlvReadXPMBitmap(IlvDisplay*, ILVSTDPREF istream& stream);

ILVDSPMODULEINIT(b1io);
#endif /* !__Ilv_Bitmaps_Io_H */
