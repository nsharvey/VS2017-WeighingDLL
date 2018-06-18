// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shpreader.h
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


#ifndef __ILV_maps_Format_shapefile_IlvShapeSHPReader_H
#define __ILV_maps_Format_shapefile_IlvShapeSHPReader_H

#include <ilog/macros.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/attribute.h>
#include <ilviews/maps/attribute/doubleattr.h>
#include <ilviews/maps/attrprop.h>
#include <ilviews/maps/laiterator.h>
#include <ilviews/base/iostream.h>
#include <ilviews/maps/format/shapefile/shpindex.h>
#include <ilviews/maps/format/shapefile/shptype.h>

ILVMAPSMODULEINIT(format_IlvShapeSHPReader);

class ILVMAPSEXPORTED IlvShapeSHPReader
    : public IlvLookAheadFeatureIterator
{
private:
    IlvMapsError _initStatus; /** The initialization status */

    IlvMapInput  _input;      /** The map input */

    IlvShapeType  _shapeType;    /** The shape feature type */
    IlDouble      _ulx;          /** UL x coordinate of data */
    IlDouble      _uly;          /** UL y coordinate of data */
    IlDouble      _lrx;          /** LR x coordinate of data */
    IlDouble      _lry;          /** LR y coordinate of data */
    IlDouble      _zMin;         /** read from header */
    IlDouble      _zMax;         /** read from header */
    IlDouble      _mMin;         /** read from header */
    IlDouble      _mMax;         /** read from header */

    IlvFeatureAttributeInfo*     _attributeInfo;

    IlvMapFeature*               _feature;

    IlvProjection* _sourceProjection;
    IlInt _limit;
    IlvShapeFileIndex* _shxIndex;
    IlInt _nextFeatureId;
    IlvMapFeatureIntegerId* _integerId;

    static IlvMapsError _NoIndexFile;
    static IlvMapsError _IndexOutOfRange;
public:
    IlvShapeSHPReader(const char* fileName,
		      const char* shxName = 0);

    IlvShapeSHPReader(IL_STDPREF istream& stream);

    IlvShapeSHPReader(IL_STDPREF istream& shpStream,
		      IL_STDPREF istream& shxStream);

    virtual ~IlvShapeSHPReader();

    //---
    // Implementation of the feature iterator interface.
    //---
    IlvMapsError getInitStatus() const;

    IlBoolean getLowerRightCorner(IlvCoordinate& result) const;

    IlBoolean getUpperLeftCorner(IlvCoordinate& result) const;

    const IlvProjection* getProjection() const;

    void setSourceProjection(IlvProjection* projection);

    const IlvMapFeature* getNextFeature(IlvMapsError& status);

    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *display);

    IlvShapeType getShapeType() const { return _shapeType; } 


    IlvShapeFileIndex* getShapeFileIndex()
    {
	return _shxIndex;
    }

    //----------------

    const IlvFeatureAttributeInfo*
    getFeatureAttributeInfo(IlvMapsError& status) const;

    virtual const IlvMapFeature* getFeatureAt(IlInt index,
					      IlvMapsError& status);

    virtual IlBoolean skipNextFeature(IlvMapsError& status);


    virtual IlInt getNextFeatureIndex();

    virtual IlvMapFeatureId* getNextFeatureId(IlvMapsError& status);

    virtual void setNextFeatureIndex(IlInt index);

    IlvMapInput* getMapInput() { return &_input; }

protected:

    IlvMapInput& getInput() { return _input; }

    virtual void setInitStatus(IlvMapsError status);

    virtual IlvMapFeature* readPointShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolylineShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolygonShape(IlvMapsError& status);

    virtual IlvMapFeature* readMultiPointShape(IlvMapsError& status);

    virtual IlvMapFeature* readPointMShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolylineMShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolygonMShape(IlvMapsError& status);

    virtual IlvMapFeature* readMultiPointMShape(IlvMapsError& status);

    virtual IlvMapFeature* readPointZShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolylineZShape(IlvMapsError& status);

    virtual IlvMapFeature* readPolygonZShape(IlvMapsError& status);

    virtual IlvMapFeature* readMultiPointZShape(IlvMapsError& status);

private:
    static void InitStatic();
    void        initialize();
    void cleanOldFeature();

    IlvMapsError readHeader();
    IlvMapFeature* readRecordContents(IlvMapsError &status);
    IlvFeatureAttributeInfo* getAttributeInfo(IlvMapsError& status);
    IlBoolean checkForEndOfRecord(IlvMapFeature* feature);

    IlvMapFeatureIteratorDeclareClassInfo();
    IlvMapsIcFriend(format_IlvShapeSHPReader, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Format_shapefile_IlvShapeSHPReader_H */
