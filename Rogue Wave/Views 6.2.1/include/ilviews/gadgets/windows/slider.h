// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/slider.h
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
// Declaration of the IlvSliderWLFHandler class
// Defined in library ilvwlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Slider_H
#define __Ilv_Gadgets_Windows_Slider_H

#if !defined(__Ilv_Gadgets_Slider_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/slider.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/slider.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Windows)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVWLOOKEXPORTED IlvSliderWLFHandler : public IlvDefaultSliderLFHandler
{
public:
    IlvSliderWLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawTrack(const IlvSlider*,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawThumb(const IlvSlider*,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	computeBBox(const IlvSlider*,
				    IlvRect&,
				    IlvRect&,
				    const IlvTransformer*) const;
    virtual IlInt	positionToValue(const IlvSlider*,
					const IlvPoint& p,
					const IlvTransformer* t) const;
    virtual void	drawFocus(const IlvSlider*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(const IlvSlider*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const;
    static IlInt	PositionToValue(const IlvSlider*,
					IlvDim size,
					const IlvPoint& p,
					const IlvTransformer* t);
};

// --------------------------------------------------------------------------
ILVWLOOKMODULEINIT(wlfslid);

#endif /* !__Ilv_Gadgets_Windows_Slider_H */
