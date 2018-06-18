// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/windows/src/gdiplus.cpp
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

#include <ilog/pathname.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/jvscript/script.h>

static const char* Title = "GDI+ Sample";

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
CloseCB(IlvGraphic* graphic,
	IlAny)
{
    IlvContainer* cont = IlvContainer::GetContainer(graphic);
    Quit(cont, 0);
}

// **************************************************************************
// C++ Entry Point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay(Title, "", argc, argv);
    if (display->isBad()) {
	delete display;
	IlvFatalError("Couldn't create display");
	exit(-1);
    }
    // Add the sample directory to the display path
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/windows");
    display->prependToPath(localPath);

    IlvGadgetContainer* cont =
	new IlvGadgetContainer(display,
			       Title,
			       Title,
			       IlvRect(0, 0, 1, 1),
			       IlFalse,
			       IlFalse);
    cont->registerCallback("CloseCB", CloseCB);
    cont->readFile("data/guigdiplus.ilv");
    cont->moveToScreen(IlvCenter);
    cont->setDestroyCallback(Quit);

    cont->show();
    IlvMainLoop();
    return 0;
}
