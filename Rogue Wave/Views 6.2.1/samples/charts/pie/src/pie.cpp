// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/pie/src/pie.cpp
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
// Pie charts sample.
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/shadlab.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

// --------------------------------------------------------------------------
static const char*	title = "Pie chart example";
static IlvRect		containerSize(0, 0, 930, 450);
static IlvRect		size(0, 0, 900, 400);
static const IlUInt	NbSlices = 10;

static const char* AnimalNames[5] =
{
    "Beef", "Chicken", "Lamb", "Rabbit", "Fish"
};

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Display initialization
    IlvDisplay* display = new IlvDisplay("Pie", 0, argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create display");
	delete display;
	return -1;
    }
    // Create the panel
    IlvContainer* cont = new IlvContainer(display,
					  "Panel",
					  title,
					  containerSize,
					  IlTrue,
					  IlFalse);
    cont->setMaximumSize(containerSize.w(), containerSize.h());
    cont->setBackground(display->getColor("white"));

    size.w(2 * size.w() / 3 - 100);
    // Create the first pie chart
    IlvPieChartGraphic* pieChart1 =
        new IlvPieChartGraphic(display, size, 0., 360., 0.4);

    IlvGradientPattern* gradientPattern =
	display->getRadialGradientPattern(display->getColor("black"),
					  display->getColor("grey"),
					  100,
					  100);
    pieChart1->setGradientPattern(gradientPattern);
    pieChart1->setFillStyle(IlvFillGradientPattern);

    // Add 2 random data sets
    IlvChartYValueSet* dataSet1 = CreateYDataSet(NbSlices, 1, 5);
    IlvChartYValueSet* dataSet2 = CreateYDataSet(NbSlices / 2, 1, 5);
    pieChart1->getData()->addDataSet(dataSet1);
    pieChart1->getData()->addDataSet(dataSet2);

    // Add the displayers.
    IlvPieChartDisplayer* pieDisp1 = pieChart1->addPieDisplayer(dataSet1, 1.);
    IlvPalette* pal = display->getPalette(display->getColor("lightblue"));
    IlvPieChartDisplayer* pieDisp2 =
        pieChart1->addPieDisplayer(dataSet2, 1., pal);

    // Set different colors for the displayers.
    IlUInt dataCount = dataSet1->getDataCount();
    IlvPalette** palettes = GetPalettes(display, dataCount);
    pieDisp1->setOffset(IlvDoublePoint(0, 20));
    IlUInt i;
    IlvPalette* labPal;
    for (i = 0; i < dataCount; ++i) {
	pieDisp1->setSlicePalette(i, palettes[i]);
	labPal = display->getPalette(palettes[i]->getForeground(),
				     display->getColor("black"));
	pieDisp1->setSliceGraphic(i,
				  new IlvShadowLabel(display,
						     IlvPoint(0, 0),
						     palettes[i]->getForeground()->getName(),
						     2,
						     IlvBottomRight,
						     labPal));
    }
    delete [] palettes;

    dataCount = dataSet2->getDataCount();
    pieDisp2->setOffset(IlvDoublePoint(0, -40));
    for (i = 0; i < dataCount; ++i) {
	pieDisp2->setSliceGraphic(i,
				  new IlvLabel(display,
					       IlvPoint(0, 0),
					       AnimalNames[i % 5]));
    }


    // Create the second pie chart
    size.x(size.right() + 50);
    size.w(size.w() / 2);
    IlvPieChartGraphic* pieChart2 =
        new IlvPieChartGraphic(display, size, 0., 180.);
    pieChart2->getData()->addDataSet(dataSet2);
    IlvPieChartDisplayer* pieDisp = pieChart2->addPieDisplayer(dataSet2);

    dataCount = dataSet2->getDataCount();
    palettes = GetPalettes(display, dataCount);
    for (i = 0; i < dataCount; ++i) {
	pieDisp->setSlicePalette(i, palettes[i]);
	pieDisp->setSliceLegendText(i, AnimalNames[i % 5]);
    }
    pieDisp->tearOffSlice(3); // Tear the 4th slice
    delete [] palettes;

    size.y(size.centery() + 20);
    IlvChartLegend* legend = new IlvChartLegend(display, size);
    legend->showFrame(IlFalse);
    legend->setItemSpacing(8);
    pieChart2->setLegend(legend);

    // Add the charts and the legend to the container.
    cont->addObject(pieChart1);
    cont->addObject(pieChart2);
    cont->addObject(legend);

    cont->setDoubleBuffering(IlTrue);
    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
