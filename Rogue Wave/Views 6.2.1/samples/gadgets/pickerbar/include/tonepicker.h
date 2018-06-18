// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/include/tonepicker.h
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
// Declaration of the Selector control.
// --------------------------------------------------------------------------
#ifndef __Ilv_Samples_Tonepicker_H
#define __Ilv_Samples_Tonepicker_H

#include <pickerbar.h>

// --------------------------------------------------------------------------
class TonePicker
: public PickerBar
{
    static const int _nTones;
public:
    TonePicker(IlvDisplay* display,
	       const IlvRect& location);
    virtual ~TonePicker();

    // PickerBar overloads
    virtual IlvPalette* getLabelPalette(IlUInt index) const;
    virtual IlvPalette* getKnobPalette(IlUInt index) const;
    virtual IlvPalette* getKnobLabelPalette(IlUInt index) const;
private:
    IlvPalette* _labelPalettes[7];
    IlvPalette* _knobPalettes[7];
    IlvPalette* _knobLabelPalette;
};
#endif /* !__Ilv_Samples_Tonepicker_H */
