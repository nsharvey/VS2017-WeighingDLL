// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/image/imgtloader.h
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
// ilog.views.maps.format.image
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Format_image_IlvImageTileLoader_H
#define __ILV_maps_Format_image_IlvImageTileLoader_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/format/maptloader.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/tiling/tile.h>
#include <ilviews/maps/tiling/tileloader.h>
#include <ilviews/maps/rendering/imagerdr.h>

ILVMAPSMODULEINIT(IlvImageTileLoader);

class ILVMAPSEXPORTED IlvImageTileLoader : public IlvMapTileLoader
{
public:
  IlvImageTileLoader(IlvDisplay* display,
		     const char* pattern,
		     const char* colFormat,
		     const char* rowFormat,
		     const IlvMapAdapter* adapter);    

    virtual ~IlvImageTileLoader();

    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *display);

    virtual
    IlvMapFeatureIterator* getFeatureIterator(IlvTile* tile);

    virtual IlBoolean	isPersistent() const;

    IlvMapInfo*		getMapInfo();

    virtual const char*	getFileName(IlvTile* tile);

    const char*		getPattern() const { return _pattern; }

    const char*		getColFormat() const { return _colFormat; }

    const char*		getRowFormat() const { return _rowFormat; }

    IlvTilingDeclareIO(IlvImageTileLoader);

private:
    void		initIndex();

    IlvMapsIcFriend(IlvImageTileLoader, ILVMAPSEXPORTED);

    IlvDisplay*		_display;
    char*		_pattern;
    IlvRect		_rect;
    char*		_colFormat;
    char*		_rowFormat;
    IlvMapInfo*		_mapinfo;
};

#endif
