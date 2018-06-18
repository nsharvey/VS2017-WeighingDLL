// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/geotiff/gtifflayer.h
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
// The GeoTIFF tiled layer class header file
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Format_IlvGeoTIFFLayer_H
#define __ILV_maps_Format_IlvGeoTIFFLayer_H

#include <ilviews/maps/format/geotiff/gtifftloader.h>
#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/tiling/tilecache.h>

ILVMAPSMODULEINIT(IlvGeoTIFFLayer);


class ILVMAPSEXPORTED IlvGeoTIFFLayer
    : public IlvTiledLayer
{    
private :
    IlvGeoTIFFTileLoader* _tileLoader;
public:

    IlvGeoTIFFLayer(IlvGeoTIFFTileLoader* tileLoader,
		    IlvTileCache* cache = 0);

    virtual ~IlvGeoTIFFLayer();

    IlvGeoTIFFTileLoader* getTileLoader() const
    {
	return _tileLoader;
    }

    IlvTilingDeclareLayerIO(IlvGeoTIFFLayer);    
};

#endif /* __ILV_maps_Format_IlvGeoTIFFLayer_H */

