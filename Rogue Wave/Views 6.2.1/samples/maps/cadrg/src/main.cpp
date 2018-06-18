// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/cadrg/src/main.cpp
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
// Main of CADRG viewer
// --------------------------------------------------------------------------
#include <viewer.h>

// --------------------------------------------------------------------------
// main : Opens a display and instantiate a CADRG viewer. Attemps to load a
// .toc file provided as argument, or attemps to load a cadrg/rpf/a.toc,
// which is the toc file present if a downloaded file is extracted in the
// executable directory (see readme file for details).
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay(argv[0], "", argc, argv);
    if (display -> isBad()) {
	IlvPrint("Cannot open display");
	delete display;
	exit(1);
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/cadrg/data");
    display->prependToPath(localPath);

    const char* tocname = "cadrg/rpf/a.toc";
    if (argc > 1) {
	tocname = argv[1];
    }
    Viewer vr(display, tocname);
    vr.show();

    IlvMainLoop();

    IlvExit(0);
    return 0;
}


