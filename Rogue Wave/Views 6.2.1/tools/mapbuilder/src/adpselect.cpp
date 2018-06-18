// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/adpselect.cpp
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
// The implementation of AdapterSelector methods.
// --------------------------------------------------------------------------
#include "adpselect.h"

#include <ilviews/manager/manager.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/graphics/rectview.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/label.h>

#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/toggle.h>

#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/projitf.h>
#include <ilviews/maps/adapter.h>
#include <ilviews/maps/mapinfo.h>

#if defined(IL_STD)
#  include <cstring>
ILVSTDUSE
#else  /* !IL_STD */
#  include <string.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
void
SelectorCB(IlvGraphic* source,IlvAny arg)
{
    AdapterSelector* selector = (AdapterSelector*)arg;
    IlShort which = ((IlvSelector*)source)->whichSelected();

    if (which == 0) {
	selector->setUnitIsMetric(IlTrue);
    }
    else if (which == 1) {
	selector->setUnitIsMetric(IlFalse);
    }
}

// --------------------------------------------------------------------------
void
TextFieldCB(IlvGraphic* source, IlvAny arg)
{
    IlvTextField* field = (IlvTextField*)source;
    IlFloat value = field->getFloatValue();
    if (value <= 0) {
	const char* label = field->getLabel();
	field->setSelection(0,(IlShort)strlen(label));
    }
}

// --------------------------------------------------------------------------
AdapterSelector::AdapterSelector(IlvDisplay* display,
				 const IlvRect& rect,
				 IlDouble defaultPrecision,
				 const IlvUnitConverter* defaultUnit)
: IlvGadgetContainerRectangle(display,rect),
  _unitIsMetric(IlTrue),
  _defaultPrecision(defaultPrecision),
  _defaultConverter(defaultUnit->copy())
{
}

// --------------------------------------------------------------------------
AdapterSelector::~AdapterSelector()
{
    if (_defaultConverter) {
	delete _defaultConverter;
    }
}

// --------------------------------------------------------------------------
IlvView*
AdapterSelector::createView(IlvAbstractView* parent,
			    const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent,rect);

    IlvGadgetContainer* container = (IlvGadgetContainer*)view;

    // Compute some sizes
    _metersTF = new IlvTextField(parent->getDisplay(), IlvPoint(0, 0),
				 "000000");
    _metersTF->fitToLabel();
    _metersTF->setValue((IlFloat)_defaultPrecision);
    _metersTF->addCallback(TextFieldCB,this);
    _metersTF->addFocusOutCallback(TextFieldCB,this);

    _metersTF->setChangeFocusOnValidation(IlFalse);

    _unitsTF = new IlvTextField(parent->getDisplay(), IlvPoint(0, 0),
				"000000");
    _unitsTF->fitToLabel();
    _unitsTF->setValue((IlFloat)_defaultPrecision);
    _unitsTF->addCallback(TextFieldCB,this);
    _unitsTF->addFocusOutCallback(TextFieldCB,this);

    _unitsTF->setChangeFocusOnValidation(IlFalse);

    // Position of TF
#define CHECK_ZONE 50
    IlvRect metersTFRect(CHECK_ZONE,5,_metersTF->w(),_metersTF->h());
    IlvRect unitsTFRect(CHECK_ZONE,5 + _metersTF->h() + 5,_unitsTF->w(),
			_metersTF->h());

    _selector = new IlvSelector();

    // radio buttons
    _metersRadio = new IlvToggle(parent->getDisplay(), IlvPoint(0, 0),
				 (const char*)0);
    _metersRadio->setRadio(IlTrue);
    IlvPoint position((CHECK_ZONE-_metersRadio->w()) / 2,
		      5 + (_metersTF->h() - _metersRadio->h()) / 2);
    _metersRadio->move(position);
    _selector->addObject(_metersRadio);


    _unitsRadio = new IlvToggle(parent->getDisplay(), IlvPoint(0, 0),
				(const char*)0);
    _metersRadio->setRadio(IlTrue);
    position.x((CHECK_ZONE-_unitsRadio->w()) / 2);
    position.y(10 + _metersTF->h() +
	       (_unitsTF->h() - _unitsRadio->h()) / 2);
    _unitsRadio->move(position);
    _selector->addObject(_unitsRadio);

    // Add selector
    container->addObject(_selector);
    _selector->setInteractor(IlvInteractor::Get("Selector"));
    _metersTF->move(metersTFRect.x(),metersTFRect.y());
    container->addObject(_metersTF);
    _unitsTF->move(unitsTFRect.x(),unitsTFRect.y());
    container->addObject(_unitsTF);

    _selector->setSelected(_metersRadio);
    _selector->setClientData(this);
    _selector->setCallback(SelectorCB);
    // unit selector
    const IlvUnitConverter* const* unitConverters = 0;
    IlUInt converterCount;
    unitConverters =
		   IlvUnitConverter::GetRegisteredConverters(converterCount);
    char** labels = new char*[converterCount];
    int meter_index = 0;
    IlUInt i;
    for (i=0; i < converterCount; i++) {
	labels[i] = IlCopyString(unitConverters[i]->getUnit(), IlFalse);
	if (strcmp(labels[i], _defaultConverter->getUnit()) == 0) {
	    meter_index = i;
	}
    }

    _unitsCombo = new IlvScrolledComboBox(parent->getDisplay(),
					  IlvRect(0,0,80,16),
					  (const char*)0,
					  (const char* const*)labels,
					  (IlUShort)converterCount);
    if (labels) {
	for (i = 0; i < converterCount; i++) {
	    if (labels[i]) {
		delete [] labels[i];
	    }
	}
	delete labels;
    }
    _unitsCombo->setVisibleItems(10);
    _unitsCombo->move(_metersTF->w() + _metersTF->x() + 5,
		      _metersTF->y()
		      + ((int)_metersTF->h() - (int)_unitsCombo->h()) / 2);
    container->addObject(_unitsCombo);

    // Label
    _unitsLabel = new IlvLabel(parent->getDisplay(),
			       IlvPoint(_unitsTF->x() + 5
					+ _unitsTF->w(),
					_unitsTF->y() + _unitsTF->h()
					- 2),
			       "manager units");
    container->addObject(_unitsLabel);
    // Select default values
    _unitsCombo->setSelected(meter_index,IlTrue);
    setUnitIsMetric(IlTrue);
    // Return created view
    return view;
}

// --------------------------------------------------------------------------
void
AdapterSelector::setUnitIsMetric(IlBoolean b)
{
    _unitIsMetric = b;
    // change sensitivity
    IlBoolean ms = b;
    IlBoolean us = b ? IlFalse : IlTrue;
    if (_metersTF->isSensitive() != ms) {
	_metersTF->setSensitive(ms);
	_metersTF->reDraw();
    }
    if (_unitsCombo->isSensitive() != ms) {
	_unitsCombo->setSensitive(ms);
	_unitsCombo->reDraw();
    }
    if (_unitsTF->isSensitive() != us) {
	_unitsTF->setSensitive(us);
	_unitsTF->reDraw();
    }
    if (_unitsLabel->isSensitive() != us) {
	_unitsLabel->setSensitive(us);
	_unitsLabel->reDraw();
    }
}

// --------------------------------------------------------------------------
IlvMapAdapter*
AdapterSelector::getAdapter(const IlvProjection* projection)
{
    IlvMapAdapter* adapter = 0;

    if (_selector->whichSelected() == 0) {
	// case of metric specification
	IlDouble metricSpec = _metersTF->getFloatValue();
	// get unit converter
	const IlvUnitConverter* conv =
	    IlvUnitConverter::GetRegisteredConverter(
		_unitsCombo->getSelection());
	// Convert metric to meters
	metricSpec = conv->toMeters(metricSpec);

	// get projection unit converter
	const IlvUnitConverter* pUnit = projection->getUnitConverter();
	IlDouble precision = pUnit->fromMeters(metricSpec);

	adapter = new IlvMapAdapter(precision);
    }
    else if (_selector->whichSelected() == 1) {
	IlDouble precision = _unitsTF->getFloatValue();
	// case of manager units specifications
	adapter = new IlvMapAdapter(precision);
    }
    return adapter;
}
