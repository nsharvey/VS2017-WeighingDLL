// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/sidebyside.h
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
// Declaration of classes to draw side by side charts.
// Contains:
//  - IlvSideBySideChartDisplayer: the root class.
//  - IlvSideBySideBarChartDisplayer: a subclass of IlvSideBySideChartDisplayer
//    which allows you to draw side by side bars.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_SideBySide_H
#define __Ilv_Charts_SideBySide_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

// --------------------------------------------------------------------------
// Class IlvSideBySideChartDisplayer
// --------------------------------------------------------------------------

class ILVCHTEXPORTED IlvSideBySideChartDisplayer
    : public IlvCompositeChartDisplayer
{
public:
    IlvSideBySideChartDisplayer();

    IlvSideBySideChartDisplayer(IlvAbstractChartDisplayer* model,
				IlUInt count,
				IlvPalette* const* palettes = 0);

    IlvSideBySideChartDisplayer(IlvChartDisplayerFactory* factory,
				IlUInt count,
				IlvPalette* const* palettes = 0);

    DeclareChartDisplayerTypeInfoRO(IlvSideBySideChartDisplayer);

protected:
    virtual void	dataSetRemoved(IlUInt index);

    virtual void	updateDisplayers();

};

// --------------------------------------------------------------------------
// Class IlvSideBySideBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvSideBySideBarChartDisplayer
    : public IlvSideBySideChartDisplayer
{
public:

    IlvSideBySideBarChartDisplayer(IlUInt count,
				   IlvPalette* const* palettes = 0);

    DeclareChartDisplayerTypeInfoRO(IlvSideBySideBarChartDisplayer);

protected:
    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);
};

ILVCHTMODULEINIT(sidebyside);

#endif /* !__Ilv_Charts_SideBySide_H */
