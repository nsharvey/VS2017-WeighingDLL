// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/sqldstbl.h
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
// Declaration of the miscellaneous classes used by
//                the IliSQLDataSourcePanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Sqldstbl_H
#define __Ili_Sqldstbl_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ili_Sqltable_H
#  include <ilviews/dataccess/sqltable.h>
#endif

#ifndef __Ili_Strtable_H
#include <ilviews/dataccess/strtable.h>
#endif

#ifndef __Ili_Tblcombo_H
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif

#ifndef __Ili_Cxncombo_H
#  include <ilviews/dataccess/gadgets/cxncombo.h>
#endif

#ifndef __Ili_Inspgad_H
#  include <ilviews/dataccess/inspect/inspgad.h>
#endif

#ifndef __Ili_Sqldspnl_H
#  include <ilviews/dataccess/inspect/sqldspnl.h>
#endif

// --------------------------------------------------------------------------
// IliSQLTableStructure
// --------------------------------------------------------------------------
class IliSQLTableStructure : public IliTable {
public:
  IliSQLTableStructure (IliSQLTable*, IliSQLDataSourcePanel* panel);
  ~IliSQLTableStructure ();

  IliSQLTable* getSQLTable () const { return _sqlTable; }

  IliTable* getTypesTable() const;
  void setTypesTable(IliTable*);

  IliQueryPage getQueryPage () const { return _queryPage; }
  void setQueryPage (IliQueryPage part);

  // -- override

  virtual void setColumnDisplayWidth (IlInt colno, IlInt width);

  virtual IlInt getRowsCount () const;
  virtual IlBoolean getValue (IlInt rowno,IlInt colno,IliValue& val) const;
  virtual IlBoolean updateRow (IlInt rowno, IliTableBuffer*);
  virtual IlBoolean deleteRow (IlInt);

  virtual IlBoolean allowColumnMove () const;
  virtual IlBoolean moveColumn (IlInt src, IlInt dest);

  IlBoolean isLastColumnNull () const;
  void adjustLastColumn ();

protected:
  IliSQLTable* _sqlTable;
  IliQueryPage _queryPage;
  IliTableHook* _hook;
  IlInt _rowsCount;
  IliTable* _typesTable;
  IliSQLDataSourcePanel* _panel;
  friend class IliSQLTableStructureHook;

  IlBoolean updateCell (IlInt rowno, IlInt colno, const IliValue& value);
  IlBoolean isColumnDefined (IlInt colno) const;

  IlInt whereCount () const;
  IlInt havingCount () const;

  void setIntVal (IliValue&,IlInt colno,IlInt intVal,
		  IlBoolean posP = IlFalse) const;

  // -- hooks

  void conjunctInserted (IlInt cno, IlBoolean whereP);
  void conjunctToBeDeleted (IlInt cno, IlBoolean whereP);
  void conjunctDeleted (IlInt cno, IlBoolean whereP);
  void tableParentPathChanged (IlInt tblno);
  void rowInserted (IlInt rowno);
  void rowDeleted (IlInt rowno);
};

// --------------------------------------------------------------------------
// IliSQLTableParams
// --------------------------------------------------------------------------
class IliSQLTableParams : public IliTable
{
public:
  IliSQLTableParams (IliSQLTable* sqlTable, IliSQLDataSourcePanel*);

  virtual IlInt getRowsCount () const;
  virtual IlBoolean getValue (IlInt rowno,IlInt colno,
			       IliValue& val) const;
  virtual IlBoolean updateRow (IlInt rowno, IliTableBuffer*);
  virtual IlBoolean insertRow (IlInt rowno, IliTableBuffer*);
  virtual IlBoolean deleteRow (IlInt);

  void reset () { tableChanged(); }

protected:
  IliSQLTable* _sqlTable;

  IlBoolean rowIsOk (IlInt rowno) const;
  IlBoolean checkBuf (IliTableBuffer* tblBuf,const char*& nm,
		      const IliDatatype*& type,const char*& dataSrc,
		      const char*& dataSrcColumn);
};

// --------------------------------------------------------------------------
// IliSQLTableStructureGadget
// --------------------------------------------------------------------------
class IliSQLTableStructureGadget : public IliTableGadget {
public:
  IliSQLTableStructureGadget (IliSQLDataSourcePanel* panel,
			      IliSQLTableStructure* data,IlBoolean owner,
			      const IlvRect& rect,IlUShort thickness,
				IlvPalette* palette);
  ~IliSQLTableStructureGadget ();

  IliSQLTable* getSQLTable () const;

  IliQueryPage getQueryPage () const;
  void setQueryPage (IliQueryPage part);

  void insertNewColumn (IlInt colno);
  void createCombo (IlInt colno);
  void createAllCombos ();
  void updateColumnFld (IlInt colno) const;
  void updateTableFld ();

  IlvDim computeMarkerWidth () const;

  virtual void drawVertRule (IlvPort* dst,IlvPos y1, IlvPos y2, IlvPos x,
			     IlInt colno, IlInt rownoTop, IlInt rownoBot,
			     IlvPalette* palette,const IlvRegion* clip) const;
  virtual void drawHorzRule (IlvPort* dst,IlvPos x1, IlvPos x2, IlvPos y,
			     IlInt rowno, IlInt colnoLeft, IlInt colnoRight,
			     IlvPalette* palette,const IlvRegion* clip) const;
  virtual void drawCorner (IlvPort* dst,IlBoolean selected,const IlvRect& bbox,
			   const IlvRegion* clip) const;
  virtual void drawMarker (IlvPort* dst,IlInt rowno,IlBoolean selected,
			   IlBoolean,const IlvRect& bbox,
			   const IlvRegion* clip) const;
  virtual IlBoolean setSelection (const IliTableSelection& selOrig);
  virtual void onSelectionChange();

  virtual void changeLanguage(const IlvSymbol*);

protected:
  IliSQLDataSourcePanel* _panel;
  IliSQLTableStructure* _data;
  IliTableComboBox* _operationsFld;
  IliTableComboBox* _orderByFld;
  IliTableComboBox* _boolFld;
  IliTableComboBox* _typeFld;
  IliTableComboBox* _alignFld;
  IliTableComboBox* _tableFld;
  IliTableComboBox* _dataSourcesFld;
  IliTableComboBox* _columnsFld;
  IliTableComboBox* _formatsFld;
  IliTableComboBox* _masksFld;
  IliEntryField* _entryFld;
  IliDatatypesTable* _typesTable;

  virtual void setHolder (IlvGadgetHolder* holder);
  virtual IliFieldItf* getCustomEditor (IlInt rowno,IlInt colno,
					IliFieldItf* fld) const;

  virtual void onEnterCell ();
  virtual IlBoolean handleKeyEvent (IlvEvent& event);
  void columnInserted (IlInt colno);
};

// --------------------------------------------------------------------------
// IliSQLTableInspector
// --------------------------------------------------------------------------
class IliSQLTableInspector : public IlvDialog 
{
public:
  IliSQLTableInspector (IliSQLTable*, IliSQLDataSourcePanel*);
  ~IliSQLTableInspector ();

  virtual void apply ();
  void open ();

  IlBoolean isReadOnly () const { return _isReadOnly; }
  void setReadOnly (IlBoolean b) { _isReadOnly = b; }

  IlBoolean isAutoSelectOn () const { return _autoSelect; }
  void setAutoSelectOn (IlBoolean b) { _autoSelect = b; }

  IlBoolean isUsingTableProperties () const { return _useTableProperties; }
  void setUseTableProperties (IlBoolean b) { _useTableProperties = b; }

  virtual void reDraw (const IlvRegion* region);
  virtual void handleResize (IlvRect& rect);

protected:
  IliSQLDataSourcePanel* _panel;
  IlBoolean _inHandleResize;
  IliSQLTable* _sqlTable;
  IliInspectorGadget* _tableGadget;
  IliStringsTable* _tablesTable;
  IlBoolean _isReadOnly;
  IlBoolean _autoSelect;
  IlBoolean _useTableProperties;
  IliSQLConnectionComboBox* _cxnCombo;
  IliTransactionManagerTable* _transMgrTable;

  void defineProps ();

  void reDefineProp(IlInt tag);
  void reDefineProps();
};

#endif
