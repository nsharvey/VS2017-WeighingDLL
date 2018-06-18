// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/geotiff/src/filesel.cpp
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
#include <filesel.h>

// --------------------------------------------------------------------------
// FileSelector
// --------------------------------------------------------------------------
FileSelector::FileSelector(IlvView* view)
    : _view(view)
{
    const char* const filters[1] = { "*.tif" };
    const char* const messages[1] = { "*.tif, Tiff file" };

    _dialog = new IlvFileBrowser (view->getDisplay(),view->getSystemView(),
				  "./",1,filters,messages);
}

// --------------------------------------------------------------------------
// Destructor, releases resources.
// --------------------------------------------------------------------------
FileSelector::~FileSelector()
{
    if (_dialog) {
	delete _dialog;
    }
}

// --------------------------------------------------------------------------
// Retrieves the string contained in the test field.
// --------------------------------------------------------------------------
const char*
FileSelector::getString()
{
    if (_filename.getLength() < 5) {
	return 0;
    }
    return (const char*)_filename;
}

// --------------------------------------------------------------------------
// Shows the file selector
// --------------------------------------------------------------------------
void
FileSelector::show()
{
    _filename = _dialog->get();
}
