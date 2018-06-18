// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step6/ActiveXGraphicAdapter.cpp
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
#include "ActiveXGraphicAdapter.h"
#include <ilviews/gadgets/menubar.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/base/error.h>
#include <ilviews/gadgets/appli.h>
#include "makenode.h"

const char* FILENAME = "ActiveXGraphicAdapter.ilv";

// --------------------------------------------------------------------------
static void ILVCALLBACK
_Load(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->Load(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_New(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->New(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_Save(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->Save(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_SaveAs(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->SaveAs(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_Quit(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->Quit(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_SetNodeInteractor(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->SetNodeInteractor(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_SetLinkInteractor(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->SetLinkInteractor(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_SetSelectInteractor(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->SetSelectInteractor(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_SetNoViewInteractor(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->SetNoViewInteractor(g);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
_Help(IlvGraphic* g, IlvAny)
{
    ActiveXGraphicAdapter* o =
	ILVDYNAMICCAST(ActiveXGraphicAdapter*,
		       IlvGraphic::GetCurrentCallbackHolder()->getContainer());
    if (o)
	o->Help(g);
}

#include <ilviews/base/sstream.h>
#if defined(ILVSTD)
#include <fstream>
using std::ofstream;
ILVSTDUSE
#else  /* !ILVSTD */
#include <fstream.h>
#endif /* !ILVSTD */

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::initialize()
{
    readFile(FILENAME);
    registerCallback("New", _New);
    registerCallback("Load", _Load);
    registerCallback("Save", _Save);
    registerCallback("SaveAs", _SaveAs);
    registerCallback("Quit", _Quit);
    registerCallback("SetNodeInteractor", _SetNodeInteractor);
    registerCallback("SetLinkInteractor", _SetLinkInteractor);
    registerCallback("SetSelectInteractor", _SetSelectInteractor);
    registerCallback("SetNoViewInteractor", _SetNoViewInteractor);
    registerCallback("Help", _Help);
    specificInitialization();
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::save()
{
    ofstream ofstr(_loadedFile.getValue());
    getGrapher()->save(ofstr);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::setInteractor(IlvGraphic* g, IlvUShort newSelectedItem)
{
    IlvPopupMenu* popup = ILVDYNAMICCAST(IlvPopupMenu*, g);
    ILVASSERT(g != 0,
	      IlvCErr << "ActiveXGraphicAdapter::setInteractor: parameter is not an IlvPopupMenu.\n";);
    popup->getItem(_selectedInteractorIndex)->setChecked(IlvFalse);
    _selectedInteractorIndex = newSelectedItem;
    popup->getItem(_selectedInteractorIndex)->setChecked(IlvTrue);
    getGrapher()->setInteractor(_interactors[_selectedInteractorIndex],
				getGrapherView());
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
ActiveXGraphicAdapter::~ActiveXGraphicAdapter()
{
    getGrapher()->setInteractor(0, getGrapherView());
    if (_interactors) {
	for (IlvUShort count = 0; count < _interactorCount; ++count)
	    if (_interactors[count])
		delete _interactors[count];
	delete [] _interactors;
    }
    if (_objectInteractor)
	_objectInteractor->unLock();
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::New(IlvGraphic*)
{
    getGrapher()->deleteAll(IlvTrue, IlvTrue);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::Load(IlvGraphic*)
{
    _fileBrowser.setType(IlvFileSelectorLoad);
    const char* file = _fileBrowser.get();
    if (file) {
	getGrapher()->read(file);
	_loadedFile = file;
	getGrapher()->reDraw();
    } else
	IlvCErr << getDisplay()->getMessage("&menu_open...")
		<< ": canceled.\n";
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::Save(IlvGraphic* g)
{
    if (!_loadedFile)
	SaveAs(g);
    else
	save();
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::SaveAs(IlvGraphic*)
{
    _fileBrowser.setType(IlvFileSelectorSave);
    const char* file = _fileBrowser.get();
    if (file) {
	_loadedFile = file;
	save();
    } else
	IlvCErr << getDisplay()->getMessage("&menu_saveAs...")
		<< ": canceled.\n";
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::Quit(IlvGraphic*)
{
    IlvApplication* app = IlvApplication::GetApplication(this);
    if (app)
	IlvAppExit(this, app);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::SetNodeInteractor(IlvGraphic* g)
{
    setInteractor(g, 0);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::SetLinkInteractor(IlvGraphic* g)
{
    setInteractor(g, 1);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::SetSelectInteractor(IlvGraphic* g)
{
    setInteractor(g, 2);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::SetNoViewInteractor(IlvGraphic* g)
{
    setInteractor(g, 3);
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::Help(IlvGraphic* g)
{
    IlvCErr << getDisplay()->getMessage("&menu_help")
	    << ": not yet implemented.\n";
}
