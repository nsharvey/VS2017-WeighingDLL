// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/sqlseitf.h
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
// Declaration of the IliSQLSessionItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqlseitf_H
#define __Ili_Sqlseitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Session_H)
#  include <ilviews/dataccess/dbms/session.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLSessionItf
: public IliRefCountedValueInterface
{
public:
    IliSQLSessionItf(IliSQLSession*);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    void sessionLost();

    IliSQLSession* getSQLSession() const { return _session; }

protected:
    IliSQLSession* _session;
};

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLSessionRegisteryItf
: public IliRefCountedValueInterface
{
public:
    IliSQLSessionRegisteryItf();

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
IlvDeclareEnumTypeClass(ILV_DBI_EXPORTED, SQLQueryConnectFlag);

IliModuleDECL_exp(ILV_DBI_EXPORTED, SQLQueryConnectFlag);
IliModuleDECL_exp(ILV_DBI_EXPORTED, IliSQLSessionItfModule);

#endif /* !__Ili_Sqlseitf_H */
