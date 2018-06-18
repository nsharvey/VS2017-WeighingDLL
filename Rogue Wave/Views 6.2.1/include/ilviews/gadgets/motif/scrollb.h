// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/scrollb.h
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
// Declaration of the IlvScrollBarHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Scrollb_H
#define __Ilv_Gadgets_Motif_Scrollb_H

#ifndef __Ilv_Gadgets_Scrollb_H
# include <ilviews/gadgets/scrollb.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvScrollBarMLFHandler
    : public IlvDefaultScrollBarLFHandler
{
public:
    IlvScrollBarMLFHandler(IlvLookFeelHandler* lfh)
	: IlvDefaultScrollBarLFHandler(lfh)  {}

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
				     const IlvRegion* = 0) const;
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
    virtual IlvDim	getCurrentSize(const IlvScrollBar* sb) const;
    virtual void	invert(IlvScrollBar*, IlBoolean) const;
    virtual IlvDim	getDefaultSize(IlvOrientation) const;
    virtual IlBoolean	stopTimer(const IlvScrollBar*, IlInt) const;
    virtual void	initFocus(const IlvScrollBar*) const;
    virtual void	stopFocus(const IlvScrollBar*) const;
    virtual void	destroyTimer(const IlvScrollBar*);
    virtual void	setMode(IlvScrollBar*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvScrollBar*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfsb);

#endif /* !__Ilv_Gadgets_Motif_Scrollb_H */
