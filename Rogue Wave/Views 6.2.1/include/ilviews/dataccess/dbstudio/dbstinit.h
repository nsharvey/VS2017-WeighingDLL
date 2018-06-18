// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/dbstinit.h
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
// Declaration of the IliDbStudioInitializer class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstinit_H
#define __Ili_Dbstinit_H

#ifndef __Ili_Dbstext_H
#  include <ilviews/dataccess/dbstudio/dbstext.h>
#endif

#ifndef __Ili_Assist_H
#  include <ilviews/dataccess/dbstudio/assist.h>
#endif

// --------------------------------------------------------------------------
// IliStDataAccessDescription
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliStDataAccessDescription
  : public IliStExtensionDescription
{
public:
  IliStDataAccessDescription(IlvStudio*);
  virtual ~IliStDataAccessDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- studio callbacks ----
  virtual void registerStudioCallback();

  //---- dbstudio options files ----
  virtual void declareOptionFileList();

  //---- dbm files ----
  virtual void readDbmFiles(IlvDisplay*);

  //---- Font ----
  virtual void registerFontAliases(IlvDisplay*);

  //---- Property panel ----
  virtual void declareProperties();

  void addBrowserPanel();

  //---- command file ----
  virtual void declareCommandFiles();
  virtual void registerCommands();

  //---- Panels ----
  virtual void createPanels();

  //---- Palettes ----
  virtual const char* getSelectedPaletteName() const;
  virtual void generatePalettes();

  //---- License ----
  virtual IlBoolean checkLicense();

  //---- Inspectors ----
  virtual void registerInspectors();

  //---- Studio ----
  virtual void declareCodeWriter();
  virtual void declareCallbackChecker();

  //---- Gadgets ----
  IlvGraphic* createTableGadget ();
  IlvGraphic* createEntryField ();
  IlvGraphic* createDbText ();
  IlvGraphic* createTableComboBox ();
  IlvGraphic* createDbPicture ();
  IlvGraphic* createDbOptionMenu ();
  IlvGraphic* createScrolledComboBox ();
  IlvGraphic* createDbStringList ();
  IlvGraphic* createDbField ();
  IlvGraphic* createDbToggle ();
  IlvGraphic* createToggleSelector ();
  IlvGraphic* createDbNavigator ();
  IlvGraphic* createMemoryDataSource ();
  IlvGraphic* createTreeGadget ();
  IlvGraphic* createDbTimer ();
  IlvGraphic* createHtmlReporter ();
  IlvGraphic* createXml ();
};

// --------------------------------------------------------------------------
// DataAccess Extension For Studio
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDataAccessExtension
  : public IliStExtension
{
public:
  IliDataAccessExtension(IlvStudio* editor,const char* = 0);

  static IlInt Prep();

  static IliDataAccessExtension* Get(IlvStudio*);
  static IliDataAccessExtension* Make(IlvStudio*);

protected:
  ~IliDataAccessExtension();
};

#if !defined(ILI_BUILDLIBS)
  static IlInt IliModuleCLASS(IliDbStudOBJ) = IliDataAccessExtension::Prep();
#endif

#endif
