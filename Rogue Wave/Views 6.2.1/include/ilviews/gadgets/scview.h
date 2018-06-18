// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/scview.h
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
// Definition of the IlvScrolledView class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Scview_H
#define __Ilv_Gadgets_Scview_H

#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif

#define IlvDefaultScrolledViewWidth 16

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvScrolledView
    : public IlvGadgetContainer,
      public IlvScrollableInterface
{
public:

    IlvScrolledView(IlvAbstractView* parent,
		    const IlvRect&   rect,
		    IlBoolean        visible = IlTrue)
	: IlvGadgetContainer(parent, rect, IlFalse, visible) { init(); }

    IlvScrolledView(IlvDisplay*    display,
		    IlvSystemView  parent,
		    const IlvRect& rect,
		    IlBoolean      visible = IlTrue)
	: IlvGadgetContainer(display, parent, rect, IlFalse, visible){init();}

    IlvScrolledView(IlvDisplay* display, IlvSystemView window)
	: IlvGadgetContainer(display, window, IlFalse)
    {
	init();
    }

    IlvScrolledView(IlvDisplay*    display,
		    const char*    name,
		    const char*    title,
		    const IlvRect& rect,
		    IlBoolean      visible = IlTrue)
	: IlvGadgetContainer(display,
			     name,
			     title,
			     rect,
			     IlFalse,
			     visible)
    {
	init();
    }

    IlvScrolledView(IlvDisplay*    display,
		    const char*    name,
		    const char*    title,
		    const IlvRect& rect,
		    IlUInt         properties,
		    IlBoolean      visible      = IlTrue,
		    IlvSystemView  transientFor = 0)
	: IlvGadgetContainer(display,
			     name,
			     title,
			     rect,
			     properties,
			     IlFalse,
			     visible,
			     transientFor)
    {
	init();
    }
    ~IlvScrolledView();

    virtual void	handleResize(IlvRect& rect);
    virtual IlBoolean	dispatchToObjects(IlvEvent&);
    virtual void	childNotifyAdd(IlvAbstractView* v) ;
    virtual void	childNotifyRemove(IlvAbstractView* v) ;

    IlvView*		getClipView() const { return _clipView; }

    IlvAbstractView*	getScrolledView() const
			{
			    return _clipView ? _clipView->childView(): 0;
			}

    void		reinitialize();
    void		reinitialise() { reinitialize(); } // 2.0 compat.

    IlvScrollBar*	getVerticalScrollBar() const { return _vertical; }

    IlvScrollBar*	getHorizontalScrollBar() const { return _horizontal; }

    IlvScrollBar*	getScrollBar(IlvDirection whichSB) const
			{
			    return (whichSB == IlvVertical)
				? _vertical
				: _horizontal;
			}

    void		showScrollBar(IlvOrientation direction);

    void		hideScrollBar(IlvOrientation direction);

    void		moveScrollBar(IlvOrientation direction,
				      IlvPosition where);

    IlvPosition		whereIsScrollBar(IlvOrientation direction) const;

    void		computeBBoxes(IlvRect& clipView,
				      IlvRect& vsb,
				      IlvRect& hsb) const;
    void		setBackground(IlvColor*);

    virtual void	scrollableSize(IlvDim& w, IlvDim& h) const;
    virtual void	visibleSize(IlvDim& w, IlvDim& h) const;
    virtual void	changeLook();

    void		adjustView();
    virtual IlBoolean	changeOrientation(); // ILVBIDI
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion*      clip = 0);
    virtual void	draw(const IlvRegion* region = 0);
    void		draw(const IlvRegion& region,
			     const IlvRegion* clip = 0);
    virtual void	drawContents(IlvPort* dst,
				     const IlvRect& size,
				     const IlvRegion* clip);

    DeclareLazyViewProperties();

protected:
    void		recomputeBBoxes();
    IlBoolean		iShowScrollBar(IlvOrientation pos);
    virtual IlvScrollableInterfaceStruct& getScrollBarStruct() const;
    virtual void	adjustScrollBarValue(IlvScrollBar* sb,
					     IlvDirection dir);
    virtual void	adjustFromScrollBar(const IlvScrollBar*sb,
					    IlvDirection dir);

    void		init();

    IlvScrollableInterfaceStruct	_scrollBars;
    IlvScrollBar*			_vertical;
    IlvScrollBar*			_horizontal;
    IlUShort				_sbFlags;
    IlvView*				_clipView;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(gscview);

#endif /* !__Ilv_Gadgets_Scview_H */
