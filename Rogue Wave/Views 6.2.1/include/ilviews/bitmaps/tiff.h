// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/tiff.h
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
// Declaration of TIFF bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Tiff_H
#define __Ilv_Bitmaps_Tiff_H

#if !defined(__Ilv_Bitmaps_Streamer_H)
#include <ilviews/bitmaps/streamer.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvtiff.lib")
#endif

#if defined(ILVTIFFLIB)
#  define ILVTIFFEXPORTED IL_BASEEXPORTED
#  define ILVTIFFEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVTIFFEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVTIFFLIB */
#  define ILVTIFFEXPORTED IL_BASEIMPORTED
#  define ILVTIFFEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVTIFFEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVTIFFLIB */

// Static initialization macros
#define ILVTIFFMODULEINIT(m) IL_MODULEINIT(m, ILVTIFFEXPORTED)
#define ILVTIFFMODULETERM(m) IL_MODULETERM(m, ILVTIFFEXPORTED)

// --------------------------------------------------------------------------
class ILVTIFFEXPORTED IlvTIFFStreamer : public IlvBitmapStreamer
{
public:
    enum Mode {
	Tile,
	Strip
    };
    enum Compression {
	None,
	Packbits,
	Zip,
	Lzw
    };
    IlvTIFFStreamer();
    IlBoolean		canRead() const;
    IlBoolean		canWrite() const;
    IlBoolean		checkSignature(const IlUChar* data, IlUInt size);
    IlvBitmapData*	read(ILVSTDPREF istream& stream); 
    IlvBitmapData*	readTile(ILVSTDPREF istream& stream,
				 IlUShort x,
				 IlUShort y); 
    IlvBitmapInformation*	readInfo(ILVSTDPREF istream& stream); 
    IlBoolean		write(IlvBitmapData* data, ILVSTDPREF ostream& stream);

    DeclareValueAccessors();
    IlvDeclareClassInfo();

    void		setTileWidth(IlUInt tilewidth);
    void		setTileHeight(IlUInt tileheight);
    void		setRowsPerStrip(IlUInt rowsperstrip);
    inline IlUInt	getTileWidth() const { return _tilewidth; }
    inline IlUInt	getTileHeight() const { return _tileheight; }
    inline IlUInt	getRowsPerStrip() const { return _rowsperstrip; }
     void		setWriteMode(Mode mode);
    inline Mode		getWriteMode() const { return _writemode; }
    void		setCompression(Compression compression);
    inline Compression	getCompression() const { return _compression; }
    virtual IlAny	openStream(ILVSTDPREF istream& stream);
    virtual void	closeStream(IlAny identifier);
    IlBoolean		getTagValue(IlAny identifier,
				    IlUInt tag, 
				    IlUInt& count,
				    IlAny value = 0);
    virtual void	writeCustomData(IlAny identifier);
    IlBoolean		writeTagValue(IlAny identifier,
				      IlUInt tag, 
				      IlUInt count,
				      IlAny value = 0);
protected:

    IlUInt		_tilewidth;
    IlUInt		_tileheight;
    IlUInt		_rowsperstrip;
    Mode		_writemode;
    Compression		_compression;
};

IL_MODULETERM(tiff, ILVTIFFEXPORTED);
#endif /* __Ilv_Bitmaps_Tiff_H */
