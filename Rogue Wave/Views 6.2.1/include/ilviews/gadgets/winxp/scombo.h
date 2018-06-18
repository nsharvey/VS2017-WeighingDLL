// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/scombo.h
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
// Declaration of the IlvScrolledComboBoxWXPLFHandler class
// Defined in library ilvawxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Scombo_H
#define __Ilv_Gadgets_Winxp_Scombo_H

#if defined(_WIN32)

#if !defined(__Ilv_Gadgets_Win95_Scombo_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/win95/scombo.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/win95/scombo.h>
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
class ILVADVWXPLOOKEXPORTED IlvScrolledComboBoxWXPLFHandler
    : public IlvScrolledComboBoxW95LFHandler
{
public:
    IlvScrolledComboBoxWXPLFHandler(IlvLookFeelHandler* lfh);
    ~IlvScrolledComboBoxWXPLFHandler();

    virtual IlBoolean	handleEvent(IlvScrolledComboBox*,
				    IlvEvent& event) const;
};

// --------------------------------------------------------------------------
ILVADVWXPLOOKMODULEINIT(wxpscombo);

#endif /* _WIN32 */
#endif /* !__Ilv_Gadgets_Winxp_Combo_H */