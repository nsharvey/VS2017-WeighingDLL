// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/spinbox.h
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
// Declaration of the IlvSpinBoxVXLFHandler class
// Defined in library ilvavxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Spinbox_H
#define __Ilv_Gadgets_Vx_Spinbox_H

#if !defined(__Ilv_Gadgets_Windows_Spinbox_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/spinbox.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/spinbox.h>
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
class ILVADVVXLOOKEXPORTED IlvSpinBoxVXLFHandler : public IlvSpinBoxWLFHandler
{
public:
    IlvSpinBoxVXLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFrame(const IlvSpinBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeArrowRects(const IlvSpinBox* spin,
					  IlvRect& r1,
					  IlvRect& r2,
					  IlvRect& r3,
					  const IlvTransformer* t) const;
    static void		ComputeArrowRects(const IlvSpinBox* spin,
					  IlvDim spacing,
					  IlvDim aspacing,
					  IlvDim awidth,
					  IlvRect& r1,
					  IlvRect& r2,
					  IlvRect& r3,
					  const IlvTransformer* t);
};

// --------------------------------------------------------------------------
ILVADVVXLOOKMODULEINIT(vxfspi);

#endif /* !__Ilv_Gadgets_Vx_Spinbox_H */
