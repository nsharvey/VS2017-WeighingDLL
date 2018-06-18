// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/gadgets/chartool.h
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
// Declaration of the IliDataSourceUsage class
// Defined in library dbchart
// --------------------------------------------------------------------------
#ifndef __Ili_Chartool_H
#define __Ili_Chartool_H

enum IliFilterValue {
  IliFilterValueFirst = 0,
  IliFilterValueLast,
  IliFilterValueBiggest,
  IliFilterValueSmallest,
  IliFilterValueSum,
  IliFilterValueAverage,
  IliFilterValueNbTag
};

#ifndef __Ili_Value_H
#  include <ilviews/dataccess/value.h>
#endif

#ifndef __Ili_gdtmodel_H
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

// --------------------------------------------------------------------------
// IliFilterValueModel
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliFilterValueModel : public IliModel
{
 public:
  IliFilterValueModel();
  virtual ~IliFilterValueModel();

  virtual const char* getName() const;
  virtual IlBoolean isSubtypeOf(const IliString& classname) const;
  virtual IlDouble filter(IlDouble pre,IlDouble val,IlInt count) const = 0;

  IliDeclareAccessorForModel(IliFilterValueModel);

  static void AtExit();
  static void AtInit();
};

// --------------------------------------------------------------------------
// Macro for IliFilterValueModel
// --------------------------------------------------------------------------
#define IliRegisterFilterValueModel(cl) \
IliFilterValueModel::RegisterModel(new cl)

// --------------------------------------------------------------------------
// IliDbSeries
// --------------------------------------------------------------------------
class IliDbSeries
{
public:
  IliDbSeries();
  virtual ~IliDbSeries();

  void setName(const IliValue&);
  const IliValue& getName() const;

  void setLabel(const char*);
  const char* getLabel() const;

  void setColor(const char*);
  const char* getColor() const;
  IlvColor* getColor(IlvDisplay*) const;

  void setPredefined(IlBoolean);
  IlBoolean isPredefined() const;

  virtual void reset();
  virtual void alloc(IlInt count);
  virtual void add(IlInt at);
  virtual IlInt getValueCount() const = 0;
  virtual IlBoolean setValue(IlDouble,IliFilterValueModel*,IlInt at = 0)=0;
  virtual IlDouble getValue(IlInt = 0) const = 0;
  virtual IlInt getCounter(IlInt = 0) const = 0;

  IlBoolean hasValue() const;

protected:
  IliValue _name;
  IliString _label;
  IliString _color;
  IlBoolean _predefined;
};

// --------------------------------------------------------------------------
// IliDbSingleSeries
// --------------------------------------------------------------------------
class IliDbSingleSeries : public IliDbSeries
{
public:
  IliDbSingleSeries();

  virtual void reset();
  virtual IlInt getValueCount() const;
  virtual IlBoolean setValue(IlDouble,IliFilterValueModel*,IlInt at = 0);
  virtual IlDouble getValue(IlInt = 0) const;
  virtual IlInt getCounter(IlInt = 0) const;

protected:
  IlDouble _value;
  IlInt _counter;
};

// --------------------------------------------------------------------------
// IliDbMultiSeries
// --------------------------------------------------------------------------
class IliDbMultiSeries : public IliDbSeries
{
public:
  IliDbMultiSeries();

  virtual void reset();
  virtual void alloc(IlInt count);
  virtual void add(IlInt at);
  virtual IlInt getValueCount() const;
  virtual IlBoolean setValue(IlDouble,IliFilterValueModel*,IlInt at = 0);
  virtual IlDouble getValue(IlInt = 0) const;
  virtual IlInt getCounter(IlInt = 0) const;

protected:
  IlDouble* _values;
  IlInt* _counters;
  IlInt _count;
};

// --------------------------------------------------------------------------
// IliDbSeriesManager
// --------------------------------------------------------------------------
class IliDbSeriesManager
{
public:
  IliDbSeriesManager();
  ~IliDbSeriesManager();

  IlInt add(IliDbSeries*, IlInt at = -1);

  void remove(const IliValue&);
  void remove(IlInt);
  void removeAll();
  void compress();

  IliDbSeries* get(const IliValue&) const;
  IliDbSeries* get(IlInt) const;

  IlInt getIndex(const IliValue&) const;
  IlInt getCount() const;

protected:
  IliDbSeries** _series;
  IlInt _count;
  IlInt _size;
};

// --------------------------------------------------------------------------
// IliDbSeriesColorModel
// --------------------------------------------------------------------------
class IliDbSeriesColorModel : public IliModel
{
public:
  IliDbSeriesColorModel();
  virtual ~IliDbSeriesColorModel();

  virtual const char* computeColor(const IliDbSeriesManager&,IlInt) const;

  IliDeclareModel();
  IliDeclareAccessorForModel(IliDbSeriesColorModel);

  void setDisplay(IlvDisplay*);
  IlvDisplay* getDisplay() const;

  static void AtExit();
  static void AtInit();
protected:
  IlvDisplay* _display;
};

// --------------------------------------------------------------------------
// Macro for IliDbSeriesColorModel
// --------------------------------------------------------------------------
#define IliRegisterDbSeriesColorModel(cl) \
  IliDbSeriesColorModel::RegisterModel(new cl)

// --------------------------------------------------------------------------
// Module
// --------------------------------------------------------------------------
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,IliFilterValueModel);

#endif







