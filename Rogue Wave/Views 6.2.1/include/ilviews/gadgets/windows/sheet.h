// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/sheet.h
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
// Declaration of the IlvSheetWLFHandler class
// Defined in library ilvawlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Sheet_H
#define __Ilv_Gadgets_Windows_Sheet_H

#if !defined(__Ilv_Gadgets_Sheet_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/sheet.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/sheet.h>
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
class ILVADVWLOOKEXPORTED IlvSheetWLFHandler
    : public IlvSheetLFHandler
{
public:
    IlvSheetWLFHandler(IlvLookFeelHandler*);

    virtual void	drawFrame(const IlvSheet*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeRects(const IlvSheet*,
				     IlvRect& titleRect,
				     IlvRect& rowRect,
				     IlvRect& colRect,
				     IlvRect& matRect,
				     const IlvTransformer* t) const;
};

// --------------------------------------------------------------------------
ILVADVWLOOKMODULEINIT(wlfsht);

#endif /* !__Ilv_Gadgets_Windows_Sheet_H */
