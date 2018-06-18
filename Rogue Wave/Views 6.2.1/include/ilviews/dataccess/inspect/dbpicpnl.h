// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbpicpnl.h
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
// Declaration of the IliDbOptionMenuPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbpicpnl_H
#define __Ili_Dbpicpnl_H

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

#ifndef __Ili_Dbpictur_H
#  include <ilviews/dataccess/gadgets/dbpictur.h>
#endif

// --------------------------------------------------------------------------
// IliDbPicturePanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbPicturePanel
  : public IliInspectorProperties {
public:
  IliDbPicturePanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliDbPicturePanel();

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pageCustomGeneralPage(IlInt);

  enum IliDbPictureTag {
    tgPic_Adjust = fld_TagsCount,
    tgPic_Type,
    tgPic_TagsCount
  };
};

#endif




