// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/scgadget.h
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
// Declaration of the IlvScrolledGadget class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Scgadget_H
#define __Ilv_Gadgets_Scgadget_H

#if !defined(__Ilv_Base_Iostream_H)
// This include needs to be out of gadget.h because of a limit of the
// preprocessor of msvc5 for the #if blocks.
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#  include <ilviews/gadgets/scrollb.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

class IlvScrolledGadget;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvScrolledGadgetLFHandler : public IlvObjectLFHandler
{
public:
    IlvScrolledGadgetLFHandler(IlvLookFeelHandler* lfh);

    virtual void	setMode(IlvScrolledGadget*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvScrolledGadget*, IlBoolean) const = 0;
    virtual IlvPalette*	getWindowBackground(const IlvScrolledGadget* gadget)
	const = 0;
    virtual void	drawBackground(const IlvScrolledGadget* gadget,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvScrolledGadget* gadget,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvScrolledGadget* gadget,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawScrollBar(const IlvScrolledGadget* gadget,
				      IlvPort* dst,
				      IlvDirection dir,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual void	internalBBox(const IlvScrolledGadget* gadget,
				     IlvRect& rect,
				     const IlvTransformer* t) const = 0;
    virtual void	scrollBarBBox(const IlvScrolledGadget* gadget,
				      IlvOrientation dir,
				      IlvRect& rect,
				      const IlvTransformer* t) const = 0;
    virtual void	getPreferredSize(const IlvScrolledGadget* obj,
					 IlvDim& w,
					 IlvDim& h) const = 0;
    virtual void	visibleBBox(const IlvScrolledGadget* gadget,
				    IlvRect& rect,
				    const IlvTransformer* t) const = 0;
    virtual void	drawFocus(const IlvScrolledGadget*,
				  IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const = 0;
    virtual void	computeFocusRegion(const IlvScrolledGadget*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const=0;
    virtual IlBoolean	handleEvent(IlvScrolledGadget* gadget,
				    IlvEvent& event) const = 0;
    virtual IlBoolean	handleScrollBarsEvent(IlvScrolledGadget* gadget,
					      IlvEvent& event) const = 0;
    virtual IlBoolean	propagateColors() const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultScrolledGadgetLFHandler
    : public IlvScrolledGadgetLFHandler
{
public:
    IlvDefaultScrolledGadgetLFHandler(IlvLookFeelHandler* lf)
	: IlvScrolledGadgetLFHandler(lf)
    {}

    virtual void	drawContents(const IlvScrolledGadget*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawScrollBar(const IlvScrolledGadget*,
				      IlvPort* dst,
				      IlvDirection          dir,
				      const IlvTransformer* t,
				      const IlvRegion*      clip) const;
    virtual void	getPreferredSize(const IlvScrolledGadget* obj,
					 IlvDim& w,
					 IlvDim& h) const;
    virtual void	visibleBBox(const IlvScrolledGadget* obj,
				    IlvRect& bbox,
				    const IlvTransformer* t) const;
    virtual IlBoolean	handleEvent(IlvScrolledGadget* sc,
				    IlvEvent& e) const;
    virtual IlBoolean	handleScrollBarsEvent(IlvScrolledGadget* sc,
					      IlvEvent& event) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvScrolledGadget
    : public IlvGadget,
      public IlvScrollableInterface
{
    friend class IlvDefaultScrolledGadgetLFHandler;
public:

    IlvScrolledGadget(IlvDisplay*	display,
		      const IlvRect&	rect,
		      IlUShort		thickness = IlvDefaultGadgetThickness,
		      IlvPalette*	palette = 0);

    ~IlvScrolledGadget();

    void		showScrollBar(IlvDirection	direction,
				      IlBoolean		redraw = IlTrue);

    void		hideScrollBar(IlvDirection	direction,
				      IlBoolean		redraw = IlTrue);

    virtual
    IlvScrollBar*	createScrollBar(const IlvRect&	rect,
					IlvDirection	direction,
					IlUShort	thickness,
					IlvPalette*	palette);

    void		moveScrollBar(IlvDirection	direction,
				      IlvPosition	where,
				      IlBoolean		redraw = IlTrue);

    void		scrollBarShowAsNeeded(IlBoolean	vertical,
					      IlBoolean	horizontal,
					      IlBoolean	redraw = IlTrue);

    void		getScrollBarShowAsNeeded(IlBoolean& vert,
						 IlBoolean& hor) const;

    inline
    IlvScrollBar*	getScrollBar(IlvDirection direction) const 
			{
			    return direction == IlvHorizontal
				? _hsb
				: _vsb;
			}

    inline
    IlvScrollBar*	getVerticalScrollBar() const { return _vsb; }

    inline
    IlvScrollBar*	getHorizontalScrollBar() const { return _hsb; }

    IlvPosition		whereIsScrollBar(IlvDirection direction) const;

    void		fitToRect(const IlvRect& rect);

    virtual void	internalBBox(IlvRect&			bbox,
				     const IlvTransformer*	t = 0) const;
    inline void		getInternalBBox(IlvRect&		bbox,
					const IlvTransformer*	t = 0) const
			{
			    internalBBox(bbox, t);
			}

    virtual void	visibleBBox(IlvRect&			bbox,
				    const IlvTransformer*	t = 0) const;

    virtual void	scrollBarBBox(IlvDirection		direction,
				      IlvRect&			bbox,
				      const IlvTransformer*	t = 0) const;

    void		computeBBox(IlvRect&			ibox,
				    IlvRect&			vs,
				    IlvRect&			hs,
				    const IlvTransformer*	t = 0) const;

    void		computeBBox(IlvRect&			ibox,
				    IlvRect&			vbox,
				    IlvRect&			vs,
				    IlvRect&			hs,
				    const IlvTransformer*	t = 0) const;

    virtual void	adjustScrollBars(IlBoolean redraw = IlFalse);

    virtual void	scrollableSize(IlvDim& width, IlvDim& height) const;

    virtual void	visibleSize(IlvDim& w, IlvDim& h) const;
    virtual void	limitScrollingValues(IlvDim& w, IlvDim& h) const;

    // Event handling methods
    virtual IlBoolean	handleScrollBarsEvent(IlvEvent& event);

    virtual IlBoolean	handleEvent(IlvEvent& e);

    virtual IlBoolean	handleGadgetEvent(IlvEvent& event);

    // Drawing methods
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;

    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlvPalette*	getWindowBackground() const;

    virtual void	drawFrame(IlvPort*		dst,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;

    virtual void	drawScrollBar(IlvPort* dst,
				      IlvDirection direction,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;


    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip = 0) const;

    // Margins
    inline IlUShort	getLeftMargin() const { return _leftMargin; }

    inline IlUShort	getRightMargin() const { return _rightMargin; }

    inline IlUShort	getTopMargin() const { return _topMargin; }

    inline IlUShort	getBottomMargin() const { return _bottomMargin; }

    inline void		setLeftMargin(IlUShort margin)
			{
			    _leftMargin = margin;
			}

    inline void		setRightMargin(IlUShort margin)
			{
			    _rightMargin = margin;
			}

    inline void		setTopMargin(IlUShort margin)
			{
			    _topMargin = margin;
			}

    inline void		setBottomMargin(IlUShort margin)
			{
			    _bottomMargin = margin;
			}

    inline void		setMargin(IlUShort val)
			{
			    _leftMargin = _rightMargin =
				_topMargin = _bottomMargin = val;
			}

    virtual void	scrollBarVisibilityChanged(IlvDirection direction);

    virtual void	scrollBarHasMoved(IlvDirection direction);

    IlUInt		getCallbackTypes(const char* const** names,
					 const IlSymbol* const** types) const;

    // Bidi interface
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual IlBoolean	setBidiContext(IlvBidiContext*);

    inline static
    IlSymbol*		ScrollBarMovedSymbol()
			{
			    return _sBMovSymbol;
			}
    inline static
    IlSymbol*		SBMovSymbol()
			{
			    return ScrollBarMovedSymbol();
			}

    IlvDefineCallback(ScrollBarMoved);

    inline static
    IlSymbol*		ScrollBarVisibilitySymbol()
			{
			    return _sBVisSymbol;
			}

    IlvDefineCallback(ScrollBarVisibility);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvScrolledGadget);

protected:
    IlvScrolledGadget(IlvDisplay*	display,
		      IlUShort		thickness = IlvDefaultGadgetThickness,
		      IlvPalette*	palette = 0);

    inline IlvDim	getScrollableWidth() const { return _maxWidth; }

    inline void		setScrollableWidth(IlvDim width) { _maxWidth = width; }

    inline IlvDim	getScrollableHeight() const { return _maxHeight; }

    inline void		setScrollableHeight(IlvDim height)
			{
			    _maxHeight = height;
			}

    inline IlvDim	getLimitWidthValue() const { return _maxWidthValue; }

    inline void		setLimitWidthValue(IlvDim value)
			{
			    _maxWidthValue = value;
			}

    inline IlvDim	getLimitHeightValue() const { return _maxHeightValue; }

    inline void		setLimitHeightValue(IlvDim value)
			{
			    _maxHeightValue = value;
			}

    virtual void	adjustScrollBarValue(IlvScrollBar*	scrollbar,
					     IlvDirection	direction);

    virtual
    IlvScrollableInterfaceStruct&	getScrollBarStruct() const;

    virtual void	adjustFromScrollBar(const IlvScrollBar*	scrollbar,
					    IlvDirection	direction);

    void		adjustScrollBarVisibility();
    virtual void	beforeAdjustScrollBarVisibility(const IlvRect&);
    virtual void	afterAdjustScrollBarVisibility(const IlvRect&);
    void		iShowFrame(IlBoolean show);
    void		iShowScrollBar(IlvDirection dir);
    void		iHideScrollBar(IlvDirection dir);
    void		iScrollBarShowAsNeeded(IlBoolean vert, IlBoolean hor);

    IlvDim		_maxHeight;
    IlvDim		_maxHeightValue;
    IlvDim		_maxWidth;
    IlvDim		_maxWidthValue;
    IlUShort		_leftMargin;
    IlUShort		_rightMargin;
    IlUShort		_topMargin;
    IlUShort		_bottomMargin;
    IlvScrollBar*	_hsb;
    IlvScrollBar*	_vsb;
    IlBoolean		_inHsb;
    IlBoolean		_inVsb;
    IlBoolean           _resKeyDown; // return HandleEvent(KeyDown) for KeyUp
    IlBoolean		_handleEventFlag;
    IlUShort		_sbFlags;

    IlvScrollableInterfaceStruct	_scrollBars;

public:
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    void		fitToContents(IlvDirection = (IlvDirection)
				      (IlvHorizontal|IlvVertical));
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	showFrame(IlBoolean show);
    void		showFrame(IlBoolean show, IlBoolean redraw); // Compat
    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual void	setMode(IlvDrawMode mode);
    virtual void	setOverwrite(IlBoolean mode);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	setPalette(IlvPalette*);
    virtual void	setBackground(IlvColor*);
    virtual void	setThickness(IlUShort);
    virtual void	setForeground(IlvColor*);
    IlBoolean		propagateColors() const;
    void		propagateColors(IlBoolean val);
    virtual void	updateLook();

    static IlSymbol*	_verticalScrollbarValue;
    static IlSymbol*	_horizontalScrollbarValue;
    static IlSymbol*	_verticalScrollbarAsNeededValue;
    static IlSymbol*	_horizontalScrollbarAsNeededValue;
    static IlSymbol*	_verticalScrollbarPositionValue;
    static IlSymbol*	_horizontalScrollbarPositionValue;
    static IlSymbol*	_leftMarginValue;
    static IlSymbol*	_rightMarginValue;
    static IlSymbol*	_topMarginValue;
    static IlSymbol*	_bottomMarginValue;
    static IlSymbol*	_sBMovSymbol;
    static IlSymbol*	_sBVisSymbol;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(scgadget);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/scgadget.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/scgadget.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/scgadget.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/scgadget.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/scgadget.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Scgadget_H */
