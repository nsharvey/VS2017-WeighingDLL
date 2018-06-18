// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/iconptrdr.h
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
// Rendering class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Rendering_IlvIconPointRenderer_H
#define __ILV_maps_Rendering_IlvIconPointRenderer_H

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/incrpalette.h>

ILVMAPSMODULEINIT(iconptrdr);

class ILVMAPSEXPORTED IlvIconPointRenderer
    :public IlvFeatureRenderer
{
private:
    IlvBitmap* _bitmap;
public:
    IlvIconPointRenderer(IlvDisplay* display);


    IlvIconPointRenderer(const IlvIconPointRenderer& source);

    virtual ~IlvIconPointRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;

    void setBitmap(IlvBitmap* bitmap);

    IlvMapsError setBitmapFileName(const char* fileName);

    IlvBitmap* getBitmap() const;

    static IlvBitmap* GetDefaultBitmap(IlvDisplay* display);

    // non documented. For test purpose
    const IlvBitmap* getBitmapPointer() const {return _bitmap;}
private:
    static void Init();
    IlvMapsIcFriend(iconptrdr,ILVMAPSEXPORTED);
public:
    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvIconPointRenderer);
};

#endif /* __ILV_maps_Rendering_IlvIconPointRenderer_H */
