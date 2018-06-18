// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/connacc.h
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
// Declaration of user accessors for connecting an input value to an output
// value
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Connacc_H
#define __Ilv_Protos_Connacc_H

#if !defined(__Ilv_Protos_Macros_H)
#include <ilviews/protos/macros.h>
#endif
#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif

// ---------------------------------------------------------------------------
// IlvConnectionAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvConnectionAccessor : public IlvUserAccessor
{
public:
    IlvConnectionAccessor(const char* name,
			  const IlvValueTypeClass* type,
			  const char* outacc);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvConnectionAccessor);

protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlSymbol*		_outacc;
};

// ---------------------------------------------------------------------------
// IlvOutputAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvOutputAccessor : public IlvUserAccessor
{
public:
    IlvOutputAccessor(const char* name,
		      const IlvValueTypeClass* type);

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvOutputAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
};

// ---------------------------------------------------------------------------
// IlvLoopbackAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvLoopbackAccessor : public IlvUserAccessor
{
public:
    IlvLoopbackAccessor(const char* name,
			const IlvValueTypeClass* type,
			const char* outacc);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvLoopbackAccessor);

protected:
    virtual void	initialize(const IlvAccessorHolder* object);

    IlSymbol*		_outacc;
};

// ---------------------------------------------------------------------------
// IlvExportOutputAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvExportOutputAccessor : public IlvLoopbackAccessor
{
public:
    IlvExportOutputAccessor(const char* name,
			    const IlvValueTypeClass* type,
			    const char* outacc);

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvExportOutputAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
};

// ---------------------------------------------------------------------------
// IlvIndirectAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvIndirectAccessor : public IlvMultipleUserAccessor
{
public:
    IlvIndirectAccessor(const char* name, const char* subacc);

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;

    virtual IlShort	matchValues(const IlvAccessorHolder* object,
				    const IlvValue* values,
				    IlUShort count,
				IlvValue* matchingValues = 0) const;

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvIndirectAccessor);

protected:
    virtual void	initialize(const IlvAccessorHolder* object);

    virtual void	queryValues(const IlvAccessorHolder* object,
				    IlvValue* values,
				    IlUShort count) const;
    virtual IlBoolean	changeValues(IlvAccessorHolder* object,
				     const IlvValue* values,
				     IlUShort count);

    void		buildNames();

    IlSymbol*			_subacc;
    IlSymbol*			_pushacc;
    const IlvAccessorHolder*	_object;
};

IlvDECLAREINITPROCLASS(connacc)

#endif /* __Ilv_Protos_Connacc_H */
