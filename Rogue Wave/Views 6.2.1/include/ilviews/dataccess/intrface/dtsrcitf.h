// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/dtsrcitf.h
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
// Declaration of the major DataSource interface classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Dtsrcitf_H
#define __Ili_Dtsrcitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Datasrc_H)
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDataSourceColumnItf
: public IliRefCountedValueInterface
{
public:
    IliDataSourceColumnItf(IliDataSource*, IlInt);
    virtual ~IliDataSourceColumnItf();

    virtual IlBoolean getValueValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliDataSource* getDataSource() const;
    IliTable* getTable() const;
protected:
    IlvSafePointer* _dsPointer;
    IlInt _token;
    IlInt _realColno;

    IlBoolean fixColno() const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDataSourceConnectionInfo
: public IliRefCountedValueInterface
{
public:
    IliDataSourceConnectionInfo(IliDataSource*);
    virtual ~IliDataSourceConnectionInfo();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);
    virtual void getAccessors(const IlvSymbol* const**,
			      const IlvValueTypeClass* const**,
			      IlUInt&) const;

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IlvValueInterface* getValueSource();

    const IliDataSource* getDataSource() const;
    IliDataSource* getDataSource();

    void detach();

protected:
    IlvSafePointer* _dsPointer;
    IlvValueInterface* _valueSource;

    void addInputValues(IlInt&, IlvSymbol**) const;
    void addOutputValues(IlInt&, IlvSymbol**) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDSErrorSinkForItf
: public IliErrorSinkForItf
{
public:
    IliDSErrorSinkForItf(IliDataSource*, IlvValueInterface*);
    virtual ~IliDSErrorSinkForItf();

    virtual void free();
protected:
    IlvSafePointer* _dsPointer;
};

IliModuleDECL_exp(ILV_INF_EXPORTED, IliDataSourceItfModule);

#endif /* !__Ili_Dtsrcitf_H */
