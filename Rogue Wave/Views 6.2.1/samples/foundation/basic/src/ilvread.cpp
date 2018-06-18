// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/basic/src/ilvread.cpp
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
// Reading an IlogViews file in a container
// --------------------------------------------------------------------------
#if !defined(IL_DLL)
#  include <ilviews/graphics/all.h>
#endif
#include <ilviews/contain/contain.h>

static const char* title = "Rogue Wave Views sample: ilvread";
static const char* DefaultFileName = "elefante.ilv";

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    const char* filename = (argc > 1) ? argv[1] : DefaultFileName;
    IlvDisplay* display = new IlvDisplay("IlvRead", "", argc, argv);
    if (!display || display->isBad()) {
	if (display) delete display;
	IlvFatalError("Can't open display...");
	return 1;
    }
    IlvContainer* container = new IlvContainer(display, title, title,
					       IlvRect(0, 0, 600, 600),
					       IlTrue, IlFalse);
    container->setDestroyCallback(Quit);
    container->readFile(filename);
    container->fitToContents();
    container->show();
    IlvMainLoop();
    return 0;
}
