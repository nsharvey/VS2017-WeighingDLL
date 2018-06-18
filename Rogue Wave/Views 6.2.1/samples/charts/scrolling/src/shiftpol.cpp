// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/src/shiftpol.cpp
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
// Demonstrating the shift scroll mode of polar charts.
// --------------------------------------------------------------------------
#include <shiftpol.h>

#if defined(IL_STD)
IL_STDUSE
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#else  /* !IL_STD */
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
#define DefaultTimerPeriod	 50
#define	MinOrd			-10.0
#define	MaxOrd			 10.0
#define Amplitude		 10.0 /* (MaxOrd - MinOrd) / 2 */
#define	XStep			  5.0

static const IlBoolean		FastScrollPol = IlTrue;
static IlvChartDataPointInfo*	PtInfosPol[3];

// --------------------------------------------------------------------------
// - Returns a point information depending on the value of the point
// Get a color from a value.
IlvChartDataPointInfo*
GetInfoFromValueShiftpol(IlvDisplay* dpy, IlDouble value)
{
    while (value > 360.) {
	value -= 360.;
    }
    return ((value >= 90) && (value < 360))
	? ((value < 180)
	   ? PtInfosPol[0]
	   : ((value < 270)
	      ? PtInfosPol[1]
	      : PtInfosPol[2]))
	: 0;
}

// --------------------------------------------------------------------------
static void
RunTimerShiftpol(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
SuspendTimerShiftpol(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
// - Timer callback to add points.
static void
AddPointsShiftpol(IlvTimer*, IlAny arg)
{
    IlvChartGraphic* chart = IL_CAST(IlvChartGraphic*, arg);
    IlvDisplay* dpy = chart->getDisplay();
    IlUInt count;
    IlvChartDataSet* dataSet;
    IlDouble val, angle;
    // Add one point on each dataSet.
    for (IlUInt i = 0; i < chart->getDataSetsCount(); ++i) {
	dataSet = chart->getDataSet(i);
	count = dataSet->getDataCount();
	angle = count * XStep;
	IlvChartDataPointInfo* ptInfo = 0;
	if (i) {
	    val = Amplitude * sin(2 * IlvDegreesToRadians(angle));
	    ptInfo = GetInfoFromValueShiftpol(dpy, angle);
	}
	else {
	    val = Amplitude * (.5 + .5 * cos(IlvDegreesToRadians(angle)));
	}
	dataSet->addPoint(IlvDoublePoint(angle, val), ptInfo);
    }
}

// --------------------------------------------------------------------------
// Panel class for sample Shiftpol
// --------------------------------------------------------------------------
Shiftpol::Shiftpol(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initShiftpol();
}

// --------------------------------------------------------------------------
Shiftpol::~Shiftpol()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Shiftpol::initShiftpol()
{
    // Display initialization
    IlvDisplay* dpy = getDisplay();

    // Create the point information used to associate colors with data points
    PtInfosPol[0] =
	new IlvChartDataPointInfo(GetPalette(dpy, "gray", "cornflowerblue"));
    PtInfosPol[0]->lock();
    PtInfosPol[1] =
	new IlvChartDataPointInfo(GetPalette(dpy, "gray", "coral"));
    PtInfosPol[1]->lock();
    PtInfosPol[2] =
	new IlvChartDataPointInfo(GetPalette(dpy, "gray", "palegreen"));
    PtInfosPol[2]->lock();

    // Create the chart
    IlvChartGraphic* chart = new IlvPolarChart(dpy, IlvRect(0,0,800,600));
    chart->setFillMode(IlvChartGraphic::FillDataArea);
    IlvGradientPattern* gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("slategray"),
				      dpy->getColor("white"),
				      10,
				      10);
    IlvPalette* palette = dpy->getPalette(dpy->getColor("white"),
					  dpy->getColor("slategray"),
					  0,
					  0,
					  0,
					  0,
					  0,
					  IlvFillGradientPattern,
					  IlvArcPie,
					  IlvEvenOddRule,
					  IlvFullIntensity,
					  IlvDefaultAntialiasingMode,
					  gradientPattern);
    chart->setDataAreaBackgroundPalette(palette);

    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0, 360));
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(MinOrd,
								MaxOrd));

    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepUnit(45., 5.);
    abscissaScale->drawLabelOnCrossings(IlTrue);

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    updater = new IlvConstantScaleStepsUpdater(ordinateScale);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    updater->fixStepsCount(11, 1);
    ordinateScale->setRelativePosition(IlvMinDataPosition, 90);
    chart->addOrdinateGrid(GetPalette(dpy, "gray", "gray"))
        ->setDrawOrder(IlvDrawBelow);

    // Create and ad the data to the chart
    IlvChartDataSet* dataSets[2];
    dataSets[0] = new IlvChartPointSet("DataSet1");
    dataSets[1] = new IlvChartPointSet("DataSet2", new IlvPointInfoArray());
    IlUInt count = 2;
    chart->getData()->setDataSets(count, dataSets, IlFalse);

    // Add the displayers.
    IlvPalette* lpal = GetPalette(dpy, "gray", "red");
    IlvAbstractChartDisplayer* disp =
	new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledCircle, 2,
					    lpal, lpal);
    chart->addDisplayer(disp,dataSets[1]);

    lpal = GetPalette(dpy, "blue", "blue");
    IlvPalette* mpal = GetPalette(dpy, "yellow", "yellow");
    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledSquare,
					       2,
					       mpal,
					       lpal);
    chart->addDisplayer(disp, dataSets[0]);

    // Sets the scroll mode on the chart
    chart->setScrollMode(IlvChartGraphic::IlvScrollModeShift);
    chart->enableFastScroll(FastScrollPol);

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);

    // Create the timer that adds new points
    int millisecs = DefaultTimerPeriod;
    IlvTimer* timer =
	new IlvTimer(dpy, 0, millisecs, AddPointsShiftpol, chart);
    timer->run();
    addAccelerator(RunTimerShiftpol, IlvKeyUp, 'r', 0, timer);
    addAccelerator(SuspendTimerShiftpol, IlvKeyUp, 's', 0, timer);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageShiftpol(Pan* mainPanel)
{
    Shiftpol* panel = new Shiftpol(mainPanel,"shiftpol.ilv");
    mainPanel->addPageNoteBook(panel, "Polar", "shiftpol.txt");
}
