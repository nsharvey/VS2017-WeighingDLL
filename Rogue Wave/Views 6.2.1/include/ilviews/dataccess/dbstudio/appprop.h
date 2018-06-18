// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/appprop.h
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
// Declaration of the IliApplicationProperties class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Appprop_H
#define __Ili_Appprop_H

#ifndef __IlvSt_Edappli_H
#include <ivstudio/edappli.h>
#endif

#ifndef __IlvSt_Stdesc_H
#  include <ivstudio/stdesc.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

class ILV_DBS_EXPORTED IliApplicationProperties
{
public:
  IliApplicationProperties ();
  ~IliApplicationProperties ();

  static void InstallNumbers (IlvStAppDescriptor*);
  static void InstallDates (IlvStAppDescriptor*);
  static void InstallFormatAliases (IlvStAppDescriptor*, IlvDisplay*);
  static void InstallMaskAliases (IlvStAppDescriptor*, IlvDisplay*);

  static IliTable* MakeFormatAliasesTable (IlvDisplay*);
  static void ReadFormatAliasesTable (IlvStAppDescriptor* app,IliTable* frm);
  static void RemoveApplicationAliasesFormat ();
  static void InstallNewAliasesFormat (IliTable* formats);

  static IliTable* MakeMaskAliasesTable (IlvDisplay*);
  static void ReadMaskAliasesTable (IlvStAppDescriptor* app,IliTable* masks);
  static void RemoveApplicationMasks ();
  static void InstallNewMasks (IliTable* masks);

  static const char* GetStringProp(IlvStAppDescriptor*,const char* section,
				   const char* topic);
  static void SetStringProp (IlvStApplication* appli,const char* section,
			     const char* topic,const char* val);
  static void RemoveOldStringProp(IlvStApplication* appli,const char* section,
				  const char* topic);
  static void RemoveStringProps (IlvStApplication* appli,const char* section);
  static void RemoveAllStringProps (IlvStApplication*,const char* section);

  static IliTable* MakeDefaultTable (IlvDisplay* dpy);
  static void ReadDefaultTable (IlvStAppDescriptor*,IliTable*,const char*);

  const char* pack (const char*, IlInt i);

protected:
  IliString _buffer;
};

// Section names
const char* const IlvNmInternationalSection = "International";

// Numbers
const char* const IlvNmDecimalPoint = "DecimalPoint";
const char* const IlvNmThousandsSeparator = "ThousandsSeparator";
const char* const IlvNmCurrencySymbol = "CurrencySymbol";
const char* const IlvNmCurrencyPosition = "CurrencyPosition";

// Dates
const char* const IlvNmDateSeparator = "DateSeparator";
const char* const IlvNmTimeSeparator = "TimeSeparator";
const char* const IlvNmDateFormat = "DateFormat";

#endif
