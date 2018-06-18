// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/matrix.h
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
// Declaration of the IlvMatrixHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Matrix_H
#define __Ilv_Gadgets_Motif_Matrix_H

#ifndef __Ilv_Gadgets_Matrix_H
# include <ilviews/gadgets/matrix.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvMatrixMLFHandler
    : public IlvDefaultMatrixLFHandler
{
public:
    IlvMatrixMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawRelief(const IlvMatrix*,
				   IlUShort,
				   IlUShort,
				   IlvPort*,
				   const IlvRect&,
				   const IlvRect*) const;
    virtual void	drawSelection(const IlvMatrix*,
				      IlvPort*,
				      const IlvRect&,
				      const IlvRect*) const;
    virtual void	computeRects(const IlvMatrix*,
				     IlvRect& titleRect,
				     IlvRect& rowRect,
				     IlvRect& colRect,
				     IlvRect& matRect,
				     const IlvTransformer* t) const;
    IlvDim		getReliefThickness(const IlvMatrix* m) const;
    virtual IlvPalette*	getSelectionPalette(const IlvMatrix* m) const;
    virtual IlvPalette*	getTextPalette(const IlvMatrix* m) const;
    virtual void	setMode(IlvMatrix*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvMatrix*, IlBoolean) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfmat);

#endif /* !__Ilv_Gadgets_Motif_Matrix_H */
