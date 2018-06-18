// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/viewsgen.h
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
// Declaration of the IlvStateGenerator related classes
// Defined in library ilvstates
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Viewsgen_H
#define __Ilv_States_Viewsgen_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#  include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Gadgets_Menubar_H)
#  include <ilviews/gadgets/menubar.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#  include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Gadgets_Appli_H)
#  include <ilviews/gadgets/appli.h>
#endif
#if !defined(__Ilv_States_Mstate_H)
#  include <ilviews/states/mstate.h>
#endif
#if !defined(__Ilv_States_State_H)
#  include <ilviews/states/state.h>
#endif

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvViewsGenerateContext
: public IlvSdGenerateContext
{
    IlvSdState*	    _State;
    IlvState*	    _Parent;
    IlInt	    _ParentSubset;
    IlvSdManager*   _RootState;
    IlvApplication* _Application;
    char*	    _ErrorString;
    IlBoolean	    _PassNumber; // used for multi pass generation
public:
    ILVSTATES_READWRITE(IlvSdState*, State);
    ILVSTATES_READWRITE(IlvState*, Parent);
    ILVSTATES_READWRITE(IlInt, ParentSubset);
    ILVSTATES_READWRITE(IlvSdManager*, RootState);
    ILVSTATES_READWRITE(IlvApplication*, Application);
    ILVSTATES_READWRITE(char*, ErrorString);
    ILVSTATES_READWRITE(IlBoolean, PassNumber);
    IlvViewsGenerateContext(IlvApplication* app)
	: _State(0),
	_Parent(0),
	_ParentSubset(0),
	_RootState(0),
	_Application(app),
	_ErrorString(0),
	_PassNumber(0) {}
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateGenerator
: public IlvSdGenerator
{
public:
    IlvStateGenerator(){}
    void* generate (IlvSdModel*,
		    IlvSdGenerateContext*);
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateRequirementGenerator
: public IlvSdGenerator
{
public:
    IlvStateRequirementGenerator() {}
    void* generate (IlvSdModel*,
		    IlvSdGenerateContext*);
};

ILVSTATESEXPORTEDFUNCTION(IlvStateManager*)
IlvReadStateFile(IlvApplication*, const char*);

// --------------------------------------------------------------------------
//class ILVSTATESEXPORTED IlvStateProcedureGenerator : public IlvSdGenerator {};
// --------------------------------------------------------------------------
//class ILVSTATESEXPORTED IlvStateManagerGenerator : public IlvSdGenerator {};

#endif /* !__Ilv_States_Viewsgen_H */
