// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/typetag.h
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
// Declaration of the IliTypeTag type and assorted functions
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Typetag_H
#define __Ili_Typetag_H

#ifndef __Ilv_Base_Array_H
#  include <ilviews/base/array.h>
#endif

#ifndef __Ili_MapTable_H
#  include <ilviews/dataccess/maptable.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

enum IliTypeTag {
  IliNullTypeTag,
  IliStringTypeTag,
  IliBooleanTypeTag,
  IliByteTypeTag,
  IliIntegerTypeTag,
  IliFloatTypeTag,
  IliDoubleTypeTag,
  IliDecimalTypeTag,
  IliDateTypeTag,
  IliBinaryTypeTag,
  IliTimeTypeTag,
  IliLongStringTypeTag,
  IliLongBinaryTypeTag,
  IliTypeTagCount
};

ILV_INF_EXPORTEDFN(IliTypeTag)
IliTypeToTag(const IliDatatype*);

ILV_INF_EXPORTEDFN(const IliDatatype*)
IliTagToType(IliTypeTag);

// ----------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypesTable : public IliTable
{
public:
  IliDatatypesTable(IlvDisplay*);
  ~IliDatatypesTable();

  virtual void clearRows();
  virtual IlInt getRowsCount() const;
  virtual IlBoolean getValue(IlInt rowno,IlInt colno,IliValue& value) const;

  void addStandardTypes();
  void addClosedTypes();

  IlInt getTypeCount() const;
  const IliDatatype* getTypeAt(IlInt idx) const;

  void addType(const IliDatatype*);
  void removeType(const IliDatatype*);

  IlInt getStandardTypeCount() const;
  IlInt getClosedTypeCount() const;
  IlInt getOtherTypeCount() const;

  void onTypeEvent(const IliDatatype* type, IlBoolean enter);

private:
  IlvArray _closedTypes;
  IlBoolean _hasStandardTypes;
  IlBoolean _hasClosedTypes;
  IliDatatypeCollection _otherTypes;

  void sortClosedTypes();
};

#endif
