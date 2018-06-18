// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/ilvmotif.cpp
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
// Connection of IlogViews with a Motif interface
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/ellipse.h>

#include <stdio.h>
#include <stdlib.h>

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <Xm/PanedW.h>
#include <Xm/PushB.h>
#include <Xm/AtomMgr.h>
#include <Xm/Protocols.h>

static Widget BuildMotifPanel(Widget);
static IlvDisplay* display;

// --------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    // Creating an IlvDisplay using the second constructor
    Widget toplevel = XtInitialize("", "Demo", NULL, 0,
#if defined(XlibSpecificationRelease) && (XlibSpecificationRelease >= 5)
				   (int*)&argc,
#else  /* !X11 R5 or higher */
				   (Cardinal*)&argc,
#endif /* !X11 R5 or higher */
				   argv);
    if (!toplevel) {
	printf("Can't open display\n");
	exit(1);
    }
    // Creates an IlvDisplay using an existing Display*
    display = new IlvDisplay(XtDisplay(toplevel), "IlvMotif");

    // Creating a Motif Interface
    Widget drawingArea = BuildMotifPanel(toplevel);

    // Creating a Container using the existing Drawing Area Widget
    // NOTE : the used widget must be already realized !!!!!

    IlvContainer* container = new IlvContainer(display, drawingArea);
    container->addObject(new IlvFilledRectangle(display,
						IlvRect(10, 100, 80, 80)));
    container->addObject(new IlvFilledEllipse(display,
					      IlvRect(100, 200, 120, 80)));
    container->addObject(new IlvLabel(display, IlvPoint(40, 40),
				      "This is an IlvContainer"));
    XtAppMainLoop(XtWidgetToApplicationContext(toplevel));
    return 0;
}

// --------------------------------------------------------------------------
static void
Quit(Widget,
     XtPointer,
     XtPointer)
{
    delete display;
    exit(0);
}

//---------------------------------------------------------------------------
// Create a small Motif interface
// Returns the inner DrawingArea
//---------------------------------------------------------------------------
static Widget
BuildMotifPanel(Widget parent)
{
    Arg args[2];
    XtSetArg(args[0], XmNx, 400);
    XtSetArg(args[1], XmNy, 400);
    Widget shell = XtCreatePopupShell("IlvMotif", topLevelShellWidgetClass,
				      parent, args, 2);
    XtVaSetValues(shell,
		  XmNdeleteResponse, XmDO_NOTHING,
		  (IlAny)0);
    Atom wm_delete_window = XmInternAtom(XtDisplay(shell),
					 (char*)"WM_DELETE_WINDOW", False);
    XmAddWMProtocolCallback(shell, wm_delete_window, Quit, 0);
    Widget pane = XtVaCreateManagedWidget("pane",
					  xmPanedWindowWidgetClass,
					  shell,
					  XmNwidth,  400,
					  XmNheight, 400,
					  (IlAny)0);
    Widget drawArea = XtVaCreateManagedWidget("ilvview",
					      xmDrawingAreaWidgetClass,
					      pane,
					      XmNwidth,  300,
					      XmNheight, 300,
					      (IlAny)0);
    Widget pushb = XtVaCreateManagedWidget("QUIT",
					   xmPushButtonWidgetClass,
					   pane,
					   (IlAny)0);
    XtAddCallback(pushb, XmNactivateCallback, Quit, 0);
    XtManageChild(shell);
    XtPopup(shell, XtGrabNone);
    return drawArea;
}
