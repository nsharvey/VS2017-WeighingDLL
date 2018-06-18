// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/filter/src/chfilter.cpp
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

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/attach.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

#ifdef IL_STD
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
IL_STDUSE
#else
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#endif

static const IlUInt NbColors = 15;
static const char* ColorNames[15] = {
    "red",
    "cornflowerblue",
    "palegreen",
    "gold",
    "salmon",
    "indianred",
    "yellow",
    "green",
    "violet",
    "magenta",
    "blue",
    "wheat",
    "maroon",
    "lightsteelblue"
};

// --------------------------------------------------------------------------
static const char*	title		= "Filtering on huge data sets";
static IlBoolean	DblBuf		= IlFalse;
static IlUInt		NbDisp		= 3;
static IlUInt		NbPts		= 500001;
static IlvDim		ClusterSize	= 5;

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    srand(113);

    IlvSetLocale();
    IlvDisplay* dpy = new IlvDisplay("Simple", 0, argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	delete dpy;
	return -1;
    }

    if (argc > 1) {
	NbPts = atoi(argv[1]) + 1;
	--argc;
	if (argc > 1) {
	    NbDisp = atoi(argv[2]);
	    --argc;
	    if (argc > 1)
		ClusterSize = IL_CAST(IlvDim, atoi(argv[3]));
	}
    }
    // Create the panel
    IlvRect size(0, 0,640, 480);
    IlvContainer* cont =
	new IlvContainer(dpy, "Panel", title, size, IlTrue, IlFalse);
    cont->setBackground(dpy->getColor("dimgray"));
    cont->setDoubleBuffering(DblBuf);

    // Creates a new cartesian chart.
    IlvPalette* pal = dpy->getPalette(dpy->getColor("dimgray"),
				      dpy->getColor("white"),
				      0,
				      0,
				      dpy->getFont("%helvetica-12-B"));
    IlvPalette* gridpal = GetPalette(dpy, "gray", "dimgray");
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,
			      size,
			      IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      pal,
			      gridpal);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("black"),
				      dpy->getColor("gray"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    pal = dpy->getPalette(dpy->getColor("gray"),
			  dpy->getColor("black"),
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
    chart->setFillMode(IlvChartGraphic::FillDataArea);
    chart->setDrawOrder(IlvDrawBelow);

    // Fix manually the layout margins
    chart->getLayout()->setDataDisplayAreaRelatively(50, 40, 20, 40);

    // Create 3 data sets
    IlUInt i;
    IlvChartDataSet** dataSets = new IlvChartDataSet*[NbDisp];
    for (i = 0; i < NbDisp; ++i) {
	dataSets[i] = CreateSmoothDataSet(NbPts, 10);
    }
    chart->getData()->setDataSets(NbDisp, dataSets);

    // Create and add the displayers.
    IlvSingleChartDisplayer* dispModel = new IlvPolylineChartDisplayer();
    // Set the filter on the displayer.
    // The filter is copied when the displayer is copied
    dispModel->setDisplayerPointsFactory(
	new IlvChartPointsFilterFactory(ClusterSize));
    IlvSingleChartDisplayer* disp;
    for (i = 0; i < NbDisp; ++i) {
	disp = IL_CAST(IlvSingleChartDisplayer*, dispModel->copy());
	disp->setForeground(dpy->getColor(ColorNames[i % NbColors]));
	chart->addDisplayer(disp, dataSets[i]);
    }
    delete [] dataSets;
    delete dispModel;

    // Add behaviors to the chart
    IlvChartInteractorManager* interMgr = new IlvChartInteractorManager();
    interMgr->addInteractor("ChartZoom");
    interMgr->addInteractor("ChartPan");
    interMgr->addInteractor("ChartScroll");
    IlvChartInteractorManager::Set(chart, interMgr);

    // Add the chart to the container.
    cont->addObject(chart, DblBuf);
    Attach(cont, chart);
    cont->show();

    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    cont->setDestroyCallback(Quit);
    IlvPrint("%lu Displayers of %lu points each", NbDisp, NbPts - 1);
    cont->setDoubleBuffering(IlTrue);
    IlvMainLoop();
    return 0;
}
