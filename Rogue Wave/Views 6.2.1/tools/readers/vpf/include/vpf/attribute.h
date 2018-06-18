// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/attribute.h
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
// Declaration of the VpfAttribute class
// --------------------------------------------------------------------------
#ifndef VPF_ATTRIBUTE_H
#define VPF_ATTRIBUTE_H

#ifndef VPF_BASICTYPES_H
# include <vpf/basictypes.h>
#endif
#ifndef __Ilv_Macros_H
# include <ilviews/macros.h>
#endif

#if defined(ILVSTD)
# include <iostream>
ILVSTDUSE
#else
# include <iostream.h>
#endif

// --------------------------------------------------------------------------
class VpfValue
{
public:
    VpfValue(const char*, VpfInt);
    VpfValue(const char*, double);
    VpfValue(const char*, const char*);
    ~VpfValue();
    // ____________________________________________________________
    const char* getDescription() const { return _description; }
    const char* getValue() const;
    VpfInt      getIntValue() const   { return _value.intVal;   }
    double      getFloatValue() const { return _value.floatVal; }
    const char* getTextValue() const  { return _value.textVal;  }
    void dump(ostream&) const;
protected:
    enum {
	INTTYPE   = 0,
	FLOATTYPE = 1,
	TEXTTYPE  = 2
    }		_type;
    union {
	VpfInt	intVal;
	double	floatVal;
	char*	textVal;
    }		_value;
    char*	_description;
};

// --------------------------------------------------------------------------
class VpfAttribute
{
public:
    VpfAttribute(const char* name, const char* description,
		 VpfUInt nValues = 0);
    ~VpfAttribute();
    // ____________________________________________________________
    const char* getName() const { return _name; }
    const char* getDescription() const { return _description; }
    VpfUInt getNValues() const { return _nValues; }
    VpfValue* getValue(VpfUInt i);
    void setValue(VpfUInt i, VpfValue* value);
    void dump(ostream&) const;
protected:
    char*	_name;
    char*	_description;
    VpfUInt	_nValues;
    VpfValue**	_values;
};

#endif /* VPF_ATTRIBUTE_H */
