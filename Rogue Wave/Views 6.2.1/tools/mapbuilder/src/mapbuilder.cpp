// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/mapbuilder.cpp
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
// The main program.
// --------------------------------------------------------------------------
#include "builder.h"

#if !defined(IL_DLL)
// Statically link look&feel classes
#  include <ilviews/win95.h>
#  include <ilviews/gadgets/notebook.h>
#endif

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
#  include <cstdlib>
IL_STDUSE
#else  /* !IL_STD */
#  include <iostream.h>
#  include <fstream.h>
#  include <stdlib.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

static MapBuilder* builder = 0;

// --------------------------------------------------------------------------
MapBuilder*
GetBuilder()
{
    return builder;
}

// --------------------------------------------------------------------------
int
main(int argc,char **argv)
{
#if defined(IL_MSVC_PORT)
    _putenv
#else
    putenv
#endif
	("ILVFILESELECTORNOCONFIRMATIONONOVERWRITING=true");
    IlvSetLocale();
    builder = new MapBuilder("Rogue Wave Views Map Builder", 0, argc, argv);
    if (!builder->getDisplay()) {
	return -1;
    }
    builder->run();

    return 0;
}
