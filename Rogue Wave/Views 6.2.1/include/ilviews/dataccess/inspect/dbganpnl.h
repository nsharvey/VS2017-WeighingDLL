// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbganpnl.h
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
// Declaration of the IliDbGanttPanel class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbganpnl_H
#define __Ili_Dbganpnl_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Contain_Contain_H
#  include <ilviews/contain/contain.h>
#endif

#ifndef __Ilv_Util_Dialogs_H
#  include <ilviews/util/dialogs.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Graphics_Holder_H
#  include <ilviews/graphics/holder.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#ifndef __Ilv_Base_Message_H
#  include <ilviews/base/message.h>
#endif

#ifndef __Ilv_Manager_Holder_H
#  include <ilviews/manager/holder.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ili_Dbfield_H
#  include <ilviews/dataccess/gadgets/dbfield.h>
#endif

#ifndef __Ili_Dbgantt_H
#  include <ilviews/dataccess/gadgets/dbgantt/dbgantt.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

enum IliDbGanttBookPage {
  IliDbGanttResPage = 0,
  IliDbGanttModPage,
  IliDbGanttSclPage,
  IliDbGanttPrdPage,
  IliDbGanttProPage,
  IliDbGanttPageCount
};

// --------------------------------------------------------------------------
// IliDbGanttPanel
// --------------------------------------------------------------------------
class ILV_DBSGANTT_EXPORTED IliDbGanttPanel
  : public IliInspectorProperties {
public:
  IliDbGanttPanel(IlvDisplay* display, IlvSystemView transientFor = 0);
  ~IliDbGanttPanel();

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

  void dsComboIsClosed();
  void dsComboIsOpened();
  void columnsComboIsOpened(IlBoolean);
  void tableGadgetModelHasChanged(IliInspectorGadget* insp);

protected:
  void initBookRes();
  void initBookMod(IliDbGadgetPanel*);
  void initBookScl(IliDbGadgetPanel*);
  void initBookPrd();
  void initBookPro(IliDbGadgetPanel*);

  void initFromBookRes();
  void initFromBookMod(IliDbGadgetPanel*,IliDbGantt*);
  void initFromBookScl(IliDbGadgetPanel*,IliDbGantt*);
  void initFromBookPrd();
  void initFromBookPro(IliDbGadgetPanel*,IliDbGantt*);

  IlBoolean validateBookRes();
  IlBoolean validateBookMod(IliDbGadgetPanel*);
  IlBoolean validateBookScl(IliDbGadgetPanel*);
  IlBoolean validateBookPrd();
  IlBoolean validateBookPro(IliDbGadgetPanel*);

  void refreshModelList();
  void refreshDataSourceList(IlBoolean reset);
  void refreshColumnList();

  //---- Resources ----
  IliDeclInspBookAccess(IliScrolledComboBox,ResCBNDsRes,0,"CBNDsRes");
  IliDeclInspBookAccess(IliMemoryDataSource,ResCOLDISP,0,"%COLDISP_MS");
  IliDeclInspBookAccess(IliMemoryDataSource,ResCOLRES,0,"%COLRES_MS");
  IliDeclInspBookAccess(IliMemoryDataSource,ResCOLDSRES,0,"%COLDSRES_MS");
  IliDeclInspBookAccess(IliMemoryDataSource,ResDSRES,0,"%DSRES_MS");
  IliDeclInspBookAccess(IliTableGadget,ResTGColRes,0,"TGColRes");
  IliDeclInspBookAccess(IliTableGadget,ResTGColDisp,0,"TGColDisp");

  //---- Model ----
  IliDeclInspBookAccess(IliMemoryDataSource,ModMODEL,1,"MODEL_MS");
  IliDeclInspBookAccess(IliMemoryDataSource,ModDS,1,"DS_MS");

  //---- Periods ----
  IliDeclInspBookAccess(IliMemoryDataSource,PrdPERIOD,3,"PERIOD_MS");
  IliDeclInspBookAccess(IliTableGadget,PrdTGPeriod,3,"TGPeriod");

  //---- Others ----
  void addNullRow(IliTable* tbl,IlInt count);
  IliDataSource* getDataSource(const char* name);
private:
  IliDbGanttModel* _model;
  IlInt _currentModel;
  IlInt _currentDs;
  IlInt _maxColumns;
  IliDbGantt* _gantt;
  IlvStringHashTable* _hshTable;

  //---- Data Sources ----
  IliString _dsName[IliDbGanttDsCount];
  IliDataSource* _ds;
  IlBoolean _interDsToGantt;

  //---- Resources ----
  IliString* _resCols;
  IlInt _resColsCount;

  //---- Columns ----
  IliString* _cols[IliDbGanttDsCount];

  //---- Scales ----
  IlInt _yearScale;
  IlInt _monthScale;
  IlBoolean _dispFullName;
  IliDbGanttScaleType _scaleType;
  IliDbGanttScaleUnit _scaleUnit;

  //---- Grid ----
  IliColorComboBox* _colorCombo[IliDbGanttColorCount];
  IliString _ganttColor[IliDbGanttColorCount];

  //---- Period ----
  IliDbGanttPeriod* _periods;
  IlInt _periodCount;

  //---- Event ----
  IlBoolean _propagateDeletion;
  IlBoolean _propagateUpdate;
  IlBoolean _readOnly;

  IliTgFocusControler _focusCtrl[IliDbGanttPageCount+1];
};

#endif
