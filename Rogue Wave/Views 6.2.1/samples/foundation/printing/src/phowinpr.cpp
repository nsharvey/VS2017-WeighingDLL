// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/printing/src/phowinpr.cpp
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
// This sample prints a bitmap on an A6 paper in landscape mode using an 
// IlvWindowsPrinter, a Windows print dialog box and a preview displayer
// --------------------------------------------------------------------------
#include <ilviews/ilv.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
static const char* title = "Printing sample for Windows: phowinpr";
// --------------------------------------------------------------------------

#if defined(WINDOWS)
#include <ilviews/bitmaps/bmp.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/printing/olayout.h>
#include <ilviews/printing/document.h>
#include <ilviews/printing/printables.h>
#include <ilviews/printing/wprinter.h>
#include <ilviews/windows/dump.h>
#include <ilviews/printing/previewdlg.h>
#include <ilviews/printing/prevdisplayer.h>

// --------------------------------------------------------------------------
static const char* BMPNAME = "rainbow.jpg";
static const char* LABEL = "Press to print on an A6 paper in landscape mode using a Windows printer dialog box and a print preview";

// --------------------------------------------------------------------------
// Exit the application
static void
Quit(IlvView* view, IlAny arg)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Print Callback
static void
Print(IlvGraphic* g, IlAny arg)
{   
    IlvDisplay* display = g->getDisplay();
    IlvBitmap* bitmap = (IlvBitmap*)arg;
        
    IlvPrintableLayoutOnePage* layout = new IlvPrintableLayoutOnePage();
    layout->lock();
    IlvPrintableDocument* document = new IlvPrintableDocument(layout);
    
    IlvZoomableIcon* icon = new IlvZoomableIcon(display, IlvPoint(), bitmap);
    IlvPrintableGraphic* printGraphic = new IlvPrintableGraphic(icon);
    printGraphic->lock();
    document->append(printGraphic);

    IlvWindowsPrinter* printer = new IlvWindowsPrinter(display);
    IlvWindowsPrinterDCDialogFactory factory;
    factory.setPaperSize(DMPAPER_A6, *display);    
    factory.setOrientation(DMORIENT_LANDSCAPE, *display);    
    printer->setPrinterDCFactory(&factory);
    
    printer->setDocumentName("Rainbow");

    IlvPrinterPreviewDialog dialog (display,
                    IlvContainer::GetContainer(g)->getSystemView(),
                    IlvPrinterPreviewDisplayer::OnePage);
    dialog.forceDialogDisplay(IlFalse);
    dialog.get(*printer, *document);

    delete printer; 
    delete document;
    printGraphic->unlock();
    layout->unlock();
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Create the display
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
    
    // Create the panel
    IlvGadgetContainer* cont =
        new IlvGadgetContainer(display,
			       title,
			       title,
			       IlvRect(10, 10, 620, 450));
   
    // Set the destroy callback to exit the application
    cont->setDestroyCallback(Quit);
    
    // Add a zoomable icon to the container
    IlvBitmap* bitmap = display->readBitmap(BMPNAME);
    IlvZoomableIcon* icon =
	new IlvZoomableIcon(display, IlvPoint(10, 10), bitmap);
    icon->resize(600, 400);
    cont->addObject(icon);
    
    // Add a button to the container
    IlvButton* button = 
        new IlvButton(display, LABEL, IlvRect(10, 415, 600, 25));
    cont->addObject(button);
    button->setCallback(Print, bitmap);

    // Show the container and run the event loop
    cont->show();
    IlvMainLoop();
    
    return 0;
}

#else /* !WINDOWS */
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Create the display
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (display->isBad()) {
        delete display;
        IlvFatalError("Couldn't create display");
        return -1;
    }
    
    IlvPrint("This sample is only supposed to run with Windows");
    
    delete display;
    return 0;
}
#endif /* !WINDOWS */
