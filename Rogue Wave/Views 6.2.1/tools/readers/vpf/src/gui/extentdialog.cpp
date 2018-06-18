// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/extentdialog.cpp
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
// Definition of the ExtentDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/extentdialog.h>
#include <vpf/extent.h>
#include <vpf/basictypes.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>

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
ExtentDialog::ExtentDialog(IlvDisplay* display,
			   const VpfExtent& extent)
: IlvDialog(display, "extent", "Set extent",
	    GetResourceFileName(display,"tools/readers/vpf/data/extent.ilv")),
  _extent(extent)
{
    ((IlvTextField*)getObject("lomin"))->
	setValue((float)_extent.getMinLongitude());
    ((IlvTextField*)getObject("lomax"))->
	setValue((float) _extent.getMaxLongitude());
    ((IlvTextField*)getObject("lamin"))->
	setValue((float) _extent.getMinLatitude());
    ((IlvTextField*)getObject("lamax"))->
	setValue((float) _extent.getMaxLatitude());
}

// --------------------------------------------------------------------------
ExtentDialog::~ExtentDialog()
{
}

// --------------------------------------------------------------------------
void
ExtentDialog::apply()
{
    VpfCoordinate c1(((IlvTextField*) getObject("lomin"))->getFloatValue(),
		     ((IlvTextField*) getObject("lamin"))->getFloatValue());
    VpfCoordinate c2(((IlvTextField*) getObject("lomax"))->getFloatValue(),
		     ((IlvTextField*) getObject("lamax"))->getFloatValue());
    _extent.set(c1, c2);
    IlvDialog::apply();
}
