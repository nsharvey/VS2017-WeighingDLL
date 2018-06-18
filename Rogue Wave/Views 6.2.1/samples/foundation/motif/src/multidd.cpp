// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/multidd.cpp
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
// Demonstrating the Multi Process Motif drag/drop
// --------------------------------------------------------------------------

#include <include/ddmotif.h>
#include <include/multidd.h>
#include <ilviews/manager/manager.h>
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>
#include <ilviews/bitmaps/ppm.h>

static const char* DefaultFileName = "demo2d.ilv";

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// This function associates the Motif D&D interactor with each of the objects
// stored in this container.
// --------------------------------------------------------------------------
void
InstallMotifDrag(IlvContainer* src)
{
    MotifDragInteractor* mdd = new MotifDragInteractor(src->getDisplay(),
						       src->getSystemView());
    IlUInt count;
    IlvGraphic* const* objects = src->getObjects(count);
    for (IlUInt loop = 0; loop < count; loop++)
	objects[loop]->setInteractor(mdd);
}

// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    const char* filename = (argc > 1) ? argv[1] : DefaultFileName;
    IlvDisplay* display = new IlvDisplay("MotifMultiDD", "", argc, argv);
    if (!display || display->isBad()) {
	if (display) delete display;
	IlvFatalError("Couldn't open display...");
	return 1;
    }
    if (!display->topShell()) {
    	delete display;
	IlvFatalError("This Views application hasn't been linked with mviews...");
	return 1;
    }

    // Create a container to drag IlogViews objects from
    const char* title = "Drag&Drop Container";
    IlvContainer* sourceContainer = new IlvContainer(display, title, title,
						     IlvRect(0, 0, 400, 400),
						     IlTrue, IlFalse);
    sourceContainer->setDestroyCallback(Quit);
    sourceContainer->readFile(filename);
    // Set the interactors to the objects
    InstallMotifDrag(sourceContainer);
    // Register as a drop site
    ContainerMotifDropSite drop(sourceContainer);

    // Show this container
    sourceContainer->show();

    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
// Definition of the MotifDragInteractor class
// --------------------------------------------------------------------------
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
    XtVaGetValues(w,
		  XmNclientData, &obj,
		  (IlAny)0);
    if (obj && (*target == MotifDropSite::ILVSAVEDOBJECT_Atom)) {
	*typeRtn = *target;
	IlvContainer* sourceContainer = IlvContainer::getContainer(obj);
	if (!sourceContainer)
	    return IlFalse;
	IlvManager* mgr = new IlvManager(sourceContainer->getDisplay());
	IlvGraphic* objectCopy = obj->copy();
	objectCopy->removeInteractor();
	mgr->addObject(objectCopy, IlFalse);
	mgr->setSelected(objectCopy, IlTrue, IlFalse);
	IlUInt saveLength;
	char* saveString = mgr->copy(saveLength);
	char* returned = (char*)XtMalloc((unsigned int)(saveLength + 1));
	strcpy(returned, saveString);
	*valueRtn = (XtPointer)returned;
	*length = saveLength;
	*format = 8;
	delete [] saveString;
	delete mgr;
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
    static IlBoolean init = IlFalse;
    if (!init) {
	Display* XDisplay = (Display*)_display->getInternal();
	MotifDropSite::ILVOBJECT_Atom =
	    XmInternAtom(XDisplay, (char*)"ILVOBJECT",      False);
	MotifDropSite::ILVSAVEDOBJECT_Atom =
	    XmInternAtom(XDisplay, (char*)"ILVSAVEDOBJECT", False);
	MotifDropSite::COMPOUND_TEXT_Atom =
	    XmInternAtom(XDisplay, (char*)"COMPOUND_TEXT",  False);
	init = IlTrue;
    }

    Arg args[8];
    int n = 0;
    
    XtSetArg(args[n], XmNexportTargets, &MotifDropSite::ILVSAVEDOBJECT_Atom);
    n++;
    XtSetArg(args[n], XmNnumExportTargets, 1);
    n++;
    XtSetArg(args[n], XmNconvertProc, ConvertDrop);
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
    XtVaSetValues(shell,
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
