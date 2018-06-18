// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/gif.h
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
// Declaration of BMP bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Gif_H
#define __Ilv_Bitmaps_Gif_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#  include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) \
    && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvgif.lib")
#endif

#if defined(ILVGIFLIB)
#  define ILVGIFEXPORTED IL_BASEEXPORTED
#  define ILVGIFEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVGIFEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVGIFLIB */
#  define ILVGIFEXPORTED IL_BASEIMPORTED
#  define ILVGIFEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVGIFEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVGIFLIB */

// Static initialization macros
#define ILVGIFMODULEINIT(m) IL_MODULEINIT(m, ILVGIFEXPORTED)
#define ILVGIFMODULETERM(m) IL_MODULETERM(m, ILVGIFEXPORTED)

// --------------------------------------------------------------------------
class ILVGIFEXPORTED IlvGIFStreamer
: public IlvBitmapStreamer
{
public:
    IlvGIFStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    IlBoolean		isGIF87Transparent() const;
    void		setGIF87Transparent(IlBoolean transparent);
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data,
			      ILVSTDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    static IlSymbol*	_gif87transpValue;

protected:
    IlBoolean		_gif87Transparent;
};

IL_MODULETERM(gif, ILVGIFEXPORTED);
#endif /* __Ilv_Bitmaps_Gif_H */
