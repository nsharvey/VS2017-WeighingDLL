// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/scmatrix.h
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
// Declaration of the IlvScrolledMatrix class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Scmatrix_H
#define __Ilv31_Scmatrix_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvScrolledMatrix
: public IlvMatrix {
public:
    IlvScrolledMatrix(IlvDisplay* display,const IlvRect& rect,
		      IlUShort nbcol, IlUShort nbrow,
		      IlvDim xgrid=IlvDefaultMatrixWidth,
		      IlvDim ygrid=IlvDefaultMatrixWidth,
		      IlvDim      thickness = IlvDefaultGadgetThickness,
		      IlBoolean   showVSB = IlTrue,
		      IlBoolean   showHSB = IlTrue,
		      IlvPalette* palette = 0);
    IlvScrolledMatrix(IlvInputFile& is, IlvPalette* palette);
    // ____________________________________________________________
    void computeBBox(IlvRect&, IlvRect& v, IlvRect& h,
		     const IlvTransformer* t = 0) const;
    DeclareLazyTypeInfo();
    virtual const char* getDefaultInteractor() const;
    // event handling methods
};

ILV31GDTMODULEINIT(scmatrix);
#endif /* !__Ilv31_Scmatrix_H */
