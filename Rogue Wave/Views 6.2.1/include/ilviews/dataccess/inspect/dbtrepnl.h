// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbtrepnl.h
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
// Declaration of the IliDbOldTreeGadgetPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtrepnl_H
#define __Ili_Dbtrepnl_H

#ifndef __IlvSt_Treepnl_H
#  include <ivstudio/gadgets/treepnl.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadmgr_Gadmgr_H
#  include <ilviews/gadmgr/gadmgr.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class IliDbTreeGadget;
class IliDbTreeModel;

// --------------------------------------------------------------------------
// IliDbOldTreeGadgetPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbOldTreeGadgetPanel:
  public IliInspectorProperties {
public:
  IliDbOldTreeGadgetPanel (IlvDisplay*, IlvSystemView transientFor = 0);
  ~IliDbOldTreeGadgetPanel ();

  enum IliTReePropTag {
    tre_ColumnParent = fld_TagsCount,
    tre_ColumnChildren,
    tre_ColumnBitmap,
    tre_TagsCount
  };

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pageCustomGeneralPage(IlInt);
};

// --------------------------------------------------------------------------
// IliDbTreeGadgetPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbTreeGadgetPanel
  : public IlvStITreeGadgetPanel {
public:
  IliDbTreeGadgetPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliDbTreeGadgetPanel();

  virtual void initializeEditors();
  virtual void initFrom(IlvGraphic* g);
  virtual void applyChange(IlvGraphic* g);

  IliDeclNotebookAccess(_nt,IliMemoryDataSource,DatDS_MS,0,"%DS_MS"); //
  IliDeclNotebookAccess(_nt,IliMemoryDataSource,DatCOL_MS,0,"%COL_MS");
  IliDeclNotebookAccess(_nt,IliMemoryDataSource,DatMODEL_MS,0,"%MODEL_MS");
  IliDeclNotebookAccess(_nt,IliMemoryDataSource,DatCHOIX_MS,0,"%CHOIX_MS");
  IliDeclNotebookAccess(_nt,IliTableGadget,DatTGDs,0,"TGDs");
  IliDeclNotebookAccess(_nt,IliScrolledComboBox,DatCBNModel,0,"CBNModel");

  void initData();
  void initBookData();
  void initDataBookData();
  IlBoolean applyBookData();

  virtual void defineProps ();
  virtual void doApplyChange (IlvGraphic*);
  virtual void doInitFrom (IlvGraphic*);

  //---- event ----
  void setModified();
  void newModel(IlBoolean fromCombo = IlTrue);
  void computeDataSources();

  //---- Tools ----
  IliDataSource* getDataSourceFromName(const char*) const;
protected:
  IliNotebookUsage* _nt;
  IliDbGadgetPanel* _insp;
  IliDbTreeGadget* _tree;

  //---- model ----
  IliDbTreeModel* _model;
  IlInt _dialogModel;
  IlInt _popupModel;

  //---- Data source ----
  IliString* _dsName;
  IliString* _identifierCol;
  IliString* _labelCol;
  IliString* _parentCol;
  IliString* _bitmapCol;
  IliString* _formatCol;
  IlInt _dsCount;
};

#endif
