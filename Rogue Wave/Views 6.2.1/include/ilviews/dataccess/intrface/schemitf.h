// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/schemitf.h
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
// Declaration of the IliColumnItf and IliSchemaItf classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Schemitf_H
#define __Ili_Schemitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Dtypeitf_H)
#  include <ilviews/dataccess/intrface/dtypeitf.h>
#endif
#if !defined(__Ili_Schema_H)
#  include <ilviews/dataccess/schema.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliColumnItf
: public IliRefCountedValueInterface
{
public:
    IliColumnItf(IliSchema*, IlInt);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliSchema* getSchema() const;

protected:
    IliSchemaPtr _schemaPtr;
    IlInt _token;
    IlInt _colno;

    IlBoolean fixColno() const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliSchemaItf
: public IliRefCountedValueInterface
{
public:
    IliSchemaItf(IliSchema*);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

protected:
    IliSchemaPtr _schemaPtr;
};

// --------------------------------------------------------------------------
IliModuleDECL_exp(ILV_INF_EXPORTED, IliSchemaItfModule);

#endif /* !__Ili_Schemitf_H */
