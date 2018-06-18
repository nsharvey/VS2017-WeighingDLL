// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/src/gauge.cpp
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
// How to use a gauge within a form
// --------------------------------------------------------------------------
#include <gauge.h>

#ifdef IL_STD
#include <cstring>
#include <cstdio>
#else
#include <string.h>
#include <stdio.h>
#endif

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
// Called when the focus moves out of the salary field
// --------------------------------------------------------------------------
void ILVCALLBACK
MyFocusOutCallBack(IlvGraphic *g,IlAny) {
  IliDbField *salaryField = (IliDbField*)g;
  Gauge *panel  = (Gauge*)IlvContainer::getContainer(g);
  IlvCircularGauge* salaryGauge = panel->getGRCircGauge();
  
  IliValue v;

  //---- set value for gauge ----
  v = salaryField->f_getValue();

  if (v.asFloat() >= 0.0 && v.asFloat() != salaryGauge->getValue()) {
    salaryGauge->setValue(v.asFloat());
    panel->reDrawObj(salaryGauge);
  }
}

// --------------------------------------------------------------------------
// Called when a new row is selected in the data-source and when a row's 
// pending edits are canceled
// --------------------------------------------------------------------------
void ILVCALLBACK
MyGaugeRefreshCallBack(IlvGraphic *g,IlAny) {
  IliSQLDataSource *ds = (IliSQLDataSource*)g;
  Gauge *panel = (Gauge*)IlvContainer::getContainer(g);
  IlvCircularGauge* salaryGauge = panel->getGRCircGauge();
  IliValue v;

  //---- set value for gauge ----
  v = ds->getValue("SALARY");
  
  if (v.asFloat() >= 0.0) {
    salaryGauge->setValue(v.asFloat());
    panel->reDrawObj(salaryGauge);
  }
}

// --------------------------------------------------------------------------
// Callback called when a row has been modified or when a new row is inserted
// --------------------------------------------------------------------------
void ILVCALLBACK
MyQuitUpdateModeCallBack(IlvGraphic *g,IlAny) {
  IliSQLDataSource *ds = (IliSQLDataSource*)g;
  Gauge *panel = (Gauge*)IlvContainer::getContainer(g);
  IlvCircularGauge* salaryGauge = panel->getGRCircGauge();
  IlvCircularScale* salaryScale = panel->getGRCircScale();
  IlFloat v;

  // set color for account field
  v = ds->getValue("SALARY").asFloat();
  
  if (v >= 0.0) {
    if (v < salaryGauge->getMin()) {
      salaryGauge->setMin(v);
      salaryScale->setLabels(10, v, salaryGauge->getMax(), "%5.f");
      panel->reDrawObj(salaryScale);
    }
    if (v > salaryGauge->getMax()) {
      salaryGauge->setMax(v);
      salaryScale->setLabels(10, salaryGauge->getMin(), v, "%5.f");
      panel->reDrawObj(salaryScale);
    }
      
    salaryGauge->setValue(v);
    panel->reDrawObj(salaryGauge);
  }
}

// --------------------------------------------------------------------------
// Interactor's callback called when the user modifies the gauge value
// --------------------------------------------------------------------------
void ILVCALLBACK
MyGaugeInteractor(IlvGauge *gauge,IlFloat,IlAny any) {
  Gauge *panel = (Gauge*)any;
  IlFloat v = gauge->getValue();

  panel->getEMP_DS()->setValue("SALARY", IliValue(v));
}

// --------------------------------------------------------------------------
// Panel class for sample Gauge
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Gauge::Gauge(IlvAbstractView* view, const char* filename) 
  : PageNoteBook(view, filename) {
    initGauge();
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
Gauge::~Gauge() {
}

// --------------------------------------------------------------------------
// Sets the callbacks and flags
// --------------------------------------------------------------------------
void
Gauge::initGauge()
{
  IlvGaugeInteractor* inter;

  //---- set interactor for gauge ----
  inter = new IlvGaugeInteractor(MyGaugeInteractor, this);
  getGRCircGauge()->setInteractor(inter);

  //---- set callback for read only and colors ----
  getEMP_DS()->setCallback(IliDataSource::EnterRowSymbol(),
                             MyGaugeRefreshCallBack);
  getEMP_DS()->setCallback(IliDataSource::QuitUpdateModeSymbol(),
                             MyQuitUpdateModeCallBack);
  getEMP_DS()->setCallback(IliDataSource::QuitInsertModeSymbol(),
                             MyQuitUpdateModeCallBack);
  getEMP_DS()->setCallback(IliDataSource::CancelEditsSymbol(),
                             MyGaugeRefreshCallBack);

  //---- set callback for Salary Field ----
  getEDTSalary()->setCallback(MyFocusOutCallBack);
  
  //---- go to first record ----
  getDBNavigator()->gotoFirst();
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageGauge(Pan* mainPanel) {
  Gauge* panel = new Gauge(mainPanel,"gauge.ilv");
  mainPanel->addPageNoteBook(panel, "Gauge", "gauge.txt");
}

