// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/hash.h
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
// Declaration of the hashing-related classes
// --------------------------------------------------------------------------
#ifndef __Il_Hash_H
#define __Il_Hash_H

#if !defined(__Il_Alloc_H)
#  include <ilog/alloc.h>
#endif

// --------------------------------------------------------------------------
class IlEntry
{
public:
    IlEntry(const IlAny tag, const IlAny value)
    : _tag((IlAny)tag),
      _value((IlAny)value),
      _next(0) {}
    IL_MLK_DECL();
    // ____________________________________________________________
    inline IlAny	getTag()   const { return _tag;   }
    inline IlAny	getValue() const { return _value; }
    inline IlEntry*	getNext()  const { return _next;  }

    inline void		setValue(const IlAny value) { _value = (IlAny)value; }
    inline void		setNext(IlEntry* next)      { _next = next; }
protected:
    IlAny		_tag;
    IlAny		_value;
    IlEntry*		_next;
};

// --------------------------------------------------------------------------
// IlBucket
// --------------------------------------------------------------------------
class IlBucket
{
public:
    IlBucket()
    : _length(0),
      _first(0)
    {}
    ~IlBucket() {
	if (_first)
	    delete _first;
    }
    IL_MLK_DECL();
    // ____________________________________________________________
    inline IlUInt	getLength() const { return _length; }
    inline IlEntry*	getFirst()  const { return _first; }

    IlUInt		_length;
    IlEntry*		_first;
};

#define IlHashDefaultMaxBucketLength    12
#define IlHashDefaultGrowingThreshold   (IlHashDefaultMaxBucketLength/2)
#define IlHashDefaultGrowingFactor      1.6
#define IlHashDefaultShrinkingThreshold 2
#define IlHashDefaultShrinkingFactor    2.0
#define IlHashDefaultBiggestSize        9239
#define IlHashDefaultLowestSize         17

// --------------------------------------------------------------------------
// IlHashTable
// --------------------------------------------------------------------------
typedef void (* IlHashMapFunction)(IlAny, IlAny, IlAny);
typedef IlBoolean (* IlHashMatchFunction)(IlAny value, IlAny userArg);

class ILOG_EXPORTED IlHashTable
{
public:
    IlHashTable(IlUInt nBuckets = IlHashDefaultLowestSize);
    virtual ~IlHashTable();
    // ____________________________________________________________
    inline IlBucket*	getBuckets() const   { return _buckets;  }
    inline IlUInt	numberOfBuckets() const { return _nBuckets; }
    inline IlUInt	getLength() const       { return _length;   }
    // Map on tag and value _______________________________________
    void		mapHash(IlHashMapFunction f, IlAny arg = 0) const;
    virtual void	insert(const IlAny tag, const IlAny value);
    virtual IlBoolean	replace(const IlAny tag, const IlAny value);
    virtual IlBoolean	contains(const IlAny tag) const;
    virtual IlBoolean	remove(const IlAny tag);
    virtual IlAny	find(const IlAny tag,
			     IlHashMatchFunction = 0,
			     IlAny userArg = 0) const;
    void		empty();
    IlAny*		convertToArray(IlUInt& count,
				       IlBoolean createArray=IlFalse) const;
protected:
    virtual IlBoolean	match(const IlAny target, const IlAny entry) const;
    virtual IlUInt	hash(const IlAny) const;
    void		growingReHash();
    void		shrinkingRehash();
    void		reHash(IlUInt newSize);
    void		insert(IlUInt hash,
			       const IlAny tag,
			       const IlAny value);
    IlBoolean		remove(IlUInt hash, const IlAny tag);
    void		init(IlUInt nBuckets = IlHashDefaultLowestSize);

    IlBucket*		_buckets;
    IlUInt		_nBuckets; // Number of buckets
    IlUInt		_length;   // Total number of entries
};

// --------------------------------------------------------------------------
// IlStringHashTable
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlStringHashTable : public IlHashTable
{
public:
    IlStringHashTable(IlUInt size)
    : IlHashTable(size)
    {}
    // ____________________________________________________________
    const char* const*	convertToStrings(IlUInt& count,
					 IlBoolean sortStrings = IlTrue,
					 IlBoolean createArray = IlFalse)
	const;

protected:
    IlBoolean		match(const IlAny target, const IlAny entry) const;
    IlUInt		hash(const IlAny) const;
};

// --------------------------------------------------------------------------
// IlSymbol
// --------------------------------------------------------------------------
class IlGlobalContext;
class ILOG_EXPORTED IlSymbol
{
public:
    inline const char*	name() const { return _name; }
    inline		operator const char*() const { return _name; }
    static IlSymbol*	Get(const char* name, IlBoolean createIt = IlTrue);
    inline IlUInt	getCache() const { return _cache; }
    inline void		setCache(IlUInt cache) { _cache = cache; }

private:
    char*		_name;
    IlUInt		_cache;

    IlSymbol(const char* name);
    ~IlSymbol();
    friend class IlGlobalContext;
};

inline IlSymbol*
IlGetSymbol(const char* name, IlBoolean createIt = IlTrue)
{
    return IlSymbol::Get(name, createIt);
}

#endif /* !__Il_Hash_H */
