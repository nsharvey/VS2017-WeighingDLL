// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdolayer.h
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
// Declaration of IlvSDOLayer class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdolayer_H
#define __Ilv_Maps_Format_Oracle_Sdolayer_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/format/oracle/sdotileload.h>

class IlvSDOTileLoader;
class IlvFeatureRenderer;
class IlvTileListener;
class IlvMapAdapter;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDOLayer
    : public IlvTiledLayer
{
public:

    IlvSDOLayer(const IlvMapAdapter*	mapAdapter,
		IldDbms*		dbms,
		const char*		layerName,
		IlvTileCache*		cache = 0,
		const char*		password = 0);
    IlvSDOLayer(IlvSDOTileLoader* sdoTileLoader,
		IlvTileCache* cache,
		const char* password = 0);
    virtual ~IlvSDOLayer();

    inline void		setFeatureRenderer(IlvFeatureRenderer* renderer)
	{ _renderer = renderer; }
    IlvFeatureRenderer*	getFeatureRenderer() const;
    inline IldDbms*	getDbms() const { return _dbms; }
    inline IlvMapsError	getInitStatus() const { return _initStatus; }
    static IlvMapsError	DbmsUpdate(IldDbms* dbms,
				   const char* userName,
				   const char* oracleSidName,
				   const char* dblinkDriverName);

    IlvTilingDeclareLayerIO(IlvSDOLayer);

protected:
    IlvTileListener*			_listener;
    static IlvDefaultSDOTileLoader*	_DefaultTileLoader;
    IlvMapsError			_initStatus;

private:
    IlvSDOTileLoader*	getSDOTileLoader() const
	{ return (IlvSDOTileLoader*) getTileLoader(); }
    static IlvRect GetOrigin(const IlvMapAdapter*, const char*, IldDbms*);

    IldDbms*		_dbms; // Just for reconnection cases
    class InternalDbms;
    InternalDbms*	_internalDbms; // for IO purpose
    IlvFeatureRenderer*	_renderer;
};

ILVDBMAPSMODULEINIT(IlvSDOLayer);

#endif /* __Ilv_Maps_Format_Oracle_Sdolayer_H */
