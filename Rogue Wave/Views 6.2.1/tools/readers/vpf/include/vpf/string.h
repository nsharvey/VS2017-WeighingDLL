// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/string.h
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
// Declaration of the VpfString class
// --------------------------------------------------------------------------
#ifndef VPF_STRING_H
#define VPF_STRING_H

#include <vpf/reference.h>

char* VpfStrDup(const char* s);
char* VpfStrTrim(char* s);
char* VpfStrFullTrim(char* s);
int   VpfStrICmp(const char*, const char*);

// --------------------------------------------------------------------------
class VpfStringBuffer
: public VpfReference {
public:
    VpfStringBuffer(VpfUInt = 32);
    VpfStringBuffer(const char*);
    VpfStringBuffer(VpfStringBuffer&);
    virtual ~VpfStringBuffer();
    // ____________________________________________________________
    char* getString() { return _string; }
    const char* getString() const { return _string; }
    void setString(const char*);

    virtual VpfStringBuffer& operator +=(const char*);
    virtual VpfStringBuffer& operator +=(char);

    VpfUInt getSize() { return _size; }
protected:
    int grow(VpfUInt);
    int shrink(VpfUInt);
    char*	_string;
    VpfUInt	_size;
};

// --------------------------------------------------------------------------
class VpfString
{
public:
    VpfString(VpfUInt = 32);
    VpfString(const char*);
    VpfString(VpfStringBuffer&);
    VpfString(VpfString&);
    virtual ~VpfString();
    // ____________________________________________________________
    virtual operator const char*() const;
    virtual operator char*();

    virtual VpfString& operator =(const char*);
    virtual VpfString& operator +=(const char*);
    virtual VpfString& operator +=(char);

    VpfString* copy() { return _handle ? new VpfString(*_handle) : 0; }
    const VpfString* copy() const
	{ return _handle ? new VpfString(*_handle) : 0; }
protected:
    VpfStringBuffer* _handle;
};

#endif /* VPF_STRING_H */
