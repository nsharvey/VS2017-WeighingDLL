// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/dbstudio/dbstoldchart.h
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
// Declaration of the IliStDbOldChartDescription class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstoldchart_H
#define __Ili_Dbstoldchart_H

#ifndef __Ili_Dbstext_H
#  include <ilviews/dataccess/dbstudio/dbstext.h>
#endif

#ifndef __Ili_Dbchart_H
#  include <../inform30/include/inform/gadgets/dbchart.h>
#endif

#ifndef __Ili_Dbpiecht_H
#  include <../inform30/include/inform/gadgets/dbpiecht.h>
#endif

// --------------------------------------------------------------------------
// IliStDbOldChartDescription
// --------------------------------------------------------------------------
class ILV_DBSCHART_EXPORTED IliStDbOldChartDescription
  : public IliStExtensionDescription
{
public:
  IliStDbOldChartDescription(IlvStudio*);
  virtual ~IliStDbOldChartDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- studio callbacks ----
  virtual void registerStudioCallback();

  //---- dbstudio options files ----
  virtual void declareOptionFileList();

  //---- Palettes ----
  virtual void generatePalettes();

  //---- Inspectors ----
  virtual void registerInspectors();

  //---- Gadgets ----
  IlvGraphic* createDbOldChart ();
  IlvGraphic* createDbOldPieChart ();
};

// --------------------------------------------------------------------------
// DbChart Extension For Studio
// --------------------------------------------------------------------------
class ILV_DBSCHART_EXPORTED IliDbOldChartExtension
  : public IliStExtension
{
public:
  IliDbOldChartExtension(IlvStudio* editor,const char* = 0);

  static IlInt Prep();

  static IliDbOldChartExtension* Get(IlvStudio*);
  static IliDbOldChartExtension* Make(IlvStudio*);

protected:
  ~IliDbOldChartExtension();
};

#endif

