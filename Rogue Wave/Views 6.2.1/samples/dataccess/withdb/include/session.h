// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/include/session.h
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
// How to use the IliSQLSession and IliSQLCursor classes
// --------------------------------------------------------------------------
#ifndef __Sample_Session_H__
#define __Sample_Session_H__

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
// Panel class for sample Session
// --------------------------------------------------------------------------
class Session
: public PageNoteBook
{
public:
  Session(IlvAbstractView* view,const char* filename);

  void initSession();

  virtual void bnClickedApply(IlvGraphic*);

    IliSQLDataSource* getEMP_DS() const
	{ return (IliSQLDataSource*)getObject("EMP_DS"); }
    IliTableGadget* getTBLSalary() const
	{ return (IliTableGadget*)getObject("TBLSalary"); }
    IlvButton* getBNApply() const
	{ return (IlvButton*)getObject("BNApply"); }
    IliEntryField* getEDTBonus() const
	{ return (IliEntryField*)getObject("EDTBonus"); }
};


#endif /* !__Sample_Session_H__*/

