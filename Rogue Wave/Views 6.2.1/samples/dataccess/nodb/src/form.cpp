// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/form.cpp
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

#include <form.h>

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
// Callbacks methods
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Called when the checkbox has been clicked
// --------------------------------------------------------------------------
static void ILVCALLBACK
_chkClickedLock(IlvGraphic* g, IlvAny) {
    Form* o = (Form*)IlvContainer::getContainer(g);
    o->chkClickedLock();
}

// --------------------------------------------------------------------------
// Make the field read-only if it is not null
// --------------------------------------------------------------------------
void ILVCALLBACK 
ReadOnlyCallBack(IliDataSource *ds, IliFieldItf *field,
                 IlvInt colno, IlvAny any) {
  Form *panel = (Form*) any;
  
  if (ds->getValue(colno).isNull() || (panel->isLockDataForm() == IlvFalse)) 
    field->f_setReadOnly(IlvFalse);
  else
    field->f_setReadOnly(IlvTrue);
}

// --------------------------------------------------------------------------
// Callback called when a new row selected
// --------------------------------------------------------------------------
void ILVCALLBACK
MyEnterRowCallBack(IlvGraphic *g,IlvAny any) {
  IliDataSource *ds = (IliDataSource*)g;
  Form *panel = (Form*) any;
  IliValue v;

  // set read only if necessary for all fields
  ds->applyToFields(ReadOnlyCallBack,any);

  // set color for account field
  v = ds->getValue("ACCOUNT");
  if((v.asInteger() >= 0) || (v.isNull())) {
    panel->getFieldAccount()->setForeground(
	     panel->getDisplay()->getColor("blue"));
  }
  else {
    panel->getFieldAccount()->setForeground(
	    panel->getDisplay()->getColor("red"));
  }
}

// --------------------------------------------------------------------------
// Callback called to validate data of a row
// --------------------------------------------------------------------------
void ILVCALLBACK
MyValidateRowCallBack(IlvGraphic *g,IlvAny) {
  IliDataSource *ds = (IliDataSource*)g;
  IliValue v;
  
  v = ds->getValue("AGE");
  if (v.asInteger() < 0) {
    ds->addErrorMessage("Invalid age");
    ds->dontValidateRow();
  }
}

// --------------------------------------------------------------------------
// Form
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Form::Form(IlvAbstractView* view, const char* filename)
  :PageNoteBook(view, filename) {
    initForm();
}

// --------------------------------------------------------------------------
// Set the callbacks and flags
// --------------------------------------------------------------------------
void
Form::initForm() {
  registerCallback("chkClickedLock", _chkClickedLock);

  //---- Set lock data ----
  _lockDataForm = IlvTrue;
  getCHKLockData()->setState(_lockDataForm);
  
  //---- set callback for read only and colors ----
  getACCOUNT_MS()->setCallback(IliDataSource::EnterRowSymbol(),
			       MyEnterRowCallBack,
			       this);
  //---- set callback to validate data ----
  getACCOUNT_MS()->setCallback(IliDataSource::ValidateRowSymbol(),
			       MyValidateRowCallBack);
  //---- go to first record ----
  getDBNavigator()->gotoFirst();

  //---- create the entry field for uppercase ----
  IlvRect rect(20, 89, 140, 22);
  _fieldUpper = new UserEntryField(getDisplay(), rect);
  _fieldUpper->f_setDataSourceName("ACCOUNT_MS");
  _fieldUpper->f_setDataSourceColumnName("NAME");
  _fieldUpper->f_setReadOnly(IlvTrue);
  addObject("FieldName",_fieldUpper);
}

// --------------------------------------------------------------------------
// Function called when the user modifies the read only flag
// --------------------------------------------------------------------------
void
Form::chkClickedLock() {
  //---- get value of read only flag ----
  _lockDataForm = getCHKLockData()->getState();
  
  //---- set read only flag for all fields ----
  getACCOUNT_MS()->applyToFields(ReadOnlyCallBack,this);

  //---- cancel modifications if the data locked again ----
  getDBNavigator()->cancel();
}

// --------------------------------------------------------------------------
// UserEntryField
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
UserEntryField::UserEntryField (IlvDisplay*    display,
				  const IlvRect& rect,
				  IlvUShort      thickness, 
				  IlvPalette*    palette)
  : IliEntryField(display, "", rect, thickness, palette) {
}

// --------------------------------------------------------------------------
// Convert the value for display
// --------------------------------------------------------------------------
void
UserEntryField::valueToLabel (const IliValue& value) {
  const char* s = value.asString();
  if(s && *s) {
    IlvInt ln = (IlvInt)strlen(s);
    char *str = new char [ln + 1];
  
    strcpy(str,s);
    for(IlvInt i = 0; i < ln; i++)
      str[i] = toupper(str[i]);
    setLabelSilently(str);
    delete [] str;
  }
  else {
    IliString lab;
    formatValue(lab, value);
    setLabelSilently(lab);
  }
}

// --------------------------------------------------------------------------
// Check the characters (skip the digits and convert uppercase the letters)
// --------------------------------------------------------------------------
const char*
UserEntryField::check(IlvUShort c) {
  
  if (isdigit(c))
    return getLabel();
  c = toupper(c);
  return IliEntryField::check(c);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageForm(Pan* mainPanel) {
  Form* panel = new Form(mainPanel,"form.ilv");
  mainPanel->addPageNoteBook(panel, "Form", "form.txt");
}


