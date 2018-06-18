// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/drview.h
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
// Declaration of the IlvDrawingView class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Drview_H
#define __Ilv_Util_Drview_H

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Region_H)
#include <ilviews/base/region.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDrawingView : public IlvView
{
public:
    IlvDrawingView(IlvAbstractView* parent,
		   const IlvRect&   size,
		   IlBoolean        visible = IlTrue);
    IlvDrawingView(IlvDisplay*     display,
		   IlvSystemView   parent,
		   const IlvRect&  size,
		   IlBoolean       visible = IlTrue);
    IlvDrawingView(IlvDisplay*   display,
		   IlvSystemView available);
    IlvDrawingView(IlvDisplay*    display,
		   const char*    name,
		   const char*    title,
		   const IlvRect& size,
		   IlBoolean      visible = IlTrue);
    IlvDrawingView(IlvDisplay*    display,
		   const char*    name,
		   const char*    title,
		   const IlvRect& size,
		   IlUInt         properties,
		   IlBoolean      visible = IlTrue,
		   IlvSystemView  transientFor = 0);
    ~IlvDrawingView();

    inline IlvDim	previousWidth(IlvDim w)  { return _previousw = w; }
    inline IlvDim	previousHeight(IlvDim h) { return _previoush = h; }
    inline IlvDim	previousWidth() const    { return _previousw;     }
    inline IlvDim	previousHeight() const   { return _previoush;     }
    virtual void	reDraw(const IlvRegion* clip = 0);
    virtual void	draw(const IlvRegion* clip = 0);
    virtual void	handleInput(IlvEvent& event);
    virtual void	handleResize(IlvRect&);
    virtual void	handleExpose(IlvEvent& event);

protected:
    void		init(); // Init Callbacks

    IlvDim		_previousw;
    IlvDim		_previoush;

    DeclareLazyViewProperties();
};

ILVDSPMODULEINIT(drview);

#endif /* !__Ilv_Util_Drview_H */
