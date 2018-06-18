// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/myutil.cpp
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
// Definition of some global functions
// --------------------------------------------------------------------------

#include <myutil.h>

// --------------------------------------------------------------------------
static IlvSymbol* parameterProperty = 0;

// --------------------------------------------------------------------------
static void 
MyInitSymbol()
{
    if (!parameterProperty)
	parameterProperty = IlvGetSymbol("My_Parameter");
}

// --------------------------------------------------------------------------
static const IlvSymbol* 
MyGetParameterProperty() 
{
    MyInitSymbol();
    return parameterProperty;
}

// --------------------------------------------------------------------------
void 
MySetParameter(IlvGraphic* g,
	       IlvSymbol* s)
{
    if (g->hasProperty(MyGetParameterProperty()))
	g->replaceProperty(MyGetParameterProperty(), s);
    else
	g->addProperty(MyGetParameterProperty(), s);
}

// --------------------------------------------------------------------------
void 
MyUnSetParameter(IlvGraphic* g)
{
    if (g->hasProperty(MyGetParameterProperty()))
	g->removeProperty(MyGetParameterProperty());
}

// --------------------------------------------------------------------------
IlvSymbol* 
MyGetParameter(const IlvGraphic* g)
{
    return (IlvSymbol*)g->getProperty(MyGetParameterProperty());
}
