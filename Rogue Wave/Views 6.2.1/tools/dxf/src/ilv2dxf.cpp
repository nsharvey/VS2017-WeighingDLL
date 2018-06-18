// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/src/ilv2dxf.cpp
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
// Converting Rogue Wave Views files to DXF format
// --------------------------------------------------------------------------
#include <dxfincl/dxwrite.h>
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
#include <ilviews/gadgets/fbrowser.h>

static const char* ViewsFilesString = "Rogue Wave Views Files (*.ilv)";
static const char* ViewsTypeString = "*.ilv";
static const char* DXFFilesString = "DXF Files (*.dxf)";
static const char* DXFTypeString = "*.dxf";
#endif /* INTERACTIVE */

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("ILV2DXF", "", argc, argv);
    if (display->isBad()) {
	IlvFatalError("Couldn't initialise IlvDisplay.");
	delete display;
	return 1;
    }
    char *filein;
    char *fileout;
    if(argc < 3) {
#if defined(INTERACTIVE)
#define ILVFILEDIR "../data"
#define DXFFILEDIR "../data"
	const char* file;
	const char* types[2];
	const char* messages[2];
	types[1]    = "*.*";
	messages[1] = "All Files (*.*)";
	if (argc < 2) {
	    types[0]    = ViewsTypeString;
	    messages[0] = ViewsFilesString;
	    IlvFileBrowser* selector = new IlvFileBrowser(display,
							  0,
							  ILVFILEDIR,
							  2,
							  types,
							  messages);
	    selector->setTitle("Load a Rogue Wave Views file");
	    selector->setType(IlvFileSelectorLoad);
	    file = selector->get();
	    if (!file) {
		delete selector;
		delete display;
		IlvExit(0);
	    }
	    filein = strdup(file);
	    delete selector;
	}
	else filein = argv[1];
	types[0]    = DXFTypeString;
	messages[0] = DXFFilesString;
	IlvFileBrowser* selector = new IlvFileBrowser(display,
						      0,
						      DXFFILEDIR,
						      2,
						      types,
						      messages);
	selector->setTitle("Save a DXF file");
	selector->setType(IlvFileSelectorSave);
	file = selector->get();
	if (!file) {
	    if (argc < 2)
		(void)free(filein);
	    delete selector;
	    delete display;
	    IlvExit(0);
	}
	fileout = strdup(file);
	delete selector;
#else  /* !INTERACTIVE */
	IlvFatalError("Usage %s <in.ilv> <out.dxf>.", argv[0]);
	delete display;
	IlvExit(0);
#endif /* INTERACTIVE */
    } else {
    	filein  = argv[1];
	fileout = argv[2];
    }
    ifstream stream(filein);
    if (!stream) {
#if defined(INTERACTIVE)
	if (argc < 3) {
	    if (argc < 2)
		(void)free(filein);
	    (void)free(fileout);
	}
#endif /* INTERACTIVE */
	IlvFatalError("Couldn't open %s for reading.", filein);
	delete display;
	IlvExit(1);
    }
    ofstream outstream(fileout, IlBinaryOutputStreamMode);
    if (!outstream) {
#if defined(INTERACTIVE)
	if (argc < 3) {
	    if (argc < 2)
		(void)free(filein);
	    (void)free(fileout);
	}
#endif /* INTERACTIVE */
	IlvFatalError("Couldn't open '%s' for writing.", fileout);
	delete display;
	IlvExit(1);
    }
    IlvManager* manager = new IlvManager(display);
    manager->read(stream);
    IlvDXFOutput dxfout(outstream);
    dxfout.save(manager);
    delete manager;
#if defined(INTERACTIVE)
    if (argc < 3) {
    	if (argc < 2)
	    (void)free(filein);
	(void)free(fileout);
    }
#endif /* INTERACTIVE */
    IlvWarning("Done.\n");
    delete display;
    IlvExit(0);
    return 0; // Dummy statement
}
