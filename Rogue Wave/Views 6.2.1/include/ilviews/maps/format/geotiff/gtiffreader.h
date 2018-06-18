// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/geotiff/gtiffreader.h
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

#ifndef __ILV_maps_Format_geotiff_IlvGeoTIFFReader_H
#define __ILV_maps_Format_geotiff_IlvGeoTIFFReader_H

#include <ilviews/ilv.h>
#include <ilviews/maps/macros.h> 
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/bitmaps/streamer.h>
#include <ilviews/bitmaps/tiff.h>
#include <ilviews/maps/geometry/geoimage.h>
#include <ilviews/maps/tiling/tile.h>
#include <ilviews/maps/mapinfo.h>

#ifdef IL_STD
#include <iostream>
#include <fstream>
IL_STDUSE;
#else
#include <iostream.h>
#include <fstream.h>
#endif

ILVMAPSMODULEINIT(IlvGeoTIFFReader);


class ILVMAPSEXPORTED IlvGeoTIFFReader : public IlvMapFeatureIterator
{
public:
    IlvGeoTIFFReader(const char* filename);

    IlvGeoTIFFReader(IL_STDPREF istream& input);
    virtual ~IlvGeoTIFFReader();

    virtual
    const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& coordinate) const;

    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& coordinate) const;

    virtual
    IlvMapsError	getInitStatus() const {	return _status; }

    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay* display);

    virtual
    IlvBitmapData*	readTile(IlInt col, IlInt row);

    IlvTIFFStreamer*	getStreamer() const { return _tiffStreamer; }

    IlBoolean		isTiled() const;

    IlvRect&		getTileOrigin(IlvMapInfo* info);

    const IlvProjection* getProjection() const { return _projection; }

    void		setSourceProjection(IlvProjection* p);

    IlInt		getImageWidth() { return _imageWidth; }

    IlInt		getImageHeight() { return _imageHeight; }

    IlUInt		getTileWidth() { return _tileWidth; }

    IlUInt		getTileHeight() { return _tileHeight; }

    IlFloat		getXScale() { return _xScale; }

    IlFloat		getYScale() { return _yScale; }

    IlInt		getColumnCount();

    IlInt		getRowCount();

protected:

    virtual void	setInitStatus(IlvMapsError status);

    virtual
    IlvMapFeature*	getMapFeature();

private:
    void		info();

    IlvMapFeatureIteratorDeclareClassInfo();

    IlvMapsIcFriend(IlvGeoTIFFReader, ILVMAPSEXPORTED);

    char*		_filename;
    IlvMapsError	_status;
    IlvMapFeature*	_feature;
    IlBoolean		_alreadyDone;  
    IlvMapGeometry*	_geometry;    
    IlvMapImage*	_imageGeometry; 
    IlvProjection*	_projection;

    IlvCoordinate*	_upperLeft;
    IlvCoordinate*	_lowerRight;    

    istream&		_stream;

    IlvTIFFStreamer*	_tiffStreamer;

    IlBoolean		_isTiled;
    IlFloat		_xScale;
    IlFloat		_yScale;
    IlvRect		_tileOrigin;

    IlInt		_imageWidth;
    IlInt		_imageHeight;

    IlUInt		_tileWidth;
    IlUInt		_tileHeight;

    IlBoolean		_ownStream;
};

#endif /* __ILV_maps_Format_geotiff_IlvGeoTIFFReader_H */
