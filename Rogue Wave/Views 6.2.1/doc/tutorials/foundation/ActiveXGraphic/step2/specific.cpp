// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step2/specific.cpp
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
    if (!grapher) {
	return;
    }
    // Creates the new IlvGraphicCOMAdapter object.
    const char* identifier = DefaultIdentifier;
    IlvGraphicCOMAdapter* obj = new IlvGraphicCOMAdapter(size, identifier, getDisplay());
    // Deselects the previous object(s) if any.
    grapher->deSelect();
    // Adds the new object as a node into the grapher.
    grapher->addNode(obj, IlvTrue, grapher->getInsertionLayer());
    // Selects it.
    grapher->makeSelected(obj);
    // Deals with the commands if needed.
    if (grapher->isUndoEnabled()) {
	grapher->addCommand(new IlvAddNodeCommand(grapher,
						  obj,
						  grapher
						    ->getInsertionLayer()));
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
}
