// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/attrprop.h
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
// General Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Attrprop_H
#define __Ilv_Maps_Attrprop_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Maps_Attribute_H)
#  include <ilviews/maps/attribute.h>
#endif
#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif

ILVMAPSMODULETERM(IlvAttributeInfoProperty);

class ILVMAPSEXPORTED IlvFeatureAttributeInfo
{
public:

    IlvFeatureAttributeInfo(IlUInt count,
			    const char* const* attributeNames,
			    const IlvMapClassInfo* const* attributeClasses,
			    const IlBoolean* nullable);

    IlvFeatureAttributeInfo(const IlvFeatureAttributeInfo& source);

    IlvFeatureAttributeInfo(IlvInputFile& file);

    IlvFeatureAttributeInfo*	copy() const
			{
			    return new IlvFeatureAttributeInfo(*this);
			}

    const char* const*	getAttributesNames(IlUInt& count) const
			{
			    count = _count;
			    return (const char* const*) _names;
			}

    const char* getAttributeName(IlUInt i) const { return _names[i]; }

    const IlvMapClassInfo* const* getAttributesClasses() const
			{
			    return (const IlvMapClassInfo* const*) _classes;
			}

    const IlvMapClassInfo* getAttributeClass(IlUInt i) const
			{
			    return _classes[i];
			}

    IlBoolean		isNullable(int i) const { return _nullable[i]; }

    IlUInt		getAttributesCount() const { return _count; }

    void		write(IlvOutputFile& output) const;

    void		lock() { _lockCount++; }

    void		unLock()
			{
			    _lockCount--;
			    if (_lockCount <= 0)
				delete this;
			}

protected:
    // use the lock / unLock API to manage object destruction
    virtual ~IlvFeatureAttributeInfo();

private:
    IlUInt		_count;
    char**		_names;
    IlvMapClassInfo**	_classes;
    IlBoolean*		_nullable;
    IlInt		_lockCount;

};

class ILVMAPSEXPORTED IlvFeatureAttributeProperty : public IlvNamedProperty
{
public:
    IlvFeatureAttributeProperty(IlvFeatureAttributeInfo* info,
				IlvFeatureAttribute** values,
				IlvMapsError& status);

    IlvFeatureAttributeProperty(const IlvFeatureAttributeProperty& source);

    IlvFeatureAttributeProperty(IlvInputFile& input, IlvSymbol* symbol);

    virtual ~IlvFeatureAttributeProperty();

    static
    const IlvSymbol*	GetName() { return _name; }

    const IlvFeatureAttributeInfo* getInfo() const { return _info; }

    static IlvMapsError	NullableError() {return _nullableError;}

    const IlvFeatureAttribute*  getAttribute(int i) const
			{
			    return _values[i];
			}

    const IlvFeatureAttribute* getAttribute(const char* name) const;


    IlvFeatureAttribute* setAttribute(IlUInt i,
				      IlvFeatureAttribute* attribute,
				      IlvMapsError& status);

    IlvFeatureAttribute* unsafeSetAttribute(int i,
					    IlvFeatureAttribute* attribute);

    virtual
    IlvNamedProperty*	copy() const;


    IlvFeatureAttribute* setAttribute(const char* name,
				      IlvFeatureAttribute* value,
				      IlvMapsError& status);

    void		write(IlvOutputFile& output) const;


private:
    IlvMapsIcFriend(IlvAttributeInfoProperty, ILVMAPSEXPORTED);

    static void		Init();

    IlvDeclarePropClassInfo();

    static IlvSymbol*		_name;
    static IlvMapsError		_nullableError;
    IlvFeatureAttributeInfo*	_info;
    IlvFeatureAttribute**	_values;
};

#endif /* !__Ilv_Maps_Attrprop_H */
