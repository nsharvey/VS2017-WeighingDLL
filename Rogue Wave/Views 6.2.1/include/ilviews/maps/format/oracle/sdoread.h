// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdoread.h
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
// Declaration of the IlvSDOFeatureIterator class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdoread_H
#define __Ilv_Maps_Format_Oracle_Sdoread_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/dftrenderer.h>
#include <ilog/string.h>

class IlvMapFeature;
class IlvMapSegmentRing;
class IlvMapPoint;
class IlvMapLineString;
class IlvMapPolygon;
class IlvDisplay;
class IlvDefaultSDOTileLoader;
class IldDbms;
class IldRequest;
class _IlvMapsQueryHandler;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDOFeatureIterator
    : public IlvMapFeatureIterator
{
    friend class _IlvMapsSDOReaderErrorReporter;
    friend class IlvDefaultSDOTileLoader;
public:

    IlvSDOFeatureIterator(IldRequest* resultSet);
    IlvSDOFeatureIterator(IldDbms* dbms, const char* query);
    virtual ~IlvSDOFeatureIterator();

    virtual
    IlvFeatureRenderer*	getDefaultFeatureRenderer(IlvDisplay*);

    const IlvProjection* getProjection() const { return _projection; }
    void		setSourceProjection(IlvProjection* projection);

    IlBoolean		isGeoreferenced() const
	{ return (getProjection() != 0); }

    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& coord) const;
    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& coord) const;

    virtual
    const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual
    IlvMapFeatureId*	getNextFeatureId(IlvMapsError& status);

    virtual IlBoolean	skipNextFeature(IlvMapsError& status);

    IlvMapsError	getInitStatus() const;

    static IlvMapsError	BadRequestError();

    static IlvMapsError	NoMoreRowError();

protected:
    // Internal use only
    void		setRequest(IldRequest*);

private:
    static IlString	_default_x;
    static IlString	_default_y;

    IlvSDOFeatureIterator(IldRequest*, const char*,  const char*);

    void		extractPoints(IlvMapLineString*,
				      IlBoolean = IlTrue);

    IlInt		getSdoGeomOrdinatesCount();
    void		init();

    IlvMapsError		_error;
    IlvMapsError		_initStatus;
    IlBoolean			_fetchHasBeenCalled;
    IlBoolean			_hasNextRow;
    IldRequest*			_request;
    IlString			_xColName;
    IlString			_yColName;
    IlInt			_ordinatesCount;
    _IlvMapsQueryHandler*	_qHandler;
    IlvMapFeature*		_feature;
    IlvMapSegmentRing*		_ring;
    IlvMapPoint*		_point;
    IlvMapLineString*		_line;
    IlvMapPolygon*		_polygon;
    IlvProjection*		_projection;
    IlvMapFeatureIntegerId*	_featureId;

    IlvMapFeatureIteratorDeclareClassInfo();
};

#endif /* __Ilv_Maps_Format_Oracle_Sdoread_H */
