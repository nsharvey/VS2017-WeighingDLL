// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/tblitf.h
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
// Declaration of the IliTableItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblitf_H
#define __Ili_Tblitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if defined(__Ili_Schemitf_H)
#  include <ilviews/dataccess/intrface/schemitf.h>
#endif
#if !defined(__Ili_Table_H)
#  include <ilviews/dataccess/table.h>
#endif
#if !defined(__Ili_Tblsel_H)
#  include <ilviews/dataccess/tblsel.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableSelectionItf
: public IliRefCountedValueInterface
{
public:
    IliTableSelectionItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt& count);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliTableSelection& getSelection();

protected:
    IliTableSelection _sel;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliParameterItf
: public IliRefCountedValueInterface
{
public:
    IliParameterItf(IliTable*, const char*);

    virtual IlBoolean getValueValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt& count);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

protected:
    IliTablePtr _tablePtr;
    IliString _name;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableColumnItf
: public IliColumnItf
{
public:
    IliTableColumnItf(IliTable*, IlInt);

    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropClassInfo();

protected:
    IliTable* getTable() const;

    const IlvValueTypeClass* getViewsType() const;
    IlBoolean getVariantArg(const IlvValue&, IlInt, IliValue&) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTMErrorSinkForItf
: public IliErrorSinkForItf
{
public:
    IliTMErrorSinkForItf(IliTransactionManager*, IlvValueInterface*);
    virtual ~IliTMErrorSinkForItf();

    virtual void free();
protected:
    IliTransactionManager* _tm;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTransactionManagerItf
: public IliRefCountedValueInterface
{
public:
    IliTransactionManagerItf(IliTransactionManager*);
    virtual ~IliTransactionManagerItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliTransactionManager* getTransactionManager() const;

protected:
    IliTransactionManager* _tm;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableItf
: public IliSchemaItf
{
public:
    IliTableItf(IliTable*);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropClassInfo();

    IliTable* getTable() const;

protected:
    friend class IliTableBufferItf;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableBufferItf
: public IliRefCountedValueInterface
{
public:
    IliTableBufferItf(IliTable*);
    virtual ~IliTableBufferItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;

    IlvDeclarePropRootClassInfo();

    const IliTableBuffer* getBuffer() const { return _buffer; }
    IliTableBuffer* getBuffer()             { return _buffer; }

protected:
    IliTablePtr _tablePtr;
    IliTableBuffer* _buffer;

    IlvValueTypeClass* getTypeClass(IlInt colno) const;

    friend class IliTableItf;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableBufferValueItf
: public IliRefCountedValueInterface
{
public:
    IliTableBufferValueItf(IliTableBuffer*, IlInt);
    virtual ~IliTableBufferValueItf();

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

protected:
    IliTablePtr _tablePtr;
    IlInt _token;
    IlInt _colno;
    IliTableBuffer* _buffer;

    const IliTable* getTable() const;
    IliTable* getTable();
    IlvValueTypeClass* getTypeClass() const;
    IlBoolean fixColno() const;

    friend class IliTableBufferItf;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTablePropertyManagerItf
: public IliRefCountedValueInterface
{
public:
    IliTablePropertyManagerItf(IliTable*);
    IliTablePropertyManagerItf(IliTablePropertyManager*);
    virtual ~IliTablePropertyManagerItf();

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
    IliTablePtr _tablePtr;
    IliTablePropertyManager* _propMgr;

    IliTablePropertyManager* getEffectivePropMgr() const;
};

// --------------------------------------------------------------------------
IlvDeclareEnumTypeClass(ILV_INF_EXPORTED, TableEventType);
IlvDeclareEnumTypeClass(ILV_INF_EXPORTED, TableSelectionType);

IliModuleDECL_exp(ILV_INF_EXPORTED, TableEventType);
IliModuleDECL_exp(ILV_INF_EXPORTED, TableSelectionType);
IliModuleDECL_exp(ILV_INF_EXPORTED, IliTableItf);

#endif /* !__Ili_Tblitf_H */
