// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/views.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Definition of the Views class
// --------------------------------------------------------------------------

#include <vpf/gui/views.h>
#include <vpf/gui/manager.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/slist.h>

// --------------------------------------------------------------------------
Views::Views(IlvGadgetContainer* container, Manager* manager)
: _container(container),
  _manager(manager)
{
    _list = (IlvStringList*)_container->getObject("views");
    _list->setCallback(ActivateCB, this);
    _list->setCallback(_list->SelectCBSymbol(), SelectCB, this);

    IlvGraphic* add = _container->getObject("addview");
    add->setCallback(AddCB, this);
    _remove = (IlvButton*)_container->getObject("deleteview");
    _remove->setCallback(RemoveCB, this);
    _remove->setSensitive(IlFalse);
}

// --------------------------------------------------------------------------
Views::~Views()
{
}

// --------------------------------------------------------------------------
void
Views::AddCB(IlvGraphic* graphic, IlvAny arg)
{
    Views* gv = (Views*) arg;
    gv->add();
}

// --------------------------------------------------------------------------
void
Views::RemoveCB(IlvGraphic* graphic, IlvAny arg)
{
    Views* gv = (Views*) arg;
    gv->remove();
}

// --------------------------------------------------------------------------
void
Views::SelectCB(IlvGraphic* graphic, IlvAny arg)
{
    Views* gv = (Views*) arg;
    gv->select();
}

// --------------------------------------------------------------------------
void
Views::ActivateCB(IlvGraphic* graphic, IlvAny arg)
{
    Views* gv = (Views*) arg;
    gv->activate();
}

// --------------------------------------------------------------------------
void
Views::UpdateCB(IlvView* view, IlvAny arg)
{
    Views* gv = (Views*) arg;
    gv->update(view);
}

// --------------------------------------------------------------------------
void
Views::update(IlvView* view)
{
    for (IlUShort i = 0; i < _list->getCardinal(); i++)
	if ((IlvView*) _list->getItemData(i) == view) {
	    _list->setLabel(i, view->getTitle());
	    _list->reDraw();
	    break;
    }
}

// --------------------------------------------------------------------------
void
Views::add()
{
    IlvView* view = _manager->installView(UpdateCB, this);
    view->moveToMouse();
    _list->addLabel(view->getTitle(), view);
    _list->reDraw();
}

// --------------------------------------------------------------------------
void
Views::remove()
{
    int i;
    IlvView* view;

    while ((i = _list->getFirstSelectedItem()) != -1) {
	view = (IlvView*) _list->getItemData(i);
	_manager->removeView(view);
	delete view;

	_list->removeLabel(i);
    }
    _list->reDraw();

    if (!_list->getCardinal()) {
	_remove->setSensitive(IlFalse);
	_remove->reDraw();
    }
}

// --------------------------------------------------------------------------
void
Views::select()
{
    if (_list->getFirstSelectedItem() != -1) {
	if (!_remove->isSensitive()) {
	    _remove->setSensitive(IlTrue);
	    _remove->reDraw();
	}
    }
}

// --------------------------------------------------------------------------
void
Views::activate()
{
    IlvView* view = 0;
    int i;
    if ((i = _list->getFirstSelectedItem()) != -1) {
	view = (IlvView*) _list->getItemData(i);
	view->show();
	view->raise();
    }
}
