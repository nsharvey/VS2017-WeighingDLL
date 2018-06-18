// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/inspect/dbpiepnl.h
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
// File: inform30/include/inform/inspect/dbpiepnl.h
// IlogViews 2.4 generated header file
// File generated: Wed May 28 16:58:52 1997
// --------------------------------------------------------------------------
#ifndef __Ili_Dbpiepnl_H
#define __Ili_Dbpiepnl_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ilv_Base_Message_H
#  include <ilviews/base/message.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#ifndef __Ilv_Graphics_Holder_H
#  include <ilviews/graphics/holder.h>
#endif

#ifndef __Ilv_Manager_Holder_H
#  include <ilviews/manager/holder.h>
#endif

#ifndef __Ili_Format_H
#  include <ilviews/dataccess/format.h>
#endif

#ifndef __Ili_Util_H
#  include <ilviews/dataccess/util.h>
#endif

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Maptable_H
#  include <ilviews/dataccess/maptable.h>
#endif

#ifndef __Ili_Datatype_H
#  include <ilviews/dataccess/datatype.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Tblcombo_H
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Clrcombo_H
#  include <ilviews/dataccess/gadgets/clrcombo.h>
#endif

#ifndef __Ili_Entryfld_H
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

#ifndef __Ili_Dbpiecht_H
#  include <../inform30/include/inform/gadgets/dbpiecht.h>
#endif

enum IliDbPieChartBookPage {
  IliDbPieChartDataPage = 0,
  IliDbPieChartSeriesPage,
  IliDbPieChartPageCount
};

// --------------------------------------------------------------------------
// IliDbPieChartPanel
// --------------------------------------------------------------------------
class ILV_DBSCHART_EXPORTED IliDbPieChartPanel
  : public IliInspectorProperties {
public:
  IliDbPieChartPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliDbPieChartPanel();

  //---- Defines pages ----
  virtual void pagesDefine();

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages without properties ----
  virtual void pageInit(IlInt);
  virtual void pageInitFrom (IlInt,IlvGraphic*);
  virtual IlBoolean pageValidate(IlInt);
  virtual void pageApply (IlInt,IlvGraphic*);
  virtual void pageCustomGeneralPage(IlInt);

  //---- Series ----
  IliDeclInspBookAccess(IliMemoryDataSource,StyDISPLAY_MS,1,"%DISPLAY_MS");
  IliDeclInspBookAccess(IliTableGadget,StyTBLChart,1,"TBLChart");
  IliDeclInspBookAccess(IlvButton,StyBTNDel,1,"BTNDel");
  IliDeclInspBookAccess(IlvButton,StyBTNRefresh,1,"BTNRefresh");

  void setDbPieChart(IliDbPieChart*);
  void chartSelected(const char*);
  void initTableGadget(IliTableGadget*, IlInt);

  void propertiesHasChanged(IliInspectorGadget*);
  void refreshSeries(IlBoolean onlyReset);
protected:
  void initBookData(IliDbGadgetPanel*);
  void initBookSeries();

  void initFromBookData(IliDbGadgetPanel*,IliDbPieChart*);
  void initFromBookSeries();

  IlBoolean validateBookData(IliDbGadgetPanel*);
  IlBoolean validateBookSeries();

private:
  IliDbPieChart* _pieChart;

  //---- data from pie chart ----
  IliString _dsName;
  IliString _seriesColumnName;
  IliString _valuesColumnName;

  IlBoolean _autoSelect;
  IliFilterValue _filter;
  IlFloat _start;
  IlFloat _range;
  IlvDim _delta;
  IliString _tearOff;
  IliFormat _valueFormat;
  IlBoolean _toolTip;
  IliDbPieLabelType _labelType;

  IliTgFocusControler _focusCtrl[IliDbPieChartPageCount];
};

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbPieChartPanel IliDbPieChartPanel
#endif

#endif 
