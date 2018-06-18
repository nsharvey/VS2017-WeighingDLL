// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/intrface/attrhold.h
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
// Declaration of the IlvAttributeHolderInterface class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Itf_Attrhold_H
#define __Ilv31_Itf_Attrhold_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

class IlvGraphic;
class IlvGraphicAttribute;
// --------------------------------------------------------------------------
#define IlvAttributeHolderInterface IlvAHItf
class ILV31VAREXPORTED IlvAttributeHolderInterface
{
public:
    virtual IlBoolean addAttribute(IlvGraphicAttribute*) = 0;
    virtual IlBoolean removeAttribute(IlvGraphicAttribute*) = 0;
    virtual IlvGraphicAttribute* getAttribute(const char* name) const = 0;
    virtual const char* const* getAttributeNames(IlUInt& count) const = 0;
    virtual IlUInt numberOfAttributes() const = 0;
protected:
    void removeAttributes(IlvGraphic*, IlBoolean);
};

#endif /* __Ilv31_Itf_Attrhold_H */
