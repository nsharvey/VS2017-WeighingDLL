// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step3/ActiveXGraphicAdapterApp.cpp
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
#include "ActiveXGraphicAdapterApp.h"

// --------------------------------------------------------------------------
Testapp::Testapp(const char*	appName,
                 const char*	displayName,
                 int		argc,
                 char**		argv)
: IlvApplication(appName, displayName, argc, argv)
{
}

// --------------------------------------------------------------------------
Testapp::Testapp(IlvDisplay* display, const char* appName)
: IlvApplication(display, appName)
{
}

// --------------------------------------------------------------------------
Testapp::~Testapp()
{
}

// --------------------------------------------------------------------------
void
Testapp::beforeRunning()
{
    IlvApplication::beforeRunning();
}

// --------------------------------------------------------------------------
void
Testapp::makePanels()
{
    // --- parameters ---
    IlvDisplay*   display = getDisplay();
    IlvRect       bbox(0, 0, 500, 500);
    // --- ActiveXGraphicAdapter ---
    IlvContainer* panel_1 =
	new ActiveXGraphicAdapter(display,
				  "ActiveXGraphicAdapter",
				  "ActiveXGraphicAdapter",
				  &bbox,
				  IlvFalse,
				  IlvFalse,
				  0,
				  0);
    addPanel(panel_1);
    panel_1->setDestroyCallback(IlvAppExit, this);
    panel_1->show();
    // --- The Exit panel is not wanted ---
    setUsingExitPanel(IlvFalse);
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
extern "C" IlvBoolean IlvSetLanguage();
// extern "C" unsigned long IlvSetCurrentCharSet(unsigned long);

int
main(int argc, char* argv[])
{
    // IlvSetCurrentCharSet(<YourCharSet>);
    IlvSetLanguage();
    Testapp* appli = new Testapp("ActiveXGraphicAdapterApp", 0, argc, argv);
    if (!appli->getDisplay()) {
	delete appli;
        return 1;
    }
    appli->run();
    return 0;
}
