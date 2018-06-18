// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/systype.h
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
// Declaration of the IliSQLSystemType and IliCxnParamRec classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Systype_H
#define __Ili_Systype_H

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

#include <ildblink/ilddbms.h>

typedef IldDbms* (*IliSQLNewDbmsFunction) (const char* dbms, const char* par);

typedef void     (*IliSQLTracePrintFunction) (const char* text);
typedef void     (*IliSQLCallHookFn)(IlAny sid, IlAny cid);

class ILV_DBI_EXPORTED IliSQLTraceOptions {
public:
  IlBoolean _traceEnabled;
  IlBoolean _traceConnect;
  IlBoolean _traceCursors;
  IlBoolean _traceSql;
  IliSQLTracePrintFunction _printFn;

  IliSQLTraceOptions();
};

// --

class IliSQLSystemType {
public:
  enum IliDefaults {
    IlvDefaultPrecision = 0,
    IlvDefaultScale     = 0
  };

  inline IliSQLSystemType (const char* t = 0,IlInt p = IlvDefaultPrecision,
			   IlInt s = IlvDefaultScale);

  inline const char* getTypeName () const;
  inline void setTypeName (const char*);

  inline IlInt getPrecision () const;
  inline IlBoolean hasPrecision () const;
  inline void setPrecision (IlInt precision);

  inline IlInt getScale () const;
  inline IlBoolean hasScale () const;
  inline void setScale (IlInt scale);

protected:
  IliString _typeName;
  IlInt _precision;
  IlInt _scale;
};

// --

enum IliStatementType {
  IliDMLStmt,
  IliDDLStmt,
  IliIDXStmt,
  IliPROCStmt
};

// --

class ILV_DBI_EXPORTED IliCxnParamRec {
public:
  IliString user;
  IliString passwd;
  IliString database;
  IliString options;

  inline IliCxnParamRec ();
  inline IliCxnParamRec (const IliCxnParamRec&);
  inline IliCxnParamRec& operator = (const IliCxnParamRec&);
  inline int operator == (const IliCxnParamRec&);
};

// --

inline
IliSQLSystemType::IliSQLSystemType (const char* t,IlInt p,IlInt s) {
  _typeName = t;
  _precision = p;
  _scale = s;
}

inline const char*
IliSQLSystemType::getTypeName () const {
  return _typeName;
}

inline void
IliSQLSystemType::setTypeName (const char* t) {
  _typeName = t;
}

inline IlInt
IliSQLSystemType::getPrecision () const {
  return _precision;
}

inline IlBoolean
IliSQLSystemType::hasPrecision () const {
  return _precision > IlvDefaultPrecision;
}

inline void
IliSQLSystemType::setPrecision (IlInt precision) {
  _precision = precision;
}

inline IlInt
IliSQLSystemType::getScale () const {
  return _scale;
}

inline IlBoolean
IliSQLSystemType::hasScale () const {
  return _scale != IlvDefaultScale;
}

inline void
IliSQLSystemType::setScale (IlInt scale) {
  _scale = scale;
}

// --

inline
IliCxnParamRec::IliCxnParamRec ()
{}

inline
IliCxnParamRec::IliCxnParamRec (const IliCxnParamRec& o)
  : user(o.user),passwd(o.passwd),database(o.database),options(o.options) {
}

inline IliCxnParamRec&
IliCxnParamRec::operator = (const IliCxnParamRec& o) {
  user = o.user;
  passwd = o.passwd;
  database = o.database;
  options = o.options;
  return *this;
}

inline int
IliCxnParamRec::operator == (const IliCxnParamRec& o) {
  return user == o.user
    && passwd == o.passwd
    && database == o.database
    && options == o.options;
}

#endif
