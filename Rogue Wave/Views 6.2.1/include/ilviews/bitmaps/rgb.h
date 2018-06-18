// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/rgb.h
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
// Declaration of SGI RGB bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Rgb_H
#define __Ilv_Bitmaps_Rgb_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvrgb.lib")
#endif

#if defined(ILVRGBLIB)
#  define ILVRGBEXPORTED IL_BASEEXPORTED
#  define ILVRGBEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVRGBEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVRGBLIB */
#  define ILVRGBEXPORTED IL_BASEIMPORTED
#  define ILVRGBEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVRGBEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVRGBLIB */

// Static initialization macros
#define ILVRGBMODULEINIT(m) IL_MODULEINIT(m, ILVRGBEXPORTED)
#define ILVRGBMODULETERM(m) IL_MODULETERM(m, ILVRGBEXPORTED)

// --------------------------------------------------------------------------
class ILVRGBEXPORTED IlvRGBStreamer : public IlvBitmapStreamer
{
public:
    IlvRGBStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    void		setAlphaLevel(IlUInt level);
    IlUInt		getAlphaLevel() const;
    IlvBitmapData*	read(IL_STDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, IL_STDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    static IlSymbol*	_alphaValue;

protected:
    IlUInt		_alphalevel;
    IlUChar		_storage;
    IlUChar		_bpc;
    IlUShort		_width;
    IlUShort		_height;
    IlUShort		_zsize;
    IlUChar*		_rawdata;

    void		getImageData(IL_STDPREF istream& stream);
    void		expandRow(IlUChar* dst, IlUChar* src);
};

IL_MODULETERM(rgb, ILVRGBEXPORTED);
#endif /* __Ilv_Bitmaps_Rgb_H */
