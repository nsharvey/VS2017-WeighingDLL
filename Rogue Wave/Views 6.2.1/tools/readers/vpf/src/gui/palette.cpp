// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/palette.cpp
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
// Definition of the Palette class
// --------------------------------------------------------------------------

#include <vpf/gui/palette.h>
#include <vpf/gui/serialize.h>
#include <vpf/gui/layer.h>
#if defined(ILVSTD)
# include <iostream>
ILVSTDUSE
#else
# include <iostream.h>
#endif

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d)
: _display(d),
  _layer(0),
  _palette(d->getPalette()),
  _markerType(IlvMarkerSquare),
  _markerSize(IlvDefaultMarkerSize)
{
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d, 
		 IlvColor* foreground, 
		 IlvMarkerType type, 
		 IlUShort size)
: _display(d),
  _layer(0),
  _palette(0),
  _markerType(type),
  _markerSize(size)
{
    _palette = d->getPalette(0, foreground);
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d,
		 IlvColor* foreground,
		 IlvLineStyle* style,
		 IlUShort width)
: _display(d),
  _layer(0),
  _palette(0),
  _markerType(IlvMarkerSquare),
  _markerSize(0)
{
    _palette = d->getPalette(0, foreground, 0, 0, 0, style, width);
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d,
		 IlvColor* foreground,
		 IlvPattern* pattern)
: _display(d),
  _layer(0),
  _palette(0),
  _markerType(IlvMarkerSquare),
  _markerSize(0)
{
    _palette = d->getPalette(0, foreground, pattern);
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d,
		 IlvColor* foreground,
		 IlvFont* font)
: _display(d),
  _layer(0),
  _palette(0),
  _markerType(IlvMarkerSquare),
  _markerSize(0)
{
    _palette = d->getPalette(0, foreground, 0, 0, font);
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(const Palette& source)
: _display(source._display),
  _layer(0),
  _palette(source._palette),
  _markerType(source._markerType),
  _markerSize(source._markerSize)
{
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::Palette(IlvDisplay* d, Unserialize& s)
: _display(d),
  _layer(0),
  _palette(0),
  _markerType(0),
  _markerSize(0)
{
    IlvColor* foreground = 0;
    IlvPattern* pattern = 0;
    IlvFont* font = 0;
    IlvLineStyle* lineStyle = 0;
    VpfUInt lineWidth = 0;
    VpfUInt i;
    VpfUInt r, g, b;

    s >> i;
    if (i) {
	s >> r >> g >> b;
	foreground = d->getColor((IlvIntensity)r,
				 (IlvIntensity)g,
				 (IlvIntensity)b);
    }

    s >> i;
    if (i) {
	char* patternName;
	s >> patternName;
	if (patternName) {
	    pattern = d->getPattern(patternName);
	    delete [] patternName;
	}
    }

    s >> i;
    if (i) {
	char* family;
	char* foundry;
	VpfUInt size;
	VpfUInt style;
	s >> family;
	s >> size;
	s >> style;
	s >> foundry;
	if (family) {
	    font = d->getFont(family, size,
			      (enum IlvFontStyle) style, foundry);
	    delete [] family;
	}
	if (foundry)
	    delete [] foundry;
    }

    s >> i;
    if (i) {
	char* lineStyleName;
	s >> lineStyleName;
	if (lineStyleName) {
	    lineStyle = d->getLineStyle(lineStyleName);
	    delete [] lineStyleName;
	}
	s >> lineWidth;
    }
    s >> i;
    _markerType = i;
    s >> i;
    _markerSize = i;

    _palette = d->getPalette(0, foreground,
			     pattern, 0, font, lineStyle, lineWidth);
    if (_palette)
	_palette->lock();
}

// --------------------------------------------------------------------------
Palette::~Palette()
{
    if (_palette)
	_palette->unLock();
}

// --------------------------------------------------------------------------
void 
Palette::setForeground(IlvColor* color)
{
    IlvPalette* palette = _display->getPalette(_palette->getBackground(),
					       color,
					       _palette->getPattern(),
					       _palette->getColorPattern(),
					       _palette->getFont(),
					       _palette->getLineStyle(),
					       _palette->getLineWidth());
    palette->lock();
    _palette->unLock();
    _palette = palette;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setPattern(IlvPattern* pattern)
{
    IlvPalette* palette = _display->getPalette(_palette->getBackground(),
					       _palette->getForeground(),
					       pattern,
					       _palette->getColorPattern(),
					       _palette->getFont(),
					       _palette->getLineStyle(),
					       _palette->getLineWidth());
    palette->lock();
    _palette->unLock();
    _palette = palette;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setFont(IlvFont* font)
{
    IlvPalette* palette = _display->getPalette(_palette->getBackground(),
					       _palette->getForeground(),
					       _palette->getPattern(),
					       _palette->getColorPattern(),
					       font,
					       _palette->getLineStyle(),
					       _palette->getLineWidth());
    palette->lock();
    _palette->unLock();
    _palette = palette;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setLineStyle(IlvLineStyle* lineStyle)
{
    IlvPalette* palette = _display->getPalette(_palette->getBackground(),
					       _palette->getForeground(),
					       _palette->getPattern(),
					       _palette->getColorPattern(),
					       _palette->getFont(),
					       lineStyle,
					       _palette->getLineWidth());
    palette->lock();
    _palette->unLock();
    _palette = palette;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setLineWidth(IlUShort lineWidth)
{
    IlvPalette* palette = _display->getPalette(_palette->getBackground(),
					       _palette->getForeground(),
					       _palette->getPattern(),
					       _palette->getColorPattern(),
					       _palette->getFont(),
					       _palette->getLineStyle(),
					       lineWidth);
    palette->lock();
    _palette->unLock();
    _palette = palette;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setMarkerType(IlvMarkerType markerType)
{
    _markerType = markerType;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::setMarkerSize(IlUShort markerSize)
{
    _markerSize = markerSize;
    if (_layer)
	_layer->setDirty(1);
}

// --------------------------------------------------------------------------
void
Palette::write(Serialize& s) const
{
    IlvColor* foreground = _palette->getForeground();
    if (foreground) {
	s << 1
	  << (VpfInt)foreground->getRed()
	  << (VpfInt)foreground->getGreen()
	  << (VpfInt)foreground->getBlue();
    } else
	s << 0;
    
    IlvPattern* pattern = _palette->getPattern();
    if (pattern)
      s << 1 << pattern->getName();
    else
      s << 0;

    IlvFont* font = _palette->getFont();
    if (font) {
	s << 1
	  << font->getFamily()
	  << (VpfInt)font->getSize()
	  << (VpfInt)font->getStyle()
	  << font->getFoundary();
    } else
	s << 0;

    IlvLineStyle* lineStyle = _palette->getLineStyle();
    if (lineStyle)
	s << 1
	  << lineStyle->getName()
	  << (VpfInt)_palette->getLineWidth();
    else
	s << 0;

    s << (VpfInt)_markerType;
    s << (VpfInt)_markerSize;
}
