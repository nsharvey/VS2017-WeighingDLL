// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57enum.h
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
#ifndef __Ilv_S57Enum_H
#define __Ilv_S57Enum_H

#include <ilviews/maps/format/s57/i8211util.h>

class IlvS57Enumeration;

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57EnumerationArray
{
public:
    IlvS57EnumerationArray();
    ~IlvS57EnumerationArray();

    IlInt		count();

    IlvS57Enumeration*	operator[](IlInt index);

    void		add(const char* ascii,
			    IlInt       value,
			    const char* label,
			    IlBoolean   show = IlTrue);

    void		add(IlvS57Enumeration* enumeration);

protected:
    IlvS57Enumeration**	_items;
    IlInt		_count;
    IlInt		_max;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57Enumeration : public IlvI8211RefCount
{
public:
    IlvS57Enumeration();

    IlvS57Enumeration(const char* ascii,
		      IlInt       value,
		      const char* label,
		      IlBoolean   show = IlTrue);

    void			set(const char* ascii,
				    IlInt       value,
				    const char* label,
				    IlBoolean   show = IlTrue);

    virtual IlBoolean		equals(IlInt val);

    virtual IlInt		hashCode();
    virtual const char*		toString();

    const char*			asciiValue() const;

    const char*			getLabel() const;

    IlInt			binaryValue() const;  

    static IlvS57Enumeration*	Find(IlvS57EnumerationArray& array,
				     IlInt value,
				     const char* prefix = 0);
protected:
    IlString			_asciiValue;
    IlString			_label;
    IlInt			_binaryValue;
    IlBoolean			_showLabel;

    IlString			_buffer;

    virtual			~IlvS57Enumeration();
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57PropertyTable
{
public:
    IlvS57PropertyTable();
    ~IlvS57PropertyTable();

    void		set(IlvS57Enumeration* key, IlAny val);
    void		add(IlvS57Enumeration* key, IlAny val);

    IlInt		find(IlvS57Enumeration* key);
    IlInt		count() const;

    IlvS57Enumeration*	getKey(IlInt);
    IlAny		getValue(IlInt);

    void		reset();

protected:
    IlvS57Enumeration**	_keys;
    IlAny*		_values;
    IlInt		_count;
    IlInt		_size;
};

#endif /* !__Ilv_S57Enum_H */

