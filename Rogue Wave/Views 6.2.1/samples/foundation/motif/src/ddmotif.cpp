// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/ddmotif.cpp
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
// Main file for the Motif drag/drop to and from IlogViews objects
// --------------------------------------------------------------------------

#include <include/ddmotif.h>
#include <ilviews/manager/manager.h>
#include <ilviews/graphics/all.h>

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/AtomMgr.h>
#include <Xm/DragDrop.h>

struct DropData
{
    MotifDropSite* site;
    Position       x;
    Position       y;
};

// --------------------------------------------------------------------------
static void
DoTransfer(Widget,
	   XtPointer closure,
	   Atom*,
	   Atom* type,
	   XtPointer value,
	   unsigned long* length,
	   int)
{
    DropData* data = (DropData*)closure;
    data->site->dropRequest(*type, (IlAny)value, *length,
			    IlvPoint(data->x, data->y));
}

// --------------------------------------------------------------------------
static void
DropProcCallback(Widget w,
		 XtPointer /* always NULL */,
		 XtPointer callData)
{
    XmDropProcCallback dropData = (XmDropProcCallback)callData;
    int n = 0;
    Arg args[3];
    if (dropData->dropAction != XmDROP) {
        XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE);
	n++;
    } else {
	XmDropTransferEntryRec transferEntries[3];
	DropData* data = (DropData*)XtMalloc(sizeof(DropData));
	data->site   = MotifDropSite::getSite(w);
	data->x = dropData->x;
	data->y = dropData->y;
	transferEntries[0].target = MotifDropSite::ILVOBJECT_Atom;
	transferEntries[0].client_data = (XtPointer)data;
	transferEntries[1].target = MotifDropSite::ILVSAVEDOBJECT_Atom;
	transferEntries[1].client_data = (XtPointer)data;
	transferEntries[2].target = MotifDropSite::COMPOUND_TEXT_Atom;
	transferEntries[2].client_data = (XtPointer)data;
	XtSetArg(args[n], XmNdropTransfers, transferEntries);
	n++;
	XtSetArg(args[n], XmNnumDropTransfers, 3);
	n++;
	XtSetArg(args[n], XmNtransferProc, DoTransfer);
	n++;
    }
    XmDropTransferStart(dropData->dragContext, args, n);
}

IlvAList MotifDropSite::_crossRef;
Atom MotifDropSite::ILVOBJECT_Atom      = 0;
Atom MotifDropSite::ILVSAVEDOBJECT_Atom = 0;
Atom MotifDropSite::COMPOUND_TEXT_Atom  = 0;
// --------------------------------------------------------------------------
MotifDropSite::MotifDropSite(Widget widget)
: _widget(widget)
{
    _crossRef.insert((IlAny)widget, (IlAny)this);
    XtRealizeWidget(widget);
    Arg args[5];
    int n = 0;
    XtSetArg(args[n], XmNdropSiteOperations, XmDROP_MOVE|XmDROP_COPY);
    n++;
    Display* XDisplay = XtDisplay(widget);
    if (!ILVOBJECT_Atom) {
	ILVOBJECT_Atom      = XmInternAtom(XDisplay, (char*)"ILVOBJECT",
					   False);
	ILVSAVEDOBJECT_Atom = XmInternAtom(XDisplay, (char*)"ILVSAVEDOBJECT",
					   False);
	COMPOUND_TEXT_Atom  = XmInternAtom(XDisplay, (char*)"COMPOUND_TEXT",
					   False);
    }
    Atom targets[3];
    targets[0] = ILVOBJECT_Atom;
    targets[1] = ILVSAVEDOBJECT_Atom;
    targets[2] = COMPOUND_TEXT_Atom;
    XtSetArg(args[n], XmNimportTargets, targets);
    n++;
    XtSetArg(args[n], XmNnumImportTargets, 3);
    n++;
    XtSetArg(args[n], XmNdropProc, DropProcCallback);
    n++;
    XmDropSiteRegister(widget, args, n);
}

// --------------------------------------------------------------------------
MotifDropSite::~MotifDropSite()
{
    _crossRef.remove((IlAny)_widget);
}

// --------------------------------------------------------------------------
void
ContainerMotifDropSite::dropRequest(Atom atom,
				    IlAny what,
				    unsigned long length,
				    const IlvPoint& where)
{
    if (atom == ILVOBJECT_Atom) {
	IlvGraphic* copy = ((IlvGraphic*)what)->copy();
	IlvRect bbox;
	copy->boundingBox(bbox);
	copy->move(where.x() - (bbox.w() >> 1),
		   where.y() - (bbox.h() >> 1));
	_container->addObject(copy, IlTrue);
	return;
    }
    if (atom == ILVSAVEDOBJECT_Atom) {
	if (length) {
	    IlvPoint newWhere(where);
	    IlvView* view = new IlvView(_container->getDisplay(), "", "",
					IlvRect(0, 0, 10, 10), IlFalse);
	    IlvManager* manager = new IlvManager(_container->getDisplay());
	    manager->addView(view);
	    manager->setTransformer(view, _container->getTransformer());
	    manager->paste(view, (char*)what, newWhere);
	    IlUInt count;
	    IlvGraphic* ILVHUGE const* objects = manager->getObjects(count);
	    IlBoolean redraw = (count == 1) ? IlTrue : IlFalse;
	    for (IlUInt loop = 0; loop < count; loop++) {
		manager->removeObject(objects[loop], IlFalse, IlFalse);
		_container->addObject(objects[loop], redraw);
	    }
	    delete manager;
	    delete view;
	    if (!redraw)
		_container->reDraw();
	}
	return;
    }
    if (atom == COMPOUND_TEXT_Atom) {
	if (length)
	    _container->addObject(new IlvLabel(_container->getDisplay(),
					       where,
					       (char*)what),
				  IlTrue);
	return;
    }
}
