// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/simple/src/xml.cpp
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

#include <xml.h>

#if defined(IL_STD)
IL_STDUSE
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#else  /* !IL_STD */
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// General purpose functions for the samples
// --------------------------------------------------------------------------

class IlvChartDefaultColors;

static IlvChartDefaultColors* defaultColors = 0;
static IlShort displayerType;

// --------------------------------------------------------------------------
/**
 * Example of a property reader
 */
class MyPropertyReader : public IlvXMLPropertyReader
{
public:

    virtual IlvXMLProperty*	readProperty(IlXmlElement*	propertyElt);

    virtual IlBoolean		setProperty(IlvChartDataSet*	dataSet,
					    IlString		propertyName,
					    IlAny		value);
};

// --------------------------------------------------------------------------
IlvXMLProperty*
MyPropertyReader::readProperty(IlXmlElement* propertyElt)
{
    int value;

    IlString propertyName = propertyElt->getAttributeValue("name");

    IlString propertyValue = propertyElt->getText();

    sscanf(propertyValue.getValue(), " %d", &value);

    IlvXMLProperty* prop = new IlvXMLProperty;
    prop->name = propertyName;
    prop->value = IlCastIlIntToIlAny(value);

    return prop;
}

// --------------------------------------------------------------------------
IlBoolean
MyPropertyReader::setProperty(IlvChartDataSet*	dataSet,
			      IlString		propertyName,
			      IlAny		value)
{
    // indicate that property must be deleted
    return IlTrue;
}

// --------------------------------------------------------------------------
static void
UpdateChart(IlvChartGraphic* chart)
{
    IlUInt count;
    IlvChartDataSet* const* dataSets = chart->getData()->getDataSets(count);

    chart->removeDisplayers();
    IlvAbstractChartDisplayer *displayer = 0;
    if (displayerType > 1) {
	// multi data set displayer
        switch (displayerType) {
        case 2:
            displayer = new IlvHiLoChartDisplayer;
            break;
        case 3:
            displayer = new IlvHiLoBarChartDisplayer;
            break;
        case 4:
            displayer = new IlvHiLoOpenCloseChartDisplayer;
            break;
        default:
            displayer = new IlvHiLoChartDisplayer;
        }
        chart->addDisplayer(displayer, count, dataSets);
    }
    else {
	// single data set displayer
        IlUInt nbColors = defaultColors->getNbColors();
        for (unsigned int i = 0; i < count; ++i) {
            IlvAbstractChartDisplayer *displayer = 0;
            switch (displayerType) {
            case 0:
                displayer = new IlvPolylineChartDisplayer;
                break;
            case 1:
                displayer = new IlvBarChartDisplayer;
                break;
            default:
                displayer = new IlvPolylineChartDisplayer;
            }

            chart->addDisplayer(displayer, dataSets[i]);
            IlvColor *color = defaultColors->getColor(i % nbColors);
            displayer->setForeground(color);
        }
    }
    chart->reDraw();
}


// --------------------------------------------------------------------------
static void
LoadXML(IlvGraphic* graphic, IlAny containerArg)
{
    Xml* panel = (Xml*)containerArg;
    IlvChartGraphic* chart = panel->getChartGraphic();
    IlvDisplay* display = panel->getDisplay();
    const char* filters[] = { "*.xml" };
    const char* messages[] = { "XML Files" };
    const char* home = display->getEnvOrResource("ILVHOME", 0);
    IlPathName dataPath;
    if (home && *home) {
        IlString strHome = home;
        strHome+= "/";
        dataPath= strHome;
        dataPath.addDirectory("samples/charts/simple/data/");
    }
    IlvFileBrowser* browser =
	new IlvFileBrowser(display, 0, dataPath, 1, filters, messages);
    IlString res = browser->get();
    delete browser;

    // Get XML data
    IlvXMLChartData xmlDataSet(display, res);

    xmlDataSet.registerPropertyReader("period", new MyPropertyReader);

    xmlDataSet.parse();

    IlUInt count;
    IlvChartDataSet* const* dataSets = xmlDataSet.getDataSets(count);
    chart->getData()->setDataSets(count, dataSets);

    if (xmlDataSet.getDataSetsCount() > 0) {
        UpdateChart(chart);
    }
    else {
        IlvWarning("No dataset found");
    }
}

// --------------------------------------------------------------------------
static void
SetDisplayerCB(IlvGraphic* graphic, IlAny containerArg)
{
    Xml* panel = IL_CAST(Xml*, containerArg);
    IlvComboBox* combo = panel->getComboBox();
    IlvChartGraphic* chart = panel->getChartGraphic();

    displayerType = combo->whichSelected();
    UpdateChart(chart);
}

// --------------------------------------------------------------------------
// Constants
static const IlDouble MinCoord = 0.;
static const IlDouble MaxCoord = 10.;

// --------------------------------------------------------------------------
// Panel class for sample Xml
// --------------------------------------------------------------------------
Xml::Xml(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename)
{
    _combo = 0;
    _chart = 0;
    initXml();
}

// --------------------------------------------------------------------------
Xml::~Xml()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Xml::initXml()
{
    IlvDisplay* dpy = getDisplay();

    const char* buf = dpy->getEnvOrResource("ILVHOME");
    if (buf) {
        dpy->appendToPath(buf);
    }

    defaultColors = new IlvChartDefaultColors(dpy);

    // Get XML data
    IlvXMLChartData xmlDataSet(dpy,
			       "samples/charts/simple/data/dataset_sample.xml");

    xmlDataSet.registerPropertyReader("period", new MyPropertyReader);

    xmlDataSet.parse();

    // Creates a new cartesian chart.
    // The following line is equivalent to :
    IlvRect sizeChartGraphic(0, 50, 400, 250);

    _chart = new IlvChartGraphic(dpy, sizeChartGraphic);
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
    _chart->setDataAreaBackgroundPalette(palette);

    _chart->setFillMode(IlvChartGraphic::FillDataArea);
    // Create and set a cartesian projector
    _chart->setProjector(new IlvCartesianProjector(IlvCartesianProjector::IlvXRightYTop));
	
    //-------------------
    // X Axis : Linear
    //-------------------
    // Create the coordinate information for the abscissa:
    IlvCoordinateInfo* coordInfo =
	new IlvCoordinateInfo(IlvAbscissaCoordinate);
	
    // Create and set the abscissa scale
    IlvPalette *PaletteAxeX = new IlvPalette(dpy);

    IlvRectangularScaleDisplayer* abscissaScale =
	new IlvRectangularScaleDisplayer(coordInfo, PaletteAxeX);
    abscissaScale->drawLabelOnCrossings(IlTrue);
    abscissaScale->setStepLabelFormat("%.0f");
    abscissaScale->setAxisLabel("Hz");
    abscissaScale->setAxisOriented(IlTrue);
    _chart->setAbscissaScale(abscissaScale);
    abscissaScale->getAxisPalette()->setForeground(dpy->getColor("red"));
	
    // Set a manual range for the abscissa coordinate
    _chart->getAbscissaInfo()
        ->setUserDataRange(IlvCoordInterval(MinCoord, MaxCoord));

    // We want to draw the step label where the abscissa scale crosses
    // the ordinate scale
    abscissaScale->drawLabelOnCrossings(IlTrue);

    //-------------------
    // Y Axis : Logarithmic
    //-------------------
    coordInfo = new IlvCoordinateInfo(IlvOrdinateCoordinate
				      /*, new IlvSimpleChartTransformer(10)*/);

    IlvPalette *PaletteAxeY = new IlvPalette(dpy);
    IlvRectangularScaleDisplayer* ordinateScale =
	new IlvRectangularScaleDisplayer(coordInfo, PaletteAxeY);
    ordinateScale->drawLabelOnCrossings(IlTrue);
    ordinateScale->setAxisLabel("g");
    ordinateScale->setAxisOriented(IlTrue);
    ordinateScale->setAxisLabelOffset(5);
    ordinateScale->getAxisPalette()->setForeground(dpy->getColor("purple"));

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
    ordinateScale->setStepLabelsVisible(IlTrue);

    _chart->addOrdinateScale(ordinateScale);
    _chart->getOrdinateInfo()->setUserDataRange(IlvCoordInterval(0.0, 30.0));

    IlUInt count;
    IlvChartDataSet* const* dataSets = xmlDataSet.getDataSets(count);
    _chart->getData()->setDataSets(count, dataSets);

    _chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[0]);
    _chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[1]);
    _chart->addDisplayer(new IlvPolylineChartDisplayer(), dataSets[2]);

    // Set different colors for the displayers.
    _chart->getDisplayer(0)->setForeground(dpy->getColor("red"));
    _chart->getDisplayer(0)->setLegendText("Legende Display. 1");
    _chart->getDisplayer(1)->setForeground(dpy->getColor("green"));
    _chart->getDisplayer(1)->setLegendText("Legende Display. 2");
    _chart->getDisplayer(2)->setForeground(dpy->getColor("blue"));
    _chart->getDisplayer(2)->setLegendText("Legende Display. 3");

    // Create the "load" button
    IlvGraphic* button =
	new IlvReliefLabel(dpy, IlvPoint(230, 30), "Load XML dataset");

    static const char* displayers[] = {
	"Line", "Bar", "HiLo", "HiLoBar", "HiLoOpenClose"
    };

    _combo = new IlvComboBox(dpy,
			     IlvPoint(465, 30),
			     "Displayer",
			     displayers,
			     5);
    _combo->setEditable(IlFalse);
    _combo->fitToContents();

    IlvButtonInteractor* buttonInteractor =
	new IlvButtonInteractor(IlvLeftButton, LoadXML, this);
    button->setInteractor(buttonInteractor);

    _combo->setCallback(SetDisplayerCB, this);

    // Add the chart to the container.
    addObject(_chart);
    addObject(button);
    addObject(_combo);

    // Attachement
    if (!IlvAttachmentsHandler::Get(this)) {
	IlvAttachmentsHandler::Set(this, new IlvAttachmentsHandler());
    }
    IlvSetAttachment(_chart, IlvLeft,		IlvFixedAttach,		15);
    IlvSetAttachment(_chart, IlvTop,		IlvFixedAttach,		25);
    IlvSetAttachment(_chart, IlvRight,		IlvFixedAttach,		15);
    IlvSetAttachment(_chart, IlvBottom,		IlvFixedAttach,		15);
    IlvSetAttachment(_chart, IlvHorizontal,	IlvElasticAttach,	 0);
    IlvSetAttachment(_chart, IlvVertical,	IlvElasticAttach,	 0);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void
DefinePageXml(Pan* mainPanel)
{
    Xml* panel = new Xml(mainPanel, "xml.ilv");
    mainPanel->addPageNoteBook(panel, "Xml", "xml.txt");
}
