// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/network.h
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
// Declaration of the IliSQLNetwork class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Network_H
#define __Ili_Network_H

#ifndef __Ilv_Grapher_Grapher_H
#  include <ilviews/grapher/grapher.h>
#endif

#ifndef __Ilv_Base_Gadget_H
#  include <ilviews/base/gadget.h>
#endif

#ifndef __Ilv_Grapher_Links_H
#  include <ilviews/grapher/links.h>
#endif

#ifndef __Ilv_Gadgets_Scrollb_H
#  include <ilviews/gadgets/scrollb.h>
#endif

#ifndef __Ilv_Gadgraph_Rectsgr_H
#  include <ilviews/gadgraph/rectscgr.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ili_Schema_H
#  include <ilviews/dataccess/schema.h>
#endif

#ifndef __Ili_Netwkobj_H
#  include <ilviews/dataccess/inspect/netwkobj.h>
#endif

class ILV_DBSSQL_EXPORTED IliSQLNetwork {
public:
  IliSQLNetwork (IlvGrapher*, IlvSCGrapherRectangle* = 0);
  virtual ~IliSQLNetwork ();

  IlBoolean isShowingNestedListsContent() const {
    return _isShowingNestedListsContent;
  }
  void showNestedListsContent(IlBoolean flag) {
    _isShowingNestedListsContent = flag;
  }

  IlvDisplay* getDisplay () const { return _grapher->getDisplay(); }
  IlvGrapher* getGrapher () const { return _grapher; }

  IlvManagerObjectInteractor* getTableInteractor () const;
  IlvManagerObjectInteractor* getColumnInteractor () const;
  IlvManagerObjectInteractor* getLinkInteractor () const;

  IlvPalette* getUpdatableTablePalette () const;
  IlvPalette* getOtherTablePalette () const;
  IlvPalette* getKeyColumnPalette () const;
  IlvPalette* getOtherColumnPalette () const;

  IlBoolean isColumnDragAndDropAllowed () const { return _columnDragAndDrop; }
  void allowColumnDragAndDrop (IlBoolean f) { _columnDragAndDrop = f; }

  IlBoolean isModified () const { return _modified; }
  virtual void setModified (IlBoolean m);

  IlvRect findFreeSlot () const;

  // -- tables

  IlInt getTablesCount () const;
  IlInt getTableToken (IlInt index) const;

  IliSchema* getTableSchema (IlInt token) const;

  IlBoolean addTable (IlInt token,IliSchema* schema,const char* alias,
		      const IlvRect&);
  void removeTable (IlInt tableToken);

  IlBoolean isTableUpadatable(IlInt token) const;
  void setTableUpdatable(IlInt token, IlBoolean b);

  const char* getTableAlias (IlInt token) const;
  void setTableAlias (IlInt token, const char*);

  IlvRect getTableRect (IlInt token) const;

  IliAttributePath getTableFocusPath(IlInt token) const;
  void setTableFocusPath(IlInt token, const IliAttributePath& path);

  IlInt getSelectedTable () const;
  void setSelectedTable (IlInt token);

  void ensureTableVisible (IlInt token);

  // -- links

  IlInt getLinksCount () const;
  IlInt getLinkToken (IlInt index) const;

  IlBoolean addLink (IlInt token,
		     IlInt tableToken1, const IliAttributePath& columnName1,
		     IlInt tableToken2, const IliAttributePath& columnName2);
  void removeLink (IlInt token);

  IlBoolean getLink (IlInt token,IlInt& tableToken1,
		     IliAttributePath& columnName1,IlInt& tableToken2,
		     IliAttributePath& columnName2) const;
  IlInt getLinkToken (IlInt tableToken1,const IliAttributePath& columnName1,
		      IlInt tableToken2,
		      const IliAttributePath& columnName2) const;

  void getLinkMarkers(IlInt linkToken,IlBoolean& marker1,
		      IlBoolean& marker2) const;
  void setLinkMarkers(IlInt linkToken,IlBoolean marker1,IlBoolean marker2);

  IlInt getSelectedLink () const;

  // --

  void startOfBatch ();
  void endOfBatch ();

  void tidy ();

  void tableLost (IliTableGraphic*);
  void linkLost (IliTableLinkImage*);

  virtual void dropColumnOnColumn (IlInt srcTableToken,
				   const IliAttributePath& srcCol,
				   IlInt destTableToken,
				   const IliAttributePath& destCol);
  virtual void dropColumnOnVoid (IlInt tableToken,const IliAttributePath& col,
				 IlvPoint pt);
  virtual void tableMoved (IlInt tableToken, const IlvRect&);
  virtual void tableDoubleClicked (IlInt tableToken);
  virtual void linkDoubleClicked (IlInt linkToken);
  virtual void tableOrJoinNewSelection();
  virtual void tableMustDelete();
  virtual void linkMustDelete();
  virtual void dropAllColumns(IlInt, IlvPoint&);
protected:
  IlvGrapher* _grapher;
  IlvHashTable _tables;
  IlvHashTable _links;
  IlBoolean _modified;
  IlvManagerObjectInteractor* _tableInteractor;
  IlvManagerObjectInteractor* _columnInteractor;
  IlvManagerObjectInteractor* _linkInteractor;
  IlBoolean _columnDragAndDrop;
  IlBoolean _isShowingNestedListsContent;
  IlInt _updatesCount;
  IlvPalette* _updatableTablePalette;
  IlvPalette* _otherTablePalette;
  IlvPalette* _keyColumnPalette;
  IlvPalette* _nonKeyColumnPalette;
  IlvSCGrapherRectangle* _scgr;
  IlvManagerViewHook* _mgrHook;

  IlInt countCommonLinks (IlInt tbl1, IlInt tbl2) const;

  friend class IliColumnGraphic;
  friend class IliTableGraphic;
};

// --

#endif
