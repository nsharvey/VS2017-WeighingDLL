// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/mgridint.cpp
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
// Definition of the IlvManagerGridInteractor class
// --------------------------------------------------------------------------
#include <ilviews/mgridint.h>
#include <ilviews/manager/objinter.h>

// --------------------------------------------------------------------------
const char*
IlvManagerGridInteractor::className() const
{
    return "Grid";
}

// --------------------------------------------------------------------------
IlvBoolean
IlvManagerGridInteractor::handleEvent(IlvManager* mgr,
				      IlvGraphic* obj, IlvEvent& event,
				      IlvView* view,
				      IlvTransformer* t)
{
    if(!obj->isSubtypeOf("IlvGridObj")) return IlvFalse;
    IlvGridObj* grid = (IlvGridObj*)obj;
    IlvPoint p(event.x(),event.y());
    if(t) t->inverse(p);
    if (((event.type() != IlvButtonDown) &&
	 (event.type() != IlvButtonUp)   &&
	 (event.type() != IlvButtonDragged)) ||
	(event.button() != IlvLeftButton)) return IlvFalse;
    static IlvGraphic*   downimage = 0; // Image selected in ButtonDown
    static IlvGraphic*   prevsel;       // Used for PushButton-like behaviour
    IlvUShort   irow, icol;
    IlvGraphic* image = grid->pointToPosition(p, icol, irow) ?
	grid->getObject(irow * grid->columns() + icol) : 0;
    switch (event.type()) {
    case IlvButtonDown:
	downimage = image;
	if (!downimage || grid->isReadOnly(downimage)) return IlvTrue;
	if ((grid->getSelectionType() == IlvGridExclusiveSelection) &&
	    ((prevsel = grid->getSelection()) != 0)             &&
	    (prevsel != downimage))
            grid->deSelect(view, t);
	grid->swapSelection(downimage);
	grid->reDrawObj(downimage, view, t,0);
	break;
    case IlvButtonDragged:
    case IlvButtonUp:
	if (downimage != image) {
	    if (!downimage || grid->isReadOnly(downimage)) {
		if ((grid->getSelectionType() ==
		     IlvGridExclusiveSelection) &&
		    ((prevsel = grid->getSelection()) != 0))
		    grid->deSelect(view, t);
	    } else {
		if (!((grid->getSelectionType() ==
		       IlvGridExclusiveSelection) &&
		      !grid->isSelected(downimage) &&
		      image && !grid->isSelected(image))) {
		    grid->swapSelection(downimage);
		    grid->reDrawObj(downimage, view, t, 0);
		}
	    }
	    downimage = image;
	    if (downimage && !grid->isReadOnly(downimage)) {
		grid->swapSelection(downimage);
		grid->reDrawObj(downimage, view, t, 0);
	    } else {
		if ((grid->getSelectionType() ==
		     IlvGridExclusiveSelection) &&
		    prevsel) {
		    grid->makeSelected(prevsel);
		    grid->reDrawObj(prevsel, view, t, 0);
		}
	    }
	}
	if (event.type() == IlvButtonUp) {
	    if (downimage && !grid->isReadOnly(downimage)) {
		if (grid->getSelectionType() == IlvGridNoSelection) {
		    grid->swapSelection(downimage);
		    grid->reDrawObj(downimage, view, t, 0);
		}
		if (image == downimage) {
		    if ((grid->getSelectionType() ==
			 IlvGridExclusiveSelection) &&
			prevsel &&
			(downimage != prevsel)) {
			grid->makeUnSelected(prevsel);
			grid->reDrawObj(prevsel, view, t, 0);
		    }
		    callCallback(mgr,view,grid,downimage);
		} else {
		    if ((grid->getSelectionType() ==
			 IlvGridExclusiveSelection) &&
			prevsel &&
			(downimage != prevsel)) {
			grid->makeSelected(prevsel);
		    }
		}
	    }
	    downimage = 0;
	}
    }
    return IlvTrue;
}

// --------------------------------------------------------------------------
void
IlvManagerGridInteractor::callCallback(IlvManager* ,IlvView*,IlvGridObj*,
				       IlvGraphic*)
{
}

ILVDECLAREMGRINTERACTOR(MakeGrid,IlvManagerGridInteractor)
// ----------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
ILVDEFINEINITCLASS(mgridint, IlvRegisterManagerInteractor("Grid",MakeGrid);)
#else  /* IlvDECLAREINITCLASS */
static int _cb= IlvRegisterManagerInteractor("Grid",MakeGrid);
#endif /* IlvDECLAREINITCLASS */
