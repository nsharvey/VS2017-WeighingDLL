// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/attribute.h
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
// Declaration of the VpfAttribute class
// --------------------------------------------------------------------------
#ifndef VPF_ATTRIBUTE_H
#define VPF_ATTRIBUTE_H

#include <vpf/basictypes.h>
#if defined(VPFSTD)
#include <iostream>
#else
#include <iostream.h>
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
    inline const char*	getDescription() const { return _description; }
    const char*		getValue() const;
    inline VpfInt	getIntValue() const   { return _value.intVal;   }
    inline double	getFloatValue() const { return _value.floatVal; }
    inline const char*	getTextValue() const  { return _value.textVal;  }
    void		dump(VPFSTDPREF ostream&) const;

protected:
    enum {
	INTTYPE   = 0,
	FLOATTYPE = 1,
	TEXTTYPE  = 2
    }			_type;
    union {
	VpfInt	intVal;
	double	floatVal;
	char*	textVal;
    }			_value;
    char*		_description;
};

// --------------------------------------------------------------------------
class VpfAttribute
{
public:
    VpfAttribute(const char* name,
		 const char* description,
		 VpfUInt     nValues = 0);
    ~VpfAttribute();
    // ____________________________________________________________
    inline const char*	getName() const { return _name; }
    inline const char*	getDescription() const { return _description; }
    inline VpfUInt	getNValues() const { return _nValues; }
    VpfValue*		getValue(VpfUInt i);
    void		setValue(VpfUInt i, VpfValue* value);
    void		dump(VPFSTDPREF ostream&) const;

protected:
    char*		_name;
    char*		_description;
    VpfUInt		_nValues;
    VpfValue**		_values;
};

#endif /* VPF_ATTRIBUTE_H */
