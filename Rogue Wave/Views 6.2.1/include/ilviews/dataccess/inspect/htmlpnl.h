// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/htmlpnl.h
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
// Declaration of the IliHTMLReporterPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Htmlpnl_H
#define __Ili_Htmlpnl_H

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class IliHTMLReporter;
class IliXML;

enum IliHTMLReporterPage {
IliHTMLReporterDocPage = 0,
IliHTMLReporterTblPage,
IliHTMLReporterFrtPage,
IliHTMLReporterPageCount
};

enum IliXMLPage {
IliXMLConnPage = 0,
IliXMLImpoPage,
IliXMLExpoPage,
IliXMLStrePage,
IliXMLPageCount
};

// --------------------------------------------------------------------------
// IliHTMLReporterPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliHTMLReporterPanel
  : public IliInspectorProperties
{
 public:
  IliHTMLReporterPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliHTMLReporterPanel();

  //---- Defines pages ----
  virtual void pagesDefine();

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pageCustomGeneralPage(IlInt);

  //---- Events ----
  void dataSourceHasChanged(IliInspectorGadget*);

protected:
  void initBookDoc(IliDbGadgetPanel*);
  void initBookTbl(IliDbGadgetPanel*);
  void initBookFrt(IliDbGadgetPanel*);

  void initFromBookDoc(IliDbGadgetPanel*,IliHTMLReporter*);
  void initFromBookTbl(IliDbGadgetPanel*,IliHTMLReporter*);
  void initFromBookFrt(IliDbGadgetPanel*,IliHTMLReporter*);

  IlBoolean validateBookDoc(IliDbGadgetPanel*);
  IlBoolean validateBookTbl(IliDbGadgetPanel*);
  IlBoolean validateBookFrt(IliDbGadgetPanel*);

  void convertColor(const char*,IliString&);

private:
  //---- Document properties ----
  IliString _filename;
  IliString _dsName;
  IliString _title;
  IliString _copyright;
  IliString _background;
  IlInt _model;
  IlBoolean _tableOfContents;
  IlBoolean _comments;

  IliColorComboBox* _colorCombo;
  IliDialogComboBox* _fileCombo;

  //---- Table of contents properties ----
  IliString _tocColumnName;
  IliString _tocTitle;
  IlBoolean  _tocAtBegining;

  //---- First page properties ----
  IliString _firstTitle;
  IliString _firstPicture;

  IliDialogComboBox* _pictureCombo;
};

// --------------------------------------------------------------------------
// IliXMLPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliXMLPanel
  : public IliInspectorProperties
{
 public:
  IliXMLPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliXMLPanel();

  //---- Defines pages ----
  virtual void pagesDefine();

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pageCustomGeneralPage(IlInt);

  //---- Events ----
  void modelHasChanged(IliInspectorGadget*);
  void initializePropertiesModel(IliXMLModel*,IliPropertiesManager&,
				 IliXMLPage);

protected:
  void initBookConn(IliDbGadgetPanel*);
  void initBookImpo(IliDbGadgetPanel*);
  void initBookExpo(IliDbGadgetPanel*);
  void initBookStre(IliDbGadgetPanel*);

  void initFromBookConn(IliDbGadgetPanel*,IliXML*);
  void initFromBookImpo(IliDbGadgetPanel*,IliXML*);
  void initFromBookExpo(IliDbGadgetPanel*,IliXML*);
  void initFromBookStre(IliDbGadgetPanel*,IliXML*);

  IlBoolean validateBookConn(IliDbGadgetPanel*);
  IlBoolean validateBookImpo(IliDbGadgetPanel*);
  IlBoolean validateBookExpo(IliDbGadgetPanel*);
  IlBoolean validateBookStre(IliDbGadgetPanel*);

  void convertColor(const char*,IliString&);

private:
  //---- Connexion ----
  IliString _dsName;
  IlInt _importModel;
  IlInt _exportModel;
  IlInt _streamModel;
  IlBoolean _autoExport;

  //---- Export properties ----
  IliPropertiesManager _propsExport;

  //---- Import properties ----
  IliPropertiesManager _propsImport;

  //---- Import properties ----
  IliPropertiesManager _propsStream;
};

#endif
