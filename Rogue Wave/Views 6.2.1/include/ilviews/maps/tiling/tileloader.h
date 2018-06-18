// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/tiling/tileloader.h
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
// Definition of the IlvTileLoader class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_tiling_IlvTileLoader_H
#define __ILV_tiling_IlvTileLoader_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/tiling/tile.h>

ILVMAPSMODULEINIT(IlvTileLoader);

class ILVMAPSEXPORTED IlvTileController;

class ILVMAPSEXPORTED IlvTileLoader
{
public:
    IlvTileLoader();
    virtual ~IlvTileLoader();

    virtual IlvMapsError load(IlvTile* tile) = 0;

    virtual void release(IlvTile* tile) = 0;

    virtual void controllerDeleted(IlvTileController* controller);

    virtual void tileDeleted(IlvTile* tile);

    virtual IlBoolean isPersistent() const = 0;

    IlvTilingDeclareIO(IlvTileLoader);
};

#endif /* __ILV_tiling_IlvTileLoader_H */
