// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/include/palettechanger.h
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
// Declaration of the PaletteChanger utility class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Samples_Palettechanger_H
#define __Ilv_Samples_Palettechanger_H

#include <ilviews/ilv.h>

// --------------------------------------------------------------------------
class PaletteChanger
{
public:
    PaletteChanger(IlvPalette* source)
    : _source(source),
      _display(source->getDisplay()),
      _background(source->getBackground()),
      _foreground(source->getForeground()),
      _pattern(source->getPattern()),
      _colorPattern(source->getColorPattern()),
      _font(source->getFont()),
      _lineStyle(source->getLineStyle()),
      _lineWidth(source->getLineWidth()),
      _fillStyle(source->getFillStyle()),
      _arcMode(source->getArcMode()),
      _fillRule(source->getFillRule()),
      _alpha(source->getAlpha()),
      _antiAlias(source->getAntialiasingMode()),
      _gradientPattern(source->getGradientPattern())
    {}

    IlvPalette* get() const
	{
	    return _display->getPalette(_background,
					_foreground,
					_pattern,
					_colorPattern,
					_font,
					_lineStyle,
					_lineWidth,
					_fillStyle,
					_arcMode,
					_fillRule,
					_alpha,
					_antiAlias,
					_gradientPattern);    
	}
    IlvPalette* replace()
	{
	    IlvPalette* newPalette = get();
	    newPalette->lock();
	    _source->unLock();
	    return newPalette;
	}
    PaletteChanger& setBackground(IlvColor* background)
	{ _background = background; return *this; }
    PaletteChanger& setBackground(const char* name)
	{ return setBackground(_display->getColor(name)); }
    PaletteChanger& setRGBBackground(IlvIntensity r,
				     IlvIntensity g,
				     IlvIntensity b)
	{ return setBackground(_display->getColor(r, g, b)); }
    PaletteChanger& setHSVBackground(IlFloat h, IlFloat s, IlFloat v)
	{ return setBackground(_display->getColor(h, s, v)); }
    PaletteChanger& setForeground(IlvColor* foreground)
	{ _foreground = foreground; return *this; }
    PaletteChanger& setForeground(const char* name)
	{ return setForeground(_display->getColor(name)); }
    PaletteChanger& setRGBForeground(IlvIntensity r,
				     IlvIntensity g,
				     IlvIntensity b)
	{ return setForeground(_display->getColor(r, g, b)); }
    PaletteChanger& setHSVForeground(IlFloat h, IlFloat s, IlFloat v)
	{ return setForeground(_display->getColor(h, s, v)); }
    PaletteChanger& setPattern(IlvPattern* pattern)
	{ _pattern = pattern; _fillStyle = IlvFillPattern; return *this; }
    PaletteChanger& setColorPattern(IlvColorPattern* pattern)
	{
	    _colorPattern = pattern;
	    _fillStyle = IlvFillColorPattern;
	    return *this;
	}
    PaletteChanger& setFont(IlvFont* font)
	{ _font = font; return *this; }
    PaletteChanger& setFont(const char* font)
	{ _font = _display->getFont(font); return *this; }
    PaletteChanger& setLineWidth(IlUShort lineWidth)
	{ _lineWidth = lineWidth; return *this; }
    PaletteChanger& setAntialiasingMode(IlvAntialiasingMode antiAlias)
	{ _antiAlias = antiAlias; return *this; }
    // To be completed as needed...
private:
    IlvPalette*         _source;
    IlvDisplay*		_display;
    IlvColor*		_background;
    IlvColor*		_foreground;
    IlvPattern*		_pattern;
    IlvColorPattern*	_colorPattern;
    IlvFont*		_font;
    IlvLineStyle*	_lineStyle;
    IlUShort		_lineWidth;
    IlvFillStyle	_fillStyle;
    IlvArcMode		_arcMode;
    IlvFillRule		_fillRule;
    IlvIntensity	_alpha;
    IlvAntialiasingMode	_antiAlias;
    IlvGradientPattern*	_gradientPattern;  
};

#endif /* !__Ilv_Samples_Palettechanger_H */
