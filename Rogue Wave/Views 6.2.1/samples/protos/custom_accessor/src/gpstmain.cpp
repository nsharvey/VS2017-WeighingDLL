// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/custom_accessor/src/gpstmain.cpp
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

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// 		Main module for Prototype Studio
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#include <ivstudio/stlibini.h>
#include <ivstudio/defaultx.h>
#include <ivstudio/jslib.h>
#include <ivstudio/protos/prlib.h>
#include <ivstudio/libini.h>
#include <gpacc.h>

// ---------------------------------------------------------------------------
// Entry point
// ---------------------------------------------------------------------------

extern "C" IlvBoolean IlvSetLanguage();

int
main(int argc,
     char* argv[])
{
    IlvSetLanguage(); // set locale according to environment variables (unix)
    // --- Display ---
    IlvDisplay* display = new IlvDisplay("ivstudio", "", argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't open display");
	if (display)
	    delete display;
	return 1;
    }

    // --- Let's go ---
    IlvStudio* editor = new IlvStudio(display, argc, argv);
    if (editor->isBad()) {
	IlvFatalError("Can not initialize the editor");
	delete display;
	return 1;
    }

    display->appendToPath("..");

   IlvStDefaultExtension::Make(editor);

    if (!IlvStScriptExtension::Get(editor))
        new IlvStScriptExtension(editor);
    IlvStGrapherExtension::Make(editor);
    if (!IlvStPrototypeExtension::Get(editor))
        new IlvStPrototypeExtension(editor);

    editor->initialize();
    editor->parseArguments();
#if 0
    IlvProtoLibrary* pLib = new IlvProtoLibrary (display, "grpath");
    IlString buf (getenv("ILVHOME"));
    buf += "/samples/protos/custom_accessor/data/grpath.ipl";
    ifstream vStream ( buf ); 
    pLib->load ( & vStream ); 
#endif
    editor->mainLoop();
    return 0;
}
