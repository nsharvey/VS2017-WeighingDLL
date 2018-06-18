// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/spinbox.h
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
// Declaration of the IlvSpinBoxHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Spinbox_H
#define __Ilv_Gadgets_Motif_Spinbox_H

#ifndef __Ilv_Gadgets_Spinbox_H
# include <ilviews/gadgets/spinbox.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvSpinBoxMLFHandler
: public IlvDefaultSpinBoxLFHandler
{
public:
    IlvSpinBoxMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFrame(const IlvSpinBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual IlvDim	getArrowSpacing(const IlvSpinBox* spin) const;
    virtual IlvDim	getFieldSpacing() const;
    virtual IlvDim	getArrowWidth(const IlvSpinBox* spin) const;
    virtual IlBoolean	propagateColors() const;
    virtual void	computeArrowRects(const IlvSpinBox* spin,
					  IlvRect& r1,
					  IlvRect& r2,
					  IlvRect& r3,
					  const IlvTransformer* t) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfspi);

#endif /* !__Ilv_Gadgets_Motif_Spinbox_H */
