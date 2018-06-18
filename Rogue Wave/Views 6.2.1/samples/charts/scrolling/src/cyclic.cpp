// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/src/cyclic.cpp
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
// Demonstrating the cyclic mode of charts.
// --------------------------------------------------------------------------

#include <cyclic.h>

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
#define MinOrd 0
#define MaxOrd 4
#define DefaultTimerPeriod 500

// --------------------------------------------------------------------------
IlDouble
GeneratePointCyclic(IlDouble current)
// A small change relative to current value
// to get a smooth random creation.
{
    IlUShort jump= (rand() % 10);
    IlInt val= (rand() % 11) - 5;
    IlDouble f = (IlDouble)val / (IlDouble)20;
    if (!jump) {
        f = f * 4;
    }
    f += current;
    if (f < MinOrd) {
        f = (IlDouble)(MinOrd + 1);
    }
    if (f > MaxOrd) {
        f = (IlDouble)(MaxOrd - 1);
    }
    return f;
}

// --------------------------------------------------------------------------
IlvColor*
GetAColorCyclic(IlvDisplay* display, IlDouble value)
// Get a color from a value.
{
    return display->getColor((value < 1)
			     ? "red"
			     : ((value < 2)
				? "coral"
				: ((value < 3)
				   ? "green"
				   : "darkgreen")));
}

// --------------------------------------------------------------------------
static void
RunTimerCyclic(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
SuspendTimerCyclic(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
// Timer callback to add points.
static void
AddPointsCyclic(IlvTimer* timer, IlAny arg)
{
    IlvChartGraphic* chart = (IlvChartGraphic*)arg;
    IlvDisplay* display = timer->getDisplay();
    IlUInt count;
    IlvDoublePoint previous;
    IlvChartDataSet* dataSet;
    // Add one point on each dataSet.
    for (IlUInt i = 0; i < chart->getDataSetsCount(); i++) {
	dataSet = chart->getDataSet(i);
	count = dataSet->getDataCount();
	// Get the previous point to have a smooth random creation
	dataSet->getPoint(count - 1, previous);
	// Create a new point.
	IlvDoublePoint newPoint(previous.x() + 0.2,
				GeneratePointCyclic(previous.y()));

	IlvColor* c = GetAColorCyclic(display, newPoint.y());
	IlvChartDataPointInfo* ptInfo = 0;
	// Associate a color to the point according to its value.
	if (c) {
	    ptInfo = new IlvChartDataPointInfo(display->getPalette(0, c));
	}

	// Add the point in the chart with the color.
	dataSet->addPoint(newPoint, ptInfo, IlFalse);
    }
}

// --------------------------------------------------------------------------
// Panel class for sample Cyclic
// --------------------------------------------------------------------------
Cyclic::Cyclic(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initCyclic();
}

// --------------------------------------------------------------------------
Cyclic::~Cyclic()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Cyclic::initCyclic()
{
    IlvDisplay* dpy = getDisplay();

    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,IlvRect(0, 0, 800, 600));

    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0, 8));
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(MinOrd,
								MaxOrd));

    IlvSingleScaleDisplayer* scale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(scale);
    delete IlvScaleStepsUpdater::Set(scale, updater);
    updater->fixStepUnit(1., .2);

    scale = chart->getOrdinateSingleScale();
    updater = new IlvConstantScaleStepsUpdater(scale);
    delete IlvScaleStepsUpdater::Set(scale, updater);
    updater->fixStepUnit(1., .2);

    IlvPalette* cursorPal = GetPalette(dpy, "lightgrey", "red");
    chart->addOrdinateCursor(1., cursorPal);
    cursorPal = GetPalette(dpy, "lightgrey", "coral");
    chart->addOrdinateCursor(2., cursorPal);
    cursorPal = GetPalette(dpy, "lightgrey", "green");
    chart->addOrdinateCursor(3., cursorPal);

    // Add the data.
    // First create 3 point sets
    IlvChartDataSet* dataSets[3];
    dataSets[0] = new IlvChartPointSet("DataSet1", new IlvPointInfoMap());
    dataSets[0]->addPoint(IlvDoublePoint(0, 0.5));

    dataSets[1] = new IlvChartPointSet("DataSet2", new IlvPointInfoMap());
    dataSets[1]->addPoint(IlvDoublePoint(0, 1.5));

    dataSets[2] = new IlvChartPointSet("DataSet3", new IlvPointInfoMap());
    dataSets[2]->addPoint(IlvDoublePoint(0, 3.5));

    // Add the data sets to the chart.
    IlUInt count = 3;
    chart->getData()->setDataSets(count, dataSets);

    // Add the displayers.
    chart->addDisplayer(new IlvScatterChartDisplayer(IlvMarkerSquare),
			dataSets[0]);
    chart->addDisplayer(new IlvScatterChartDisplayer(IlvMarkerFilledDiamond),
			dataSets[1]);
    chart->addDisplayer(new IlvScatterChartDisplayer(IlvMarkerCircle),
			dataSets[2]);

    // Set different colors for the displayers.
    chart->getDisplayer(0)->setForeground(dpy->getColor("red"));
    chart->getDisplayer(1)->setForeground(dpy->getColor("green"));
    chart->getDisplayer(2)->setForeground(dpy->getColor("cyan"));

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);

    chart->setScrollMode(IlvChartGraphic::IlvScrollModeCycle);
    chart->setScrollRatio(.5);
    chart->resetCycleValues();

    int millisecs = DefaultTimerPeriod;
    IlvTimer* timer = new IlvTimer(dpy, 0, millisecs, AddPointsCyclic, chart);
    timer->run();

    // Add accelerators for  the timer.
    addAccelerator(RunTimerCyclic, IlvKeyUp, 'r', 0, timer);
    addAccelerator(SuspendTimerCyclic, IlvKeyUp, 's', 0, timer);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageCyclic(Pan* mainPanel)
{
    Cyclic* panel = new Cyclic(mainPanel, "cyclic.ilv");
    mainPanel->addPageNoteBook(panel, "Cyclic", "cyclic.txt");
}
