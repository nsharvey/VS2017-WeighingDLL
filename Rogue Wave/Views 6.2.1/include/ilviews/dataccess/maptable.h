// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/maptable.h
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
// Declaration of the IliMapTable class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_MapTable_H
#define __Ili_MapTable_H

#ifndef __Ili_Table_H
#  include <ilviews/dataccess/table.h>
#endif

// --------------------------------------------------------------------------
// IliMapEntry
// --------------------------------------------------------------------------
struct IliMapEntry {
  IlInt value;
  const char* label;
};

// --------------------------------------------------------------------------
// IliMapTable
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliMapTable
  : public IliTable
{
public:
  IliMapTable (IlvDisplay*, const IliMapEntry* map, IlBoolean owner = IlFalse);
  IliMapTable (const IliMapTable& table);
  IliMapTable (IlvDisplay* display,IL_STDPREF istream& input);

  IliDeclareDTypeInfo(IliMapTable);
  virtual void write (IL_STDPREF ostream& output) const;

  int operator == (const IliMapTable&) const;
  IlBoolean isLanguageSensitive () const;

  void setLanguageSensitive (IlBoolean f);

  virtual void setReadOnly (IlBoolean);
  virtual IlInt getRowsCount () const;
  virtual IlBoolean getValue (IlInt rowno,IlInt colno,IliValue& val) const;
  static IliMapTable* GetBooleanMap (IlvDisplay* display);

  static const IliMapEntry* GetBooleanMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetTypeMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetAlignMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetShowMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetFitMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetLocalMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetStyleMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetLabelPosMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetNavigatorPosMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetLayoutFieldMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetOrderByMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetOperatorMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetFetchPolicyMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetBitmapTypeMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetLinkTypeMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetScaleTypeMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetScaleUnitMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetMonthMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetDayMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetWeekDayMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetHourMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetMinuteMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetPeriodUnitMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetPeriodTestMapEntries(IlInt* count = 0);
  static const IliMapEntry* GetIgnoreMapEntries(IlInt* count = 0);

  static void AtExit ();

protected:
  IlBoolean _languageSensitive;
  IlBoolean _owner;
  const IliMapEntry* _map;
  IlInt _rowsCount;

  virtual ~IliMapTable ();

private:
  void setMap (const IliMapEntry* map, IlBoolean owner);
};

// --

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliMapTable);

#endif
