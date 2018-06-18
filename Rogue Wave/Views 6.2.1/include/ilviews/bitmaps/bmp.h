// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/bmp.h
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
// Declaration of BMP bitmap streaming utilities in IlogViews
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Bmp_H
#define __Ilv_Bitmaps_Bmp_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvbmp.lib")
#endif

#if defined(ILVBMPLIB)
#  define ILVBMPEXPORTED IL_BASEEXPORTED
#  define ILVBMPEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVBMPEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVBMPLIB */
#  define ILVBMPEXPORTED IL_BASEIMPORTED
#  define ILVBMPEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVBMPEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVBMPLIB */

// Static initialization macros
#define ILVBMPMODULEINIT(m) IL_MODULEINIT(m, ILVBMPEXPORTED)
#define ILVBMPMODULETERM(m) IL_MODULETERM(m, ILVBMPEXPORTED)

// --------------------------------------------------------------------------
class ILVBMPEXPORTED IlvBMPStreamer : public IlvBitmapStreamer
{
public:
    IlvBMPStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data,
			      ILVSTDPREF ostream& stream);

    IlvDeclareClassInfo();

protected:
    void		loadDIB1(ILVSTDPREF istream& stream, 
				 IlvBitmapData* bitmapdata);
    void		loadDIB4(ILVSTDPREF istream& stream, 
				 IlUInt compression, 
				 IlvBitmapData* bitmapdata);
    void		loadDIB8(ILVSTDPREF istream& stream, 
				 IlUInt compression, 
				 IlvBitmapData* bitmapdata);
    void		loadDIB16(ILVSTDPREF istream& stream,
				  IlvBitmapData* bitmapdata);
    void		loadDIB24(ILVSTDPREF istream& stream,
				  IlvBitmapData* bitmapdata);
    void		loadDIB32(ILVSTDPREF istream& stream,
				  IlvBitmapData* bitmapdata);
    IlUInt		_width;
    IlUInt		_height;
    IlUChar*		_data;
};

IL_MODULETERM(bmp, ILVBMPEXPORTED);
#endif /* __Ilv_Bitmaps_Bmp_H */
