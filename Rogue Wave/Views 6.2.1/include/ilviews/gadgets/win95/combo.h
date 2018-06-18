// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/combo.h
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
// Declaration of the IlvComboBoxW95LFHandler class
// Defined in library ilvw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Combo_H
#define __Ilv_Gadgets_Win95_Combo_H

#if !defined(__Ilv_Gadgets_Windows_Combo_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/combo.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/combo.h>
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
class ILVW95LOOKEXPORTED IlvComboBoxW95LFHandler
    : public IlvComboBoxWLFHandler
{
public:
    IlvComboBoxW95LFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvComboBox*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawArrow(const IlvComboBox*,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawFrame(const IlvComboBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	getArrowBBox(const IlvComboBox*, IlvRect&) const;
    virtual IlvDim	getMenuLeftMargin(const IlvComboBox* cb) const;
    virtual IlvDim	getAdjustWidth() const;
    virtual IlvDim	getMarkerWidth(const IlvComboBox*) const;
    virtual void	getTextBBox(const IlvComboBox*, IlvRect& rect) const;
};

// --------------------------------------------------------------------------
ILVW95LOOKMODULEINIT(w9fcombo);

#endif /* !__Ilv_Gadgets_Win95_Combo_H */
