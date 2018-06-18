// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shpindex.h
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
#ifndef __ILV_maps_Format_shapefile_IlvShapeFileIndex_H
#define __ILV_maps_Format_shapefile_IlvShapeFileIndex_H

#include <ilviews/macros.h>
#include <ilviews/base/iostream.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/coord.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/format/shapefile/shptype.h>

#ifndef IL_STD
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
IL_STDUSE
#endif

ILVMAPSMODULEINIT(IlvShapeFileIndex);


class ILVMAPSEXPORTED IlvShapeFileIndex
{
public:
    IlvShapeFileIndex(const char* shxFileName);

    IlvShapeFileIndex(IL_STDPREF istream& stream) ;

    virtual ~IlvShapeFileIndex();

    IlvMapsError	getInitStatus() const { return _initStatus;};

    IlBoolean		getLowerRightCorner(IlvCoordinate& result) const;

    IlBoolean		getUpperLeftCorner(IlvCoordinate& result) const;

    IlvMapsError	getRecordOffset(IlInt index, IlInt& offset);

    IlvMapsError	getRecordLength(IlInt index, IlInt& length);

    IlInt		getRecordCount() const
			{
			    return ((_fileLength - 50) / 4);
			};

protected:
    virtual void	setInitStatus(IlvMapsError status);

    const IlvMapInput&	getInput() const { return _input; }

private:
    IlvMapsError	readRecord(IlInt index);
    IlvMapsError	readHeader();

    IlvMapsIcFriend(IlvShapeFileIndex, ILVMAPSEXPORTED);

    IlvMapInput		_input;
    IlvMapsError	_initStatus;    
    IlDouble		_ulx;
    IlDouble		_uly;
    IlDouble		_lrx;
    IlDouble		_lry;
    IlDouble		_zMin;
    IlDouble		_zMax;
    IlDouble		_mMin;
    IlDouble		_mMax;
    IlvShapeType	_shapeType;
    IlInt		_currentIndex;
    IlInt		_currentOffset;
    IlInt		_currentLength;
    IlInt		_fileLength;
};

#endif /* __ILV_maps_Format_shapefile_IlvShapeFileIndex_H */
