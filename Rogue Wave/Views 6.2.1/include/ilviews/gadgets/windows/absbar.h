// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/absbar.h
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
// Declaration of the IlvAbstractBarWLFHandler class
// Defined in library ilvwlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Absbar_H
#define __Ilv_Gadgets_Windows_Absbar_H

#if !defined(__Ilv_Gadgets_Absbar_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/absbar.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/absbar.h>
#    undef ILVSKIPLOOKS
#endif
#endif
#if !defined(__Ilv_Looks_Windows)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVWLOOKEXPORTED IlvAbstractBarWLFHandler
: public IlvDefaultAbstractBarLFHandler
{
public:
    IlvAbstractBarWLFHandler(IlvLookFeelHandler*);
    // ____________________________________________________________
    virtual void drawContents(const IlvAbstractBar*,
			      IlvPort*,
			      const IlvTransformer*,
			      const IlvRegion*) const;
    virtual void drawBackground(const IlvAbstractBar*,
				IlvPort*,
				const IlvTransformer*,
				const IlvRegion*) const;
    virtual void drawFrame(const IlvAbstractBar*,
			   IlvPort*,
			   const IlvTransformer*,
			   const IlvRegion*) const;
    virtual void getInternalBBox(const IlvAbstractBar*,
				 IlvRect&) const;
    virtual void setMode(IlvAbstractBar*,
			 IlvDrawMode) const;
    virtual void setOverwrite(IlvAbstractBar*,
			      IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVWLOOKMODULEINIT(wlfabsbr);

#endif /* !__Ilv_Gadgets_Windows_Absbar_H */
