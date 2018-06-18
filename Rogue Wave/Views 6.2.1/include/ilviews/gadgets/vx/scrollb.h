// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/scrollb.h
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
// Declaration of the IlvScrollBarVXLFHandler class
// Defined in library ilvvxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Scrollb_H
#define __Ilv_Gadgets_Vx_Scrollb_H

#if !defined(__Ilv_Gadgets_Windows_Scrollb_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/scrollb.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/scrollb.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Vx_H)
#  include <ilviews/looks/vx.h>
#endif
#if !defined(__Ilv_Gadgets_vx_Macros_H)
#  include <ilviews/gadgets/vx/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVVXLOOKEXPORTED IlvScrollBarVXLFHandler : public IlvScrollBarWLFHandler
{
public:
    IlvScrollBarVXLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvScrollBar*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvScrollBar*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawInternal(const IlvScrollBar*,
				     IlvPort*,
				     const IlvRect&,
				     const IlvRect&,
				     const IlvRegion*) const;
    virtual void	drawArrow(const IlvScrollBar*,
				  IlvPosition,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	computeBBox(const IlvScrollBar*,
				    IlvRect&,
				    IlvRect&,
				    IlvRect&,
				    IlvRect&,
				    const IlvTransformer*) const;
    virtual IlBoolean	isValidPosition(const IlvScrollBar*,
					const IlvPoint&,
					const IlvTransformer*) const;
    virtual IlBoolean	stopTimer(const IlvScrollBar*, IlInt) const;
    virtual void	setMode(IlvScrollBar*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvScrollBar*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVVXLOOKMODULEINIT(vxfsb);

#endif /* !__Ilv_Gadgets_Vx_Scrollb_H */
