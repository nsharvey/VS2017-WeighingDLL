// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/optmenu.h
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
// Declaration of the IlvOptionMenuLFHandler classes
// Defined in library ilvawxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Optmenu_H
#define __Ilv_Gadgets_Winxp_Optmenu_H

#if defined(_WIN32)

#if !defined(__Ilv_Gadgets_Win95_Optmenu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/win95/optmenu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/win95/optmenu.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Winxp_H)
#  include <ilviews/looks/winxp.h>
#endif
#if !defined(__Ilv_Gadgets_Winxp_Macrosadv_H)
#  include <ilviews/gadgets/winxp/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVWXPLOOKEXPORTED IlvOptionMenuWXPLFHandler
    : public IlvOptionMenuW95LFHandler
{
public:
    IlvOptionMenuWXPLFHandler(IlvLookFeelHandler* lfh);
    ~IlvOptionMenuWXPLFHandler();

    virtual void	drawFrame(const IlvOptionMenu*,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const;
    virtual void	drawBackground(const IlvOptionMenu*,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawArrow(const IlvOptionMenu*,
				  IlvPort*,
			   const IlvRect&,
				  const IlvRegion*) const;
    virtual IlvDim	getMarkerWidth(const IlvOptionMenu*) const;
    virtual void	itemsBBox(const IlvOptionMenu* menu,
				  IlvRect& labRect,
				  IlvRect& relfRect,
				  const IlvTransformer* t) const;
    virtual IlBoolean	handleEvent(IlvOptionMenu*, IlvEvent& event) const;
    HTHEME		getTheme() const { return _theme; }
    HTHEME		getBackgroundTheme() const { return _backgroundTheme; }

protected:
    HTHEME		_theme;
    HTHEME		_backgroundTheme;
};

// --------------------------------------------------------------------------
ILVADVWXPLOOKMODULEINIT(wxpoptm);

#endif /* _WIN32 */

#endif /* !__Ilv_Gadgets_Winxp_Optmenu_H */
