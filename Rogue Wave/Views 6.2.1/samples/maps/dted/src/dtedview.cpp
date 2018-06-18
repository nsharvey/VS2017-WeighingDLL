// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/dted/src/dtedview.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Main of DTED viewer.
// --------------------------------------------------------------------------
#include <dtedlod.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
// Main : Opens a display, creates an instance of DTED loader.
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay(argv[0], "", argc, argv);
    if (display -> isBad()) {
	IlvPrint("Can't open display");
	delete display;
	IlvExit(1);
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/dted/data");
    display->prependToPath(localPath);

    char* dirname;
    if (argc > 1) {
	dirname = argv[1];
    }
    else {
	dirname = (char*)display->findInPath("n45.dt1");
    }

    DtedLod d(display, dirname);
    d.show();

    IlvMainLoop();

    exit(0);
}
