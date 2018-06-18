// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/scgadget.h
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
// Declaration of the IlvScrolledGadgetWLFHandler class
// Defined in library ilvawlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Scgadget_H
#define __Ilv_Gadgets_Windows_Scgadget_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/scgadget.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/scgadget.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Windows)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macrosadv_H)
#  include <ilviews/gadgets/windows/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVWLOOKEXPORTED IlvScrolledGadgetWLFHandler
    : public IlvDefaultScrolledGadgetLFHandler
{
public:
    IlvScrolledGadgetWLFHandler(IlvLookFeelHandler* lfh);

    virtual IlvPalette*	getWindowBackground(const IlvScrolledGadget*) const;
    virtual void	drawFocus(const IlvScrolledGadget*,
				  IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(const IlvScrolledGadget*,
					   IlvRegion&,
					   const IlvTransformer*
					   t = 0) const;
    virtual void	drawBackground(const IlvScrolledGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvScrolledGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	internalBBox(const IlvScrolledGadget*,
				     IlvRect& rect,
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
ILVADVWLOOKMODULEINIT(wlfscgad);

#endif /* !__Ilv_Gadgets_Windows_Scgadget_H */
