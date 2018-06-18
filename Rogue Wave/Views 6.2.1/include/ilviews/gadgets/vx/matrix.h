// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/matrix.h
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
// Declaration of the IlvMatrixVXLFHandler class
// Defined in library ilvavxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Matrix_H
#define __Ilv_Gadgets_Vx_Matrix_H

#if !defined(__Ilv_Gadgets_Windows_Matrix_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/matrix.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/matrix.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Vx_H)
#  include <ilviews/looks/vx.h>
#endif
#if !defined(__Ilv_Gadgets_Vx_Macrosadv_H)
#  include <ilviews/gadgets/vx/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVVXLOOKEXPORTED IlvMatrixVXLFHandler : public IlvMatrixWLFHandler
{
public:
    IlvMatrixVXLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawRelief(const IlvMatrix*,
				   IlUShort,
				   IlUShort,
				   IlvPort*,
				   const IlvRect&,
				   const IlvRect*) const;
    IlvDim		getReliefThickness(const IlvMatrix* m) const;
};

// --------------------------------------------------------------------------
ILVADVVXLOOKMODULEINIT(vxfmat);

#endif /* !__Ilv_Gadgets_Vx_Matrix_H */
