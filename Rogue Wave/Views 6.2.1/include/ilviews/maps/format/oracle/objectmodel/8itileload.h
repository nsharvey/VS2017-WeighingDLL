// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/8itileload.h
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
// Declaration of the IlvDefaultObjectSDOTileLoader class
// Defined in library ilvdbmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_8itileload_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_8itileload_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/format/oracle/sdotileload.h>
#include <ilviews/maps/coord.h>

class IlvObjectSDOLayerMetaData;
class IlvObjectSDOKeyExtractor;
class IlvObjectSDOFeatureIterator;
class IldDbms;
class _IlvMaps8iTileListener;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvDefaultObjectSDOTileLoader
    : public IlvSDOTileLoader
{
    friend class _IlvMaps8iTileListener;
public:

    IlvDefaultObjectSDOTileLoader(const IlvMapAdapter* mapAdapter,
				  IldDbms* dbms,
				  const char* tableName,
				  const char* geometryColumnName,
				  IlDouble tileWidth,
				  IlDouble tileHeight,
				  const char* xDimensionName = 0,
				  const char* yDimensionName = 0,
				  const char* keyColumnName = 0,
				  const IlvCoordinate* upperLeft = 0,
				  const IlvCoordinate* lowerRight = 0);

    virtual ~IlvDefaultObjectSDOTileLoader();

    inline const char*	getLayerName() { return _layerName.getValue(); }
    virtual
    const IlvRect&	getTileOrigin() const;
    virtual IldRequest* getRequest(IlvTile* tile);
    virtual IlvRect*	getSize();

    inline void		setClippingRequest(IlBoolean set)
			{
			    _clipRequest = set;
			}
    inline IlBoolean	isClippingRequest() const { return _clipRequest; }

    virtual IlvObjectSDOFeatureIterator*
	getFeatureIterator(IldRequest* request,
			   const char* geometryColumnName,
			   IlvObjectSDOKeyExtractor* keyExtractor,
			   const char* xDimensionName,
			   const char* yDimensionName,
			   IlvMapsError& error);

    virtual IlvMapsError
	setRequestParameters(const char* selectClause = "*",
			     const char* fromClause = 0,
			     const char* whereClause = 0,
			     const char* spatialOperator = "mdsys.sdo_filter",
			     const char* spatialOperatorParams = "querytype=window",
			     IlUInt colArraySize = 10);
    char**		getRequestParameters() const;

    inline IlUInt	getColArraySize() const { return _colArraySize; }

    virtual
    IlvMapsError	load(IlvTile* tile);

    void		setTileGroupingCount(IlUShort nb);

    inline IlUShort	getTileGroupingCount() const { return _nbTilesToLoad; }

    virtual
    IlvMapsError	dbmsRestored();

    IlvTilingDeclareIO(IlvDefaultObjectSDOTileLoader);

private:
    void		init(IlDouble, IlDouble);
    IlvMapsError	prepareDynamicRequest();
    static IlvRect	ComputeTileOrigin(IlvMapInfo*,
					  IlvObjectSDOLayerMetaData*,
					  const char*,
					  const char*,
					  IlDouble,
					  IlDouble,
					  IlvMapsError&);

    IlvMapsError                 _error;
    IlvRect                      _tileOrigin;
    IlvRect                      _size;
    IlvObjectSDOLayerMetaData*   _layerMetaData;
    IlString                     _xDimName;
    IlString                     _yDimName;
    IldRequest*                  _dynRequest;
    IlString                     _layerName;
    IlString                     _geomColName;
    IlDouble                     _tileWidth;
    IlDouble                     _tileHeight;
    IlvObjectSDOKeyExtractor*    _keyExtractor;
    IlvObjectSDOFeatureIterator* _iterator;
    _IlvMaps8iTileListener*      _listener;
    IlBoolean                    _loadIt;
    IlUShort                     _nbTilesToLoad;
    IlBoolean                    _is816;
    IlBoolean                    _clipRequest;
    IlUInt                       _colArraySize;
    IlString                     _selectClause;
    IlString                     _fromClause;
    IlString                     _whereClause;
    IlString                     _spatialOperator;
    IlString                     _spatialOperatorParams;
};

ILVDBMAPSMODULEINIT(8itileload);

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_8itileload_H */
