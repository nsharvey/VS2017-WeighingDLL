// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/scalecombo.h
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
// Declaration of the ScaleCombo class
// -------------------------------------------------------------------------
#ifndef _ScaleCombo_h_
#define _ScaleCombo_h_

#include <ilviews/gadgets/combo.h>

// -------------------------------------------------------------------------
class ScaleCombo
    : public IlvComboBox
{
public:
    ScaleCombo(IlvDisplay* display,
	       const IlvPoint& point);

    virtual const char* check(IlUShort sh);

    // If a scale is 1/x , this method return x, or a negative value if
    // unknown
    virtual IlDouble getScale();
};

#endif
