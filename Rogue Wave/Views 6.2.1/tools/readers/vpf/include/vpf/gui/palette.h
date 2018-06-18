// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/palette.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the Palette class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_PALETTE_H
#define VPF_GUI_PALETTE_H

#include <ilviews/ilv.h>
#include <ilviews/base/resource.h>

class Serialize;
class Unserialize;
class Layer;

// --------------------------------------------------------------------------
class Palette
{
public:
    Palette(IlvDisplay*);
    Palette(IlvDisplay*, IlvColor*, IlvMarkerType, IlUShort size);
    Palette(IlvDisplay*, IlvColor*, IlvLineStyle*, IlUShort width);
    Palette(IlvDisplay*, IlvColor*, IlvPattern*);
    Palette(IlvDisplay*, IlvColor*, IlvFont*);
    Palette(const Palette&);
    Palette(IlvDisplay*, Unserialize&);
    ~Palette();
    // ____________________________________________________________
    IlvPalette* getPalette() const { return _palette; }
    IlvColor* getForeground() const { return _palette->getForeground(); }
    void setForeground(IlvColor*);
    IlvPattern* getPattern() const { return _palette->getPattern(); }
    void setPattern(IlvPattern*);
    IlvFont* getFont() const { return _palette->getFont(); }
    void setFont(IlvFont*);
    IlvLineStyle* getLineStyle() const { return _palette->getLineStyle(); }
    void setLineStyle(IlvLineStyle*);
    IlUShort getLineWidth() const { return _palette->getLineWidth(); }
    void setLineWidth(IlUShort);
    IlvMarkerType getMarkerType() const { return _markerType; }
    void setMarkerType(IlvMarkerType);
    IlUShort getMarkerSize() const { return _markerSize; }
    void setMarkerSize(IlUShort);
    void setLayer(Layer* layer) { _layer = layer; }
    void write(Serialize&) const;
protected:
    IlvDisplay*		_display;
    Layer*		_layer;
    IlvPalette*		_palette;
    IlvMarkerType	_markerType;
    IlUShort		_markerSize;
};

#endif /* VPF_GUI_PALETTE_H */
