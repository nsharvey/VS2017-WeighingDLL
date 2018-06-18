// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/tiling/tilecache.h
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
// Definition of the IlvTileCache class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_tiling_IlvTileCache_H
#define __ILV_tiling_IlvTileCache_H

#include <ilviews/maps/macros.h>
#include <ilviews/base/link.h>
#include <ilviews/maps/clssinfo.h>
#include <ilviews/maps/tiling/tile.h>

ILVMAPSMODULEINIT(IlvTileCache);

class ILVMAPSEXPORTED IlvTile;
class ILVMAPSEXPORTED IlvTileController;

class ILVMAPSEXPORTED IlvTileCache
{
public:
    virtual void tileAboutToLoad(IlvTile* tile) = 0;

    virtual void tileCached(IlvTile* tile) = 0;

    virtual void tileRetrieved(IlvTile* tile) = 0;


    void lock() {_lockCount++;}

    void unLock();

    virtual void controllerDeleted(IlvTileController* controller) = 0;

    IlvTilingDeclareIO(IlvTileCache);

protected:
    IlvTileCache();
    virtual ~IlvTileCache();

    void releaseTile(IlvTile* tile);

private:
    IlInt _lockCount;
}; /* IlvTileCache */


ILVMAPSMODULETERM(IlvDefaultTileCache);

class ILVMAPSEXPORTED IlvDefaultTileCache
    :public IlvTileCache
{
private:
    static IlvDefaultTileCache* _singleton;
    IlvList _tiles;
    IlInt _cacheSize;

protected:
    virtual ~IlvDefaultTileCache();
public:
     IlvDefaultTileCache(IlInt size = 5);

    static IlvDefaultTileCache* GetDefaultCache();

    virtual void tileAboutToLoad(IlvTile* tile);

    virtual void tileCached(IlvTile* tile);

    virtual void tileRetrieved(IlvTile* tile);

    IlInt getCacheSize() const {return _cacheSize;}

    void setCacheSize(IlInt size) {_cacheSize = size;}

    virtual void controllerDeleted(IlvTileController* controller);

    static void Finalize();
    IlvTilingDeclareIO(IlvDefaultTileCache);

    IlvMapsIcFriend(IlvDefaultTileCache,ILVMAPSEXPORTED);    
};

#endif /* __ILV_tiling_IlvTileCache_H */
