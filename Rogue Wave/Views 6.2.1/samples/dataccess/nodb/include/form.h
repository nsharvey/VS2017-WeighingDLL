// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/form.h
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
#ifndef __Sample_Form__H__
#define __Sample_Form__H__

#include <ilviews/gadgets/frame.h>
#include <ilviews/dataccess/gadgets/dbtoggle.h>
#include <ilviews/dataccess/gadgets/dbfield.h>
#include <ilviews/dataccess/gadgets/mdatasrc.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/dataccess/gadgets/dbnavig.h>
#include <ilviews/base/gadget.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/gadgets/msglabel.h>

#include <app.h>

// --------------------------------------------------------------------------
// Entry field which converts to upper case
// --------------------------------------------------------------------------
class UserEntryField
   : public IliEntryField
{
public:
  UserEntryField (IlvDisplay*    display,
		  const IlvRect& rect,
		  IlvUShort      thickness = IlvDefaultGadgetThickness, 
		  IlvPalette*    palette   = 0);

  virtual const char* check(IlvUShort);
protected:
  virtual void valueToLabel (const IliValue& value);
};

// --------------------------------------------------------------------------
// Panel class for sample Form
// --------------------------------------------------------------------------
class Form
: public PageNoteBook 
{
public:
  Form(IlvAbstractView* view, const char* filename);

  void initForm();

  virtual void chkClickedLock();
  inline IlvBoolean isLockDataForm();

    IliDbNavigator* getDBNavigator() const
	{ return (IliDbNavigator*)getObject("DBNavigator"); }
    IliMemoryDataSource* getACCOUNT_MS() const
	{ return (IliMemoryDataSource*)getObject("ACCOUNT_MS"); }
    IliDbField* getFieldName() const
	{ return (IliDbField*)getObject("FieldName"); }
    IliDbField* getFieldFirstName() const
	{ return (IliDbField*)getObject("FieldFirstName"); }
    IliDbField* getFieldAge() const
	{ return (IliDbField*)getObject("FieldAge"); }
    IliDbField* getFieldAccount() const
	{ return (IliDbField*)getObject("FieldAccount"); }
    IliDbField* getFieldIdentifier() const
	{ return (IliDbField*)getObject("FieldIdentifier"); }
    IlvButton* getBNQuit() const
	{ return (IlvButton*)getObject("BNQuit"); }
    IliDbToggle* getCHKLockData() const
	{ return (IliDbToggle*)getObject("CHKLockData"); }

protected:
  IlvBoolean _lockDataForm;
  UserEntryField* _fieldUpper;
};

inline IlvBoolean
Form::isLockDataForm()
{
  return _lockDataForm;
}

#endif /* !__Sample_Form__H__*/

