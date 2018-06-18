// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/userman/src/pie.cpp
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

// Include for all charts class headers
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
    // Creating the panel
    IlvContainer* cont = new IlvContainer(display,
					  "Pie Chart",
					  "Pie Chart",
					  IlvRect(0, 0, 470, 400),
					  IlTrue,
					  IlFalse);


    // Creates a new cartesian chart.
    IlvPieChartGraphic* chart =
        new IlvPieChartGraphic(display, IlvRect(10, 10, 450, 300));

    // Create the data set to be represented by a pie.
    IlvChartYValueSet* dataSet = new IlvChartYValueSet();
    dataSet->addValue(1.);
    dataSet->addValue(2.);
    dataSet->addValue(2.);
    dataSet->addValue(3.);
    dataSet->addValue(4.);

    // Add the data set to the chart data object.
    chart->getData()->addDataSet(dataSet);

    // Create and add the pie displayer.
    chart->addPieDisplayer(dataSet);

    // Customize the slices display.
    // Define a specific palette for each slice.
    IlvPalette* bluePal =
	display->getPalette(0, display->getColor("lightblue"));
    IlvPalette* redPal =
	display->getPalette(0, display->getColor("red"));
    IlvPalette* darkBluePal =
	display->getPalette(0, display->getColor("blue"));
    IlvPalette* greenPal =
	display->getPalette(0, display->getColor("green"));
    IlvPalette* goldPal =
	display->getPalette(0, display->getColor("gold"));

    chart->getPieDisplayer(0)->setSlicePalette(0, bluePal);
    chart->getPieDisplayer(0)->setSlicePalette(1, redPal);
    chart->getPieDisplayer(0)->setSlicePalette(2, darkBluePal);
    chart->getPieDisplayer(0)->setSlicePalette(3, greenPal);
    chart->getPieDisplayer(0)->setSlicePalette(4, goldPal);

    // Define a graphic object storing a specific label for each slice.
    chart->getPieDisplayer(0)
        ->setSliceGraphic(0, new IlvLabel(display, 0, 0, "A"));
    chart->getPieDisplayer(0)
        ->setSliceGraphic(1, new IlvLabel(display, 0, 0, "B"));
    chart->getPieDisplayer(0)
        ->setSliceGraphic(2, new IlvLabel(display, 0, 0, "C"));
    chart->getPieDisplayer(0)
        ->setSliceGraphic(3, new IlvLabel(display, 0, 0, "D"));
    chart->getPieDisplayer(0)
        ->setSliceGraphic(4, new IlvLabel(display, 0, 0, "E"));

    // Define the offset between the slices and the added graphic objects.
    chart->getPieDisplayer(0)->setOffset(IlvDoublePoint(0, 5));

    // Tear off the slice with index 3.
    chart->getPieDisplayer(0)->tearOffSlice(3);

    // Add the chart to the container.
    cont->addObject(chart);

    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'Q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
