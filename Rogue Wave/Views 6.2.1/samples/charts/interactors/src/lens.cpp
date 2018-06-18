// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/interactors/src/lens.cpp
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
// Example of a local zoom on a chart coordinate.
// --------------------------------------------------------------------------

#include <lens.h>
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
static const IlUInt	NbPts		= 301;
static const IlDouble	DeltaZoom	= 5.;

// --------------------------------------------------------------------------
// Accelerator to switch between polar/cartesian projector
static void
ChangeProjectorAcc(IlvContainer* cont, IlvEvent&, IlAny arg)
{
    IlvChartGraphic* chart = IL_CAST(IlvChartGraphic*, arg);
    if (!chart) {
      return;
    }

    if (chart->getProjector()->isSubtypeOf(IlvPolarProjector::ClassInfo())) {
	chart->setProjector(new IlvCartesianProjector());
    }
    else {
	IlvPolarProjector* prj = new IlvPolarProjector(0., 360., IlFalse);
	prj->setSymmetric(IlFalse);
	chart->setProjector(prj);
    }

    IlvZoomCoordinateTransformer* t =
	IL_CAST(IlvZoomCoordinateTransformer*,
		chart->getAbscissaInfo()->getTransformer());
    IlvAbstractChartCursor* cursor =
	chart->addAbscissaCursor(t->getZoomWindow().getMin());
    cursor->setName("ZoomWindowStart");
    cursor = chart->addAbscissaCursor(t->getZoomWindow().getMax());
    cursor->setName("ZoomWindowEnd");
    chart->invalidateLayout();
    chart->updateAndReDraw();
}

// --------------------------------------------------------------------------
// - Accelerator to change interactively the zoom transformer
static void
ChangeZoom(IlvContainer* p, IlvEvent& ev, IlAny arg)
{
    IlvChartGraphic* chart = (IlvChartGraphic*)arg;
    IlvZoomCoordinateTransformer* t = (IlvZoomCoordinateTransformer*)
	chart->getAbscissaInfo()->getTransformer();

    IlBoolean reDraw = IlFalse;;
    if (ev.getKey() == 'c') {
	t->setContinuous(!t->isContinuous());
    }
    else if (ev.getKey() == '+') {
	reDraw = t->setZoomFactor(t->getZoomFactor() * 2);
    }
    else if (ev.getKey() == '-') {
	reDraw = t->setZoomFactor(t->getZoomFactor() / 2);
    }
    else {
	IlvCoordInterval zoomWindow = t->getZoomWindow();
	if (ev.getKey() == IlvRightKey) {
	    zoomWindow.translate(DeltaZoom);
	}
	else if (ev.getKey() == IlvLeftKey) {
	    zoomWindow.translate(-DeltaZoom);
	}
	else if (ev.getKey() == IlvUpKey) {
	    zoomWindow.set(zoomWindow.getMin() - DeltaZoom,
			   zoomWindow.getMax() + DeltaZoom);
	}
	else if (ev.getKey() == IlvDownKey) {
	    zoomWindow.set(zoomWindow.getMin() + DeltaZoom,
			   zoomWindow.getMax() - DeltaZoom);
	}
	reDraw = t->setZoomWindow(zoomWindow);
	if (reDraw) {
	    IlvSingleScaleDisplayer* scale = chart->getAbscissaScale();
	    zoomWindow = t->getZoomWindow();
	    IlvAbstractChartCursor* cursor =
		scale->getCursorByName("ZoomWindowStart");
	    if (cursor) {
		cursor->setValue(zoomWindow.getMin());
	    }
	    cursor = scale->getCursorByName("ZoomWindowEnd");
	    if (cursor) {
		cursor->setValue(zoomWindow.getMax());
	    }
	}
    }
    if (reDraw) {
	chart->invalidateLayout();
	chart->updateAndReDraw();
    }
}

// --------------------------------------------------------------------------
// Panel class for sample Lens
// --------------------------------------------------------------------------
Lens::Lens(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initLens();
}

// --------------------------------------------------------------------------
Lens::~Lens()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Lens::initLens()
{
    IlvDisplay* dpy = getDisplay();
    srand(333);

    // Create the chart
    IlvPalette* gridpal = GetPalette(dpy, "gray", "dimgray");
    IlvPalette* palch = GetPalette(dpy, "white", "black");
    IlvChartGraphic* chart =
	new IlvCartesianChart(dpy,
			      IlvRect(0, 0, 800, 600),
			      IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      palch,
			      gridpal);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("gray"),
				      dpy->getColor("white"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    IlvPalette* palette = dpy->getPalette(dpy->getColor("darkgray"),
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
    chart->setDrawOrder(IlvDrawBelow);

    // Add the zoom transformer on the abscissa scale
    IlvZoomCoordinateTransformer* t =
	new IlvZoomCoordinateTransformer(IlvCoordInterval(NbPts / 2
							  - NbPts / 20,
							  NbPts / 2 +
							  NbPts / 20), 4);
    chart->getAbscissaInfo()->setTransformer(t);

    // Connect the step updater to the abscissa scale
    IlvSingleScaleDisplayer* scale = chart->getAbscissaScale();
    delete IlvScaleStepsUpdater::Set(scale,
				     new IlvZoomScaleStepsUpdater(scale));

    // Add two cursors to the scale to highlight the zoom window.
    IlvAbstractChartCursor* cursor =
	chart->addAbscissaCursor(t->getZoomWindow().getMin());
    cursor->setName("ZoomWindowStart");
    cursor = chart->addAbscissaCursor(t->getZoomWindow().getMax());
    cursor->setName("ZoomWindowEnd");

    // Create 2 data sets and add them to the chart data object.
    IlvChartDataSet* dataSets[2];
    dataSets[0] = CreateSmoothDataSet(NbPts, 2);
    dataSets[1] = CreateSmoothDataSet(NbPts, 2);
    IlUInt count = 2;
    chart->getData()->setDataSets(count, dataSets);

    // Create and add the displayers.
    IlvAbstractChartDisplayer* disp =
	new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledSquare,
					    2,
					    GetPalette(dpy, "gray", "gold"),
					    GetPalette(dpy, "gray", "yellow"));

    chart->addDisplayer(disp, dataSets[0]);
    disp =
	new IlvMarkedPolylineChartDisplayer(IlvMarkerFilledSquare,
					    2,
					    GetPalette(dpy, "gray", "red"),
					    GetPalette(dpy, "gray", "pink"));
    chart->addDisplayer(disp, dataSets[1]);

    // Add the chart to the container.
    addObject(chart, IlTrue);
    setGraphicAttachments(chart);

    // Add accelerators to modify the zoom transformer.
    addAccelerator(ChangeZoom,	IlvKeyDown,	IlvRightKey, 0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	IlvLeftKey,  0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	IlvUpKey,    0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	IlvDownKey,  0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	'c',         0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	'+',         0, chart);
    addAccelerator(ChangeZoom,	IlvKeyDown,	'-',         0, chart);
    addAccelerator(Quit,	IlvKeyUp,	'q'		      );
    addAccelerator(ChangeProjectorAcc, IlvKeyUp, 'p', 0, chart);

    // Add behaviors to the chart
    IlvChartInteractorManager* interMgr = new IlvChartInteractorManager();
    interMgr->addInteractor("ChartInfoView");
    interMgr->addInteractor("ChartDragPoint");
    interMgr->addInteractor("ChartZoom");
    interMgr->addInteractor("ChartPan");
    IlvChartInteractorManager::Set(chart, interMgr);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageLens(Pan* mainPanel)
{
    Lens* panel = new Lens(mainPanel, "lens.ilv");
    mainPanel->addPageNoteBook(panel, "Lens", "lens.txt");
}
