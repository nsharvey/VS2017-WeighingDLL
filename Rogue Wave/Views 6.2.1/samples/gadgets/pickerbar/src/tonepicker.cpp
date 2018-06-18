// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/src/tonepicker.cpp
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
// Definition of the Selector control.
// --------------------------------------------------------------------------
#include <tonepicker.h>
#include <palettechanger.h>

static const char* noteNames[] = { "A", "B", "C", "D", "E", "F", "G" };
static const char* noteColors[] = {
    "red",
    "orange",
    "yellow",
    "green",
    "darkslateblue",
    "blue",
    "purple"
};
const int TonePicker::_nTones = 7;

// --------------------------------------------------------------------------
TonePicker::TonePicker(IlvDisplay* display,
		       const IlvRect& location)
: PickerBar(display,
	    _nTones, noteNames,
	    location)
{
    setAntialiasingMode(IlvUseAntialiasingMode);
    setBarHorizontalMargin(1);
    setBackground(display->getColor("snow"));
    setKnobHorizontalMargin(3);
    setKnobVerticalMargin(3);
    for (int loop = 0; loop < _nTones; loop++) {
	_labelPalettes[loop] = PaletteChanger(getPalette())
			       .setForeground(noteColors[loop])
			       .setAntialiasingMode(IlvUseAntialiasingMode)
			       .get();
	_labelPalettes[loop]->lock();
	IlvFloat hue, saturation, value;
	IlvColor* noteColor = display->getColor(noteColors[loop]);
	noteColor->getHSV(hue,saturation,value);
	_knobPalettes[loop] = PaletteChanger(getPalette())
			      .setForeground(noteColor)
			      .setHSVBackground(hue,saturation/2,.90f)
			      .setLineWidth(2)
			      .setAntialiasingMode(IlvUseAntialiasingMode)
			      .get();
	_knobPalettes[loop]->lock();
    }
    _knobLabelPalette = PaletteChanger(getPalette())
			.setForeground(getPalette()->getBackground())
			.setFont("%Arial-18-B")
			.setAntialiasingMode(IlvUseAntialiasingMode)
			.get();
    _knobLabelPalette->lock();
}

// --------------------------------------------------------------------------
TonePicker::~TonePicker()
{
    for (int loop = 0; loop < _nTones; loop++) {
	_labelPalettes[loop]->unLock();
	_knobPalettes[loop]->unLock();
    }
    _knobLabelPalette->unLock();
}

// --------------------------------------------------------------------------
IlvPalette*
TonePicker::getLabelPalette(IlUInt index) const
{
    return _labelPalettes[index];
}

// --------------------------------------------------------------------------
IlvPalette*
TonePicker::getKnobPalette(IlUInt index) const
{
    return _knobPalettes[index];
}

// --------------------------------------------------------------------------
IlvPalette*
TonePicker::getKnobLabelPalette(IlUInt index) const
{
    return _knobLabelPalette;
}
