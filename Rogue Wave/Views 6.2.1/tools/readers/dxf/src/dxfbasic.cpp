// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/src/dxfbasic.cpp
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
// Definition of the DXF Entities used by the reader
// --------------------------------------------------------------------------

#include <ilviews/base/memory.h>

#include "dxfbasic.h"

#ifdef ILVSTD
#include <cstring>
using namespace std;
#else
#include <string.h>
#endif

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

DXFGroup::~DXFGroup()
{
    release();
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
    size_t length = strlen(value) + 1;
    _value.stringValue = new char[length];
    strcpy(_value.stringValue, value);
    if ((length > 1) && (_value.stringValue[length - 2] == 13))
	_value.stringValue[length - 2] = 0;
}

IlBoolean
DXFGroup::match(IlInt code, const char* string) const
{
    return ((code == _code) &&
	    (_type == STRING_TYPE) &&
	    !ILVSTRCASECMP(string, _value.stringValue)); 
}

// --------------------------------------------------------------------------

DXFElement::DXFElement(const DXFGroup& group)
:_data(0),
 _elements(new DXFGroup*[5]),
 _size(0),
 _maxSize(5),
 _palette(0),
 _entities(0)
{
    _elements[_size++] = new DXFGroup(group);
}

DXFElement::DXFElement(const DXFElement& source)
:_data(source._data),
 _elements(0),
 _size(source._size),
 _maxSize(source._maxSize),
 _palette(source._palette),
 _entities(source._entities)
{
    if (_palette)
	_palette->lock();
    _elements = new DXFGroup*[_maxSize];
    for (int i = 0; i < _size; i++) {
	_elements[i] = new DXFGroup(*source._elements[i]);
    }
}

DXFElement::~DXFElement()
{
    empty();
    delete [] _elements;
}

void
DXFElement::empty()
{
    for (IlInt i = 0; i < _size; i++) {
	delete _elements[i];
    }
    _size = 0;
    _data = 0;
    if (_palette) {
	_palette->unLock();
	_palette = 0;
    }
    if (_entities)
	delete _entities;
}

void
DXFElement::setPalette(IlvPalette* palette)
{
    _palette = palette;
    _palette->lock();
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

// --------------------------------------------------------------------------

DXFElementList::DXFElementList(DXFElement* element)
:_elements(new DXFElement*[5]),
 _size(0),
 _maxSize(5),
 _data(0)
{
    if (element)
	_elements[_size++] = element;
}

DXFElementList::~DXFElementList()
{
    for (int i = 0; i < _size; i++)
	delete _elements[i];
    delete [] _elements;
}

void
DXFElementList::grow()
{
    DXFElement** oldElements = _elements;
    _elements = new DXFElement*[_maxSize * 2];
    for (IlInt i = 0; i < _size; i++) 
	_elements[i] = oldElements[i];
    delete [] oldElements;
    _maxSize *= 2;
}

void
DXFElementList::addElement(DXFElement* element)
{
    if (_size == _maxSize)
	grow();
    _elements[_size++] = element;
}
// --------------------------------------------------------------------------

DXFCoordinateArray::DXFCoordinateArray()
:_points(new IlvCoordinate[5]),
 _size(0),
 _maxSize(5)
{
}

DXFCoordinateArray::~DXFCoordinateArray()
{
    delete [] _points;
}
void
DXFCoordinateArray::reset()
{
    _size = 0;
}

void
DXFCoordinateArray::grow()
{
    IlvCoordinate* oldPoints = _points;
    _points = new IlvCoordinate[_maxSize * 2];
    for (IlInt i = 0; i < _size; i++) 
	_points[i].move(oldPoints[i].x(), oldPoints[i].y());
    delete [] oldPoints;
    _maxSize *= 2;
}

void
DXFCoordinateArray::addElement(const IlvCoordinate& point)
{
    if (_size == _maxSize)
	grow();
    _points[_size++].move(point.x(), point.y());
}

