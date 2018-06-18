// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/arrowb.h
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
// Declaration of the IlvArrowButtonW95LFHandler class
// Defined in library ilvaw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Arrowb_H
#define __Ilv_Gadgets_Win95_Arrowb_H

#if !defined(__Ilv_Gadgets_Windows_Arrowb_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/arrowb.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/arrowb.h>
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
class ILVADVW95LOOKEXPORTED IlvArrowButtonW95LFHandler
: public IlvArrowButtonWLFHandler
{
public:
    IlvArrowButtonW95LFHandler(IlvLookFeelHandler*);
    virtual void drawFrame(const IlvArrowButton*,
			   IlvPort*,
			   const IlvTransformer*,
			   const IlvRegion*) const;
    virtual void drawContents(const IlvArrowButton*,
			      IlvPort*,
			      const IlvTransformer*,
			      const IlvRegion*) const;
};

// --------------------------------------------------------------------------
ILVADVW95LOOKMODULEINIT(w9farrb);

#endif /* !__Ilv_Gadgets_Win95_Arrowb_H */
