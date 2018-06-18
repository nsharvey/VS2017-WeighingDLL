// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/slider.h
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
// Declaration of the IlvSlider class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Slider_H
#define __Ilv_Gadgets_Slider_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#  include <ilviews/graphics/holder.h>
#endif

class IlvSlider;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvSliderLFHandler : public IlvObjectLFHandler
{
public:
    IlvSliderLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvSlider* slider,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvSlider* slider,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvSlider* slider,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawTrack(const IlvSlider* slider,
				  IlvPort* dst,
				  const IlvRect& rect,
				  const IlvRegion* clip) const = 0;
    virtual void	drawThumb(const IlvSlider* slider,
				  IlvPort* dst,
				  const IlvRect& rect,
				  const IlvRegion* clip) const = 0;
    virtual void	computeBBox(const IlvSlider* slider,
				    IlvRect& track,
				    IlvRect& thumb,
				    const IlvTransformer* t) const = 0;
    virtual IlInt	positionToValue(const IlvSlider* slider,
					const IlvPoint& point,
					const IlvTransformer* t) const = 0;
    virtual void	drawFocus(const IlvSlider*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const = 0;
    virtual void	computeFocusRegion(const IlvSlider*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const=0;
    virtual IlBoolean	handleEvent(IlvSlider* slider,
				    IlvEvent& event) const = 0;
    virtual void	getPreferredSize(const IlvSlider*,
					 IlvDim&,
					 IlvDim&) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultSliderLFHandler : public IlvSliderLFHandler
{
public:
    IlvDefaultSliderLFHandler(IlvLookFeelHandler* lf)
	: IlvSliderLFHandler(lf)
    {}

    virtual void	drawBackground(const IlvSlider*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvSlider*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(const IlvSlider*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvSlider*, IlvEvent& e) const;
    virtual void	getPreferredSize(const IlvSlider*,
					 IlvDim&,
					 IlvDim&) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvSlider : public IlvGadget
{
    friend class IlvSliderTimer;
    friend class IlvDefaultSliderLFHandler;

public:

    IlvSlider(IlvDisplay*	display,
	      const IlvRect&	rect,
	      IlvOrientation	orientation	= IlvLeft,
	      IlUShort		thickness	= IlvDefaultGadgetThickness,
	      IlvPalette*	palette		= 0);

    IlvSlider(IlvDisplay*	display,
	      const IlvPoint&	p,
	      IlvDim		size,
	      IlvOrientation	orientation	= IlvLeft,
	      IlUShort		thickness	= IlvDefaultGadgetThickness,
	      IlvPalette*	palette		= 0);


    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawTrack(IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawThumb(IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette* ,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;

    inline void		setValues(IlInt		min,
				  IlInt		max,
				  IlInt		value,
				  IlvDim	size)
			{
			    _min = min;
			    _max = max;
			    if (min > max) {
				_min = max;
				_max = min;
			    }
			    else {
				_min = min;
				_max = max;
			    }
			    _sliderSize =
				IlMax((IlvDim)1,
				      IlMin(size, (IlvDim)(_max - _min)));
			    _value = IlMin(IlMax(value, _min), _max);
			    _pageIncrement = IlMin(_pageIncrement, _max-_min);
			}

    inline void		setValues(IlInt min, IlInt max, IlInt value)
			{
			    setValues(min, max, value, _sliderSize);
			}

    void		setValue(IlInt value, IlBoolean redraw = IlFalse);

    inline void		getValues(IlInt& min,
				  IlInt&  max,
				  IlInt& value,
				  IlvDim& sSize) const
			{
			    min = _min;
			    max = _max;
			    value = _value;
			    sSize = _sliderSize;
			}

    inline IlInt	getValue() const { return _value; }

    inline IlvDim	getSliderSize() const { return _sliderSize; }

    inline IlInt	getMin() const { return _min; }

    inline IlInt	getMax() const { return _max; }

    inline IlInt	getPageIncrement() const { return _pageIncrement; }

    inline void		setPageIncrement(IlInt value)
			{
			    _pageIncrement = IlMin(value, _max -_min);
			}

    inline
    IlvOrientation	getOrientation() const { return _orientation; }

    inline void		setOrientation(IlvOrientation orientation)
			{
			    _orientation = orientation;
			    if (orientation == IlvVertical)
				_orientation = IlvTop;
			    if (orientation == IlvHorizontal)
				_orientation = IlvLeft;
			}

    IlInt		positionToValue(const IlvPoint& point,
					const IlvTransformer* t = 0) const;

    virtual const char*	getDefaultInteractor() const;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	valueChanged();

    void		setThumbOrientation(IlvOrientation orientation);

    IlvOrientation	getThumbOrientation() const;

    inline IlBoolean	isDragged() const { return _dragging; }
    virtual void	computeBBox(IlvRect&,
				    IlvRect&,
				    const IlvTransformer* = 0) const;

    DeclareGraphicAccessors();

    static IlSymbol*	_orientationValue;
    static IlSymbol*	_minValue;
    static IlSymbol*	_maxValue;
    static IlSymbol*	_valueValue;
    static IlSymbol*	_sliderSizeValue;
    static IlSymbol*	_pageIncrementValue;
    static IlSymbol*	_thumbOrientationValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvSlider);

protected:
    virtual IlBoolean	classFocusable() const;
    void		internalSetValue(IlInt value,
					 IlBoolean reDraw = IlTrue);
    void		iCallValueChanged();
    virtual IlBoolean	iHandleEvent(IlvEvent& event);

    IlInt		_min;
    IlInt		_max;
    IlInt		_value;
    IlvDim		_sliderSize;
    IlvOrientation	_orientation; // Left/Right or Top/Bottom
    IlInt		_pageIncrement;
    IlBoolean		_dragging;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvHSliderInteractor : public IlvHGadgetInteractor
{
public:
    virtual void	valueChanged(IlvSlider*) = 0;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(slider);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    if !defined(__Ilv_Gadgets_Motif_Slider_H)
#      include <ilviews/gadgets/motif/slider.h>
#    endif
#  endif
#  if defined(ILVWINDOWSLOOK)
#    if !defined(__Ilv_Gadgets_Windows_Slider_H)
#      include <ilviews/gadgets/windows/slider.h>
#    endif
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    if !defined(__Ilv_Gadgets_Win95_Slider_H)
#      include <ilviews/gadgets/win95/slider.h>
#    endif
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    if !defined(__Ilv_Gadgets_Winxp_Slider_H)
#      include <ilviews/gadgets/winxp/slider.h>
#    endif
#  endif
#  if defined(ILVVXLOOK)
#    if !defined(__Ilv_Gadgets_Vx_Slider_H)
#      include <ilviews/gadgets/vx/slider.h>
#    endif
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Slider_H */
