// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/areardrstyle.h
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
#ifndef __ILV_maps_Rendering_IlvMapAreaRenderingStyle_H
#define __ILV_maps_Rendering_IlvMapAreaRenderingStyle_H

#include <ilviews/maps/rendering/rdrstyle.h>
#include <ilviews/maps/rendering/linerdrstyle.h>
#include <ilviews/maps/rendering/incrpalette.h>
#include <ilviews/graphics/path.h> /* for IlvDrawRule */

ILVMAPSMODULEINIT(areardrstyle);

class ILVMAPSEXPORTED IlvMapAreaRenderingStyle
    :public IlvMapRenderingStyle
{
private:
    IlvMapIncrementalPalette _palette;
    IlBoolean _fillObject;
    IlBoolean _drawStroke;
    IlvDrawRule _drawRule;
    IlvMapLineRenderingStyle* _lineRenderingStyle;

protected:
    virtual ~IlvMapAreaRenderingStyle();

public:
    IlvMapAreaRenderingStyle(IlvDisplay* display);

    IlvMapAreaRenderingStyle(const IlvMapAreaRenderingStyle& source);

    IlvPalette* getPalette() const {return _palette.getPalette();}

    void setPalette(IlvPalette* palette) {_palette.setPalette(palette);}

    void setFillColor(IlvColor* color)
	{_palette.setForeground(color);}

    IlvMapsError setFillColor(const char* colorName)
	{return _palette.setForeground(colorName);}

    IlvColor*  getFillColor() const {return _palette.getForeground();}

    void setFillBackground(IlvColor* color)
	{_palette.setBackground(color);}

    IlvMapsError setFillBackground(const char* colorName)
	{return _palette.setBackground(colorName);}

    IlvColor*  getFillBackground() const {return _palette.getBackground();}

    void setFillPattern(IlvPattern* pattern)
	{_palette.setPattern(pattern);}

    IlvMapsError setFillPattern(const char* fileName)
	{return _palette.setPattern(fileName);}


    IlvPattern* getFillPattern() const {return _palette.getPattern();}

    
    void setFillingObject(IlBoolean fillObject);

    IlBoolean isFillingObject() const {return _fillObject;}


    void setDrawingStroke(IlBoolean   drawStroke);

    IlBoolean isDrawingStroke() const {return _drawStroke;}

    void setLineRenderingStyle(IlvMapLineRenderingStyle* lineRenderingStyle);

    IlvMapLineRenderingStyle* getLineRenderingStyle() const;

    // undocumented goodie
    IlvDrawRule getDrawRule() const {return _drawRule;}

private:
    static void Init();
    IlvMapsIcFriend(areardrstyle, ILVMAPSEXPORTED);
    ILVMAPS_DECLMANDATORYRDRSTYLEMEMBERS(IlvMapAreaRenderingStyle);
};

#endif /* __ILV_maps_Rendering_IlvMapAreaRenderingStyle_H */
