// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/geotiff/src/alert.cpp
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
#include <alert.h>

#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/button.h>

// --------------------------------------------------------------------------
// An alert box made from an .ilv file produced with Rogue Wave Views Studio
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Construtor.
// Pass an IlvView as parameter so that the alert will be centered
// --------------------------------------------------------------------------
Alert::Alert(IlvView* view)
    : _view(view)
{
    _dialog = new IlvDialog(view->getDisplay(),
			    "Alert",
			    "Alert",
			    "alert.ilv",
			    IlvNoResizeBorder,
			    0,
			    view->getSystemView());
    IlvButton* ok = (IlvButton*)_dialog->getObject("apply");
    _dialog->setDefaultButton(ok);
}

// --------------------------------------------------------------------------
// Destructor, releases resources.
// --------------------------------------------------------------------------
Alert::~Alert()
{
    if (_dialog) {
	delete _dialog;
    }
}

// --------------------------------------------------------------------------
// Sets the alert message to be displayed.
// --------------------------------------------------------------------------
void
Alert::setMessage(const char* m)
{
    IlvMessageLabel* label = (IlvMessageLabel*)_dialog->getObject("message");
    label->setLabel(m);
}

// --------------------------------------------------------------------------
// Shows the alert box.
// --------------------------------------------------------------------------
void
Alert::show()
{
    _dialog->moveToView(_view);
    _dialog->showModal();
}
