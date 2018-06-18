// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/accessor.h
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
// Declaration of group accessors
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Accessor_H
#define __Ilv_Protos_Accessor_H

#if !defined(__Ilv_Protos_Value_H)
# include <ilviews/protos/value.h>
#endif

// ---------------------------------------------------------------------------
// Forward declarations.
// ---------------------------------------------------------------------------
class IlvAccessor;
class IlvMultipleAccessor;


// ---------------------------------------------------------------------------
// IlvAccessorHolder	A holder object for dynamic accessors.
//
// An IlvAccessorHolder is an IlvAccessible which holds IlvAccessors.
// IlvAccessors handle the side-effects of changing and querying values
// to/from the AccessorHolder, and can be added dynamically to the
// AccessorHolder.
//
// The AccessorHolder implements the change/query value methods by calling
// the corresponding methods of its associated accessors.
//
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvAccessorHolder : public IlvAccessible
{
    friend class IlvAccessor;
public:
#ifdef USE_CACHE
    IlvAccessorHolder():_accCache(0) {}
    ~IlvAccessorHolder();
#else
    IlvAccessorHolder(){}
#endif
    // Accessor methods ___________________________________________
    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);

    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlUInt	compareValues(const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;
    virtual
    IlvAccessor*	nextAccessor(IlAny& link) const = 0;

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    virtual
    IlvAccessorHolder*	getTopHolder() const;
    virtual IlList*	getAccessorList() const = 0;
    virtual IlList*	getClassAccList(IlAny&) const = 0;

#ifdef USE_CACHE    
    void		refreshAccessorCache()
			{
			    emptyCache();
			    IlvAccessible::refreshAccessorCache();
			}
    IlList*		getCache(IlSymbol*) const;
    void		addToCache(IlSymbol*, IlvAccessor*) const;
    void		emptyCache();
    IlBoolean		queryCache(IlvValue&) const;
    IlBoolean		changeCache(const IlvValue&);

    IlArray		_accCache;
#endif
};

// ---------------------------------------------------------------------------
// IlvAccessor	Generic "dynamic" accessor.
//
// A dynamic accessor is a logical input/output port used to interface
// with an \c IlvAccessorHolder using a simple name-based "change/query" API.
//
// For example, an \c IlvAccessorHolder representing a gauge could have
// an accessor called "gaugeValue". To change the gauge value, an
// application would do something like:
//
//	IlvValue val("gaugeValue");
//	gauge->queryValue(val);
//	val = (int)val + 10;
//	gauge->changeValue(val);
//
// Whereas \c IlvGraphic objects provide built-in accessors (e.g. "x", "foreground",
// etc.),
// an \c IlvAccessorHolder allows the application (or the user, or a sub-class) to
// define new accessors dynamically.
//
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvAccessor
{
    friend class IlvAccessorHolder;
public:
    IlvAccessor(const char* name, IlvValueTypeClass* type);
    virtual ~IlvAccessor();

    inline
    const IlSymbol*	getName() const { return _name; }

    inline void		setName(const IlSymbol* name) { _name = name; }

    inline
    IlvValueTypeClass*	getType() const { return _type; }

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;

    virtual IlBoolean	isOutputAccessor(IlBoolean& inputAndOutput);

    virtual IlShort	matchValues(const IlvAccessorHolder* object,
				    const IlvValue* values,
				    IlUShort count,
				    IlvValue* matchingValues = 0) const;

    virtual void	filterValues(const IlvAccessorHolder* object,
				     IlvValue* values,
				     IlUShort& count) const;

    inline void		setType(IlvValueTypeClass* nt) { _type = nt; }

protected:
    const IlSymbol*	_name;
    IlvValueTypeClass*	_type;

public:
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
    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				      const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;

};

// ---------------------------------------------------------------------------
// IlvMultipleAccessor		A multiple accessor defines the side effects
//				of changing or querying several values
//				in a single call. It can also be used to
//				set several values in a single changeValue
//				call: the IlvValue passed then contains an
//				array of IlvValues (not working yet?).
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvMultipleAccessor : public IlvAccessor
{
public:
    IlvMultipleAccessor(const char* name,
			IlUShort count,
			const char** names,
			IlvValueTypeClass** types);
    IlvMultipleAccessor(const char* name,
			IlUShort count,
			const char** names,
			IlvValueTypeClass*** types);
    ~IlvMultipleAccessor();

protected:
    IlUShort		_count;
    IlSymbol**		_names;
    IlvValueTypeClass** _types;

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlShort	matchValues(const IlvAccessorHolder* object,
				    const IlvValue* values,
				    IlUShort count,
				    IlvValue* matchingValues = 0) const;
};

#endif /* __Ilv_Protos_Accessor_H */
