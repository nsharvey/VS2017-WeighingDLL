// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intl.h
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
// Declaration of the IliWideCharGenerator classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Intl_H
#define __Ili_Intl_H

#if !defined(__Ilv_Macros_H)
# include <ilviews/macros.h>
#endif
#if !defined(__Ili_String_H)
# include <ilviews/dataccess/string.h>
#endif
#if defined(IL_STD)
# include <cctype>
# include <cstdlib>
# include <cstring>
# include <climits>
# include <iostream>
#else  /* !IL_STD */
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <iostream.h>
#endif /* !IL_STD */

class ILV_INF_EXPORTED IliWideCharString;

const size_t ILI_MB_LEN_MAX = MB_LEN_MAX;

// --------------------------------------------------------------------------

static inline IlBoolean
IliIsMultibyte() {
  return (MB_CUR_MAX > 1);
}

ILV_INF_EXPORTEDFN(wchar_t)
IliChToWc(char c);

static inline int
IliMbLen(const char* str,size_t maxlen) {
  return mblen(str, maxlen);
}

static inline int
IliMbLen(const char* str) {
  return mblen(str, MB_CUR_MAX);
}

ILV_INF_EXPORTEDFN(const char*)
IliSafeStrStr(const char* str, const char* substr);

ILV_INF_EXPORTEDFN(IlUInt)
IliMbStringLength(const char* str);

ILV_INF_EXPORTEDFN(IlUInt)
IliMbStringLength(const char* str, IlUInt maxlen);

ILV_INF_EXPORTEDFN(wchar_t)
IliMbToChar(const char* str);

static inline int
IliMbToWc(wchar_t* pwc, const char* str, size_t len) {
  return mbtowc(pwc, str, len);
}

static inline int
IliWcToMb(char* str, wchar_t wc) {
#if defined(IL_MSVC_PORT)
#  pragma warning(push)
#  pragma warning(disable : 4996)
#endif /* IL_MSVC_PORT */
  return wctomb(str, wc);
#if defined(IL_MSVC_PORT)
#  pragma warning(pop)
#endif /* IL_MSVC_PORT */
}

ILV_INF_EXPORTEDFN(IlBoolean)
IliIsAscii(wchar_t wc);

ILV_INF_EXPORTEDFN(char)
IliWCharToChar(wchar_t wc);

static inline IlBoolean
IliIsSpace(wchar_t wc) {
  return (IliIsAscii(wc) && isspace(IliWCharToChar(wc)));
}

static inline IlBoolean
IliIsDigit(wchar_t wc) {
  return (IliIsAscii(wc) && isdigit(IliWCharToChar(wc)));
}

static inline IlBoolean
IliIsAlpha(wchar_t wc) {
  return (IliIsAscii(wc) && isalpha(IliWCharToChar(wc)));
}

static inline IlBoolean
IliIsAlnum(wchar_t wc) {
  return (IliIsAscii(wc) && isalnum(IliWCharToChar(wc)));
}

static inline IlBoolean
IliIsUpper(wchar_t wc) {
  return (IliIsAscii(wc) && isupper(IliWCharToChar(wc)));
}

static inline IlBoolean
IliIsLower(wchar_t wc) {
  return (IliIsAscii(wc) && islower(IliWCharToChar(wc)));
}

static inline wchar_t
IliToUpper(wchar_t wc) {
  return (IliIsAscii(wc) ? IliChToWc(toupper(IliWCharToChar(wc))) : wc);
}

static inline wchar_t
IliToLower(wchar_t wc) {
  return (IliIsAscii(wc) ? IliChToWc(tolower(IliWCharToChar(wc))) : wc);
}

// -----------------------------------------------------------------------

class ILV_INF_EXPORTED IliWideCharGenerator {
public:
  IliWideCharGenerator();
  virtual ~IliWideCharGenerator();

  virtual IlBoolean eof() const = 0;

  IlBoolean get(wchar_t& wchar);

  inline wchar_t next();
  inline wchar_t nextUpper();
  inline wchar_t nextLower();
  inline const char* getLastMbs() const;
  inline IlBoolean isAscii() const;
  inline IlBoolean isDigit() const;
  inline IlBoolean isSpace() const;
  inline IlBoolean isAlpha() const;
  inline wchar_t toUpper() const;
  inline wchar_t toLower() const;

  void reset();

protected:
  IliString _buffer;
  IlBoolean _endOfStringSeen;
  IlBoolean _isMulti;
  wchar_t _last;

  virtual IlBoolean wget(wchar_t& wchar);
  virtual IlBoolean getNextByte(char& c) = 0;
};

// -----------------------------------------------------------------------

class ILV_INF_EXPORTED IliIstreamWideCharGenerator
  : public IliWideCharGenerator {
public:
  IliIstreamWideCharGenerator(IL_STDPREF istream& is);

  virtual IlBoolean eof() const;
private:
  IL_STDPREF istream& _is;

  virtual IlBoolean getNextByte(char& c);
};

// -----------------------------------------------------------------------

class ILV_INF_EXPORTED IliStringWideCharGeneratorRef
  : public IliWideCharGenerator
{
public:
  IliStringWideCharGeneratorRef(const char*& str,IlUInt& len);
  IliStringWideCharGeneratorRef(const char*& str);

  wchar_t peek(int idx = 0) const;

  virtual IlBoolean eof() const;

private:
  IliString _save;
  const char*& _str;
  IlUInt& _len;
  IlUInt _l;

  virtual IlBoolean getNextByte(char& c);
};

// -----------------------------------------------------------------------

class ILV_INF_EXPORTED IliStringWideCharGenerator
  : public IliStringWideCharGeneratorRef
{
public:
  IliStringWideCharGenerator(const char* str,IlUInt len);
  IliStringWideCharGenerator(const char* str);
private:
  const char* _rstr;
  IlUInt _rlen;
};

// -----------------------------------------------------------------------

class ILV_INF_EXPORTED IliRevStringWideCharGenerator
  : public IliWideCharGenerator {
public:
  IliRevStringWideCharGenerator(const char* start);
  ~IliRevStringWideCharGenerator();

  wchar_t peek(int idx = 0) const;

  virtual IlBoolean eof() const;

private:
  IliString _save;
  const char* _start;
  const char*& _end;
  const char* _rend;
  IliWideCharString* _wstr;
  IlInt _widx;

  IlBoolean wget(wchar_t& wchar);
  virtual IlBoolean getNextByte(char& c);

  IliRevStringWideCharGenerator(const char* start,const char*& end);
};

// -----------------------------------------------------------------------

inline wchar_t
IliWideCharGenerator::next() {
  wchar_t c;
  return (get(c) ? c : (wchar_t)0);
}

inline wchar_t
IliWideCharGenerator::nextUpper() {
  wchar_t c;
  return (get(c) ? toUpper() : (wchar_t)0);
}

inline wchar_t
IliWideCharGenerator::nextLower() {
  wchar_t c;
  return (get(c) ? toLower() : (wchar_t)0);
}

inline const char*
IliWideCharGenerator::getLastMbs() const {
  return _buffer;
}

inline IlBoolean
IliWideCharGenerator::isAscii() const {
  return ((_buffer.length() == 1) && isascii(_buffer[0]));
}

inline IlBoolean
IliWideCharGenerator::isDigit() const {
  return ((_buffer.length() == 1) && isdigit(_buffer[0]));
}

inline IlBoolean
IliWideCharGenerator::isSpace() const {
  return ((_buffer.length() == 1) && isspace(_buffer[0]));
}

inline IlBoolean
IliWideCharGenerator::isAlpha() const {
  return ((_buffer.length() == 1) && isalpha(_buffer[0]));
}

inline wchar_t
IliWideCharGenerator::toUpper() const {
  return ((_buffer.length() == 1)? IliChToWc(toupper(_buffer[0])) : _last);
}

inline wchar_t
IliWideCharGenerator::toLower() const {
  return ((_buffer.length() == 1)? IliChToWc(tolower(_buffer[0])) : _last);
}

// -----------------------------------------------------------------------

#ifdef NOWCHARLIT
#  define ILVWCH(c,wc) ((wchar_t)c) // IliChToWc((char)c)
#else
#  define ILVWCH(c,wc) wc
#endif

#endif
