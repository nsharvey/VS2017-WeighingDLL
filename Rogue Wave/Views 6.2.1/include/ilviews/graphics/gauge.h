// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/gauge.h
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
// Definition of the IlvGauge class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Gauge_H
#define __Ilv_Graphics_Gauge_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGauge : public IlvSimpleGraphic
{
public:
    IlvGauge(IlvDisplay*	display,
	     const IlvRect&	drawrect,
	     IlFloat		min	=   0,
	     IlFloat		max	= 100,
	     IlFloat		value	=  50,
	     IlvPalette*	palette	=   0);
    virtual ~IlvGauge();

    inline IlFloat	getMin() const { return _min; }
    void		setMin(IlFloat min);
    inline IlFloat	getMax() const { return _max; }
    void		setMax(IlFloat max);
    inline IlFloat	getValue() const { return _value; }
    virtual void	setValue(IlFloat value);
    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawValue(IlvPort*		dst,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const = 0;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const = 0;
    virtual void	applyTransform(const IlvTransformer* t);

    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setMode(IlvDrawMode);
    virtual void	invert(IlBoolean = IlFalse);
    virtual void	setPalette(IlvPalette*);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	setAlpha(IlvIntensity alpha);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);


    virtual IlFloat	requestValue(const IlvPoint& point,
				     const IlvTransformer* t,
				     IlBoolean& connect) const = 0;
    virtual void	bboxRange(IlFloat		v1,
				  IlFloat		v2,
				  IlvRect&		rect,
				  const IlvTransformer*	t = 0) const = 0;
    virtual const char* getDefaultInteractor() const;

    DeclareGraphicAccessors();

    static IlSymbol*	_minValue;
    static IlSymbol*	_maxValue;
    static IlSymbol*	_valueValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGauge);

protected:
    virtual void	computeInvertedPalette();

    IlvRect		_drawrect;
    IlFloat		_min;
    IlFloat		_max;
    IlFloat		_value;
    IlvPalette*		_invertedPalette;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvRectangularGauge : public IlvGauge
{
public:
    IlvRectangularGauge(IlvDisplay*	display,
			const IlvRect&	drawrect,
			IlFloat		min		= 0,
			IlFloat		max		= 100,
			IlFloat		value		= 50,
			IlvDirection	direction	= IlvVertical,
			IlBoolean	showBox		= IlTrue,
			IlvPalette*	palette		= 0)
	: IlvGauge(display, drawrect, min, max, value, palette),
	  _direction(direction),
	  _showBox(showBox)
    {}

    inline IlvDirection	getDirection() const { return _direction; }
    inline void		setDirection(IlvDirection direction)
			{
			    _direction = direction;
			}
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	drawValue(IlvPort*,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    inline void		showBox(IlBoolean show) { _showBox = show; }
    inline IlBoolean	isBoxShown() const { return _showBox; }
    virtual IlFloat	requestValue(const IlvPoint&,
				     const IlvTransformer*,
				     IlBoolean&) const;
    virtual void	bboxRange(IlFloat		v1,
				  IlFloat		v2,
				  IlvRect&		rect,
				  const IlvTransformer*	t = 0) const;

    virtual void	setGradientPattern(IlvGradientPattern* pattern);
    virtual void	setColorPattern(IlvColorPattern* pattern);
    virtual void	setFillStyle(IlvFillStyle style);

    DeclareGraphicAccessors();

    static IlSymbol*	_directionValue;
    static IlSymbol*	_showBoxValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvRectangularGauge);

protected:
    virtual void	computeSliderBBox(IlvRect&,
					  const IlvTransformer* = 0) const;
    virtual void	computeInvertedPalette();

    IlvDirection	_direction;
    IlBoolean		_showBox;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSliderGauge : public IlvRectangularGauge
{
public:
    IlvSliderGauge(IlvDisplay*		display,
		   const IlvRect&	drawrect,
		   IlFloat		min		= 0,
		   IlFloat		max		= 100,
		   IlFloat		value		= 50,
		   IlvDirection		direction	= IlvVertical,
		   IlUShort		sliderSize	= 0,
		   IlBoolean		showBox		= IlTrue,
		   IlvPalette*		palette		= 0)
	: IlvRectangularGauge(display,
			      drawrect,
			      min,
			      max,
			      value,
			      direction,
			      showBox,
			      palette),
	  _sliderSize(sliderSize)
    {}

    inline IlUShort	getSliderSize() const { return _sliderSize; }
    inline void		setSliderSize(IlUShort size) { _sliderSize = size; }
    virtual void	drawValue(IlvPort*,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual IlFloat	requestValue(const IlvPoint&,
				     const IlvTransformer*,
				     IlBoolean&) const;
    virtual void	bboxRange(IlFloat		v1,
				  IlFloat		v2,
				  IlvRect&		rect,
				  const IlvTransformer*	t = 0) const;

    DeclareGraphicAccessors();

    static IlSymbol*	_sliderSizeValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvSliderGauge);

protected:
    virtual void	computeSliderBBox(IlvRect& bbox,
					  const IlvTransformer* t = 0) const;

    IlUShort		_sliderSize;
};

#define IlvDefaultReliefGaugeThickness 4
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefGauge : public IlvRectangularGauge
{
public:
    IlvReliefGauge(IlvDisplay*	display,
		   const IlvRect& drawrect,
		   IlFloat	min	= 0,
		   IlFloat	max	= 100,
		   IlFloat	value	= 50,
		   IlvDirection	direction = IlvVertical,
		   IlUShort	thickness = IlvDefaultReliefGaugeThickness,
		   IlBoolean	showBox	= IlTrue,
		   IlvPalette*	palette	= 0);
    virtual ~IlvReliefGauge();

    virtual void	drawValue(IlvPort*,
				  const IlvTransformer* t    = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	bboxRange(IlFloat		v1,
				  IlFloat		v2,
				  IlvRect&		rect,
				  const IlvTransformer*	t = 0) const;
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness)
			{
			    _thickness = thickness;
			}
    virtual void	setForeground(IlvColor*);
    virtual void	setMode(IlvDrawMode);
    virtual void	invert(IlBoolean = IlFalse);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity alpha);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);

    DeclareGraphicAccessors();

    static IlSymbol*	_thicknessValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvReliefGauge);

protected:
    IlvPalette*		_topPalette;
    IlvPalette*		_bottomPalette;
    IlvPalette*		_selPalette;
    IlUShort		_thickness;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGaugeInteractor : public IlvInteractor
{
public:

    typedef void (*Callback)(IlvGauge*, IlFloat, IlAny);

    IlvGaugeInteractor(Callback	callback	= 0,
		       IlAny	callbackArg	= 0,
		       Callback	dragCallback	= 0,
		       IlAny	dragCallbackArg = 0);

    virtual IlBoolean	handleEvent(IlvGraphic*			obj,
				    IlvEvent&			event,
				    const IlvTransformer*	t);
    virtual IlBoolean	accept(const IlvGraphic*) const;

    virtual void	valueChanged(IlvGauge* gauge, IlFloat   value);
    virtual void        draggedValueChanged(IlvGauge* gauge, IlFloat   value);

    virtual IlBoolean   invalidValueSet(IlvGauge*, IlFloat);

    DeclareLazyInteractorTypeInfoRO(IlvGaugeInteractor);

protected:
    Callback		_callback;
    IlAny		_callbackarg;
    Callback		_dragCallback;
    IlAny		_dragCallbackarg;
};

ILVVWSMODULEINIT(g0gauge);
ILVVWSMODULEINIT(g0relgauge);
#endif /* !__Graphics_Ilv_GaugeH */
