// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/scgadget.h
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
// Declaration of the IlvScrolledGadgetLFHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Scgadget_H
#define __Ilv_Gadgets_Motif_Scgadget_H

#ifndef __Ilv_Gadgets_Scgadget_H
# include <ilviews/gadgets/scgadget.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvScrolledGadgetMLFHandler
    : public IlvDefaultScrolledGadgetLFHandler
{
public:
    IlvScrolledGadgetMLFHandler(IlvLookFeelHandler* lfh);

    virtual IlvPalette*	getWindowBackground(const IlvScrolledGadget*) const;
    virtual void	drawFocus(const IlvScrolledGadget*,
				  IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(const IlvScrolledGadget*,
					   IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	drawBackground(const IlvScrolledGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvScrolledGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	internalBBox(const IlvScrolledGadget*, IlvRect& rect,
				     const IlvTransformer* t) const;
    virtual void	scrollBarBBox(const IlvScrolledGadget* obj,
				      IlvOrientation dir,
				      IlvRect& bbox,
				      const IlvTransformer* t) const;
    virtual IlBoolean	propagateColors() const;
    virtual void	setMode(IlvScrolledGadget*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvScrolledGadget*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfscgad);

#endif /* !__Ilv_Gadgets_Motif_Scgadget_H */


