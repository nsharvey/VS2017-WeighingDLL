// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/xlib/src/ilvolit.cpp
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
// Integration sample with OpenLook
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>

// --------------------------------------------------------------------------
// Integration Part with Olit
// --------------------------------------------------------------------------

#include <X11/Xlib.h>
#include <Xol/OpenLook.h>
#include <Xol/ControlAre.h>
#include <Xol/DrawArea.h>
#include <Xol/BaseWindow.h>
#include <Xol/ScrolledWi.h>
#include <Xol/OblongButt.h>
#include <X11/StringDefs.h>

// --------------------------------------------------------------------------
static void
Quit(Widget,
     XtPointer display,
     XtPointer)
{
    delete (IlvDisplay*)display;
    IlvExit(0);
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
    static IlvDisplay* display = 0;
    if (!display)
	display = new IlvDisplay(xdisplay, "IlvOlit");
    return display;
}

// --------------------------------------------------------------------------
IlvContainer*
CreateContainer(Widget widget)
{
    IlvContainer* view = new IlvContainer(IlvGetDisplay(XtDisplay(widget)),
					  (IlvSystemView)XtWindow(widget));
    XtAddEventHandler(widget, INPUT_MASK, IlvFalse,
		      ManageInput, (XtPointer)view);
    return view;
}

// --------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
int
main(int argc,
     char* argv[])
{
    Widget toplevel = OlInitialize("", "IlvOlit", NULL, 0,
				   (Cardinal*)&argc,
				   argv);
    if (!toplevel)
	IlvExit(1);
    Widget control = XtVaCreateManagedWidget("control",
					     controlAreaWidgetClass,
					     toplevel,
					     XtNwidth,  430,
					     XtNheight, 400,
					     XtNbackground, 0xC0C0C0,
					     (IlAny)0);
    Widget scrolled = XtVaCreateManagedWidget("scolling",
					      scrolledWindowWidgetClass,
					      control,
					      XtNwidth,  400,
					      XtNheight, 430,
					      (IlAny)0);
    Widget drawArea = XtVaCreateManagedWidget("ilvview",
					      drawAreaWidgetClass,
					      scrolled,
					      XtNwidth, 800,
					      XtNheight, 800,
					      (IlAny)0);
    Widget pushb = XtVaCreateManagedWidget("button",
					   oblongButtonWidgetClass,
					   control,
					   XtNlabel, "Quit",
					   XtNbackground, 0xA0A0A0,
					   (IlAny)0);
    XtRealizeWidget(toplevel);

    IlvContainer* container = CreateContainer(drawArea);
    XtAddCallback(pushb, XtNselect, Quit, container->getDisplay());
    container->readFile("demo2d.ilv");
    XtMainLoop();
}
