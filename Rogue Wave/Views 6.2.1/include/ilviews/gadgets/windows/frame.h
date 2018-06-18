// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/frame.h
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
// Declaration of the IlvFrameWLFHandler class
// Defined in library ilvwlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Frame_H
#define __Ilv_Gadgets_Windows_Frame_H

#if !defined(__Ilv_Gadgets_Frame_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/frame.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/frame.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Windows)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif

#define ILVFRAME_WLFH_FIXED_SPACING 10

// --------------------------------------------------------------------------
class ILVWLOOKEXPORTED IlvFrameWLFHandler : public IlvDefaultFrameLFHandler
{
public:
    IlvFrameWLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFrame(const IlvFrame*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(const IlvFrame*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
};

// --------------------------------------------------------------------------
ILVWLOOKMODULEINIT(wlfframe);

#endif /* !__Ilv_Gadgets_Windows_Frame_H */