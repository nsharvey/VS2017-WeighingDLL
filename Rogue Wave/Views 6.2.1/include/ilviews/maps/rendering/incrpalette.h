// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/incrpalette.h
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

#ifndef __ILV_maps_Rendering_IlvMapIncrementalPalette
#define __ILV_maps_Rendering_IlvMapIncrementalPalette

#include <ilviews/ilv.h>
#include <ilviews/graphics/io.h>
#include <ilviews/maps/maps.h>

// undocumented class
// manages an internal palette that can be modified
// by increments
// and provides persitence services
class ILVMAPSEXPORTED IlvMapIncrementalPalette
{
private:
    IlvDisplay* _display;
    IlvPalette* _palette;
public:
    IlvMapIncrementalPalette(IlvDisplay* display, IlvPalette* palette);
    IlvMapIncrementalPalette(const IlvMapIncrementalPalette& source);
    ~IlvMapIncrementalPalette();

    IlvDisplay* getDisplay() const {return _display;}

    void setPalette(IlvPalette* palette);
    IlvPalette* getPalette() const {return _palette;}

    void setForeground(IlvColor* color);
    IlvMapsError setForeground(const char* colorName);
    IlvColor* getForeground() const
    {return _palette ? _palette->getForeground() : 0;}

    void setBackground(IlvColor* color);
    IlvMapsError setBackground(const char* colorName);
    IlvColor* getBackground() const
    {return _palette ? _palette->getBackground() : 0;}

    // sets the pattern or the color pattern depending on the pattern's
    // depth. Updates the fillStyle to make it used.
    void setPattern(IlvPattern* pattern);
    IlvMapsError setPattern(const char* fileName);
    // returns null, an IlvPattern or an IlvColorPattern depending on
    // the fill style
    IlvPattern* getPattern() const;

    void setLineWidth(IlUShort lineWidth);
    IlUShort getLineWidth() const
    {return _palette ? _palette->getLineWidth() : 0;}

    void setLineStyle(IlvLineStyle* lineStyle);
    IlvMapsError setLineStyle(const char* lineStyleName);
    IlvLineStyle* getLineStyle() const
    {return _palette ? _palette->getLineStyle() : 0;}

    void setFont(IlvFont* font);
    IlvMapsError setFont(const char* fontName);
    IlvFont* getFont() const {return _palette ? _palette->getFont() : 0;}

    // supports null palettes and named palettes
    static void WritePalette(const IlvPalette* palette,
			     IlvOutputFile& stream);
    // The palette must have been saved with WritePalette....
    static IlvPalette* ReadPalette(IlvDisplay* display,
				   IlvInputFile& file);

};

#endif
