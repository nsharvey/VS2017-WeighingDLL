// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scales/src/loga.cpp
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
// Demonstrating the use of logarithmic scales in a chart.
// --------------------------------------------------------------------------

#include <loga.h>

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
static const IlUInt NbPoints = 20;

// --------------------------------------------------------------------------
// Callback functions for the data sets
// --------------------------------------------------------------------------
static IlDouble
Func(IlDouble val)
{
    // x = x^4
    return pow(val, 4.);
}

// --------------------------------------------------------------------------
static IlDouble
Func2(IlDouble val)
{
    // x = f(x)
    return val;
}

// --------------------------------------------------------------------------
static IlDouble
Func3(IlDouble val)
{
    // x = 4*log(x)/log(10)
    return 4 * log(val) / log(10.);
}

// --------------------------------------------------------------------------
// Panel class for sample Logarithmic
// --------------------------------------------------------------------------
Logarithmic::Logarithmic(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initLogarithmic();
}

// --------------------------------------------------------------------------
Logarithmic::~Logarithmic()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Logarithmic::initLogarithmic()
{
    IlvDisplay* dpy = getDisplay();

    // Create the panel
    IlvPalette* chartPal = dpy->getPalette(0,
					   dpy->getColor("black"),
					   0,
					   0,
					   dpy->getFont("bold"),
					   0,
					   0);
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,
			      IlvRect(0, 0, 800, 600),
			      IlFalse,
			      IlvCartesianProjector::IlvXRightYTop,
			      chartPal);
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

    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater =
	new IlvConstantScaleStepsUpdater(abscissaScale, 1.);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    abscissaScale->drawOverlappingLabels(IlFalse);

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    updater = new IlvConstantScaleStepsUpdater(ordinateScale, 1.);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    ordinateScale->drawOverlappingLabels(IlFalse);

    // Create a second ordinate scale with a logarithmic transformer
    IlvCoordinateInfo* ordinateInfo2 =
	new IlvCoordinateInfo(IlvOrdinateCoordinate,
			      new IlvSimpleChartTransformer(10));

    IlvRectangularScaleDisplayer* ordinateScale2 =
	new IlvRectangularScaleDisplayer(ordinateInfo2, chart->getPalette());

    // Customize the scale
    IlvLogScaleStepsUpdater* logUpdater =
        new IlvLogScaleStepsUpdater(ordinateScale2);
    delete IlvScaleStepsUpdater::Set(ordinateScale2, logUpdater);
    ordinateScale2->setRelativePosition(IlvMaxDataPosition);
    ordinateScale2->drawLabelOnCrossings(IlTrue);
    ordinateScale2->setStepLabelFormat("%g");
    ordinateScale2->setTickLayout(IlvAbstractScaleDisplayer::TickCross);
    ordinateScale2->drawOverlappingLabels(IlFalse);

    // Add a grid to the scale
    IlvPalette* majPal = dpy->getPalette(0, dpy->getColor("lightgray"));
    IlvPalette* minPal = dpy->getPalette(0,
					 dpy->getColor("lightgray"),
					 0,
					 0,
					 0,
					 dpy->alternateLineStyle());
    IlvAbstractGridDisplayer* grid =
        new IlvRectangularGridDisplayer(majPal, minPal);
    grid->drawMinorLines(IlTrue);
    grid->setDrawOrder(IlvDrawBelow);
    ordinateScale2->setGridDisplayer(grid);
    chart->addOrdinateScale(ordinateScale2);

     // Create two callback functions.
    IlvCallbackChartFunction* function =
	new IlvCallbackChartFunction(IlvCoordInterval(1.,10.),
				     NbPoints,
				     Func);

    IlvCallbackChartFunction* function2 =
	new IlvCallbackChartFunction(IlvCoordInterval(1.,10.),
				     NbPoints,
				     Func2);

    IlvCallbackChartFunction* function3 =
	new IlvCallbackChartFunction(IlvCoordInterval(1.,10.),
				     NbPoints,
				     Func3);

    // Add the data to the chart
    chart->getData()->addDataSet(function);
    chart->getData()->addDataSet(function2);
    chart->getData()->addDataSet(function3);

    // Create and add the displayers.
    gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("green"),
				      dpy->getColor("red"),
				      IlvPoint(0, 1),
				      IlvPoint(0, 0));
    IlvPalette* pal = dpy->getPalette(dpy->getColor("green"),
				      dpy->getColor("lightblue"),
				      dpy->getPattern("diaglr"),
				      0,
				      0,
				      0,
				      2,
				      IlvFillGradientPattern,
				      IlvArcPie,
				      IlvEvenOddRule,
				      IlvFullIntensity / 3,
				      IlvDefaultAntialiasingMode,
				      gradientPattern);
    IlvAbstractChartDisplayer* disp = new IlvStairChartDisplayer(pal);
    chart->addDisplayer(disp, function3);
    disp->setLegendText("4*log(x)/log(10) on main ordinate");

    pal = dpy->getPalette(0,dpy->getColor("yellow"));
    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledDiamond,
					       3,
					       pal,
					       pal);
    chart->addDisplayer(disp,function2, ordinateInfo2);
    disp->setLegendText("x on logarithmic ordinate");

    pal = dpy->getPalette(0, dpy->getColor("blue"));
    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledSquare,
					       3,
					       pal,
					       pal);
    chart->addDisplayer(disp, function, ordinateInfo2);
    disp->setLegendText("x^4 on logarithmic ordinate");

    // Create a legend for the chart		
    IlvChartLegend* legend =
	new IlvChartLegend(dpy, IlvRect(50, 50, 100, 100), 25, 25);
    legend->setItemPalette(dpy->getPalette(0,
					   0,
					   0,
					   0,
					   dpy->getFont("%helvetica-14-")));
    legend->setBackground(dpy->getColor("lightgray"));
    chart->setLegend(legend);

    // Add the chart and the legend to the container.
    addObject(chart);
    addObject(legend);
    setGraphicAttachments(chart);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageLogarithmic(Pan* mainPanel)
{
    Logarithmic* panel = new Logarithmic(mainPanel, "loga.ilv");
    mainPanel->addPageNoteBook(panel, "Logarithmic", "loga.txt");
}
