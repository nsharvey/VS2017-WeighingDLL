// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/html.h
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
// Compute read only flag and color in a form
// --------------------------------------------------------------------------
#ifndef __Sample_Html__H__
#define __Sample_Html__H__

#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/base/gadget.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/dataccess/gadgets/htmlrep.h>
#include <ilviews/dataccess/gadgets/mdatasrc.h>
#include <ilviews/dataccess/gadgets/tablegad.h>
#include <ilviews/dataccess/gadgets/toggsel.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Html
// --------------------------------------------------------------------------
class Html
: public PageNoteBook 
{
public:
  Html(IlvAbstractView* view, const char* filename);

  void initHtml();

  virtual void bnGenerate();

  IliHTMLReporter* getHTMLRep() const
    { return (IliHTMLReporter*)getObject("HTMLRep"); }
  IliToggleSelector* getTOGTable() const
    { return (IliToggleSelector*)getObject("TOGTable"); }
  IliToggleSelector* getTOGDoc() const
    { return (IliToggleSelector*)getObject("TOGDoc"); }
  IlvButton* getBTNGenerate() const
    { return (IlvButton*)getObject("BTNGenerate"); }
};

#endif /* !__Sample_Html__H__*/

