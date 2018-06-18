// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/gui/compass.h
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
// Declaration of the IlvMapsCompass class
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __IlvMapsCompassBar_H__
#define __IlvMapsCompassBar_H__

#include <ilviews/manager/manager.h>
#include <ilviews/base/graphic.h>
#include <ilviews/maps/macros.h>

ILVMAPSMODULEINIT(mapcompass);
ILVMAPSMODULEINIT(mapdefaultneedle);


enum IlvMapDefaultNeedleStyle {
    IlvMapSimpleNeedle,
    IlvMapCompassNeedle,
    IlvMapCrossNeedle,
    IlvMapCompassRoseNeedle
};

class ILVMAPSEXPORTED IlvMapDefaultNeedle : public IlvSimpleGraphic
{
public:
    IlvMapDefaultNeedle(IlvDisplay* display,
			IlvRect& rect,
			IlvMapDefaultNeedleStyle style,
			IlvPalette* palette = 0);

    virtual void	draw(IlvPort*,
			     const IlvTransformer*t,
			     const IlvRegion*) const;
    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t) const;
    virtual void	applyTransform(const IlvTransformer* t);

    void		setForeground(IlvColor* col);

    const IlvColor*	getForeground() { return _foreground; }

    void		setBackground(IlvColor* col);

    const IlvColor*	getBackground() { return _background; }

    void		setStyle(IlvMapDefaultNeedleStyle style,
				 IlBoolean redraw = IlTrue);

    IlvMapDefaultNeedleStyle getStyle() { return _style; }

    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapDefaultNeedle);

private:
    IlvRect		_box;
    IlvColor*		_foreground;
    IlvColor*		_background;
    IlvMapDefaultNeedleStyle _style;
};


class _IlvCompassInternalHook;

class ILVMAPSEXPORTED IlvMapCompass : public IlvSimpleGraphic
{
    friend class _IlvCompassInternalHook;   
public:
    IlvMapCompass(IlvDisplay* display,
		  IlvRect& rect,
		  IlvGraphic* cartoNeedle = 0,
		  IlvGraphic* geoNeedle = 0,
		  IlvPalette* palette = 0);

    virtual ~IlvMapCompass();

    void		setView(IlvView* view);

    const IlvView*	getView() { return _view; }

    IlDouble		getCartographicNorth() { return _cartoNorth; }

    IlDouble		getGeographicNorth() { return _geoNorth; }

    void		setForeground(IlvColor* color);

    const IlvColor*	getForeground() { return _foreground; }

    void		setBackground(IlvColor* color);

    const IlvColor*	getBackground() { return _background; }

    void		setCartographicNeedle(IlvGraphic* graphic);

    const IlvGraphic*	getCartographicNeedle() { return _cartoNeedle; }

    void		setGeographicNeedle(IlvGraphic* gn);

    const IlvGraphic*	getGeographicNeedle() { return _geoNeedle; }

    virtual void	draw(IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const;

    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	apply(IlvApplyObject f, IlAny arg);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapCompass);

protected:

    void		computeNorths();
    void		drawDecorations(IlvPort*, IlvRect&) const;

private:
    _IlvCompassInternalHook* _hook;

    IlvView*		_view;
    IlvManager*		_manager;

    IlDouble		_cartoNorth;
    IlDouble		_geoNorth;

    IlDouble		_oldCartoNorth;
    IlDouble		_oldGeoNorth;

    IlvColor*		_foreground;
    IlvColor*		_background;

    IlvGraphic*		_cartoNeedle;
    IlvGraphic*		_geoNeedle;

    IlvRect		_box;
};

#endif /* __IlvMapsCompassBar_H__ */
