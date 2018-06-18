// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/libdeps/src/dialog.cpp
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
// Definition of new dialog class: GraphLayoutDialog
// --------------------------------------------------------------------------

#include <dialog.h>

// --------------------------------------------------------------------------
static const char* FILENAME = "dialog.ilv";
static const char* titleS   = "title";

// --------------------------------------------------------------------------
GraphLayoutDialog::GraphLayoutDialog(IlvDisplay*    display,
				     const char*    name,
				     const char*    title,
				     IlvSystemView  transientFor)
: IlvDialog(display, name, title, display->findInPath(FILENAME),
	    IlvNoResizeBorder, 0, transientFor)
{
    IlvMessageLabel* msg = (IlvMessageLabel*)getObject(titleS);
    if (msg) {
	msg->setLabel(name);
	msg->fitToContents();
    }
    setLibName("");
    setFocus(getObject("TextField"));
    setDefaultButton((IlvButton*)getObject("apply"), IlTrue);
}

// --------------------------------------------------------------------------
IlBoolean
GraphLayoutDialog::get(IlBoolean grab)
{
    wait(grab);
    return getResult();
}

// --------------------------------------------------------------------------
IlBoolean
GraphLayoutDialog::getResult()
{
    return wasCanceled() ? IlFalse : IlTrue;
}

// --------------------------------------------------------------------------
const char*
GraphLayoutDialog::getLibName() const
{
    return ((IlvTextField*)getObject("TextField"))->getLabel();
}

// --------------------------------------------------------------------------
void
GraphLayoutDialog::setLibName(const char* lib)
{
    ((IlvTextField*)getObject("TextField"))->setLabel(lib);
}

// --------------------------------------------------------------------------
