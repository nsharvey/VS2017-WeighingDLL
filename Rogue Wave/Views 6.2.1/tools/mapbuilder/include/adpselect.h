// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/adpselect.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the AdapterSelector class
// -------------------------------------------------------------------------

#ifndef _AdapterSelector_h_
#define _AdapterSelector_h_

#include <ilviews/gadgets/rectgadc.h>

#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/projection/projdict.h>
#include <ilviews/maps/adapter.h>
#include <ilviews/maps/unitconv.h>

class IlvGadgetContainerRectangle;
class IlvScrolledComboBox;
class IlvViewRectangle;
class IlvMapAdapter;
class IlvToggle;
class IlvTextField;
class IlvLabel;
class IlvSelector;

// --------------------------------------------------------------------------
class AdapterSelector
    : public IlvGadgetContainerRectangle
{
public:
    AdapterSelector(IlvDisplay* display,
		    const IlvRect& rect,
		    IlDouble defaultPrecision = 1.0,
		    const IlvUnitConverter* = IlvUnitConverter::METERS());
    virtual ~AdapterSelector();

    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    IlvMapAdapter* getAdapter(const IlvProjection* projection);

    // Internal use
    void setUnitIsMetric(IlBoolean b);
private:

    IlvTextField* _metersTF;
    IlvToggle*    _metersRadio;

    IlvTextField* _unitsTF;
    IlvToggle*    _unitsRadio;
    IlvLabel*     _unitsLabel;

    IlvSelector*  _selector;

    IlvScrolledComboBox* _unitsCombo;
    IlBoolean _unitIsMetric;

    IlDouble _defaultPrecision;
    IlvUnitConverter* _defaultConverter;
};
#endif
