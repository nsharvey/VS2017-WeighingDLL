// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/amenu.h
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
// Declaration of the IlvAbstractMenuHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Amenu_H
#define __Ilv_Gadgets_Motif_Amenu_H

#ifndef __Ilv_Gadgets_Amenu_H
# include <ilviews/gadgets/amenu.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvAbstractMenuMLFHandler
    : public IlvAbstractMenuLFHandler
{
public:
    IlvAbstractMenuMLFHandler(IlvLookFeelHandler*);

    virtual void drawSelection(const IlvAbstractMenu*,
			       IlvPort*,
			       const IlvRect&,
			       const IlvGadgetItem*,
			       const IlvTransformer*,
			       const IlvRegion*) const;
    virtual IlUShort	getSeparatorSize() const;
    virtual IlvPalette*	getSelectionTextPalette(const IlvAbstractMenu*) const;
    virtual void	setMode(IlvAbstractMenu*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvAbstractMenu*, IlBoolean) const;
    virtual IlvPalette*	getInsensitivePalette(const IlvMenuItem*) const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfamenu);

#endif /* !__Ilv_Gadgets_Motif_Amenu_H */
