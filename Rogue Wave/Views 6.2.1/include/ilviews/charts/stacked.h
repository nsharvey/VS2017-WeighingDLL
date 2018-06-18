// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/stacked.h
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
// Declaration of classes to draw stacked charts.
// Contains:
//  - IlvStackedChartDisplayer: the base class.
//  - IlvStackedBarChartDisplayer: a subclass of IlvStackedChartDisplayer
//    which allows you to draw stacked bars.
//  - IlvStackedPolygonChartDisplayer: a subclass of IlvStackedChartDisplayer
//    which allows you to draw stacked areas.
//  - IlvStacked3dBarChartDisplayer: a subclass of IlvStackedChartDisplayer
//    which allows you to draw stacked 3d bars.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Stacked_H
#define __Ilv_Charts_Stacked_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

// --------------------------------------------------------------------------
// Class IlvStackedChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStackedChartDisplayer
    : public IlvCompositeChartDisplayer
{

public:

    //== Constructors =======================

    IlvStackedChartDisplayer(IlBoolean stacked100PerCent = IlFalse);

    IlvStackedChartDisplayer(IlvAbstractChartDisplayer* model,
			     IlUInt count,
			     IlvPalette* const* palettes = 0,
			     IlBoolean stacked100PerCent = IlFalse);

    IlvStackedChartDisplayer(IlvChartDisplayerFactory* factory,
			     IlUInt count,
			     IlvPalette* const* palettes = 0,
			     IlBoolean stacked100PerCent = IlFalse);

    inline IlBoolean	isStacked100PerCent() const
			{
			    return _stacked100PerCent;
			}

    inline void		setStacked100PerCent(IlBoolean b) 
			{
			    _stacked100PerCent = b; update();
			}

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t,
			     const IlvRegion* clip) const;

    virtual IlBoolean	useVirtualDataSets() const;

    virtual
    IlvCombinedChartDataSet* getVirtualDataSet(const IlvChartDataSet* dataSet,
					       IlUInt& index) const;
    virtual IlvAbstractChartDisplayer* 
	getDisplayerForDataSet(const IlvChartDataSet* dataSet) const;

    DeclareChartDisplayerTypeInfo(IlvStackedChartDisplayer);

protected:
    IlBoolean _stacked100PerCent;

    //== Update methods =======================

    virtual void	dataSetRemoved(IlUInt index);

    virtual void	updateVirtualDataSets();

};

// --------------------------------------------------------------------------
// Class IlvStackedBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStackedBarChartDisplayer
    : public IlvStackedChartDisplayer
{
public:

    IlvStackedBarChartDisplayer(IlUInt count,
				IlvPalette* const* palettes = 0,
				IlBoolean stacked100PerCent = IlFalse);


    DeclareChartDisplayerTypeInfoRO(IlvStackedBarChartDisplayer);

protected:
    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);

};

// --------------------------------------------------------------------------
// Class IlvStackedPolygonChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStackedPolygonChartDisplayer
    : public IlvStackedChartDisplayer
{
public:

    IlvStackedPolygonChartDisplayer(IlUInt count,
				    IlvPalette* const* palettes = 0,
				    IlBoolean stacked100PerCent = IlFalse);

    DeclareChartDisplayerTypeInfoRO(IlvStackedPolygonChartDisplayer);

protected:
    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);
};

// --------------------------------------------------------------------------
// Class IlvStacked3dBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStacked3dBarChartDisplayer
    : public IlvStackedChartDisplayer
{
public:

    IlvStacked3dBarChartDisplayer(IlUInt count,
				  IlvPalette* const* palettes = 0,
				  IlBoolean stacked100PerCent = IlFalse);

    DeclareChartDisplayerTypeInfoRO(IlvStacked3dBarChartDisplayer);

protected:
    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);

    virtual void	updateDisplayers();
};

ILVCHTMODULEINIT(stacked);

#endif /* !__Ilv_Charts_Stacked_H */
