// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/param.h
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
// Declaration of the IliParameter class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Param_H
#define __Ili_Param_H

#ifndef __Ili_Value_H
#  include <ilviews/dataccess/value.h>
#endif

class ILVVWSEXPORTED IlvGadgetHolder;

class ILV_INF_EXPORTED IliParameter : public IliCollectable
{
public:
  IliParameter (const char* name,const IliDatatype* type,IlInt maxlen = -1);
  IliParameter (const IliParameter&);
  IliParameter (IL_STDPREF istream&);
  ~IliParameter();

  IliDeclareTypeInfo(IliParameter);
  virtual void write (IL_STDPREF ostream&) const;
  int operator == (const IliParameter&) const;

  const char* getName () const { return _name; }
  void setName (const char* n) { _name = n; }

  const IliDatatype* getType () const { return _type; }
  void setType (const IliDatatype*);

  IlInt getMaxlen () const { return _maxlen; }
  void setMaxlen (IlInt m) { _maxlen = m; }

  const char* getDataSourceName () const;
  void setDataSourceName (const char*);

  const char* getDataSourceColumnName () const;
  virtual void setDataSourceColumnName (const char*);

  IliValue getDataSourceValue (IlvGadgetHolder*) const;

  const IliValue& getValue () const { return _value; }
  IlBoolean setValue (const IliValue& v);

  IlvValueInterface* getItf() const;
  void setItf(IlvValueInterface*);

protected:
  IliString _name;
  const IliDatatype* _type;
  IlInt _maxlen;
  IliValue _value;
  IliString _dataSourceName;
  IliString _dataSourceColumn;
  IlvValueInterface* _itf;
};

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliParameter);

IliDeclareCollection(INF,IliParameterCollection,IliParameter);

#endif
