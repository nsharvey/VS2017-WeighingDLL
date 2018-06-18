// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/dbgraphe/src/main.cpp
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// File: samples/dataccess/dbgraphe/src/main.cpp
// IlogViews 2.21 generated application source file
// File generated: Mon Sep  2 11:27:25 1996
// --------------------------------------------------------------------------

#include <app.h>
#include <string.h>
#include <ilviews/dataccess/home.h>
#include <ilviews/dataccess/format.h>
#include <ilviews/dataccess/gcallbak.h>

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
extern "C" IlvBoolean IlvSetLanguage();
// extern "C" unsigned long IlvSetCurrentCharSet(unsigned long);

int
main(int argc, char* argv[])
{
    // IlvSetCurrentCharSet(<YourCharSet>);
    IlvSetLanguage();
    NoDbApp* appli = new NoDbApp("noDbApp", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    IlPathName localPath(appli->getDisplay()->getHomePath());
    localPath.addDirectory("samples/dataccess/dbgraphe/data"); 
    appli->getDisplay()->prependToPath(localPath);
    appli->run();
    return 0;
}
