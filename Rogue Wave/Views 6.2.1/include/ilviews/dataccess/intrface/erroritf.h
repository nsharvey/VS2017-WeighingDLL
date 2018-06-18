// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/erroritf.h
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
// Declaration of the IliErrorMessageItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Erroritf_H
#define __Ili_Erroritf_H

#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Error_H)
#  include <ilviews/dataccess/error.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorMessageItf
: public IliRefCountedValueInterface
{
public:
    IliErrorMessageItf(const IliErrorMessage&);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropRootClassInfo();

    const IliErrorMessage& getErrorMessage() const { return _errorMessage; }
    IliErrorMessage& getErrorMessage() { return _errorMessage; }

protected:
    IliErrorMessage _errorMessage;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorMessageClassItf
: public IliClassItf
{
public:
    IliErrorMessageClassItf();

    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlvValueInterface* newObject(const IlvValue&);
    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorListItf
: public IliRefCountedValueInterface
{
public:
    IliErrorListItf(const IliErrorList&);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropRootClassInfo();

    const IliErrorList& getErrorList() const { return _errorList; }
    IliErrorList& getErrorList() { return _errorList; }

protected:
    IliErrorList _errorList;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorListClassItf
: public IliClassItf
{
public:
    IliErrorListClassItf();

    virtual IlvValueInterface* newObject(const IlvValue&);
    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorSinkForItf
: public IliErrorSink {
public:
    IliErrorSinkForItf(IlvValueInterface*);
    virtual ~IliErrorSinkForItf();

    virtual void addError(const IliErrorMessage&);
    virtual void free();

    static IliErrorSinkForItf* Find(IlvValueInterface*);
    static void FreeAll();

    static IlBoolean IsUsable(IlvValueInterface*);

protected:
    IlvValueInterface* _itf;
    static IlvArray _allInstances;
};

// --------------------------------------------------------------------------
IlvDeclareEnumTypeClass(ILV_INF_EXPORTED, ErrorSeverity);
IlvDeclareEnumTypeClass(ILV_INF_EXPORTED, ErrorOrigin);

IliModuleDECL_exp(ILV_INF_EXPORTED, ErrorSeverity);
IliModuleDECL_exp(ILV_INF_EXPORTED, ErrorOrigin);
IliModuleDECL_exp(ILV_INF_EXPORTED, IliErrorMessageItfModule);

#endif /* !__Ili_Erroritf_H */
