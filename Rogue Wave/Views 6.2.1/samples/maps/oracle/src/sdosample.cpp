// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/src/sdosample.cpp
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
//
// --------------------------------------------------------------------------
#include <mysdopan.h>
#include <sdopan.h>
#include <ilog/pathname.h>


// --------------------------------------------------------------------------
// Callback function
// --------------------------------------------------------------------------
static void
DestroyCB(IlvView* v, IlvAny)
{
    IlvDisplay* d = v->getDisplay();
    delete v;
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main( int argc, char **argv)
{
    IlvDisplay* display = new IlvDisplay("test", "");
    if(display->isBad()) {
        IlvPrint("Can't open display");
        delete display;
        IlvExit(1);
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/oracle/data");
    display->prependToPath(localPath);
    display->prependToPath("../data");


    MySdopan* sdopan = new MySdopan(display,"Oracle SDO Sample",
				    "Oracle SDO Sample",
                                    new IlvRect(0,0,500,500));

    sdopan->setDestroyCallback(DestroyCB);
    sdopan->show();

    IlvMainLoop();
    return 0;
}
