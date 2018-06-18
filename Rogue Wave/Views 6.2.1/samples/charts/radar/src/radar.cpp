// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/radar/src/radar.cpp
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
// Radar chart demo.
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/base/timer.h>
#include <ilog/pathname.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

#ifdef IL_STD
#include <cstdlib>
#include <cstring>
IL_STDUSE
#else
#include <stdlib.h>
#include <string.h>
#endif

// --------------------------------------------------------------------------
// - Static vars
static const char*	FileName = "radar.ilv";
static const char*	title = "Radar Chart";
static const IlUInt	NbPoints = 10;

// --------------------------------------------------------------------------
static char*
ValueToLabelCB(IlDouble val, IlAny)
{
    char* label = new char[2];
    label[1] = '\0';
    label[0] = 'A' + IL_CAST(char, val);
    return label;
}

// --------------------------------------------------------------------------
// - Timer to randomly change data values
static void
RunTimer(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->run();
}

// --------------------------------------------------------------------------
static void
StopTimer(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = (IlvTimer*)arg;
    timer->suspend();
}

// --------------------------------------------------------------------------
static void
SimulateTimerCB(IlvTimer* timer, IlAny arg)
{
    IlvAbstractChartData* data = IL_CAST(IlvAbstractChartData*, arg);
    IlvChartDataSet* ds = data->getDataSet(rand() % data->getDataSetsCount());
    IlvDoublePoint dataPoint;
    IlUInt idx = rand() % ds->getDataCount();
    ds->getPoint(idx, dataPoint);
    dataPoint.y(IlAbs(dataPoint.y() + (rand() % 5) - 2));
    ds->setPoint(idx, dataPoint);
}

// --------------------------------------------------------------------------
static void
SimulateCB(IlvGraphic* g, IlAny arg)
{
    IlvTimer* timer = IL_CAST(IlvTimer*, arg);
    if (timer->isRunning())
	timer->suspend();
    else
	timer->run();

}

// --------------------------------------------------------------------------
// - Changes displayers type: Normal/Stacked/Stacked100
static void
ChangeDisplayerType(IlvChartGraphic* chart, IlBoolean radar, IlUShort type)
{
    IlBoolean stacked100 = (type == 2);
    IlBoolean stacked = ((type == 1) || stacked100);
    IlvAbstractChartDisplayer* disp;
    IlUInt dispCount = chart->getDisplayersCount();
    for (IlUInt i = 0; i < dispCount; ++i) {
	disp = chart->getDisplayer(i);
	if (disp->getName() && !strcmp(disp->getName(), "Stacked")) {
	    IL_CAST(IlvStackedChartDisplayer*, disp)
		    ->setStacked100PerCent(stacked100);
	    disp->setVisible(stacked);
	} else
	    disp->setVisible(!stacked);

    }
    IlvCoordinateInfo* coord =
        chart->getOrdinateSingleScale()->getCoordinateInfo();
    if (stacked100) {
      coord->useAutoDataRange(IlFalse);
      coord->setUserDataMin(0.0);
      coord->setUserDataMax(100.0);
    }
    else {
      coord->useAutoDataRange(IlTrue);
    }
    chart->invalidateLayout();
    chart->updateAndReDraw();
}

// --------------------------------------------------------------------------
static void
ChangeDisplayerTypeCB(IlvGraphic* g, IlAny)
{
    IlvChartGraphic* radarChart =
	IL_CAST(IlvChartGraphic*,g->getHolder()->getObject("RadarChart"));
    IlvChartGraphic* cartChart =
	IL_CAST(IlvChartGraphic*,g->getHolder()->getObject("CartesianChart"));
    IlvSelector* selector = IL_CAST(IlvSelector*, g);

    IlShort sel = selector->whichSelected();
    ChangeDisplayerType(radarChart, IlTrue, sel);
    ChangeDisplayerType(cartChart, IlFalse, sel);
    //cartChart->updateAndReDraw();
    //radarChart->updateAndReDraw();
}

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

    IlPathName localPath(dpy->getHomePath());
    localPath.addDirectory("samples/charts/radar/data");
    dpy->prependToPath(localPath);

    // Create the panel
    IlvRect size(0, 0, 800, 450);
    IlvContainer* cont =
	new IlvContainer(dpy, "Panel", title, size, IlTrue, IlFalse);
    cont->setMinimumSize(size.w(), size.h());
    cont->setMaximumSize(size.w(), size.h());
    cont->setBackground(dpy->getColor("lightgray"));

    // Create 3 random data sets and add add it to a chart data object.
    IlvChartDataSet* dataSets[3];
    dataSets[0] = CreateYDataSet(NbPoints, 0, 10);
    dataSets[1] = CreateYDataSet(NbPoints, 0, 10);
    dataSets[2] = CreateYDataSet(NbPoints, 0, 10);
    IlUInt dsCount = 3;
    IlvMemoryChartData* chartData = new IlvMemoryChartData();
    chartData->setDataSets(dsCount, dataSets);

    // Palettes for the curve displayers
    IlvPalette* pals[3];
    pals[0] = dpy->getPalette(dpy->getColor("pink"),
			      dpy->getColor("red"));
    pals[1] = dpy->getPalette(dpy->getColor("palegreen"),
			      dpy->getColor("darkgreen"));
    pals[2] = dpy->getPalette(dpy->getColor("lightsteelblue"),
			      dpy->getColor("blue"));
    IlvPalette* dotpals[3];
    dotpals[0] = dpy->getPalette(pals[0]->getBackground(),
				 pals[0]->getForeground(),
				 0,
				 0,
				 0,
				 dpy->alternateLineStyle());
    dotpals[1] = dpy->getPalette(pals[1]->getBackground(),
				 pals[1]->getForeground(),
				 0,
				 0,
				 0,
				 dpy->alternateLineStyle());
    dotpals[2] = dpy->getPalette(pals[2]->getBackground(),
				 pals[2]->getForeground(),
				 0,
				 0,
				 0,
				 dpy->alternateLineStyle());

    // Palettes for the charts
    IlvPalette* pal = dpy->getPalette(dpy->getColor("lightgray"),
				      dpy->getColor("black"),
				      0,
				      0,
				      dpy->getFont("bold"));
    IlvPalette* gridpal = dpy->getPalette(0,
					  dpy->getColor("dimgray"),
					  0,
					  0,
					  0);
    if (!cont->readFile(FileName)) {
	IlvFatalError("Could not open file: %s", FileName);
	IlvExit(1);
    }

    // Create the radar chart
    IlvRect rect;
    cont->getObject("RadarRect")->boundingBox(rect);
    rect.expand(-5);
    IlvChartGraphic* radarChart =
	new IlvRadarChart(dpy, rect, IlTrue, pal, gridpal);
    radarChart->setData(chartData);
    IlvGradientPattern* gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("black"),
				      dpy->getColor("white"),
				      10,
				      10);
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
    radarChart->setDataAreaBackgroundPalette(palette);
    radarChart->setFillMode(IlvChartGraphic::FillDataArea);
    radarChart->getAbscissaScale()->setValueToLabelCB(ValueToLabelCB);

    radarChart->addDisplayer(new IlvPolygonChartDisplayer(pals[0]),
			     dataSets[0]);
    radarChart->addDisplayer(new IlvPolygonChartDisplayer(pals[1]),
			     dataSets[1]);
    radarChart->addDisplayer(new IlvPolygonChartDisplayer(pals[2]),
			     dataSets[2]);

    radarChart->addDisplayer(new IlvPolylineChartDisplayer(dotpals[0]),
			     dataSets[0]);
    radarChart->addDisplayer(new IlvPolylineChartDisplayer(dotpals[1]),
			     dataSets[1]);
    radarChart->addDisplayer(new IlvPolylineChartDisplayer(dotpals[2]),
			     dataSets[2]);

    IlvStackedChartDisplayer* disp =
	new IlvStackedPolygonChartDisplayer(3, pals);
    disp->setName("Stacked");
    disp->setVisible(IlFalse);
    radarChart->addDisplayer(disp, 3, dataSets);

    // Create a cartesian chart
    cont->getObject("CartesianRect")->boundingBox(rect);
    rect.expand(-5);
    IlvChartGraphic* cartChart =
	new IlvCartesianChart(dpy, rect, IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      pal, gridpal);
    cartChart->setData(chartData);
    cartChart->setDrawOrder(IlvDrawBelow);
    gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("white"),
				      dpy->getColor("gray"),
				      IlvPoint(0, 0),
				      IlvPoint(0, 1));
    palette = dpy->getPalette(dpy->getColor("white"),
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
    cartChart->setDataAreaBackgroundPalette(palette);
    cartChart->setFillMode(IlvChartGraphic::FillDataArea);
    cartChart->getAbscissaScale()->setValueToLabelCB(ValueToLabelCB);

    IlvSingleScaleDisplayer* scale = cartChart->getOrdinateSingleScale();
    scale->setMajorTickSize(14);
    scale->setMinorTickSize(6);

    cartChart->addDisplayer(new IlvBarChartDisplayer(20, pals[0]),
			    dataSets[0]);
    cartChart->addDisplayer(new IlvBarChartDisplayer(14, pals[1]),
			    dataSets[1]);
    cartChart->addDisplayer(new IlvBarChartDisplayer(8, pals[2]),
			    dataSets[2]);
    disp = new IlvStackedBarChartDisplayer(3, pals);
    disp->setName("Stacked");
    disp->setVisible(IlFalse);
    cartChart->addDisplayer(disp, 3, dataSets);

    // Add the charts to the container.
    cont->addObject("RadarChart", radarChart);
    cont->addObject("CartesianChart", cartChart);
    cont->setDoubleBuffering(IlTrue);
    cont->show();

    IlvTimer* timer = new IlvTimer(dpy, 0, 100, SimulateTimerCB, chartData);
    cont->addAccelerator(RunTimer, IlvKeyUp, 'r', 0, timer);
    cont->addAccelerator(StopTimer, IlvKeyUp, 's', 0, timer);

    cont->registerCallback("ChangeDisplayerTypeCB", ChangeDisplayerTypeCB);
    cont->registerCallback("SimulateCB", SimulateCB);
    cont->getObject("SimulateButton")->setClientData(timer);

    // Add behaviors to the cartesian chart.
    IlvChartInteractorManager* interMgr = new IlvChartInteractorManager();
    IlvChartInteractorManager::Set(cartChart, interMgr);
    IlvChartDragPointInteractor* inter = new IlvChartDragPointInteractor();
    inter->setOpaque(IlTrue);
    interMgr->addInteractor(inter);

    // Add behaviors to the radar chart.
    interMgr = new IlvChartInteractorManager();
    IlvChartInteractorManager::Set(radarChart, interMgr);
    interMgr->addInteractor("ChartSelect");
    inter = new IlvChartDragPointInteractor();
    interMgr->addInteractor(inter);
    inter->setOpaque(IlTrue);

    // Set an accelerator to quit.
    cont->addAccelerator(Quit, IlvKeyUp, 'q');
    // Set the destroy callback.
    cont->setDestroyCallback(Quit);

    IlvMainLoop();
    return 0;
}
