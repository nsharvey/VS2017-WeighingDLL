// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/maptloader.h
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
// Definition of the IlvMapTileLoader class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_tiling_IlvMapTileLoader_H
#define __ILV_tiling_IlvMapTileLoader_H

#include <ilviews/ilv.h>
#include <ilviews/graphics/io.h>

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/tiling/tileloader.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/renderer.h>

ILVMAPSMODULEINIT(IlvMapTileLoader);

class ILVMAPSEXPORTED IlvMapTileLoader : public IlvTileLoader
{
public:    
    virtual ~IlvMapTileLoader();

    virtual IlBoolean	isPersistent() const = 0;

    virtual
    IlvMapsError	load(IlvTile* tile);

    virtual void	release(IlvTile* tile);

    virtual
    IlvMapFeatureIterator* getFeatureIterator(IlvTile* tile) = 0;

    virtual
    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay* display) = 0;

    virtual void	setAttachingAttributes(IlBoolean set);

    virtual IlBoolean	isAttachingAttributes() const;

    virtual void	setFeatureRenderer(IlvFeatureRenderer* renderer,
					   IlBoolean owner = IlFalse);

    IlBoolean		isOwnerOfRenderer() const { return _owner; }

    virtual
    IlvFeatureRenderer*	getFeatureRenderer(IlvDisplay* display);

    virtual
    IlvMapInfo*		getMapInfo() = 0;

    IlvMapsError	getInitStatus() const { return _status; }

    void		setKeepingReader(IlBoolean keep)
			{
			    _keepReader = keep;
			}

    IlBoolean		isKeepingReader() const { return _keepReader; }

    IlvTilingDeclareIO(IlvMapTileLoader);

protected:
    IlvMapTileLoader();
    void		setInitStatus(IlvMapsError status)
			{
			    _status = status;
			}

private:
    IlvMapsIcFriend(IlvMapTileLoader, ILVMAPSEXPORTED);

    IlBoolean		_attachAttributes;
    IlvFeatureRenderer* _renderer;
    IlvMapsError	_status;
    IlvProjection*	_projection;
    // experiment
    IlvMapFeatureIterator* _iterator;
    IlBoolean		_keepReader;
    IlBoolean		_owner;
};

#endif /* __ILV_tiling_IlvMapTileLoader_H */
