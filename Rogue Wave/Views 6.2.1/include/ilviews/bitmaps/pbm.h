// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/pbm.h
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
// PBM bitmaps format i/o function
// --------------------------------------------------------------------------
#ifndef _Ilv_Bitmaps_Pbm_H
#define _Ilv_Bitmaps_Pbm_H

#if !defined(__Ilv_Bitmaps_Io_H)
#include <ilviews/bitmaps/io.h>
#endif

// --------------------------------------------------------------------------
// Reads in a PBM-formated image file (PBM, PGM or PPM) to create an IlogViews
// bitmap.
// Returns 0 on error.
// --------------------------------------------------------------------------
ILVDSPEXPORTEDFUNCTION(IlvBitmap*)
IlvReadPBMBitmap(IlvDisplay*, ILVSTDPREF istream& stream);

// --------------------------------------------------------------------------
// Writes out a PBM-formated image file (PBM or PPM) from an IlogViews
// bitmap.
// Output format will be P4 (binary monochrome) or P6 (binary colored)
// Returns IlFalse on error.
// --------------------------------------------------------------------------
ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvWritePBMBitmap(IlvBitmap*, ILVSTDPREF ostream& stream);

#endif /* !_Ilv_Bitmaps_Pbm_H */
