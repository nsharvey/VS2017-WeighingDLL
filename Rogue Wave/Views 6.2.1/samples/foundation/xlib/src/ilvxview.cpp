// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/xlib/src/ilvxview.cpp
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
// Using the grapher into a XView window
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>
#include <stdio.h>

// --------------------------------------------------------------------------
// Integration Part with XView
// --------------------------------------------------------------------------

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/canvas.h>
#include <xview/panel.h>
#include <xview/scrollbar.h>
#include <xview/svrimage.h>
#include <xview/termsw.h>
#include <xview/text.h>
#include <xview/tty.h>
#include <xview/xv_xrect.h>

extern "C" void IlvDispatchEvent(XEvent* xevent);

// --------------------------------------------------------------------------
IlvDisplay*
IlvGetDisplay(Display* xdisplay)
{
    static IlvDisplay* display = 0;
    if (!display)
	display = new IlvDisplay(xdisplay, "IlvXView");
    return display;
}

// --------------------------------------------------------------------------
IlvContainer*
CreateContainer(Display* dpy,
		Window window)
{
    IlvContainer* view = new IlvContainer(IlvGetDisplay(dpy),
					  (IlvSystemView)window);
    return view;
}

// --------------------------------------------------------------------------
// event handler
void
ManageInput(Xv_window,
	    Event *event)
{
    IlvDispatchEvent((XEvent *)(event->ie_xevent));
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    Display* dpy;
    //
    // Initialize XView.
    //
    xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);

    Xv_opaque	    popup;
    Xv_opaque	    canvas;

    // create a  frame
    popup = xv_create(XV_NULL, FRAME_CMD,
		      XV_WIDTH, 640,
		      XV_HEIGHT, 400,
		      XV_LABEL, "Rogue Wave Views in XView",
		      FRAME_SHOW_RESIZE_CORNER, TRUE,
		      FRAME_CMD_PUSHPIN_IN, FALSE,
		      NULL);
    xv_set(xv_get(popup, FRAME_CMD_PANEL), WIN_SHOW, FALSE, NULL);

    // get a pointer on the X display
    dpy = (Display*)xv_get(popup, XV_DISPLAY);

    // create a canvas
    canvas = xv_create(popup, CANVAS,
		       XV_X, 0,
		       XV_Y, 0,
		       CANVAS_AUTO_SHRINK, FALSE,
		       CANVAS_AUTO_EXPAND, FALSE,
		       CANVAS_WIDTH,  1000,
		       CANVAS_HEIGHT, 1000,
		       XV_WIDTH, WIN_EXTEND_TO_EDGE,
		       XV_HEIGHT, WIN_EXTEND_TO_EDGE,
		       CANVAS_X_PAINT_WINDOW, TRUE,
		       NULL);
    xv_create(canvas, SCROLLBAR, SCROLLBAR_DIRECTION,
	      SCROLLBAR_HORIZONTAL,
	      SCROLLBAR_SPLITTABLE, TRUE,
	      NULL);
    xv_create(canvas, SCROLLBAR, SCROLLBAR_DIRECTION,
	      SCROLLBAR_VERTICAL,
	      SCROLLBAR_SPLITTABLE, TRUE,
	      NULL);

    // catch all events
    //
    xv_set(canvas_paint_window(canvas),
	   WIN_EVENT_PROC, ManageInput,
	   WIN_CONSUME_EVENTS,
	   WIN_REPAINT,
	   KBD_DONE,
	   KBD_USE,
	   WIN_MOUSE_BUTTONS,
	   LOC_MOVE,
	   LOC_DRAG,
	   LOC_WINENTER,
	   LOC_WINEXIT,
	   WIN_ASCII_EVENTS,
	   WIN_LEFT_KEYS,
	   WIN_RIGHT_KEYS,
	   WIN_TOP_KEYS,
	   NULL, NULL);

    // Create a Rogue Wave Views view within the canvas window
    IlvContainer* container =
	CreateContainer(dpy,
			(Window)xv_get(canvas_paint_window(canvas), XV_XID));
    container->readFile("demo2d.ilv");

    // Give control to the XView.
    xv_main_loop(popup);
    IlvExit(0);

    return 0;
}
