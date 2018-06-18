// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/wbmp.h
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
// Declaration of WBMP bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Wbmp_H
#define __Ilv_Bitmaps_Wbmp_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvwbmp.lib")
#endif

#if defined(ILVWBMPLIB)
#  define ILVWBMPEXPORTED IL_BASEEXPORTED
#  define ILVWBMPEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVWBMPEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVWBMPLIB */
#  define ILVWBMPEXPORTED IL_BASEIMPORTED
#  define ILVWBMPEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVWBMPEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVWBMPLIB */

// Static initialization macros
#define ILVWBMPMODULEINIT(m) IL_MODULEINIT(m, ILVWBMPEXPORTED)
#define ILVWBMPMODULETERM(m) IL_MODULETERM(m, ILVWBMPEXPORTED)

// --------------------------------------------------------------------------
class ILVWBMPEXPORTED IlvWBMPStreamer : public IlvBitmapStreamer
{
public:
    IlvWBMPStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		isWhiteTransparent() const;
    void		setWhiteTransparent(IlBoolean transp);
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, IL_STDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    static IlSymbol*	_wtransValue;

protected:
    IlBoolean		_wtrans;
};

IL_MODULETERM(wbmp, ILVWBMPEXPORTED);
#endif /* __Ilv_Bitmaps_Wbmp_H */
