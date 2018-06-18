// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/src/scrolling.cpp
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
// Main program
// --------------------------------------------------------------------------

#include <app.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    IlvDisplay* display = new IlvDisplay("ScrollingApp", "", argc, argv);
    if (display->isBad()) {
	IlvFatalError("Could not create display");
	delete display;
	return -1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/charts/scrolling/data");
    display->prependToPath(localPath);

    const char* title = "Rogue Wave Views sample: scrolling charts";
    Pan* panel = new Pan(display, title, title, IlvRect(0, 0, 610, 510));
    panel->initializeSamples();
    panel->show();

    IlvMainLoop();
    return 0;
}
