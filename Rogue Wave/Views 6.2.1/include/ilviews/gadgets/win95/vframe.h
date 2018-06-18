// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/vframe.h
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
// Declaration of the IlvViewFrameW95LFHandler classes
// Defined in library ilvaw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Vframe_H
#define __Ilv_Gadgets_Win95_Vframe_H

#if !defined(__Ilv_Gadgets_Vframe_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/vframe.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/vframe.h>
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
class ILVADVW95LOOKEXPORTED IlvViewFrameW95LFHandler
    : public IlvDefaultViewFrameLFHandler
{
public:
    IlvViewFrameW95LFHandler(IlvLookFeelHandler*);
    ~IlvViewFrameW95LFHandler();

    virtual void	drawFrame(const IlvViewFrame* vframe,
				  const IlvGadget* gadget,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const;
};

// --------------------------------------------------------------------------
ILVADVW95LOOKMODULEINIT(w9fvfram);

#endif /* !__Ilv_Gadgets_Win95_Vframe_H */
