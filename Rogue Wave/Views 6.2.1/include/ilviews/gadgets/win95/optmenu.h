// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/optmenu.h
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
// Declaration of the IlvOptionMenuW95LFHandler class
// Defined in library ilvaw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Optmenu_H
#define __Ilv_Gadgets_Win95_Optmenu_H

#if !defined(__Ilv_Gadgets_Windows_Optmenu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/optmenu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/optmenu.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Win95_H)
#  include <ilviews/looks/win95.h>
#endif
#if !defined(__Ilv_Gadgets_Win95_Macrosadv_H)
#  include <ilviews/gadgets/win95/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVW95LOOKEXPORTED IlvOptionMenuW95LFHandler
    : public IlvOptionMenuWLFHandler
{
public:
    IlvOptionMenuW95LFHandler(IlvLookFeelHandler* lfh);

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
ILVADVW95LOOKMODULEINIT(w9foptm);

#endif /* !__Ilv_Gadgets_Win95_Optmenu_H */
