// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/userman/src/pointinfo.cpp
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
// Simple example using Charts
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>

// Include for all charts class headers.
#include <ilviews/charts/chartinc.h>

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
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    IlvDisplay* display = new IlvDisplay("Simple", 0, argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create display");
	delete display;
	return -1;
    }
    // Creating the panel.
    IlvContainer* cont = new IlvContainer(display,
					  "Temperatures Chart",
					  "Temperatures Chart",
					  IlvRect(0, 0, 470, 640),
					  IlTrue,
					  IlFalse);

    // Creation of the first chart -----------------------------------------

    // Creates a new cartesian chart.
    IlvChartGraphic* chart1 =
	new IlvCartesianChart(display, IlvRect(10, 10, 450, 300));

    // Set some properties on the scales:
    IlvSingleScaleDisplayer* abscissaScale1 = chart1->getAbscissaScale();
    // Define a fixed number of steps and substeps between two steps.
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale1);
    delete IlvScaleStepsUpdater::Set(abscissaScale1, updater);
    updater->fixStepsCount(7, 0);

    IlvSingleScaleDisplayer* ordinateScale1 = chart1->getOrdinateSingleScale();
    // Define a fixed step and substep unit.
    updater = new IlvConstantScaleStepsUpdater(ordinateScale1);
    delete IlvScaleStepsUpdater::Set(ordinateScale1, updater);
    updater->fixStepUnit(5, 1);

    // Create two data sets.
    IlvChartDataSet* dataSets[2];
    // Create one data set to store the morning temperatures.
    dataSets[0] = new IlvChartPointSet("Morning Temperatures");
    dataSets[0]->addPoint(IlvDoublePoint(0, 10));
    dataSets[0]->addPoint(IlvDoublePoint(1, 8));
    dataSets[0]->addPoint(IlvDoublePoint(2, 12));
    dataSets[0]->addPoint(IlvDoublePoint(3, 15));
    dataSets[0]->addPoint(IlvDoublePoint(4, 14));
    dataSets[0]->addPoint(IlvDoublePoint(5, 14));
    dataSets[0]->addPoint(IlvDoublePoint(6, 13));
    // Create one data set to store the afternoon temperatures.
    dataSets[1] = new IlvChartPointSet("Afternoon Temperatures");
    dataSets[1]->addPoint(IlvDoublePoint(0, 16));
    dataSets[1]->addPoint(IlvDoublePoint(1, 12));
    dataSets[1]->addPoint(IlvDoublePoint(2, 20));
    dataSets[1]->addPoint(IlvDoublePoint(3, 25));
    dataSets[1]->addPoint(IlvDoublePoint(4, 22));
    dataSets[1]->addPoint(IlvDoublePoint(5, 24));
    dataSets[1]->addPoint(IlvDoublePoint(6, 26));

    // Add the data sets to the chart data object.
    IlUInt dataSetsCount = 2;
    chart1->getData()->setDataSets(dataSetsCount, dataSets);

    // Create and add the displayers.
    chart1->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[0]);
    chart1->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[1]);

    IlvPalette* risePalette = display->getPalette(display->getColor("red"),
						  display->getColor("white"));
    IlvPalette* fallPalette = display->getPalette(display->getColor("blue"),
						  display->getColor("white"));
    chart1->addDisplayer(new IlvHiLoBarChartDisplayer(12, risePalette,
						      fallPalette),
			dataSetsCount, dataSets);

    // Set different colors for the displayers.
    chart1->getDisplayer(0)->setForeground(display->getColor("blue"));
    chart1->getDisplayer(1)->setForeground(display->getColor("red"));

    // Add the chart to the container.
    cont->addObject(chart1);

    // Add a point information object to a data point.
    IlvChartDataPointInfo* pointInfo =
	new IlvChartDataGraphicInfo(new IlvLabel(display,
						 0,
						 0,
						 "Highest afternoon temperature"),
				    0,
				    0,
				    IlvTopRight,
				    display->getPalette(display->getColor("green"),
							display->getColor("white")));

    //-------------------------------------------------------------------------
    // The point information is associated with the data point at the
    // level of the data set.

    // Set the point information collection object.
    dataSets[1]->setPointInfoCollection(new IlvPointInfoMap());

    // Set the point information object.
    dataSets[1]->setPointInfo(6, pointInfo);
    // Equivalent to:
    // dataSets[1]->getPointInfoCollection()->setPointInfo(6, pointInfo);

    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // The point information is associated with the data point at the
    // level of the high-low bar displayer.
    /*
    // Set the point information collection object.
    chart1->getDisplayer(2)->setPointInfoCollection(dataSets[1],
						    new IlvPointInfoMap());

    // Set the point information object.
    chart1->getDisplayer(2)->getPointInfoCollection(dataSets[1])
	->setPointInfo(6, pointInfo);
    */
    //-------------------------------------------------------------------------

    // Creation of the second chart -----------------------------------------

    IlvChartGraphic* chart2 =
	new IlvCartesianChart(display, IlvRect(10, 330, 450, 300));

    // Set some properties on the scales:
    IlvSingleScaleDisplayer* abscissaScale2 = chart2->getAbscissaScale();
    // Define a fixed number of steps and substeps between two steps.
    updater = new IlvConstantScaleStepsUpdater(abscissaScale2);
    delete IlvScaleStepsUpdater::Set(abscissaScale2, updater);
    updater->fixStepsCount(7, 0);

    IlvSingleScaleDisplayer* ordinateScale2 = chart2->getOrdinateSingleScale();
    // Define a fixed step and substep unit.
    updater = new IlvConstantScaleStepsUpdater(ordinateScale2);
    delete IlvScaleStepsUpdater::Set(ordinateScale2, updater);
    updater->fixStepUnit(5, 1);

    // We use the same chart data object for both charts.
    chart2->setData(chart1->getData());

    // Create and add the displayers.
    IlvPalette* palettes[2];
    palettes[0] =
	display->getPalette(display->getColor("blue"),
			    display->getColor("Navy"));
    palettes[1] =
	display->getPalette(display->getColor("red"),
			    display->getColor("Navy"));
    chart2->addDisplayer(new IlvStackedBarChartDisplayer(dataSetsCount,
							 palettes),
			 dataSetsCount,
			 dataSets);

   // Add the chart to the container.
    cont->addObject(chart2);

    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'Q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
