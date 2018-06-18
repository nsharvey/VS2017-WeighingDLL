// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/string.h
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
// Declaration of the IliString class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_String_H
#define __Ili_String_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#include <cstdlib>
#include <iostream>
#else
#include <stdlib.h>
#include <iostream.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

class ILV_INF_EXPORTED IliString
{
public:
    enum Tag {
	MAXLEN = -1
    };

    inline IliString() {
	_size = 0;
	_length = 0;
	_buf = 0;
    }
    IliString(char c);
    IliString(const char* str);
    IliString(const char* str, IlUInt len);
    IliString(const IliString& s);
    ~ IliString();
    inline operator	const char*() const { return _buf ? _buf : ""; }
    inline IlUInt	length() const { return _length; }
    inline IlBoolean	isNull() const { return _length == 0; }
    inline void		nullify()
			{
			    _length = 0;
			    if (_buf)
				_buf[0] = 0;
			}
    inline
    const char& operator [](int i) const
			{
			    if (i >= 0 && (IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}
    inline
    char& operator	[](int i)
			{
			    if (i >= 0 && (IlUInt)i < _length)
				return _buf[i] ;
			    return _badc;
			}

    inline
    const char& operator [](unsigned int i) const
			{
			    if ((IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}
    inline
    char& operator	[](unsigned int i)
			{
			    if ((IlUInt)i < _length)
				return _buf[i] ;
			    return _badc;
			}
    inline
    const char& operator [](long i) const
			{
			    if (i >= 0 && (IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}
    inline
    char& operator	[](long i)
			{
			    if (i >= 0 && (IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}

    inline
    const char& operator [](unsigned long i) const
			{
			    if ((IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}
    inline
    char& operator	[](unsigned long i)
			{
			    if ((IlUInt)i < _length)
				return _buf[i];
			    return _badc;
			}
    IliString& operator	=(const char* str);
    IliString& operator	=(const IliString& str);
    IliString& operator	<<(char c);
    IliString& operator	<<(int i);
    IliString& operator	<<(unsigned u);
    IliString& operator <<(long l);
    IliString& operator	<<(unsigned long ul);
    IliString& operator	<<(double d);
    inline
    IliString& operator	<<(const char* str) { return append(str); }
    inline
    IliString& operator	<<(const IliString& str)
			{
			    return append((const char*)str);
			}

    IliString&		appendWChar(wchar_t wc);
    IliString&		append(const char* str);
    IliString&		append(const char* str, IlUInt len);
    IliString&		appendHex(unsigned long l);
    IliString&		appendExp(float d);
    IliString&		appendExp(double d);
    IliString&		prepend(char c);
    IliString&		prepend(int i);
    IliString&		prepend(unsigned u);
    IliString&		prepend(long l);
    IliString&		prepend(unsigned long ul);
    IliString&		prepend(double d);
    IliString&		prepend(const char* str);
    IliString&		prepend(const IliString& str);

    // upTo is excluded
    IlUInt		findFirst(char c,
				  IlUInt startAt = 0,
				  IlUInt upTo = (IlUInt)MAXLEN);
    IlUInt		findLast(char c,
				 IlUInt startAt = 0,
				 IlUInt upTo = (IlUInt)MAXLEN);
    void		deleteCharAt(unsigned int pos);

    IL_STDPREF istream& readLine(IL_STDPREF istream&);
    IL_STDPREF istream& read(IL_STDPREF istream&, IlUInt count);

    IlUShort		hash() const;

    void		swap(IliString&);

    void		eatNextWChar(const char*& str);

protected:
    char*		_buf;
    IlUInt		_length;
    IlUInt		_size;
    static char		_badc;

    void		init();
};

// -------------------------------------------------
#ifdef DOXYGEN_GENERATION
int operator ==(const IliString& a, const IliString& b);

int operator ==(const IliString& a, const char* b);

int operator ==(const char* a, const IliString& b);

ostream& operator <<(ostream& out, const IliString& s);

istream& operator >>(istream& input, IliString& s);

int operator !=(const IliString& a, const IliString& b);

int operator !=(const IliString& a, const char* b);

int operator !=(const char* a, const IliString& b);

#else
ILV_INF_EXPORTEDFN(int)
operator ==(const IliString&, const IliString&);
ILV_INF_EXPORTEDFN(int)
operator ==(const IliString&, const char*);
ILV_INF_EXPORTEDFN(int)
operator ==(const char*, const IliString&);
ILV_INF_EXPORTEDFN(IL_STDPREF ostream&)
operator << (IL_STDPREF ostream&, const IliString&);
ILV_INF_EXPORTEDFN(IL_STDPREF istream&)
operator >> (IL_STDPREF istream&, IliString&);

inline int
operator !=(const IliString& a, const IliString& b)
{
    return !(a == b);
}

inline int
operator !=(const IliString& a, const char* b)
{
    return !(a == b);
}

inline int
operator !=(const char* a, const IliString& b)
{
    return !(a == b);
}
#endif

#endif
