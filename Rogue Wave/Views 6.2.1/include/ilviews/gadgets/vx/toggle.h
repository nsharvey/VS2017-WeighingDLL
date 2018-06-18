// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/toggle.h
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
// Declaration of the IlvToggleVXLFHandler class
// Defined in library ilvvxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Toggle_H
#define __Ilv_Gadgets_Vx_Toggle_H

#if !defined(__Ilv_Gadgets_Toggle_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/toggle.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/toggle.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Gadgets_Windows_Toggle_H)
#  include <ilviews/gadgets/windows/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Vx_Macros_H)
#  include <ilviews/gadgets/vx/macros.h>
#endif
#if !defined(__Ilv_Looks_Vx_H)
#  include <ilviews/looks/vx.h>
#endif

// --------------------------------------------------------------------------
class ILVVXLOOKEXPORTED IlvToggleVXLFHandler : public IlvToggleWLFHandler
{
public:
    IlvToggleVXLFHandler(IlvLookFeelHandler* lfh);

    virtual IlUShort	getCheckSize() const;
    virtual IlUShort	getXMargin() const;
    virtual void	drawContents(const IlvToggle*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawCheckBox(const IlvToggle*,
				     IlvPort*,
				     const IlvRect&,
				     const IlvRegion*) const;
    virtual void	drawText(const IlvToggle*,
				 IlvPort*,
				 const IlvRect&,
				 const IlvRegion*) const;
    virtual void	setMode(IlvToggle*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvToggle*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVVXLOOKMODULEINIT(vxftog);

#endif /* !__Ilv_Gadgets_Vx_Toggle_H */
