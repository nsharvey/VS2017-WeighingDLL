// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/dbgraphe/include/grapher.h
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
// Customize a grapher
// --------------------------------------------------------------------------
#ifndef __Sample_Grapher__H__
#define __Sample_Grapher__H__

#include <ilviews/gadgets/frame.h>
#include <ilviews/dataccess/gadgets/mdatasrc.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/base/gadget.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/polyline.h>

#include <ilviews/dataccess/gadgets/tablegad.h>
#include <ilviews/dataccess/gadgets/dbgraphe.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Grapher
// --------------------------------------------------------------------------
class Grapher
    : public PageNoteBook 
{
public:
    Grapher(IlvAbstractView* view, const char* filename);

    void initGrapher();
    virtual void afterBuild();

    IliDbGrapher* getGRAPHER() const
    { return (IliDbGrapher*)getObject("GRAPHER"); }
};

// --------------------------------------------------------------------------
// Panel class for sample nodes of the Grapher
// --------------------------------------------------------------------------
class NodeGrapher
    : public PageNoteBook 
{
public:
    NodeGrapher(IlvAbstractView* view, const char* filename);

    void initNodeGrapher();

    IliTableGadget* getTG() const
    { return (IliTableGadget*)getObject("TG"); }
};

// --------------------------------------------------------------------------
// Panel class for sample links of the Grapher
// --------------------------------------------------------------------------
class LinkGrapher
    : public PageNoteBook 
{
public:
    LinkGrapher(IlvAbstractView* view, const char* filename);

    void initLinkGrapher();

    IliTableGadget* getTG() const
    { return (IliTableGadget*)getObject("TG"); }
};

#endif /* !__Sample_Grapher__H__*/


