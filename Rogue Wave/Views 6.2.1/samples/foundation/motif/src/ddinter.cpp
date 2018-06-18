// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/ddinter.cpp
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
// Object interactor that implements the Motif Drag&Drop
// --------------------------------------------------------------------------

#include <include/ddmotif.h> // Defines the known Atoms
#include <include/ddinter.h>
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/AtomMgr.h>
#include <Xm/DragDrop.h>

// --------------------------------------------------------------------------
Boolean
ConvertDrop(Widget w,
	    Atom*,
	    Atom* target,
	    Atom* typeRtn,
	    XtPointer* valueRtn,
	    unsigned long* length,
	    int* format)
{
    if (!XmIsDragContext(w))
        return False;
    IlvGraphic* obj;
    XtVaGetValues(w, XmNclientData, &obj, (IlAny)0);
    if (obj && (*target == MotifDropSite::ILVOBJECT_Atom)) {
	*typeRtn = *target;
	IlvGraphic* returned = (IlvGraphic*)XtMalloc(sizeof(IlvGraphic*));
	returned = obj;
	*valueRtn = (XtPointer)returned;
	*length = sizeof(IlvGraphic*);
	*format = 8;
	return IlTrue;
    }
    return False;
}

// --------------------------------------------------------------------------
IlBoolean
MotifDragInteractor::handleButtonDown(IlvGraphic* obj,
				      IlvEvent& event,
				      const IlvTransformer*)
{
    Arg args[8];
    int n = 0;
    XtSetArg(args[n], XmNexportTargets, &MotifDropSite::ILVOBJECT_Atom);
    n++;
    XtSetArg(args[n], XmNnumExportTargets, 1);
    n++;
    XtSetArg(args[n], XmNconvertProc,      ConvertDrop);
    n++;
    XtSetArg(args[n], XmNdragOperations, XmDROP_MOVE|XmDROP_COPY);
    n++;
    XtSetArg(args[n], XmNclientData, obj);
    n++;
    Widget shell = (Widget)_widget;
    while (shell && !XtIsShell(shell))
	shell = XtParent(shell);
    int focusPolicy;
    XtVaGetValues(shell,
		  XmNkeyboardFocusPolicy, &focusPolicy,
		  (IlAny)0);
    XtVaSetValues(shell,
		  XmNkeyboardFocusPolicy, XmEXPLICIT,
		  (IlAny)0);
    (void)XmDragStart((Widget)_widget, (XEvent*)event.getInternal(), args, n);
    XtVaSetValues((Widget)shell,
		  XmNkeyboardFocusPolicy, focusPolicy,
		  (IlAny)0);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
MotifDragInteractor::handleEvent(IlvGraphic* obj,
				 IlvEvent& event,
				 const IlvTransformer* t)
{
    if (event.type() == IlvButtonDown) {
	if (event.button() == IlvMiddleButton)
	    return handleButtonDown(obj, event, t);
    }
    return IlFalse;
}
