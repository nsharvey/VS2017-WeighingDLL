// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/rectscgc.h
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
// Definition of the IlvSCGadgetContainerRectangle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Rectscgc_H
#define __Ilv_Gadgets_Rectscgc_H

#if !defined(__Ilv_Gadgets_Rectgadc_H)
#  include <ilviews/gadgets/rectgadc.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#  include <ilviews/gadgets/scrollb.h>
#endif

class ILVGDTEXPORTED IlvScrolledView;
// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvSCGadgetContainerRectangle
: public IlvGadgetContainerRectangle
{
public:

    IlvSCGadgetContainerRectangle(IlvDisplay* display,
				  const IlvRect& rect,
				  IlvPalette* palette = 0);

    virtual IlvContainer*	getContainer() const;
    virtual IlvGadgetContainer*	getGadgetContainer() const;
    virtual void		makeView(IlvPort*,
					 const IlvTransformer* = 0);

    IlvScrolledView*	getScrolledView() const;
    IlBoolean		isUsingScrollBar(IlvOrientation direction);
    void		useScrollBar(IlvDirection direction,
				     IlBoolean value);
    IlvScrollBar*	getVerticalScrollBar() const;
    IlvScrollBar*	getHorizontalScrollBar() const;
    IlvScrollBar*	getScrollBar(IlvOrientation whichSB) const
	{
	    return (whichSB == IlvVertical)
		   ? getVerticalScrollBar()
		   : getHorizontalScrollBar();
	}
    void		showScrollBar(IlvOrientation direction);
    void		hideScrollBar(IlvOrientation direction);

    void		moveScrollBar(IlvOrientation	direction,
				      IlvPosition	where);
    IlvPosition		whereIsScrollBar(IlvOrientation direction) const;

    virtual void	setBackground(IlvColor*);
    virtual void	setPalette(IlvPalette*);
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	drawContents(IlvPort*,
				     const IlvRect&,
				     const IlvRegion*) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvSCGadgetContainerRectangle);

protected:
    IlvGadgetContainer*	_gadcont;
    IlUShort		_sbFlags;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(rectscgc);

#endif /* !__Ilv_Gadgets_Rectscgc_H */
