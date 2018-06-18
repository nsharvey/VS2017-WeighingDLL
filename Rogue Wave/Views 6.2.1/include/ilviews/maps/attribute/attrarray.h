// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/attribute/attrarray.h
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
// Attribute Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Attribute_Attrarray_H
#define __Ilv_Maps_Attribute_Attrarray_H

#if !defined(__Ilv_Maps_Attribute_H)
#  include <ilviews/maps/attribute.h>
#endif
#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif

class ILVMAPSEXPORTED IlvStringAttribute;
ILVMAPSMODULETERM(attribute_IlvAttributeArray);

class ILVMAPSEXPORTED IlvAttributeArray
: public IlvFeatureAttribute
{
public:
    IlvAttributeArray(IlInt size);
    IlvAttributeArray(const IlvAttributeArray& source);
    virtual ~IlvAttributeArray();

    IlvFeatureAttribute* getAttribute(IlInt index) const;
    IlvFeatureAttribute* setAttribute(IlInt index,
				      IlvFeatureAttribute* attribute,
				      IlvMapsError& status);
    IlvFeatureAttribute*  unsafeSetAttribute(IlInt index,
					     IlvFeatureAttribute* attribute);

    inline static IlvMapsError IndexError() { return _indexError; }

    inline IlInt getSize() const { return _valueCount; }

    void setSize (IlInt newSize);

    inline const IlvMapClassInfo* getCommonClass() const
	{ return _commonClass; }
    IlvMapsError setCommonClass(const IlvMapClassInfo* commonClass);

    virtual IlvFeatureAttribute* copy() const;

    ILVMAPS_DECLMANDATORYATTRMEMBERS(IlvAttributeArray);
private:
    static void InitNullAttribute();

    static IlvMapsError _indexError;
    static IlvStringAttribute* _nullAttribute;

    IlvFeatureAttribute** _values;
    int _valueCount;
    const IlvMapClassInfo* _commonClass;
};

#endif /* !__Ilv_Maps_Attribute_Attrarray_H */
