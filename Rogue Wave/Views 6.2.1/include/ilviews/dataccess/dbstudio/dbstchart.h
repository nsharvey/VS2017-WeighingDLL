// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/dbstchart.h
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
// Declaration of the IliChartDescription class
// Defined in library dbstchart
// --------------------------------------------------------------------------

#ifndef __Ili_Dbstchart_H
#define __Ili_Dbstchart_H

#include <ivstudio/charts/stext.h>

#ifndef __Ili_Dbstext_H
#  include <ilviews/dataccess/dbstudio/dbstext.h>
#endif

#ifndef __Ili_Chartgraphic_H
#  include <ilviews/dataccess/gadgets/chartgraphic.h>
#endif

// --------------------------------------------------------------------------
// IliStChartDescription
// --------------------------------------------------------------------------
class ILV_DBSTCHART_EXPORTED IliStChartDescription
  : public IliStExtensionDescription
{
public:
  IliStChartDescription(IlvStudio*);
  virtual ~IliStChartDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- dbstudio options files ----
  virtual void declareOptionFileList();

  //---- command file ----
  virtual void declareCommandFiles();
  virtual void registerCommands();

  //---- Palettes ----
  virtual void generatePalettes();

  //---- Inspectors ----
  virtual void registerInspectors();

  //---- Gadgets ----
  IlvGraphic* createChart ();
};

// --------------------------------------------------------------------------
// Chart Extension For Studio
// --------------------------------------------------------------------------
class ILV_DBSTCHART_EXPORTED IliChartExtension
  : public IliStExtension
{
public:
  IliChartExtension(IlvStudio* editor);

  static IlInt Prep();

  static IliChartExtension* Get(IlvStudio*);
  static IliChartExtension* Make(IlvStudio*);

protected:
  ~IliChartExtension();
};

#endif

