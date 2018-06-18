// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/simplegr.h
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
// Declaration of the IlvCartesianChart and IlvPolarChart classes which  
// are subclasses of IlvChartGraphic.
// Declaration of the IlvPieChartGraphic class which is a subclass of
// IlvPolarChart.
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Simplegr_H
#define __Ilv_Charts_Simplegr_H

#if !defined(__Ilv_Charts_Graphic_H)
#include <ilviews/charts/graphic.h>
#endif

class ILVCHTEXPORTED IlvPieChartDisplayer;

// --------------------------------------------------------------------------
// Class IlvCartesianChart
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCartesianChart : public IlvChartGraphic
{
public:
    IlvCartesianChart(IlvDisplay* display,
		      const IlvRect& bbox,
		      IlBoolean useGrid = IlFalse,
		      IlvCartesianProjector::Orientation
		      orientation = IlvCartesianProjector::IlvXRightYTop,
		      IlvPalette* palette = 0,
		      IlvPalette* gridPalette = 0);

    // Not documented since it does nothing.
    virtual ~IlvCartesianChart();

    // Persistence
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvCartesianChart);

protected:
    void		initScales(IlBoolean, IlvPalette*);

};

// --------------------------------------------------------------------------
// Class IlvPolarChart
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPolarChart : public IlvChartGraphic
{
public:
    IlvPolarChart(IlvDisplay* display,
		  const IlvRect& bbox,
		  IlBoolean useGrid = IlFalse,
		  IlDouble startingAngle = 0.0,
		  IlDouble range=0.0,
		  IlBoolean orientedClockwise = IlFalse,
		  IlvPalette* palette = 0,
		  IlvPalette* gridPalette = 0);

    // Not documented since it does nothing.
    virtual ~IlvPolarChart();

    // Persistence
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvPolarChart);

protected:
    void		initScales(IlBoolean, IlvPalette*);

};

// --------------------------------------------------------------------------
// Class IlvPieChartGraphic
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPieChartGraphicDataListener 
    : public IlvChartGraphicDataListener
{
public:
    IlvPieChartGraphicDataListener(IlvChartGraphic* chart)
	: IlvChartGraphicDataListener(chart) {}

    virtual void	dataPointChanged(const IlvAbstractChartData*,
					 const IlvChartDataSet*,
					 IlUInt,
					 IlBoolean);

    virtual void	dataPointAdded(const IlvAbstractChartData*,
				       const IlvChartDataSet*,
				       IlUInt);

    virtual void	dataPointRemoved(const IlvAbstractChartData*,
					 const IlvChartDataSet*,
					 IlUInt);

    virtual void	endBatch(const IlvAbstractChartData*,
				 const IlvChartDataSet*);

protected:
    void		reDrawChart(const IlvChartDataSet* dataSet);
};

class ILVCHTEXPORTED IlvPieChartGraphic : public IlvPolarChart
{
public:

    IlvPieChartGraphic(IlvDisplay* display,
		       const IlvRect& bbox,
		       IlDouble startingAngle = 0.,
		       IlDouble range = 360.,
		       IlDouble centerRatio = 0.,
		       IlvPalette* palette = 0);

    // Not documented since it does nothing.
    virtual ~IlvPieChartGraphic();

    IlvPieChartDisplayer* addPieDisplayer(IlvChartDataSet* dataSet,
					  IlDouble radiusRatio = 1.,
					  IlvPalette* palette=0);

    IlvPieChartDisplayer* getPieDisplayer(IlUInt index) const;

    inline IlDouble	getCenterRatio() const { return _centerRatio;}

    inline void		setCenterRatio(IlDouble ratio)
			{
			    _centerRatio = ratio;
			}

    inline IlBoolean	isUsingAutoRadius() const { return _autoRadius; }

    void		useAutoRadius(IlBoolean b);

    inline IlDouble	getStartingAngle() const { return _startingAngle; }

    void		setStartingAngle(IlDouble angle);

    inline IlDouble	getRange() const { return _range; }

    void		setRange(IlDouble range);

    virtual void	draw(IlvPort* dst, 
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;


    // Persistence
    DeclareTypeInfo();
    DeclareIOConstructors(IlvPieChartGraphic);

protected:
    IlDouble		_centerRatio;
    IlBoolean		_autoRadius;
    IlDouble		_startingAngle;
    IlDouble		_range;

    virtual IlvPieChartDisplayer* createPieDisplayer(IlDouble radiusRatio,
						     IlDouble startingAngle,
						     IlDouble range) const;

    // Not documented.
    void		updateDisplayersRadius();
    virtual
    IlvChartDataListener* createDataListener();
};

ILVCHTMODULEINIT(simplegr);

#endif /* !__Ilv_Charts_Simplegr_H */
