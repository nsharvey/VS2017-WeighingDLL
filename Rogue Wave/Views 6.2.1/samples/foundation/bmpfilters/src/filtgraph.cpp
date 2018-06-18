// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bmpfilters/src/filtgraph.cpp
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
// Using IlvFilteredGraphic. 
// --------------------------------------------------------------------------

#include <filtgraph.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Panel class for sample Emboss
// --------------------------------------------------------------------------
Filters::Filters(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename) 
{
    initFilters();
}

// --------------------------------------------------------------------------
Filters::~Filters()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Filters::initFilters()
{
    IlvDisplay* display = getDisplay();

    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/bmpfilters/data");
    display->prependToPath(localPath);

    // Load a background image
    IlvBitmap* background = display->readBitmap("greenstone.png");
    IlvDim width = background->width();
    IlvDim height = background->height();

    IlvFont* font = display->getFont("%Helvetica-120-"); // 120!
    IlFloat scale = 1.0;

    // Create a zoomable label to start with
    IlvZoomableLabel* org =
	new IlvZoomableLabel(display, IlvPoint(50, 100), "Views");
    // Initialize some graphic properties
    org->setForeground(display->getColor("white"));
    org->setFont(font);
    org->scale(scale, scale);    

    // Create another zoomable label
    IlvZoomableLabel* glowsource =
	new IlvZoomableLabel(display, IlvPoint(470, 100), "Views");
    glowsource->setForeground(display->getColor("white"));
    glowsource->setFont(font);
    glowsource->scale(scale, scale);
    // Apply a glow effect to it
    IlvFilteredGraphic* glow  =
	new IlvFilteredGraphic(display, glowsource, "glow.xml", IlTrue);

    // Create yet another zoomable label
    IlvZoomableLabel* embosssource =
	new IlvZoomableLabel(display, IlvPoint(470, 100), "Views");
    embosssource->setForeground(display->getColor((IlvIntensity)( 5 << 8),
						  (IlvIntensity)( 5 << 8), 
						  (IlvIntensity)( 56 << 8)));
    embosssource->setFont(font);
    embosssource->scale(scale, scale);
    // Apply an emboss effect to it
    IlvFilteredGraphic* emboss =
	new IlvFilteredGraphic(display, embosssource, "emboss.xml", IlTrue);

    // Group those two filtered graphics
    IlvGraphicSet* gset = new IlvGraphicSet(2, glow, emboss);

    addObject(new IlvIcon(display, IlvPoint(10, 25), background));
    addObject(org);

    addObject(new IlvIcon(display, IlvPoint(30 + width, 25), background));
    addObject(gset);

    resize(width * 2 + 60, height + 20);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
CreateFiltersPage(Pan* mainPanel)
{
    Filters* panel = new Filters(mainPanel, "emboss.ilv");
    mainPanel->addPageNoteBook(panel, "Filter graphic", "filters.txt");
}
