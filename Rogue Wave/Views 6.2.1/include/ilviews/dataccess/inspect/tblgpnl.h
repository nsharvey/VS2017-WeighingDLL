// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/tblgpnl.h
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
// Declaration of the IliTableGadgetPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Tblgpnl_H
#define __Ili_Tblgpnl_H

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

class ILV_DBS_EXPORTED IliTableGadgetPanel:
  public IliInspectorProperties {
public:
  IliTableGadgetPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  IliTableGadgetPanel(IlvDisplay*,const char* title,
		      IlvSystemView transientFor = 0);

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pagesDefine();
  virtual void pageCustomGeneralPage(IlInt);

  enum Page {
    page_DataSource,
    page_General,
    page_Specific
  };

  enum IliTGPropTag {
    tg_KbdDelete = fld_TagsCount,
    tg_ConfirmDeletes,
    tg_KbdRefresh,
    tg_FixedColumns,
    tg_ColumnsGeometry,
    tg_AutoFit,
    tg_HeaderHeight,
    tg_RowHeight,
    tg_ShowHeaders,
    tg_ShowMarkers,
    tg_ShowGrid,
    tg_ShowInsertRow,
    tg_UseRelief,
    tg_ShowCellEditor,
    tg_RowSelect,
    tg_AlwaysShowSelection,
    tg_VertScroll,
    tg_HorzScroll,
    tg_HeaderFont,
    tg_CellFont,
    tg_CellBackground,
    tg_CellForeground,
    tg_BoundToDataSource,
    tg_MultiSelEnabled,
    tg_SortEnabled,
    tg_UsePropertyManager,
    tg_TagsCount
  };

protected:
  IliColorComboBox* _fgColorCombo;
  IliColorComboBox* _bgColorCombo;
  IliFontComboBox* _cellFontCombo;
  IliFontComboBox* _headerFontCombo;

  void initTableGadgetPanel();
};

#endif

