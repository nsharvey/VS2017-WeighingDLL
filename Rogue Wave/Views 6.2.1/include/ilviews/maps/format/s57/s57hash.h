// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57hash.h
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
#ifndef __Ilv_S57hash_H
#define __Ilv_S57hash_H

#include <ilviews/maps/format/s57/i8211util.h>

// --------------------------------------------------------------------------
// IlvS57HashKey
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57HashKey
{
public:
    IlvS57HashKey() {}
    virtual ~IlvS57HashKey() {}

    virtual IlBoolean	isSameKey(const IlvS57HashKey& k) const;
};

// --------------------------------------------------------------------------
// IlvS57HashTable
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57HashTable : public IlHashTable
{
public:
    IlvS57HashTable(IlUInt size = 16)
	: IlHashTable(size)
    {}
    // ____________________________________________________________
protected:
    virtual IlBoolean match(const IlAny target, const IlAny entry) const;
};

// --------------------------------------------------------------------------
// IlvS57String
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57String : public IlString, public IlvS57HashKey
{
public:
    IlvS57String(const char* cstring = 0);
    IlvS57String(const IlString& string);
    IL_EXPLICIT IlvS57String(int value, 
			     const char* format = DefaultIntegerFormat);
    IL_EXPLICIT IlvS57String(unsigned int value,
			     const char* format = DefaultUnsignedIntegerFormat);
    IL_EXPLICIT IlvS57String(short value, 
			     const char* format = DefaultShortFormat);
    IL_EXPLICIT IlvS57String(unsigned short value,
			     const char* format = DefaultUnsignedShortFormat);
    IL_EXPLICIT IlvS57String(long value, 
			     const char* format = DefaultLongFormat);
    IL_EXPLICIT IlvS57String(unsigned long value,
			     const char* format = DefaultUnsignedLongFormat);
    IL_EXPLICIT IlvS57String(float value, 
			     const char* format = DefaultFloatFormat);
    IL_EXPLICIT IlvS57String(double value,
			     const char* format = DefaultDoubleFormat);

    virtual IlBoolean	isSameKey(const IlvS57HashKey& k) const;
};

// --------------------------------------------------------------------------
// IlvS57AssocId
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57AssocId
{
public:
    IlvS57AssocId(IlInt h = 0,IlInt l = 0);

    IlvS57AssocId(const IlvS57AssocId& src);

    void	set(IlInt h ,IlInt l);

    int		operator==(const IlvS57AssocId& obj) const;

    const char*	getValue();

    IlBoolean	isNull() const;

    IlInt	_hight;
    IlInt	_low;
};

// --------------------------------------------------------------------------
// IlvS57AssocTable
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57AssocTable
{
public:
    IlvS57AssocTable();
    virtual ~IlvS57AssocTable();

    void		add(const IlvS57AssocId& cle, IlvI8211RefCount* item);
    void		put(const IlvS57AssocId& cle, IlvI8211RefCount* item);

    IlInt		getCount();
    IlvI8211RefCount*	get(const IlvS57AssocId& cle);

    inline IlvI8211TreeNode*	getFirst() { return _items.getFirst(); }

    void		reset();

protected:
    IlvI8211Tree _items;
};

#endif /* !__Ilv_S57hash_H */
