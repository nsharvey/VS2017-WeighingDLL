// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step1/specific.cpp
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
    _interactors[0] = 0;
    _interactors[1] = new IlvMakeLinkImageInteractor(grapher, view);
    _interactors[2] = new IlvGraphSelectInteractor(grapher, view);
    _interactors[3] = 0;
    _selectedInteractorIndex = 3;
}
