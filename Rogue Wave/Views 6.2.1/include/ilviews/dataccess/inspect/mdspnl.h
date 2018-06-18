// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/mdspnl.h
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
// Declaration of the IliMemoryDataSourcePanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Mdspnl_H
#define __Ili_Mdspnl_H

#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif

#ifndef __Ilv_Gadgets_Toggle_H
#  include <ilviews/gadgets/toggle.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadmgr_Gadmgr_H
#  include <ilviews/gadmgr/gadmgr.h>
#endif

#ifndef __Ili_Entryfld_H
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class IliMemoryTableStructure;
class IliMemoryTableStructureInspector;
class IliMemoryTableStructureGadget;

class ILV_DBS_EXPORTED IliMemoryDataSourcePanel
  : public IliInspectorProperties
{
public:
  IliMemoryDataSourcePanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliMemoryDataSourcePanel();

  enum Page {
    page_DataSource,
    page_General,
    page_Specific,
    page_Data
  };

  enum Tag {
    mds_ReadOnly,
    mds_Global,
    mds_AllowInsert,
    mds_TransactionManager,
    mds_UsePropertyManager,
    mds_TagsCount
  };

  virtual void pagesDefine();
  virtual void pageInit(IlInt);
  virtual void pageInitFrom (IlInt,IlvGraphic*);
  virtual IlBoolean pageValidate(IlInt);
  virtual void pageApply(IlInt, IlvGraphic*);
  void pageCustomGeneralPage(IlInt pageno);


  virtual void defineTags(IlInt, IliDbGadgetPanel*);
  virtual void propertiesPageDefine(IlInt, IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt, IliDbGadgetPanel*, IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt, IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt, IliDbGadgetPanel*, IlvGraphic*);

  void initDataSourcePage();

  void onSelectorCB ();

  inline IliDataSourceTable* getDataSourceTable() const;
  inline IliDataSourceColumnTable* getDataSourceColumnTable() const;
  inline IliFormatsTable* getFormatsTable() const;
  inline IliMasksTable* getMasksTable() const;
  inline IliTransactionManagerTable* getTransMgrTable() const;

protected:
  IliDataSourceTable* _dataSourceTable;
  IliDataSourceColumnTable* _dataSourceColumnTable;
  IliFormatsTable* _formatsTable;
  IliMasksTable* _masksTable;
  IliTransactionManagerTable* _transMgrTable;
  IliMemoryTableStructure* _structure;
  IliMemoryTableStructureGadget* _tgMain;
  IliMemoryTableStructureInspector* _tgInspector;
  IliEntryField* _publicName;
  IliDbToggle* _readOnly;
  IliDbToggle* _allowInsert;
  IliDbToggle* _global;
  IliTgFocusControler _focusCtrl[2];
};

inline IliDataSourceTable*
IliMemoryDataSourcePanel::getDataSourceTable() const {
  return _dataSourceTable;
}

inline IliDataSourceColumnTable*
IliMemoryDataSourcePanel::getDataSourceColumnTable() const {
  return _dataSourceColumnTable;
}

inline IliFormatsTable*
IliMemoryDataSourcePanel::getFormatsTable() const {
  return _formatsTable;
}

inline IliMasksTable*
IliMemoryDataSourcePanel::getMasksTable() const {
  return _masksTable;
}

inline IliTransactionManagerTable*
IliMemoryDataSourcePanel::getTransMgrTable() const {
  return _transMgrTable;
}

#endif

