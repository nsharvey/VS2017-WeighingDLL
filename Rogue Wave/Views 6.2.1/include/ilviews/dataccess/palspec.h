// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/palspec.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
#ifndef __Ili_Palspec_H
#define __Ili_Palspec_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#  include <iostream>
#else
#  include <iostream.h>
#endif

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ilv_Base_Look_H
#  include <ilviews/base/look.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

// -------------------------------------------------------------------
class ILV_INF_EXPORTED IliPaletteSpec {
public:
  IliPaletteSpec (IlvDisplay*);
  IliPaletteSpec (IlvPalette*);
  ~IliPaletteSpec ();

  void setBackground(IlvColor*);
  IlvColor* getBackground() const;
  void setForeground(IlvColor*);
  IlvColor* getForeground() const;
  void setPattern(IlvPattern*);
  IlvPattern* getPattern() const;
  void setColorPattern(IlvColorPattern*);
  IlvColorPattern* getColorPattern() const;
  void setLineStyle(IlvLineStyle*);
  IlvLineStyle* getLineStyle() const;
  void setLineWidth(IlUShort);
  IlUShort getLineWidth() const;
  void setFillStyle(IlvFillStyle);
  IlvFillStyle getFillStyle() const;
  void setArcMode(IlvArcMode);
  IlvArcMode getArcMode() const;
  void setFillRule(IlvFillRule);
  IlvFillRule getFillRule() const;

  IlvFont* getFont () const { return _font; }
  void setFont (IlvFont*);

  void clone (IlvPalette*);
  void invert();
  void topShadow ();
  void bottomShadow ();
  void setFontStyle (IlvFontStyle);
  void setFontSize (IlvFontSize);
  IlvPalette* findPalette ();

protected:
  IliPaletteSpec () {}

  IlvFont* _font;
  IlvDisplay* _dpy;
  IlvColor* _background;
  IlvColor* _foreground;
  IlvPattern* _pattern;
  IlvColorPattern* _colorPattern;
  IlvLineStyle* _lineStyle;
  IlUShort _lineWidth;
  IlvFillStyle _fillStyle;
  IlvArcMode _arcMode;
  IlvFillRule _fillRule;
};

// -------------------------------------------------------------------

class ILV_INF_EXPORTED IliPaletteManip {
public:
  IliPaletteManip() { _palette = 0; }
  ~IliPaletteManip() {
    if (_palette)
      _palette->unLock();
  }

  IlvPalette* getPalette() {
    return _palette;
  }
  void setPalette(IlvPalette* p) {
    if (p) p->lock();
    if (_palette) _palette->unLock();
    _palette = p;
  }

  void setForeground(IlvColor*);
  void setFont(IlvFont*);

protected:
  IlvPalette* _palette;
};

// -------------------------------------------------------------------
class ILV_INF_EXPORTED IliReliefPalette {
public:
  IliReliefPalette (IlvPalette*);
  ~IliReliefPalette ();

  void setPalette (IlvPalette*);

  void setForeground (IlvColor*);
  IlvColor* getForeground () const;

  void setBackground (IlvColor*);
  IlvColor* getBackground () const;

  void setMode (IlvDrawMode);
  void setOverwrite (IlBoolean);
  void setAlpha(IlvIntensity alpha);
  void setAntialiasingMode(IlvAntialiasingMode mode);
  void invert ();

  IlvPalette* getPalette () const { return _palette; }
  IlvPalette* getInvertedPalette () const { return _invpalette; }
  IlvPalette* getTopShadowPalette () const { return _topshadow; }
  IlvPalette* getBottomShadowPalette () const { return _bottomshadow; }
  IlvPalette* getSelectionPalette () const { return _selpalette; }

protected:
  IlvPalette* _palette;
  IlvPalette* _invpalette;
  IlvPalette* _topshadow;
  IlvPalette* _bottomshadow;
  IlvPalette* _selpalette;

  IliReliefPalette () {} // don't
  void init ();
  void unLock ();
};

// -------------------------------------------------------------------
class ILV_INF_EXPORTED IliTextPalette
{
public:
  IliTextPalette (IlvPalette*);
  ~IliTextPalette ();

  void checkLook () const;

  IlBoolean isLookSensitive () { return _isLookSensitive; }
  void setLookSensitive (IlBoolean);

  IlBoolean isSelectionLookSensitive () {
    return _isSelectionLookSensitive;
  }
  void setSelectionLookSensitive (IlBoolean);

  void setTextPalette (IlvPalette*);

  void setFont (IlvFont*);
  IlvFont* getFont () const;

  void setForeground (IlvColor*);
  IlvColor* getForeground () const;

  void setBackground (IlvColor*);
  IlvColor* getBackground () const;

  void setMode (IlvDrawMode);
  void setOverwrite (IlBoolean);
  void setAlpha(IlvIntensity alpha);
  void setAntialiasingMode(IlvAntialiasingMode mode);
  void invert ();

  IlvPalette* getTextPalette () const { return _textPalette; }
  IlvPalette* getGrayedTextPalette () const { return _grayedTextPalette; }
  IlvPalette* getFillPalette () const { return _fillPalette; }
  IlvPalette* getSelectionTextPalette () const { return _selTextPalette; }
  IlvPalette* getGrayedSelectionTextPalette () const {
    return _grayedSelTextPalette;
  }
  IlvPalette* getSelectionFillPalette () const { return _selFillPalette; }

  IlvPalette* getLinePalette () const { return _linePalette; }
  IlvPalette* getDotPalette () const { return _dotPalette; }
  IlvPalette* getSelectionDotPalette () const { return _selDotPalette; }

protected:
  IlvPalette* _textPalette;
  IlvPalette* _grayedTextPalette;
  IlvPalette* _fillPalette;
  IlvPalette* _selTextPalette;
  IlvPalette* _grayedSelTextPalette;
  IlvPalette* _selFillPalette;
  IlvPalette* _linePalette;
  IlvPalette* _dotPalette;
  IlvPalette* _selDotPalette;
  IlBoolean _isLookSensitive;
  IlBoolean _isSelectionLookSensitive;
  const IlvLookFeelHandler* _currentLook;

  IliTextPalette (); // don't
  void unLock ();
};

// --

ILV_INF_EXPORTEDFN(void)
IliWriteFont (IL_STDPREF ostream&, IlvFont*);

ILV_INF_EXPORTEDFN(IlvFont*)
IliReadFont (IL_STDPREF istream&, IlvDisplay*);

ILV_INF_EXPORTEDFN(void)
IliWriteColor (IL_STDPREF ostream&, IlvColor*);

ILV_INF_EXPORTEDFN(IlvColor*)
IliReadColor (IL_STDPREF istream&,IlvDisplay*,IlBoolean foreground = IlTrue);

ILV_INF_EXPORTEDFN(IlvColor*)
IliGetResourceColor (IlvDisplay*, const char*, const char* = 0);

ILV_INF_EXPORTEDFN(IlvFont*)
IliGetResourceFont (IlvDisplay*, const char*, const char* = 0);

#endif
