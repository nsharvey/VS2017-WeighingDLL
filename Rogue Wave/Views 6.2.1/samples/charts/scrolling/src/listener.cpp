// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/src/listener.cpp
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
// Demonstrating the use of data set listeners in charts.
// --------------------------------------------------------------------------

#include <listener.h>

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
#define NbAddedPts		  1
#define TMin			-40.0
#define TMax			 60.0
#define Amplitude		100.0
#define DefaultTimerPeriod	100

// --------------------------------------------------------------------------
class TemperatureDataListener : public IlvChartDataSetListener
{
public:
    TemperatureDataListener(IlvChartGraphic* hiLoChart)
    {
	_hiLoChart = hiLoChart;
    }

    virtual void	dataPointAdded(const IlvChartDataSet*	dataSet,
				       IlUInt			position);

protected:
    IlvChartGraphic*	_hiLoChart;
};

// --------------------------------------------------------------------------
void
TemperatureDataListener::dataPointAdded(const IlvChartDataSet*	dataSet,
					IlUInt			position)
{
    IlUInt count = dataSet->getDataCount() - 1;
    IlvAbstractChartData* hiLoChartData = _hiLoChart->getData();

    IlvDoublePoint newPoint;
    dataSet->getPoint(position, newPoint);

    if (!(count%24)) { // Add a point for the new day
	for (IlUInt i = 0; i < hiLoChartData->getDataSetsCount(); ++i) {
	    hiLoChartData->getDataSet(i)->addPoint(newPoint);
	}
    }
    else { // Update high/low/current(end)
	IlUInt idx = count / 24;
	IlvDoublePoint previous;

	hiLoChartData->getDataSet(3)->setPoint(idx, newPoint);
	hiLoChartData->getDataSet(0)->getPoint(idx, previous);

	if (previous.y() > newPoint.y()) {
	    hiLoChartData->getDataSet(0)->setPoint(idx, newPoint);
	}

	hiLoChartData->getDataSet(1)->getPoint(idx, previous);
	if (previous.y() < newPoint.y()) {
	    hiLoChartData->getDataSet(1)->setPoint(idx, newPoint);
	}
    }
}

// --------------------------------------------------------------------------
// Callbacks to translate data values to scale labels
static char*
ValueToHourOfDay(IlDouble val, IlAny)
{
    char* res = new char[16];
    sprintf(res,
	    "%u : %u",
	    IL_CAST(unsigned int, val) / 24 + 1,
	    IL_CAST(unsigned int, val) % 24);
    return res;
}

// --------------------------------------------------------------------------
static char*
ValueToDayOfWeek(IlDouble val, IlAny)
{
    char* res = new char[16];
    sprintf(res,
	    "%u : %u",
	    IL_CAST(unsigned int, val) / 7 + 1,
	    IL_CAST(unsigned int, val) % 7 + 1);
    return res;
}

// --------------------------------------------------------------------------
IlDouble
GeneratePointListener(IlDouble current)
// A small change relative to current value
// to get a smooth random creation.
{
    IlDouble f = Amplitude / 1000 * ((rand() % 201) - 100);
    if (!(rand() % 12)) {
	f *= 3;
    }
    f += current;
    if (f < TMin) {
	f = (TMin + 1);
    }
    if (f > TMax) {
	f =  (TMax - 1);
    }
    return f;
}

// --------------------------------------------------------------------------
static void
RunTimerListener(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
SuspendTimerListener(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
// Point info used to change the color of data points with negative values
IlvChartGradientPointInfo* gradientInfo = 0;

// --------------------------------------------------------------------------
static void
InitGradientListener(IlvDisplay* display)
{
    IlDouble values[] = { TMin, (TMin + TMax) / 2.0, TMax };
    IlArray colors;
    IlvColor *col = display->getColor("blue");
    colors.add(col);
    col = display->getColor("white");
    colors.add(col);
    col = display->getColor("red");
    colors.add(col);

    gradientInfo = new IlvChartGradientPointInfo(values, colors);
}

// --------------------------------------------------------------------------
// Timer callback to add points.
static void
AddPointsListener(IlvTimer* timer, IlAny arg)
{
    IlvChartGraphic* chart = (IlvChartGraphic*)arg;
    IlvChartDataSet* dataSet = chart->getDataSet(0);
    IlvDoublePoint previous(0., 0.);
    IlUInt count = dataSet->getDataCount();
    for (IlUInt i = 0; i < NbAddedPts; ++i) {
	if (count) {
	    dataSet->getPoint(count - 1, previous);
	}
	// Create a new point.
	IlvDoublePoint newPoint(previous.x() + 1,
				GeneratePointListener(previous.y()));
 	dataSet->addPoint(newPoint, gradientInfo, IlFalse);
    }
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
static IlvRect size(0, 0, 800, 600);

// --------------------------------------------------------------------------
// Panel class for sample Listener
// --------------------------------------------------------------------------
Listener::Listener(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initListener();
}

// --------------------------------------------------------------------------
Listener::~Listener()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Listener::initListener()
{
    IlvRect size(15, 25, 760, 440);
    IlvDisplay* dpy = getDisplay();

    srand(117);

    // Create the display gradient
    InitGradientListener(dpy);

    // Create the panel
    IlvPalette* chartPal = GetFontPalette(dpy, "%helvetica-12-");
    IlvPalette* gridPal = dpy->getPalette(0,
					  dpy->getColor("slategray"),
					  0,
					  0,
					  0,
					  dpy->alternateLineStyle());;
    IlvPalette* axisLabelPalette = GetFontPalette(dpy, "%helvetica-12-B");

    // Create the chart to display the temperature values
    size.h(size.h() / 2 - 40);
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,
			      IlvRect(15,25,760,200),
			      IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      chartPal,
			      gridPal);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("slategray"),
				      dpy->getColor("white"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    IlvPalette* palette = dpy->getPalette(dpy->getColor("black"),
					  dpy->getColor("lightgray"),
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
    chart->setFillMode(IlvChartGraphic::FillDataArea);
    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0, 48));
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(TMin, TMax));

    chart->enableFastScroll(IlFalse);

    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();

    abscissaScale->setCrossingValue(TMin,ordinateScale);

    IlvConstantScaleStepsUpdater* updater =
	new IlvConstantScaleStepsUpdater(abscissaScale);
    updater->fixStepsCount(9, 5);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);

    abscissaScale->setValueToLabelCB(ValueToHourOfDay, 0);
    abscissaScale->setAxisLabel("D:H");
    abscissaScale->setAxisLabelPalette(axisLabelPalette);
    abscissaScale->getGridDisplayer()->setDrawOrder(IlvDrawBelow);

    ordinateScale->setRelativePosition(IlvMinDataPosition, -20);
    updater = new IlvConstantScaleStepsUpdater(ordinateScale);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    updater->fixStepUnit(Amplitude / 10, Amplitude / 50);
    ordinateScale->setAxisLabel("Temp");
    ordinateScale->setAxisOriented(IlTrue);
    ordinateScale->setAxisLabelPalette(axisLabelPalette);
    ordinateScale->getGridDisplayer()->setDrawOrder(IlvDrawBelow);

    // Create the data set for the temperature values
    IlvChartYValueSet* temperatureDS =
	new IlvChartYValueSet("Temperature", new IlvPointInfoMap());
    temperatureDS->setName("Temperature");
    chart->getData()->addDataSet(temperatureDS);

    // Add the displayer for the temperature values
    IlvPalette* temperaturePal = GetPalette(dpy, "coral", "black");
    IlvBarChartDisplayer* bar = new IlvBarChartDisplayer(4, temperaturePal);
    bar->setWidthPercent(100);

    chart->addDisplayer(bar, temperatureDS);
    chart->setAxisCrossing(-1, 0.0);

    // Add the chart to the container.
    addObject(chart);

    chart->setScrollMode(IlvChartGraphic::IlvScrollModeCycle);
    //chart->setScrollMode(IlvChartGraphic::IlvScrollModeShift);
    chart->setScrollRatio(.5);

    // Create the hiLo chart as a copy of the temperature chart since
    // they share many common properties.
    IlvChartGraphic* hiLoChart = IL_CAST(IlvChartGraphic*, chart->copy());
    size.y(size.bottom()+ 20);
    hiLoChart->moveResize(size);

    hiLoChart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0, 14));
    hiLoChart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(TMin,
								    TMax));
    abscissaScale = hiLoChart->getAbscissaScale();

    abscissaScale->setValueToLabelCB(ValueToDayOfWeek, 0);
    abscissaScale->setAxisLabel("W:D");
    updater = new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepsCount(15,0);

    IlvChartYValueSet* lo	= new IlvChartYValueSet("lo");
    IlvChartYValueSet* hi	= new IlvChartYValueSet("hi");
    IlvChartYValueSet* start	= new IlvChartYValueSet("start");
    IlvChartYValueSet* end	= new IlvChartYValueSet("end");

    IlvChartDataSet* dataSets[4];
    dataSets[0] = lo;
    dataSets[1] = hi;
    dataSets[2] = start;
    dataSets[3] = end;

    IlUInt count = 4;
    hiLoChart->getData()->setDataSets(count,dataSets);

    IlvPalette* hiLoPal = dpy->getPalette(dpy->getColor("white"),
					  dpy->getColor("white"),
					  0,
					  0,
					  0,
					  0,
					  2);
    IlvPalette* startEndRisePal = GetPalette(dpy, "coral", "red");
    IlvPalette* startEndFallPal = GetPalette(dpy, "lightsteelblue", "blue");

    IlvHiLoOpenCloseChartDisplayer* hiloOCDisp =
	new IlvHiLoOpenCloseChartDisplayer(8,
					   hiLoPal,
					   startEndRisePal,
					   hiLoPal,
					   startEndFallPal);
    hiloOCDisp->setLegendText("High/Low", 0);
    hiloOCDisp->setLegendText("Start/End", 1);
    hiLoChart->addDisplayer(hiloOCDisp, 4, dataSets);
    hiLoChart->setScrollMode(IlvChartGraphic::IlvScrollModeShift);
    hiLoChart->setScrollRatio(.5);

    // Add the listener that will update the hi/lo start/end data sets
    temperatureDS->addListener(new TemperatureDataListener(hiLoChart));


    // Create a legend for the second chart
    IlvRect legRect(size.w() / 2 - 150, size.bottom() + 10, 300, 30);
    IlvChartLegend* legend = new IlvChartLegend(dpy, legRect);
    legend->setBackground(dpy->getColor("lightgray"));
    legend->setAutoFit(IlFalse);

    // Add the legend and the hiLo chart.
    addObject(legend);
    hiLoChart->setLegend(legend);
    addObject(hiLoChart);

    // Timer to add points.
    int millisecs = DefaultTimerPeriod ;
    IlvTimer* timer =
	new IlvTimer(dpy, 0, millisecs, AddPointsListener, chart);
    timer->run();

    // Add accelerators for the timer.
    addAccelerator(RunTimerListener, IlvKeyUp, 'r', 0, timer);
    addAccelerator(SuspendTimerListener, IlvKeyUp, 's', 0, timer);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageListener(Pan* mainPanel)
{
    Listener* panel = new Listener(mainPanel, "listener.ilv");
    mainPanel->addPageNoteBook(panel, "Listener", "listener.txt");
}
