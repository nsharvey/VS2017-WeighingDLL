// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/multiscale/src/multiscale.cpp
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
// Example of a cartesian chart using a multi-scale.
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

// --------------------------------------------------------------------------
// Some constants used for the sample
static const char*	title = "Multi-scale sample";
static const IlDouble	MinCoord = 0.;
static const IlDouble	MaxCoord = 4.;

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    IlvDisplay* dpy = new IlvDisplay("Simple", 0, argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	delete dpy;
	return -1;
    }
    // Create the panel
    IlvRect size(0, 0, 810, 370);
    IlvContainer* cont =
	new IlvContainer(dpy, "Panel" , title, size, IlTrue, IlFalse);
    cont->setMaximumSize(size.w(), size.h());
    cont->setBackground(dpy->getColor("lightgray"));

    // Creates a new cartesian chart.
    IlvChartGraphic* cartChart =
	new IlvChartGraphic(dpy, IlvRect(20, 20, 400, 300));
    // Create and set a cartesian projector
    cartChart->setProjector(new IlvCartesianProjector(IlvCartesianProjector::IlvXRightYTop));
	
    // Create the coordinate information for the abscissa:
    IlvCoordinateInfo* coordInfo =
	new IlvCoordinateInfo(IlvAbscissaCoordinate);
	
    // Create and set the abscissa scale
    IlvSingleScaleDisplayer* abscissaScale =
	new IlvRectangularScaleDisplayer(coordInfo, cartChart->getPalette());
    abscissaScale->drawLabelOnCrossings(IlTrue);
    abscissaScale->setStepLabelFormat("%.0f");
    abscissaScale->setRelativePosition(IlvMinDataPosition, -10);
    // Define a fixed step and substep unit
    IlvConstantScaleStepsUpdater* updater =
        new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepUnit(1, 0);

    cartChart->setAbscissaScale(abscissaScale);

    // Create the coordinate information objects and the scale
    // displayers for the ordinate:
    IlvSingleScaleDisplayer* scale;
    IlvAbstractGridDisplayer* grid;
    IlvPalette* gridPalette = dpy->getPalette(0,
					      dpy->getColor("black"),
					      0,
					      0,
					      0,
					      dpy->alternateLineStyle());
    IlUInt i;
    for (i = 0; i < 3; i++) {
	coordInfo = new IlvCoordinateInfo(IlvOrdinateCoordinate);
	scale = new IlvRectangularScaleDisplayer(coordInfo,
						 cartChart->getPalette());
	grid = new IlvRectangularGridDisplayer(gridPalette);
	scale->setGridDisplayer(grid);
	updater = new IlvConstantScaleStepsUpdater(scale);
	delete IlvScaleStepsUpdater::Set(scale, updater);
	updater->fixStepUnit(1., 0.2);
	scale->drawLabelOnCrossings(IlTrue);
	scale->setRelativePosition(IlvMinDataPosition, -10);
	cartChart->addOrdinateScale(scale);
    }

    // Define palettes for the ordinate scales.
    IlvPalette* bluePalette = dpy->getPalette(0, dpy->getColor("darkblue"));
    IlvPalette* redPalette = dpy->getPalette(0, dpy->getColor("darkred"));
    IlvPalette* greenPalette = dpy->getPalette(0, dpy->getColor("darkgreen"));
    cartChart->getOrdinateScale(0)->setAxisPalette(bluePalette);
    cartChart->getOrdinateScale(0)->setStepLabelsPalette(bluePalette);
    cartChart->getOrdinateScale(1)->setAxisPalette(redPalette);
    cartChart->getOrdinateScale(1)->setStepLabelsPalette(redPalette);
    cartChart->getOrdinateScale(2)->setAxisPalette(greenPalette);
    cartChart->getOrdinateScale(2)->setStepLabelsPalette(greenPalette);

    // Stack the ordinate scales
    const IlvSingleScaleDisplayer* ordinateScales[3];
    for (i = 0; i < 3; i++)
	ordinateScales[i] = cartChart->getOrdinateSingleScale(i);
    cartChart->stackScales(3, ordinateScales, 0.1);

    cartChart->setFillMode(IlvChartGraphic::FillDataArea);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("white"),
				      dpy->getColor("lightgray"),
				      IlvPoint(0, 0),
				      IlvPoint(0, 1));
    IlvPalette* palette = dpy->getPalette(dpy->getColor("white"),
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
    cartChart->setDataAreaBackgroundPalette(palette);

    // Set a manual range for the abscissa coordinate
    cartChart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(MinCoord,
								    MaxCoord));
    // Set a manual range for the ordinate coordinate
    cartChart->getOrdinateInfo(0)->setUserDataRange(IlvCoordInterval(0, 3));
    cartChart->getOrdinateInfo(1)->setUserDataRange(IlvCoordInterval(0, 1));
    cartChart->getOrdinateInfo(2)->setUserDataRange(IlvCoordInterval(1, 3));

    // Create 3 data sets
    IlvChartDataSet* dataSets[3];
    dataSets[0] = new IlvChartPointSet("Serie1");
    dataSets[0]->addPoint(IlvDoublePoint(0.2, 0.7));
    dataSets[0]->addPoint(IlvDoublePoint(0.8, 1.5));
    dataSets[0]->addPoint(IlvDoublePoint(1.5, 2));
    dataSets[0]->addPoint(IlvDoublePoint(2, 1));
    dataSets[0]->addPoint(IlvDoublePoint(2.4, 1.6));
    dataSets[0]->addPoint(IlvDoublePoint(3.0, 1));
    dataSets[0]->addPoint(IlvDoublePoint(3.6, 2.8));
    dataSets[1] = new IlvChartPointSet("Serie2");
    dataSets[1]->addPoint(IlvDoublePoint(0, 1));
    dataSets[1]->addPoint(IlvDoublePoint(0.2, 0.2));
    dataSets[1]->addPoint(IlvDoublePoint(0.8, 0.9));
    dataSets[1]->addPoint(IlvDoublePoint(1.5, 0.3));
    dataSets[1]->addPoint(IlvDoublePoint(2, 1));
    dataSets[1]->addPoint(IlvDoublePoint(2.2, 0.3));
    dataSets[1]->addPoint(IlvDoublePoint(2.6, 0.8));
    dataSets[1]->addPoint(IlvDoublePoint(3.2, 0));
    dataSets[1]->addPoint(IlvDoublePoint(4, 0.9));
    dataSets[2] = new IlvChartPointSet("Serie3");
    dataSets[2]->addPoint(IlvDoublePoint(0, 1.1));
    dataSets[2]->addPoint(IlvDoublePoint(0.5, 1.5));
    dataSets[2]->addPoint(IlvDoublePoint(1, 2));
    dataSets[2]->addPoint(IlvDoublePoint(1.5, 2.2));
    dataSets[2]->addPoint(IlvDoublePoint(2, 2.8));
    dataSets[2]->addPoint(IlvDoublePoint(2.5, 1.2));
    dataSets[2]->addPoint(IlvDoublePoint(3, 2));
    dataSets[2]->addPoint(IlvDoublePoint(3.8, 3));

    // Add the data sets to the chart data object.
    IlUInt count = 3;
    cartChart->getData()->setDataSets(count, dataSets);

    // Create and add the displayers.
    cartChart->addDisplayer(new IlvStairChartDisplayer(),
			    dataSets[0],
			    cartChart->getOrdinateInfo(0));
    cartChart->addDisplayer(new IlvPolylineChartDisplayer(),
			    dataSets[1],
			    cartChart->getOrdinateInfo(1));
    cartChart->addDisplayer(new IlvStepChartDisplayer(),
			    dataSets[2],
			    cartChart->getOrdinateInfo(2));

    // Set different colors for the displayers.
    gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("white"),
				      dpy->getColor("lightsteelblue"),
				      IlvPoint(0, 0),
				      IlvPoint(1, 0));
    palette = dpy->getPalette(dpy->getColor("lightsteelblue"),
			      dpy->getColor("blue"),
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
    cartChart->getDisplayer(0)->setPalette(palette);

    palette = dpy->getPalette(0, dpy->getColor("red"), 0, 0, 0, 0, 2);
    cartChart->getDisplayer(1)->setPalette(palette);

    palette = dpy->getPalette(0, dpy->getColor("green"), 0, 0, 0, 0, 2);
    cartChart->getDisplayer(2)->setPalette(palette);

    // Creates a new polar chart.
    IlvChartGraphic* polarChart =
        new IlvChartGraphic(dpy, IlvRect(440, 20, 300, 300));
    // Create and set a polar projector
    polarChart->setProjector(new IlvPolarProjector(0.0, 270.0, IlFalse));
	
    // Create the coordinate information for the abscissa:
    coordInfo = new IlvCoordinateInfo(IlvAbscissaCoordinate);
	
    // Create and set the abscissa scale
    abscissaScale =
        new IlvCircularScaleDisplayer(coordInfo, polarChart->getPalette());
    abscissaScale->drawLabelOnCrossings(IlTrue);
    abscissaScale->setStepLabelFormat("%.0f");
    // Define a fixed step and substep unit
    updater = new IlvConstantScaleStepsUpdater(abscissaScale);
    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);
    updater->fixStepUnit(1, 0);

    polarChart->setAbscissaScale(abscissaScale);
	
    // Create the coordinate information objects and the scale
    // displayers for the ordinate:
    for (i = 0; i < 3; i++) {
	coordInfo = new IlvCoordinateInfo(IlvOrdinateCoordinate);
	scale = new IlvRectangularScaleDisplayer(coordInfo,
						 polarChart->getPalette());
	grid = new IlvCircularGridDisplayer((IlvCircularScaleDisplayer*)
					    polarChart->getAbscissaScale(),
					    gridPalette);
	scale->setGridDisplayer(grid);
	updater = new IlvConstantScaleStepsUpdater(scale);
	delete IlvScaleStepsUpdater::Set(scale, updater);
	updater->fixStepUnit(1., 0);
	scale->drawLabelOnCrossings(IlTrue);
	scale->setRelativePosition(IlvMinDataPosition, 90 * i );
	polarChart->addOrdinateScale(scale);
    }

    // Define palettes for the ordinate scales.
    polarChart->getOrdinateScale(0)->setAxisPalette(bluePalette);
    polarChart->getOrdinateScale(0)->setStepLabelsPalette(bluePalette);
    polarChart->getOrdinateScale(1)->setAxisPalette(redPalette);
    polarChart->getOrdinateScale(1)->setStepLabelsPalette(redPalette);
    polarChart->getOrdinateScale(2)->setAxisPalette(greenPalette);
    polarChart->getOrdinateScale(2)->setStepLabelsPalette(greenPalette);

    // Stack the ordinate scales
    for (i = 0; i < 3; i++)
	ordinateScales[i] = polarChart->getOrdinateSingleScale(i);
    polarChart->stackScales(3, ordinateScales, 0.1);

    polarChart->setFillMode(IlvChartGraphic::FillDataArea);
    gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("lightgray"),
				      dpy->getColor("white"),
				      10,
				      10);
    palette = dpy->getPalette(dpy->getColor("white"),
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
    polarChart->setDataAreaBackgroundPalette(palette);

    // Set a manual range for the abscissa coordinate
    polarChart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(MinCoord,
								     MaxCoord));
    // Set a manual range for the ordinate coordinate
    polarChart->getOrdinateInfo(0)->setUserDataRange(IlvCoordInterval(1, 3));
    polarChart->getOrdinateInfo(1)->setUserDataRange(IlvCoordInterval(0, 1));
    polarChart->getOrdinateInfo(2)->setUserDataRange(IlvCoordInterval(0, 3));

    // Set the data
    polarChart->setData(cartChart->getData());

    // Create and add the displayers.
    polarChart->addDisplayer(new IlvStairChartDisplayer(),
			     dataSets[0],
			     polarChart->getOrdinateInfo(2));
    polarChart->addDisplayer(new IlvPolylineChartDisplayer(),
			     dataSets[1],
			     polarChart->getOrdinateInfo(1));
    polarChart->addDisplayer(new IlvStepChartDisplayer(),
			     dataSets[2],
			     polarChart->getOrdinateInfo(0));

    // Set different colors for the displayers.
    gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("lightsteelblue"),
				      dpy->getColor("blue"),
				      10,
				      10);
    palette = dpy->getPalette(dpy->getColor("lightsteelblue"),
			      dpy->getColor("blue"),
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
    polarChart->getDisplayer(0)->setPalette(palette);

    palette = dpy->getPalette(0, dpy->getColor("red"), 0, 0, 0, 0, 2);
    polarChart->getDisplayer(1)->setPalette(palette);

    palette = dpy->getPalette(0, dpy->getColor("green"), 0, 0, 0, 0, 2);
    polarChart->getDisplayer(2)->setPalette(palette);

    // Add the charts to the container.
    cont->addObject(cartChart);
    cont->addObject(polarChart);

    cont->show();

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    cont->setDoubleBuffering(IlTrue);
    IlvMainLoop();
    return 0;
}
