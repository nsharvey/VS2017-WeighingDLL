// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/src/selinter.cpp
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
// Definition of SelectInteractor class
// --------------------------------------------------------------------------
#include "selinter.h"
#include <ManagerDocument.h>
#include <ManagerView.h>

// --------------------------------------------------------------------------
// SelectInteractor methods
// --------------------------------------------------------------------------
SelectInteractor::SelectInteractor(IlvManager*    manager,
				   ManagerView*   view,
				   unsigned short button,
				   IlBoolean      showCursor)
    : IlvSelectInteractor(manager,
			  (IlvView*)view->getDvView(),
			  button,
			  showCursor),
      _view(view),
      _translationStep(1, 1)
{
}

// --------------------------------------------------------------------------
SelectInteractor::~SelectInteractor()
{
}

// --------------------------------------------------------------------------
void
SelectInteractor::addedToSelection(IlvGraphic* graphic)
{
    IlvSelectInteractor::addedToSelection(graphic);
    _view->setActiveSelection(graphic);
    _view->selectionChanged();
}

// --------------------------------------------------------------------------
void
SelectInteractor::removedFromSelection(IlvGraphic* graphic)
{
    IlvSelectInteractor::removedFromSelection(graphic);
    _view->removedFromSelection(graphic);
    _view->selectionChanged();
}

// --------------------------------------------------------------------------
void
SelectInteractor::doTranslate(const IlvPoint& point)
{
    _view->doTranslate(point);
}

// --------------------------------------------------------------------------
void
SelectInteractor::doReshape(IlvGraphic* graphic,
			    const IlvRect& rect)
{
    _view->doReshape(graphic, rect);
}

// --------------------------------------------------------------------------
void
SelectInteractor::objectReSelected(IlvGraphic* graphic)
{
    IlvSelectInteractor::objectReSelected(graphic);
    _view->setActiveSelection(graphic);
}

// --------------------------------------------------------------------------
IlBoolean
SelectInteractor::handleEvent(IlvEvent& event)
{
    switch (event.type()) {
    case IlvKeyDown: {
	if (event.getKey() == IlvDeleteKey) {
	    if (!event.modifiers()) {
		_view->deleteSelectedGraphics();
		return IlTrue;
	    }
	}
	if (!event.modifiers()) {
	    IlvPoint offset(0, 0);
	    switch(event.key()) {
	    case IlvLeftKey:
		offset.setX(-_translationStep.x());
		break;
	    case IlvUpKey:
		offset.setY(-_translationStep.y());
		break;
	    case IlvRightKey:
		offset.setX(_translationStep.x());
		break;
	    case IlvDownKey:
		offset.setY(_translationStep.y());
		break;
	    }
	    if (offset.x() || offset.y()) {
		_view->doTranslate(offset);
		return IlTrue;
	    }
	}
	break;
    }
    default:
	break;
    }
    return IlvSelectInteractor::handleEvent(event);
}

// --------------------------------------------------------------------------
// Static initializations
IL_BEGINMODULEINITDEF(selinter)
IL_ENDMODULEINITDEF(selinter)
#if !defined(ILVBUILDLIBS)
static int selinter_ini = (IL_MODINIT(selinter)(), 0);
#endif
