// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/tiling/tilectrl.h
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
// Definition of the IlvTileController class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_tiling_IlvTileController_H
#define __ILV_tiling_IlvTileController_H

#include <ilviews/maps/tiling/tile.h>
#include <ilviews/maps/tiling/tileloader.h>
#include <ilviews/manager/manager.h>
#include <ilviews/maps/clssinfo.h>

class ILVMAPSEXPORTED IlvTiledLayer;
class ILVMAPSEXPORTED IlvTileListener;
class ILVMAPSEXPORTED IlvTileCache;

ILVMAPSMODULEINIT(IlvTileController);



typedef void (*IlvTileControllerMapFunction)(IlvTile* tile,IlAny arg);

typedef IlBoolean (*IlvTileControllerMatchFunction)(IlvTile* tile,IlAny arg);



// not documented
class ILVMAPSEXPORTED IlvTileHashTable : public IlvHashTable
{
public:
    IlvTileHashTable() : IlvHashTable(17) {}
    virtual ~IlvTileHashTable();

    virtual IlBoolean	matchF(IlvTileControllerMatchFunction f,IlAny a);

protected:
    virtual IlBoolean	match(const IlAny target, const IlAny entry) const;
    virtual IlUInt	hash(const IlAny) const;
};


class ILVMAPSEXPORTED IlvTileController
{
public:

    IlvTileController(IlvManager* manager,
		      const IlvRect& tileOrigin,
		      IlvTileCache* cache = 0,
		      IlBoolean startEnabled = IlTrue);

    virtual ~IlvTileController();

    virtual
    IlvMapsError	getInitStatus() const { return _initStatus; }

    inline
    const IlvRect&	getTileOrigin() const { return _tileOrigin; }

    inline void		getTileIndexes(const IlvRect& rect,
				       IlInt& upperRow,
				       IlInt& lowerRow,
				       IlInt& leftCol,
				       IlInt& rightCol) const
			{
			    getTileIndexes(rect,
					   upperRow,
					   lowerRow,
					   leftCol,
					   rightCol,
					   IlFalse);
			}

    // Not documented
    void		getTileIndexes(const IlvRect& rect,
				       IlInt& upperRow,
				       IlInt& lowerRow,
				       IlInt& leftCol,
				       IlInt& rightCol,
				       IlBoolean ceilForLowerRight) const;

    inline void		setSize(const IlvRect& size) { _size = size; }

    inline IlBoolean	hasBounds() const
			{
			    return !((_size.w() == 0) || (_size.h() == 0));
			}

    inline
    const IlvRect&	getSize() const { return _size; }

    IlvTile*		getTile(IlInt column, IlInt row) const;

    void		lockTile(IlInt column, IlInt row, IlAny source);

    IlBoolean		unLockTile(IlInt row, IlInt column, IlAny source);

    void		fireTileChanged(IlvTile* tile,
					IlvTileStatus oldStatus,
					IlvTileStatus newStatus);
    void		fireLoadError(IlvTile* tile, IlvMapsError errorCode);

    void		tileBBox(IlInt column,
				 IlInt row,
				 IlvRect& result) const;

    void		start();

    inline IlBoolean	isStarted() const { return _started && _startEnabled; }

    inline void		addTileListener(IlvTileListener* listener)
			{
			    _listeners.append(listener);
			}

    inline void		removeTileListener(IlvTileListener* listener)
			{
			    _listeners.remove(listener);
			}

    void		unLockTiles(IlAny source);

    void		enableStart(const IlvRect& tileOrigin,
				    const IlvRect& size);

    inline void		setTileLoader(IlvTileLoader* tileLoader)
			{
			    _tileLoader = tileLoader;
			}

    IlvTileLoader*	getTileLoader() const { return _tileLoader; }

    inline IlvManager* getManager() const { return _manager; }

    inline
    IlvTiledLayer*	getLayer() const { return _layer; }

    IlvTileCache*	getCache() const;

    void		mapToTiles(IlvTileControllerMapFunction func,
				   IlAny arg);

    IlBoolean		mapToTilesUntilMatch(IlvTileControllerMatchFunction f,
					     IlAny arg);

    static void		IgnoreView(IlvView* view, IlBoolean ignore = IlTrue);

    void		updateView(IlvView* view);

    inline 
    static IlBoolean	IsIgnoringView(IlvView* view)
			{
			    return (_ignoredViews.find(view) != 0);
			}

    IlInt		getControlledTilesCount() const;

    // use this before Views allows an automatic update
    void		viewAdded(IlvView* view);

    // not documented - intended as private to the tiling package
    IlvTileController(const IlvRect& tileOrigin,
		      IlvTiledLayer* layer,
		      IlvTileCache* cache,
		      IlBoolean startEnabled);

    static IlvRect	BBoxOfInverse(const IlvRect& rect,
				      const IlvTransformer* t);
    static IlvRect	BBoxOfApply(const IlvRect& rect,
				    const IlvTransformer* t);
    void		visibleRectChanged(IlvView* view,
					   const IlvRect& newRect);
    IlBoolean		isLockEnabled(IlvView* view, IlvRect& rect) const;
    IlBoolean		intersectsSize(const IlvRect& rect) const;
    inline void		removeHookFromList(IlvManagerViewHook* hook)
			{
			    _hooks.remove(hook);
			}
    void		retreiveFromCache(IlvTile* tile);
    void		addToCache(IlvTile* tile);
    inline IlBoolean	isStartEnabled() const { return _startEnabled; }
    void		release(IlvTile* tile);
    inline void		setLayer(IlvTiledLayer* layer) {_layer = layer;}
    void		setManager(IlvManager* manager);
    void		notifyLoadComplete(IlvTile* tile);
    inline IlBoolean	isAdjusting() { return  _adjusting; }

    IlvTilingDeclareIO(IlvTileController);

protected:
    virtual void	setInitStatus(IlvMapsError status)
			{
			    _initStatus = status;
			}

private:
    void		initListeners();
    void		loadTile(IlInt column, IlInt row, IlAny source);
    void		installHook(IlvView* view);
    void		unLockTiles(const IlvRect& rect, IlvView* view);
    void		updateViews();
    void		setCache(IlvTileCache* cache);

    IlvManager*		_manager;
    IlvRect		_tileOrigin;
    IlvTiledLayer*	_layer;
    IlBoolean		_adjusting;
    IlvRect		_size;
    IlvTileHashTable	_tiles;
    IlvList		_lockedTiles;
    IlvList		_hooks;
    IlvList		_listeners;
    IlBoolean		_started;
    IlBoolean		_startEnabled;
    IlvTileLoader*	_tileLoader;
    IlvTileCache*	_cache;
    IlBoolean		_initialized;
    static IlvList	_ignoredViews;
    IlvMapsError	_initStatus;

};

class ILVMAPSEXPORTED IlvTileListener
{
public:
    virtual ~IlvTileListener();
    virtual void	beginGroupedNotification(IlvTileController* tc) = 0;

    virtual void	endGroupedNotification(IlvTileController* tc) = 0;


    virtual void	tileChanged(IlvTile* tile,
				    IlvTileStatus oldStatus,
				    IlvTileStatus newStatus) = 0;
    virtual void	controllerDeleted(IlvTileController* tc) = 0;

    virtual void	startEnabled(IlvTileController* tc);

    virtual void	loadError(IlvTile* tile, IlvMapsError errorCode);

    virtual void	loadComplete(IlvTile* tile);

};

#endif /* __ILV_tiling_IlvTileController_H */
