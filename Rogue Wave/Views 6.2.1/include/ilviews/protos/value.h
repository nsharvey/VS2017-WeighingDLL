// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/value.h
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
// Declaration of IlvValue fonctionalities and extensions for groups
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Value_H
#define __Ilv_Protos_Value_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Intrface_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Protos_Macros_H)
#include <ilviews/protos/macros.h>
#endif

// ---------------------------------------------------------------------------
// Debug macros
// ---------------------------------------------------------------------------
#ifndef TRACE
#ifdef DEBUG_PROTOS
#if defined(IL_STD)
#include <cstdio>
#else  /* !IL_STD */
#include <stdio.h>
#endif /* !IL_STD */
#define TRACE(l, x) if(DEBUG >= l) printf x
#else /* DEBUG */
#define TRACE(l, x)
#endif /* DEBUG */

#define DEBUG_NO_TRACE		0
#define DEBUG_MIN_TRACE		1
#define DEBUG_MED_TRACE		5
#define DEBUG_MAX_TRACE		10
#endif /* !TRACE */

// ---------------------------------------------------------------------------
// Macros used to create/delete temporary IlvValue objects without
// causing extraneous memory allocations/deallocations.
// ---------------------------------------------------------------------------

#define DECLARE_VALUE(v) IlvValue v("")
#if 0
#define COPY_VALUE(v1, v2) memcpy((char*)&(v1), (char*)&(v2), sizeof(IlvValue))
#define ALLOC_VALUES(n) (IlvValue*)calloc((unsigned int)n, sizeof(IlvValue))
#define FREE_VALUES(values) free((char*)values)
#else
#define COPY_VALUE(v1, v2) v1=v2
#define ALLOC_VALUES(n) new IlvValue [n]
#define FREE_VALUES(values) delete [] values
#endif
#define SET_VALUE_NAME(v, s) (v)._name = (s)
#define SET_VALUE_TYPE(v, t) (v)._type = (t)
#define DECLARE_TMP_VALUE(tmpval, value, name) \
		DECLARE_VALUE(tmpval); \
		COPY_VALUE(tmpval, value); \
		SET_VALUE_NAME(tmpval, IlvGetSymbol(name))
#if 0
#define DELETE_TMP_VALUE(tmpval) SET_VALUE_TYPE(tmpval, IlvValueNoType)
#else
#define DELETE_TMP_VALUE(tmpval) 
#endif
// ---------------------------------------------------------------------------
// IlvValueArray	A dynamic array of IlvValues.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvValueArray
{
public:
    IlvValueArray() : _values(0), _count(0), _max(0) {}
    IlvValueArray(const IlvValueArray& source);
    ~IlvValueArray();

    void		add(IlvValue& v, IlBoolean copy = IlTrue);
    inline IlvValue&	get(IlUInt i) const { return(_values[i]); }
    inline
    IlvValue& operator	[](IlUInt i) const { return(_values[i]); }
    inline IlUInt	count() const { return(_count); }
    inline IlvValue*	getValues() const { return(_values); }
protected:
    IlvValue* _values;
    IlUInt _count;
    IlUInt _max;
};

// ---------------------------------------------------------------------------
// IlvValueSubscription	Internal class: one entry in a subscription list
//				for a given value.
// ---------------------------------------------------------------------------

class IlvAccessible;

typedef enum IlvValueSubscriptionMode {
    IlvValueSubscriptionNone		= 0x0,
    IlvValueSubscriptionChange		= 0x1,
    IlvValueSubscriptionQuery		= 0x2,
    IlvValueSubscriptionInternal	= 0x10,
    IlvValueSubscriptionRunTime		= 0x20
} _IlvValueSubscriptionMode;

// ---------------------------------------------------------------------------
// IlvAccessible	An object with an IlvValue-based interface.
// ---------------------------------------------------------------------------

typedef void (*IlvValueChangeHook)(IlBoolean before, IlAny arg);

class IlvSubscriptionInputFile;
class IlvSubscriptionOutputFile;

class ILVPROEXPORTED IlvAccessible : public IlvValueInterface
{
    friend class IlvSubscriptionInputFile;
    friend class IlvSubscriptionOutputFile;
public:
    IlvAccessible() : _sources(), _subscriptions() {}
    virtual ~IlvAccessible();

    virtual const char*	getName() const = 0;
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual void	queryValues(IlvValue* v, IlUShort c) const;
    virtual IlBoolean	changeValue(const IlvValue& v);
    virtual IlBoolean	changeValues(const IlvValue* v, IlUShort c);
    virtual IlBoolean	applyValue(const IlvValue& v);
    virtual void	getAccessors(const IlSymbol* const** a,
				     const IlvValueTypeClass* const** t,
				     IlUInt& c) const = 0;
    virtual IlBoolean	isOutputValue(const IlSymbol* value) const;
    virtual IlUInt	compareAllValues(const IlvAccessible* ref,
					 IlvValueArray& diffs,
					 IlBoolean any=IlFalse)
	const;
    virtual IlUInt	compareValues(const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;
    virtual IlBoolean	convertValues(IlvValue* v,
				      IlUShort c,
				      IlvDisplay* d) const;
    virtual const IlvValueTypeClass* getValueType(const IlSymbol* s) const;
    static IlBoolean	ValuesAreEqual(IlvValue& v1,
				       IlvValue& v2,
				       IlBoolean compareNames = IlTrue);
    static IlBoolean	StringToValue(const char* s,
				      IlSymbol* type,
				      IlvValue& v,
				      IlvDisplay* display);
    static IlBoolean	StringToValue(const char* s,
				      const IlvValueTypeClass* typeClass,
				      IlvValue& v,
				      IlvDisplay* d);

    static const IlvValueTypeClass* GetType(IlSymbol* name);

    virtual void	subscribe(IlvAccessible* subscriber,
				  IlSymbol* sourceValue,
				  IlSymbol* subscriberValue,
				  IlvValueTypeClass* type,
				  IlvValueSubscriptionMode mode
				  = IlvValueSubscriptionChange);
    virtual void	subscribeByName(const char* subscriberName,
					IlSymbol* sourceValue,
					IlSymbol* subscriberValue,
					IlvValueTypeClass* type,
					IlvValueSubscriptionMode mode
					= IlvValueSubscriptionChange);
    virtual void	unSubscribe(IlvAccessible* subscriber,
				    IlSymbol* sourceValue = 0,
				    IlSymbol* subscriberValue = 0);
    virtual void	unSubscribeByName(const char* subscriber,
					  IlSymbol* sourceValue = 0,
					  IlSymbol* subscriberValue = 0);
    IlUInt		getSubscriptions(IlvAccessible* subscriber,
					 IlSymbol**& sourceValue,
					 IlSymbol**& subscriberValue,
					 IlvValueTypeClass**& type,
					 IlvValueSubscriptionMode*& mode,
					 IlvAccessible*** subscribers=0)const;
    IlUInt		getSubscriptionCount(IlvAccessible* subscriber = 0);

    static void		DelayedSubscribe(IlSymbol* sourceName,
					 IlAny holder,
					 IlvAccessible* subscriber,
					 IlSymbol* sourceValue,
					 IlSymbol* subscriberValue,
					 IlvValueTypeClass* type,
					 IlvValueSubscriptionMode mode
					 = IlvValueSubscriptionChange);
    static void		DelayedUnSubscribe(IlSymbol* sourceName,
					   IlAny holder,
					   IlvAccessible* subscriber,
					   IlSymbol* sourceValue = 0,
					   IlSymbol* subscriberValue = 0);
    virtual IlBoolean	pushValue(const IlvValue& v) const;
    virtual IlBoolean	pushValues(const IlvValue* vals, IlUShort c) const;
    virtual IlvValue&	pullValue(IlvValue& v) const;
    virtual void	pullValues(IlvValue* vals, IlUShort c) const;

    static void		DeclareAccessor(const IlSymbol* attr,
					IlvValueTypeClass* type,
					const IlSymbol* const** accessors,
					const IlvValueTypeClass* const** types,
					IlUInt& count,
					IlBoolean checkDuplicates = IlFalse,
					IlAny accessorList = 0);

    static IlAny	PushAccessorList();	// returns old list
    static void		PopAccessorList(IlAny oldList);

    inline
    static IlBoolean	HasDelayedSubscriptions()
			{
			    return(_delayedSubscriptions != 0);
			}

    IlvAccessible**	getSources(IlUInt& count);

    void		callValueChangeHooks(IlBoolean before) const;

    static void		AddValueChangeHook(IlvValueChangeHook hook, IlAny arg);
    static void		RemoveValueChangeHook(IlvValueChangeHook hook,
					      IlAny arg);

    void		getCachedAccessors(const IlSymbol* const** accessors,
					   const IlvValueTypeClass* const**,
					   IlUInt& count) const;
    static IlBoolean	IsAccessorCacheEnabled();
    static void		SetAccessorCacheEnabled(IlBoolean enabled);
    virtual
    IlvAccessible*	resolveSubscription(const char*) const;
    void		deleteAllSubscriptions();

protected:
    void		addSource(IlvAccessible* source);
    void		removeSource(IlvAccessible* source);

    virtual void	deleteNotify(IlvAccessible* deleted);
    void		copySubscriptions(const IlvAccessible& source,
					  const IlvAccessible* subscriber = 0);

    static void		RemoveSubscriptions(IlvAccessible* source,
					    IlList* list,
					    IlvAccessible* subscriber,
					    IlSymbol* subscriberValue);

    virtual void	readSubscription(IlvSubscriptionInputFile& f,
					 IlvValueSubscriptionMode mask
					 = IlvValueSubscriptionNone);
    virtual void	writeSubscriptions(IlvSubscriptionOutputFile& f,
					   IlvValueSubscriptionMode mask
					   = IlvValueSubscriptionNone);

    static void		ResolveDelayedSubscription(IlvAccessible* object,
						   IlAny holder);

    // Cache for accessor types (to speed up scripts):
    //
    void		setCachedAccessors(const IlSymbol* const* accessors,
					   const IlvValueTypeClass* const*,
					   IlUInt count) const;

    virtual IlAny	getAccessorCache() const;
    virtual void	setAccessorCache(IlAny);
    virtual void	refreshAccessorCache();

    IlList		_sources;
    IlAList		_subscriptions;

    static IlvList*	_delayedSubscriptions;

    static IlvList*	_valueChangeHooks;

    friend struct _IlvSubscription;
};

// ---------------------------------------------------------------------------
// IlvSubscriptionInputFile	Input context for subscriptions
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvSubscriptionInputFile
{
    friend class IlvAccessible;

public:
    IlvSubscriptionInputFile(ILVSTDPREF istream& stream) : _str(&stream) {}
    virtual ~IlvSubscriptionInputFile();

    void		setStream(ILVSTDPREF istream& stream)
			{
			    _str = &stream;
			}
    ILVSTDPREF istream&	getStream() { return(*_str); }
    void		readSubscriptions();

protected:
    virtual
    IlvAccessible*	getSubscriber(const char*);
    virtual
    IlvValueSubscriptionMode getMask();

    ILVSTDPREF istream*	_str;
};

// ---------------------------------------------------------------------------
// IlvSubscriptionOutputFile	Output context for subscriptions
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvSubscriptionOutputFile
{
    friend class IlvAccessible;

public:
    IlvSubscriptionOutputFile(ILVSTDPREF ostream& stream)
	: _str(&stream),
	  _indent(0),
	  _label("Subscriptions")
    {}

    virtual ~IlvSubscriptionOutputFile();

    void		setStream(ILVSTDPREF ostream& stream)
			{
			    _str = &stream;
			}
    ILVSTDPREF ostream& getStream() { return(*_str); }

    void		writeSubscriptions(IlvAccessible** subscribees,
					   IlUInt count);

    void		addIndent(int d);

    const char*		getLabel() { return(_label); }
    void		setLabel(const char* label) { _label = label; }

protected:
    virtual IlvValueSubscriptionMode getMask()
			{
			    return(IlvValueSubscriptionInternal);
			}

    void		indent();

    ILVSTDPREF ostream*	_str;
    int			_indent;
    const char*		_label;
};

// ---------------------------------------------------------------------------
// IlvCallbackSubscriber     A subscriber object that calls a callback.
// ---------------------------------------------------------------------------
class IlvCallbackSubscriber;

typedef void (*IlvValueCallback)(IlvCallbackSubscriber* subscriber,
				 IlvValue* vals,
				 IlUShort count,
				 IlAny arg,
				 IlBoolean query);

class ILVPROEXPORTED IlvCallbackSubscriber : public IlvAccessible
{
public:
    IlvCallbackSubscriber(IlvValueCallback callback,
			  IlAny arg)
	: _callback(callback),
	  _arg(arg) {}

    virtual const char*	getName() const { return(""); }

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);

    virtual void	getAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&) const {}

protected:
    IlvValueCallback	_callback;
    IlAny		_arg;
};

// ---------------------------------------------------------------------------
// Utility functions.
// ---------------------------------------------------------------------------

extern void _IlvPrototypeExpandPath(const char* path, char* buffer);

extern ILVPROEXPORTEDFUNCTION(const char*)
    _IlvGetProtoMessage(IlvDisplay* display,
			const char* id,
			const char* msg);

#endif /* __Ilv_Protos_Value_H */
