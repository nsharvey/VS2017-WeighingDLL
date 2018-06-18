// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/pointrdr.h
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
#ifndef __ILV_maps_Rendering_IlvDefaultPointRenderer_H
#define __ILV_maps_Rendering_IlvDefaultPointRenderer_H

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/incrpalette.h>
#include <ilviews/graphics/marker.h>

ILVMAPSMODULEINIT(pointrdr);

class ILVMAPSEXPORTED IlvDefaultPointRenderer : public IlvFeatureRenderer
{
private:
    IlvMapIncrementalPalette _palette;
    IlvMapIncrementalPalette _internalPalette;
    IlvMarkerType _markerType;
    IlBoolean _paletteSpecified;
    IlUShort _markerSize;

public:
    IlvDefaultPointRenderer(IlvDisplay* display);


    IlvDefaultPointRenderer(const IlvDefaultPointRenderer& source);

    virtual ~IlvDefaultPointRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;

    void setMarkerType(IlvMarkerType markerType);

    IlvMarkerType getMarkerType() const {return _markerType;}

    void setPalette(IlvPalette* palette);

    IlvPalette* getPalette() const {return _palette.getPalette();}

    void setMarkerSize(IlUShort markerSize) {_markerSize = markerSize;}

    IlUShort getMarkerSize() const { return _markerSize;}

    void setForeground(IlvColor* color);

    IlvMapsError setForeground(const char* colorName);

    IlvColor* getForeground() const {return _internalPalette.getForeground();}

    void setPattern(IlvPattern* pattern);

    IlvMapsError setPattern(const char* fileName);


    IlvPattern* getPattern() const {return _internalPalette.getPattern();}

    void setLineWidth(IlUShort lineWidth);

    IlUShort getLineWidth() const {return _internalPalette.getLineWidth();}

private:
    static void Init();
    IlvMapsIcFriend(pointrdr,ILVMAPSEXPORTED);
public:
    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvDefaultPointRenderer);

protected:
    // computes the actual pallette used to create the marker
    // using compatibility rules to ensure a common behaviour
    // on any platform. Not called if the palette is specified
    // by the user using setPalette.
    virtual void computePalette();

    // the palette that stores the user settings - used by computePalette.
    const IlvPalette* getInternalPalette() const
    { return _internalPalette.getPalette(); }
};


#endif /* __ILV_maps_Rendering_IlvDefaultPointRenderer_H */
