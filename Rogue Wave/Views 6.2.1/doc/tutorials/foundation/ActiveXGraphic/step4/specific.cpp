// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step4/specific.cpp
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
// Original includes from the step1.
#include "ActiveXGraphicAdapter.h"
#include <ilviews/grapher/inters.h>
// Added for step2.
#include <ilviews/windows/comgadap.h>
#include <oleidl.h>
#include "makenode.h"
#include <ilviews/grapher/commands.h>
// Added for step3.
#include <ilviews/base/error.h>
#if defined(IL_STD)
using std::ostream;
#endif
// Added for step4.
#include <ilviews/windows/comgint.h>

// Code from the step2.
// Control identifier.
const char* DefaultIdentifier =
  "http://www.roguewave.com/products-services/visualization/views";

// --------------------------------------------------------------------------
// This member function actually creates an IlvGraphicCOMAdapter and stores
// it as a node into the grapher.
void
MakeNodeInteractor::doIt(IlvRect& size)
{
    // the manager should actually be a grapher.
    IlvGrapher* grapher = IL_DYNAMICCAST(IlvGrapher*, manager());
    if (!grapher)
	return;
    // Creates the new IlvGraphicCOMAdapter object.
    const char* identifier = DefaultIdentifier;
    IlvGraphic* obj = new IlvGraphicCOMAdapter(size, identifier, getDisplay());
    // Deselects the previous object(s) if any.
    grapher->deSelect();
    // Adds the new object as a node into the grapher.
    grapher->addNode(obj, IlvTrue, grapher->getInsertionLayer());
    // Selects it.
    grapher->makeSelected(obj);
    // Deals with the commands if needed.
    if (grapher->isUndoEnabled())
	grapher->addCommand(new IlvAddNodeCommand(grapher,
						  obj,
						  grapher
						    ->getInsertionLayer()));
}

// Code from the step3.
// --------------------------------------------------------------------------
// This operator prints wchar_t strings into a standard ostream.
ostream&
operator<<(ostream& o, const wchar_t* str)
{
    size_t len = wcslen(str);
    size_t size = wcstombs(0, str, len) + 1;
    char* buf = new char[size];
    wcstombs(buf, str, len+1);
    o << buf;
    delete[] buf;
    return o;
}

// --------------------------------------------------------------------------
// This function, associated to an accelerator, gets the user type name of
// the control and prints it.
static void
GetTypeAccelerator(IlvManager* man, IlvView*, IlvEvent& ev, IlvAny)
{
    // Gets the object above which is the mouse pointer.
    IlvGraphic* graphic = man->lastContains(IlvPoint(ev.x(), ev.y()));
    // Any object?

    if (graphic) {
	// Is it an IlvGraphicCOMAdapter?
	IlvGraphicCOMAdapter* adapt =
	    IL_DYNAMICCAST(IlvGraphicCOMAdapter*, graphic);

	if (adapt) {
	    // Queries for the IOleObject interface.
	    IOleObject* pInterface;
	    HRESULT hr =
		adapt->queryInterface(IID_IOleObject, (void**)&pInterface);
	    // Smart pointer.
	    IlvCOMInterface<IOleObject> oleObject(pInterface);

	    // Succeeded?
	    if (SUCCEEDED(hr)) {
		// Asks for the user type name.
		LPOLESTR userType;
		hr = oleObject->GetUserType(USERCLASSTYPE_FULL, &userType);

		// Succeeded?
		if (SUCCEEDED(hr)) {
		    // Prints the result.
		    IlvCOut << "The type is: " << userType << ".\n";
		    // Asks for the global allocator.
		    LPMALLOC pMalloc;
		    if (SUCCEEDED(CoGetMalloc(1, &pMalloc))) {
			// Releases the memory allocated by GetUserType.
			pMalloc->Free(userType);
			// Releases the global allocator.
			pMalloc->Release();
		    }
		}
	    }

	}

    }

}

// Code from the step4.
// --------------------------------------------------------------------------
void
AttachInteractorAccelerator(IlvManager*	man,
			    IlvView*,
			    IlvEvent&	ev,
			    IlvAny	arg)
{
    // The arg parameter is actually an object interactor.
    IlvInteractor* inter = IL_CAST(IlvInteractor*, arg);
    // Gets the object above which is the mouse pointer.
    IlvGraphic* graphic = man->lastContains(IlvPoint(ev.x(), ev.y()));
    // Any object?

    if (graphic) {
	// Is it an IlvGraphicCOMAdapter?
	IlvGraphicCOMAdapter* adapt =
	    IL_DYNAMICCAST(IlvGraphicCOMAdapter*, graphic);

	if (adapt) {
	    // Attaches the interactor to the object.
	    adapt->setInteractor(inter);
	}
    }
}

// --------------------------------------------------------------------------
void
ActiveXGraphicAdapter::specificInitialization()
{
    // Code from the step1.
    // Initialization of the interactors.
    getGrapherRectangle()->makeView(this);
    IlvGrapher* grapher = getGrapherRectangle()->getGrapher();
    IlvView* view = getGrapherRectangle()->getView();
    _interactorCount = 4;
    _interactors = new IlvManagerViewInteractor*[_interactorCount];
    // Code modified for the step2.
    _interactors[0] = new MakeNodeInteractor(grapher, view);
    _interactors[1] = new IlvMakeLinkImageInteractor(grapher, view);
    _interactors[2] = new IlvGraphSelectInteractor(grapher, view);
    _interactors[3] = 0;
    _selectedInteractorIndex = 3;

    // Code added for the step3.
    // Adds an accelerator in order to get the UserType of the control
    // under the mouse pointer.
    grapher->addAccelerator(GetTypeAccelerator, IlvKeyUp, IlvCtrlChar('i'));

    // Code added for the step4.
    _objectInteractor = new IlvGraphicComAdapterInteractor;
    _objectInteractor->lock();
    // Adds an accelerator in order to attach an object interactor to the
    // control under the mouse pointer.
    grapher->addAccelerator(AttachInteractorAccelerator,
			    IlvKeyUp,
			    IlvCtrlChar('b'),
			    0,
			    _objectInteractor);
}
