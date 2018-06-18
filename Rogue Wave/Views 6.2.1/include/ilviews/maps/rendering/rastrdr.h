// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/rastrdr.h
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
// Rendering Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Geometry_IlvDefaultRasterRenderer_H
#define __ILV_maps_Geometry_IlvDefaultRasterRenderer_H

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/incrpalette.h>
#include <ilviews/maps/rendering/cmodel.h>

ILVMAPSMODULEINIT(rastrdr);

class ILVMAPSEXPORTED IlvDefaultRasterRenderer
    : public IlvFeatureRenderer
{
private:
    IlvMapColorModel* _cmodel;
    IlBoolean      _ownerOfModel;
public:
    IlvDefaultRasterRenderer(IlvDisplay* display,
			     IlvMapColorModel* colorModel,
			     IlBoolean ownerOfModel);

    IlvDefaultRasterRenderer(const IlvDefaultRasterRenderer& source);

    ~IlvDefaultRasterRenderer();

    IlvGraphic* makeGraphic(const IlvMapFeature& feature,
			    const IlvMapInfo& targetMapInfo,
			    IlvMapsError& status) const;

    static IlvMapsError BitmapError();

private:
    static void Init();
    IlvMapsIcFriend(rastrdr,ILVMAPSEXPORTED);
public:
    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvDefaultRasterRenderer);
};



#endif // __ILV_maps_Geometry_IlvDefaultRasterRenderer_H
