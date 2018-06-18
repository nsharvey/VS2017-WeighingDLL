// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/resourcedialog.cpp
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
// Definition of the ResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/resourcedialog.h>
#include <vpf/string.h>
#include <string.h>
#include <stdio.h>
#include <ilviews/base/pathname.h>

static const char* GetResourceFileName(IlvDisplay* display,const char*name)
{
    static char path[2048];
    const char* home=display->getEnvOrResource("ILVMAPSHOME");
    sprintf(path,"%s/%s",home?home:".",name);
    if (IlvFileExists(path)) {
	return path;
    } else {
	home=display->getEnvOrResource("ILVHOME");
	sprintf(path,"%s/%s",home?home:".",name);
	if (IlvFileExists(path)) {
	    return path;
	}
    }
    return name;
}


// --------------------------------------------------------------------------
ResourceDialog::ResourceDialog(IlvDisplay* display,
			       const char* fileName,
			       const char* resourceName,
			       Palette* resourcePalette)
: IlvDialog(display, resourceName, "", GetResourceFileName(display,fileName)),
  _palette(resourcePalette)
{
    const char*	name = "Resource Editor";
    char*	buffer = new char[strlen(resourceName) + strlen(name) + 4];
    if (buffer) {
	strcpy(buffer, resourceName);
	strcat(buffer, " - ");
	strcat(buffer, name);
	setTitle(buffer);
	delete [] buffer;
    } else
	setTitle(name);
}

// --------------------------------------------------------------------------
ResourceDialog::~ResourceDialog()
{
}
