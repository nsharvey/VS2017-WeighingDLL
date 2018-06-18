// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/src/shiftcar.cpp
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
// Demonstrating the shift scrolling mode of charts.
// --------------------------------------------------------------------------

#include <shiftcar.h>

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
// Some constants used for the sample
#define DefaultTimerPeriod	 50
#define NbAddedPts		  4
#define MaxPoints		400
#define MinOrd			  0.0
#define MaxOrd			  6.0
#define XStep			  0.002
#define NbShownPts		400
#define NbDisplayers		  6
#define Amplitude		  6.0  // MaxOrd - MinOrd;

static const IlBoolean FastScrollCar   = IlTrue;
static IlvChartDataPointInfo* PtInfosCar[2];

// --------------------------------------------------------------------------
// - Returns a point information depending on the value of the point
// Get a color from a value.
IlvChartDataPointInfo*
GetInfoFromValueShiftcar(IlvDisplay* dpy, IlDouble value)
{
    if (value > 2.5) {
        return PtInfosCar[0];
    }
    return PtInfosCar[1];
}

// --------------------------------------------------------------------------
static void
RunTimerShiftcar(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
SuspendTimerShiftcar(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
// Timer callback to add points.
static void
AddPointsShiftcar(IlvTimer* timer, IlAny arg)
{
    static IlUInt cpt = 0;
    IlvChartGraphic* chart = (IlvChartGraphic*)arg;
    IlvDisplay* display = chart->getDisplay();

    if (!FastScrollCar) {
	chart->getHolder()->initRedraws();
    }

    IlUInt dispCount = chart->getDisplayersCount();
    IlDouble amplitude = Amplitude / dispCount;

    for (IlUInt k = 0; k < dispCount; ++k) {
	IlvChartDataSet* dataSet = chart->getDataSet(k);
	if (FastScrollCar) {
	    dataSet->startBatch();
	}
	IlUInt count = dataSet->getDataCount();
	IlDouble randVal = rand() % 3 + 1;
	IlDouble val;
	IlDouble newX = cpt;
	for (IlUInt i = 0; i < NbAddedPts; ++i ,++count) {
	    val = IlvPi * count * XStep * randVal;
	    val = IlAbs(amplitude * cos(val) * sin(2 * val)) + k * amplitude;
	    IlvChartDataPointInfo* ptInfo =
		GetInfoFromValueShiftcar(display, val);
	    dataSet->addPoint(IlvDoublePoint(newX, val), ptInfo);
	    ++newX;
	}
	if (FastScrollCar) {
	    dataSet->endBatch();
	}
    }
    if (!FastScrollCar)	 {
	chart->getHolder()->reDrawViews();
    }
    cpt += NbAddedPts;
    //chart->updateAndReDraw();
}

// --------------------------------------------------------------------------
// Panel class for sample Shiftcar
// --------------------------------------------------------------------------
Shiftcar::Shiftcar(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initShiftcar();
}

// --------------------------------------------------------------------------
Shiftcar::~Shiftcar()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Shiftcar::initShiftcar()
{
    IlvDisplay* dpy = getDisplay();

    // Create the point information used to associate colors with data points
    PtInfosCar[0] =
	new IlvChartDataPointInfo(GetPalette(dpy, "gray", "cornflowerblue"));
    PtInfosCar[0]->lock();
    PtInfosCar[1] =
	new IlvChartDataPointInfo(GetPalette(dpy, "gray", "coral"));
    PtInfosCar[1]->lock();

    // Create the chart
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("lightsteelblue"),
				      dpy->getColor("white"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    IlvPalette* pal = dpy->getPalette(dpy->getColor("lightsteelblue"),
				      0,
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
    IlvPalette* gridPal =
	dpy->getPalette(0, dpy->getColor("lightgray"), 0, 0, 0);
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,
			      IlvRect(0,0,800,600),
			      IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      pal,
			      gridPal);
    chart->setDataAreaBackground(dpy->getColor("white"));
    chart->setFillMode(IlvChartGraphic::FillDataAndGraphArea);
    chart->setDrawOrder(IlvDrawBelow);

    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0,
								NbShownPts));
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(MinOrd,
								MaxOrd));

    IlvSingleScaleDisplayer* scale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater;

    scale = chart->getOrdinateSingleScale();
    updater = new IlvConstantScaleStepsUpdater(scale);
    delete IlvScaleStepsUpdater::Set(scale, updater);
    updater->fixStepUnit(1., 0.1);

    // Add the data.
    IlUInt i;
    char buf[32];
    IlvChartDataSet* dataSets[NbDisplayers];
    for (i = 0; i < NbDisplayers; ++i) {
	sprintf(buf, "Series#%d", (int)i);
	dataSets[i] =
	    new IlvChartCyclicPointSet(buf, new IlvPointInfoCyclicArray());
	dataSets[i]->setMaxCount(MaxPoints);

    }
    IlUInt count = NbDisplayers;
    chart->getData()->setDataSets(count,dataSets);

    IlvPalette** palettes = GetPalettes(dpy, NbDisplayers);
    for (i = 0; i < NbDisplayers; ++i) {
	chart->addDisplayer(new IlvPolylineChartDisplayer(palettes[i]),
			    dataSets[i]);
    }
    delete [] palettes;

    // Set the scroll mode
    chart->setScrollMode(IlvChartGraphic::IlvScrollModeShift);
    chart->enableFastScroll(FastScrollCar);

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);

    //chart->reDrawWhenNotified(IlFalse);
    // Create and launch the timer
    int millisecs = DefaultTimerPeriod;
    IlvTimer* timer =
	new IlvTimer(dpy, 0, millisecs, AddPointsShiftcar, chart);
    timer->run();

    // Add accelerators for  the timer.
    addAccelerator(RunTimerShiftcar, IlvKeyUp, 'r', 0, timer);
    addAccelerator(SuspendTimerShiftcar, IlvKeyUp, 's', 0, timer);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageShiftcar(Pan* mainPanel)
{
    Shiftcar* panel = new Shiftcar(mainPanel,"shiftcar.ilv");
    mainPanel->addPageNoteBook(panel, "Cartesian", "shiftcar.txt");
}
