// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/tooltip.h
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
// Declaration of the IlvToolTip class
// Defined in library views
// --------------------------------------------------------------------------

#ifndef __Ilv_Graphics_Tooltip_H
#define __Ilv_Graphics_Tooltip_H

#if !defined(ILVNODEFAULTLOOK)
#include <ilviews/looks/default.h>
#endif
#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Util_Drview_H)
#include <ilviews/util/drview.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvToolTipView : public IlvDrawingView
{
public:
    IlvToolTipView(const IlvView*  transient,
		   const IlvRect&  bbox,
		   IlvPalette*     palette = 0);
    virtual ~IlvToolTipView();

    virtual IlUInt	getVisiblePeriod() const;
    inline
    const IlvView*	getTransient() const { return _transientView; }
    inline IlvPalette*	getPalette() const { return _palette; }
    virtual void	draw(const IlvRegion* clip);
    virtual void	drawContents(IlvPort* dst,
				     const IlvRect&   rect,
				     const IlvRegion* clip) = 0;
    virtual void	hide();
    virtual void	show();

protected:
    IlvBitmap*		_bmp;
    IlvPalette*		_palette;
    const IlvView*	_transientView;
    IlvTimer*		_timer;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvToolTip : public IlvNamedProperty
{
public:
    IlvToolTip(const char*	label,
	       IlvPalette*	palette = 0,
	       IlUShort		xMargin = 4,
	       IlUShort		yMargin = 4,
	       IlvAlignment	alignment = IlvLeft);
    virtual ~IlvToolTip();

    virtual
    const IlSymbol*	getValueName() const;

    inline IlUShort	getXMargin() const { return _xMargin; }

    inline void		setXMargin(IlUShort xMargin) { _xMargin = xMargin; }

    inline IlUShort	getYMargin() const { return _yMargin; }

    inline void		setYMargin(IlUShort yMargin) { _yMargin = yMargin; }

    virtual void	boundingBox(IlvRect&	bbox,
				    IlvDisplay* display = 0) const;

    virtual void	draw(IlvPort*		dst,
			     const IlvRect&	bbox,
			     const IlvRegion*	clip) const;

    inline IlvPalette*	getPalette() const { return _palette; }

    void		setPalette(IlvPalette* palette);

    void		setBackground(IlvColor* color);

    void		setForeground(IlvColor* color);

    inline const char*	getLabel() const { return _label; }

    void		setLabel(const char* label);

    inline IlvAlignment	getAlignment() const { return _alignment; }

    inline void		setAlignment(IlvAlignment alignment)
			{
			    _alignment = alignment;
			}

    inline
    const IlvGraphic*	getGraphic() const { return _graphic; }

    virtual void	init(const IlvView*	view,
			     const IlvGraphic*	graphic,
			     const IlvPoint&	point);

    virtual void	reInit(const IlvView*		view,
			       const IlvGraphic*	graphic,
			       const IlvPoint&		point);

    virtual void	abort(const IlvView*	view,
			      const IlvGraphic*	graphic);

    virtual void	show(IlvView* view, IlvRect& bbox);

    // Static functions for tooltip management
    static void		InitToolTip(const IlvView*,
				    const IlvGraphic*,
				    const IlvPoint&);
    static void		ReinitToolTip(const IlvView*,
				      const IlvGraphic*,
				      const IlvPoint&);
    static void		AbortToolTip(const IlvView*, const IlvGraphic*);
    static void		InitToolTipView(IlvToolTip*, const IlvView*);
    static void		ShowToolTip(IlvToolTip*);

    // Static functions for global properties
    static IlSymbol*	GetSymbol();
    static IlSymbol*	GetLabelValue();
    static IlSymbol*	GetAlignmentValue();
    static IlvToolTip*	GetCurrentToolTip(IlvDisplay*);

    inline
    static IlvToolTip*	GetToolTip(const IlvGraphic* obj) { return Get(obj); }
    static IlvToolTip*	Get(const IlvGraphic*);

    static IlBoolean	IsEnabled();

    static void		Enable(IlBoolean value);

    static IlUInt	GetTimerPeriod() { return _timerPeriod; }

    static inline void	SetTimerPeriod(IlUInt period)
			{
			    _timerPeriod = period;
			}

    inline
    static IlUInt	GetTimerVisibilityPeriod()
			{
			    return _VisibilityPeriod;
			}

    inline static void	SetTimerVisibilityPeriod(IlUInt period)
			{
			    _VisibilityPeriod = period;
			}

    inline
    static IlvPos	GetHorizontalOffset() { return _hOffset; }

    inline static void	SetHorizontalOffset(IlvPos offset)
			{
			    _hOffset = offset;
			}

    inline
    static IlvPos	GetVerticalOffset() { return _vOffset; }

    inline static void	SetVerticalOffset(IlvPos offset)
			{
			    _vOffset = offset;
			}

    static IlvPalette*	GetPalette(const IlvToolTip*, IlvDisplay*);

    inline void		setDisplay(IlvDisplay* d) { _display = d; };

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvToolTip);

private:
    char*		_label;
    IlvPalette*		_palette;
    IlvDisplay*		_display;
    IlUShort		_xMargin;
    IlUShort		_yMargin;
    const IlvGraphic*	_graphic;
    IlvAlignment	_alignment;

    inline void		setGraphic(const IlvGraphic* graphic)
			{
			    _graphic = graphic;
			}
public:
    DeclareValueAccessors();

    static IlUInt	_timerPeriod;
    static IlUInt	_VisibilityPeriod;
    static IlBoolean	_disabled;
    static IlvPos	_hOffset;
    static IlvPos	_vOffset;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvToolTipHandler : public IlvViewHandler
{
public:
    IlvToolTipHandler(IlvView* view = 0);

    virtual ~IlvToolTipHandler();

    virtual void	setView(IlvView* view);
    virtual void	viewDeleted();
    virtual void	lastPointedGraphicDeleted();
    virtual void	handleInput(IlvEvent& event);
    virtual void	handlePointerMoved(IlvEvent&);
    virtual void	handleButtonDragged(IlvEvent&);
    virtual void	handleLeaveWindow(IlvEvent&);

    virtual IlvGraphic*	lastContains(const IlvPoint& point) const = 0;

    virtual void	abortToolTip(IlvGraphic* g);
    virtual void	initToolTip(IlvGraphic* g, const IlvPoint& point);
    virtual void	reinitToolTip(IlvGraphic* g, const IlvPoint& point);

    inline IlvGraphic*	getLastPointedGraphic() const { return _lastPointed; }

protected:
    IlvGraphic*		_lastPointed;

    void		setLastPointedGraphic(IlvGraphic* graphic);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicHolderToolTipHandler : public IlvToolTipHandler
{
public:
    IlvGraphicHolderToolTipHandler();

    virtual IlvGraphic*	lastContains(const IlvPoint& point) const;

    IlvGraphicHolder*	getGraphicHolder() const;

    static IlvGraphicHolderToolTipHandler*	Get(const IlvView* view);

    static IlvGraphicHolderToolTipHandler*
		Set(IlvView* view, IlvGraphicHolderToolTipHandler* handler);
};

ILVVWSMODULEINIT(tooltip);

#endif /* !__Ilv_Graphics_Tooltip_H */
