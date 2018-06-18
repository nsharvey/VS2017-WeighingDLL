// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/tiling/tiledlayer.h
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
// Definition of the IlvTiledLayer class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_tiling_IlvTiledLayer_H
#define __ILV_tiling_IlvTiledLayer_H

#include <ilviews/maps/macros.h>
#include <ilviews/manager/layer.h>
#include <ilviews/maps/tiling/tilectrl.h>
#include <ilviews/maps/featureid.h>

class ILVMAPSEXPORTED IlvTileController;
class ILVMAPSEXPORTED IlvMapIncrementalPalette;

ILVMAPSMODULEINIT(IlvTiledLayer);

class ILVMAPSEXPORTED IlvTiledLayer
    :public IlvManagerLayer
{
private:
    IlvTileController* _tileController;
    IlvTileListener* _debugListener;
    IlvManagerViewHook* _debugHook;
    IlvView* _debugView;
    IlvMapIncrementalPalette* _borderPalette;
    IlvMapIncrementalPalette* _lockedTilePalette;
    IlvMapIncrementalPalette* _cachedTilePalette;
    IlvMapFeatureIdHashTable* _featureIdTable;
    IlvMapsError _initStatus;
    IlBoolean _squaresOnTop;

public:
    IlvTiledLayer(const IlvRect& tileOrigin,
		  IlvTileCache* cache = 0,
		  IlBoolean startEnabled = IlTrue,
		  // large numbers deactivate the spacial indexation
		  IlUShort maxInList = IlvMaxObjectsInList,
		  IlUShort maxInNode = IlvMaxObjectsInList);

    virtual ~IlvTiledLayer();

    virtual IlvMapsError getInitStatus() const { return _initStatus; }

    virtual void draw(IlvPort* port,
		      const IlvTransformer* t	   = 0,
		      const IlvRegion*	    region = 0,
		      const IlvRegion*	    clip   = 0) const;

    void setSize(const IlvRect& rect) {_tileController->setSize(rect);}

    const IlvRect& getSize() const {return _tileController->getSize();}

    IlvTileController* getTileController() const {return _tileController;}

    void setDebugView(IlvView* view,
		      IlvColor* borderColor = 0,
		      IlvColor* lockedTilesColor = 0,
		      IlvColor* cachedTilesColor = 0);
    IlvView* getDebugView() const {return _debugView;}

    void fitTransformerToTile(IlvView* view,
			      IlInt row,
			      IlInt column) const;

    void start() {_tileController->start();}

    IlvTileLoader* getTileLoader() const
    {return _tileController->getTileLoader();}

    void setTileLoader(IlvTileLoader* tileLoader)
    {_tileController->setTileLoader(tileLoader);}


    static void StartAll(IlvManager* manager);

    static IlvTiledLayer* GetFirstTiledLayer(IlvManager* manager);

    // not documented
    virtual void computeBBox(IlvRect& rect,
			     const IlvTransformer* t = 0);
    IlBoolean isLockEnabled(IlvView* view) const;
    IlvMapFeatureIdHashTable* getObjectTable();

    virtual IlBoolean mustSaveObjects() const;

    void setDebugDrawingOnTop(IlBoolean set) {
	_squaresOnTop = set;
    }

    IlBoolean isDebugDrawingOnTop() {
	return _squaresOnTop;
    }

    IlvTilingDeclareLayerIO(IlvTiledLayer);

protected:
    virtual void setManager(IlvManager* manager);
    virtual void setInitStatus(IlvMapsError status) { _initStatus = status; }

private:

    void drawTiles(IlvPort*,
		   const IlvTransformer* t,
		   const IlvRegion* region,
		   const IlvRegion* clip) const;
    void updateDebugPalettes(IlvDisplay* display,
			     IlvColor* borderColor,
			     IlvColor* lockedTilesColor,
			     IlvColor* cachedTilesColor);

    IlvMapsIcFriend(IlvTiledLayer,ILVMAPSEXPORTED);
    static void Init();
};

#endif /* __ILV_tiling_IlvTiledLayer_H */
