// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/dockpane.h
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
// Declaration of the IlvDockableVXLFHandler class
// Defined in library ilvavxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Dockpane_H
#define __Ilv_Gadgets_Vx_Dockpane_H

#if !defined(__Ilv_Gadgets_Dockpane_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/dockpane.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/dockpane.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Vx_H)
#  include <ilviews/looks/vx.h>
#endif
#if !defined(__Ilv_Gadgets_Vx_Macrosadv_H)
#  include <ilviews/gadgets/vx/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVVXLOOKEXPORTED IlvDockableVXLFHandler
    : public IlvDefaultDockableLFHandler
{
public:
    IlvDockableVXLFHandler(IlvLookFeelHandler* lfh);
    ~IlvDockableVXLFHandler();

    virtual void	drawGripper(const IlvDockingHandlePane* handle,
				    const IlvGadget* gadget,
				    IlvPort* dst,
				    const IlvRect& rect,
				    IlvDirection direction,
				    const IlvRegion* clip) const;
    virtual void	drawSmallCaption(const IlvDockingHandlePane* handle,
					 const IlvGadget* gadget,
					 IlvPort* dst,
					 const IlvRect& rect,
					 IlvDirection direction,
					 const IlvRegion* clip) const;
    virtual void	drawHideButton(const IlvDockingHandlePane* handle,
				       const IlvButton* button,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual IlvDim	getHandleSize(IlBoolean smallSize) const;
};

// --------------------------------------------------------------------------
ILVADVVXLOOKMODULEINIT(vxfdockp);

#endif /* !__Ilv_Gadgets_Vx_Docpane_H */
