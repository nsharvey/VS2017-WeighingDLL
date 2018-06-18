// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/sintoggl.h
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
#ifndef __Sample_Sintoggl__H__
#define __Sample_Sintoggl__H__

#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/dataccess/gadgets/mdatasrc.h>
#include <ilviews/dataccess/gadgets/tablegad.h>
#include <ilviews/dataccess/gadgets/tblcombo.h>
#include <ilviews/dataccess/gadgets/dbsimtog.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample SingleToggle
// --------------------------------------------------------------------------
class SingleToggle
  : public PageNoteBook 
{
public:
  SingleToggle(IlvAbstractView* view, const char* filename);

  void initSingleToggle();

  IliTableGadget* getTBLOptions() const
  { return (IliTableGadget*)getObject("TBLOptions"); }
protected:
  IliSimpleToggle* _toggleEditor;
};

#endif /* !__Sample_Sintoggl__H__*/


