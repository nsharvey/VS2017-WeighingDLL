// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/rectgadc.h
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
// Definition of the IlvGadgetContainerRectangle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Rectgadc_H
#define __Ilv_Gadgets_Rectgadc_H

#if !defined(__Ilv_Contain_Rectangl_H)
#  include <ilviews/contain/rectangl.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#  include <ilviews/gadgets/gadcont.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetContainerRectangle
: public IlvContainerRectangle
{
public:

    IlvGadgetContainerRectangle(IlvDisplay*	display,
				const IlvRect&	rect,
				IlvPalette*	palette = 0);


    virtual IlvView*	createView(IlvAbstractView*,
				   const IlvRect&);
    virtual
    IlvGadgetContainer*	getGadgetContainer() const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvGadgetContainerRectangle);
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(rectgadc);

#endif /* __Ilv_Gadgets_Rectgadc_H */
