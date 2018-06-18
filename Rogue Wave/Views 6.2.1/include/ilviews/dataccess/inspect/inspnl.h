// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/inspnl.h
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
// Declaration of the IliInspectorPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Inspnl_H
#define __Ili_Inspnl_H

#ifndef __IlvSt_Insppnl_H
#  include <ivstudio/inspectors/insppnl.h>
#endif

#ifndef __Ilv_Edit_Inspanel_H
#  include <ilviews/edit/inspanel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Maptable_H
#  include <ilviews/dataccess/maptable.h>
#endif

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

#ifndef __Ili_Strtable_H
#  include <ilviews/dataccess/strtable.h>
#endif

class ILVGDTEXPORTED IlvNotebook;
class ILV_DBS_EXPORTED IliInspectorGadget;
class IliNotebookUsage;

// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDataSourceTable
  : public IliMemoryTable {
public:
  IliDataSourceTable (IlvDisplay*,IlvGraphicHolder* = NULL);

  virtual IlBoolean select ();
  void setGraphicHolder(IlvGraphicHolder*);

protected:
  IlvGraphicHolder* _holder;
};

// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDataSourceColumnTable
  : public IliMemoryTable {
public:
  IliDataSourceColumnTable (IlvDisplay*,IlvGraphicHolder* = NULL);

  virtual IlBoolean select ();
  virtual IlBoolean isValidColumnType(IliTable*,IlInt);
  void setGraphicHolder(IlvGraphicHolder*);
  void setDataSource (const char* name);
protected:
  IlvGraphicHolder* _holder;
  IliString _dataSourceName;
};

// -----------------------------------------------------------------

class ILV_DBS_EXPORTED IliFormatsTable
  : public IliStringsTable {
public:
  IliFormatsTable (IlvDisplay* dpy);

  virtual IlBoolean select ();

  void setDatatype (const IliDatatype* type);
  void setAllDatatypes ();

protected:
  const IliDatatype* _type;
  IlBoolean _allDatatypes;
};

// -----------------------------------------------------------------

class ILV_DBS_EXPORTED IliMasksTable
  : public IliStringsTable
{
public:
  IliMasksTable (IlvDisplay* dpy);

  virtual IlBoolean select ();
};

// -----------------------------------------------------------------

class ILV_DBS_EXPORTED IliPropertyManagerTable
  : public IliMemoryTable {
public:
  IliPropertyManagerTable(IlvDisplay*,IlvGraphicHolder* = NULL);

  virtual IlBoolean select ();
  void setGraphicHolder(IlvGraphicHolder*);
  void setDataSource(const char* name);

protected:
  IlvGraphicHolder* _holder;
  IliString _dataSourceName;
};

// -----------------------------------------------------------------

class ILV_DBS_EXPORTED IliTransactionManagerTable
  : public IliMemoryTable {
public:
  IliTransactionManagerTable(IlvDisplay*,IlvGraphicHolder* = NULL);

  virtual IlBoolean select ();
  void setGraphicHolder(IlvGraphicHolder*);

protected:
  IlvGraphicHolder* _holder;
};

// -----------------------------------------------------------------

enum IliFLDPropTag {
  fld_DataSource,
  fld_Column,
  fld_AutoConnect,
  fld_AutoReDraw,
  fld_Alignment,
  fld_Format,
  fld_Mask,
  fld_MaxLen,
  fld_ReadOnly,
  fld_ForeignDataSource,
  fld_ForeignColumn,
  fld_ForeignDisplayColumn,
  fld_Constrained,
  fld_Completion,
  fld_UsePropertyManager,
  fld_TagsCount
};

// -----------------------------------------------------------------

class ILV_DBS_EXPORTED IliInspectorPanel
  : public IlvInspectorPanel
{
public:
  IliInspectorPanel (IlvManager*,const char* className,const char* title,
		     const char* icon,IlvSystemView transientFor = 0);
  IliInspectorPanel (IlvManager*,const char* className,const char* title,
		     const char* icon,const char* data,
		     const char* filename = 0, // if present, overloads data
		     IlvSystemView transientFor = 0);
  ~IliInspectorPanel ();
  virtual void reDraw (const IlvRegion* region = 0);
  virtual void handleResize (IlvRect& rect);

  IliTable* getDataSourcesTable () const;
  IliTable* getDataSourceColumnsTable () const;
  void setDataSourceName (const char*) const;

  IliTable* getFormatsTable () const;
  void setFormatsDatatype (const IliDatatype*) const;
  void setFormatsAllDatatypes () const;
  virtual void callSetFormatsDatatype ();

  IliTable* getMasksTable () const;

  virtual void init();
  virtual void applyChange(IlvGraphic*);
  virtual void initFrom(IlvGraphic*);

  virtual void defineProps (IliInspectorGadget*);
  virtual void doApplyChange (IliInspectorGadget*, IlvGraphic*);
  virtual void doInitFrom (IliInspectorGadget*, IlvGraphic*);

  virtual void onEnterCell ();
  virtual void onQuitCell ();

  static IliTable* MakeDataSourcesTable (IlvManager*);

  IlBoolean isIncluded (IliFLDPropTag);
  void includeAllTags (); // must be called before init
  void includeTag (IliFLDPropTag); // must be called before init
  void excludeTag (IliFLDPropTag); // must be called before init
  void excludeForeignTags (); // must be called before init

  static IlvNotebookPage* NewLightNotebookPage(IlvNotebook* notebook,
					       const char* label,
					       IlvBitmap* bitmap = NULL,
					       IlBoolean transparent = IlTrue,
					       const char*  filename = NULL);
  static void LightenNotebook (IlvNotebook*);

protected:
  IlBoolean _inHandleResize;
  IliDataSourceTable* _dataSourcesTable;
  IliDataSourceColumnTable* _dataSourceColumnsTable;
  IliFormatsTable* _formatsTable;
  IliMasksTable* _masksTable;
  IlBoolean _tags[fld_TagsCount];

  void initInspectorPanel();
};

// --------------------------------------------------------------------------
// IliTgFocusControler
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliTgFocusControler
{
public:
  IliTgFocusControler(IlvGadgetContainer* = 0, IliTableGadget* = 0);
  virtual ~IliTgFocusControler() {}

  void setTableGadget(IliTableGadget*);
  IliTableGadget* getTableGadget() const;

  void setGadgetContainer(IlvGadgetContainer*);
  IlvGadgetContainer* getGadgetContainer() const;

  virtual void eventFocusIn();
  virtual void eventFocusOut();

protected:
  IliTableGadget* _tableGadget;
  IlvGadgetContainer* _gadgetContainer;
  IlvButton* _defButton;
};

// --------------------------------------------------------------------------
// IliDbGadgetPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbGadgetPanel : public IliTgFocusControler
{
public:
  IliDbGadgetPanel(IlvDisplay*,IlvGadgetContainer*);
  ~IliDbGadgetPanel();

  void initialize(IlvDisplay*);

  //---- flags ----
  IlBoolean isIncluded (IliFLDPropTag);
  void includeAllTags (); // must be called before beginBuild
  void includeTag (IliFLDPropTag); // must be called before beginBuild
  void excludeTag (IliFLDPropTag); // must be called before beginBuild
  void excludeForeignTags (); // must be called before beginBuild

  //---- Gadget ----
  void beginBuildGadget(const char*,IlvGraphicCallback,IlAny);
  void endBuildGadget();

  void beginInitFrom(IlvGraphic*);
  void endInitFrom();

  void beginApply(IlvGraphic*);
  void endApply(IlvGraphic*);

  //---- properties ----
  // use defineProp between beginBuildGadget & endBuildGadget

  void defineBooleanProp (IlInt tag, const char* name);
  void defineProp (IlInt tag, const char* name, const IliDatatype*);
  void defineProp (IlInt tag, const char* name, const IliDatatype*,
		   IliTable*, IlBoolean owner = IlFalse);
  void defineProp (IlInt tag, const char* name, const IliDatatype*,
		   const IliMapEntry*, IlBoolean owner = IlFalse);
  void defineProp (IlInt tag, const char* name, const IliDatatype*,
		   IliFieldItf*, IlBoolean owner = IlFalse);
  void renameProp (IlInt tag, const char* name);

  void undefineProp (IlInt tag);
  void undefineAllProps ();
  IlBoolean isPropDefined (IlInt tag) const;

  // Use between beginInit & endInit or beginApply & endApply
  const IliValue& at (IlInt tag) const;
  IliValue& at (IlInt tag);

  //---- Data Sources & tables ----
  IliTable* getDataSourcesTable () const;
  IliTable* getDataSourceColumnsTable () const;
  IliTable* getDataSourceColumnsStrTable () const;
  IliTable* getDataSourceColumnsIntTable () const;
  IliTable* getDataSourceColumnsNumTable () const;
  void setDataSourceName (const char*) const;
  static IliTable* MakeDataSourcesTable (IlvDisplay*,IlvGraphicHolder*);

  //---- Format ----
  IliTable* getFormatsTable () const;
  void setFormatsDatatype (const IliDatatype*) const;
  void setFormatsAllDatatypes () const;
  virtual void callSetFormatsDatatype ();

  //---- Mask ----
  IliTable* getMasksTable () const;

  //---- others ----
  virtual void onEnterCell ();
  virtual void onQuitCell ();

  void addForeignColumnTag(IlInt);
  void setDataSourceTag(IlInt);
  void addDataSourceColumnTag(IlInt);

  //---- other ----
  IliInspectorGadget* getInspectorGadget();

  //---- Event modified ----
  void setModifiedEventCallback(IlvGraphicCallback,IlAny);

protected:
  //---- Tables ----
  IliDataSourceTable* _dataSourcesTable;
  IliDataSourceColumnTable* _dataSourceColumnsTable;
  IliDataSourceColumnTable* _dataSourceColumnsStrTable;
  IliDataSourceColumnTable* _dataSourceColumnsIntTable;
  IliDataSourceColumnTable* _dataSourceColumnsNumTable;
  IliFormatsTable* _formatsTable;
  IliMasksTable* _masksTable;
  IlBoolean _tags[fld_TagsCount];

  //---- page ----
  IlvGraphicHolder* _holder;
  IlvDisplay* _display;

  //---- data sources ----
  IlInt _dsTag;

  //---- columns ----
  IlInt* _dsCols;
  IlInt _dsColCount;

  //---- foreign column ----
  IlInt* _foreignCols;
  IlInt _foreignColCount;

  void defineProps();
  void initProps(IlvGraphic*);
  void applyProps(IlvGraphic*);
};

#endif
