// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/array.h
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
// Declaration of the IlArray class: A generic, type-safe efficient
// stl-like implementation of expensible arrays.
// --------------------------------------------------------------------------
#ifndef __Il_Array_H
#define __Il_Array_H

#if !defined(__Il_Memory_H)
#  include <ilog/memory.h>
#endif

#if defined(IL_STD)
#  include <new>
#else  /* !IL_STD */
#  include <new.h>
// for void* new (size_t, void*)
#endif /* IL_STD */

// --------------------------------------------------------------------------
// Internal macros.
#define IlInternalArrayDeclareHead(Name) 				\
Name { 									\
public:									\
    Name(IlUInt startLength = 4) : _array(0), _maxLength(0), _length(0)	\
    	{ setMaxLength(startLength); }					\
    Name(const Name& a):_array(0),_maxLength(0),_length(0) {(*this)=a;}

#define IlInternalArrayDeclareMainMembers(Type,Name)   		\
public:								\
    ~Name();							\
    Name&   operator=(const Name&);				\
    void    setMaxLength(IlUInt nlen, IlBoolean exact=IlTrue);	\
    void    setData(Type*, IlUInt, IlUInt=(IlUInt) -1);		\
    void    erase(IlUInt from=0, IlUInt to=(IlUInt)-1);		\
    void    insert(const Type* src, IlUInt len, IlUInt rank);

#define IlInternalArrayDeclareMembers(Type,Name) 			\
private:								\
    Type*   _array;							\
    IlUInt _maxLength;							\
    IlUInt _length;							\
public:									\
/* accessors */ 						    	\
inline IlUInt getMaxLength() const { return _maxLength; }		\
inline IlUInt getLength() const { return _length; }			\
inline Type* getArray() const { return _array; }			\
inline Type& operator[](IlUInt rank) { return _array[rank]; }		\
inline Type  operator[](IlUInt rank) const { return _array[rank]; }	\
inline Type& top() { return _array[_length-1]; }			\
/* modifiers */  							\
inline Type* exportData() 						\
    { Type* res = _array; _array = 0; setData(0, 0); return res; }	\
inline void grow() { setMaxLength(_maxLength*2, IlFalse); }		\
inline void compact() { setMaxLength(_length, IlTrue); }		\
inline void insert(const Name& src, IlUInt rank) 			\
    { insert(IL_CAST(const Type*, IL_CAST(IlAny, src.getArray())),	\
	     src.getLength(),rank); }					\
inline void append(const Name& src) 					\
    { insert(IL_CAST(const Type*, IL_CAST(IlAny, src.getArray())),	\
	     src.getLength(),_length);} 				\
inline void append(const Type* src, IlUInt l)				\
	{ insert(src, l, _length); }					\
inline void add(const Type value) 					\
	{ insert(&value, (IlUInt)1, _length); }				\
inline void insert(IlUInt rank, const Type& value) 			\
	{ insert(&value, (IlUInt)1, rank); }				\
inline void remove(IlUInt rank) { erase(rank, rank+1); }		\
inline void clear() { erase(); }					\
inline void empty() { erase(); }					\
inline void pop() { if (_length > 0) erase(_length - 1, _length); }	\
inline void push(const Type& value) 					\
	{ insert(&value, (IlUInt)1, _length); }

// --------------------------------------------------------------------------
// Main macros (declaration)
#define IlDeclareArrayOf(Type,Name)	 		\
    IlInternalArrayDeclareHead(Name)			\
    IlInternalArrayDeclareMainMembers(Type,Name)	\
    IlInternalArrayDeclareMembers(Type,Name) 		\
}

#define IlDeclareArrayWithoutEquality(Type,Name) 	\
	IlDeclareArrayOf(Type,Name)

// --------------------------------------------------------------------------
// Implementation macros
#define IlImplementArrayOf(T,N) 				\
N::~N() 							\
{ 								\
    if (_array) { 						\
	for (IlUInt i=0; i<_length;i++)	{ _array[i].~T(); }	\
	IlFree(_array); 					\
    }								\
}								\
void N::setData(T* a, IlUInt l, IlUInt m) 			\
{ 								\
    this->~N();    						\
    _length = l;						\
    _maxLength = (m==(IlUInt)-1)?l:m;				\
    _array=a; 							\
}								\
N& N::operator=(const N& src)	 				\
{ 								\
    this->~N();							\
    _maxLength   = src._maxLength;				\
    _length      = src._length;					\
    if (_length > 0) { _array = IL_MALLOC(T, _maxLength); }	\
    else { _array=0; _maxLength=0; }				\
    for (IlUInt i=0; i<_length;i++) {				\
	new (_array + i) T(src._array[i]); }			\
    return *this;						\
}								\
void N::setMaxLength(IlUInt nlen, IlBoolean exact)		\
{ 								\
    if (nlen < _length) return;					\
    if (!exact) { 						\
    	if (nlen < 4) nlen=4;					\
	IlUInt tlen=4;						\
	while (tlen < nlen) { tlen*=2; }			\
 	nlen=tlen;						\
    }								\
    if (nlen == _maxLength) { return; }				\
    if ((nlen == 0) && _array) {				\
  	for (IlUInt i=0; i<_length;i++) { _array[i].~T(); }	\
	IlFree(_array);						\
  	_array=0;						\
    } else if (_array) {					\
    	T* op = _array;						\
	_array = IL_MALLOC(T, nlen);				\
	for (IlUInt i=0; i<_length;i++) {			\
	    new (_array + i) T(op[i]);				\
	    op[i].~T();						\
	} 							\
	IlFree(op);						\
    } else { _array = IL_MALLOC(T,nlen); }			\
    _maxLength = nlen;						\
}								\
void N::erase (IlUInt from, IlUInt to)		 		\
{ 								\
    if (to > _length || to < from) { to = _length; } 		\
    if (to < _length) {						\
    	for (IlUInt i=0; i < _length - to;i++) {		\
	    _array[from+i]=_array[to+i]; } }			\
    for (IlUInt i = _length - (to - from); i < _length; i++) {	\
	_array[from+i].~T(); }					\
    _length -= to - from;					\
    if (_maxLength >= _length*4) {				\
	setMaxLength(_length, IlFalse); }			\
}								\
void N::insert(const T* src, IlUInt len, IlUInt at)		\
{ 								\
    if (len == 0) { return; }					\
    if (at > _length) { at = _length; }				\
    if (_length + len > _maxLength) {				\
    	setMaxLength(_length + len, IlFalse); }			\
    if (_length > at) {						\
	for (IlUInt i=_length-1; i >= at; i--) {		\
	    new (_array+i+len) T (_array[i]); } }		\
    IlUInt i;							\
    for (i=at; i<_length;i++) { _array[i] = src[i-at]; }	\
    for (; i<_length+len;i++) { new (_array+i) T (src[i-at]); }	\
    _length += len;						\
}

// --------------------------------------------------------------------------
// Amorphic implementation.
#define IlImplementAmorphicArrayOf(T,N) 			\
N::~N() { if (_array) IlFree(_array); }				\
void N::setData(T* a, IlUInt l, IlUInt m) 			\
{ 								\
    if (_array) { IlFree(_array); } 				\
    _array = a; 						\
    _length = l;						\
    _maxLength = (m == (IlUInt)-1) ? l : m;			\
}								\
N& N::operator=(const N& src)	 				\
{ 								\
    if (_array) { IlFree(_array); } 				\
    _maxLength   = src._maxLength;				\
    _length      = src._length;					\
    if (_length > 0) { _array = IL_MALLOC(T, _maxLength); } 	\
    else { _array=0; _maxLength=0; }				\
    IlMemMove(_array, src._array, _length * sizeof(T));		\
    return *this;						\
}								\
void N::setMaxLength(IlUInt nlen, IlBoolean exact)	 	\
{ 								\
    if (nlen < _length) return;					\
    if (!exact) { 						\
    	if (nlen < 4) { nlen = 4; }				\
	IlUInt tlen = 4;					\
	while (tlen < nlen) { tlen *= 2; }			\
 	nlen = tlen;						\
    }								\
    if (nlen == _maxLength) { return; }				\
    if ((nlen == 0) && _array) { 				\
	IlFree(_array);						\
  	_array=0;						\
    } else if (_array) { _array = IL_REALLOC(T, _array, nlen); }\
    else { _array = IL_MALLOC(T, nlen); }			\
    _maxLength = nlen;						\
}								\
void N::erase(IlUInt from, IlUInt to)			 	\
{ 								\
    if ((to > _length) || (to < from)) { to = _length; }	\
    if (to < _length) {						\
	IlMemMove(IL_REINTERPRETCAST(char*, _array)		\
		    + (from * sizeof(T)),			\
		  IL_REINTERPRETCAST(const char*, _array)	\
		    + (to * sizeof(T)),				\
		  (_length - to) * sizeof(T)); }		\
    _length -= to - from;					\
    if (_maxLength >= _length*4) {				\
	setMaxLength(_length, IlFalse); }			\
}								\
void N::insert(const T* src, IlUInt len, IlUInt at)		\
{ 								\
    if (len == 0) { return; }					\
    if (at > _length) { at = _length; }				\
    if (_length + len > _maxLength) {				\
	setMaxLength(_length + len, IlFalse); }			\
    if (_length > at) {						\
    	IlMemMove(IL_REINTERPRETCAST(char*, _array)		\
		    + ((at + len) * sizeof(T)),			\
		  IL_REINTERPRETCAST(const char*, _array)	\
		    + (at * sizeof(T)),				\
		  (_length - at) * sizeof(T)); }		\
    IlMemMove(IL_REINTERPRETCAST(char*, _array)+(at*sizeof(T)),	\
	      src, len * sizeof(T));				\
    _length += len;						\
}

// --------------------------------------------------------------------------
// The array of IlAny class
class ILOG_EXPORTED IlInternalArrayDeclareHead(IlArray)

    IlInternalArrayDeclareMainMembers(IlAny,IlArray)

    IlInternalArrayDeclareMembers(IlAny,IlArray)

    IlUInt getIndex(const void*) const;
    inline void remove(const void* value) { 
	IlInt ndx = (IlInt)getIndex(value);	
	if (ndx != -1) {
	    remove((IlUInt)ndx);
	}
    }
};

// --------------------------------------------------------------------------
// Arrays of pointers:
#define IlDeclareAndImplementArrayOfPointerTo(Type,Name)		\
IlInternalArrayDeclareHead(Name)					\
inline ~Name() {  if (_array) IlFree(_array); }				\
inline void setData(Type** a, IlUInt l, IlUInt m=(IlUInt)-1) 		\
{ 									\
    IL_CAST(IlArray*, IL_CAST(void*, this))->setData((IlAny*)a, l, m);	\
}									\
inline Name& operator=(const Name& src)	 				\
{ 									\
    *(IL_CAST(IlArray*, IL_CAST(void*, this))) =			\
	*(IL_CAST(const IlArray*, IL_CAST(const void*, &src)));		\
    return *this;							\
}									\
inline void setMaxLength(IlUInt n, IlBoolean e=IlTrue)			\
{ 									\
    IL_CAST(IlArray*, IL_CAST(void*, this))->setMaxLength(n, e);	\
}									\
inline void erase (IlUInt from = 0, IlUInt to = (IlUInt)-1)		\
{ 									\
    IL_CAST(IlArray*, IL_CAST(void*, this))->erase(from,to);		\
}									\
inline void insert(const Type** src, IlUInt len, IlUInt at)		\
{ 									\
    IL_CAST(IlArray*, IL_CAST(void*, this))				\
	->insert(IL_CAST(const IlAny*, IL_CAST(void*, src)), len, at);	\
}									\
inline IlUInt getIndex(const Type* value) const 			\
{ 									\
    return IL_CAST(const IlArray*, IL_CAST(const void*, this)) 		\
	->getIndex(IL_CAST(const void*, value));			\
}									\
inline void remove(const Type* value) { 				\
	 IlUInt ndx = getIndex(value);					\
    	 if (ndx != (IlUInt)-1) { remove(ndx); }			\
    }									\
    IlInternalArrayDeclareMembers(Type*,Name) 				\
}

// --------------------------------------------------------------------------
// Bit arrays have a whole different implementation
class ILOG_EXPORTED IlBitArray
{
public:
    IlBitArray(IlUInt length, IlBoolean initialState = IlFalse);
    IlBitArray(const IlBitArray&);
    virtual ~IlBitArray();
    // ____________________________________________________________
    IlUInt		getLength() const { return _length; }
    void		setLength(IlUInt newLength,
				  IlBoolean newState = IlFalse);
    IlBoolean		isSet(IlUInt rank) const;
    void		set(IlUInt rank, IlBoolean flag);
    void		invert(IlUInt rank);
    inline void		set(IlUInt rank)   { set(rank, IlTrue);  }
    inline void		unset(IlUInt rank) { set(rank, IlFalse); }
    inline IlBoolean	operator[](IlUInt rank) const { return isSet(rank); }
    inline void		operator+=(IlUInt rank) { set(rank); }
    inline void		operator-=(IlUInt rank) { unset(rank); }

private:
    IlUInt		_length;
    unsigned char*	_bits;
};

#endif /* !__Il_Array_H */
