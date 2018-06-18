// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/simple/src/polar.cpp
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
// Example of a polar chart using callback functions.
// --------------------------------------------------------------------------

#include <polar.h>

#if defined(IL_STD)
IL_STDUSE
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// Some constants used for the sample
static const IlUInt NbPoints = 91;

// --------------------------------------------------------------------------
// Callback functions for the data sets
static IlDouble
Func(IlDouble val)
{
    // abs(2*sin(2x))
    val = IlvDegreesToRadians(2 * val);
    return IlAbs(2 * sin(val));
}

// --------------------------------------------------------------------------
static IlDouble
Func2(IlDouble val)
{
    // abs(sin(3x))
    val = IlvDegreesToRadians(3 * val);
    return IlAbs(sin(val));
}

// --------------------------------------------------------------------------
// Panel class for sample Polar
// --------------------------------------------------------------------------
Polar::Polar(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initPolar();
}

// --------------------------------------------------------------------------
Polar::~Polar()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Polar::initPolar()
{
    IlvDisplay* dpy = getDisplay();

    IlvChartGraphic* chart =
	new IlvPolarChart(dpy, IlvRect(0, 0, 800, 600), IlFalse);

    IlvPalette* pal = dpy->getPalette(0,
				      dpy->getColor("black"),
				      0,
				      0,
				      dpy->getFont("bold"),
				      0,
				      2);

    // Set some properties on the scales:
    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepUnit(45., 5.);
    abscissaScale->setMajorTickSize(12);
    abscissaScale->setMinorTickSize(6);
    abscissaScale->setAxisPalette(pal);
    abscissaScale->setStepLabelsPalette(pal);
    abscissaScale->drawLabelOnCrossings(IlTrue);

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    ordinateScale->setAxisPalette(pal);
    ordinateScale->setStepLabelsPalette(pal);
    ordinateScale->setMajorTickSize(10);
    ordinateScale->setMinorTickSize(6);
    ordinateScale->drawOverlappingLabels(IlFalse);

    // Create two callback functions.
    IlvCallbackChartFunction* function =
	new IlvCallbackChartFunction(IlvCoordInterval(0., 360.),
				     NbPoints,
				     Func);

    IlvCallbackChartFunction* function2 =
	new IlvCallbackChartFunction(IlvCoordInterval(0., 360.),
				     NbPoints,
				     Func2);

    // Add the data to the chart
    chart->getData()->addDataSet(function);
    chart->getData()->addDataSet(function2);

    // Create the curve displayers
    IlvGradientPattern* gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("white"),
				      dpy->getColor("pink"),
				      10,
				      10);
    pal = dpy->getPalette(dpy->getColor("pink"),
			  dpy->getColor("red"),
			  0,
			  0,
			  0,
			  0,
			  2,
			  IlvFillGradientPattern,
			  IlvArcPie,
			  IlvEvenOddRule,
			  IlvFullIntensity,
			  IlvDefaultAntialiasingMode,
			  gradientPattern);
    chart->addDisplayer(new IlvPolygonChartDisplayer(pal), function);
    pal = dpy->getPalette(dpy->getColor("limegreen"), dpy->getColor("black"));
    chart->addDisplayer(new IlvBarChartDisplayer(6, pal), function2);

    chart->setFillMode(IlvChartGraphic::FillDataArea);
    gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("black"),
				      dpy->getColor("white"),
				      10,
				      10);
    pal = dpy->getPalette(dpy->getColor("white"),
			  dpy->getColor("gray"),
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
    chart->setDataAreaBackgroundPalette(pal);

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePagePolar(Pan* mainPanel)
{
    Polar* panel = new Polar(mainPanel, "polar.ilv");
    mainPanel->addPageNoteBook(panel, "Polar", "polar.txt");
}
