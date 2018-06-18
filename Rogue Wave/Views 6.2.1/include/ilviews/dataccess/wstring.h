// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/wstring.h
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
// Declaration of the IliWideCharString class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Wstring_H
#define __Ili_Wstring_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#  include <iostream>
#else
#  include <iostream.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

#ifndef __Ili_Intl_H
#  include <ilviews/dataccess/intl.h>
#endif

class IliString;

class ILV_INF_EXPORTED IliWideCharString {
public:
  inline IliWideCharString ();
  IliWideCharString (const char* str);
  IliWideCharString (const char* str, IlUInt len);
  IliWideCharString (const IliWideCharString& s);
  ~IliWideCharString ();

  inline operator const wchar_t* () const;
  inline IlUInt length () const;
  inline IlBoolean isNull () const;
  inline void nullify ();

  inline const wchar_t& operator [] (int i) const;
  inline wchar_t& operator [] (int i);

  inline const wchar_t& operator [] (long i) const;
  inline wchar_t& operator [] (long i);

  inline const wchar_t& operator [] (short i) const;
  inline wchar_t& operator [] (short i);

  IliWideCharString& operator = (const char* str);
  IliWideCharString& operator = (const IliWideCharString& s);

  inline IliWideCharString& operator << (const char* str);
  inline IliWideCharString& operator << (const IliWideCharString& s);

  IliWideCharString& appendChar (char c);
  IliWideCharString& appendWChar (wchar_t c);
  IliWideCharString& append (const char* str);
  IliWideCharString& append (const char* str, IlUInt len);
  IliWideCharString& append (const IliWideCharString& s);

  void deleteChars(IlUInt from, IlUInt to);

  IL_STDPREF istream& readLine (IL_STDPREF istream&);
  IlUShort hash () const;

protected:
  wchar_t* _buf;
  IlUInt _length;
  IlUInt _size;
  static wchar_t _badc;

  void init ();
  void reserve(IlUInt size) {
    if (size > _size)
      _reserve(size);
  }
  void _reserve(IlUInt size);
};

ILV_INF_EXPORTEDFN(int)
operator == (const IliWideCharString&, const IliWideCharString&);

ILV_INF_EXPORTEDFN(int)
operator == (const IliWideCharString&, const char*);

ILV_INF_EXPORTEDFN(int)
operator == (const char*, const IliWideCharString&);

inline int
operator != (const IliWideCharString& a, const IliWideCharString& b) {
  return !(a == b);
}

inline int
operator != (const IliWideCharString& a, const char* b) {
  return !(a == b);
}

inline int
operator != (const char* a, const IliWideCharString& b) {
  return !(a == b);
}

ILV_INF_EXPORTEDFN(IL_STDPREF ostream&)
operator << (IL_STDPREF ostream&, const IliWideCharString&);

ILV_INF_EXPORTEDFN(IL_STDPREF istream&)
operator >> (IL_STDPREF istream&, IliWideCharString&);

ILV_INF_EXPORTEDFN(IliString&)
operator << (IliString&, const IliWideCharString&);

// --

inline
IliWideCharString::IliWideCharString () {
  _size = 0;
  _length = 0;
  _buf = 0;
}

inline
IliWideCharString::operator const wchar_t* () const {
  return _buf;
}

inline IlUInt
IliWideCharString::length () const {
  return _length;
}

inline IlBoolean
IliWideCharString::isNull () const {
  return length() == 0;
}

inline void
IliWideCharString::nullify () {
  _length = 0;
  if (_buf) _buf[0] = 0;
}

inline const wchar_t&
IliWideCharString::operator [] (short i) const {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i];
  return _badc;
}

inline wchar_t&
IliWideCharString::operator [] (short i) {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i] ;
  return _badc;
}

inline const wchar_t&
IliWideCharString::operator [] (int i) const {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i];
  return _badc;
}

inline wchar_t&
IliWideCharString::operator [] (int i) {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i] ;
  return _badc;
}

inline const wchar_t&
IliWideCharString::operator [] (long i) const {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i];
  return _badc;
}

inline wchar_t&
IliWideCharString::operator [] (long i) {
  if (i >= 0 && i < (int)(unsigned int)_length)
    return _buf[i];
  return _badc;
}

inline IliWideCharString&
IliWideCharString::operator << (const char* str) {
  return append(str);
}

inline IliWideCharString&
IliWideCharString::operator << (const IliWideCharString& s) {
  return append(s);
}

#endif

