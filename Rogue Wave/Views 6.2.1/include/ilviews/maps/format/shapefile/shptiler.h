// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shptiler.h
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

#ifndef __ILV_maps_Format_shapefile_IlvShapeFileTiler_H
#define __ILV_maps_Format_shapefile_IlvShapeFileTiler_H

#include <ilviews/macros.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/coord.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/spindex.h>

ILVMAPSMODULEINIT(IlvShapeFileTiler);

class BBoxReader;


class ILVMAPSEXPORTED IlvShapeFileTiler
{
private:
    IlDouble _tileWidth;
    IlDouble _tileHeight;
    IlInt _count;
    BBoxReader* _bboxReader;    
    IlInt _numRows;
    IlInt _numColumns;
    IlvCoordinate* _origin;
    IlvShapeSHPReader* _shpReader;
    IlvShapeSpatialIndex* _tileInfo;
    IlInt _maxCount;
    char* _targetFilename;
    IlDouble _width;
    IlDouble _height;
    IlvMapsError _status;

public:
    IlvShapeFileTiler(const char* shpFilename,
		      const char* shxFileName,
		      const char* targetFileName,
		      IlDouble tileWidth,
		      IlDouble tileHeight);

    IlvShapeFileTiler(const char* shpFilename,
		      const char* shxFileName,
		      const char* targetFileName,
		      IlInt numColumns,
		      IlInt numRows);

    virtual ~IlvShapeFileTiler();

    IlBoolean getUpperLeftCorner(IlvCoordinate& c) const {
	return _shpReader->getUpperLeftCorner(c);
    }

    IlBoolean getLowerRightCorner(IlvCoordinate& c) const {
	return _shpReader->getLowerRightCorner(c);
    }

    static IlvMapsError CreateShapeSpatialIndex(const char* shpFilename,
						const char* targetFileName,     
						IlInt numColumns,
						IlInt numRows);

    static IlvMapsError CreateShapeSpatialIndex(const char* shpFilename,
					const char* targetFileName,     
					IlDouble tileWidth,
					IlDouble tileHeight);


    void addInfo();


    const IlvMapFeature* getNextFeature();


    void close();

    IlvCoordinate* getOrigin() const {
	return _origin;
    }

    IlDouble getTileWidth() const {
	return _tileWidth;
    }

    IlDouble getTileHeight() const {
	return _tileHeight;
    }

    IlInt getColumnCount() const {
	return _numColumns;
    }

    IlInt getRowCount() const {
	return _numRows;
    }

    IlInt getCurrentCount() const {
	return _count;
    }

    IlInt getFeatureCount() const {
	return _maxCount;
    }

    IlvMapsError getStatus() const {
	return _status;
    }

protected:
    void setStatus(IlvMapsError status) {
	_status = status;
    }

private:
    IlvMapsError
    init(const char* shpFilename,
	 const char* shxFileName,
	 const char* targetFileName);

    IlvMapsIcFriend(IlvShapeFileTiler, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Format_shapefile_IlvShapeFileTiler_H */
