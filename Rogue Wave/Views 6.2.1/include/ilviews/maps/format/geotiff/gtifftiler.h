// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/geotiff/gtifftiler.h
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
// Rogue Wave Views - Maps add-on.
// ilog.views.maps.format.geotiff
// Defined in library ilvmaps
// --------------------------------------------------------------------------


#ifndef __ILV_maps_Format_geotiff_IlvGeoTIFFTiler_H
#define __ILV_maps_Format_geotiff_IlvGeoTIFFTiler_H

#include <ilviews/ilv.h>
#include <ilviews/maps/maps.h>
#include <ilviews/bitmaps/tiff.h>

#ifndef IL_STD
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
IL_STDUSE
#endif

ILVMAPSMODULEINIT(format_IlvGeoTIFFTiler);


class ILVMAPSEXPORTED IlvGeoTIFFTiler
{
public:
    IlvGeoTIFFTiler(const char* input,
		    const char* output,
		    IlInt tileWidth,
		    IlInt tileHeight);

    IlvMapsError	performTiling(IlvTIFFStreamer& outStreamer);

    IlvMapsError	getInitStatus() const { return _status; }

    IlInt		getTileWidth() const { return _tileWidth; }

    IlInt		getTileHeight() const { return _tileHeight; }

    IlInt		getRowCount() const
			{
			    return _imageWidth / _tileWidth;
			}
    IlInt		getColumnCount() const
			{
			    return _imageHeight / _tileHeight;
			}
    void		setCompression(IlvTIFFStreamer::Compression c)
			{
			    _compression = c;
			}

    IlvTIFFStreamer::Compression getCompression() const
			{
			    return _compression;
			}

private:
    void		info();

    istream&		_in;
    ostream&		_out;
    IlInt		_tileWidth;
    IlInt		_tileHeight;
    IlvMapsError	_status;
    IlvTIFFStreamer::Compression _compression;    
    IlInt		_imageWidth;
    IlInt		_imageHeight;    

};

#endif /* __ILV_maps_Format_geotiff_IlvGeoTIFFTiler_H */
