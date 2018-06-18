// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/src/dbfbasic.cpp
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
// Declaration of the DXF Entities used by the reader
// --------------------------------------------------------------------------

#include "dxfbasic.h"

const IlShort DXFGroup::STRING_TYPE  = 1;
const IlShort DXFGroup::SHORT_TYPE   = 2;
const IlShort DXFGroup::DOUBLE_TYPE  = 3;
const IlShort DXFGroup::NO_TYPE      = 0;


DXFGroup::DXFGroup()
:_code(-1),
 _type(NO_TYPE)
{
    release();
}


DXFGroup::DXFGroup(const DXFGroup& source)
:_code(-1),
 _type(NO_TYPE)
{
    release();
    _code = source._code;
    _type = source._type;
    switch (source._type) {
    case SHORT_TYPE:
	_value.shortValue   = source._value.shortValue;
	break;
    case DOUBLE_TYPE:
	_value.doubleValue = source._value.doubleValue;
	break;
    case STRING_TYPE:
	_value.stringValue = new char[strlen(source._value.stringValue) + 1];
	strcpy(_value.stringValue, source._value.stringValue);
	break;
    default:
	_code = -1;
    }
}

void
DXFGroup::release()
{
    _code = -1;
    if (_type == STRING_TYPE)
	delete [] _value.stringValue;
    _type = NO_TYPE;
    _value.stringValue = 0;
}

#if 0
// Destructeur ?
// les typedef dans views (float64, int16 ???)
// les astuces sur les fonts
// warning sur les arcs qui tournent.
#endif


void
DXFGroup::set(IlInt code, IlShort value)
{
    release();
    _code = code; 
    _type = SHORT_TYPE;
    _value.shortValue = value;
}

void
DXFGroup::set(IlInt code, IlDouble value)
{
    release();
    _code = code; 
    _type = DOUBLE_TYPE;
    _value.doubleValue = value;
}
  
void
DXFGroup::set(IlInt code, const char* value)
{
    release();
    _code = code; 
    _type = STRING_TYPE;
    _value.stringValue = new char[strlen(value) + 1];
    strcpy(_value.stringValue, value);
}

IlBoolean
DXFGroup::match(IlInt code, const char* string) const
{
    return ((code == _code) &&
	    (_type == STRING_TYPE) &&
	    !ILVSTRCASECMP(string, _value.stringValue)); 
}

// --------------------------------------------------------------------------

#if 0
// destruction des elements ?
#endif
DXFElement::DXFElement(const DXFGroup& group)
:_data(0),
 _elements(new DXFGroup*[5]),
 _size(0),
 _maxSize(5)
{
#if 0
    // copy here ???
#endif
    _elements[_size++] = new DXFGroup(group);
}

void
DXFElement::empty()
{
    for (IlInt i = 0; i < _size; i++) {
	delete _elements[i];
    }
    _size = 0;
    _data = 0;
}

void
DXFElement::grow()
{
    DXFGroup** oldGroups = _elements;
    _elements = new DXFGroup*[_maxSize * 2];
    for (IlInt i = 0; i < _size; i++) 
	_elements[i] = oldGroups[i];
    delete [] oldGroups;
    _maxSize *= 2;
}

void
DXFElement::addGroup(const DXFGroup& newGroup)
{
    if (_size == _maxSize)
	grow();
    _elements[_size++] = new DXFGroup(newGroup);
}

DXFGroup*
DXFElement::getGroup(IlInt code)  const
{
    for (IlInt i = 0; i < _size; i++) 
	if (_elements[i]->getCode() == code)
	    return _elements[i];
    return 0;
}

IlShort
DXFElement::getShort(IlInt group) const
{ 
    DXFGroup* g = getGroup(group);
    return g ? g->getShort() : 0;
}

IlDouble
DXFElement::getDouble(IlInt group) const
{ 
    DXFGroup* g = getGroup(group);
    return g ? g->getDouble() : 0.; 
}
  
const char*
DXFElement::getString(IlInt group) const
{ 
    DXFGroup* g = getGroup(group); 
    return g ? g->getString() : 0; 
}


