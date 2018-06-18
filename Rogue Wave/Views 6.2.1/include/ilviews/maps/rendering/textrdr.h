// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/textrdr.h
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
// Definition of the IlvDefaultTextRenderer class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Rendering_IlvDefaultTextRenderer_H
#define __ILV_maps_Rendering_IlvDefaultTextRenderer_H

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/incrpalette.h>

ILVMAPSMODULEINIT(textrdr);

class ILVMAPSEXPORTED IlvDefaultTextRenderer
    :public IlvFeatureRenderer
{
private:
    IlvMapIncrementalPalette _palette;
public:
    IlvDefaultTextRenderer(IlvDisplay* display);

    IlvDefaultTextRenderer(const IlvDefaultTextRenderer& source);

    virtual ~IlvDefaultTextRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;

    void setPalette(IlvPalette* palette) {_palette.setPalette(palette);}

    IlvPalette* getPalette() const {return _palette.getPalette();}

    IlvColor* getTextColor() const { return _palette.getForeground(); }

    void setTextColor(IlvColor* color)
	{_palette.setForeground(color);}

    IlvMapsError setTextColor(const char* colorName)
	{return _palette.setForeground(colorName);}

    void setTextFont(IlvFont* font) {_palette.setFont(font);}

    IlvMapsError setTextFont(const char* fontName) {
	return _palette.setFont(fontName);
    }

    IlvFont* getTextFont() const
	{return _palette.getFont();}

private:
    static void Init();
    IlvMapsIcFriend(textrdr,ILVMAPSEXPORTED);
public:  
    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvDefaultTextRenderer);
};

#endif /* __ILV_maps_Rendering_IlvDefaultTextRenderer_H */
