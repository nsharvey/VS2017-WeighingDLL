// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/png.h
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
// Declaration of PNG bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Png_H
#define __Ilv_Bitmaps_Png_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvpng.lib")
#endif

#if defined(ILVPNGLIB)
#  define ILVPNGEXPORTED IL_BASEEXPORTED
#  define ILVPNGEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVPNGEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVPNGLIB */
#  define ILVPNGEXPORTED IL_BASEIMPORTED
#  define ILVPNGEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVPNGEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVPNGLIB */

// Static initialization macros
#define ILVPNGMODULEINIT(m) IL_MODULEINIT(m, ILVPNGEXPORTED)
#define ILVPNGMODULETERM(m) IL_MODULETERM(m, ILVPNGEXPORTED)

// --------------------------------------------------------------------------
class ILVPNGEXPORTED IlvPNGStreamer : public IlvBitmapStreamer
{
public:
    IlvPNGStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    void		setInterlace(IlBoolean interlace);
    IlBoolean		hasInterlace() const;
    void		setCompressionLevel(IlUInt level);
    IlUInt		getCompressionLevel() const;
    void		setAlphaLevel(IlUInt level);
    IlUInt		getAlphaLevel() const;
    void		setIndexed(IlBoolean indexed, IlUShort numcols = 256);
    IlBoolean		isIndexed() const;
    IlUShort		getIndexedColors() const;
    IlvBitmapData*	read(IL_STDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, IL_STDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    static IlSymbol*	_interlaceValue;
    static IlSymbol*	_compressionValue;
    static IlSymbol*	_alphaValue;
    static IlSymbol*	_indexedValue;
    static IlSymbol*	_colorsValue;

protected:
    IlBoolean		_interlace;
    IlUInt		_compressionlevel;
    IlUInt		_alphalevel;
    IlBoolean		_indexed;
    IlUShort		_colors;
};

IL_MODULETERM(png, ILVPNGEXPORTED);
#endif /* __Ilv_Bitmaps_Png_H */
