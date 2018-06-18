// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/userman/src/stackedpolygon.cpp
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
// Polygon displayer factory
// --------------------------------------------------------------------------
class PolygonDisplayerFactory : public IlvChartDisplayerFactory
{
public:

    PolygonDisplayerFactory() : IlvChartDisplayerFactory() {}

    virtual
    IlvChartDisplayerFactory* copy() const;

    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlvCompositeChartDisplayer* parent,
					       IlUInt idx,
					       IlvPalette *palette);
};

// --------------------------------------------------------------------------
IlvChartDisplayerFactory*
PolygonDisplayerFactory::copy() const
{
    return new PolygonDisplayerFactory();
}

// --------------------------------------------------------------------------
IlvAbstractChartDisplayer*
PolygonDisplayerFactory::createDisplayer(IlvCompositeChartDisplayer* /* parent */,
					 IlUInt /* idx */,
					 IlvPalette * palette)
{
    return new IlvPolygonChartDisplayer(palette);
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
    // Create the panel
    IlvContainer* cont = new IlvContainer(display,
					  "Stacked Polygon",
					  "Stacked Polygon",
					  IlvRect(0, 0, 400, 300),
					  IlTrue,
					  IlFalse);

    // Creates a new cartesian chart.
    IlvChartGraphic* chart =
	new IlvCartesianChart(display, IlvRect(20, 20, 250, 190));

    // Set some properties on the scales:

    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    // Define a fixed step and substep unit.
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepUnit(1., 0.5);

    IlvSingleScaleDisplayer* ordinateScale = chart->getOrdinateSingleScale();
    // Define a fixed step and substep unit.
    updater = new IlvConstantScaleStepsUpdater(ordinateScale);
    delete IlvScaleStepsUpdater::Set(ordinateScale, updater);
    updater->fixStepUnit(1., 0.1);

    // Set a manual range for the ordinate coordinate.
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(0, 3));

    // Create the data sets.
    IlvChartYValueSet* dataSet0 = new IlvChartYValueSet();
    IlvChartYValueSet* dataSet1 = new IlvChartYValueSet();

    dataSet0->addValue(0.7);
    dataSet0->addValue(0.6);
    dataSet0->addValue(0.9);
    dataSet0->addValue(0.7);
    dataSet0->addValue(1.3);
    dataSet0->addValue(0.8);
    dataSet0->addValue(0.5);

    dataSet1->addValue(1.3);
    dataSet1->addValue(0.9);
    dataSet1->addValue(1.5);
    dataSet1->addValue(0.3);
    dataSet1->addValue(0.9);
    dataSet1->addValue(1.5);
    dataSet1->addValue(1);

    // Set the data sets on the chart data object.
    chart->getData()->addDataSet(dataSet0);
    chart->getData()->addDataSet(dataSet1);

    // Create the stacked displayer.
    IlvPalette* palettes[2];
    palettes[0] =
	display->getPalette(display->getColor("palegreen"),
			    display->getColor("blue"));
    palettes[1] =
	display->getPalette(display->getColor("gold"),
			    display->getColor("red"));

    IlvStackedChartDisplayer* stackedDisplayer;

    // Creation of a stacked polygons representation with the
    // IlvStackedPolygonChartDisplayer class.
    stackedDisplayer = new IlvStackedPolygonChartDisplayer(2, palettes);

    // Creation of a stacked polygons representation with the
    // IlvStackedChartDisplayer class and a model.
    /*
    IlvAbstractChartDisplayer* model = new IlvPolygonChartDisplayer();
    stackedDisplayer = new IlvStackedChartDisplayer(model, 2, palettes);
    */

    // Creation of a stacked polygons representation with the
    // IlvStackedChartDisplayer class and a factory.
    /*
    PolygonDisplayerFactory* factory = new PolygonDisplayerFactory();
    stackedDisplayer = new IlvStackedChartDisplayer(factory, 2, palettes);
    */

    IlvChartDataSet* dataSets[2];
    dataSets[0] = dataSet0;
    dataSets[1] = dataSet1;

    chart->addDisplayer(stackedDisplayer, 2, dataSets);

    // Add the chart to the container.
    cont->addObject(chart);

    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
