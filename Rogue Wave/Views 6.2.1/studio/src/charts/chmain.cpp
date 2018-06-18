// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: studio/src/charts/chmain.cpp
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

#include <ivstudio/charts/stext.h>
#include <ivstudio/st2dlibini.h>
#include <ivstudio/iscript/jsstudio.h>
#include <ivstudio/graphicx.h>

extern "C" IlvBoolean IlvSetLanguage();

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLanguage();
    // --- Display ---
    IlvDisplay* display = new IlvDisplay("ivstudio", "", argc, argv);
    if (display->isBad()) {
        IlvFatalError("Couldn't open display");
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

    new IlvStGraphicExtension(editor);
    new IlvStScriptExtension(editor);
    new IlvStChartsExtension(editor);

    editor->options().setEditorShortName("chstudio");

    editor->initialize();
    editor->parseArguments();
    editor->mainLoop();
    return 0;
}
