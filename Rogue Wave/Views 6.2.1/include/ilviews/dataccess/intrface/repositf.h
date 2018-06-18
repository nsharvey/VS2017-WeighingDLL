// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/repositf.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliRepositoryItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Repositf_H
#define __Ili_Repositf_H

#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ili_Reposit_H)
#  include <ilviews/dataccess/reposit.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRepositoryItf
: public IliRefCountedValueInterface
{
public:
    IliRepositoryItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    const char* getName() const;

    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
IliModuleDECL_exp(ILV_INF_EXPORTED, IliRepositoryItf);

#endif /* !__Ili_Repositf_H */
