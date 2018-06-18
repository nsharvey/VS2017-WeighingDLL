// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/radar.h
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
// Declaration of the IlvRadarChart class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Radar_H
#define __Ilv_Charts_Radar_H

#if !defined(__Ilv_Charts_Simplegr_H)
#include <ilviews/charts/simplegr.h>
#endif

#if !defined(__Ilv_Charts_Grid_H)
#include <ilviews/charts/grid.h>
#endif

// --------------------------------------------------------------------------
// Class IlvRadarChart
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRadarChart : public IlvPolarChart
{
public:
    IlvRadarChart(IlvDisplay*	    display,
		  const IlvRect&    bbox,
		  IlBoolean	    useGrid = IlFalse,
		  IlvPalette*	    palette = 0,
		  IlvPalette*	    gridPalette = 0);

    virtual ~IlvRadarChart();

    virtual
    IlBoolean	addDisplayer(IlvAbstractChartDisplayer* displayer,
			     IlUInt count,
			     IlvChartDataSet* const* dataSets,
			     IlvCoordinateInfo* ordinateInfo = 0,
			     IlUInt  position = IlvLastPositionIndex);

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvRadarChart);

protected:
    virtual
    void	validateAutoDataRange(const IlvCoordinateInfo* coord,
				      IlvCoordInterval& range) const;
    virtual
    IlvChartDataListener* createDataListener();
};

class IlvRadarGridDisplayer : public IlvCircularGridDisplayer
{
public:
    IlvRadarGridDisplayer(IlvCircularScaleDisplayer* ref,
			  IlvPalette* major = 0,
			  IlvPalette* minor = 0);

    virtual void	drawTick(IlUInt tickIdx,
				 const IlvPoint& tickPoint,
				 IlDouble tickAngle,
				 IlBoolean major,
				 IlvPort* dst,
				 const IlvRegion* clip) const;

    DeclareGridDisplayerTypeInfoRO(IlvRadarGridDisplayer);
};

ILVCHTMODULEINIT(radar);

#endif /* !__Ilv_Charts_Radar_H */

