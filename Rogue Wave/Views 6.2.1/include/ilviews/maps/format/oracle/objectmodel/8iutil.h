// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/8iutil.h
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
// Declaration of the IlvObjectSDOUtil class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_8iutil_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_8iutil_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ilviews/maps/coord.h>

class IlvObjectSDOLayerMetaData;
class IlvObjectSDOLayer;
class IlvDefaultObjectSDOTileLoader;
class IlvObjectSDOWriter;
class IldRequest;
class _IlvMaps8iUtilErrorReporter;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvObjectSDOUtil
{
    //FLE friend class _SDOUtilErrorReporter;
    friend class IlvObjectSDOLayer;
    friend class IlvDefaultObjectSDOTileLoader;
    friend class IlvObjectSDOWriter;
public:
    static
    IlvMapsError	NoMetaDataError();

    static char**	GetAllLayers(IlUShort& layersCount,
				     IldDbms* dbms,
				     const char* ownerName,
				     IlBoolean concatenateGeometryName,
				     IlvMapsError& status);

    static IlBoolean	CheckMetadataTableExistence(IldDbms* dbms,
						    const char* ownerName,
						    IlvMapsError& status);

    static IlInt	GetGeometriesCount(IldDbms* dbms,
					   const char* tableName,
					   IlvMapsError& status);

    static IlBoolean	CheckTableExistence(IldDbms* dbms,
					    const char* layerName,
					    IlvMapsError& status);

    static void		DropLayer(IldDbms* dbms,
				  const char* layerName,
				  IlvMapsError& status);

    static void		GetLayerExtent(IldDbms* dbms,
				       const char* layerName,
				       const char* geometryColumnName,
				       const char* xDimensionName,
				       const char* yDimensionName,
				       IlBoolean useExtentOf,
				       IlvCoordinate& upperLeftCorner,
				       IlvCoordinate& lowerRightCorner,
				       IlvMapsError& status);

    static IlBoolean	CheckLayerExistence(IldDbms* dbms,
					    const char* layerName,
					    IlvMapsError& status);

    static IlBoolean	IsUsing816(IldDbms*, IlvMapsError&);

    static
    IldRequest*		GetRequestFromRect(IldDbms* dbms,
					   const char* layerName,
					   const char* geometryName,
					   const IlvCoordinate& upperLeft,
					   const IlvCoordinate& lowerRight,
					   IlvMapsError& status);

    static IlvObjectSDOLayerMetaData* GetLayerMetaData(IldDbms*,
						       const char*,
						       const char*,
						       IlvMapsError&);
private:
    // Cannot instantiate
    IlvObjectSDOUtil() {}

    static IlvObjectSDOLayerMetaData* GetMetaData(const char*,
						  IldRequest*,
						  IlvMapsError&);

    // Returns the owner name from specified layer name ("owner.table"),
    // where owner is optionnal.
    static IlString	GetOwnerName(IlString*);
    // Returns the table name from specified layer name ("owner.table"),
    // where owner is optionnal.
    static IlString	GetTableName(IlString*);
};

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_8iutil_H */
