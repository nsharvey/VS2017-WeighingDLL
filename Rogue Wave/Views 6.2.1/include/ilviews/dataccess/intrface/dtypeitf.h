// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/dtypeitf.h
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
// Declaration of the IliValueDatatypeTypeClass class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Dtypeitf_H
#define __Ili_Dtypeitf_H

#if !defined(__Ili_Datatype_H)
#  include <ilviews/dataccess/datatype.h>
#endif
#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if defined(IL_STD)
#  include <cstring>
#else /* !IL_STD */
#  include <string.h>
#endif /* !IL_STD */


// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliValueDatatypeTypeClass
: public IlvValueTypeClass
{
public:
    IliValueDatatypeTypeClass();
    virtual ~IliValueDatatypeTypeClass();

    virtual IlUInt getCapacities() const;
    virtual const char* toString(const IlvValue&) const;
    virtual IlBoolean fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlBoolean isPersistent() const;
    virtual IlInt compareValues(const IlvValue&, const IlvValue&) const;

    const IliDatatype* toDatatype(const IlvValue&) const;
    IlBoolean fromDatatype(IlvValue&, const IliDatatype*) const;

    static void AtInit();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypesItf
: public IliRefCountedValueInterface
{
public:
    IliDatatypesItf();
    virtual ~IliDatatypesItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual void getAccessors(const IlvSymbol* const**,
			      const IlvValueTypeClass* const**,
			      IlUInt&) const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    static IliDatatypesItf* GetSingleton();

private:
    static IliDatatypesItf* _Singleton;
};

// --------------------------------------------------------------------------
extern ILV_INF_EXPORTEDVAR(IliValueDatatypeTypeClass*) IliValueDatatypeType;
IliModuleDECL_exp(ILV_INF_EXPORTED, IliValueDatatypeTypeClass);

#endif /* !__Ili_Dtypeitf_H */
