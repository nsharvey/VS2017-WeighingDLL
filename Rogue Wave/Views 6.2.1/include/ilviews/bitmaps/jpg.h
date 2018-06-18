// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/jpg.h
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
// Declaration of JPG bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Jpg_H
#define __Ilv_Bitmaps_Jpg_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvjpg.lib")
#endif

#if defined(ILVJPGLIB)
#  define ILVJPGEXPORTED IL_BASEEXPORTED
#  define ILVJPGEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVJPGEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVJPGLIB */
#  define ILVJPGEXPORTED IL_BASEIMPORTED
#  define ILVJPGEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVJPGEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVJPGLIB */

// Static initialization macros
#define ILVJPGMODULEINIT(m) IL_MODULEINIT(m, ILVJPGEXPORTED)
#define ILVJPGMODULETERM(m) IL_MODULETERM(m, ILVJPGEXPORTED)

// --------------------------------------------------------------------------
class ILVJPGEXPORTED IlvJPGStreamer : public IlvBitmapStreamer
{
public:
    IlvJPGStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    void		setQuality(IlUInt quality);
    IlUInt		getQuality() const;
    void		setProgressive(IlBoolean progressive);
    IlBoolean		isProgressive() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, ILVSTDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    static IlSymbol*	_qualityValue;
    static IlSymbol*	_progressiveValue;

protected:
    IlUInt		_quality;
    IlBoolean		_progressive;
};

IL_MODULETERM(jpg, ILVJPGEXPORTED);
#endif /* __Ilv_Bitmaps_Jpg_H */
