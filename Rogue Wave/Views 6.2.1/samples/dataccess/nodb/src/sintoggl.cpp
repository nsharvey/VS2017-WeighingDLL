// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/sintoggl.cpp
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// How to insert a single toggle into table-gadget
// --------------------------------------------------------------------------

#include <sintoggl.h>

#ifdef IL_STD
#  include <strstream>
#else
#ifdef ILVFATFILENAMES
#  include <strstrea.h>
#else
#  include <strstream.h>
#endif
#endif

IL_STDUSE

// --------------------------------------------------------------------------
// panel class for sample SingleToggle
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
SingleToggle::SingleToggle(IlvAbstractView *view,const char* filename)
  :PageNoteBook(view, filename) {
    initSingleToggle();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
SingleToggle::initSingleToggle() {
  _toggleEditor = new IliSimpleToggle(getDisplay(), IlvPoint(0,0));
  getTBLOptions()->setColumnEditor(1,_toggleEditor);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageSingleToggle(Pan* mainPanel) {
  SingleToggle* panel = new SingleToggle(mainPanel,"sintoggl.ilv");
  mainPanel->addPageNoteBook(panel, "Single toggle", "sintoggl.txt");
}

