// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/chartcsc.h
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
// Declaration of the IlvSCGadgetContainer class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Chartcsc_H
#define __Ilv31_Chartcsc_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Chartcnt_H)
#include <ilviews/chartcnt.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvSCChartContainer
: public IlvChartContainer {
public:
    IlvSCChartContainer(IlvAbstractView* parent,
			const IlvRect&   size,
			const IlvRect&   chartsRect,
			const IlvPoint&  legendPosition,
			IlvPosition      legendAlignment = IlvVertical,
			IlvPosition      scalesMask = IlvBottomLeft,
			IlBoolean        useacc  = IlTrue,
			IlBoolean        visible = IlTrue);
    virtual ~IlvSCChartContainer();
    // ____________________________________________________________
    virtual void addChart(IlvAbstractChart*, IlBoolean = IlFalse);
    virtual void insertChart(IlvAbstractChart*, IlBoolean = IlFalse);
    virtual void moveCharts(IlvPos, IlvPos, IlBoolean = IlTrue);
    virtual void reshapeCharts(const IlvRect&, IlBoolean = IlTrue);
    virtual void zoomCharts(IlvDirection, IlFloat, IlFloat,
			    IlFloat, IlFloat, IlBoolean = IlTrue);
    virtual void translateCharts(IlvDirection, IlFloat dx,
				 IlFloat dy, IlBoolean = IlTrue);
    virtual void contentsChanged(IlBoolean redraw = IlTrue);
    virtual void scrollCharts(IlvScrollBar* sb, IlBoolean = IlTrue);
    void scrolledChartsBBox(IlvRect& bbox) const;
    void getScrollBarBBox(IlvRect& bbox, const IlvRect&,
			  IlvOrientation whichSB) const;
    IlvScrollBar* getScrollBar(IlvOrientation whichSB) const;
    IlBoolean isScrollBarVisible(IlvOrientation whichSB) const;
    void showScrollBar(IlvOrientation whichSB, IlBoolean = IlFalse,
		       IlBoolean = IlTrue);
    void hideScrollBar(IlvOrientation whichSB, IlBoolean = IlTrue);
    void moveScrollBar(IlvOrientation whichSB,
		       IlvPosition where, IlBoolean redraw = IlTrue);
    virtual IlBoolean adjustScrollBar(IlvScrollBar*, IlBoolean = IlTrue);
    virtual IlBoolean adjustScrollBars(IlBoolean = IlTrue);
    virtual void scrollBarsChanged(IlUInt mask, IlBoolean = IlTrue);
    IlvPosition whereIsScrollBar(IlvOrientation) const;
    void attachScrollBar(IlvScrollBar*);
    void removeScrollBar(IlvScrollBar*);
    void attachScrollBars(IlvScrollBar* h, IlvScrollBar* v)
	{ attachScrollBar(h); attachScrollBar(v); }
    void removeScrollBars(IlvScrollBar* h, IlvScrollBar* v)
	{ removeScrollBar(h); removeScrollBar(v); }
    IlUShort getScrollBarFlags() const { return _sbFlags; }
    void setScrollBarFlags(IlUShort flags);
    const IlList* getScrollBars() const { return &_scrollBars; }
    static IlSymbol* _scrollProperty;
    IlSymbol* scrollProperty() const { return _scrollProperty; }
protected:
    IlList              _scrollBars;
    IlvScrollBar*       _vScrollBar;
    IlvScrollBar*       _hScrollBar;
    IlvScrollBar*       _activeSB;
    IlInt               _visibleW;
    IlInt               _visibleH;
    IlUShort            _sbFlags;
    void addScrollBarCallback(IlvScrollBar*) const;
    IlvScrollBar* createScrollBar(IlvDirection);
};

ILV31GDTMODULEINIT(chartcsc);
#endif /* __Ilv31_Chartcsc_H */
