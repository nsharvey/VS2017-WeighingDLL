// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/attribute/stringattr.h
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
#ifndef __Ilv_Maps_Attribute_Stringattr_H
#define __Ilv_Maps_Attribute_Stringattr_H

#if !defined(__Ilv_Maps_Attribute_H)
#  include <ilviews/maps/attribute.h>
#endif
ILVMAPSMODULETERM(attribute_IlvStringAttribute);

class ILVMAPSEXPORTED IlvStringAttribute
: public IlvFeatureAttribute
{
public:
    IlvStringAttribute();    
    IlvStringAttribute(const char* value, IlBoolean copy = IlTrue);
    IlvStringAttribute(const IlvStringAttribute& source);
    virtual ~IlvStringAttribute();

    void setValue(const char* value, IlBoolean copy = IlTrue);
    inline const char* getValue() const { return _value; }
    virtual IlvFeatureAttribute* copy() const;

    ILVMAPS_DECLMANDATORYATTRMEMBERS(IlvStringAttribute);
private:
    char* _value;
};

#endif /* !__Ilv_Maps_Attribute_Stringattr_H */
