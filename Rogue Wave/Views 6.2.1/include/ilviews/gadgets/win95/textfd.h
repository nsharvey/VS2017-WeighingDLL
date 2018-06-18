// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/textfd.h
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
// Declaration of the IlvTextFieldW95LFHandler class
// Defined in library ilvw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Textfd_H
#define __Ilv_Gadgets_Win95_Textfd_H

#if !defined(__Ilv_Gadgets_Windows_Textfd_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/textfd.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/textfd.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Win95_H)
#  include <ilviews/looks/win95.h>
#endif
#if !defined(__Ilv_Gadgets_Win95_Macros_H)
#  include <ilviews/gadgets/win95/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVW95LOOKEXPORTED IlvTextFieldW95LFHandler
    : public IlvTextFieldWLFHandler
{
public:
    IlvTextFieldW95LFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvTextField*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvTextField*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
};

// --------------------------------------------------------------------------
ILVW95LOOKMODULEINIT(w9ftfd);

#endif /* !__Ilv_Gadgets_Win95_Textfd_H */
