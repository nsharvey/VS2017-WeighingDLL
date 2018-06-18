// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shpfile.h
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
#ifndef __ILV_maps_Format_shapefile_IlvShapeFileReader_H
#define __ILV_maps_Format_shapefile_IlvShapeFileReader_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/attribute.h>
#include <ilviews/maps/attrprop.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/dbfreader.h>
#include <ilviews/maps/laiterator.h>

#include <ilviews/base/iostream.h>

ILVMAPSMODULEINIT(format_IlvShapeFileReader);


class ILVMAPSEXPORTED IlvShapeFileReader : public IlvLookAheadFeatureIterator
{
public:
    IlvShapeFileReader(const char* shpFileName,
		       const char* dbfFileName,
		       const char* shxFileName = 0);

    IlvShapeFileReader(IlvShapeSHPReader* shpReader,
		       IlvShapeDBFReader* dbfReader,
		       IlBoolean ownerOfReaders = IlFalse);

    IlvShapeFileReader(IlvShapeSHPReader* shpReader,
		       IlvShapeDBFReader* dbfReader,
		       IlvShapeFileIndex* shxIndex,
		       IlBoolean ownerOfReaders = IlFalse);

    virtual ~IlvShapeFileReader();

    IlvShapeSHPReader*	getSHPReader() { return _shpReader; }

    IlvShapeDBFReader*	getDBFReader() { return _dbfReader; }

    IlvShapeFileIndex*	getSHXReader() { return _shxReader; }

    IlBoolean		isLoadingAttributes() { return (_dbfReader != 0); }

    //---
    // Implementation of the feature iterator interface.
    //---

    IlvMapsError	getInitStatus() const;

    IlBoolean		getLowerRightCorner(IlvCoordinate &result) const;

    IlBoolean		getUpperLeftCorner(IlvCoordinate &result) const;

    const IlvProjection* getProjection() const;

    void		setSourceProjection(IlvProjection* projection);

    const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual
    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *display);

    virtual
    const IlvMapFeature* getFeatureAt(IlInt index, IlvMapsError& status);

    virtual
    IlvMapFeatureId*	getNextFeatureId(IlvMapsError& status);

    virtual IlBoolean	skipNextFeature(IlvMapsError& status);

protected:
    virtual void	setInitStatus(IlvMapsError status);

private:
    static void		InitStatic();
    void		initialize();
    void		init(IlvShapeSHPReader* shpReader,
			     IlvShapeDBFReader* dbfReader,
			     IlvShapeFileIndex* shxIndex,
			     IlBoolean ownerOfReaders);
    IlvFeatureAttributeProperty*
			mergeAttributes(const IlvMapFeature* feature,
					IlvFeatureAttributeProperty* atts,
					IlvMapsError& status);

    IlvMapFeatureIteratorDeclareClassInfo();
    IlvMapsIcFriend(format_IlvShapeFileReader, ILVMAPSEXPORTED);

    IlvShapeSHPReader*		_shpReader;
    IlvShapeDBFReader*		_dbfReader;
    IlvShapeFileIndex*		_shxReader;
    IlBoolean			_ownerOfReaders;
    IlvFeatureAttributeInfo*	_attributeInfo;
    IlvMapsError		_initStatus;

    static IlvMapsError		_NoIndexFile;
    static IlvMapsError		_IndexOutOfRange;

};

#endif /* __ILV_maps_Format_shapefile_IlvShapeFileReader_H */
