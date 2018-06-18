// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: studio/src/ivfstudio.cpp
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

#include <ivstudio/st2dlibini.h>

#include <ivstudio/graphicx.h>
#if defined(WINDOWS)
#include <ivstudio/windows/winext.h>
#endif
#if !defined(ILVNOSCRIPT)
#include <ivstudio/iscript/jsstudio.h>
#endif

#ifdef IL_STD
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    const char* rstr = "ILVFILESELECTORNOCONFIRMATIONONOVERWRITING=true";
#ifdef WINDOWS
    _putenv((char*) rstr);
#else
    putenv((char*) rstr);
#endif
    IlvSetLocale();
    // --- Display ---
    IlvDisplay* display = new IlvDisplay("ivstudio", "", argc, argv);
    if (display->isBad()) {
        IlvFatalError("Could not open display");
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

    // --- Extensions ---
    IlvStGraphicExtension::Make(editor);
#if defined(WINDOWS)
    IlvStWindowsExtension::Make(editor);
#endif
#if !defined(ILVNOSCRIPT)
    IlvStScriptExtension::Make(editor);
#endif
    editor->initialize();

    editor->parseArguments();
    editor->mainLoop();
    return 0;
}
