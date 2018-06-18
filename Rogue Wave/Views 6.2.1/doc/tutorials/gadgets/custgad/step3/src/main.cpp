// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/custgad/step3/src/main.cpp
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
// Creating an UpdownField instance.
// --------------------------------------------------------------------------

#include <updown.h>
#include <ilviews/gadgets/idialog.h>

#if defined(ILVSTD)
ILVSTDUSE
#include <cstdlib>
#include <cstdio>
#else
#include <stdlib.h>
#include <stdio.h>
#endif

// --------------------------------------------------------------------------
static void
Increment(IlvGraphic* g, IlvAny)
{
    char buffer[1000];
    UpDownField * obj = (UpDownField*)g;
    const char* label = obj->getLabel();
    if (label && *label) {
        IlvInt value = ((IlvInt)atof(label))+1;
        sprintf(buffer, "%ld", value);
        obj->setLabel(buffer, IlvTrue);
    } else
        obj->setLabel("0", IlvTrue);
}

// --------------------------------------------------------------------------
static void
Decrement(IlvGraphic* g, IlvAny)
{
    char buffer[1000];
    UpDownField * obj = (UpDownField*)g;
    const char* label = obj->getLabel();
    if (label && *label) {
        IlvInt value = ((IlvInt)atof(label))-1;
        sprintf(buffer, "%ld", value);
        obj->setLabel(buffer, IlvTrue);
    } else
        obj->setLabel("0", IlvTrue);
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlvAny)
{
   IlvDisplay* display = top->getDisplay();
   delete top;
   delete display;
   IlvExit(0);
}

// **************************************************************************
// Entry Point
// **************************************************************************

static const char title[] = "Spin sample program";

int
main(int argc , char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Spin", "", argc, argv);
    if (display->isBad()) {
        delete display;
        IlvFatalError("Couldn't create display");
        exit(-1);
    }
    
    // Create the container
    IlvDialog* dialog = new IlvDialog(display,
				      title,
				      title,
                                      IlvRect(0, 0, 100, 100));
    dialog->setDestroyCallback(Quit);

    // Create the UpDownField instance
    UpDownField* but = new UpDownField(display, IlvRect(5, 5, 100, 23) , "0");

    // Add it to the container
    dialog->addObject(but);
    
    // Set up the UpDownField callbacks
    but->setUpCallback(Increment);
    but->setDownCallback(Decrement);

    dialog->fitToContents();
    dialog->resize(dialog->width()+10, dialog->height()+10);
    dialog->showModal();
    return 0;
}
