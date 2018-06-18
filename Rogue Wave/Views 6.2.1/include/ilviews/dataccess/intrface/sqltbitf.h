// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/sqltbitf.h
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
// Declaration of the IliSQLTableItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqltbitf_H
#define __Ili_Sqltbitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Tblitf_H)
#  include <ilviews/dataccess/intrface/tblitf.h>
#endif
#if !defined(__Ili_Sqltable_H)
#  include <ilviews/dataccess/sqltable.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTableColumnItf
: public IliTableColumnItf
{
public:
    IliSQLTableColumnItf(IliSQLTable*, IlInt);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropClassInfo();

    IliSQLTable* getSQLTable() const;
};

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTableAliasItf
: public IliRefCountedValueInterface
{
public:
    IliSQLTableAliasItf(IliSQLTable*, IlInt);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropClassInfo();

    IlBoolean isBeingDeleted() const;

    IliSQLTable* getSQLTable() const;
    virtual const char* getName() const;

protected:
    IliSQLTablePtr _sqlTablePtr;
    IlInt _token;
    IlInt _tblno;

    IlBoolean fixTblno() const;
};

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTableItf
: public IliMemoryTableItf
{
public:
    IliSQLTableItf(IliSQLTable*);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IliSQLTable* getSQLTable() const;

    IlvDeclarePropClassInfo();
};

// --------------------------------------------------------------------------
IlvDeclareEnumTypeClass(ILV_DBI_EXPORTED, FetchPolicy);
IlvDeclareEnumTypeClass(ILV_DBI_EXPORTED, SQLOrderBy);
IlvDeclareEnumTypeClass(ILV_DBI_EXPORTED, SQLOperation);

IliModuleDECL_exp(ILV_DBI_EXPORTED, FetchPolicy);
IliModuleDECL_exp(ILV_DBI_EXPORTED, SQLOrderBy);
IliModuleDECL_exp(ILV_DBI_EXPORTED, SQLOperation);
IliModuleDECL_exp(ILV_DBI_EXPORTED, IliSQLTableItf);

#endif /* !__Ili_Sqltbitf_H */
