// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/scrollb.h
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
// Declaration of the IlvScrollBar class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Scrollb_H
#define __Ilv_Gadgets_Scrollb_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#  include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#  include <ilviews/gadgets/menu.h>
#endif

class IlvScrollBar;
#define ILVSCROLLB_INRECT1	1 // Arrow 1
#define ILVSCROLLB_INRECT2	2 // Arrow 2
#define ILVSCROLLB_INSLIDER	3 // slider
#define ILVSCROLLB_INRECT3	4 // Internal rectangle after  the slider.
#define ILVSCROLLB_INRECT4	5 // Internal rectangle before the slider.

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvScrollBarLFHandler : public IlvObjectLFHandler
{
public:
    IlvScrollBarLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvScrollBar* sb,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvScrollBar* sb,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual IlBoolean	isValidPosition(const IlvScrollBar* sb,
					const IlvPoint& point,
					const IlvTransformer* t) const = 0;
    virtual void	drawFocus(const IlvScrollBar*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvScrollBar*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual void	drawContents(const IlvScrollBar* sb,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawInternal(const IlvScrollBar* sb,
				     IlvPort* dst,
				     const IlvRect& internal,
				     const IlvRect& thumb,
				     const IlvRegion* clip) const = 0;
    virtual void	drawArrow(const IlvScrollBar* sb,
				  IlvPosition position,
				  IlvPort* dst,
				  const IlvRect& arrow,
				  const IlvRegion* clip) const = 0;
    virtual void	computeBBox(const IlvScrollBar* sb,
				    IlvRect& arrow1,
				    IlvRect& internal,
				    IlvRect& arrow2,
				    IlvRect& thumb,
				    const IlvTransformer* t) const = 0;
    virtual IlBoolean	handleMiddleButton(IlvScrollBar*, IlvEvent&) const = 0;
    virtual IlvDim	getCurrentSize(const IlvScrollBar*) const = 0;
    virtual void	invert(IlvScrollBar*, IlBoolean) const = 0;
    virtual IlvDim	getDefaultSize(IlvOrientation) const = 0;
    virtual IlBoolean	stopTimer(const IlvScrollBar*, IlInt) const = 0;
    virtual void	initFocus(const IlvScrollBar*) const = 0;
    virtual void	stopFocus(const IlvScrollBar*) const = 0;
    virtual void	destroyTimer(const IlvScrollBar*) = 0;
    virtual void	setMode(IlvScrollBar*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvScrollBar*, IlBoolean) const = 0;

    virtual IlBoolean	handleEvent(IlvScrollBar* sb,
				    IlvEvent& event) const = 0;
    virtual void	getPreferredSize(const IlvScrollBar*,
					 IlvDim&,
					 IlvDim&) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultScrollBarLFHandler
    : public IlvScrollBarLFHandler
{
public:
    IlvDefaultScrollBarLFHandler(IlvLookFeelHandler* lf)
	: IlvScrollBarLFHandler(lf)
    {}

    virtual void	drawContents(const IlvScrollBar*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvScrollBar*, IlvEvent& e) const;
    virtual void	getPreferredSize(const IlvScrollBar*,
					 IlvDim&,
					 IlvDim&) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvScrollBar : public IlvGadget
{
    friend class IlvSBTimer;
    friend class IlvStringList;
    friend class IlvDefaultScrollBarLFHandler;
    friend class IlvScrollBarMLFHandler;
    friend class IlvScrollBarWLFHandler;

public:

    IlvScrollBar(IlvDisplay*    display,
		 const IlvRect& rect,
		 IlvOrientation orientation = IlvVertical,
		 IlUShort       thickness   = IlvDefaultGadgetThickness,
		 IlvPalette*    palette     = 0);

    virtual ~IlvScrollBar();

    void		setMode(IlvDrawMode m);
    void		setOverwrite(IlBoolean value);

    void		setValues(IlInt min,
				  IlInt max,
				  IlInt value,
				  IlInt size);

    inline void		setIncrement(IlInt value)
			{
			    _increment = IlMin(value, _max-_min-_sliderSize);
			    _decrement = _increment;
			}

    inline void		setDecrement(IlInt value)
			{
			    _decrement = IlMin(value, _max-_min-_sliderSize);
			}

    inline void		setPageIncrement(IlInt value)
			{
			    _pageIncrement =
				IlMin(value, _max -_min - _sliderSize);
			    _pageDecrement = _pageIncrement;
		}

    inline void		setPageDecrement(IlInt value)
			{
			    _pageDecrement =
				IlMin(value, _max - _min - _sliderSize);
			}

    void		setValue(IlInt value, IlBoolean redraw = IlFalse);

    inline void		getValues(IlInt& min,
				  IlInt&  max,
				  IlInt& value,
				  IlInt& sliderSize) const
			{
			    min = _min;
			    max = _max;
			    value = _value;
			    sliderSize = _sliderSize;
			}

    inline IlInt	getIncrement() const { return _increment; }

    inline IlInt	getDecrement() const { return _decrement; }

    inline IlInt	getValue() const { return _value; }

    inline IlInt	getPageIncrement() const { return _pageIncrement; }

    inline IlInt	getPageDecrement() const { return _pageDecrement; }

    inline IlInt	getSliderSize() const    { return _sliderSize; }

    inline IlInt	getMin() const { return _min; }

    inline IlInt	getMax() const { return _max; }

    inline
    IlvOrientation	getOrientation() const { return _orientation; }

    inline void		setOrientation(IlvPosition orientation)
			{
			    _orientation = orientation;
			}

    virtual void	invert(IlBoolean temp = IlFalse);
    virtual void	print(IL_STDPREF ostream&, int level = 0) const;

    virtual void	computeBBox(IlvRect& tlArrow,
				    IlvRect& scrollingBox,
				    IlvRect& brArrow,
				    IlvRect& scrollerBox,
				    const IlvTransformer* t = 0) const;

    virtual IlInt	positionToValue(const IlvPoint& point,
					const IlvTransformer* t = 0) const;

    virtual const char*	getDefaultInteractor() const;
    // event handling methods
    virtual IlBoolean	handleEvent(IlvEvent& event);

    virtual void	valueChanged();

    virtual void	drag();

    virtual void	dragged();

    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawInternal(IlvPort*,
				     const IlvRect& internal,
				     const IlvRect& slider,
				     const IlvRegion* clip) const;
    virtual void	drawArrow(IlvPort*,
				  IlvPosition pos,
				  const IlvRect& rect,
				  const IlvRegion* clip) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette* ,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	useDefaultSize(IlBoolean);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;
    inline IlvDim	getOldSize() const { return _oldSize; }
    inline int		getWhichSide() const { return _whichSide; }
    void		applyTransform(const IlvTransformer*);
    static IlvDim	getDefaultSize(IlvDisplay*, IlvOrientation);
    static IlvDim	getDefaultSize(IlvLookFeelHandler*, IlvOrientation);

    DeclareGraphicAccessors();

    static IlSymbol*	_orientationValue;
    static IlSymbol*	_minValue;
    static IlSymbol*	_maxValue;
    static IlSymbol*	_valueValue;
    static IlSymbol*	_sliderSizeValue;
    static IlSymbol*	_incrementValue;
    static IlSymbol*	_decrementValue;
    static IlSymbol*	_pageIncrementValue;
    static IlSymbol*	_pageDecrementValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvScrollBar);

protected:
    IlInt		_min;
    IlInt		_max;
    IlInt		_value;
    IlInt		_sliderSize;
    IlInt		_increment;
    IlInt		_pageIncrement;
    IlInt		_pageDecrement;
    IlInt		_decrement;
    IlvOrientation	_orientation; // Vertical - Horizontal
    IlvDim		_oldSize;
    int			_whichSide; // Windows : internal area to draw inverted
    static IlvTimer*	_timer;

    static void		StopTimer();

    virtual IlBoolean	classFocusable() const;
    // Event handling methods
    void		iCallValueChanged();
    void		iCallDrag();
    IlBoolean		iHandleEvent(IlvEvent&);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvScrollableInterface
{
public:
    virtual ~IlvScrollableInterface();

    class ILVGDTEXPORTED IlvScrollableInterfaceStruct
    {
    public:
	IlvScrollableInterfaceStruct() : _scrollbars(), _movingScrollBar(0) {}

	IlList        _scrollbars;
	IlvScrollBar* _movingScrollBar;
    };
    IlvScrollBar*	getMovingScrollBar() const;
    virtual void	adjustScrollBars(IlBoolean redraw = IlFalse);
    void		attachScrollBar(IlvScrollBar* sb);
    void		detachScrollBar(IlvScrollBar* sb);
    void		detachAllScrollBars();
    void		reDrawScrollBars(IlvDirection = (IlvDirection)
					 (IlvHorizontal | IlvVertical));
    virtual void	scrollableSize(IlvDim& w, IlvDim& h) const = 0;
    virtual void	visibleSize(IlvDim& w, IlvDim& h) const = 0;
    virtual void	limitScrollingValues(IlvDim& w, IlvDim& h) const;
    IlvScrollBar*	getFirstScrollBar(IlvDirection) const;
    IlvScrollBar*	getFirstVerticalScrollBar() const;
    IlvScrollBar*	getFirstHorizontalScrollBar() const;
    static void		GetScrollBarValues(IlvScrollBar*, IlInt*);
    static IlBoolean	CompareScrollBarValues(IlInt*, IlInt*);

protected:
    void		scrollBarCallback(IlvScrollBar* sb);
    virtual IlvScrollableInterfaceStruct& getScrollBarStruct() const = 0;
    virtual void	adjustScrollBarValue(IlvScrollBar*, IlvDirection) = 0;
    void		adjustScrollBarValues(IlvDirection = (IlvDirection)
					      (IlvHorizontal | IlvVertical));
    virtual void	adjustFromScrollBar(const IlvScrollBar*,
					    IlvDirection) = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvHScrollBarInteractor : public IlvHGadgetInteractor
{
public:
    virtual void	drag(IlvScrollBar*) = 0;
    virtual void	valueChanged(IlvScrollBar*) = 0;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(scrollb);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/scrollb.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/scrollb.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/scrollb.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/scrollb.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/scrollb.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Scrollb_H */
