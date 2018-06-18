// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/scrollb.h
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
// Declaration of the IlvScrollBarWLFHandler class
// Defined in library ilvwlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Scrollb_H
#define __Ilv_Gadgets_Windows_Scrollb_H

#if !defined(__Ilv_Gadgets_Scrollb_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/scrollb.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/scrollb.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Windows)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif
#if !defined(__Ilv_Base_Timer_H)
#  include <ilviews/base/timer.h>
#endif

#define ILVWLF_SBTIMER_BLINK_SEC   0
#define ILVWLF_SBTIMER_BLINK_MILLI 500

// ----------------------------------------------------------------
class IlvWSBTimer
    : public IlvTimer
{
public:
    IlvWSBTimer(const IlvScrollBar* sb, int sec, int milli)
    : IlvTimer(sb->getDisplay(), sec, milli),
      _sb(sb),
      _state(0) {}
    const IlvScrollBar* getSb() const  { return _sb;    }
    int  getState()		       { return _state; }
    void setSb(const IlvScrollBar* sb) { _sb = sb; }
    void resetState()		       { _state = 0;    }
    virtual void doIt();
protected:
    const IlvScrollBar* _sb;
    int			_state;
};

// --------------------------------------------------------------------------
class ILVWLOOKEXPORTED IlvScrollBarWLFHandler
    : public IlvDefaultScrollBarLFHandler
{
public:
    IlvScrollBarWLFHandler(IlvLookFeelHandler* lfh);
    virtual ~IlvScrollBarWLFHandler();

    virtual void	drawBackground(const IlvScrollBar*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvScrollBar*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual IlBoolean	isValidPosition(const IlvScrollBar*,
					const IlvPoint&,
					const IlvTransformer*) const;
    virtual void	drawFocus(const IlvScrollBar*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(const IlvScrollBar*,
					   IlvRegion&,
					   const IlvTransformer*) const;
    virtual void	drawContents(const IlvScrollBar*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawInternal(const IlvScrollBar*,
				     IlvPort*,
				     const IlvRect&,
				     const IlvRect&,
				     const IlvRegion*) const;
    virtual void	drawArrow(const IlvScrollBar*,
				  IlvPosition,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	computeBBox(const IlvScrollBar*,
				    IlvRect&,
				    IlvRect&,
				    IlvRect&,
				    IlvRect&,
				    const IlvTransformer*) const;
    virtual IlBoolean	handleMiddleButton(IlvScrollBar*, IlvEvent&) const;
    virtual IlvDim	getCurrentSize(const IlvScrollBar*) const;
    virtual void	invert(IlvScrollBar*, IlBoolean) const;
    virtual IlvDim	getDefaultSize(IlvOrientation) const;
    virtual IlBoolean	stopTimer(const IlvScrollBar*, IlInt) const;
    virtual void	initFocus(const IlvScrollBar*) const;
    virtual void	stopFocus(const IlvScrollBar*) const;
    IlvWSBTimer*	getTimer() const { return _timer; }
    void		createTimer(const IlvScrollBar*);
    virtual void	destroyTimer(const IlvScrollBar*);
    IlvPalette*		getGrayedPalette(const IlvScrollBar*);
    virtual void	setMode(IlvScrollBar*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvScrollBar*, IlBoolean) const;
    IlvBitmap*		getScrollBitmap(IlvPos pos) const;

private:
    IlvWSBTimer*	_timer;
    IlvPalette*		_grayedPalette;
    IlvBitmap*		_scrolldBitmap;
    IlvBitmap*		_scrolluBitmap;
    IlvBitmap*		_scrolllBitmap;
    IlvBitmap*		_scrollrBitmap;
};

// --------------------------------------------------------------------------
ILVWLOOKMODULEINIT(wlfsb);

#endif /* !__Ilv_Gadgets_Windows_Scrollb_H */
