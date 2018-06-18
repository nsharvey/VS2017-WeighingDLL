// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scales/src/ex2y.cpp
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
// Demonstrating the use of multiple Y scales in a chart.
// --------------------------------------------------------------------------

#include <ex2y.h>

#if defined(IL_STD)
IL_STDUSE
#include <cstring>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */

// Some constants used in this sample
static const IlUInt TwoScalesNbPoints = 20;

// --------------------------------------------------------------------------
// Panel class for sample TwoScales
// --------------------------------------------------------------------------
TwoScales::TwoScales(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initTwoScales();
}

// --------------------------------------------------------------------------
TwoScales::~TwoScales()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
TwoScales::initTwoScales()
{
    // Display initialization
    IlvDisplay* dpy = getDisplay();

    // Create the panel
    IlvPalette* chartPal =
	dpy->getPalette(0, 0, 0, 0, dpy->getFont("bold"), 0, 2);
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
    IlvPalette* palette =
	dpy->getPalette(dpy->getColor("black"),
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

    IlvSingleScaleDisplayer* scale = chart->getAbscissaScale();
    IlvConstantScaleStepsUpdater* updater =
         new IlvConstantScaleStepsUpdater(scale);
    delete IlvScaleStepsUpdater::Set(scale, updater);
    updater->fixStepUnit(1., 0.);
    scale->drawOverlappingLabels(IlFalse);

    scale = chart->getOrdinateSingleScale();
    updater = new IlvConstantScaleStepsUpdater(scale);
    delete IlvScaleStepsUpdater::Set(scale, updater);
    updater->fixStepsCount(10, 1);
    scale->drawOverlappingLabels(IlFalse);

    // Create a second ordinate scale
    IlvCoordinateInfo* ordinateInfo2 =
	new IlvCoordinateInfo(IlvOrdinateCoordinate, 0., 46);

    IlvRectangularScaleDisplayer* secondOrdinateScale =
	new IlvRectangularScaleDisplayer(ordinateInfo2, chart->getPalette());

    // Customize the scale
    secondOrdinateScale->drawOverlappingLabels(IlFalse);
    secondOrdinateScale->setRelativePosition(IlvMaxDataPosition);
    secondOrdinateScale->drawLabelOnCrossings(IlTrue);
    chart->addOrdinateScale(secondOrdinateScale);

    // Create 4 random data sets and add them to the chart data.
    IlvChartDataSet* dataSets[4];
    dataSets[0] = CreateYDataSet(TwoScalesNbPoints, 1, 6);
    dataSets[1] = CreateYDataSet(TwoScalesNbPoints, 4, 9);
    dataSets[2] = CreateYDataSet(TwoScalesNbPoints, 8, 14);
    dataSets[3] = CreateYDataSet(TwoScalesNbPoints, 12, 19);
    IlUInt dsCount = 4;
    chart->getData()->setDataSets(dsCount, dataSets);

    // Create the palettes for the displayers
    IlvPalette* palettes[4];
    palettes[0] =
	dpy->getPalette(dpy->getColor("wheat"), dpy->getColor("brown"));
    palettes[1] =
	dpy->getPalette(dpy->getColor("lightblue"), dpy->getColor("blue"));
    palettes[2] =
	dpy->getPalette(dpy->getColor("white"), dpy->getColor("black"));
    palettes[3] =
	dpy->getPalette(dpy->getColor("pink"), dpy->getColor("red"));

    // Add the displayers.

    // A stacked displayer
    chart->addDisplayer(new IlvStacked3dBarChartDisplayer(4, palettes),
			4,
			dataSets,
			ordinateInfo2);

    // 4 displayers on the stacked data sets
    IlvMarkedPolylineChartDisplayer* disp;

    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledSquare, 3);
    disp->setLineForeground(palettes[0]->getBackground());
    disp->setMarkerForeground(palettes[0]->getForeground());
    chart->addDisplayer(disp, dataSets[3]);

    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledDiamond, 3);
    disp->setLineForeground(palettes[1]->getBackground());
    disp->setMarkerForeground(palettes[1]->getForeground());
    chart->addDisplayer(disp, dataSets[2]);

    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledCircle, 3);
    disp->setLineForeground(palettes[2]->getBackground());
    disp->setMarkerForeground(palettes[2]->getForeground());
    chart->addDisplayer(disp, dataSets[1]);

    disp = new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledTriangle,3);
    disp->setLineForeground(palettes[3]->getBackground());
    disp->setMarkerForeground(palettes[3]->getForeground());
    chart->addDisplayer(disp,dataSets[0]);

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageTwoScales(Pan* mainPanel)
{
    TwoScales* panel = new TwoScales(mainPanel, "ex2y.ilv");
    mainPanel->addPageNoteBook(panel, "Two scales", "ex2y.txt");
}
