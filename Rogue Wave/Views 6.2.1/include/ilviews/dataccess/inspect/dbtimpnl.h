// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbtimpnl.h
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
// Declaration of the IliDbTimerPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtimpnl_H
#define __Ili_Dbtimpnl_H

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

// --------------------------------------------------------------------------
// IliDbTimerPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbTimerPanel
  : public IliInspectorProperties {
public:
  IliDbTimerPanel(IlvDisplay*,IlvSystemView transientFor = 0);

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);

  //---- Pages ----
  virtual void pagesDefine();

  enum IliTimerPropTag {
    tim_Name = fld_TagsCount,
    tim_Period,
    tim_TagsCount
  };

};

#endif




