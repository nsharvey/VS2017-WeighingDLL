// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/lookfeel/src/lookfeel.cpp
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
// Sample that shows how to use the dynamic loading of look and feel
// handlers.
// Note : This sample only works with shared libraries
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/menubar.h>
#include <ilog/pool.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
static void
QuitCB(IlvGraphic* g,
       IlAny)
{
    delete ((IlvButton*)g)->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
ChangeLookCB(IlvGraphic* g,
	     IlAny)
{
    IlvComboBox* combo = (IlvComboBox*)g;
    const char* lookSelected = combo->getSelection();
    IlvLookFeelHandler* lfh =
	combo->getDisplay()->getLookFeelHandler(IlGetSymbol(lookSelected));
    IlvContainer* container = IlvContainer::GetContainer(g);
    IlvGadgetContainerRectangle* rectangle =
	(IlvGadgetContainerRectangle*)container->getObject("Rectangle");
    if (rectangle && rectangle->getGadgetContainer())
	rectangle->getGadgetContainer()->setLookFeelHandler(lfh);
}
    
// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("LookFeel", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open display...");
	if (display)
	    delete display;
	return 1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/gadgets/lookfeel/data");
    display->prependToPath(localPath);
    

    // Create the main window
    const char* title = "Look and Feel sample"; 
    IlvGadgetContainer* container =
	new IlvGadgetContainer(display,
			       title,
			       title,
			       IlvRect(0, 0, 100, 100),
			       IlFalse,
			       IlFalse);
    // Connect a destroy callback
    container->setDestroyCallback(Quit);

    // Read the data file 
    container->readFile("lookfeel.ilv");
    container->setMinimumSize(container->width(), container->height());
    container->moveToScreen(IlvCenter);

    // Register callbacks
    container->registerCallback("ComboCB", ChangeLookCB);
    container->registerCallback("QuitCB", QuitCB);

    // Fill the combo box with availables looks
    IlvComboBox* combo = (IlvComboBox*)container->getObject("Combo");
    if (!combo) {
	IlvFatalError("Bad resource file !");
	delete display;
	IlvExit(0);
    }

    // Default Button
    IlvButton* button = (IlvButton*)container->getObject("Close");
    if (button)
	container->setDefaultButton(button);
    IlvGadgetContainerRectangle* rectangle =
	(IlvGadgetContainerRectangle*)container->getObject("Rectangle");
    IlvGadgetContainer* gadcont = rectangle->getGadgetContainer();
    gadcont->setDefaultButton(button);

    IlUInt count;
    const IlSymbol* const* looks =
	IlvLookFeelHandler::GetAvailableLooks(count);
    if (count) {
	IlPoolOf(Pointer)::Lock((IlAny*)looks);
	for (IlUShort i = 0; i < count; ++i)
	    combo->addLabel(*looks[i]);
	IlPoolOf(Pointer)::UnLock((IlAny*)looks);
    }
    // Show the main window
    container->show();

    IlvMainLoop();
    return 0;
}
