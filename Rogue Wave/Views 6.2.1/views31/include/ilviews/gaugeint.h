// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/gaugeint.h
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
// Declaration of the IlvViewGaugeInteractor class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Gaugeint_H
#define __Ilv31_Gaugeint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Graphics_Gauge_H)
#include <ilviews/graphics/gauge.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif

typedef void (* IlvViewGaugeCallback)(IlvContainer*, IlvGauge*,
				      IlFloat, IlAny);

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewGaugeInteractor
: public IlvViewObjectInteractor {
public:
    IlvViewGaugeInteractor(IlvViewGaugeCallback callback        = 0,
			   IlAny                callbackarg     = 0,
			   IlvViewGaugeCallback dragCallback    = 0,
			   IlAny                dragCallbackarg = 0)
    : IlvViewObjectInteractor(),
      _callback(callback),
      _callbackarg(callbackarg),
      _dragCallback(dragCallback),
      _dragCallbackarg(dragCallbackarg)
    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic*, IlvEvent&, IlvContainer*,
				  IlvTransformer*);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual void valueChanged(IlvContainer* container,
			      IlvGauge*     gauge,
			      IlFloat       value);
    virtual void draggedValueChanged(IlvContainer* container,
				     IlvGauge*     gauge,
				     IlFloat       value);
    virtual IlBoolean invalidValueSet(IlvContainer*, IlvGauge*, IlFloat);
    virtual const char* className() const;
protected:
    IlBoolean			_connected;
    IlvViewGaugeCallback	_callback;
    IlAny			_callbackarg;
    IlvViewGaugeCallback	_dragCallback;
    IlAny			_dragCallbackarg;
};

ILV31VWSMODULEINIT(gaugeint);
#endif /* !__Ilv31_Gaugeint_H */
