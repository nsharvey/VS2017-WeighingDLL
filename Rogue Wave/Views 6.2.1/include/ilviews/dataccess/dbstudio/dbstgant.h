// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/dbstgant.h
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
// Declaration of the IliStDbGanttDescription class
// Defined in library dbstudio
// --------------------------------------------------------------------------

#ifndef __Ili_Dbstgant_H
#define __Ili_Dbstgant_H

#ifndef __Ili_Dbstext_H
#  include <ilviews/dataccess/dbstudio/dbstext.h>
#endif

#ifndef __Ili_Dbgantt_H
#  include <ilviews/dataccess/gadgets/dbgantt/dbgantt.h>
#endif

// --------------------------------------------------------------------------
// IliStDbGanttDescription
// --------------------------------------------------------------------------
class ILV_DBSGANTT_EXPORTED IliStDbGanttDescription
  : public IliStExtensionDescription
{
public:
  IliStDbGanttDescription(IlvStudio*);
  virtual ~IliStDbGanttDescription();

  //---- default extensions ----
  virtual void declareDefaultExtensions();

  //---- dbstudio options files ----
  virtual void declareOptionFileList();

  //---- Palettes ----
  virtual void generatePalettes();

  //---- Inspectors ----
  virtual void registerInspectors();

  //---- Gadgets ----
  IlvGraphic* createDbGantt();
};

// --------------------------------------------------------------------------
// DbGantt Extension For Studio
// --------------------------------------------------------------------------
class ILV_DBSGANTT_EXPORTED IliDbGanttExtension
  : public IliStExtension
{
public:
  IliDbGanttExtension(IlvStudio* editor);

  static IlInt Prep();

  static IliDbGanttExtension* Get(IlvStudio*);
  static IliDbGanttExtension* Make(IlvStudio*);

protected:
  ~IliDbGanttExtension();
};

#endif

