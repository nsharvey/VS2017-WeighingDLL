// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/refcount.h
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
// Definitions of classes used for reference counting.
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Refcount_H
#define __Ilv_Util_Refcount_H

#if !defined(__ILV_Macros_H)
#include <ilviews/macros.h>
#endif /* !__Ilv_Macros_H */
#if !defined(__Ilv_Hash_H)
#include <ilviews/base/hash.h>
#endif /* !__Ilv_Hash_H */

#if defined(ILVBUILDLIBS)
#define ILVREFCOUNTEXPORTED IL_BASEEXPORTED
#else  /* !ILVBUILDLIBS */
#define ILVREFCOUNTEXPORTED IL_BASEIMPORTED
#endif /* !ILVBUILDLIBS */
// --------------------------------------------------------------------------
template<class LOCKABLE> class ILVREFCOUNTEXPORTED IlvRefCountPtr
{
public:
    ILVEXPLICIT IlvRefCountPtr(LOCKABLE* ptr = 0)
	: _ptr(ptr), _counter(0)
    {
#if defined(ILVSTD)
	try {
#endif /* ILVSTD */
	    _counter = new long(1);
#if defined(ILVSTD)
	} catch (...) {
#endif /* ILVSTD */
	    if (ptr)
		delete ptr;
#if defined(ILVSTD)
	    throw;
	}
#endif /* ILVSTD */
    }
    IlvRefCountPtr(const IlvRefCountPtr& src)
#if defined(ILVSTD)
	throw()
#endif /* ILVSTD */
    : _ptr(src._ptr), _counter(src._counter)
    {
	++*_counter;
    }
    ~IlvRefCountPtr() { dispose(); }
    IlvRefCountPtr& operator	=(const IlvRefCountPtr& src)
			{
			    share(src._ptr, src._counter);
			    return *this;
			}
    IlvRefCountPtr& operator	=(LOCKABLE* ptr)
			{
			    share(ptr, new long(1));
			    return *this;
			}
    LOCKABLE& operator	*() const
#if defined(ILVSTD)
	throw()
#endif /* ILVSTD */
    { return *_ptr; }
    LOCKABLE* operator	->() const
#if defined(ILVSTD)
	throw()
#endif /* ILVSTD */
    { return _ptr;  }
    LOCKABLE*		get() const
#if defined(ILVSTD)
	throw()
#endif /* ILVSTD */
    { return _ptr;  }

protected:
    // This function sets a new object to be pointed to by this
    // instance. It first decrements the counter associated to the
    // previous object if any, and delete if needed. Then it
    // increments the counter given as second parameter and stores the
    // pointer to the object and the counter.
    void		share(LOCKABLE* ptr, long* counter)
			{
			    if (_counter != counter) {
				dispose();
				_ptr = ptr;
				++*(_counter = counter);
			    }
			}

private:
    void		dispose()
			{
			    if (!--*_counter) {
				delete _ptr;
				delete _counter;
			    }
			}

    LOCKABLE*		_ptr;
    long*		_counter;
};

// --------------------------------------------------------------------------
// Auxiliary class that use a counter initialized out of the class.
template<class LOCKABLE> class ILVREFCOUNTEXPORTED IlvInitializedRefCountPtr
    : public IlvRefCountPtr<LOCKABLE>
{
public:
    // The constructor.
    IlvInitializedRefCountPtr(LOCKABLE* ptr, long* counter)
	: IlvRefCountPtr<LOCKABLE>()
    {
	share(ptr, counter);
    }

private:
    // These two functions are intentionally not defined.
    IlvInitializedRefCountPtr(const IlvInitializedRefCountPtr<LOCKABLE>&);
    const IlvInitializedRefCountPtr&
	operator=(const IlvInitializedRefCountPtr<LOCKABLE>&);
};

// --------------------------------------------------------------------------
template<class OBJECT, int HASHSIZE = 7> class ILVREFCOUNTEXPORTED IlvOwnership
{
    // Definitions of typedefs to simplify the code.
    typedef IlvRefCountPtr<IlvOwnership<OBJECT, HASHSIZE> > CntPtr;
    typedef IlvInitializedRefCountPtr<IlvOwnership<OBJECT, HASHSIZE> >
		InitCntPtr;
    // Instances of this structure are kept as value in the hash
    // table.
    // See the comments of the static function factory for more
    // precisions.
    struct Info {
	// The constructor. It creates a new counter set to 0.
	Info(IlvOwnership<OBJECT, HASHSIZE>* ownership)
	    : _ownership(ownership),
	      _counter(new long(0))
	{}
	// The ownership object.
	IlvOwnership<OBJECT, HASHSIZE>*	_ownership;
	// The counter given to the IlvRefCountPtr.
	long*	_counter;
    };

public:
    ~IlvOwnership()
    {
	// Get the instance of the struct info associated to the ownership.
	Info* val = ILVREINTERPRETCAST(Info*, _Hash->find(_object));
	// Delete this instance.
	delete val;
	// Remove the object from the hash table.
	_Hash->remove(_object);
	// Check whether the hash table is empty.
	if (!_Hash->getLength()) {
	    // In this case, delete the hash table.
	    delete _Hash;
	    _Hash = 0;
	}
	// If the ownership property is true then delete the object
	// pointed to by this instance.
	if (_owner)
	    delete _object;
    }
    OBJECT& operator	*()	const { return *get();  }
    OBJECT* operator	->()	const { return get();   }
    OBJECT*		get()	const { return _object; }
    IlBoolean		isOwner() const { return _owner;  }
    static CntPtr	Factory(OBJECT* object, IlBoolean owner = IlTrue) 
    {
	// This class uses a hash table which is stores as a static
	// member of the class (that means there is one hash table by
	// type given as template parameter).
	// The adresse of the object is used as key of the hash table,
	// and the value is an instance of the strut info that stores
	// a pointer to the \c IlvOwnership and a pointer to the
	// counter
	// used by the \c IlvRefCountPtr that is returned.

	// Is the pointer null?
	if (!object) {
	    // In this case return a special instance.
	    static CntPtr NullPtr(0);
	    return NullPtr;
	}
	// Must we build the hash table?
	if (!_Hash)
	    // Build the hash table.
	    _Hash = new IlvHashTable(HASHSIZE);
	// Checks whether the object was already in the hash table. If
	// the object is found, then a pointer to a struct info is
	// returned.
	Info* info = ILVREINTERPRETCAST(Info*, _Hash->find(object));
	if (info) {
	    // The object was already in the hash table.
	    if (owner)
		// If the ownership property given as parameter is
		// true then the ownership property of the
		// IlvOwnership instance is set, otherwise it keeps
		// its previous version (it is equivalent to a logical
		// or between the two values).
		info->_ownership->setOwner();
	} else {
	    // The object was not yet in the hash table.
	    // We build a new instance of IlvOwnership and a new
	    // instance of the struct info that points to this
	    // instance of IlvOwnership. The counter is set to 0 by
	    // the constructor of info.
	    info = new Info(new IlvOwnership(object, owner));
	    // The object is inserted into the hash table.
	    _Hash->insert(object, info);
	}
	// Return an instance of IlvRefCountPtr initialized with the
	// counter of the struct info. This is done through the
	// auxiliary class IlvInitializedRefCountPtr that increments
	// the counter.
	return InitCntPtr(info->_ownership, info->_counter);
    }
    void		setOwner(IlBoolean owner = IlTrue) { _owner = owner; }

protected:
    IlvOwnership(OBJECT* object, IlBoolean owner)
    : _object(object),
      _owner(owner)
    {}
    // The internal hash table. The hashing is done on the pointer of
    // the object.
    static
    IlvHashTable*	_Hash;

private:
    // These two functions are intentionally not defined.
    IlvOwnership(const IlvOwnership<OBJECT, HASHSIZE>&);
    IlvOwnership<OBJECT, HASHSIZE>& operator=(const IlvOwnership<OBJECT, HASHSIZE>&);

    // The pointer to the object.
    OBJECT*		_object;
    // The ownership property.
    IlBoolean		_owner;

};

#endif /* !__Ilv_Util_Refcount_H */
