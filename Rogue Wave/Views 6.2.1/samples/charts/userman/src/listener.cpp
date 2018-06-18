// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/userman/src/listener.cpp
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

#if defined(IL_STD)
#include <iostream>
IL_STDUSE
#else  /* !IL_STD */
#include <iostream.h>
#endif /* IL_STD */

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
class TemperatureDataSetListener : public IlvChartDataSetListener
{
public:
    TemperatureDataSetListener(IlDouble		min,
			       IlDouble		max,
			       IlvChartGraphic*	chart = 0,
			       IlvPalette*	cursorPalette = 0);

    virtual void	dataPointAdded(const IlvChartDataSet*	dataSet,
				       IlUInt			position);

protected:
    IlDouble		_min;
    IlDouble		_max;
    IlvChartGraphic*	_chart;
};

// --------------------------------------------------------------------------
TemperatureDataSetListener::TemperatureDataSetListener(IlDouble min,
						       IlDouble max,
						       IlvChartGraphic* chart,
						       IlvPalette* cursorPalette)
    : IlvChartDataSetListener(),
      _min(min),
      _max(max)
{
    if (chart) {
	IlvDisplay* dpy = chart->getDisplay();
	IlvPalette* palette = cursorPalette ? cursorPalette
	    : dpy->getPalette(dpy->getColor("white"), 0);
	chart->addOrdinateCursor(_min, palette);
	chart->addOrdinateCursor(_max, palette);
    }
}

// --------------------------------------------------------------------------
void
TemperatureDataSetListener::dataPointAdded(const IlvChartDataSet* dataSet,
					   IlUInt position)
{
    IlvDoublePoint dataPoint;
    dataSet->getPoint(position, dataPoint);
    if (dataPoint.y() < _min)
	cout << dataSet->getName() << ": Temperature at the index "
	     << position << " = " << dataPoint.y() << " degrees ( < "
	     << _min << " )" << endl;
    if (dataPoint.y() > _max)
	cout << dataSet->getName() << ": Temperature at the index "
	     << position << " = " << dataPoint.y() << " degrees ( > "
	     << _max << " )" << endl;
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
					  IlvRect(0, 0, 470, 400),
					  IlTrue,
					  IlFalse);


    // Creates a new cartesian chart.
    IlvChartGraphic* chart =
	new IlvCartesianChart(display, IlvRect(10, 10, 450, 300));

    // Set some properties on the scales:
    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    // Define a fixed number of steps and substeps between two steps.
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepsCount(7, 0);

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    // Define a fixed step and substep unit.
    updater = new IlvConstantScaleStepsUpdater(ordinateScale);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    updater->fixStepUnit(5, 1);

    // Create two data sets.
    IlvChartDataSet* dataSets[2];
    // Create one data set to store the morning temperatures.
    dataSets[0] = new IlvChartPointSet("Morning Temperatures");
    // Create one data set to store the afternoon temperatures.
    dataSets[1] = new IlvChartPointSet("Afternoon Temperatures");

    // Add a listener on the temperature data sets.
    TemperatureDataSetListener* listener =
        new TemperatureDataSetListener(10, 22, chart);
    dataSets[0]->addListener(listener);
    dataSets[1]->addListener(listener);

    // Put the data into the morning temperatures data set.
    dataSets[0]->addPoint(IlvDoublePoint(0, 10));
    dataSets[0]->addPoint(IlvDoublePoint(1, 8));
    dataSets[0]->addPoint(IlvDoublePoint(2, 12));
    dataSets[0]->addPoint(IlvDoublePoint(3, 15));
    dataSets[0]->addPoint(IlvDoublePoint(4, 14));
    dataSets[0]->addPoint(IlvDoublePoint(5, 14));
    dataSets[0]->addPoint(IlvDoublePoint(6, 13));

    // Put the data into the afternoon temperatures data set.
    dataSets[1]->addPoint(IlvDoublePoint(0, 16));
    dataSets[1]->addPoint(IlvDoublePoint(1, 12));
    dataSets[1]->addPoint(IlvDoublePoint(2, 20));
    dataSets[1]->addPoint(IlvDoublePoint(3, 25));
    dataSets[1]->addPoint(IlvDoublePoint(4, 22));
    dataSets[1]->addPoint(IlvDoublePoint(5, 24));
    dataSets[1]->addPoint(IlvDoublePoint(6, 26));

    // Add the data sets to the chart data object.
    IlUInt dataSetsCount = 2;
    chart->getData()->setDataSets(dataSetsCount, dataSets);

    // Create and add the displayers.
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[0]);
    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[1]);

    IlvPalette* risePalette =
	display->getPalette(display->getColor("red"),
			    display->getColor("white"));
    IlvPalette* fallPalette =
	display->getPalette(display->getColor("blue"),
			    display->getColor("white"));
    chart->addDisplayer(new IlvHiLoBarChartDisplayer(12,
						     risePalette,
						     fallPalette),
			dataSetsCount,
			dataSets);

    // Set different colors for the displayers.
    chart->getDisplayer(0)->setForeground(display->getColor("blue"));
    chart->getDisplayer(1)->setForeground(display->getColor("red"));

    // Create and set a legend object.
    IlvChartLegend* legend =
	new IlvChartLegend(display, IlvRect(10, 330, 450, 50));
    chart->setLegend(legend);

    // Add the chart to the container.
    cont->addObject(chart);

    // Add the legend to the container.
    cont->addObject(legend);

    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'Q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
