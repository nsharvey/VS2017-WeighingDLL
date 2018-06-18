// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/optmenu.h
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
// Declaration of the IlvOptionMenuVXLFHandler class
// Defined in library ilvavxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Optmenu_H
#define __Ilv_Gadgets_Vx_Optmenu_H

#if !defined(__Ilv_Gadgets_Windows_Optmenu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/optmenu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/optmenu.h>
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
class ILVADVVXLOOKEXPORTED IlvOptionMenuVXLFHandler
    : public IlvOptionMenuWLFHandler
{
public:
    IlvOptionMenuVXLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawArrow(const IlvOptionMenu*,
				  IlvPort* dst,
				  const IlvRect& rect,
				  const IlvRegion* clip) const;
    virtual void	drawFrame(const IlvOptionMenu*,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const;
    virtual void	drawBackground(const IlvOptionMenu*,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    IlvDim		getMarkerWidth(const IlvOptionMenu*) const;
    void		itemsBBox(const IlvOptionMenu* menu,
				  IlvRect& labRect,
				  IlvRect& relfRect,
				  const IlvTransformer* t) const;
    virtual void	drawFocusBox(const IlvOptionMenu*,
				     IlvPort* dst,
				     IlvRect&,
				     const IlvRegion* clip) const;
    virtual IlvDim	getAdjustWidth() const;
    virtual void	getPreferredSize(const IlvOptionMenu*,
					 IlvDim& w,
					 IlvDim& h) const;
};

// --------------------------------------------------------------------------
ILVADVVXLOOKMODULEINIT(vxfoptm);

#endif /* !__Ilv_Gadgets_Vx_Optmenu_H */
