// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/string.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Definition of the VpfString class
// --------------------------------------------------------------------------

#include <vpf/string.h>
#include <string.h>

// --------------------------------------------------------------------------
char*
VpfStrDup(const char* s) 
{
    if (!s)
	return 0;
    char* result = new char[strlen(s) + 1];
    if (result)
	strcpy(result, s);
    return result;
}

// --------------------------------------------------------------------------
char*
VpfStrTrim(char* s)
{
    if (!s)
	return 0;

    size_t len = strlen(s);
    size_t i = len - 1;

    while ((i > 0) && ((!s[i]) || (s[i] == ' ')))
	i--;
    if (i < (len - 1))
	s[i + 1] = '\0';

    for (i = 0; i < len; i++) {
	switch(s[i]) {
	case '\n':
	case '\t':
	case '\b':
	    s[i] = '\0';
	    break;
	default:
	    ;
	}
    }
    return s;
}

// --------------------------------------------------------------------------
char*
VpfStrFullTrim(char* s)
{
    if (!s)
	return 0;

    size_t len = strlen(s);
    size_t i = len - 1;

    while ((i > 0) && ((!s[i]) || (s[i] == ' ')))
	i--;
    if (i < (len - 1))
	s[i + 1] = '\0';

    char* start = s;
    while (*s && *s == ' ')
	s++;
    strcpy(start, s);

    return start;
}

#ifndef WIN32
#include <ctype.h>
#endif
 
int
VpfStrICmp(const char* a, const char* b)
{
    if (!a || !b)
	return -1;
#ifdef WIN32
# if defined(_MSC_VER) && (_MSC_VER >= 1400) /* x86_.net2005_8.0 or higher */
    return _stricmp(a, b);
# else /* x86_.net2003_7.1 or lower, or other PC compilers */
    return stricmp(a, b);
# endif /* x86_.net2003_7.1 or lower, or other PC compilers */
#else
    while(*a && *b) {
	if (isalpha(*a)) {
	    if (tolower(*a) != tolower(*b))
		break;
	} else
	if (*a != *b)
	    break;
	a++;
	b++;
    }
    return *a - *b;
#endif
}

// --------------------------------------------------------------------------
VpfStringBuffer::VpfStringBuffer(VpfUInt size)
: VpfReference(),
  _string(size
	  ? new char[size]
	  : 0),
  _size(size)
{
    if (!_string)
	_size = 0;
}

// --------------------------------------------------------------------------
VpfStringBuffer::VpfStringBuffer(const char* string)
: VpfReference(),
  _string(0),
  _size(0)
{
    if (string) {
	_size = (VpfUInt)strlen(string) + 1;
	_string = strcpy(new char[_size], string);
    }
}

// --------------------------------------------------------------------------
VpfStringBuffer::VpfStringBuffer(VpfStringBuffer& buffer)
: VpfReference(),
  _string(0),
  _size(0)
{
    if (buffer._string) {
	_size = buffer._size;
	_string = new char[_size];
	memcpy(_string, buffer._string, _size);
    }
}

// --------------------------------------------------------------------------
VpfStringBuffer::~VpfStringBuffer()
{
    if (_string)
	delete [] _string;
}

// --------------------------------------------------------------------------
void
VpfStringBuffer::setString(const char* string)
{
    if (!string)
	return;
    if (!grow((VpfUInt)strlen(string) + 1))
	strcpy(_string, string);
}

// --------------------------------------------------------------------------
VpfStringBuffer&
VpfStringBuffer::operator +=(const char* string)
{
    if (!string)
	return *this;

    size_t l_string = _string
	? strlen(_string)
	: 0;
    if (!grow((VpfUInt)strlen(string) + l_string + 1))
	strcat(_string, string);
    return *this;
}

// --------------------------------------------------------------------------
VpfStringBuffer&
VpfStringBuffer::operator+=(char c)
{
    size_t l_string = _string
	? strlen(_string)
	: 0;
    if (!grow((VpfUInt)l_string + 2)) {
	_string[l_string] = c;
	_string[l_string + 1] = '\0';
    }
    return *this;
}

// --------------------------------------------------------------------------
int
VpfStringBuffer::grow(VpfUInt nSize)
{
    if (nSize <= _size)
	return 0;
    char* nString = new char[nSize];
    if (!nString)
	return 1;
    memcpy(nString, _string, _size);
    delete [] _string;
    _string = nString;
    _size = nSize;
    return 0;
}

// --------------------------------------------------------------------------
int
VpfStringBuffer::shrink(VpfUInt nSize)
{
    if (nSize >= _size)
	return 0;
    if (nSize <= strlen(_string))
	return 1;
    char* nString = new char[nSize];
    if (!nString)
	return 1;
    strcpy(nString, _string);
    delete [] _string;
    _string = nString;
    _size = nSize;
    return 0;
}

// --------------------------------------------------------------------------
VpfString::VpfString(VpfUInt size)
: _handle(new VpfStringBuffer(size))
{
}

// --------------------------------------------------------------------------
VpfString::VpfString(const char* string)
: _handle(new VpfStringBuffer(string))
{
}

// --------------------------------------------------------------------------
VpfString::VpfString(VpfStringBuffer& handle)
: _handle(&handle)
{
    _handle->reference();
}

// --------------------------------------------------------------------------
VpfString::~VpfString()
{
    if (_handle)
	_handle->unreference();
}

// --------------------------------------------------------------------------
VpfString::VpfString(VpfString& source)
: _handle(source._handle
	  ? new VpfStringBuffer(*source._handle)
	  : 0)
{
}

// --------------------------------------------------------------------------
VpfString::operator const char*() const
{
    return _handle->getString();
}

// --------------------------------------------------------------------------
VpfString::operator char*()
{
    return _handle->getString();
}

// --------------------------------------------------------------------------
VpfString&
VpfString::operator=(const char* string)
{
    if (_handle)
	_handle->setString(string);
    else
	_handle = new VpfStringBuffer(string);
    return *this;
}

// --------------------------------------------------------------------------
VpfString&
VpfString::operator+=(const char* string)
{
    if (_handle)
	*_handle += string;
    else
	_handle->setString(string);
    return *this;
}

// --------------------------------------------------------------------------
VpfString&
VpfString::operator+=(char c)
{
    char s[2];
    s[0] = c;
    s[1] = 0;
    if (_handle)
	*_handle += c;
    else
	_handle->setString(s);
    return *this;
}
