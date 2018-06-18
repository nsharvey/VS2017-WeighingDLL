// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbfldpnl.h
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
// Declaration of the IliDbFieldPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbfldpnl_H
#define __Ili_Dbfldpnl_H

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadmgr_Gadmgr_H
#  include <ilviews/gadmgr/gadmgr.h>
#endif

#ifndef __Ili_Fontcomb_H
#  include <ilviews/dataccess/gadgets/fontcomb.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class ILV_DBS_EXPORTED IliDbFieldPanel:
  public IliInspectorProperties {
public:
  IliDbFieldPanel (IlvDisplay* display,IlvSystemView transientFor = 0);

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pagesDefine();
  virtual void pageCustomGeneralPage(IlInt);

  enum IliDbFieldPropTag {
    dbf_Style = fld_TagsCount,
    dbf_Label,
    dbf_LabelFont,
    dbf_LabelColor,
    dbf_LabelPos,
    dbf_TagsCount
  };

protected:
  IliColorComboBox* _colorCombo;
  IliFontComboBox* _fontCombo;
};

#endif
