// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/geotiff/src/tiler.cpp
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
#include <tiler.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/frame.h>
#include <stdlib.h>

// --------------------------------------------------------------------------
// Tiler
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// The tiler box.
// --------------------------------------------------------------------------
Tiler::Tiler(IlvView* view)
    : _view(view)
{
    _dialog = new IlvDialog(view->getDisplay(),
			    "Tiling Parameters",
			    "Tiling Parameters",
			    "tiling.ilv",
			    IlvNoResizeBorder,
			    0,
			    view->getSystemView());
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
Tiler::~Tiler()
{
    if (_dialog) {
	delete _dialog;
    }
}

// --------------------------------------------------------------------------
// Retrieves the tile width from the text field.
// --------------------------------------------------------------------------
IlInt
Tiler::getTileWidth()
{
    if (_dialog->wasCanceled()) {
	return 0;
    }
    IlvTextField* tf = (IlvTextField*)_dialog->getObject("tilewidth");
    const char* ret = tf->getLabel();
    if (*ret == 0) {
	return 0;
    }
    char* end;
    IlInt v = strtol(ret, &end, 10);
    return v;
}

// --------------------------------------------------------------------------
// Retrieves the tile height from the text field.
// --------------------------------------------------------------------------
IlInt
Tiler::getTileHeight()
{
    if (_dialog->wasCanceled()) {
	return 0;
    }
    IlvTextField* tf = (IlvTextField*)_dialog->getObject("tileheight");
    const char* ret = tf->getLabel();
    if (*ret == 0) {
	return 0;
    }
    char* end;
    IlInt v = strtol(ret, &end, 10);
    return v;
}

// --------------------------------------------------------------------------
// Retrieves the source file name from the text field.
// --------------------------------------------------------------------------
const char*
Tiler::getSourceFile()
{
    if (_dialog->wasCanceled()) {
	return 0;
    }
    IlvTextField* tf = (IlvTextField*)_dialog->getObject("sourcefile");
    const char* ret = tf->getLabel();
    if (*ret == 0) {
	return 0;
    }
    return ret;
}

// --------------------------------------------------------------------------
// Retrieves the target file name from the text field.
// --------------------------------------------------------------------------
const char*
Tiler::getTargetFile()
{
    if (_dialog->wasCanceled()) {
	return 0;
    }
    IlvTextField* tf = (IlvTextField*)_dialog->getObject("targetfile");
    const char* ret = tf->getLabel();
    if (*ret == 0) {
	return 0;
    }
    return ret;
}

// --------------------------------------------------------------------------
// Shoes the box.
// --------------------------------------------------------------------------
void
Tiler::show()
{
    _dialog->moveToView(_view);
    _dialog->showModal();
}
