// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/intrface/attrmgr.h
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
// Declaration of the IlvAttributeManagerInterface class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Itf_Attrmgr_H
#define __Ilv31_Itf_Attrmgr_H

#if !defined(__Ilv31_Itf_Attrhold_H)
#include <ilviews/intrface/attrhold.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

// --------------------------------------------------------------------------
#define IlvAttributeManagerInterface IlvAMItf
class ILV31VAREXPORTED IlvGraphicAttribute;
class ILV31VAREXPORTED IlvAttributeManagerInterface
: public IlvAttributeHolderInterface
{
public:
    virtual IlBoolean addAttribute(IlvGraphicAttribute*);
    virtual IlBoolean removeAttribute(IlvGraphicAttribute*);
    virtual IlvGraphicAttribute* getAttribute(const char* name) const;
    virtual const char* const* getAttributeNames(IlUInt& count) const;
    virtual IlUInt numberOfAttributes() const;
protected:
    virtual IlvStringHashTable* getAttributesTable() const = 0;
};

#endif /* __Ilv31_Itf_Attrmgr_H */
