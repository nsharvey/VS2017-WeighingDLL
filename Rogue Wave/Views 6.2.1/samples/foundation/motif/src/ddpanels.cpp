// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/ddpanels.cpp
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
// Creates Motif panels the Motif drag/drop of IlogViews objects
// --------------------------------------------------------------------------

#include <include/ddpanels.h>

#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

// --------------------------------------------------------------------------
Widget
CreateMotifPanels(IlvDisplay* display)
{
    Arg args[7];
    int n = 0;
    // Create a pure Motif drop area
    XtSetArg(args[n], XmNx,   0);
    n++;
    XtSetArg(args[n], XmNy, 450);
    n++;
    XtSetArg(args[n], XmNwidth,  200);
    n++;
    XtSetArg(args[n], XmNheight, 200);
    n++;
    XtSetArg(args[n], XmNdeleteResponse, XmDO_NOTHING);
    n++;
    XtSetArg(args[n], XmNtitle, "DragArea");
    n++;
    XtSetArg(args[n], XmNgeometry, "200x200+0+420");
    n++;
    Widget dragShell = XtCreatePopupShell("DragShell",
					  topLevelShellWidgetClass,
					  (Widget)display->topShell(),
					  args, n);
    XtManageChild(dragShell);
    Widget label = XmCreateLabel(dragShell, (char*)"Drag this label", args, 0);
    XtManageChild(label);
    XtPopup(dragShell, XtGrabNone);
    
    // Create a pure Motif drop area
    n = 0;
    XtSetArg(args[n], XmNx, 420);
    n++;
    XtSetArg(args[n], XmNy, 450);
    n++;
    XtSetArg(args[n], XmNwidth,  300);
    n++;
    XtSetArg(args[n], XmNheight, 300);
    n++;
    XtSetArg(args[n], XmNdeleteResponse, XmDO_NOTHING);
    n++;;
    XtSetArg(args[n], XmNtitle, "DropArea");
    n++;
    XtSetArg(args[n], XmNgeometry, "200x200+440+420");
    n++;
    Widget dropShell = XtCreatePopupShell("DropShell",
					  topLevelShellWidgetClass,
					  (Widget)display->topShell(),
					  args, n);
    XtManageChild(dropShell);
    Widget form = XmCreateForm(dropShell, (char*)"DropForm", args, 0);
    XtManageChild(form);
    XtPopup(dropShell, XtGrabNone);
    return form;
}

// --------------------------------------------------------------------------
// A drop has occured in the Motif drop area.
// Create a Label that shows the object's type, or the text contents.
// --------------------------------------------------------------------------
#include <ilviews/base/graphic.h>
void
MotifTextDropSite::dropRequest(Atom atom,
			       IlAny value,
			       unsigned long length,
			       const IlvPoint& p)
{
    if (atom == ILVOBJECT_Atom) {
	IlvGraphic* obj = (IlvGraphic*)value;
	Arg args[3];
	int n = 0;
	XtSetArg(args[n], XmNx, p.x());
	n++;
	XtSetArg(args[n], XmNy, p.y());
	n++;
	XtManageChild(XmCreateLabel(getWidget(), (char*)obj->className(),
				    args, n));
    }
    if (atom == COMPOUND_TEXT_Atom) {
	if (length) {
	    Arg args[3];
	    int n = 0;
	    XtSetArg(args[n], XmNx, p.x());
	    n++;
	    XtSetArg(args[n], XmNy, p.y());
	    n++;
	    XtManageChild(XmCreateLabel(getWidget(), (char*)value, args, n));
	}
    }
}
