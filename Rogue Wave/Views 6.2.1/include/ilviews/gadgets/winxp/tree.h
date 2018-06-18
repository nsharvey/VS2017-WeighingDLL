// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/tree.h
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
// Declaration of the IlvTreeGadgetXPLFHandler class
// Defined in library ilvawxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Tree_H
#define __Ilv_Gadgets_Winxp_Tree_H

#if defined(_WIN32)

#include <ilviews/macros.h>

#include <windows.h>
#include <uxtheme.h>

#if !defined(__Ilv_Gadgets_Win95_Tree_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/win95/tree.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/win95/tree.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Winxp_H)
#  include <ilviews/looks/winxp.h>
#endif
#if !defined(__Ilv_Gadgets_Winxp_Macrosadv_H)
#  include <ilviews/gadgets/winxp/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVWXPLOOKEXPORTED IlvTreeGadgetWXPLFHandler
    : public IlvTreeGadgetW95LFHandler
{
public:
    IlvTreeGadgetWXPLFHandler(IlvLookFeelHandler* lfh);
    ~IlvTreeGadgetWXPLFHandler();

    virtual void	getButtonSize(const IlvTreeGadget*,
				      const IlvTreeGadgetItem*,
				      IlvDim& width,
				      IlvDim& height) const;
    virtual void	drawButton(const IlvTreeGadget*,
				   IlvPort*	     dst,
				   const IlvTreeGadgetItem* item,
				   const IlvRect&     bbox,
				   const IlvRegion*  clip ) const;
    HTHEME		getTheme() const { return _theme; }

protected:
    HTHEME		_theme;
};

// --------------------------------------------------------------------------
ILVADVWXPLOOKMODULEINIT(wxptree);

#endif /* _WIN32 */

#endif /* !__Ilv_Gadgets_Winxp_Tree_H */
