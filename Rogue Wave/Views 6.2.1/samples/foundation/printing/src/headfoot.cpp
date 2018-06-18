// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/printing/src/headfoot.cpp
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
// This sample shows how to to print a chart on two pages, with header and 
// footer using an IlvPrintable instance.
// --------------------------------------------------------------------------

#include <ilviews/manager/manager.h>

#include <ilviews/printing/mgrprint.h>
#if defined (WINDOWS)
#  include <ilviews/printing/wprinter.h>
#else /* !WINDOWS */
#  include <ilviews/printing/psprinter.h>
#endif /* !WINDOWS */
#include <ilviews/printing/dialogs.h>
#include <ilviews/printing/document.h>
#include <ilviews/printing/mlayout.h>
#include <ilviews/printing/printables.h>
#include <ilviews/graphics/all.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
static const char* title = "Printing sample: headfoot";

// --------------------------------------------------------------------------
static IlvPrintableDocument*
CreateDocument(IlvDisplay* display)
{
    // Create the layout on two pages vertically
    IlvPrintableLayout* layout = new IlvPrintableLayoutMultiplePages(1, 2);

    // Create a new palette with the specified font
    IlvFont* font = display->getFont("%times-16-B");
    IlvPalette* palette = display->getPalette(0, 0, 0, 0, font);

    // Specify the height of the header and the footer
    IlvDim height = IL_CAST(IlvDim, IlvPrintCMUnit(4).getPoints());

    // Add the header to the layout
    layout->setHeaderAreaHeight(height);
    IlvPrintableText* text =
	new IlvPrintableText(palette, "Example of printing.");
    layout->setHeaderPrintable(text);

    // Add the footer to the layout
    layout->setFooterAreaHeight(height);
    text = new IlvPrintableFormattedText(palette, "Page %p/%P.");
    layout->setFooterPrintable(text);

    // Create the document from the layout
    return new IlvPrintableDocument(layout);
}


// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Create a display
    IlvSetLocale();
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (display->isBad()) {
        delete display;
        IlvFatalError("Couldn't create display");
        return -1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/printing/data");
    display->prependToPath(localPath);
    
    // Load graphic data in a manager
    IlvManager* manager = new IlvManager(display);
    manager->read("plane.ilv");
    
    IlUInt count;
    IlvGraphic* const* objs = manager->getObjects(count);
    for (IlUInt i = 0 ; i < count ; i++)
        objs[i]->translate(0, 1000);
        
    manager->read("plane2.ilv");

    // Create the document
    IlvPrintableDocument* document = CreateDocument(display);
	
    // Append the manager with the chart as an IlvPrintable
    IlvPrintable* printable = new IlvPrintableManager(manager);
    document->append(printable);

#if defined(WINDOWS)
    IlvWindowsPrinter printer(display);
    // This factory is used to create the dialog used for the settings of
    // the printer.
    IlvWindowsPrinterDCDialogFactory factory;
    printer.setPrinterDCFactory(&factory);
#else  /* !WINDOWS */
    IlvPSPrinter printer(display);
    printer.setDocumentName("headfoot.ps");
#endif /* WINDOWS */

    document->print(printer);

    return 0;
}
