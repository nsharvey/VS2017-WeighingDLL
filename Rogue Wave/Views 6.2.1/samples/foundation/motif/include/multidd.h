// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/include/multidd.h
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
// Object interactor that implements the Multi Process Motif Drag&Drop of
// IlvGraphic objects
// --------------------------------------------------------------------------

#ifndef __Ilv_SampleMotif_Multidd_H
#define __Ilv_SampleMotif_Multidd_H

#include <ilviews/base/inter.h>

// --------------------------------------------------------------------------
class MotifDragInteractor
: public IlvInteractor {
public:
    MotifDragInteractor(IlvDisplay*   display,
			IlvSystemView widget)
    : IlvInteractor(),
      _display(display),
      _widget(widget)
	{}
    virtual IlvBoolean handleEvent(IlvGraphic*,
				   IlvEvent&,
				   const IlvTransformer*);
    virtual IlvBoolean handleButtonDown(IlvGraphic*,
					IlvEvent&, 
					const IlvTransformer*);
private:
    IlvDisplay*   _display;
    IlvSystemView _widget;
};
#endif /* !__Ilv_SampleMotif_Multidd_H */
