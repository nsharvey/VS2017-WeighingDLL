// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/scombo.h
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
// Declaration of the IlvScrolledComboBoxHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Scombo_H
#define __Ilv_Gadgets_Motif_Scombo_H

#ifndef __Ilv_Gadgets_Scombo_H
# include <ilviews/gadgets/scombo.h>
#endif
#ifndef __Ilv_Gadgets_motif_Combo_H
# include <ilviews/gadgets/motif/combo.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvScrolledComboBoxMLFHandler
    : public IlvDefaultScrolledComboBoxLFHandler
{
public:
    IlvScrolledComboBoxMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	setSelectionCursor(IlvScrolledComboBox*);
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfscombo);

#endif /* !__Ilv_Gadgets_Motif_Combo_H */
