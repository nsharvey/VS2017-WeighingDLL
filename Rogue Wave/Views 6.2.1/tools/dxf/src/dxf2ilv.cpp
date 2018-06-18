// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/src/dxf2ilv.cpp
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
// Converting Dxf files to Rogue Wave Views format
// --------------------------------------------------------------------------
#include <dxfincl/dxread.h>
#include <ilviews/base/iostream.h>
#include <ilviews/manager/manager.h>
#include <ilviews/manager/io.h>
#if defined(ILVSTD)
#include <fstream>
#include <cstring>
#include <cstdlib>
ILVSTDUSE
#else
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#endif

// #define INTERACTIVE

#if defined(INTERACTIVE)
#include <ilviews/gadgets/filesel.h>
#endif /* INTERACTIVE */

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("DXF", "", argc, argv);
    if(!display || display->isBad()) {
	IlvFatalError("Couldn't initialise IlvDisplay.");
	delete display;
	return 1;
    }
    char* filein,
	* fileout;
    if(argc < 3) {
#if defined(INTERACTIVE)
#define ILVFILEDIR "../data"
#define DXFFILEDIR "../data"
	const char *file;
	if (argc < 2) {
	    IlvIFileSelector* selector =
		new IlvIFileSelector(display, DXFFILEDIR, "*.dxf");
	    file = selector->get();
	    if (!file) {
		IlvFatalError("No file selected.");
		delete display;
		return 1;
	    }
	    filein = new char[strlen(file)+1];
	    (void)strcpy(filein, file);
	}
	else filein = argv[1];
	IlvIFileSelector* selector =
	    new IlvIFileSelector(display, ILVFILEDIR, "*.ilv");
	file = selector->get(IlTrue);
	if (!file) {
	    IlvFatalError("No file selected.");
	    if (argc < 2)
		delete filein;
	    delete display;
	    return 1;
	}
	fileout = new char[strlen(file)+1];
	(void)strcpy(fileout, file);
#else  /* !INTERACTIVE */
	IlvFatalError("Usage %s <in.dxf> <out.ilv> [precision default:500000]",
		      argv[0]);
	delete display;
	return 1;
#endif /* INTERACTIVE */
    } else {
    	filein  = argv[1];
    	fileout = argv[2];
    }
    ifstream stream(filein);
    if(!stream) {
#if defined(INTERACTIVE)
	if (argc < 3) {
	    if (argc < 2)
		delete filein;
	    delete fileout;
	}
#endif /* !INTERACTIVE */
	IlvFatalError("Bad file %s.",filein);
	delete display;
	return 1;
    }
    ofstream outstream(fileout, IlBinaryOutputStreamMode);
    if (!outstream) {
#if defined(INTERACTIVE)
	if (argc < 3) {
	    if (argc < 2)
		delete filein;
	    delete fileout;
	}
#endif /* !INTERACTIVE */
	IlvFatalError("Couldn't open file '%s' for writing.", fileout);
	delete display;
	return 1;
    }
    IlvDim maxDim = 1000;
    if (argc > 3)
	maxDim = (IlvDim)atoi(argv[3]);
    if ((maxDim < 1) || (maxDim > 100000))
	maxDim = 100000;
    IlvDXFInput dxfinput(stream);
    if (dxfinput.isBad()) {
	IlvFatalError("Noting do be saved...");
	delete display;
	IlvExit(0);
    }
    dxfinput.setViewsExtents(IlvRect(0, 0, maxDim, maxDim));
    IlUInt count = 0;
    IlvGraphic** graphics = dxfinput.readObjects(count, *display);
    IlvPrint("%ld objects created", count);
    if(!count) {
#if defined(INTERACTIVE)
	if (argc < 3) {
	    if (argc < 2)
		delete filein;
	    delete fileout;
	}
#endif /* INTERACTIVE */
	delete display;
	return 1;
    }
    IlvManager* manager = new IlvManager(display);
    for (IlUInt i = 0; i < count; i++)
	manager->addObject(graphics[i], IlFalse);
    if (manager->getCardinal()) {
	manager->save(outstream);
	IlvPrint("Done.");
    }
#if defined(INTERACTIVE)
    if (argc < 3) {
    	if (argc < 2)
	    delete filein;
	delete fileout;
    }
#endif /* INTERACTIVE */
    delete manager;
    delete display;
    IlvExit(0);
    return 0;
}
