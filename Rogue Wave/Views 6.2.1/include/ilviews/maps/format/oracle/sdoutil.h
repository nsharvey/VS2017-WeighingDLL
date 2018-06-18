// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdoutil.h
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
// Declaration of the IlvSDOUtil class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdoutil_H
#define __Ilv_Maps_Format_Oracle_Sdoutil_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/maps.h>

class IlvObjectSDOUtil;
class IlvSDODbmsFactory;
class IldDbms;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDOUtil
{
    friend class _IlvMapsSDOUtilErrorReporter;
    friend class _IlvMaps8iUtilErrorReporter;
    friend class IlvObjectSDOUtil;

public:
    static IlvMapsError DbLinkError();
    static const char*	LAYER_EXTENT;
    static const char*	ALL_GID_EXTENT;
    static const char*	AVERAGE_GID_EXTENT;

    static void		EnableSQLTraces(IL_STDPREF ostream* stream);
    static void		DisableSQLTraces();
    inline static
    IL_STDPREF ostream*	GetTraceStream() { return _traceStream; }
    inline
    static IlBoolean	SQLTracesEnabled() { return _SQLTracesEnabled; }

    static void		DropLayer(IldDbms* dbms,
				  const char* layerName,
				  IlvMapsError& status);
    static char**	GetAllLayers(IlUShort& layersCount,
				     IldDbms* dbms,
				     const char* ownerName,
				     IlvMapsError& status);
    static IlUShort	EstimateTilingLevel(IldDbms* dbms,
					    const char* layerName,
					    const char* typeOfEstimate,
					    IlInt maxTiles,
					    IlvMapsError& status);
    static IlBoolean	CheckSdoExistence(IldDbms* dbms,
					  IlvMapsError& status);
    static IlInt	GetGeometriesCount(IldDbms* dbms,
					   const char* layerName,
					   IlvMapsError& status);
    static IlBoolean	CheckLayerExistence(IldDbms* dbms,
					    const char* layerName,
					    IlvMapsError& status);

    static
    IlvSDODbmsFactory*	GetDbmsFactory();
    inline
    static void		SetDbmsFactory(IlvSDODbmsFactory* factory)
	{ _dbmsFactory = factory; }

    static void		SetLastDbErrorMessage(const char* message);
    static void		SetLastDbErrorQuery(const char* query);
    static void		SetLastDbErrorCode(IlInt code);
    static const char*	GetLastDbErrorMessage();
    static const char*	GetLastDbErrorQuery();
    static IlInt	GetLastDbErrorCode();
    static void		ResetLastDbError();
    static IlvMapsError	EnableDbLink();

private:
    IlvSDOUtil() {}

    // Returns the owner name from specified layer name ("owner.table"),
    // where owner is optionnal.
    static IlString	GetOwnerName(IlString*);
    // Returns the table name from specfied layer name ("owner.table"),
    //  where owner is optionnal.
    static IlString	GetTableName(IlString*);

    static IlBoolean		_SQLTracesEnabled;
    static IL_STDPREF ostream*	_traceStream;
    static IlString		_errMessage;
    static IlString		_errQuery;
    static IlInt		_errCode;
    static IlvSDODbmsFactory*	_dbmsFactory;
    // Internal error that can happen when executing internal queries
    // Used for returned statuses :
    static IlvMapsError		_error;
};

#endif /* __Ilv_Maps_Format_Oracle_Sdoutil_H */
