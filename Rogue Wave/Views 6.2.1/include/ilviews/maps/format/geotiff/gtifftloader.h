// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/geotiff/gtifftloader.h
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

#ifndef __ILV_maps_Format_geotiff_IlvGeoTIFFTileLoader_H
#define __ILV_maps_Format_geotiff_IlvGeoTIFFTileLoader_H

#include <ilviews/ilv.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/tiling/tile.h>
#include <ilviews/maps/format/geotiff/gtiffreader.h>
#include <ilviews/maps/format/maptloader.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/mapfeature.h>

ILVMAPSMODULEINIT(IlvGeoTIFFTileLoader);

class GeoTIFFReader;


class ILVMAPSEXPORTED IlvGeoTIFFTileLoader
    :public IlvMapTileLoader
{
private:
    IlvMapInfo* _mapinfo;
    char* _filename;
    IlvRect _tileOrigin;
    GeoTIFFReader* _iterator;
public:

    IlvGeoTIFFTileLoader(const char* filename,
			 const IlvMapAdapter* adapter);

    virtual ~IlvGeoTIFFTileLoader();

    virtual IlBoolean isPersistent() const;

    virtual IlvMapFeatureIterator* getFeatureIterator(IlvTile* tile);

    virtual IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay* display);

    virtual IlvMapInfo* getMapInfo();

    virtual IlvRect& getTileOrigin();

    IlvTilingDeclareIO(IlvGeoTIFFTileLoader);

private:
    IlvMapsIcFriend(IlvGeoTIFFTileLoader, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Format_geotiff_IlvGeoTIFFTileLoader_H */
