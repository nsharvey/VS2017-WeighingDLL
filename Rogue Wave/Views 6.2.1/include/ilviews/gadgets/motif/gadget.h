// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/gadget.h
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
// Declaration of the IlvGadgetHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Gadget_H
#define __Ilv_Gadgets_Motif_Gadget_H

#ifndef __Ilv_Base_Gadget_H
# include <ilviews/base/gadget.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvGadgetMLFHandler : public IlvGadgetLFHandler
{
public:
    IlvGadgetMLFHandler(IlvLookFeelHandler*);

    virtual void	computePalettes(IlvGadget*) const;
    virtual void	setMode(IlvGadget*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvGadget*, IlBoolean) const;
    virtual void	drawBackground(const IlvGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	invert(IlvGadget*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfgad);

#endif /* !__Ilv_Gadgets_Motif_Gadget_H */
