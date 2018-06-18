// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/include/query.h
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
// Add a condition to a query
// --------------------------------------------------------------------------
#ifndef __Sample_Query_H__
#define __Sample_Query_H__

#include <app.h>

#include <ildblink/dblink.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/dataccess/gadgets/dbfield.h>
#include <ilviews/dataccess/gadgets/dbnavig.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/dataccess/gadgets/sqldtsrc.h>
#include <ilviews/dataccess/gadgets/tablegad.h>

// --------------------------------------------------------------------------
// Panel class for sample Query
// --------------------------------------------------------------------------
class Query
: public PageNoteBook
{
public:
  Query(IlvAbstractView* view, const char* filename);

  void initQuery();

  virtual void bnClickedSelect(IlvGraphic*);

  IliSQLDataSource* getEMP_DS() const
  { return (IliSQLDataSource*)getObject("EMP_DS"); }
  IliEntryField* getEDTEmployee() const
  { return (IliEntryField*)getObject("EDTEmployee"); }
  IliEntryField* getEDTManager() const
  { return (IliEntryField*)getObject("EDTManager"); }
  IliEntryField* getEDTDept() const
  { return (IliEntryField*)getObject("EDTDept"); }
  IlvButton* getBNSelect() const
  { return (IlvButton*)getObject("BNSelect"); }
};

#endif /* !__Sample_Query_H__*/
