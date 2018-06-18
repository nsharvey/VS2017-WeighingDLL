// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/stateass.h
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
// Declaration of an associative array type used to store indexed items
// (for dictionaries).
// It is implemented here as an array of lists
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Stateass_H
#define __Ilv_States_Stateass_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_States_Gendefs_H)
#  include <ilviews/states/gendefs.h>
#endif
#if !defined(__Ilv_States_List_H)
#include <ilviews/states/list.h>
#endif

// assumptions  :
// - these are implementation classes, not abstract classes
// - abstract associative classes, as well as set types based on those
// may be added later
// - there is no undue information hiding
// - the table size is always a power of two (access is a bit faster cf. X11)

// - the indexation function is (a) local (field) to the hash table and
// is NOT implemented by objects themselves (as in Java for instance)
// - the comparison function follows the same rule

// data structures:
// the associative arrays are based on hash tables involving an array of
// lists. The implementation for lists guarantees that this is no more than
// an array of pointers (to links)

// the bucket chaining is intrusive :
// in this core implementation, the associative buckets are subclasses of
// IlvSuList (via IlvSuKeyList), and must be allocated by the user.
// more encapsulated versions can be derived from this hash table type

// there are two levels of abstraction : we first define IlvSuKeyList to
// implement tables of keys with no data associated, that may be used to
// implement sets, and then CassocList that adds data to it

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuKeyList
: public IlvSuList
{
    typedef IlvSuKeyList* self;
    typedef IlvSuList	  inherited;
    IlAny		  _Key;
public:
    IlvSuKeyList(IlAny k,
		 IlvSuKeyList* n=0)
	: IlvSuList(n),
	_Key(k)
	{}
      ~IlvSuKeyList()
	  {}
      // aspects
      ILVSTATES_READWRITE(IlAny, Key);
      // accessors
      selffield(Next);
      // no modifiers
};

// --------------------------------------------------------------------------
// predefined comparison and indexation functions
typedef IlInt (*Faddr_to_int)(void*); 	// returns an int from a pointer
typedef IlInt (*Fdistinct)(void*, void*); // compares two pointers by values

extern IlInt AssocStrToInt(void*); // makes an int from a string (like X11)
extern IlInt AssocStrDiff(void*, void*); // compares two strings

// --------------------------------------------------------------------------
// a class for getting statistics from hash tables
class ILVSTATESEXPORTED IlvSuKeyTable;
class ILVSTATESEXPORTED IlvSuKeyTableStatistics {
    friend class IlvSuKeyTable;
    int _Min;
    int _Max;
    int _NumAtMin;
    int _NumAtMax;
public:
    IlvSuKeyTableStatistics()
	: _Min(0),
	_Max(0),
	_NumAtMin(0),
	_NumAtMax(0)
    {}
    ILVSTATES_READONLY(int, Min);
    ILVSTATES_READONLY(int, Max);
    ILVSTATES_READONLY(int, NumAtMin);
    ILVSTATES_READONLY(int, NumAtMax);
};

// --------------------------------------------------------------------------
// the hash table core class
class ILVSTATESEXPORTED IlvSuKeyTable
{
    friend class IlvSuKeyTableIterator;
    IlInt         	_Size;   // as an exponent of two
    IlInt           	_Mask;  	// cached to avoid recomputations
    IlInt           	_Count;	// the number of items stored
    Faddr_to_int	_ToInt;  // a pointer to the indexation function
    Fdistinct		_Distinct;  // a pointer to the comparison function
    IlvSuKeyList     **	_Array;  // the reallocatable array of pointers
    IlvSuKeyList     *	_Found;	// a cache for the item found
    IlvSuKeyList     *	_Prev;	// a cache for the item before the one found
    IlInt           	_Location; // a cache for the index of the item found
public:
    //constructors
    IlvSuKeyTable(IlInt = 3,
		  Faddr_to_int = 0,
		  Fdistinct = 0);
    // note : the default value 3 indicates that default size is 8 (2^3)
    virtual ~IlvSuKeyTable();
    //accessors
    IlvSuKeyList* exists(void* key); // cannot be const because of caches
    IlvSuKeyList* getKey()   const { return _Found;}
    IlInt	  getCount() const { return _Count;}
    IlInt	  isEmpty()  const { return (_Count ? 0 : 1);}
    //modifiers
	// the pointer key must be unique (intrusively chained)
    void	  store(IlvSuKeyList*);
    void	  remove(void);    // the key found by exists
    void	  deleteR(void);   // deletes the table and all keyList objects
    //utility
    void  printStats(IlvSuKeyTableStatistics&) const; // fills the argument
};

// --------------------------------------------------------------------------
// the iterator type on hash tables,
class ILVSTATESEXPORTED IlvSuKeyTableIterator
{
    IlvSuKeyTable*	_Table;
    IlInt		_Index;
    IlvSuKeyList*  	_Current;
    void findFirst();
public:
    IlvSuKeyTableIterator(IlvSuKeyTable* t)
	: _Table(t),
	_Index(0),
	_Current(0)
    {
	findFirst();
    }
    void	  next();
    IlBoolean	  isPastEnd();
    IlvSuKeyList* get();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuAssocList
: public IlvSuKeyList
{
    typedef IlvSuAssocList* self;
    typedef IlvSuKeyList    inherited;
    IlAny		    _Data;
public:
    //constructors
    IlvSuAssocList(void* k,
		   IlAny d,
		   IlvSuKeyList* n=0)
	: IlvSuKeyList(k, n),
	_Data(d)
    {}
    ~IlvSuAssocList() {}
    // accessors
    IlAny getData() const { return _Data; }
    selffield(Next);
    // modifiers
    void setData(IlAny d) { _Data = d; }
};

#if 0
// --------------------------------------------------------------------------
// a class to automatically delete recursively tables
class ILVSTATESEXPORTED IlvSuKeyTableAutoDelete
{
    IlvSuKeyTable* _table;
public:
    IlvSuKeyTableAutoDelete(IlvSuKeyTable* t) : _table(t) {}
    IlvSuKeyTableAutoDelete(IlvSuKeyTable& t) : _table(&t) {}
    ~IlvSuKeyTableAutoDelete() { _table->deleteR(); }
};
#endif

// --------------------------------------------------------------------------
// a class to store into tables outside of functions
class ILVSTATESEXPORTED IlvSuKeyTableAutoStore
{
public:
    IlvSuKeyTableAutoStore(IlvSuKeyTable* t, IlvSuKeyList* l) { t->store(l); }
    IlvSuKeyTableAutoStore(IlvSuKeyTable& t, IlvSuKeyList* l) { t.store(l); }
    ~IlvSuKeyTableAutoStore() {}
};
#endif /* !__Ilv_States_Stateass_H */
