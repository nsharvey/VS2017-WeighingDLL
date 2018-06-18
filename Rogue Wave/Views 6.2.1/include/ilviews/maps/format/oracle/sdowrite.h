// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdowrite.h
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
// Declaration of the IlvSDOWriter class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdowrite_H
#define __Ilv_Maps_Format_Oracle_Sdowrite_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/geometry/geopoint.h>
#include <ilviews/maps/maps.h>
#include <ilog/string.h>

class IlvCoordinate;
class IlvMapGeometry;
class IlvMapCoordinateVector;
class IlvMapFeature;
class IlvMapFeatureIterator;
class IldDbms;
class IldRequest;
class _IlvMapsQueryHandler;
class _IlvMapsSDOWriterErrorReporter;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDOWriter
{
    friend class _IlvMapsSDOWriterErrorReporter;
public:
    IlvSDOWriter(IldDbms* dbms,
		 const char* layerName,
		 IlInt firstGidValue);
    IlvSDOWriter(IldDbms*		dbms,
		 const char*		layerName,
		 IlInt			sdoGeomCoordinatesCount,
		 const IlvCoordinate&	upperLeftBound,
		 const IlvCoordinate&	lowerRightBound);
    virtual ~IlvSDOWriter();

    virtual
    IlvMapsError	getInitStatus() const { return _initStatus; }

    IlvMapsError	getSdoGeomOrdinatesCount(IlInt&);

    inline const char*	getLayerName() const { return _layerName.getValue(); }

    inline IldDbms*	getDbms() const;

    virtual
    IlvMapsError	writeFeature(const IlvMapFeature* feature);

    virtual
    IlvMapsError	writeFeatureIterator(IlvMapFeatureIterator* reader,
					     IlInt& count);

    virtual
    IlvMapsError	populateIndexes(IlUShort tilingLevel);

protected:

private:
    static IlvMapsError	_unrecognizedGeometryError;

    static void		InitStatic();

    // Returns the owner name from specified layer name ("owner.table"),
    // where owner is optionnal.
    static IlString	GetOwnerName(IlString*);
    // Returns the table name from specfied layer name ("owner.table"),
    // where owner is optionnal.
    static IlString	GetTableName(IlString*);

    void		init();
    IldRequest*		executeQuery(IlString*);
    IldRequest*		executeQuery(const IlString&);
    void		commit();
    void		fillSDOLayerTable(IlUShort tilingLevel);
    void		fillSDODimTable(const IlvCoordinate&,
					const IlvCoordinate&);
    void		createSDOIndexTable();
    void		createSdoTables(IlInt,
					const IlvCoordinate&,
					const IlvCoordinate&);

    void		addPolygonOrLineString(const IlvMapGeometry*);

    void executeMultiPointDynamicRequest(IlInt,
					 const IlvMapCoordinateVector*);
    void		addPoint(const IlvCoordinate&);
    inline void		addPoint(IlvMapPoint* point)
			{
			    addPoint(point->getPoint());
			}

    _IlvMapsSDOWriterErrorReporter*	_errReporter;
    IlvMapsError			_error;
    IlvMapsError			_initStatus;
    IlInt				_gid;
    IlString				_layerName;
    IlString				_ownerName;
    _IlvMapsQueryHandler*		_qHandler;
    IldRequest*				_rqInit;
    IldRequest*				_rqAddNodes;
};

#endif /* __Ilv_Maps_Format_Oracle_Sdowrite_H */
