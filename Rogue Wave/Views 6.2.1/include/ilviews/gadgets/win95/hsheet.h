// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/hsheet.h
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
// Declaration of the IlvHierarchicalSheetW95LFHandler class
// Defined in library ilvaw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Hsheet_H
#define __Ilv_Gadgets_Win95_Hsheet_H

#if !defined(__Ilv_Gadgets_Windows_Hsheet_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/hsheet.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/hsheet.h>
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
class ILVADVW95LOOKEXPORTED IlvHierarchicalSheetW95LFHandler
    : public IlvHierarchicalSheetWLFHandler
{
public:
    IlvHierarchicalSheetW95LFHandler(IlvLookFeelHandler* lfh);
    // ____________________________________________________________
    IlvPalette* getLinkPalette(const IlvHierarchicalSheet* obj) const;
    IlvPalette* getGridPalette(const IlvHierarchicalSheet* obj) const;
};

// --------------------------------------------------------------------------
ILVADVW95LOOKMODULEINIT(w9fhsht);

#endif /* !__Ilv_Gadgets_Win95_Hsheet_H */
