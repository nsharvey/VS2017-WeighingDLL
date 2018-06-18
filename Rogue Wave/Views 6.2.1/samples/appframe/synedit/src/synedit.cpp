// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/synedit.cpp
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
// File generated Wed Mar 29 19:00:22 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Include used for static initializations
#include <ilviews/appframe/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/gadgets.h>
#include <ilviews/graphics/selector.h>

// Main includes
#include <ilviews/base/message.h>
#include <ilviews/base/pathname.h>
#include "TreeView.h"
#include "TextView.h"
#include "ProjectDocument.h"
#include "ProjectView.h"
#include "docsynt.h"
#include "synode.h"
#include "synparse.h"


// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDvApplication* application =
		    new IlvDvApplication("synedit", 0, argc, argv);
    IlvDisplay* display = application->getDisplay();
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        delete display;
        return -1;
    }

    // Add the directory path to access the synedit sample data
    const char* home = display->getEnvOrResource("ILVHOME", 0);
    if (home && *home) {
      IlString strHome = home;
      strHome+= "/";
      IlPathName dataPath = strHome;
      dataPath.addDirectory("samples/appframe/synedit/data/");
      display->prependToPath((const char*)dataPath);
    }

    // Adding option file
    application->setAppOptionsFilename((const char*)"synedit.odv");

	// Adding data base file
    application->setDataBaseFilename((const char*)"synedit.dbm");
	
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