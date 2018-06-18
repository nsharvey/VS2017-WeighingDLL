// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/multires/src/filesel.cpp
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
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>

// --------------------------------------------------------------------------
FileSelector::FileSelector(IlvView* view)
  : _view(view)
{
    _dialog = new IlvDialog(view->getDisplay(),
			    "Choose a Multires Directory",
			    "Choose a Multires Directory",
			    "filesel.ilv",
			    IlvNoResizeBorder,
			    0,
			    view->getSystemView());
    IlvButton* ok = (IlvButton*)_dialog->getObject("apply");
    _dialog->setDefaultButton(ok);
}

// --------------------------------------------------------------------------
FileSelector::~FileSelector()
{
    if (_dialog) {
	delete _dialog;
    }
}

// --------------------------------------------------------------------------
const char*
FileSelector::getString()
{
    if (_dialog->wasCanceled()) {
	return 0;
    }
    IlvTextField* tf = (IlvTextField*)_dialog->getObject("filename");
    const char* ret = tf->getLabel();
    if (*ret == 0) {
	return 0;
    }
    return ret;
}

// --------------------------------------------------------------------------
void
FileSelector::show()
{
    _dialog->moveToView(_view);
    _dialog->showModal();
}
