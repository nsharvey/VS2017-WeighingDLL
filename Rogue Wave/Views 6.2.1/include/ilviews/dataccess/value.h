// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/value.h
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
// Declaration of the IliValue class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Value_H
#define __Ili_Value_H

#ifndef __Ilv_Base_Value_H
#  include <ilviews/base/value.h>
#endif

#ifndef __Ili_Datatype_H
#  include <ilviews/dataccess/datatype.h>
#endif

#ifndef __Ili_Refcount_H
#  include <ilviews/dataccess/refcount.h>
#endif

// --

typedef void (*IliValueCallback) (IliValue&, IlAny);

class ILV_INF_EXPORTED IliTable;
class ILV_INF_EXPORTED IliInputMask;

// --

class ILV_INF_EXPORTED IliIlvValueConverter
  : public IliRefCounted
{
public:
  virtual IlBoolean toIlvValue(const IliValue&,IlvValue&,
			       IlBoolean typeOnly = IlFalse);
  virtual IlBoolean toIliValue(const IlvValue&,IliValue&,
			       IlBoolean typeOnly = IlFalse);
};

class ILV_INF_EXPORTED IliValue {
public:
  IliValue ();

  IliValue (const IliDatatype* type);

  IliValue (const IliValue& val);

  IliValue (const char* val);

  IliValue (IliByte val);

  IliValue(IlInt val);

  IliValue (IlFloat val);

  IliValue (IlDouble val);

  IliValue (const IliDecimal& val);

  IliValue (const IliDate& val);

  IliValue (const IliTime& val);

  IliValue (const IliBinary& val);

  IliValue (const IliTable* val);

  IliValue (IlAny val);

  virtual ~IliValue ();

  void read (IL_STDPREF istream& input);

  void write (IL_STDPREF ostream& output) const;

  inline const IliDatatype* getType () const;

  inline IlBoolean isNull () const;

  inline void setNull (const IliDatatype* type = 0);

  inline IlBoolean isModified () const;

  inline void setModified (IlBoolean modified);

  // -- Comparison
  int operator == (const IliValue& val) const;

  int operator != (const IliValue& val) const { return !(*this == val); }

  int operator < (const IliValue& val) const;

  int operator <= (const IliValue& val) const;

  int operator > (const IliValue& val) const;

  int operator >= (const IliValue& val) const;

  int compare (const IliValue& val) const;

  // -- Assignment

  IliValue& operator = (const IliValue& val);

  inline IliValue& operator = (const char* val);

  inline IliValue& operator = (IliByte val);

  inline IliValue& operator = (IlInt val);

  inline IliValue& operator = (IlFloat val);

  inline IliValue& operator = (IlDouble val);

  inline IliValue& operator = (const IliDecimal& val);

  inline IliValue& operator = (const IliDate& val);

  inline IliValue& operator = (const IliTime& val);

  inline IliValue& operator = (const IliBinary& val);

  IliValue& operator = (const IliTable* val);

  inline IliValue& operator = (IlAny val);

  // -- Casts

  inline operator const char* () const;

  inline operator IliByte () const;

  inline operator IlInt () const;

  inline operator IlFloat () const;

  inline operator IlDouble () const;

  inline operator IliDecimal () const;

  inline operator IliDate () const;

  inline operator IliTime () const;

  inline operator IliBinary () const;

  inline operator const IliTable* () const;

  inline operator IlAny () const;

  // -- Guarder casts

  const char* asString (const char* nvl = 0) const;

  IlBoolean asBoolean (IlBoolean nvl = IlFalse) const;

  IliByte asByte (IliByte nvl = 0) const;

  IlInt asInteger (IlInt nvl = 0) const;

  IlFloat asFloat (IlFloat nvl = 0.0) const;

  IlDouble asDouble (IlDouble nvl = 0.0) const;

  IliDecimal asDecimal (const IliDecimal& nvl) const;

  IliDecimal asDecimal () const;

  IliDate asDate (const IliDate& nvl = IliDate::GetDefault()) const;

  IliTime asTime (const IliTime& nvl = IliTime::GetDefault()) const;

  IliBinary asBinary (const IliBinary& nvl = IliBinary::GetDefault()) const;

  const IliTable* asTable (const IliTable* nvl = 0) const;

  IlAny asAny (IlAny nvl = 0) const;

  // -- Conversions

  IlBoolean import (const IliValue& val);

  inline IlBoolean importString (const char* val, IlUInt len = IliNTS);

  inline IlBoolean importBoolean (IlBoolean val);

  IlBoolean importByte (IliByte val);

  inline IlBoolean importInteger (IlInt val);

  inline IlBoolean importFloat (IlFloat val);

  inline IlBoolean importDouble (IlDouble val);

  inline IlBoolean importDecimal (const IliDecimal& val);

  inline IlBoolean importDate (const IliDate& val);

  inline IlBoolean importTime (const IliTime& val);

  inline IlBoolean importBinary (const IliBinary& val);

  IlBoolean importTable (const IliTable* val);

  inline IlBoolean importAny (IlAny val);

  // -- Formatting

  inline void format(IliString& dest, const IliFormat& fmt) const;

  inline void format(IliString& dest, const char* fmt = 0) const;

  void format(IliString& dest, const IliFormat& fmt,
	      const IliInputMask& mask) const;

  const char* getFormatted(const IliFormat& fmt) const;

  const char* getFormatted(const char* fmt = 0) const;
  const char* getFormattedEx(IliString& buf, const IliFormat& fmt) const;
  const char* getFormattedEx(IliString& buf, const char* fmt = 0) const;
  const char* getFormatted(const IliFormat& fmt,
			   const IliInputMask& mask) const;
  const char* getFormattedEx(IliString& dest,const IliFormat& fmt,
			     const IliInputMask& mask) const;

  // -- Other

  inline IlBoolean emit (IliString& dest,const IliSession* session = 0) const;
  void swap (IliValue&);
  virtual void onModify ();
  static const IliValue& GetNullValue ();

  IlBoolean assign (const IlvValue&);
  IlBoolean exportValue (IlvValue&) const;
  IlBoolean exportType (IlvValue&) const;


  static void AddConverter(IliIlvValueConverter*);
  static void RemoveConverter(IliIlvValueConverter*);

#if 0
  IlBoolean export(IlvValue& val) const {
    return exportValue(val);
  }
#endif

  static void AtInit ();
  static void AtExit ();

protected:
  const IliDatatype* _type;
  IlBoolean _isNull;
  IlBoolean _modified;
  IliValueRecord _data;

  static IliString* _buf;
  static IliValue* _nullValue;
  static IlvArray* _converters;

  IlBoolean exportTypeOrVal (IlvValue& ov,IlBoolean typeP) const;
  void iSetNull (const IliDatatype* t = 0);

  void init(const IliDatatype*);

  friend class IliDatatype;
  friend class IliModuleCLASS(IliValue);

  void realloc (IlUInt sz);
  void freebuf ();
  IlBoolean assignByConverter (const IlvValue&,IlBoolean typeOnly = IlFalse);
  IlBoolean exportByConverter (IlvValue&,IlBoolean typeOnly = IlFalse) const;
};

// --

class ILV_INF_EXPORTED IliCBValue
  : public IliValue {
public:
  IliCBValue (const IliDatatype* t = 0);
  IliCBValue (const IliCBValue& o);

  IliValue& operator = (const IliValue& o) {
    return IliValue::operator = (o);
  }
  virtual void onModify ();

  IliValueCallback getCallback () const { return _callback; }
  void setCallback (IliValueCallback cb) { _callback = cb; }

  IlAny getUserData () const { return _userData; }
  void setUserData (IlAny u) { _userData = u; }

protected:
  IliValueCallback _callback;
  IlAny _userData;
};

// -- util

static inline void
IliNullify(IlvValue& val) {
  val.empty();
  val._type = IlvValueNullType;
}

// --

inline const IliDatatype*
IliValue::getType () const {
  return _type;
}

inline IlBoolean
IliValue::isNull () const {
  return _isNull;
}

inline void
IliValue::setNull (const IliDatatype* t) {
  iSetNull(t);
  onModify();
}

inline IlBoolean
IliValue::isModified () const {
  return _modified;
}

inline void
IliValue::setModified (IlBoolean m) {
  _modified = m;
}

// -- formatting

inline void
IliValue::format (IliString& dest,const IliFormat& fmt) const {
  _type->format(*this, dest, fmt);
}

inline void
IliValue::format (IliString& dest,const char* fmt) const {
  IliFormat rfmt(fmt);
  format(dest, rfmt);
}

// -- converstions

inline IlBoolean
IliValue::importString (const char* val,IlUInt len) {
  return _type->setString(*this, val, len);
}

inline IlBoolean
IliValue::importBoolean (IlBoolean val) {
  return _type->setBoolean(*this, val);
}

inline IlBoolean
IliValue::importInteger (IlInt val) {
  return _type->setInt(*this, val);
}

inline IlBoolean
IliValue::importFloat (IlFloat val) {
  return _type->setFloat(*this, val);
}

inline IlBoolean
IliValue::importDouble (IlDouble val) {
  return _type->setDouble(*this, val);
}

inline IlBoolean
IliValue::importDecimal (const IliDecimal& val) {
  return _type->setDecimal(*this, val);
}

inline IlBoolean
IliValue::importDate (const IliDate& val) {
  return _type->setDate(*this, val);
}

inline IlBoolean
IliValue::importTime (const IliTime& val) {
  return _type->setTime(*this, val);
}

inline IlBoolean
IliValue::importBinary (const IliBinary& val) {
  return _type->setBinary(*this, val);
}

inline IlBoolean
IliValue::importAny (IlAny val) {
  return _type->setAny(*this, val);
}

// -- casts

inline
IliValue::operator const char* () const {
  return asString(0);
}

inline
IliValue::operator IliByte () const {
  return asByte(0);
}

inline
IliValue::operator IlInt () const {
  return asInteger(0);
}

inline
IliValue::operator IlFloat () const {
  return asFloat((IlFloat)0.0);
}

inline
IliValue::operator IlDouble () const {
  return asDouble(0.0);
}

inline
IliValue::operator IliDecimal () const {
  return asDecimal();
}

inline
IliValue::operator IliDate () const {
  return asDate();
}

inline
IliValue::operator IliTime () const {
  return asTime();
}

inline
IliValue::operator IliBinary () const {
  return asBinary();
}

inline
IliValue::operator IlAny () const {
  return asAny();
}

inline
IliValue::operator const IliTable* () const {
  return asTable();
}

// -- assignment

inline IliValue&
IliValue::operator = (const char* str) {
  if (getType() != IliStringType)
    setNull(IliStringType);
  importString(str);
  return *this;
}

inline IliValue&
IliValue::operator = (IliByte b) {
  if (getType() != IliByteType)
    setNull(IliByteType);
  importByte(b);
  return *this;
}

inline IliValue&
IliValue::operator = (IlInt i) {
  if (getType() != IliIntegerType)
    setNull(IliIntegerType);
  importInteger(i);
  return *this;
}

inline IliValue&
IliValue::operator = (IlFloat f) {
  if (getType() != IliFloatType)
    setNull(IliFloatType);
  importFloat(f);
  return *this;
}

inline IliValue&
IliValue::operator = (IlDouble d) {
  if (getType() != IliDoubleType)
    setNull(IliDoubleType);
  importDouble(d);
  return *this;
}

inline IliValue&
IliValue::operator = (const IliDecimal& d) {
  if (getType() != IliDecimalType)
    setNull(IliDecimalType);
  importDecimal(d);
  return *this;
}

inline IliValue&
IliValue::operator = (const IliDate& dt) {
  if (getType() != IliDateType)
    setNull(IliDateType);
  importDate(dt);
  return *this;
}

inline IliValue&
IliValue::operator = (const IliTime& dt) {
  if (getType() != IliTimeType)
    setNull(IliTimeType);
  importTime(dt);
  return *this;
}

inline IliValue&
IliValue::operator = (const IliBinary& bin) {
  if (getType() != IliBinaryType)
    setNull(IliBinaryType);
  importBinary(bin);
  return *this;
}

inline IliValue&
IliValue::operator = (IlAny a) {
  if (getType() != IliAnyType)
    setNull(IliAnyType);
  importAny(a);
  return *this;
}

inline IlBoolean
IliValue::emit (IliString& dest,const IliSession* session) const {
  return _type->emit(*this, dest, session);
}

IliModuleDECL_exp(ILV_INF_EXPORTED,IliValue);

#endif
