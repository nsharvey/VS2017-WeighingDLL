// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/interactors/src/stock.cpp
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
// Sample demonstrating hi/lo chart displayers and interactors.
// --------------------------------------------------------------------------

#include <stock.h>

#if defined(IL_STD)
IL_STDUSE
#include <fstream>
#include <cstdlib>
#else  /* !IL_STD */
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
static IlvChartInteractor*
GetViewInfoInteractor(IlvChartInteractorManager* interMgr)
{
    IlString t = "ChartInfoView";
    IlString g;
    IlUInt i;
    for (i = 0; i < interMgr->getCardinal(); i++) {
        g = interMgr->getInteractor(i)->getRegisteredName();
	if (t == g) {
	    return interMgr->getInteractor(i);
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
static void
ToggleInfoAcc(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvChartInteractorManager* interMgr =
	IL_CAST(IlvChartInteractorManager*, arg);
    if (GetViewInfoInteractor(interMgr) != 0) {
        interMgr->removeInteractor("ChartInfoView");
    }
    else {
        interMgr->addInteractor("ChartInfoView");
    }
}

// --------------------------------------------------------------------------
static void
ToggleInfoPickingMode(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvChartInteractorManager* interMgr =
	IL_CAST(IlvChartInteractorManager*, arg);
    IlvChartDataInteractor* inter =
	IL_CAST(IlvChartDataInteractor*, GetViewInfoInteractor(interMgr));
    if (!inter) {
        return;
    }

    IlvChartDataInteractor::PickingMode mode = inter->getPickingMode();

    mode = (mode == IlvChartDataInteractor::NearestPointPicking)
	? IlvChartDataInteractor::ItemPicking
	: IlvChartDataInteractor::NearestPointPicking;

    IlvPrint("Toggling picking mode to %s",
             (mode == IlvChartDataInteractor::NearestPointPicking)
	     ? "NearestPoint"
	     : "ItemPicking");

    inter->setPickingMode(mode);
}

// --------------------------------------------------------------------------
static void
ToggleFollowMouseMode(IlvContainer* p, IlvEvent&, IlAny arg)
{
    IlvChartInteractorManager* interMgr =
	IL_CAST(IlvChartInteractorManager*, arg);
    IlvChartInfoViewInteractor* inter =
	IL_CAST(IlvChartInfoViewInteractor*, GetViewInfoInteractor(interMgr));
    if (!inter) {
        return;
    }
    IlBoolean mode = !inter->isFollowingMouse();

    IlvPrint("Toggling follow mouse mode to %s",
             (mode) ? "true" : "false");

    inter->setFollowingMouse(mode);
}

// --------------------------------------------------------------------------
int
getMonthNum(IlString monthName)
{
    static const char* monthNames[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    for (unsigned int i = 0; i < 12; ++i) {
        if (monthName == IlString(monthNames[i])) {
	    return i + 1;
	}
    }

    return 0;
}

// --------------------------------------------------------------------------
static IlvAbstractChartData*
ParseStockStream(istream&		inFile,
		 IlvMemoryChartData*	data,
		 IlvChartPointSet*	lo,
		 IlvChartPointSet*	hi,
		 IlvChartPointSet*	open,
		 IlvChartPointSet*	close,
		 IlvChartPointSet*	volume)
{
    char buf[512];
    inFile.getline(buf,512,'\n'); // skip 1st line (column names)

    IlvDouble calTime = 0;
    int count = 0;

    int day = 1, month = 1, year = 1900;
    IlDateErrorCode s = IL_DATE_ZERO_ERROR;
    IlGregorianCalendar cal(s);

    IlvChartDoubleArray aLo, aHi, aOpen, aClose, aVolume, aTime;

    while (!inFile.eof() && inFile.good() && count < 5000) {
	inFile.getline(buf, 512, '\n');
        ++count;
	if (inFile.eof() || !inFile.good()) {
	    break;
	}

        char monthName[20];
        double fLo = 0.0, fHi = 0.0, fOpen = 0.0, fClose = 0.0, fVolume = 0.0;

        // Date,Open,High,Low,Close,Volume
	char* ptr = buf;
	char* previous = buf;
	while(ptr && *ptr && (*ptr != '-')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    day = atoi(previous);
	    ptr++;
	    previous = ptr;
	}

	while(ptr && *ptr && (*ptr != '-')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    strcpy(monthName,previous);
	    ptr++;
	    previous = ptr;
	}
	while(ptr && *ptr && (*ptr != ',')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    year = atoi(previous);
	    ptr++;
	    previous = ptr;
	}
	while(ptr && *ptr && (*ptr != ',')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    fOpen = IlA2D(previous);
	    ptr++;
	    previous = ptr;
	}
	while(ptr && *ptr && (*ptr != ',')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    fHi = IlA2D(previous);
	    ptr++;
	    previous = ptr;
	}
	while(ptr && *ptr && (*ptr != ',')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    fLo = IlA2D(previous);
	    ptr++;
	    previous = ptr;
	}
	while(ptr && *ptr && (*ptr != ',')) {
	    ptr++;
	}
	if (ptr && *ptr) {
	    *ptr = '\0';
	    fClose = IlA2D(previous);
	    ptr++;
	    previous = ptr;
	    fVolume = IlA2D(previous);
	}
        month = getMonthNum(monthName);
        if (year < 70) {
	  year += 2000;
	}
        else {
	  year += 1900;
	}

        cal.set(year, month, day);
        calTime = cal.getTime(s);

        aTime  .push(calTime);
        aLo    .push(fLo);
        aHi    .push(fHi);
        aOpen  .push(fOpen);
        aClose .push(fClose);
        aVolume.push(fVolume);
    }

    // Store points in pointsets in reverse order
    for (int i = aTime.getLength() - 1; i >= 0; --i) {
	lo    ->addPoint(IlvDoublePoint(aTime[i], aLo[i]));
	hi    ->addPoint(IlvDoublePoint(aTime[i], aHi[i]));
	open  ->addPoint(IlvDoublePoint(aTime[i], aOpen[i]));
	close ->addPoint(IlvDoublePoint(aTime[i], aClose[i]));
	volume->addPoint(IlvDoublePoint(aTime[i], aVolume[i]));
    }

    data->addDataSet(lo);
    data->addDataSet(hi);
    data->addDataSet(open);
    data->addDataSet(close);
    data->addDataSet(volume);
    return data;
}

// --------------------------------------------------------------------------
static IlvAbstractChartData*
ReadStockFile(const char* stockFilename)
{
    IlvMemoryChartData* data	= new IlvMemoryChartData();
    IlvChartPointSet* lo	= new IlvChartPointSet();
    IlvChartPointSet* hi	= new IlvChartPointSet();
    IlvChartPointSet* open	= new IlvChartPointSet();
    IlvChartPointSet* close	= new IlvChartPointSet();
    IlvChartPointSet* volume	= new IlvChartPointSet();
    lo    ->setName("lo");
    hi    ->setName("hi");
    open  ->setName("open");
    close ->setName("close");
    volume->setName("volume");

    const char* urlFormat = "http://chart.yahoo.com/table.csv?s=ilog"
        "&a=%d&b=%d&c=%d&d=%d&e=%d&f=%d&g=d&q=q&y=0&z=ilog&x=.csv";

    char url[2048];

    time_t now = time(0);
    struct tm *timeM = localtime(&now);
    sprintf(url,
	    urlFormat,
            timeM->tm_mday,
	    timeM->tm_mon,
	    timeM->tm_year + 1900 - 1,
            timeM->tm_mday,
	    timeM->tm_mon, timeM->tm_year + 1900);

    istream *inFile = new ifstream(stockFilename);

    IlvAbstractChartData* res =
	ParseStockStream(*inFile, data, lo, hi, open, close, volume);

    delete inFile;
    return res;
}

// --------------------------------------------------------------------------
// Panel class for sample Stock
// --------------------------------------------------------------------------
Stock::Stock(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initStock();
}

// --------------------------------------------------------------------------
Stock::~Stock()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Stock::initStock()
{
    IlvRect size(50,25,700,400);
    IlvDisplay* dpy = getDisplay();

    // Create the panel
    IlvChartGraphic* chart = new IlvCartesianChart(dpy, size);
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

    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();
    abscissaScale->setAutoStepsCount(IlTrue, 10, 0);

    IlvTimeScaleStepsUpdater* updater =
        new IlvTimeScaleStepsUpdater(abscissaScale);

    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);

    IlvAbstractGridDisplayer* grid = chart->addAbscissaGrid();
    grid->setMajorPalette(dpy->getPalette(0, dpy->getColor("gray")));
    grid->setDrawOrder(IlvDrawBelow);

    chart->getOrdinateScale()->setRelativePosition(IlvMinDataPosition, -3);

    IlvRectangularScaleDisplayer* ordinateScale2 =
	new IlvRectangularScaleDisplayer(new IlvCoordinateInfo(IlvOrdinateCoordinate),
					 chart->getPalette());
    ordinateScale2->setRelativePosition(IlvMaxDataPosition, -3);
    chart->addOrdinateScale(ordinateScale2);

    chart->setData(ReadStockFile(dpy->findInPath("stock.dat")));
    IlUInt dsCount;
    IlvChartDataSet* const* dataSets = chart->getDataSets(dsCount);

    IlvPalette* pal = GetPalette(dpy, "wheat", "black");

    // Bar chart
    IlvBarChartDisplayer* volumeDisp = new IlvBarChartDisplayer(6,pal);
    chart->addDisplayer(volumeDisp,chart->getData()->getDataSetByName("volume")
                        /*,chart->getOrdinateInfo(1)*/);
    volumeDisp->setWidthPercent(200);

    IlvPalette* palettes[3];
    palettes[0] = GetPalette(dpy, "black",		"black");
    palettes[1] = GetPalette(dpy, "lightsteelblue",	"blue");
    palettes[2] = GetPalette(dpy, "coral",		"red");

    // Hilo chart
    IlvHiLoOpenCloseChartDisplayer* hiloOCDisp =
	new IlvHiLoOpenCloseChartDisplayer(6,
					   palettes[0],
					   palettes[1],
					   palettes[0],
					   palettes[2]);
    chart->addDisplayer(hiloOCDisp,
			4,
			dataSets,
		        chart->getOrdinateInfo(1));
    hiloOCDisp->setWidthPercent(200);

    // Create and add a legend
    IlvChartLegend* legend = new IlvChartLegend(dpy,IlvRect(50, 25, 500, 40));
    legend->setItemSpacing(30);
    legend->showFrame(IlFalse);
    chart->setLegend(legend);
    chart->getLayout()->setTopMargin(30);

    addObject(chart);
    addObject(legend);
    setGraphicAttachments(chart);

    // Add interactions on the chart
    // Create an interactor manager
    IlvChartInteractorManager* interMgr = new IlvChartInteractorManager();

    // Add several behaviors
    IlvChartZoomInteractor* zinter = new IlvChartZoomInteractor();
    zinter->setZoomSteps(4);
    interMgr->addInteractor(zinter);
    interMgr->addInteractor("ChartPan");
    interMgr->addInteractor("ChartScroll");
    interMgr->addInteractor("ChartInfoView");

    // Attach the interactor manager to the chart
    // This automaticallly creates an  interactor dispatcher
    // and associates it with the chart
    IlvChartInteractorManager::Set(chart, interMgr);
    addAccelerator(ToggleInfoAcc, IlvKeyUp, 'i', 0, interMgr);
    addAccelerator(ToggleInfoPickingMode, IlvKeyUp, 's', 0, interMgr);
    addAccelerator(ToggleFollowMouseMode, IlvKeyUp, 'm', 0, interMgr);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageStock(Pan* mainPanel)
{
    Stock* panel = new Stock(mainPanel,"stock.ilv");
    mainPanel->addPageNoteBook(panel, "Stock", "stock.txt");
}
