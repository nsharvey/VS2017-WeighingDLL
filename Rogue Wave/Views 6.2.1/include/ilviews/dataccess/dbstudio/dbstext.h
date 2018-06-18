// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/dbstext.h
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
// Declaration of the IliStExtension class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstext_H
#define __Ili_Dbstext_H

#ifndef __IlvSt_Continfo_H
#  include <ivstudio/continfo.h>
#endif

#ifndef __IlvSt_Studio_H
#  include <ivstudio/studio.h>
#endif

#ifndef __IlvSt_Appcode_H
#  include <ivstudio/appli/appcode.h>
#endif

#ifndef __IlvSt_Studext_H
#  include <ivstudio/studext.h>
#endif

#ifndef __IlvSt_Insppnl_H
#  include <ivstudio/inspectors/insppnl.h>
#endif

#ifndef __Ili_Browse_H
#  include <ilviews/dataccess/dbstudio/browse.h>
#endif

// --------------------------------------------------------------------------
// IliInspectorBuilder
// --------------------------------------------------------------------------
class IliInspectorBuilder : public IlvStInspectorPanelBuilder
{
public:
  IliInspectorBuilder(IlvStudio* ed = 0) { _studio = ed; }
  virtual ~IliInspectorBuilder() {}

  virtual IlvStInspectorPanel* create(IlvDisplay*,const char*,
				      IlvSystemView = 0,
				      IlvStIAccessor::UpdateMode mode =
				      IlvStIAccessor::OnApply) = 0;
  IlvStudio* _studio;
};

// --------------------------------------------------------------------------
// IliStExtensionDescription
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliStExtensionDescription
{
public:
  IliStExtensionDescription(IlvStudio*);
  virtual ~IliStExtensionDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- new palette container type----
  virtual void declareNewPaletteContainerType();
  void addPaletteContainerType(IlvStContainerInfo*);

  //---- studio callbacks ----
  virtual void registerStudioCallback();
  void addStudioCallback(const char*,IlvStMessageCallbackType);

  //---- dbstudio options files ----
  virtual void declareOptionFileList();
  void addOptionFile(const char*);

  //---- dbm files ----
  virtual void readDbmFiles(IlvDisplay*);

  //---- editor name ----
  virtual const char* getEditorName() const;

  //---- Font ----
  virtual void registerFontAliases(IlvDisplay*);

  //---- Property panel ----
  virtual void declareProperties();
  void addPropertyString(const char*,const char*);

  //---- commands ----
  virtual void declareCommandFiles();
  void addCommandFile(const char*);

  virtual void declareCommandEnabler();

  virtual void registerCommands();
  void registerCommand(const char*,IlvStCommandConstructor);

  //---- panels ----
  virtual void createPanels();
  virtual void declareBrowserPages(IlvView* view);
  void addBrowserPage(IliDlgBrowsePage*,const char*);

  //---- Palettes ----
  virtual const char* getSelectedPaletteName() const;
  virtual void generatePalettes();
  void createPage();
  void fitContentsPage();
  void addGraphic(IlvGraphic*);

  //---- License ----
  virtual IlBoolean checkLicense();

  //---- Inspectors ----
  virtual void registerInspectors();
  void registerBuilder(const char*,IlvStInspectorPanelBuilder*);

  //---- Studio ----
  virtual void declareCodeWriter();
  void setCodeWriter(IlvStCodeWriter);

  virtual void declareCallbackChecker();
  void setCallbackChecker(IlvStCallbackChecker);

  //---- Others ----
  IlvStudio* getStudio() const;
  IlvDisplay* getDisplay() const;
  IlvSystemView getTransientFor() const;

protected:
  IlvStudio* _studio;

  //---- Palettes ----
  IlvManager* _manager;
  IlvPalette* _gadgetPalette;
  IlvPalette* _gadgetPaletteBold;
  IlInt _x;
  IlInt _y;
  IlInt _nexty;
};

// --------------------------------------------------------------------------
// Data Access Extension
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliStExtension : public IlvStExtension
{
public:
  IliStExtension(IlvStudio* editor,const char* name,
		 IliStExtensionDescription* desc);

  //---- IlvStExtension ----
  virtual IlBoolean preInitialize();
  virtual IlBoolean initializeBuffers();
  virtual IlBoolean initializeCommandDescriptors();
  virtual IlBoolean initializePanels();
  virtual IlBoolean initializeInspectors();
  virtual IlBoolean initializeModes();
  virtual IlBoolean postInitialize();

  //---- Arguments ----
  void parseParameters(IlvStudio* ed,int argc,char** argv);

protected:
  virtual ~IliStExtension();

  //---- Description ----
  IliStExtensionDescription* _description;

  //---- Arguments ----
  IlBoolean _createPalette;
};

#endif
