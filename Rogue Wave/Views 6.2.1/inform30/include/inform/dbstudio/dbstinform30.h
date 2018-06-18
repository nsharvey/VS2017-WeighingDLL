// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/dbstudio/dbstinform30.h
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
// Declaration of the IliStInFormDescription class
// Defined in library dbstinform30
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstinform30_H
#define __Ili_Dbstinform30_H

#ifndef __Ili_Dbstext_H
#  include <ilviews/dataccess/dbstudio/dbstext.h>
#endif

#ifndef __Ili_Compat_Dbstrlst_H
#  include <../inform30/include/inform/gadgets/dbstrlst.h>
#endif

// --------------------------------------------------------------------------
// IliStInFormDescription
// --------------------------------------------------------------------------
class ILV_STINFORM30_EXPORTED IliStInForm30Description
  : public IliStExtensionDescription
{
public:
  IliStInForm30Description(IlvStudio*);
  virtual ~IliStInForm30Description();

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
};

// --------------------------------------------------------------------------
// InForm 3.0 Extension For Studio
// --------------------------------------------------------------------------
class ILV_STINFORM30_EXPORTED IliInForm30Extension
  : public IliStExtension
{
public:
  IliInForm30Extension(IlvStudio* editor,const char* = 0);

  static IlInt Prep();

  static IliInForm30Extension* Get(IlvStudio*);
  static IliInForm30Extension* Make(IlvStudio*);

protected:
  ~IliInForm30Extension();
};

#endif

