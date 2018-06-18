// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/bubble/src/bubble.cpp
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
// Bubble displayer demo.
// --------------------------------------------------------------------------
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/base/timer.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/bitmaps/png.h>
#include <ilog/pathname.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

#if defined(IL_STD)
#  include <cstdlib>
#  include <cstdio>
IL_STDUSE
#else
#  include <stdlib.h>
#  include <stdio.h>
#endif
IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// Static variables
static const char*	FileName	= "data/bubble.ilv";
static const char*	BitmapName	= "data/orb.png";
static const char*	title		= "Bubble Chart";
static const IlDouble	MinY		=   0.;
static const IlDouble	MaxY		= 100.;
static const IlUInt	NbPoints	=   8;
static IlUInt		LogCount	=   20;

// --------------------------------------------------------------------------
static char*
ValueToLabelCB(IlDouble val, IlAny)
{
    char* label = new char[16];
    sprintf(label, "In#%u", IL_CAST(unsigned, val) + 1);
    return label;
}

// --------------------------------------------------------------------------
// Modify the projector
static void
ChangeProjector(IlvChartGraphic* chart, int orient)
{
    if (!chart)
	return;
#if CHANGETOPOLAR
    chart->setProjector(new IlvPolarProjector(0., 360., IlTrue));
    chart->getAbscissaInfo()->setUserDataRange(IlvCoordInterval(0,
								NbPoints - 1));
#else
    IlvCartesianProjector* prj =
	IL_CAST(IlvCartesianProjector*, chart->getProjector());
    prj->setOrientation(IL_CAST(IlvCartesianProjector::Orientation, orient));
#endif
    chart->invalidateLayout();
    chart->updateAndReDraw();
}

// --------------------------------------------------------------------------
static void
ChangeProjectorAcc(IlvContainer* cont, IlvEvent&, IlAny arg)
{
    static int orient = 0;
    orient = (orient + 1) % 8;
    ChangeProjector(IL_CAST(IlvChartGraphic*, cont->getObject("Chart1")),
		    orient);
    ChangeProjector(IL_CAST(IlvChartGraphic*, cont->getObject("Chart2")),
		    orient);
}

// --------------------------------------------------------------------------
// Change the graphic object used to display the 'bubbles'
static void
ChangeBubbleTypeAcc(IlvContainer* cont, IlvEvent&, IlAny arg)
{
    static IlUInt cpt = 1;
    IlvBubbleChartDisplayer* disp = IL_CAST(IlvBubbleChartDisplayer*, arg);
    IlvDisplay* dpy = cont->getDisplay();
    IlvGraphic* g;
    switch (cpt) {
    case 0:
	g = new IlvFilledArc(dpy, IlvRect(0, 0, 41, 41), 0, 360);
	break;
    case 1:
    default:{
	IlvBitmap* bmp = dpy->readBitmap(BitmapName);
	g = new IlvZoomableTransparentIcon(dpy, IlvPoint(0, 0), bmp);
	break;
    }
    }
    delete disp->setGraphicModel(g);
    disp->getChartGraphic()->updateAndReDraw();;
    cpt = (cpt + 1) % 2;
}

// --------------------------------------------------------------------------
// Timer to randomly change data values
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
    IlvChartDataSet* dataSet = IL_CAST(IlvChartDataSet*, arg);
    IlvDoublePoint dataPoint;
    IlUInt count = dataSet->getDataCount();
    for (IlUInt i = 0; i < count; ++i) {
	if (!(rand() % NbPoints))
	    continue;
	dataSet->getPoint(i, dataPoint);
	dataPoint.y(IlMin(IlAbs(dataPoint.y() + ((rand() % 100) - 50) / 10),
			  MaxY));
	dataSet->setPoint(i, dataPoint);
    }
}

// --------------------------------------------------------------------------
// The InputListener class listen to changes on the main data values
// It keeps track of the maximum value of each data point between <LogCount>
// changes and computes a weighted average of all the values taken by
// a data point. The maximum and average values are stored respectively
// in the <logDataSet> and <avgDataSet> data sets.
class InputListener : public IlvChartDataSetListener
{
public:
    InputListener(IlvChartDataSet* logDataSet,
		  IlvChartDataSet* avgDataSet);

    virtual ~InputListener();

    virtual void	dataPointChanged(const IlvChartDataSet*	dataSet,
					 IlUInt			position,
					 IlBoolean		beforeChange);

protected:
    IlvChartDataSet*	_logDataSet;
    IlUInt*		_logCounter;
    IlvChartDataSet*	_avgDataSet;
};

// --------------------------------------------------------------------------
InputListener::InputListener(IlvChartDataSet* logDataSet,
			     IlvChartDataSet* avgDataSet)
    : _logDataSet(logDataSet),
      _avgDataSet(avgDataSet)
{
    IlUInt count = logDataSet->getDataCount();
    _logCounter = new IlUInt[count];
    memset(_logCounter, 0, count*sizeof(IlUInt));
}

// --------------------------------------------------------------------------
InputListener::~InputListener()
{
    delete [] _logCounter;
}

// --------------------------------------------------------------------------
void
InputListener::dataPointChanged(const IlvChartDataSet*	dataSet,
				IlUInt			idx,
				IlBoolean		beforeChange)
{
    if (beforeChange)
	return;
    IlvDoublePoint oldDataPt, newDataPt;
    _logDataSet->getPoint(idx, oldDataPt);
    dataSet->getPoint(idx, newDataPt);
    if ((_logCounter[idx]>LogCount) ||
	newDataPt.y() > oldDataPt.y()) {
	_logCounter[idx] = 0;
	_logDataSet->setPoint(idx, newDataPt);
    }
    else ++(_logCounter[idx]);

    _avgDataSet->getPoint(idx, oldDataPt);
    newDataPt.y((oldDataPt.y() * (LogCount - 1) + newDataPt.y()) / LogCount);
    _avgDataSet->setPoint(idx, newDataPt);
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

    IlPathName path = dpy->getHomePath();
    path.addDirectory("samples/charts/bubble");
    dpy->prependToPath(path.getDirectory());

    // This enables reDraw requests to be buffered and optimized without
    // having to use iniReDraws/reDrawViews explicitely.
    IlvEventLoop::getEventLoop()->setLazyRedraw(4);

    // Create the panel
    IlvRect size(0, 0, 500, 700);
    IlvContainer* cont =
	new IlvContainer(dpy, "Panel", title, size, IlTrue, IlFalse);
    cont->setMinimumSize(size.w(), size.h());
    cont->setMaximumSize(size.w(), size.h());

    if (!cont->readFile(FileName)) {
	IlvFatalError("Could not open file: %s", FileName);
	IlvExit(1);
    }

    // Create te data sets.
    IlvChartYValueSet* inputSet = CreateYDataSet(NbPoints, 0, 0);
    IlvChartDataSet* logSet = inputSet->copy();
    IlvChartDataSet* avgSet = inputSet->copy();

    // Connect the data sets
    inputSet->addListener(new InputListener(logSet, avgSet));

    // Palettes for the charts
    IlvPalette* pal = dpy->getPalette(dpy->getColor("lightgray"),
				      dpy->getColor("white"),
				      0,
				      0,
				      dpy->getFont("%helvetica-12-B"));
    IlvPalette* gridpal = dpy->getPalette(0, dpy->getColor("dimgray"));

    // Create the first chart
    IlvRect rect;
    cont->getObject("ChartRect1")->boundingBox(rect);
    IlvChartGraphic* chart1 =
	new IlvCartesianChart(dpy,
			      rect,
			      IlTrue,
			      IlvCartesianProjector::IlvXRightYTop,
			      pal,
			      gridpal);
    rect.expand(-50);
    chart1->setDrawOrder(IlvDrawBelow);
    chart1->getLayout()->setDataDisplayArea(rect);
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
    chart1->setDataAreaBackgroundPalette(pal);
    chart1->setFillMode(IlvChartGraphic::FillDataArea);

    chart1->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(MinY, MaxY));
    IlvSingleScaleDisplayer* scale = chart1->getAbscissaScale();
    scale->getGridDisplayer()->setVisible(IlFalse);
    delete IlvScaleStepsUpdater::Set(scale,
				     new IlvConstantScaleStepsUpdater(scale,
								      1.));
    scale->setValueToLabelCB(ValueToLabelCB);
    scale->setDrawOrder(IlvDrawAbove);
    chart1->getOrdinateScale()->setRelativePosition(IlvMinDataPosition, -20);
    chart1->getOrdinateScale()->setDrawOrder(IlvDrawAbove);

    // Create the second chart
    IlvChartGraphic* chart2 = IL_CAST(IlvChartGraphic*, chart1->copy());
    cont->getObject("ChartRect2")->boundingBox(rect);
    chart2->moveResize(rect);
    rect.expand(-50);
    chart2->getLayout()->setDataDisplayArea(rect);

    // Add the data sets and displayers to the first chart
    IlvChartDataSet* dataSets[2];
    chart1->getData()->addDataSet(logSet);
    dataSets[0] = logSet;
    chart1->getData()->addDataSet(avgSet);
    dataSets[1] = avgSet;
    gradientPattern =
	dpy->getRadialGradientPattern(dpy->getColor("white"),
				      dpy->getColor("palegreen"),
				      IlvPoint(3,3),
				      1,
				      IlvPoint(5, 5),
				      5);
    pal = dpy->getPalette(dpy->getColor("palegreen"),
			  dpy->getColor("dimgray"),
			  dpy->light3Pattern(),
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
    IlvGraphic* g = new IlvFilledArc(dpy, IlvRect(0, 0, 41, 41), 0, 360);
    IlvBubbleChartDisplayer* bubbleDisp =
	new IlvBubbleChartDisplayer(g, 80, 20, pal);
    // Add annotations to the bubbles
    IlvChartDataPointLabel* ptLabel =
	new IlvChartDataPointLabel(dpy,
				   0,
				   0,
				   IlvCenter,
				   IlvChartDataPointLabel::YValue,
				   "%.0f");
    ptLabel->getGraphic()->setFont(dpy->getFont("%helvetica-14-B"));
    bubbleDisp->setPointInfoCollection(avgSet,
				       new IlvPointInfoSingleton(ptLabel));
    chart1->addDisplayer(bubbleDisp, 2, dataSets);


    // Add the data sets and displayers to the second chart
    pal = GetPalette(dpy, "palegreen", "limegreen");
    chart2->getData()->addDataSet(inputSet);
    chart2->getData()->addDataSet(logSet);
    IlvSingleChartDisplayer* disp = new IlvBarChartDisplayer(20, pal);
    chart2->addDisplayer(disp, inputSet);
    pal = dpy->getPalette(0, dpy->getColor("limegreen"), 0, 0, 0, 0, 3);
    disp = new IlvFixedStepChartDisplayer(20, pal);
    chart2->addDisplayer(disp, logSet);
    // Add annotations to the step displayer
    ptLabel = new IlvChartDataPointLabel(dpy,
					 0,
					 4,
					 IlvBadPosition,
					 IlvChartDataPointLabel::YValue,
					 "%.0f");
    ptLabel->getGraphic()->setForeground(dpy->getColor("antiquewhite"));
    ptLabel->getGraphic()->setFont(dpy->getFont("%helvetica-12-"));
    disp->setPointInfoCollection(logSet, new IlvPointInfoSingleton(ptLabel));

    // Add the charts to the container.
    cont->addObject("Chart1", chart1);
    cont->addObject("Chart2", chart2);

    // Add a timer to randomly change values.
    IlvTimer* timer = new IlvTimer(dpy, 0, 100, SimulateTimerCB, inputSet);
    timer->run();

    // Add some accelerators.
    cont->addAccelerator(RunTimer,		IlvKeyUp, 'r', 0, timer);
    cont->addAccelerator(StopTimer,		IlvKeyUp, 's', 0, timer);
    cont->addAccelerator(ChangeProjectorAcc,	IlvKeyUp, ' ');
    cont->addAccelerator(ChangeBubbleTypeAcc,	IlvKeyUp, 'b', 0, bubbleDisp);
    cont->addAccelerator(Quit,			IlvKeyUp, 'q');

    cont->setDestroyCallback(Quit);
    cont->setDoubleBuffering(IlTrue);
    cont->show();
    IlvMainLoop();
    return 0;
}
