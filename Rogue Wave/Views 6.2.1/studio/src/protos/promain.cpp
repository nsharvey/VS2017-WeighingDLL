// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: studio/src/protos/promain.cpp
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
// Main module for Prototype Studio
// ---------------------------------------------------------------------------

#include <ivstudio/stlibini.h>
#include <ivstudio/defaultx.h>
#include <ivstudio/graphicx.h>
#include <ivstudio/grapher/grapher.h>
#include <ivstudio/jslib.h>
#include <ivstudio/protos/prlib.h>

#if 0
#include <ivstudio/protos/oldproto.h>
#endif

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale(); // Set locale according to environment variables (unix)

    IlvDisplay* display = new IlvDisplay("ivstudio", "", argc, argv);
    if (display->isBad()) {
        IlvFatalError("Couldn't open display");
        delete display;
	return 1;
    }
    
    IlvStudio* editor = new IlvStudio(display, argc, argv);
    if (editor->isBad()) {
	IlvFatalError("Can not initialize the editor");
	delete display;
	return 2;
    }
#if 1
    IlvStDefaultExtension::Make(editor);
#else
    IlvStGraphicExtension::Make(editor);
#ifdef WINDOWS
    IlvStWindowsExtension::Make(editor);
#endif
#endif
    if (!IlvStScriptExtension::Get(editor))
        new IlvStScriptExtension(editor);
    IlvStGrapherExtension::Make(editor);
    if (!IlvStPrototypeExtension::Get(editor))
    	new IlvStPrototypeExtension(editor);
#if 0    
    if (!IlvStPrototypeCompatExtension::Get(editor))
    	new IlvStPrototypeCompatExtension(editor);
#endif    
    editor->initialize();
    
    editor->parseArguments();
    editor->mainLoop();
    return 0;
}








