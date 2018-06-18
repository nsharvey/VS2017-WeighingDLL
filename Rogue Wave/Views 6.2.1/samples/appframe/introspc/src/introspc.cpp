// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/src/introspc.cpp
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
// IlogViews 4 generated source file
// File generated Wed Mar 29 15:01:36 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Include used for static initializations
#include <ilviews/appframe/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/gadgets.h>

// Main includes
#include <ilviews/base/message.h>
#include <ilviews/base/pathname.h>
#include "IntroDocument.h"
#include "IntroView.h"
#include "introcmd.h"
#include "execdlg.h"

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDvApplication* application =
		    new IlvDvApplication("introspc", 0, argc, argv);
    IlvDisplay* display = application->getDisplay();
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        delete display;
        return -1;
    }

    // Add the directory path to access the introspc sample data
    const char* home = display->getEnvOrResource("ILVHOME", 0);
    if (home && *home) {
      IlString strHome = home;
      strHome+= "/";
      IlPathName dataPath = strHome;
      dataPath.addDirectory("samples/appframe/introspc/data/");
      display->prependToPath((const char*)dataPath);
    }

    // Adding option file
    application->setAppOptionsFilename((const char*)"introspc.odv");

	// Adding data base file
    application->setDataBaseFilename((const char*)"introspc.dbm");
	
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
