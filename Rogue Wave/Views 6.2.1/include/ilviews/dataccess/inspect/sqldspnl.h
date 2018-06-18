// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/sqldspnl.h
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
// Declaration of the IliSQLDataSourcePanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Sqldspnl_H
#define __Ili_Sqldspnl_H

#ifndef __Ilv_Gadgets_Menu_H
#  include <ilviews/gadgets/menu.h>
#endif

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

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __IlvSt_Gadpnl_H
#  include <ivstudio/inspectors/gadpnl.h>
#endif

#ifndef __Ili_Sqltable_H
#  include <ilviews/dataccess/sqltable.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Sqldtsrc_H
#  include <ilviews/dataccess/gadgets/sqldtsrc.h>
#endif

#ifndef __Ili_Network_H
#  include <ilviews/dataccess/inspect/network.h>
#endif

#ifndef __Ili_Cxncombo_H
#  include <ilviews/dataccess/gadgets/cxncombo.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class IliSQLTableStructureGadget;
class IliSQLTableStructure;
class IliSQLTableParams;
class IliSQLTableInspector;

enum IliQueryPage {
  IliNotAPage,
  IliSelectPage,
  IliHavingPage,
  IliDatatypePage,
  IliLookPage,
  IliMappingPage,
  IliParametersPage,
  IliQueryPageCount
};

enum IliShowPagePolicy {
  IliShowPageIfNeeded,
  IliShowPageAlways,
  IliShowPageNever
};

// --------------------------------------------------------------------------
// IliSQLDataSourcePanel
// --------------------------------------------------------------------------
class ILV_DBSSQL_EXPORTED IliSQLDataSourcePanel
  : public IliInspectorPanel
{
public:
  typedef IliInspectorPanel Super;

  IliSQLDataSourcePanel (IlvManager*, IlvSystemView transientFor = 0);
  ~IliSQLDataSourcePanel ();

  virtual void init ();
  virtual void applyChange (IlvGraphic*);
  virtual void initFrom (IlvGraphic*);

  IlBoolean isPageShown(IliQueryPage page) const;

  IliShowPagePolicy getShowPagePolicy(IliQueryPage page) const;
  void setShowPagePolicy(IliQueryPage page, IliShowPagePolicy policy);

  enum PropertyTag {
    NameProp,
    GlobalProp,
    AllowInsertProp,
    ReadOnlyProp,
    DistinctProp,
    UpdatableTablesProp,
    ConcurrencyControlProp,
    FetchPolicyProp,
    AutoCommitProp,
    AutoRefreshProp,
    AutoSelectProp,
    InsertNullsProp,
    DynamicSQLProp,
    UseBoundVarsProp,
    RowsCountLimitProp,
    ConnectionProp,
    QueryConjunctProp,
    TransactionManagerProp,
    UsePropertyManager,
    PropCount
  };

  IlBoolean isPropertyShown(PropertyTag tag) const;
  void showProperty(PropertyTag tag, IlBoolean flag);

  // -- internal

  void onProperties ();
  void onViewSource ();
  void onClose ();
  void onAddTable ();
  void onEditTable ();
  void onRemoveTable ();
  void onSyncroTable ();
  void onSyncroAllTables ();
  void onAppendColumn ();
  void onInsertColumn ();
  void onDeleteColumn ();
  void onEditJoin ();
  void onDeleteJoin ();
  void onSelectPage ();
  void onOpenQueryMenu (IlvPopupMenu*);

  IliSQLTable* getSQLTable () const { return _sqlTable; }
  IlBoolean validate (IlBoolean interactive = IlFalse);

  void dropColumnOnColumn (IlInt tableToken1,
			   const IliAttributePath& columnName1,
			   IlInt tableToken2,
			   const IliAttributePath& columnName2);
  void dropColumnOnVoid (IlInt tableToken,
			 const IliAttributePath& columnName,const IlvPoint&);
  void dropAllColumns(IlInt, const IlvPoint&);
  void addDropedColumn(IliSQLTableDef*,IlInt, IlInt,
		       const IliAttributePath& parentPath,const char* colname);

  void tableMoved (IlInt tableToken, const IlvRect&);
  void tableDoubleClicked(IlInt);
  void linkDoubleClicked(IlInt);
  virtual void tableToBeDeleted (IlInt tblno);
  virtual void joinToBeDeleted (IlInt jno);
  virtual void aliasesChanged ();
  virtual void tableParentPathChanged(IlInt tblno);
  virtual void columnToBeDeleted(IlInt colno);

  void inspectorDeleted () { _inspector = 0; }

  virtual void hide ();

  void newSelectionFromTableGadget();
  void newTableOrJoinSelected();

  IlInt syncronizeTable(IliSQLSession*, IliSQLTableRef* = NULL);

  inline IliSQLNetwork* getNetwork();

  inline IliDataSourceTable* getDataSourceTable() const;
  inline IliDataSourceColumnTable* getDataSourceColumnTable() const;
  inline IliFormatsTable* getFormatTable() const;
  inline IliMasksTable* getMaskTable() const;
  inline IliTransactionManagerTable* getTransMgrTable() const;

  void setModified();

protected:
  IlBoolean _busy;
  IlBoolean _inInitFrom;
  IlvNotebook* _notebook;
  IlvTextField* _nameGadget;
  IlvToggle* _globalGadget;
  IlvToggle* _allowInsertGadget;
  IliSQLNetwork* _network;
  IliTableHook* _hook;
  IliSQLTable* _sqlTable;
  IliQueryPage _queryPage;
  IlInt _bottomMargin;
  IliSQLTableStructureGadget* _structTableGadget;
  IliSQLTableStructure* _structTable;
  IliTableGadget* _paramsTableGadget;
  IliSQLTableParams* _paramsTable;
  IliSQLTableInspector* _inspector;
  IlvArray* _arrayCols;
  IlBoolean _isPageShown[IliQueryPageCount];
  IliShowPagePolicy _showPagePolicy[IliQueryPageCount];
  IliString _pageLabel[IliQueryPageCount];
  IlInt _pageIndex[IliQueryPageCount];
  IlBoolean _isPropertyShown[PropCount];
  IliDataSourceTable* _dataSourceTable;
  IliDataSourceColumnTable* _dataSourceColumnTable;
  IliFormatsTable* _formatTable;
  IliMasksTable* _maskTable;
  IliTransactionManagerTable* _transMgrTable;

  virtual void handleResize (IlvRect& rect);
  void reconfigure ();
  void initTableGadget (IliTableGadget*);
  void initStructureTable ();
  void initParametersTable ();
  void fillNetwork ();
  IlBoolean connectIfNeeded ();
  void addTable (IliSQLTableRef&);

  void impackChanges(IliSQLSession*, IlBoolean);
  void impackNew(IliSQLTableDef*,IliSQLTableDef*,IlUInt);
  void impackLost(IliSQLTableDef*,IliSQLTableDef*,IlUInt,IlBoolean);
  void impackModify(IliSQLTableDef*,IliSQLTableDef*,IlUInt,IlBoolean);

  void aliasAlreadyUsedError(IlInt tblno);
  void adjustNotebook();
  void setPageShown(IliQueryPage page, IlBoolean);
  IlBoolean canDropColumnOnCurrentPage() const;
  IliQueryPage getPageForIndex(IlInt idx) const;
  void adjustProperties();
};

inline IliSQLNetwork*
IliSQLDataSourcePanel::getNetwork() {
  return _network;
}

inline IliDataSourceTable*
IliSQLDataSourcePanel::getDataSourceTable() const {
  return _dataSourceTable;
}

inline IliDataSourceColumnTable*
IliSQLDataSourcePanel::getDataSourceColumnTable() const {
  return _dataSourceColumnTable;
}

inline IliFormatsTable*
IliSQLDataSourcePanel::getFormatTable() const {
  return _formatTable;
}

inline IliMasksTable*
IliSQLDataSourcePanel::getMaskTable() const {
  return _maskTable;
}

inline IliTransactionManagerTable*
IliSQLDataSourcePanel::getTransMgrTable() const {
  return _transMgrTable;
}

#endif
