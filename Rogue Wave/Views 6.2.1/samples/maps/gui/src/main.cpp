// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/gui/src/main.cpp
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
// Main of graphical user interface component viewer.
// --------------------------------------------------------------------------
#include <guic.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* d = new IlvDisplay(argv[0], "", argc, argv);
    if (d -> isBad()) {
	IlvPrint("Can't open display");
	delete d;
	exit(1);
    }
    IlPathName localPath(d->getHomePath());
    localPath.addDirectory("samples/maps/gui/data");
    d->prependToPath(localPath);

    char* file;
    if (argc > 1) {
	file = argv[1];
    }
    else {
	file = (char*)"world.ilv";
    }
    Guic t(d, file);
    t.show();

    IlvMainLoop();

    return 0;
}
