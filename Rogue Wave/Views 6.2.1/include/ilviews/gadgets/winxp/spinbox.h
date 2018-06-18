// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/spinbox.h
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
// Declaration of the IlvSpinBoxWXPLFHandler classes
// Defined in library ilvawxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Spinbox_H
#define __Ilv_Gadgets_Winxp_Spinbox_H

#if defined(_WIN32)

#include <ilviews/macros.h>

#include <windows.h>
#include <uxtheme.h>

#if !defined(__Ilv_Gadgets_Win95_Spinbox_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/win95/spinbox.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/win95/spinbox.h>
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
class ILVADVWXPLOOKEXPORTED IlvSpinBoxWXPLFHandler
    : public IlvSpinBoxW95LFHandler
{
public:
    IlvSpinBoxWXPLFHandler(IlvLookFeelHandler* lfh);
    ~IlvSpinBoxWXPLFHandler();

    virtual void	drawArrow(const IlvSpinBox*,
				  const IlvArrowButton*,
				  IlvPort*,
				  const IlvTransformer* t,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvSpinBox*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvSpinBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeArrowRects(const IlvSpinBox* spin,
					  IlvRect& r1,
					  IlvRect& r2,
					  IlvRect& r3,
					  const IlvTransformer* t) const;
    virtual IlBoolean	handleEvent(IlvSpinBox*, IlvEvent& e) const;
    HTHEME		getTheme() const { return _theme; }
    HTHEME		getBackgroundTheme() const { return _backgroundTheme; }

protected:
    HTHEME		_theme;
    HTHEME		_backgroundTheme;
};

// --------------------------------------------------------------------------
ILVADVWXPLOOKMODULEINIT(wxpspin);

#endif /* _WIN32 */

#endif /* !__Ilv_Gadgets_Winxp_Spinbox_H */
