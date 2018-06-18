// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/inspector/src/inspector.cpp
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
// Sample showing how to use the graph layout algorithms and the layout
// inspector of Rogue Wave Views
// --------------------------------------------------------------------------

#include <panel.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Layout", "", argc, argv);
    if (!display || display->isBad()) {
	if (display) {
	    delete display;
	}
	IlvFatalError("Cannot open display.");
	return -1;
    }
    IlPathName path = display->getHomePath();
    path.addDirectory("samples/layout/inspector");
    display->prependToPath(path.getDirectory());

    MainPanel* mainPanel = new MainPanel(display,
					 "Main Panel",
					 "Main Panel",
					 IlvRect(0, 0, 500, 500));
    mainPanel->show();
    if (argc > 1) {
	mainPanel->getGrapher()->read(argv[1]);
    }
    IlvMainLoop();
    return 0;
}
