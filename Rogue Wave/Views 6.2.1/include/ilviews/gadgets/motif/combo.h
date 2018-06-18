// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/combo.h
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
// Declaration of the IlvComboBoxHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Combo_H
#define __Ilv_Gadgets_Motif_Combo_H

#ifndef __Ilv_Gadgets_Combo_H
# include <ilviews/gadgets/combo.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvComboBoxMLFHandler
    : public IlvDefaultComboBoxLFHandler
{
public:
    IlvComboBoxMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFrame(const IlvComboBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(const IlvComboBox*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawArrow(const IlvComboBox*,
				  IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawFocus(const IlvComboBox*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	setMode(IlvComboBox*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvComboBox*, IlBoolean) const;
    virtual IlvDim	getMenuLeftMargin(const IlvComboBox* cb) const;
    virtual void	getArrowBBox(const IlvComboBox*, IlvRect&) const;
    virtual IlvDim	getAdjustWidth() const;
    virtual IlvDim	getMarkerWidth(const IlvComboBox*) const;
    virtual void	getTextBBox(const IlvComboBox*, IlvRect& rect) const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfcombo);

#endif /* !__Ilv_Gadgets_Motif_Combo_H */
