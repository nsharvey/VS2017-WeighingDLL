// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdotileload.h
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
// Declaration of IlvSDOTileLoader and IlvDefaultSDOTileLoader classes
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdotileload_H
#define __Ilv_Maps_Format_Oracle_Sdotileload_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/tiling/tileloader.h>
#include <ilog/string.h>

class IlvSDOLayer;
class IlvSDOFeatureIterator;
class IlvMapAdapter;
class IlvMapInfo;
class IlvMapFeatureIterator;
class IldDbms;
class IldRequest;
class _IlvMapsQueryHandler;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDOTileLoader
    : public IlvTileLoader
{
    friend class IlvSDOLayer;
    friend class IlvObjectSDOLayer;
    friend class _IlvSDOLayerConnectionObserver;
    friend class _IlvMapsSDOTileLoaderErrorReporter;

public:
    virtual ~IlvSDOTileLoader();

    virtual
    const IlvRect&	getTileOrigin() const;
    virtual IldRequest*	getRequest(IlvTile* tile);
    virtual IlvRect*	getSize();
    virtual void	release(IlvTile* tile);
    inline IldDbms*	getDbms() const { return _dbms; }
    IlvMapsError	getInitStatus() const { return _initStatus; }
    virtual IlBoolean	isPersistent() const;
    virtual
    IlvMapsError	load(IlvTile* tile);
    virtual IlvMapsError dbmsRestored();

    IlvTilingDeclareIO(IlvSDOTileLoader);
protected:
    IlvSDOTileLoader(IldDbms* dbms);

    IldRequest*		executeQuery(const char* query);
    IldRequest*		executeQuery(const IlString&);

    IlvMapsError	loadObjectsFromIterator(IlvTile*,
						IlvMapFeatureIterator*);

    static
    IlvMapAdapter*	GetAdapter(const IlvMapAdapter*);
    void		setMapInfo(IlvMapInfo* mapinfo) { _mapinfo = mapinfo; }

    _IlvMapsQueryHandler*	_qHandler;
    IldDbms*			_dbms;
    IlvSDOFeatureIterator*	_iterator;
    IlvMapsError		_initStatus;
    IlvMapsError		_error;
    IlvMapInfo*			_mapinfo;
    IlvRegion			_tilesRegion;
    IlBoolean			_attachAttributes;

private:
    inline void		setPassword(const char* pass)
			{
			    _password = IlString(pass);
			}
    inline void		setDbms(IldDbms* dbms) { _dbms = dbms; }

    IlString		_password;
};

ILVDBMAPSMODULEINIT(IlvDefaultSDOTileLoader);

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvDefaultSDOTileLoader
    : public IlvSDOTileLoader
{
    friend class _IlvMapsSDOTileListener;
public:
    IlvDefaultSDOTileLoader(const IlvMapAdapter* mapadapter,
			    IldDbms*             dbms,
			    const char*          layerName);
    virtual ~IlvDefaultSDOTileLoader();

    inline const char*	getLayerName() { return _layerName.getValue(); }
    const IlvRect&	getTileOrigin() const;
    virtual IldRequest*	getRequest(IlvTile* tile);
    const char*		getSDOCode(IlvTile* tile);
    virtual
    IlvMapsError	load(IlvTile* tile);
    virtual IlvRect*	getSize();
    void		setTileGroupingCount(IlUShort nb);
    inline IlUShort	getTileGroupingCount() const { return _nbTilesToLoad; }
    virtual
    IlvMapsError	dbmsRestored();

    IlvTilingDeclareIO(IlvDefaultSDOTileLoader);
protected:
    IlvSDOFeatureIterator* getFeatureIterator(IldRequest* request,
					      IlvMapsError& status);
private:
    void		init();
    void		prepareDynamicRequest();

    IlString		_layerName;
    IlInt		_sdoTilingLevel;
    IlvRect		_size;
    IlvRect		_tileOrigin;
    IlInt		_columnCount;
    IlInt		_rowCount;
    IldRequest*		_dynRequest;
    IlString		_sdoCode;
    IlBoolean		_loadIt;
    IlUShort		_nbTilesToLoad;
};

ILVDBMAPSMODULEINIT(IlvSDOTileLoader);

#endif /* __Ilv_Maps_Format_Oracle_Sdotileload_H */
