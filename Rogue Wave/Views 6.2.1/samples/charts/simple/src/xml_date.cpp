// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/simple/src/xml_date.cpp
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
// Example of a chart using XML data
// --------------------------------------------------------------------------

#include <xml_date.h>

#if defined(IL_STD)
IL_STDUSE
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */

class IlvChartDefaultColors;

// --------------------------------------------------------------------------
static IlvDisplay* dpy = 0;
static IlvChartDefaultColors* defaultColors = 0;

// --------------------------------------------------------------------------
// Constants
static const IlDouble MinCoord = 0.;
static const IlDouble MaxCoord = 10.;

// --------------------------------------------------------------------------
// Panel class for sample XmlDate
// --------------------------------------------------------------------------
XmlDate::XmlDate(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    initXmlDate();
}

// --------------------------------------------------------------------------
XmlDate::~XmlDate()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
XmlDate::initXmlDate()
{
    IlvDisplay* dpy = getDisplay();

    const char* buf = dpy->getEnvOrResource("ILVHOME");
    if (buf) {
        dpy->appendToPath(buf);
    }

    defaultColors = new IlvChartDefaultColors(dpy);

    // Get XML data
    IlvXMLChartData xmlDataSet(dpy,
			       "samples/charts/simple/data/dataset_sample_date.xml");
    xmlDataSet.parse();

    // Creates a new cartesian chart.
    // The following line is equivalent to :
    IlvRect sizeChartGraphic(0, 50, 400, 250);

    IlvChartGraphic* chart = new IlvCartesianChart(dpy, sizeChartGraphic);
    IlvGradientPattern* gradientPattern =
	dpy->getLinearGradientPattern(dpy->getColor("slategray"),
				      dpy->getColor("white"),
				      IlvPoint(1, 0),
				      IlvPoint(0, 1));
    IlvPalette* palette = dpy->getPalette(0,
					  dpy->getColor("white"),
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

    // Create and set a cartesian projector
    chart->setProjector(new IlvCartesianProjector(IlvCartesianProjector::IlvXRightYTop));
	
    //-------------------
    // X Axis
    //-------------------
    IlvSingleScaleDisplayer* abscissaScale = chart->getAbscissaScale();

    abscissaScale->setAutoStepsCount(IlTrue, 10, 0);
    IlvTimeScaleStepsUpdater* updater =
        new IlvTimeScaleStepsUpdater(abscissaScale);
    updater->setAutoUnit(IlTrue);

    delete IlvScaleStepsUpdater::Set(abscissaScale, updater);

    //-------------------
    // Y Axis
    //-------------------
    IlvCoordinateInfo* coordInfo =
        new IlvCoordinateInfo(IlvOrdinateCoordinate
			      /*, new IlvSimpleChartTransformer(10)*/);

    IlvPalette *PaletteAxeY = new IlvPalette(dpy);
    IlvRectangularScaleDisplayer* ordinateScale =
        new IlvRectangularScaleDisplayer(coordInfo, PaletteAxeY);
    ordinateScale->drawLabelOnCrossings(IlTrue);

    // Add a grid to the scale
    IlvPalette* majPal = dpy->getPalette(0, dpy->getColor("black"));
    IlvPalette* minPal = dpy->getPalette(0,
					 dpy->getColor("blue"),
					 0,
					 0,
					 0,
					 dpy->alternateLineStyle());
    IlvAbstractGridDisplayer* grid =
       new IlvRectangularGridDisplayer(majPal, minPal);
    grid->drawMinorLines(IlTrue);
    grid->setDrawOrder(IlvDrawBelow);
    ordinateScale->setGridDisplayer(grid);
	
    ordinateScale->setStepLabelsVisible (IlTrue);

    chart->addOrdinateScale(ordinateScale);
    chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(0.0, 30.0));

    IlUInt count;
    IlvChartDataSet* const* dataSets = xmlDataSet.getDataSets(count);

    chart->getData()->setDataSets(count, dataSets);

    chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[0]);

    // Set different colors for the displayers.
    chart->getDisplayer(0)->setForeground(dpy->getColor("red"));
    chart->getDisplayer(0)->setLegendText("Legende Display. 1");

    // Add the chart to the container.
    addObject(chart);

    // Attachement
    if (!IlvAttachmentsHandler::Get(this)) {
	IlvAttachmentsHandler::Set(this, new IlvAttachmentsHandler());
    }
    IlvSetAttachment(chart, IlvLeft,		IlvFixedAttach,		15);
    IlvSetAttachment(chart, IlvTop,		IlvFixedAttach,		25);
    IlvSetAttachment(chart, IlvRight,		IlvFixedAttach,		15);
    IlvSetAttachment(chart, IlvBottom,		IlvFixedAttach,		15);
    IlvSetAttachment(chart, IlvHorizontal,	IlvElasticAttach,	 0);
    IlvSetAttachment(chart, IlvVertical,	IlvElasticAttach,	 0);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageXmlDate(Pan* mainPanel)
{
    XmlDate* panel = new XmlDate(mainPanel,"xml_date.ilv");
    mainPanel->addPageNoteBook(panel, "Xml date", "xml_date.txt");
}
