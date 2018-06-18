// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/rectscvi.h
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
// Definition of the IlvSCViewRectangle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Rectscvi_H
#define __Ilv_Gadgets_Rectscvi_H

#if !defined(__Ilv__Rectview_H)
#include <ilviews/graphics/rectview.h>
#endif
#if !defined(__Ilv_Gadgets_Scview_H)
#include <ilviews/gadgets/scview.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvSCViewRectangle : public IlvViewRectangle
{
public:

    IlvSCViewRectangle(IlvDisplay* display,
		       const IlvRect& rect,
		       IlvPalette* palette = 0);

    // ____________________________________________________________

    IlvScrolledView*	getScrolledView() const;

    virtual IlvView*	createView(IlvAbstractView* parent,
				   const IlvRect& size);

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvSCViewRectangle);
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(rectscvi);

#endif /* !__Ilv_Gadgets_Rectscvi_H */
