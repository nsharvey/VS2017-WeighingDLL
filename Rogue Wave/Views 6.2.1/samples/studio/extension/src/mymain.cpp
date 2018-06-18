// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/mymain.cpp
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
//  Definition of the application main function
// --------------------------------------------------------------------------

#include <ivstudio/lib.h>
#include <myext.h>

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvSetLanguage();
    // --- Display ---
    IlvDisplay* display = new IlvDisplay("ivstudio", "", argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't open display");
	if (display)
	    delete display;
	return 1;
    }

    // ---- Create and initialize the editor ---
    IlvStudio* editor = new IlvStudio(display, argc, argv);
    if (editor->isBad()) {
	IlvFatalError("Could not initialize the editor");
	delete display;
	return 2;
    }

    MyStudioExtension::Make(editor);

    editor->initialize();
    editor->parseArguments();
    editor->mainLoop();
    return 0;
}