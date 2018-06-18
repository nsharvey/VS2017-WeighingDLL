// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/dbstsql.h
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
// Declaration of the IliStSQLDescription class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstsql_H
#define __Ili_Dbstsql_H

#include <ilviews/gadgets/toolbar.h>

#ifndef __Ili_Dbstinit_H
#  include <ilviews/dataccess/dbstudio/dbstinit.h>
#endif

#ifndef __Ili_Sqlrepvw_H
#  include <ilviews/dataccess/gadgets/sqlrepvw.h>
#endif

#ifndef __Ili_Session_H
#  include <ilviews/dataccess/dbms/session.h>
#endif

#ifndef __Ili_Cxncombo_H
#  include <ilviews/dataccess/gadgets/cxncombo.h>
#endif

#ifndef __Ili_Sqldtsrc_H
#  include <ilviews/dataccess/gadgets/sqldtsrc.h>
#endif

#ifndef __Ili_Netwkobj_H
#  include <ilviews/dataccess/inspect/netwkobj.h>
#endif

#ifndef __Ili_Filename_H
#  include <ilviews/dataccess/filename.h>
#endif

#ifndef MAKE_DBSTDQL_MODULE

// --- DbLink driver bindings ---
#if defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
#include <ildblink/dblink.h>
static IldDbms* ILVCALLBACK
NewDbms (const char* db, const char* param) {
  return IldNewDbms(db, param);
}
static void
BindDbmsDrivers() {
  IliSQLSession::SetNewDbmsFunction(NewDbms);
}
#else // defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
static void BindDbmsDrivers() {}
#endif // defined(ILI_CUSTOM_NEW_DBMS_NEEDED)

#endif

// --------------------------------------------------------------------------
// IliDsAssistant
// --------------------------------------------------------------------------
class IliDsAssistant
: public IlvGadgetContainer {
public:
  IliDsAssistant(IlvDisplay*,const char*,const char*,const IlvRect&,
		 IlUInt,IlBoolean,IlBoolean,IlvSystemView);
  IliDsAssistant(IlvAbstractView*,const IlvRect&,IlBoolean,IlBoolean);
  ~IliDsAssistant();

  void init();
  void initializeResize();
  void initialize(IlvStudio*);

  void refresh(const char*);

  //---- Event ----
  void bnConnect();
  void bnDrop();
  void bnCreate();
  void bnEdit();
  void bnData();
  void bnDebug();
  void bnExport();
  void bnImport();

  //---- Tools ---
  char** getTableList(IlInt&);
  char** getColumnList(const char*,IlInt&);
  void eventDragDrop(IlvEvent&);
  void eventCreate(IlInt,IlInt);
  IliDataSource* createDataSource(const char*,IlInt*,IlInt,IlInt,IlInt);

  virtual void handleInput(IlvEvent&);

  //---- SQL cmd ----
  IlBoolean submitSQL (const char* stmt,IliErrorMessage& err) const;
  IlBoolean dropTable (const IliSQLTableRef&,IliErrorMessage& err) const;
  IlBoolean commit (IliErrorMessage& err) const;
  IlBoolean impactTable (const IliSQLTableDef* tblDef);
  IlBoolean createTable (const IliSQLTableDef* tblDef,
			 IliErrorMessage& err) const;
  IlBoolean tableExists (const IliSQLTableRef& tblRef) const;
  IlBoolean startTransaction (IliErrorMessage& err) const;
  void editTable(IliSQLTableDef* tblDef);
  IlBoolean saveAsDlg (IliSQLTableDef* tblDef);
  IlBoolean saveAs (IliFileName fn,IliSQLTableDef* tblDef);

  IlBoolean load (IliFileName fn);
  void readData (IL_STDPREF istream& is);

protected:
  IliTreeClassesGadget* _tree;
  IliSQLSession* _session;
  IliString _owner;

  //---- Tables ---- ... + Synonyms
  IlInt _tableCount;
  char** _tables;
  //---- Synonym names are stored in this hash table.
  // To check if a name stored in _tables is a table name, or a synonym
  // name, we check if that entry exists in the hash table. If it is there,
  // the name is a synonym, else, it's a table.
  IlStringHashTable* _hashSynonyms ;
  IlvBitmap* _synBitmap ;

  //---- Columns ----
  IlInt _sizeBuffer;
  char** _buffer;

  //---- Drag and drop ----
  IlvStudio* _mstudio;
  IlvManager* _manager;
  IlBoolean  _dragAndDrop;
  IlvView*    _target;
  IlInt      _dx, _dy;
  IlvPoint    _position;

  IlBoolean getSelectedItemBBox(IlvRect& rect,const IlvTransformer* t = 0);
  IlBoolean isValidBuffer(IlBoolean bell = IlFalse);
  IlBoolean inTarget(const IlvPoint& p);
  void doIt(IlvView* target, const IlvPoint& where);
  void drawGhost(const IlvPoint& point);
  IlInt* getSelection(IliString&,IlInt&);
  IlvManager* getCurrentManager();
  void getTableOwner(IliSQLSession* session,IliString& owner);

  //---- Other ----
  IlBoolean connectSession();
  void refreshSessionParams();
  void disconnectSession();

  //---- Tables ----
  void resetTablesBuffer();
  inline
  IlBoolean isSynonym(const char* name) const ;

  //---- Columns ----
  void resetBuffer();

  //---- For SQL commands ----
  IlBoolean getSelectedTable(IliSQLTableRef& tblref);
  void displayMsg(const char* key,const char* def,const char* arg = 0,
		  IlBoolean isError = IlTrue);
  IlBoolean answer(const char* key,const char* def,const char* arg = 0);

  //---- Display tree of SQL tables ----
  void displayTree() ;
};

inline
IlBoolean IliDsAssistant::isSynonym(const char* name) const
{
  return (_hashSynonyms && _hashSynonyms->find(IL_CONSTCAST(char*, name))) ;
}

// --------------------------------------------------------------------------
// IliStSQLDescription
// --------------------------------------------------------------------------
class ILV_DBSSQL_EXPORTED IliStSQLDescription
  : public IliStExtensionDescription
{
public:
  IliStSQLDescription(IlvStudio*);
  virtual ~IliStSQLDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- new palette container type----
  virtual void declareNewPaletteContainerType();

  //---- studio callbacks ----
  virtual void registerStudioCallback();

  //---- dbstudio options files ----
  virtual void declareOptionFileList();

  //---- dbm files ----
  virtual void readDbmFiles(IlvDisplay*);

  //---- command file ----
  virtual void declareCommandFiles();
  virtual void declareCommandEnabler();
  virtual void registerCommands();

  //---- panels ----
  virtual void createPanels();
  virtual void declareBrowserPages(IlvView* view);

  //---- Palettes ----
  virtual void generatePalettes();

  //---- License ----
  virtual IlBoolean checkLicense();

  //---- Inspectors ----
  virtual void registerInspectors();

  //---- Studio ----
  virtual void declareCodeWriter();

  //---- Gadgets ----
  IlvGraphic* createSQLDataSource ();
};

// --------------------------------------------------------------------------
// SQL Extension For Studio
// --------------------------------------------------------------------------
class ILV_DBSSQL_EXPORTED IliSQLExtension
  : public IliStExtension
{
public:
  IliSQLExtension(IlvStudio* editor,const char* = 0);

  static IliSQLExtension* Get(IlvStudio*);
  static IliSQLExtension* Make(IlvStudio*);

protected:
  ~IliSQLExtension();
};

#endif

