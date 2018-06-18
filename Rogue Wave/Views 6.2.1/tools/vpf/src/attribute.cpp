// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/attribute.cpp
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
// Definition of the VpfValue and VpfAttribute classes
// --------------------------------------------------------------------------

#include <vpf/attribute.h>
#include <vpf/string.h>
#if defined(VPFSTD)
#include <cstdio>
VPFSTDUSE
#else
#include <stdio.h>
#endif

// --------------------------------------------------------------------------
VpfValue::VpfValue(const char* description, VpfInt value)
: _type(INTTYPE),
  _description(VpfStrDup(description))
{
    _value.intVal = value;
}

// --------------------------------------------------------------------------
VpfValue::VpfValue(const char* description, double value)
: _type(FLOATTYPE),
  _description(VpfStrDup(description))
{
    _value.floatVal = value;
}

// --------------------------------------------------------------------------
VpfValue::VpfValue(const char* description, const char* value)
: _type(TEXTTYPE),
  _description(VpfStrDup(description))
{
    _value.textVal = VpfStrDup(value);
}

// --------------------------------------------------------------------------
VpfValue::~VpfValue()
{
    if (_type == TEXTTYPE) {
	if (_value.textVal)
	    delete  [] _value.textVal;
    }
    if (_description)
	delete [] _description;
}

// --------------------------------------------------------------------------
const char*
VpfValue::getValue() const
{
    static char buffer[64];
    switch (_type) {
    case INTTYPE:
	sprintf(buffer, "%d", _value.intVal);
	return buffer;
    case FLOATTYPE:
	sprintf(buffer, "%f", _value.floatVal);
	return buffer;
    case TEXTTYPE:
	return _value.textVal;
    }
    return 0;
}

// --------------------------------------------------------------------------
void
VpfValue::dump(ostream& s) const
{
    s << "[";
    switch (_type) {
    case INTTYPE:
	s << _value.intVal;
	break;
    case FLOATTYPE:
	s << _value.floatVal;
	break;
    case TEXTTYPE:
	s << _value.textVal;
	break;
    }
    s << ", " << _description << "]";
}

// --------------------------------------------------------------------------
VpfAttribute::VpfAttribute(const char* name,
                           const char* description,
                           VpfUInt nValues)
: _name(VpfStrDup(name)),
  _description(VpfStrDup(description)),
  _nValues(nValues),
  _values(nValues
	  ? new VpfValue*[_nValues]
	  : 0)
{
}

// --------------------------------------------------------------------------
VpfAttribute::~VpfAttribute()
{
    if (_name)
	delete [] _name;
    if (_description)
	delete [] _description;
    if (_values) {
	for (VpfUInt i = 0; i < _nValues; i++)
	    delete _values[i];
	delete [] _values;
    }
}

// --------------------------------------------------------------------------
VpfValue*
VpfAttribute::getValue(unsigned int i)
{
    return (i >= _nValues)
	? 0
	:_values[i];
}

// --------------------------------------------------------------------------
void
VpfAttribute::setValue(unsigned int i, VpfValue* value)
{
    if (i < _nValues)
	_values[i] = value;
}

// --------------------------------------------------------------------------
void
VpfAttribute::dump(ostream& s) const
{
    s << _name << " ";
    for (unsigned int i = 0; i < _nValues; i++)
	if (_values[i])
	    _values[i]->dump(s);
}
