// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/optmenu.h
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
// Declaration of the IlvOptionMenuWLFHandler class
// Defined in library ilvawlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Optmenu_H
#define __Ilv_Gadgets_Windows_Optmenu_H

#if !defined(__Ilv_Gadgets_Optmenu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/optmenu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/optmenu.h>
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
class ILVADVWLOOKEXPORTED IlvOptionMenuWLFHandler
    : public IlvDefaultOptionMenuLFHandler
{
public:
    IlvOptionMenuWLFHandler(IlvLookFeelHandler* lfh);
    ~IlvOptionMenuWLFHandler();

    virtual void	drawArrow(const IlvOptionMenu*,
				  IlvPort* dst,
				  const IlvRect& rect,
				  const IlvRegion* clip) const;
    virtual void	drawText(const IlvOptionMenu*,
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
    virtual void	drawContents(const IlvOptionMenu*,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const;
    virtual void	drawFocusBox(const IlvOptionMenu*, IlvPort* dst,
				     IlvRect&,
				     const IlvRegion* clip) const;
    virtual void	drawFocus(const IlvOptionMenu*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(const IlvOptionMenu*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const;
    virtual IlvDim	getMarkerWidth(const IlvOptionMenu*) const;
    virtual void	itemsBBox(const IlvOptionMenu* menu,
				  IlvRect& labRect,
				  IlvRect& relfRect,
				  const IlvTransformer* t) const;
    virtual
    IlvDirection	computeOpenMenuPoint(const IlvOptionMenu* menu,
					     IlvPoint& point) const;
    virtual void	setMode(IlvOptionMenu*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvOptionMenu*, IlBoolean) const;
    virtual IlvPalette*	getSelectionTextPalette(const IlvOptionMenu*) const;
    virtual IlBoolean	handleButtonDrag() const;
    virtual IlBoolean	inArrow(const IlvOptionMenu*, IlvPoint&) const;
    virtual IlvDim	getAdjustWidth() const;
    virtual void	getPreferredSize(const IlvOptionMenu*,
					 IlvDim& w,
					 IlvDim& h) const;
protected:
    IlvBitmap*		_optionBitmap;
};

// --------------------------------------------------------------------------
ILVADVWLOOKMODULEINIT(wlfoptm);

#endif /* !__Ilv_Gadgets_Windows_Optmenu_H */
