// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/8iread.h
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
// Declaration of the IlvObjectSDOFeatureIterator class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_8iread_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_8iread_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/dftrenderer.h>
#include <ilviews/maps/geometry/all.h>

class IlvFeatureAttributeProperty;
class IlvFeatureAttributeInfo;
class IlvObjectSDOKeyExtractor;
class IlvDefaultObjectSDOTileLoader;
class IlvProjection;
class IlvMapFeature;
class IldRequest;
class IldADTValue;
class _IlvMapsQueryHandler;
class _IlvMaps8iSDOReaderErrorReporter;
class _IlvMaps8iElemInfoIterator;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvObjectSDOFeatureIterator
    : public IlvMapFeatureIterator
{
    friend class _IlvMaps8iSDOReaderErrorReporter;
    friend class IlvDefaultObjectSDOTileLoader;

public:

    IlvObjectSDOFeatureIterator(IldDbms* dbms,
				const char* request,
				const char* geometryName = "GEOMETRY",
				const char* keyColumnName = 0,
				const char* xDimensionName = 0,
				const char* yDimensionName = 0);

    IlvObjectSDOFeatureIterator(IldRequest* request,
				const char* geometryName = "GEOMETRY",
				const char* keyColumnName = 0,
				const char* xDimensionName = 0,
				const char* yDimensionName = 0);

    IlvObjectSDOFeatureIterator(IldRequest* request,
				const char* geometryName,
				IlvObjectSDOKeyExtractor* keyExtractor,
				const char* xDimensionName = 0,
				const char* yDimensionName = 0);

    virtual ~IlvObjectSDOFeatureIterator();

    virtual
    IlvMapsError	getInitStatus() const;

    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& coord) const;
    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& coord) const;

    const IlvProjection* getProjection() const;
    IlBoolean		isGeoreferenced() const
	{ return (getProjection() != 0); }

    virtual
    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay*);

    IlBoolean		isLoadingAttributes() const
	{ return _isLoadingAttributes; }
    void		setLoadingAttributes(IlBoolean loadAttributes)
	{ _isLoadingAttributes = loadAttributes; }

    void		setSourceProjection(IlvProjection* projection);

    virtual
    const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual
    IlvMapFeatureId*	getNextFeatureId(IlvMapsError& status);

    virtual IlBoolean	skipNextFeature(IlvMapsError& status);

    void		setRequest(IldRequest* request);

    IlvMapFeatureIteratorDeclareClassInfo();

protected:
    virtual
    IlvMapGeometry*	makeGeometry(IldADTValue* geomADT,
				     IlvMapsError& status);

    virtual
    IlvFeatureAttributeProperty* makeAttributes(IldRequest* req,
						IlvMapsError& status);

    void		processSegmentString(_IlvMaps8iElemInfoIterator*,
					     IldADTValue*,
					     IlvMapSegmentString*,
					     IlvMapsError&);
    void		processPolygonString(_IlvMaps8iElemInfoIterator*,
					     IldADTValue*,
					     IlvMapPolygon*,
					     IlvMapsError&,
					     IlBoolean = IlFalse);
    void		processCircleString(_IlvMaps8iElemInfoIterator*,
					    IldADTValue*, IlvMapCircle*,
					    IlvMapsError&);
    virtual
    IlvMapGeometry*	makePointGeometry(IldADTValue*, IlvMapsError&);
    virtual
    IlvMapGeometry*	makeSegmentStringGeometry(IldADTValue*,
						  IlvMapsError&);
    virtual
    IlvMapGeometry*	makePolygonGeometry(IldADTValue*, IlvMapsError&,
					    IlBoolean = IlFalse);
    virtual
    IlvMapGeometry*	makeCircleGeometry(IldADTValue*, IlvMapsError&);
    virtual
    IlvMapGeometry*	makeMultiPointGeometry(IldADTValue*, IlvMapsError&);
    virtual
    IlvMapGeometry*	makeMultiSegmentStringGeometry(IldADTValue*,
						       IlvMapsError&);
    virtual
    IlvMapGeometry*	makeMultiAreaGeometry(IldADTValue*, IlvMapsError&);
    virtual
    IlvMapGeometry*	makeCollectionGeometry(IldADTValue*, IlvMapsError&);
    virtual void	makeAttributeInfo(IldRequest*, IlvMapsError&);

private:
    void		initElemInfoIterator(IldADTValue*);
    void		init(const char*, const char*, const char*);
    void		initMembers();
    void		computeGeometryColumnIndex(const char*,
						   IlvMapsError&);
    void		computeDimsIndex(const char*,
					 const char*,
					 const char*,
					 IlvMapsError&);

    _IlvMapsQueryHandler*        _qHandler;
    IldRequest*                  _request;
    IlvProjection*               _projection;
    IlvMapFeature*               _feature;
    IlvMapsError                 _error;
    IlvMapsError                 _initStatus;
    _IlvMaps8iElemInfoIterator*  _elemInfoIterator;
    _IlvMaps8iSDOReaderErrorReporter* _errRep;
    IlBoolean                    _isVolatile;

    IlShort                      _geometryColumnIndex;
    IlInt                        _coordDim;
    IlInt                        _xDimIndex;
    IlInt                        _yDimIndex;

    IlvFeatureAttributeInfo*     _attributeInfo;
    IlvFeatureAttributeProperty* _attributeProperty;
    IlList*                      _decoders;
    IlBoolean                    _isLoadingAttributes;

    // variables to manage object id
    IlvObjectSDOKeyExtractor*    _keyExtractor;
    IlvMapFeatureId*             _nextFeatureId;
    IlBoolean                    _nextFeatureIdFetched;
    // volatile point geometries
    IlvCoordinate                _singleCoordinate;
    IlvMapPoint*                 _pointGeometry;
    IlvMapMultiPoint*            _multiPointGeometry;
    // volatile line geometries
    IlvMapLineString*            _lineStringGeometry;
    IlvMapArcString*             _arcStringGeometry;
    IlvMapCurveString*           _curveStringGeometry;
    IlvMapMultiCurve*            _multiCurveGeometry;
    // volatile polygon geometries
    IlvMapCircle*                _circleGeometry;
    IlvMapPolygon*               _polygonGeometry;
    IlvMapMultiArea*             _multiPolygonGeometry;
    // volatile collection
    IlvMapGeometryCollection*    _collectionGeometry;
};

ILVDBMAPSMODULEINIT(IlvObjectSDOFeatureIterator);

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_8iread_H */
