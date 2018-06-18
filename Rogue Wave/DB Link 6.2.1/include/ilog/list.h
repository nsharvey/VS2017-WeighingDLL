// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/list.h
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
// Declaration of the list-related classes
// --------------------------------------------------------------------------
#ifndef __Il_List_H
#define __Il_List_H

#if !defined(__Il_Alloc_H)
#  include <ilog/alloc.h>
#endif
#define IlListNoE

// --------------------------------------------------------------------------
// IlListIterator: The base list iterator type
// --------------------------------------------------------------------------
class ILOG_EXPORTED Il_List;
class ILOG_EXPORTED Il_LIterator
{
public:
    Il_LIterator(const Il_List&);
    // ____________________________________________________________
    inline IlBoolean	isListAlive() const     { return (_l != 0); }
    inline IlBoolean	hasMoreElements() const { return (_c != 0); }
    Il_LIterator&	operator++();
    inline Il_LIterator& operator++(int)     { return ++(*this); }
    void		d();
    void		e();
    void		r(IlAny);
protected:
    IlAny		nextElement();
    const Il_List*	_l;
private:
    IlAny		_c;
};

// --------------------------------------------------------------------------
// IlSafeListIterator: A safe list iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED Il_SLIterator : public Il_LIterator
{
public:
    Il_SLIterator(const Il_List& list);
    ~Il_SLIterator();
    Il_SLIterator*	_n;
};

// --------------------------------------------------------------------------
// Il_List: The base list type
// --------------------------------------------------------------------------
typedef void (*IlMapListFunction)(IlAny, IlAny);
typedef IlAny (*IlMapUntilListFunction)(IlAny v, IlAny a, IlAny nf);

// --------------------------------------------------------------------------
class ILOG_EXPORTED Il_List
{
public:
    Il_List() : _first(0), _last(0), _i(0), _length(0) {}
    ~Il_List();
    IL_MLK_DECL();
    // ____________________________________________________________
    class ILOG_EXPORTED Cell {
	friend class Il_List;
    public:
	Cell(IlAny value = 0, Cell* next = 0) : _value(value), _next(next) {}
	~Cell();
	IL_MLK_DECL();
	// ________________________________________________________
	inline	IlAny	getValue()   const    { return _value; }
	inline	void	setValue(IlAny value) { _value = value; }
	inline	Cell*	getNext()     const   { return _next; }
	inline	void	setNext(Cell* next)   { _next = next; }
	inline	IlUInt	length() const        { return getLength(); }
	inline	void	map(IlMapListFunction f, IlAny a = 0) { apply(f, a); }
	IlUInt		getLength() const;
	Cell*		getLast() const;
	Cell*		copy() const;
	Cell*		remove(IlAny v);
	void		setValue(IlUInt pos, IlAny v);
	IlAny		operator[](IlUInt pos) const;
	const Cell*	find(IlAny v) const;
	IlAny		mapUntil(IlMapUntilListFunction,
				 IlAny = 0,
				 IlAny = 0) const;
	void		apply(IlMapListFunction, IlAny a = 0);
    private:
	IlAny		_value;
	Cell*		_next;
    };
    inline Cell*	getFirst()  const { return _first; }
    inline Cell*	getLast()   const { return _last; }
    inline void		map(IlMapListFunction f, IlAny a = 0) { apply(f, a); }
    inline void		apply(IlMapListFunction f, IlAny a = 0)
			{
			    if (_first)
				_first->apply(f, a);
			}
    inline IlUInt	getLength() const { return _length; }
    inline IlUInt	length()  const { return getLength(); }
    inline void		setValue(IlUInt pos, IlAny v)
			{
			    if (_first)
				_first->setValue(pos,v);
			}
    inline void		empty()
			{
			    e();
			    delete _first;
			    _first = _last = 0;
			    _length = 0;
			}
    void		insert(Cell*, IlInt position = 0);
    void		append(Cell*);
    Cell*		removeCell(IlAny value);
    IlAny		mapUntil(IlMapUntilListFunction,
				 IlAny = 0,
				 IlAny = 0) const;
    void		swap(IlAny value1, IlAny value2);
    void		push(IlAny value);
    void		pop(IlAny value);
    void		ai(Il_SLIterator*);
    void		ri(Il_SLIterator*);

protected:
    void		i(IlAny value, IlInt position = 0);	// insert
    void		a(IlAny value);				// append
    IlBoolean		r(IlAny value);				// remove
    inline IlBoolean	f(IlAny v) const			// find
			{
			    return (IlBoolean)(_first && _first->find(v));
			}
    inline IlAny	get(IlUInt pos) const			// getValue
			{
			    return (_first) ? (*_first)[pos] : (IlAny)0;
			}
    Il_List*		cp() const;				// copy

private:
    void		d();
    void		e();
    void		n(Cell*);
    Cell*		_first;
    Cell*		_last;
    Il_SLIterator*	_i;
    IlUInt		_length;
};

#define IL_DEF_LIST(NAME, TYPE)						\
NAME: public Il_List { public: NAME() : Il_List() {}			\
inline void insert(TYPE v, IlInt pos = 0) { i(IL_CAST(IlAny,v), pos); } \
inline void append(TYPE v) { a(IL_CAST(IlAny,v)); }			\
inline IlBoolean remove(TYPE v) { return r(IL_CAST(IlAny,v)); }		\
inline TYPE getValue(IlUInt pos) const					\
	{ return IL_REINTERPRETCAST(TYPE, get(pos));  }			\
inline TYPE operator[](IlUInt pos)  const { return getValue(pos); }	\
inline IlBoolean find(TYPE v) const { return f(IL_CAST(IlAny,v)); }	\
inline NAME* copy() const { return IL_REINTERPRETCAST(NAME*, cp()); }	\
}
#define IL_DEF_LISTI(NAME, LNAME, TYPE)					\
NAME: public Il_LIterator { public: NAME(const LNAME& l)		\
    : Il_LIterator(l) {}						\
inline TYPE getNextElement()						\
	{ return IL_REINTERPRETCAST(TYPE, nextElement()); } }
#define IL_DEF_SLISTI(NAME, LNAME, TYPE)				\
NAME: public Il_SLIterator { public: NAME(const LNAME& l)		\
    : Il_SLIterator(l) {}						\
inline TYPE getNextElement()						\
	{ return IL_REINTERPRETCAST(TYPE, nextElement()); } }

#define IlListOf(NAME) Il##NAME##List
#define IlListIteratorOf(NAME) Il##NAME##LIter
#define IlSafeListIteratorOf(NAME) Il##NAME##SLIter
#define IlDefineExpListOf(NAME, TYPE, EXP)				\
class EXP IL_DEF_LIST(IlListOf(NAME), TYPE);				\
class EXP IL_DEF_LISTI(IlListIteratorOf(NAME), IlListOf(NAME), TYPE);	\
class EXP IL_DEF_SLISTI(IlSafeListIteratorOf(NAME), IlListOf(NAME),	\
			TYPE)
#define IlDefineListOf(NAME, TYPE) IlDefineExpListOf(NAME, TYPE, IlListNoE)


class ILOG_EXPORTED IL_DEF_LIST(IlList, IlAny);
class ILOG_EXPORTED IL_DEF_LISTI(IlListIterator, IlList, IlAny);
class ILOG_EXPORTED IL_DEF_SLISTI(IlSafeListIterator, IlList, IlAny);

#define IlMapListCell(list, type, arg, exp) {	\
    const Il_List::Cell* _l = (list);		\
    while (_l) {				\
	arg = (type)(_l->getValue());		\
	_l  = _l->getNext();			\
	exp; } }

#define IlMapList(list, type, arg, exp) {		\
    const Il_List::Cell* _l = (list)->getFirst();	\
    while (_l) {					\
	arg = (type)(_l->getValue());			\
	_l  = _l->getNext();				\
	exp; } }

// --------------------------------------------------------------------------
// IlListIterator: The base list iterator type
// --------------------------------------------------------------------------
class ILOG_EXPORTED Il_AList;
class ILOG_EXPORTED Il_ALIterator
{
public:
    Il_ALIterator(const Il_AList&);
    // ____________________________________________________________
    inline IlBoolean		isListAlive() const	{ return (_l != 0); }
    inline IlBoolean		hasMoreElements() const { return (_c != 0); }
    inline Il_ALIterator&	operator++(int)		{ return ++(*this); }
    Il_ALIterator&		operator++();
    void			d();
    void			e();
    void			r(IlAny);

protected:
    IlAny			nextKey();
    IlAny			nextElement();
    IlAny			nextPair(IlAny&);
    const Il_AList*		_l;
private:
    IlAny			_c;
};

// --------------------------------------------------------------------------
// IlSafeAListIterator: A safe associative list iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED Il_SALIterator : public Il_ALIterator
{
public:
    Il_SALIterator(const Il_AList& alist);
    ~Il_SALIterator();
    Il_SALIterator*	_n;
};

// --------------------------------------------------------------------------
// Il:AList : 
// --------------------------------------------------------------------------
typedef void (*IlMapAListFunction)(IlAny key, IlAny value, IlAny);
typedef IlAny (*IlMapUntilAListFunction)(IlAny k, IlAny v, IlAny, IlAny);
class ILOG_EXPORTED Il_AList
{
public:
    class ILOG_EXPORTED Cell {
    public:
	Cell(IlAny key, IlAny value, Cell* next = 0)
	: _key(key), _value(value), _next(next) {}
	~Cell();
	IL_MLK_DECL();
	// ____________________________________________________________
	inline IlAny	getKey()     const { return _key; }
	inline void	setKey(IlAny key) { _key = key; }
	inline IlAny	getValue()       const { return _value;  }
	inline void	setValue(IlAny value) { _value = value; }
	inline Cell*	getNext()     const { return _next; }
	inline void	setNext(Cell* next) { _next = next; }
	const Cell*	find(IlAny key, IlAny* value = 0) const;
	IlAny		mapUntil(IlMapUntilAListFunction,
				 IlAny = 0,
				 IlAny = 0) const;
    private:
	IlAny		_key;
	IlAny		_value;
	Cell*		_next;
    };
    Il_AList() : _first((Cell*)0), _i(0), _length(0) {}
    ~Il_AList();
    IL_MLK_DECL();
    // ____________________________________________________________
    inline Cell*	getFirst() const { return _first; }
    inline IlUInt	length() const { return getLength(); } // 3.x compat.
    inline IlUInt	getLength() const { return _length; }
    inline void		empty()
			{
			    e();
			    delete _first;
			    _first = 0;
			    _length = 0;
			}
    IlAny		mapUntil(IlMapUntilAListFunction,
				 IlAny = 0,
				 IlAny = 0) const;
    void		apply(IlMapAListFunction, IlAny = 0);
    void		ai(Il_SALIterator*);
    void		ri(Il_SALIterator*);
protected:
    void		i(IlAny,		// insert
			  IlAny,
			  IlInt = 0);
    void		a(IlAny, IlAny);	// append
    IlBoolean		r(IlAny, IlAny);	// replace
    IlBoolean		rm(IlAny);		// First match
    IlBoolean		rm(IlAny, IlAny);	// Exact match
    Cell*		gfc(IlAny, Cell** = 0) const;	// First match
    Cell*		gc(IlAny,			// Exact match
			   IlAny,
			   Cell** = 0) const;
    IlAny		g(IlAny) const;			// get
    IlBoolean		f(IlAny, IlAny* = 0) const;	// find
private:
    void		d();
    void		e();
    void		n(Cell*);
    Cell*		_first;
    Il_SALIterator*	_i;
    IlUInt		_length;
};

// TODO: REMOVE getItem
#define IL_DEF_ALIST(NAME, KEYTYPE, VALTYPE)				\
NAME: public Il_AList { public:						\
    NAME() : Il_AList() {}						\
inline void insert(KEYTYPE k, VALTYPE v, IlInt p = 0)			\
	{ i((IlAny)k, (IlAny)v, p); }					\
inline void append(KEYTYPE k, VALTYPE v) { a(k, v); }			\
inline IlBoolean replace(KEYTYPE k, VALTYPE v) { return r(k, v); }	\
inline IlBoolean remove(KEYTYPE k) { return rm(k); }			\
inline IlBoolean remove(KEYTYPE k, VALTYPE v) { return rm(k, v); }	\
inline Cell* getFirstCell(KEYTYPE k, Cell** c=0) const {return gfc(k, c);}\
inline Cell* getCell(KEYTYPE k, IlAny v, Cell** c = 0) const		\
	{ return gc(k, v, c); }						\
inline VALTYPE get(KEYTYPE k) const					\
	{ return IL_REINTERPRETCAST(VALTYPE, g(k)); }			\
inline IlBoolean find(KEYTYPE k, VALTYPE* v = 0) const			\
	{ return f(k, (IlAny*)v); }					\
inline Cell* getItem(KEYTYPE k, Cell** c=0) const {return gfc(k, c);}	\
}
#define IL_DEF_ALISTI(NAME, LNAME, KEYTYPE, VALTYPE)			\
NAME : public Il_ALIterator { public:					\
    NAME(const LNAME& l) : Il_ALIterator(l) {}				\
inline KEYTYPE getNextKey()						\
	{ return IL_REINTERPRETCAST(KEYTYPE, nextKey()); }\
inline VALTYPE getNextElement()						\
	{ return IL_REINTERPRETCAST(VALTYPE, nextElement()); }		\
inline KEYTYPE getNextPair(VALTYPE& v)					\
	{ return IL_REINTERPRETCAST(KEYTYPE, nextPair((IlAny&)v)); } }
#define IL_DEF_SALISTI(NAME, LNAME, KEYTYPE, VALTYPE)			\
NAME : public Il_SALIterator { public:					\
    NAME(const LNAME& l) : Il_SALIterator(l) {}				\
inline KEYTYPE getNextKey()						\
	{ return IL_REINTERPRETCAST(KEYTYPE, nextKey()); }		\
inline VALTYPE getNextElement()						\
	{ return IL_REINTERPRETCAST(VALTYPE, nextElement()); }		\
inline KEYTYPE getNextPair(VALTYPE& v)					\
	{ return IL_REINTERPRETCAST(KEYTYPE, nextPair((IlAny&)v)); } }

#define IlAListOf(NAME) Il##NAME##AList
#define IlAListIteratorOf(NAME) Il##NAME##ALIter
#define IlSafeAListIteratorOf(NAME) Il##NAME##SALIter
#define IlDefineExpAListOf(NAME, KEYTYPE, VALTYPE, EXP)			\
class EXP IL_DEF_ALIST(IlAListOf(NAME), KEYTYPE, VALTYPE);		\
class EXP IL_DEF_ALISTI(IlAListIteratorOf(NAME), IlAListOf(NAME),	\
			 KEYTYPE, VALTYPE);				\
class EXP IL_DEF_SALISTI(IlSafeAListIteratorOf(NAME), IlAListOf(NAME),	\
			 KEYTYPE, VALTYPE)
#define IlDefineAListOf(NAME, KEYTYPE, VALTYPE) \
IlDefineExpAListOf(NAME, KEYTYPE, VALTYPE, IlListNoE)

class ILOG_EXPORTED IL_DEF_ALIST(IlAList, IlAny, IlAny);
class ILOG_EXPORTED IL_DEF_ALISTI(IlAListIterator,
				  IlAList, IlAny, IlAny);
class ILOG_EXPORTED IL_DEF_SALISTI(IlSafeAListIterator,
				   IlAList, IlAny, IlAny);

#define IlMapAList(list, typeKey, argKey, typeValue, argValue, exp) {	\
    const IlAList::Cell* _p = (list)->getFirst();			\
    while (_p) {							\
	argKey	 = (typeKey)(_p->getKey());				\
	argValue = IL_REINTERPRETCAST(typeValue, _p->getValue());	\
	_p	 = _p->getNext(); exp } }
#define IlMapAListKey(list, typeKey, argKey, exp) {	\
    const IlAList::Cell* _p = (list)->getFirst();	\
    while (_p) {					\
	argKey = IL_CAST(typeKey, _p->getKey());	\
	_p     = _p->getNext(); exp } }
#define IlMapAListValue(list, typeValue, argValue, exp) {		\
    const IlAList::Cell* _p = (list)->getFirst();			\
    while (_p) {							\
	argValue = IL_REINTERPRETCAST(typeValue, _p->getValue());	\
	_p	 = _p->getNext(); exp    } }

#endif /* !__Il_List_H */
