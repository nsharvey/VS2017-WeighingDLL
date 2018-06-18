// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/gadget.h
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
// Declaration of the IlvGadgetVXLFHandler class
// Defined in library ilvvxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Gadget_H
#define __Ilv_Gadgets_Vx_Gadget_H

#if !defined(__Ilv_Gadgets_Windows_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/gadget.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/gadget.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Vx_H)
#  include <ilviews/looks/vx.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Vx_Macros_H)
#  include <ilviews/gadgets/vx/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVVXLOOKEXPORTED IlvGadgetVXLFHandler : public IlvGadgetWLFHandler
{
public:
    IlvGadgetVXLFHandler(IlvLookFeelHandler*);

    virtual void	computePalettes(IlvGadget*) const;
    virtual void	setMode(IlvGadget*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvGadget*, IlBoolean) const;
    virtual void	drawBackground(const IlvGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
};

// --------------------------------------------------------------------------
#include <ilviews/graphics/relfline.h>
class ILVVXLOOKEXPORTED IlvReliefLineVXLFHandler
    : public IlvDefaultReliefLineLFHandler
{
public:
    IlvReliefLineVXLFHandler(IlvLookFeelHandler* lf)
	: IlvDefaultReliefLineLFHandler(lf) {}

    virtual IlvPalette*	getBottomShadow(const IlvReliefLine*) const;
    virtual IlvPalette*	getTopShadow(const IlvReliefLine*) const;
};

ILVVXLOOKMODULEINIT(vxfgad);

#endif /* !__Ilv_Gadgets_Vx_Gadget_H */
