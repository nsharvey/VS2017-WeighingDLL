// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/slider.h
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
// Declaration of the IlvSLiderHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Slider_H
#define __Ilv_Gadgets_Motif_Slider_H

#ifndef __Ilv_Gadgets_Slider_H
# include <ilviews/gadgets/slider.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvSliderMLFHandler
    : public IlvDefaultSliderLFHandler
{
public:
    IlvSliderMLFHandler(IlvLookFeelHandler* lfh);
    virtual void	drawContents(const IlvSlider*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
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
    virtual void	computeSliderBBox(const IlvSlider*,
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
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfslid);

#endif /* !__Ilv_Gadgets_Motif_Slider_H */
