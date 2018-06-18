// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/xlib/src/ilvmotif.cpp
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
// Using the grapher in a Motif widget
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>
#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------------------------
// Integration Part with Motif
// --------------------------------------------------------------------------

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>
#include <X11/Shell.h>
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <Xm/PushB.h>

// --------------------------------------------------------------------------
static void
Quit(Widget,
     XtPointer display,
     XtPointer)
{
    delete (IlvDisplay*)display;
    exit(0);
}

#define INPUT_MASK (unsigned long)(ButtonPressMask | ButtonReleaseMask |\
				   KeyPressMask | KeyReleaseMask |\
				   ButtonMotionMask | EnterWindowMask |\
				   LeaveWindowMask | PointerMotionMask | \
				   ExposureMask | StructureNotifyMask)

extern "C" void IlvDispatchEvent(XEvent* xevent);

// --------------------------------------------------------------------------
static void
ManageInput(Widget,
	    XtPointer,
	    XEvent* xevent,
	    Boolean*)
{
    IlvDispatchEvent(xevent);
}

// --------------------------------------------------------------------------
IlvDisplay*
IlvGetDisplay(Display* xdisplay)
{
    static IlvDisplay* ilv_display = 0;
    if (!ilv_display)
	ilv_display = new IlvDisplay(xdisplay, "IlvMotif");
    return ilv_display;
}

// --------------------------------------------------------------------------
IlvContainer*
CreateContainer(Widget widget)
{
    IlvContainer* c = new IlvContainer(IlvGetDisplay(XtDisplay(widget)),
				       (IlvSystemView)XtWindow(widget));
    XtAddEventHandler(widget, INPUT_MASK, False,
		      ManageInput, (XtPointer)c);
    return c;
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    Widget toplevel = XtInitialize("", "IlvMotif", NULL, 0,
				   &argc, argv);
    if (!toplevel)
	exit(1);
    Widget drawArea = XtVaCreateManagedWidget("ilvview",
					      xmDrawingAreaWidgetClass,
					      (Widget)toplevel,
					      XtNwidth,  400,
					      XtNheight, 400,
					      (IlAny)0);
    Widget pushb = XtVaCreateManagedWidget("Quit",
					   xmPushButtonWidgetClass,
					   drawArea,
					   (IlAny)0);
    XtRealizeWidget(toplevel);
    IlvContainer* container = CreateContainer(drawArea);
    XtAddCallback(pushb, XmNactivateCallback, Quit, container->getDisplay());
    container->readFile("demo2d.ilv");
    XtMainLoop();
    return 0;
}
