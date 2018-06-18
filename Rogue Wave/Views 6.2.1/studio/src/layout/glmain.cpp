// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: studio/src/layout/glmain.cpp
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

#include <ivstudio/stlibini.h>
#include <ivstudio/defaultx.h>
#include <ivstudio/grapher/grapher.h>
#include <ilviews/grapher/polylink.h>
#include <ilviews/gadgets/notebook.h>
#include <ivstudio/inspectors/genedt.h>
#include <ivstudio/inspectors/insppnl.h>
#include <ivstudio/layout/extension.h>
#include <ilviews/layout/graphmod.h>
#include <ilviews/layout/gphadapt.h>
#include <ilviews/layout/gphlayout.h>
#include <ilviews/layout/orthlink/lnkshaptyp.h>
#include <ilviews/layout/orthlink/lnkshaprod.h>
#include <ilviews/layout/bus.h>
#include <ivstudio/layout/bus/busitf.h>
#include <ilviews/layout/tree.h>
#include <ivstudio/layout/tree/treeitf.h>
#include <ilviews/layout/random.h>
#include <ivstudio/layout/random/randomitf.h>
#include <ilviews/layout/hierarchical.h>
#include <ivstudio/layout/hierarchical/hieritf.h>
#include <ilviews/layout/orthlink.h>
#include <ivstudio/layout/orthlink/orthoitf.h>

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    IlvDisplay* display = new IlvDisplay("layout", "", argc, argv);
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

    new IlvStDefaultExtension(editor);
    IlvStGrapherExtension::Make(editor);
    IlvStLayoutExtension* ext = new IlvStLayoutExtension(editor);
    IlvLayoutInspectorInterface* itf;
    IlvGraphLayout* layout;

    layout = new IlvTreeLayout();
    itf = new IlvTreeLayoutInterface(layout);
    ext->registerLayoutInterface("Tree Layout", itf);

    layout = new IlvRandomLayout();
    itf = new IlvRandomLayoutInterface(layout);
    ext->registerLayoutInterface("Random Layout", itf);

    layout = new IlvBusLayout();
    itf = new IlvBusLayoutInterface(layout);
    ext->registerLayoutInterface("Bus Layout", itf);

    layout = new IlvHierarchicalLayout();
    itf = new IlvHierarchicalLayoutInterface(layout);
    ext->registerLayoutInterface("Hierarchical Layout", itf);

    layout = new IlvOrthogonalLinkLayout();
    itf = new IlvOrthogonalLayoutInterface(layout);
    ext->registerLayoutInterface("Orthogonal Layout", itf);

    editor->initialize();

    editor->parseArguments();
    editor->mainLoop();
    return 0;
}
