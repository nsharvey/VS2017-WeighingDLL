// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/slider.h
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
// Declaration of the IlvSliderWXPLFHandler class
// Defined in library ilvwxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Slider_H
#define __Ilv_Gadgets_Winxp_Slider_H

#if defined(_WIN32)

#if !defined(__Ilv_Gadgets_Win95_Slider_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/win95/slider.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/win95/slider.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Winxp_H)
#  include <ilviews/looks/winxp.h>
#endif
#if !defined(__Ilv_Gadgets_Winxp_Macros_H)
#  include <ilviews/gadgets/winxp/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVWXPLOOKEXPORTED IlvSliderWXPLFHandler
    : public IlvSliderW95LFHandler
{
public:
    IlvSliderWXPLFHandler(IlvLookFeelHandler* lfh);
    ~IlvSliderWXPLFHandler();

    virtual void	computeBBox(const IlvSlider*,
				    IlvRect& track,
				    IlvRect& thumb,
				    const IlvTransformer*) const;
    virtual IlInt	positionToValue(const IlvSlider* slider,
					const IlvPoint& point,
					const IlvTransformer* t) const;
    virtual void	drawTrack(const IlvSlider*,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawThumb(const IlvSlider*,
				   IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvSlider*, IlvEvent&) const;
    virtual void	getPreferredSize(const IlvSlider*,
					 IlvDim&,
					 IlvDim&) const;
    HTHEME		getTheme() const { return _theme; }

protected:
    HTHEME		_theme;
};

// --------------------------------------------------------------------------
ILVWXPLOOKMODULEINIT(wxpslid);

#endif /* _WIN32 */

#endif /* !__Ilv_Gadgets_Winxp_Slider_H */
