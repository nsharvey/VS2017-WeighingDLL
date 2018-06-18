// -------------------------------------------------------------- -*- C++ -*-
// File: main.cpp
// IlogViews 4 generated source file
// File generated Thu Jul 27 18:02:48 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Include used for static initializations
#include <ilviews/appframe/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/gadgets.h>

// Main includes
#include <ilviews/graphics/selector.h>
#include <ilviews/base/message.h>
#include <ilviews/base/pathname.h>
#include <BitmapDocument.h>
#include <BitmapView.h>


// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDvApplication* application =
		    new IlvDvApplication("BitmapEditor", 0, argc, argv);
    IlvDisplay* display = application->getDisplay();
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        delete display;
        return -1;
    }
    // Adding option file
    application->setAppOptionsFilename((const char*)"BitmapEditor.odv");

	// Adding data base file
    application->setDataBaseFilename((const char*)"BitmapEditor.dbm");
	
    // Initializes the application
    // Read option files and create panels
    application->initialize();

    // Insert here extra initialization code

    IlvDvDockableMainWindow* mainWindow =
                                application->getDockableMainWindow();
    if (mainWindow) {
        // Add here extra initialization code to the main window
        // For example, insert here panes to the window
    }
    
    // Now go on...
    application->run();
    return 0;
}

