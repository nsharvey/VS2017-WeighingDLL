// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/serialize.cpp
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
// Definition of the Serialize and Unserialize classes
// --------------------------------------------------------------------------

#include <vpf/gui/serialize.h>
#include <string.h>

// --------------------------------------------------------------------------
Serialize::Serialize(ostream& stream)
: _stream(stream)
{
}

// --------------------------------------------------------------------------
Serialize::~Serialize()
{
}

// --------------------------------------------------------------------------
Serialize&
Serialize::operator<<(const char* string)
{
    if (string) {
	_stream << (unsigned int)strlen(string) << ' ';
	if (strlen(string))
	    _stream << string;
	else
	    _stream << 'E';
    } else
	_stream << 0 << " N"; 
    _stream << ' ';
    return *this;
}

// --------------------------------------------------------------------------
Unserialize::Unserialize(istream& stream)
: _stream(stream)
{
}

// --------------------------------------------------------------------------
Unserialize::~Unserialize()
{
}

// --------------------------------------------------------------------------
Unserialize&
Unserialize::operator>>(char*& string)
{
    unsigned int length;
    char c;
    char* ptr;
    string = 0;
    _stream >> length;

    if (length) {
	ptr = string = new char[length + 1];
	_stream.read(string, 1);
	_stream.read(string, length);
	*(string+length) = '\0';
    } else {
	_stream >> c;
	if (c == 'E') {
	    string = new char[1];
	    *string = '\0';
	}
    }
    return *this;
}
