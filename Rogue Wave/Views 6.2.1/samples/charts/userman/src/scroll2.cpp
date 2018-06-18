// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/userman/src/scroll2.cpp
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
// Demonstrating the scroll mode of charts
// --------------------------------------------------------------------------
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/base/timer.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

#ifdef IL_STD
#include <cstdlib>
#include <cstdio>
IL_STDUSE
#else
#include <stdio.h>
#include <stdlib.h>
#endif


// --------------------------------------------------------------------------
// Some constants used for the sample
static const IlUInt MinOrd = 0;
static const IlUInt MaxOrd = 4;
static const int  DefaultTimerPeriod = 500;

// --------------------------------------------------------------------------
static void
Quit(IlvView* view, IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Quit(IlvContainer* container, IlvEvent&, IlAny)
{
    Quit(container, 0);
}

// --------------------------------------------------------------------------
IlvPalette*
GetPalette(IlvDisplay* dpy, const char* bg, const char* fg)
{
    return dpy->getPalette(dpy->getColor(bg), dpy->getColor(fg));
}

// --------------------------------------------------------------------------
void
GeneratePoint(const IlvDoublePoint& previous, IlvDoublePoint& next)
// A small change relative to current value
// to get a smooth random creation.
{
    next.x(previous.x() + 0.2);
    IlUShort jump= (rand() % 10);
    IlInt val= (rand() % 11) - 5;
    IlDouble f = (IlDouble)val / (IlDouble)20;
    if (!jump)
        f = f * 4;
    f += previous.y();
    if (f < MinOrd)
        f = (IlDouble)(MinOrd + 1);
    if (f > MaxOrd)
        f = (IlDouble)(MaxOrd - 1);
    next.y(f);
}

// --------------------------------------------------------------------------
static void
RunTimer(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
SuspendTimer(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
static void
AddPoints(IlvTimer* timer, IlAny arg)
    // Timer callback to add points.
{
    IlvChartGraphic* chart = (IlvChartGraphic*)arg;
    chart->getHolder()->initReDraws();

    IlUInt count;
    IlvDoublePoint previousPoint;
    IlvDoublePoint nextPoint;
    IlvChartDataSet* dataSet;
    // Add one point on each dataSet.
    for (IlvUInt i = 0; i < chart->getDataSetsCount(); i++) {
	dataSet = chart->getDataSet(i);
	count = dataSet->getDataCount();
	// Get the previous data point to have a smooth random creation.
	if (count != 0) {
	    dataSet->getPoint(count - 1, previousPoint);

	    // Create a new data point.
	    GeneratePoint(previousPoint, nextPoint);
	}
	else {
	    nextPoint.x(0);
	    nextPoint.y(i + 0.5);
	}
	// Add the data point to the data set.
	dataSet->addPoint(nextPoint);
    }
    chart->getHolder()->reDrawViews();
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    IlvDisplay* dpy = new IlvDisplay("Scrolling", 0, argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	delete dpy;
	return -1;
    }
    // Create the panel
    IlvRect size(0, 0, 800, 600);

    IlvContainer* cont =
	new IlvContainer(dpy, "Panel" , "Scrolling", size, IlTrue, IlFalse);

    IlvChartGraphic* chart = new IlvCartesianChart(dpy, size);

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
    // First create 3 data points sets.
    IlvChartDataSet* dataSets[3];
    dataSets[0] = new IlvChartPointSet("DataSet1");
    dataSets[1] = new IlvChartPointSet("DataSet2");
    dataSets[2] = new IlvChartPointSet("DataSet3");

    // Add the data sets to the chart data object.
    IlUInt count = 3;
    chart->getData()->setDataSets(count, dataSets);

    // Add the displayers.
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[0]);
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[1]);
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[2]);

    // Set different colors for the displayers.
    chart->getDisplayer(0)->setForeground(dpy->getColor("red"));
    chart->getDisplayer(1)->setForeground(dpy->getColor("green"));
    chart->getDisplayer(2)->setForeground(dpy->getColor("cyan"));

    // Add the chart to the container.
    cont->addObject(chart);
    IlvAttachmentsHandler::Set(cont, new IlvAttachmentsHandler);
    IlvSetAttachment(chart, IlvLeft,		IlvFixedAttach,		0);
    IlvSetAttachment(chart, IlvTop,		IlvFixedAttach,		0);
    IlvSetAttachment(chart, IlvRight,		IlvFixedAttach,		0);
    IlvSetAttachment(chart, IlvBottom,		IlvFixedAttach,		0);
    IlvSetAttachment(chart, IlvHorizontal,	IlvElasticAttach,	0);
    IlvSetAttachment(chart, IlvVertical,	IlvElasticAttach,	0);
    cont->show();

    chart->setScrollMode(IlvChartGraphic::IlvScrollModeShift);
    chart->setScrollRatio(.5);

    int millisecs = (argc > 1) ? atoi(argv[1]) : DefaultTimerPeriod;

    IlvTimer* timer = new IlvTimer(dpy, 0, millisecs, AddPoints, chart);
    timer->run();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    // Add accelerators for  the timer.
    cont->addAccelerator(RunTimer, IlvKeyUp, 'r', 0, timer);
    cont->addAccelerator(SuspendTimer, IlvKeyUp, 's', 0, timer);

    IlvMainLoop();
    return 0;
}
