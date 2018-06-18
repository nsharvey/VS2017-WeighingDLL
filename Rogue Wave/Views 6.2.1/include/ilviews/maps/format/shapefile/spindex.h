// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/spindex.h
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
// ilog.views.maps.format.shapefile
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Format_shapefile_IlvShapeSpatialIndex_H
#define __ILV_maps_Format_shapefile_IlvShapeSpatialIndex_H

#include <ilviews/macros.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/coord.h>
#include <ilviews/base/iostream.h>
#include <ilviews/maps/format/shapefile/shpreader.h>

ILVMAPSMODULEINIT(IlvShapeSpatialIndex);

class TilePositionInfo;

class ILVMAPSEXPORTED IlvShapeSpatialIndex
{
public:
    IlvShapeSpatialIndex(IlInt columNum,
			 IlInt rowNum,
			 IlvCoordinate *origin,
			 IlDouble tileWidth,
			 IlDouble tileHeight);

    IlvShapeSpatialIndex(const char* indexFilename);

    virtual ~IlvShapeSpatialIndex();

    IlvMapsError	getIdArray(IlInt column,
				   IlInt row,
				   IlInt*& ret,
				   IlUInt& size);
    IlBoolean		add(IlInt c, IlInt r, IlInt id);

    inline IlInt	getColumnCount() const { return _numColumns; }
    inline IlInt	getRowCount() const { return _numRows; }

    inline IlvCoordinate* getOrigin() const { return _origin; }

    inline IlDouble	getTileWidth() const { return _tileWidth; }

    inline IlDouble	getTileHeight() const { return _tileHeight; }

    IlvMapsError	save(const char* filename);    

    inline IlvMapsError	getInitStatus() const { return _status; }

private:
    static void		InitStatic();

    IlvMapsIcFriend(IlvShapeSpatialIndex, ILVMAPSEXPORTED);

    IlvMapsError	_status;
    char*		_indexFilename;
    IlInt		_numColumns;
    IlInt		_numRows;
    IlvCoordinate*	_origin;
    IlDouble		_tileWidth;
    IlDouble		_tileHeight;
    TilePositionInfo**	_tiles;    

};

#endif /*__ILV_maps_Format_shapefile_IlvShapeSpatialIndex_H*/
