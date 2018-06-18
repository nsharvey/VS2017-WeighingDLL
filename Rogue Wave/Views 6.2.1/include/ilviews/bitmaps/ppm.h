// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/ppm.h
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
// Declaration of PPM bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Ppm_H
#define __Ilv_Bitmaps_Ppm_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvppm.lib")
#endif

#if defined(ILVPPMLIB)
#  define ILVPPMEXPORTED IL_BASEEXPORTED
#  define ILVPPMEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVPPMEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVPPMLIB */
#  define ILVPPMEXPORTED IL_BASEIMPORTED
#  define ILVPPMEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVPPMEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVPPMLIB */

// Static initialization macros
#define ILVPPMMODULEINIT(m) IL_MODULEINIT(m, ILVPPMEXPORTED)
#define ILVPPMMODULETERM(m) IL_MODULETERM(m, ILVPPMEXPORTED)

// --------------------------------------------------------------------------
class ILVPPMEXPORTED IlvPPMStreamer : public IlvBitmapStreamer
{
public:
    IlvPPMStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    void		setBinary(IlBoolean interlace);
    IlBoolean		isBinary() const;
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, ILVSTDPREF ostream& stream);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_binaryValue;

protected:
    IlBoolean		_binary;
};

IL_MODULETERM(ppm, ILVPPMEXPORTED);
#endif /* __Ilv_Bitmaps_Ppm_H */
