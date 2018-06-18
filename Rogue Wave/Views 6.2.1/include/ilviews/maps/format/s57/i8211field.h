// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211field.h
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
// Rogue Wave Views - Maps add-on.
// --------------------------------------------------------------------------
#ifndef __Ilv_I8211field_H
#define __Ilv_I8211field_H

#include <ilviews/maps/format/s57/i8211decl.h>
#include <ilviews/maps/format/s57/i8211util.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Property
: public IlvI8211Entry::Value
{
public:
    IlvI8211Property();
    IlvI8211Property(const IlString& name, const char* data, IlInt length);
    virtual ~IlvI8211Property();

    const IlString&	getName() const;

    const char*		getData(IlInt& length, IlInt ndx) const;
    char*		getData(IlInt& length, IlInt ndx);

    const char*		getData(IlInt ndx = 0) const;
    IlInt		getLength(IlInt ndx = 0) const;

    void		setData(const char* data, IlInt length);
    void		addData(const char* data, IlInt length);

    IlInt		count() const;

protected:
    IlString		_name;
    char**		_data;
    IlInt*		_length;
    IlInt		_count;
    IlInt		_size;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Field
{
public:
    IlvI8211Field();

    IlvI8211Field(const char* name, IlvI8211FieldDeclaration* declaration);
    virtual	~IlvI8211Field();

    void	setName(const char*);

    const char* getName();

    IlBoolean	isThis(const IlString&) const;

    IlvI8211SubFieldDeclaration*	getDeclaration(const IlString& name);

    IlvValue*	getValue(const char* name);

    const char*	getStringValue(const char* name);

    IlInt	getIntegerValue(const char* name);

    IlDouble	getDoubleValue(const char* name);

    IlvValue**	getValues(const char* name, IlInt& count);

    IlInt*	getIntegerValues(const char* name, IlInt& count);

    IlBoolean	hasProperties() const;
    void	removeProperty(const char* name);
    void	setProperty(const char* name, const char* val, IlInt length);
    void	addProperty(const char* name, const char* val, IlInt length);
    const char* getPropertyValue(const char* name, IlInt& length) const;

protected:
    void	normalize(IlString& propertyName) const;

    IlvI8211FieldDeclaration*	_declaration;
    IlString			_name;
    IlvI8211HashTable           _properties;
};

#endif /* !__Ilv_I8211field_H */
