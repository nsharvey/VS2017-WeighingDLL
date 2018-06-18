// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/mgrhook.cpp
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
// Definition of the IlvGridViewHook class
// --------------------------------------------------------------------------

#include <ilviews/mgrhook.h>
#include <ilviews/manager/mkrectin.h>

// --------------------------------------------------------------------------
IlvGridViewHook::IlvGridViewHook(IlvManager* mgr, IlvView* view,
				 IlvGridView* gridview)
: IlvManagerViewHook(mgr,view),_gridview(gridview)
{
    _interactors = new IlvAList();
}

// --------------------------------------------------------------------------
void
IlvGridViewHook::initialise(IlvManager* mgr,IlvView* view,
			    IlvGridView* gridview)
{
    setManager(mgr);
    setView(view);
    _gridview=gridview;
}

// --------------------------------------------------------------------------
IlvGridViewHook::~IlvGridViewHook()
{
    delete _interactors;
}

// --------------------------------------------------------------------------
static void
PushInteractor(IlvView*, IlvGridObj*, IlvGraphic*, IlvBoolean value,
	       IlvAny arg)
{
    IlvManagerViewInteractor* interactor = (IlvManagerViewInteractor*)arg;
    IlvManager* manager = interactor->manager();
    if (value)
	manager->pushInteractor(interactor);
    else
      manager->removeInteractor(interactor->view());
}

// --------------------------------------------------------------------------
static void
MakeObjectAction(IlvView*, IlvGridObj*, IlvGraphic* obj, IlvBoolean value,
		 IlvAny arg)
{
    IlvMakeObjectInteractor* interactor = (IlvMakeObjectInteractor*)arg;
    IlvManager* manager= interactor->manager();
    if (value) {
	interactor->setObject(obj);
	manager->setInteractor(interactor);
    } else
      manager->removeInteractor(interactor->view());
}

// --------------------------------------------------------------------------
void
IlvGridViewHook::add(IlvGraphic* gr,IlvManagerViewInteractor* inter)
{
    (*_gridview)->add(gr,IlvFalse,PushInteractor,inter);
    _interactors->insert(inter,gr);
  }

// --------------------------------------------------------------------------
void
IlvGridViewHook::addDynamic(IlvGraphic* gr,IlvManagerViewInteractor* inter)
{
    (*_gridview)->add(gr,IlvFalse,MakeObjectAction,inter);
    _interactors->insert(inter,gr);
}

// --------------------------------------------------------------------------
void
IlvGridViewHook::interactorChanged(IlvManagerViewInteractor* oldone,
				   IlvManagerViewInteractor* newone)
{
    IlvGraphic* oldgr=(IlvGraphic *)_interactors->get(oldone);
    IlvGraphic* newgr=(IlvGraphic *)_interactors->get(newone);
    if(newgr) {
	(*_gridview)->makeSelected(newgr);
	(*_gridview)->reDrawObj(newgr, _gridview,
				_gridview->getTransformer(), 0);
    }
    if (oldgr) {
	(*_gridview)->makeUnSelected(oldgr);
	(*_gridview)->reDrawObj(oldgr, _gridview,
				_gridview->getTransformer(),0);
      }
}
