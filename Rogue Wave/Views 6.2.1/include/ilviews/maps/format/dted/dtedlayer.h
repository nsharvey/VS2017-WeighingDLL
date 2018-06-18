// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/dted/dtedlayer.h
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
// The DTED layer class header file
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Format_IlvDTEDLayer_H
#define __ILV_maps_Format_IlvDTEDLayer_H

#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/tiling/tilecache.h>

#ifdef IL_STD
#include <string>
using namespace std;
#else
#include <string.h>
#endif

ILVMAPSMODULEINIT(IlvDTEDLayer);

class ILVMAPSEXPORTED IlvDTEDLayer : public IlvTiledLayer
{
    friend class _IlvDTEDTileLoader;

public:
    IlvDTEDLayer(const char* dirName,
		 IlUInt level,
		 const IlvMapAdapter* adapter,
		 IlvTileCache* cache = 0);

    virtual ~IlvDTEDLayer();

    void		setRasterRenderer(IlvFeatureRenderer* renderer);

    const IlvFeatureRenderer* getRasterRenderer() const;

    IlString*		getFileName(IlInt row, IlInt column);

    const IlvMapAdapter* getAdapter();

    void		setAdapter(IlvMapAdapter* a);

    const IlString*	getDirName() { return _dirName; }

    IlvTilingDeclareLayerIO(IlvDTEDLayer);

private:
    void		initCase();
    static
    IlvDefaultTileCache* GetTileCache();
    static IlvRect	GetTileOrigin(const IlvMapAdapter* adapter);
    static IlvMapsError DirectoryError();

    IlUInt		_dtedLevel;
    IlString*		_dirName;
    IlvFeatureRenderer*	_renderer;
    IlBoolean		_lowerCase;
    IlBoolean		_caseInited;
    IlvMapAdapter*	_adapter;
    IlvTileLoader*	_tileLoader;
};

#endif /* __ILV_maps_Format_IlvDTEDLayer_H*/
