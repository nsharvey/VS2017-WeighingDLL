// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/simple/src/cartesian.cpp
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
// Simple example of a cartesian chart.
// --------------------------------------------------------------------------

#include <cartesian.h>

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

// --------------------------------------------------------------------------
// Some constants used for the sample
static const IlDouble MinCoord = 0.;
static const IlDouble MaxCoord = 4.;

// --------------------------------------------------------------------------
// Panel class for sample Cartesian
// --------------------------------------------------------------------------
Cartesian::Cartesian(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initCartesian();
}

// --------------------------------------------------------------------------
Cartesian::~Cartesian()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Cartesian::initCartesian()
{
    // Display initialization
    IlvDisplay* dpy = getDisplay();

    // Creates a new cartesian chart.
    // The following line is equivalent to :
    /*
	IlvChartGraphic* chart = new IlvChartGraphic(dpy, size);
	// Create and set a cartesian projector
	chart->setProjector(new IlvCartesianProjector(IlvCartesianProjector::IlvXRightYTop));
	// Create the coordinate information for the abscissa:
	IlvCoordinateInfo* coordInfo
	    = new IlvCoordinateInfo(IlvAbscissaCoordinate);
	// Create and set the abscissa scale
	IlvRectangularScaleDisplayer* abscissaScale
	    = new IlvRectangularScaleDisplayer(coordInfo,chart->getPalette());
	abscissaScale->drawLabelOnCrossings(IlTrue);
	abscissaScale->setStepLabelFormat("%.0f");
	chart->setAbscissaScale(abscissaScale);
    	// Create the coordinate information for the ordinate:
	coordInfo = new IlvCoordinateInfo(IlvOrdinateCoordinate);
	// Create and add an ordinate scale
	IlvRectangularScaleDisplayer* ordinateScale
	    = new IlvRectangularScaleDisplayer(coordInfo,chart->getPalette());
	ordinateScale->drawLabelOnCrossings(IlTrue);
	chart->addOrdinateScale(ordinateScale);
    */
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,IlvRect(0, 0, 400, 300));

    // Set some properties on the scales:
    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    // Define a fixed number of steps and substeps
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepsCount(5, 1);

    // Set a manual range for the abscissa coordinate
    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(MinCoord,
								MaxCoord));

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    // Define a fixed step and substep unit
    updater = new IlvConstantScaleStepsUpdater(ordinateScale);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    updater->fixStepUnit(1., 0.1);

    // We want to draw the step label where the abscissa scale crosses
    // the ordinate scale
    abscissaScale->drawLabelOnCrossings(IlTrue);

    // Create 3 data sets
    IlvChartDataSet* dataSets[3];
    dataSets[0] = new IlvChartPointSet("Serie1");
    dataSets[0]->addPoint(IlvDoublePoint(0, 1));
    dataSets[0]->addPoint(IlvDoublePoint(0.5, 0));
    dataSets[0]->addPoint(IlvDoublePoint(0.9, 1.5));
    dataSets[0]->addPoint(IlvDoublePoint(1.2, 1.2));
    dataSets[0]->addPoint(IlvDoublePoint(2, 1.5));
    dataSets[0]->addPoint(IlvDoublePoint(2.2, 2.4));
    dataSets[0]->addPoint(IlvDoublePoint(2.5, 2));
    dataSets[0]->addPoint(IlvDoublePoint(3, 3));
    dataSets[0]->addPoint(IlvDoublePoint(3.2, 3.6));
    dataSets[0]->addPoint(IlvDoublePoint(3.5, 2.2));
    dataSets[1] = new IlvChartPointSet("Serie2");
    dataSets[1]->addPoint(IlvDoublePoint(0, 0.5));
    dataSets[1]->addPoint(IlvDoublePoint(0.5, 4));
    dataSets[1]->addPoint(IlvDoublePoint(1, 2));
    dataSets[1]->addPoint(IlvDoublePoint(1.5, 2.9));
    dataSets[1]->addPoint(IlvDoublePoint(2.1, 2));
    dataSets[1]->addPoint(IlvDoublePoint(3, 3.7));
    dataSets[1]->addPoint(IlvDoublePoint(3.5, 0.3));
    dataSets[1]->addPoint(IlvDoublePoint(3.8, 2.1));
    dataSets[1]->addPoint(IlvDoublePoint(4, 1.2));
    dataSets[2] = new IlvChartPointSet("Serie3");
    dataSets[2]->addPoint(IlvDoublePoint(1, 0.7));
    dataSets[2]->addPoint(IlvDoublePoint(1.5, 2));
    dataSets[2]->addPoint(IlvDoublePoint(2, 1));
    dataSets[2]->addPoint(IlvDoublePoint(2.4, 1.6));
    dataSets[2]->addPoint(IlvDoublePoint(3, 2.4));

    // Add the data sets to the chart data object.
    IlUInt count = 3;
    chart->getData()->setDataSets(count, dataSets);

    // Create and add the displayers.
    chart->addDisplayer(new IlvBarChartDisplayer(), dataSets[2]);
    chart->addDisplayer(new IlvScatterChartDisplayer(IlvMarkerFilledDiamond),
			dataSets[0]);
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[1]);

    // Set different colors for the displayers.
    chart->getDisplayer(0)->setForeground(dpy->getColor("blue"));
    chart->getDisplayer(0)->setBackground(dpy->getColor("lightsteelblue"));
    chart->getDisplayer(1)->setForeground(dpy->getColor("red"));
    chart->getDisplayer(2)->setForeground(dpy->getColor("green"));

    // Set background colors for the chart.
    chart->setFillMode(IlvChartGraphic::FillDataArea);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("slategray"),
				      dpy->getColor("lightgrey"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    IlvPalette* palette = dpy->getPalette(0,
					  dpy->getColor("white"),
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

    // Add the chart to the container.
    addObject(chart);
    setGraphicAttachments(chart);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageCartesian(Pan* mainPanel)
{
    Cartesian* panel = new Cartesian(mainPanel, "cartesian.ilv");
    mainPanel->addPageNoteBook(panel, "Cartesian", "cartesian.txt");
}
