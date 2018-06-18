// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/viewfile/step1/src/viewfile.cpp
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
// Implements the FileViewerApplication class
// This class uses the FileViewerWindow and FileViewer classes to display
// the file hierarchy of a hard drive.
// --------------------------------------------------------------------------

#include <viewfile.h>

// --------------------------------------------------------------------------
FileViewerApplication::FileViewerApplication(const char* name,
					     const char* displayName,
					     int argc,
					     char** argv)
: IlvApplication(name, displayName, argc, argv)
{
    // Do not use the default exit panel
    setUsingExitPanel(IlvFalse);
}

// --------------------------------------------------------------------------
FileViewerApplication::~FileViewerApplication()
{
}

// ------------------------------------------------------------------------
void
FileViewerApplication::makePanels()
{
    // Initialize the main window
    initMainWindow();
    // Show it
    getMainWindow()->show();
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initMainWindow() 
{
    // Create the main window
    IlvRect rect(0, 0, 500, 300);
    IlvContainer* mainWindow = createMainWindow(rect);
    // Name it to be able to retrieve it
    mainWindow->setName(getName());
    // Quit the application when user asks for termination
    mainWindow->setDestroyCallback(IlvAppExit, this);
    // Add the panel to the application
    addPanel(mainWindow);
}

// ------------------------------------------------------------------------
FileViewerWindow*
FileViewerApplication::getMainWindow() const
{
    return (FileViewerWindow*)getPanel(getName());
}

// ------------------------------------------------------------------------
IlvContainer* 
FileViewerApplication::createMainWindow(const IlvRect& rect) const
{
    return new FileViewerWindow(getDisplay(),
				getName(),
				getName(),
				rect,
				IlvFalse);
}

// ------------------------------------------------------
// Entry point
// ------------------------------------------------------
int main(int argc, char* argv[])
{
    IlvSetLocale();
    FileViewerApplication* appli =
	new FileViewerApplication("VIEWFILE Sample", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    appli->run();
    return 0;
}
