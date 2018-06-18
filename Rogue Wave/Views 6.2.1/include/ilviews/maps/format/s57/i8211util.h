// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211util.h
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
// Rogue Wave Views - Maps add-on.
// --------------------------------------------------------------------------
#ifndef __Ilv_I8211util_H
#define __Ilv_I8211util_H

#include <ilviews/base/value.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>

#define ILVS57_OPTIMIZE

#ifdef ILVS57_OPTIMIZE
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211BasicEntry
{
public:
    IlvI8211BasicEntry(const IlString tag)
    : _tag(tag),
      _next(0) {}

    virtual ~IlvI8211BasicEntry() {}

    inline const IlString&	getTag()   const { return _tag;   }
    inline IlvI8211BasicEntry*	getNext()  const { return _next;  }

    inline void		setNext(IlvI8211BasicEntry* next) { _next = next; }

protected:
    IlString		_tag;
    IlvI8211BasicEntry*	_next;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Entry
: public IlvI8211BasicEntry
{
public:
    class ILVMAPSEXPORTED Value {
    public:
	virtual ~Value();
    };

    IlvI8211Entry(const IlString tag, Value* value)
    : IlvI8211BasicEntry(tag), _value(value) {}
    virtual ~IlvI8211Entry();

    inline Value*	getValue() const { return _value; }
    inline void		setValue(Value* value) { _value = value; }
protected:
    Value*		_value;
};
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211RefCount
{
public:
    IlvI8211RefCount();

    void	lock();
    void	unLock();    
protected:
    virtual	~IlvI8211RefCount();

    IlInt	_refCount;
};

#ifdef ILVS57_OPTIMIZE
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211EntryRefCounted
: public IlvI8211BasicEntry
{
public:
    IlvI8211EntryRefCounted(const IlString tag, IlvI8211RefCount* value);
    virtual ~IlvI8211EntryRefCounted();

    inline IlvI8211RefCount*	getValue() const { return _value; }
    void			setValue(IlvI8211RefCount* value);

protected:
    IlvI8211RefCount*		_value;
};


// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Bucket
{
public:
    IlvI8211Bucket()
    : _length(0),
      _first(0)
    {}
    ~IlvI8211Bucket()
    {
	if (_first)
	    delete _first;
    }

    inline IlUInt		getLength() const { return _length; }
    inline IlvI8211BasicEntry*	getFirst()  const { return _first; }

    IlUInt			_length;
    IlvI8211BasicEntry*		_first;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211HashTable
{
public:
    IlvI8211HashTable(IlUInt nBuckets = IlHashDefaultLowestSize);
    virtual ~IlvI8211HashTable();
    inline IlvI8211Bucket*	getBuckets() const { return _buckets;  }
    inline IlUInt		numberOfBuckets() const { return _nBuckets; }
    inline IlUInt		getLength() const { return _length;   }
    // Map on tag and value _______________________________________
    virtual void		insertRef(const IlString& tag,
					  IlvI8211RefCount* value);
    virtual void		insert(const IlString& tag,
				       IlvI8211Entry::Value* value);
    virtual IlBoolean		contains(const IlString& tag) const;
    virtual IlBoolean		remove(const IlString& tag);
    virtual IlAny		find(const IlString& tag) const;
    virtual IlvI8211RefCount*	findRef(const IlString& tag) const;
    void			empty();

protected:
    virtual IlUInt	hash(const IlString&) const;
    void		growingReHash();
    void		shrinkingRehash();
    void		reHash(IlUInt newSize);
    void		init(IlUInt nBuckets = IlHashDefaultLowestSize);

    IlvI8211Bucket* _buckets;
    IlUInt    _nBuckets; // Number of buckets
    IlUInt    _length;   // Total number of entries
};
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Tokenize
{
public:
    IlvI8211Tokenize();
    IlvI8211Tokenize(const char* s,
		     const char* delim,
		     IlBoolean   keep = IlFalse);
    ~IlvI8211Tokenize();

    void	initialize(const char* s, const char* delim);
    void	reset();

    const char*	token() const;
    char*	nextToken();
    IlBoolean	hasMoreToken() const;

protected:
    IlBoolean	_keep;
    char*	_buffToken;
    char*	_string;
    char*	_delim;
    char*	_cursor;
    char*	_token;
    IlInt	_count;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Rectangle
{
public:
    IlvI8211Rectangle();

    void	set(IlDouble x,
		    IlDouble y,
		    IlDouble w = 0.0,
		    IlDouble h = 0.0);

    IlDouble	getX() const;
    IlDouble	getY() const;
    IlDouble	getW() const;
    IlDouble	getH() const;

    IlDouble	getMinX() const;
    IlDouble	getMinY() const;
    IlDouble	getMaxX() const;
    IlDouble	getMaxY() const;

    IlBoolean	isNull() const;
    IlBoolean	contains(IlDouble, IlDouble) const;
    IlBoolean	intersects(const IlvI8211Rectangle&) const;

    void	add(IlDouble, IlDouble);

protected:
    IlDouble	_x;
    IlDouble	_y;
    IlDouble	_w;
    IlDouble	_h;
};

#ifdef ILVS57_OPTIMIZE
// --------------------------------------------------------------------------
enum IlvI8211TreeNodeStatus {
    IlvI8211TreeNodeBlackStatus,
    IlvI8211TreeNodeRedStatus,
    IlvI8211TreeNodeDupStatus
};

// --------------------------------------------------------------------------
class IlvI8211Tree;
class ILVMAPSEXPORTED IlvI8211TreeNode
{
 public:
    IlvI8211TreeNode(IlInt hight = 0,
		     IlInt low = 0,
		     IlvI8211RefCount* data = 0);

    inline IlvI8211TreeNode*	getNext() { return _next; }
    inline IlvI8211TreeNode*	getPrevious() { return _previous; }

    void			setData(IlvI8211RefCount*);
    inline IlvI8211RefCount*	getData() { return _data; }

    inline IlInt		getLowKey() { return _lowKey; }
    inline IlInt		getHightKey() { return _hightKey; }

    void			changeKey(IlInt hight, IlInt low);

 protected:
    friend class IlvI8211Tree;

    IlvI8211TreeNode*		_next;
    IlvI8211TreeNode*		_previous;
    IlvI8211TreeNode*		_left;
    IlvI8211TreeNode*		_right;
    IlvI8211TreeNode*		_parent;
    IlvI8211TreeNodeStatus	_status;

    IlInt			_lowKey;
    IlInt			_hightKey;
    IlvI8211RefCount*		_data;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Tree
{
 public:
    IlvI8211Tree();
    virtual ~IlvI8211Tree();


    IlvI8211TreeNode*	add(IlInt hight, IlInt low, IlvI8211RefCount *data);
    void		remove(IlvI8211TreeNode* node);
    void		removeAll();

    IlvI8211TreeNode*		find(IlInt hight, IlInt low);
    inline IlvI8211TreeNode*	getFirst() { return _first; }
    inline IlvI8211TreeNode*	getLast() { return _last; }
    IlvI8211TreeNode*		getNextUnique(IlvI8211TreeNode* node);
    IlvI8211TreeNode*		getPreviousUnique(IlvI8211TreeNode* node);

    void		replaceKey(IlvI8211TreeNode* node,
				   IlInt hight,
				   IlInt low);
    inline IlInt	getCount() { return _count; }

    virtual IlInt	compare(IlInt h1, IlInt l1, IlInt h2, IlInt l2);

 protected:
    void		rotateRight(IlvI8211TreeNode* node);
    void		rotateLeft(IlvI8211TreeNode* node);
    void		finalizeInsert(IlvI8211TreeNode* node);
    void		finalizeDelete(IlvI8211TreeNode* node);
    void		makeInsert(IlvI8211TreeNode* node);
    void		makeDelete(IlvI8211TreeNode* node);

    void		deleteInList(IlvI8211TreeNode* node);
    void		insertBeforeInList(IlvI8211TreeNode* before,
					   IlvI8211TreeNode* node);
    void		addAfterInList(IlvI8211TreeNode* after,
				       IlvI8211TreeNode* node);

    IlvI8211TreeNode*	getNextTree(IlvI8211TreeNode* node);
    IlvI8211TreeNode*	getPreviousTree(IlvI8211TreeNode* node);
    IlvI8211TreeNode*	getMinimumTree(IlvI8211TreeNode* node);
    IlvI8211TreeNode*	getMaximumTree(IlvI8211TreeNode* node);

    void		replaceNode(IlvI8211TreeNode* l, IlvI8211TreeNode* y);
    IlvI8211TreeNode*	createNode(IlInt hight,
				   IlInt low,
				   IlvI8211RefCount *data);

    IlvI8211TreeNode*	_first;
    IlvI8211TreeNode*	_last;
    IlvI8211TreeNode*	_root;
    IlvI8211TreeNode*	_empty;
    IlInt		_count;
};

#endif

#endif /* !__Ilv_I8211util_H */
