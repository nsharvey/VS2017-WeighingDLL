// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/protoacc.h
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
// Declaration of the accessor for connecting an output value to a callback.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Protoacc_H
#define __Ilv_Protos_Protoacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif

// ---------------------------------------------------------------------------
// IlvPrototypeAccessorHolder
// ---------------------------------------------------------------------------
class IlvPrototypeAccessorHolder : public IlvAccessorHolder
{
    friend class IlvPrototypeAccessor;

public:
    IlvPrototypeAccessorHolder();
    virtual ~IlvPrototypeAccessorHolder();

    virtual const char*	getName() const { return(""); }
    virtual
    IlvClassInfo*	getClassInfo() const { return(0); }

    virtual
    IlvAccessor*	nextAccessor(IlAny& cell) const;

    void		addAccessor(IlvUserAccessor* acc);

    void		setTopHolder(IlvAccessorHolder* object)
			{
			    _object = object;
			}

    virtual
    IlvAccessorHolder*	getTopHolder() const;
    IlList*		getAccessorList() const
			{
			    return (IlList*) &_accessors;
			}
    IlList*		getClassAccList(IlAny& /* a */) const { return 0; }

    void		refreshAccessorCache()
			{
			    emptyCache();
			    IlvAccessible::refreshAccessorCache();
			}
    IlList*		getCache(IlSymbol*) const;
    void		addToCache(const IlSymbol*, IlvAccessor*);
    void		buildCache();
    void		emptyCache();
    IlvValue&		queryValue(IlvValue& val) const;
    //    void		queryValues(IlvValue* values, IlUShort count) const;
    IlBoolean		changeValue(const IlvValue& val);
    //    IlBoolean	changeValues(const IlvValue* values, IlUShort count);

    IlvAccessorHolder*	_object;
    IlList		_accessors;  
    IlArray		_accCache;
};

// --------------------------------------------------------------------------
// IlvPrototypeAccessor		output a value when a callback is called
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvPrototypeAccessor : public IlvUserAccessor
{
public:
    IlvPrototypeAccessor(const char* name,
			 const IlvValueTypeClass* type,
			 IlvDisplay* display,
			 const char* protoname);
    virtual ~IlvPrototypeAccessor();

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;
    virtual IlBoolean	isPrivateValue(const IlSymbol* name) const;

    virtual void	initialize(const IlvAccessorHolder* object);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvPrototypeAccessor);

    inline
    IlvPrototypeAccessorHolder* getAccessorHolder() { return _holder; }
    inline
    const IlSymbol*	getDelegateName() { return _protoname; }

protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual void	queryValues(const IlvAccessorHolder* object,
				    IlvValue* values,
				    IlUShort count) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
    virtual IlBoolean	changeValues(IlvAccessorHolder* object,
				     const IlvValue* values,
				     IlUShort count);

    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlShort	matchValues(const IlvAccessorHolder* object,
				    const IlvValue* values,
				    IlUShort count,
				    IlvValue* matchingValues = 0) const;

    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				      const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;

    virtual void	filterValues(const IlvAccessorHolder* object,
				     IlvValue* values,
				     IlUShort& count) const;

    IlSymbol*			_protoname;
    IlvDisplay*			_display;
    IlvPrototypeAccessorHolder* _holder;
};

IlvDECLAREINITPROCLASS(protoacc)
#endif /* __Ilv_Protos_Protoacc_H */
