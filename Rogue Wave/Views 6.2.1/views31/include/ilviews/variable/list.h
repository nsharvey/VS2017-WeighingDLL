// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/list.h
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
//
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_List_H
#define __Ilv31_Variable_List_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Assert_H)
#include <ilviews/variable/assert.h>
#endif
#if !defined(__Ilv31_Variable_Boolean_H)
#include <ilviews/variable/boolean.h>
#endif
#if !defined(__Ilv31_Variable_Mlk_H)
#include <ilviews/variable/mlk.h>
#endif

// --------------------------------------------------------------------------
//     IlvvLink
// --------------------------------------------------------------------------
#define ILVV_TMPL_LINK_DEF(IlvvLink,ValueType,TagType) \
class ILV31VAREXPORTED IlvvLink  \
{ \
private: \
    ValueType _value; \
    IlvvLink* _next; \
    IlvvLink(const IlvvLink&); \
public: \
    IlvvLink(ValueType value, IlvvLink* next = 0); \
    ~IlvvLink(); \
    ValueType car(); \
    IlvvLink*  cdr(); \
    IlvvLink*  append(IlvvLink* l); \
    IlvvLink*  newr(ValueType v); \
    IlvvLink*  cons(ValueType v); \
    int       length() const; \
    IlvvLink*  remove(ValueType v); \
    IlvvLink*  suppress(TagType tag); \
    IlvvLink*  linkFrom(ValueType v); \
    ValueType find(TagType tag); \
    ILVV_MLK_GDECL(); \
};

//  to define for the body
// #define ILVV_MATCH(v1,v2) v1 == v2
// #define ILVV_GET_TAG(Value) Value.GetTag()
// the copy constructor for IlvvLink is defined for g++
#define ILVV_TMPL_LINK_BODY(IlvvLink,ValueType,TagType,NullValue) \
ILVV_MLK_GDEF(IlvvLink) \
IlvvLink::IlvvLink(ValueType value, IlvvLink* next) \
: _value(value), _next(next){} \
IlvvLink::IlvvLink(const IlvvLink&){} \
IlvvLink::~IlvvLink() { delete _next; } \
ValueType    \
IlvvLink::car(){return _value;} \
IlvvLink*  \
IlvvLink::cdr(){return _next;} \
IlvvLink*  \
IlvvLink::append(IlvvLink* l) \
{ \
  IlvvLink* link = this; \
  IlvvLink* previous = new IlvvLink(link->_value); \
  IlvvLink* new_link = previous; \
  link = link->_next; \
  while (link) { \
    previous->_next = new IlvvLink(link->_value); \
    previous = previous->_next; \
    link = link->_next; \
  } \
  previous->_next = l; \
  return new_link;     \
} \
IlvvLink* \
IlvvLink::newr(ValueType v) \
{ \
    IlvvLink* p = this; \
    while ( p->_next) { \
      p = p->_next; \
    } \
    p->_next = new IlvvLink(v); \
    return this; \
} \
IlvvLink* \
IlvvLink::cons(ValueType v) \
{ \
    IlvvLink* l = new IlvvLink(v); \
    l->_next = this; \
    return l; \
} \
int \
IlvvLink::length() const \
{ \
  const IlvvLink* p = this; \
  int i = 0; \
  while (p) { \
      p = p->_next; \
      i++; \
    } \
  return i; \
} \
IlvvLink*  \
IlvvLink::remove(ValueType v) \
{ \
  return suppress(ILVV_GET_TAG(v)); \
} \
IlvvLink*  \
IlvvLink::suppress(TagType tag) \
{ \
  IlvvLink* p; \
  if (ILVV_MATCH(ILVV_GET_TAG(_value), tag)) { \
    p = _next; \
    _next = (IlvvLink*)0; \
    delete this; \
    return p; \
  } \
  p = _next;  \
  IlvvLink* previous = this; \
  while (p){ \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value), tag)) break; \
    previous = p; \
    p = p->_next; \
  } \
  ILVV_ASSERT(p); \
  previous->_next = p->_next; \
  p->_next = (IlvvLink*)0; \
  delete p; \
  return this; \
} \
IlvvLink*  \
IlvvLink::linkFrom(ValueType v)  \
{ \
  IlvvLink* p = this; \
  while (p) { \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value),ILVV_GET_TAG(v))) break; \
    p = p->_next; \
  } \
  return p; \
} \
ValueType  \
IlvvLink::find(TagType tag) \
{ \
  IlvvLink* p = this; \
  while(p){ \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value),tag)) break; \
    p = p->_next; \
  } \
  if (p) return p->_value; \
  return NullValue; \
}

#define ILVV_TMPL_LIST_DEF(IlvvLink,IlvvList,ValueType,TagType)\
class IlvvList;\
class ILV31VAREXPORTED IlvvLink \
{ \
    friend class IlvvList;\
  public: \
    IlvvLink(ValueType value,  IlvvLink* next = 0); \
    ~IlvvLink(); \
    ValueType value() const; \
    IlvvLink* next() const; \
    IlvvLink* copy() const;\
    void recursiveDelete(); \
    ILVV_MLK_GDECL(); \
  private:\
    ValueType _value; \
    IlvvLink* _next; \
    IlvvLink(const IlvvLink&); \
}; \
class ILV31VAREXPORTED IlvvList \
{ \
  private: \
    IlvvLink* _link; \
    IlvvList(const IlvvList&); \
    IlvvList& operator = (const IlvvList&); \
    IlvvList& suppress(TagType tag, IlvvBoolean check); \
    virtual void extraSuppress(ValueType v); \
  public: \
    virtual ~IlvvList(); \
    IlvvList(); \
    IlvvList& suppress(TagType tag); \
    IlvvList& suppressF(TagType tag); \
    IlvvList& remove(ValueType); \
    IlvvList& removeF(ValueType); \
    IlvvLink* detachLink(); \
    IlvvList* attachLink(IlvvLink*); \
    int length() const; \
    ValueType find(TagType tag) const; \
    ValueType pop(); \
    IlvvList& cons(ValueType value); \
    IlvvBoolean empty() const; \
    IlvvLink* link() const; \
    IlvvLink* linkFrom(TagType tag) const;\
    IlvvList& operator<<(ValueType value); \
};

// the copy constructor for IlvvList is defined for g++
#define ILVV_TMPL_LIST_BODY(IlvvLink,IlvvList,ValueType,TagType,NullValue)\
ILVV_MLK_GDEF(IlvvLink) \
IlvvLink::IlvvLink(ValueType value, IlvvLink* next): \
_value(value), _next(next) {} \
IlvvLink::IlvvLink(const IlvvLink&){} \
IlvvLink::~IlvvLink(){} \
IlvvLink* IlvvLink::next() const {return _next;}\
ValueType IlvvLink::value() const {return _value;}\
void IlvvLink::recursiveDelete() { \
    IlvvLink* cur = this; \
    IlvvLink* next; \
    while (cur) { \
	next = cur->_next; \
	cur->_next = 0; \
	delete cur; \
	cur = next; \
    } \
} \
IlvvLink* IlvvList::link() const {return _link;}\
IlvvList& IlvvList::suppress(TagType tag){return suppress(tag,IlvvFalse);} \
IlvvList& IlvvList::suppressF(TagType tag){return suppress(tag,IlvvTrue);} \
IlvvLink* IlvvLink::copy() const {\
  if (_next) return new IlvvLink(_value, _next->copy()); \
  return new IlvvLink(_value); \
} \
IlvvList::IlvvList(): _link(0) {} \
IlvvList::IlvvList(const IlvvList&){} \
IlvvList::~IlvvList()  \
{ \
  if (_link) _link->recursiveDelete(); \
} \
IlvvList& IlvvList::remove(ValueType v){return suppress(ILVV_GET_TAG(v),IlvvFalse);} \
IlvvList& IlvvList::removeF(ValueType v){return suppress(ILVV_GET_TAG(v),IlvvTrue);} \
IlvvLink* IlvvList::detachLink() \
{ \
  IlvvLink* p = _link; \
  _link = 0; \
  return p; \
} \
IlvvList* IlvvList::attachLink(IlvvLink* l) \
{ \
  ILVV_ASSERT(_link == 0); \
  _link = l; \
  return this; \
} \
int IlvvList::length() const \
{\
  int i = 0; \
  IlvvLink* l = _link; \
  while (l) { i++; l = l->_next; } \
  return i;\
}\
IlvvList& IlvvList::cons(ValueType value) \
{ \
  _link = new IlvvLink(value, _link); \
  return *this; \
} \
ValueType IlvvList::pop() \
{ \
  ILVV_ASSERT(_link); \
  ValueType v = _link->_value; \
  IlvvLink* p = _link->_next; \
  delete _link; \
  _link = p; \
  return v; \
} \
void IlvvList::extraSuppress(ValueType){} \
IlvvList& IlvvList::suppress(TagType tag, IlvvBoolean check) \
{ \
  IlvvLink* p = _link; \
  if (ILVV_MATCH(ILVV_GET_TAG(p->_value), tag)){ \
    _link = p->_next; \
    extraSuppress(p->_value); \
    delete p; \
    return *this; \
  } \
  p = p->_next;  \
  IlvvLink* previous = _link; \
  while (p){ \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value), tag)) break; \
    previous = p; \
    p = p->_next; \
  } \
  if (!p){ \
     if (check) \
	IlvFatalError("vvList::suppress: Could not find element"); \
     return *this; \
  } \
  extraSuppress(p->_value); \
  previous->_next = p->_next; \
  delete p; \
  return *this; \
} \
ValueType  \
IlvvList::find(TagType tag) const \
{ \
  IlvvLink* p = _link; \
  while (p){ \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value),tag)) break; \
    p = p->_next; \
  } \
  if (p) return p->_value; \
  return NullValue; \
} \
IlvvLink*  \
IlvvList::linkFrom(TagType tag) const \
{ \
  IlvvLink* p = _link; \
  while (p){ \
    if (ILVV_MATCH(ILVV_GET_TAG(p->_value),tag)) break; \
    p = p->_next; \
  } \
  return p; \
} \
IlvvBoolean IlvvList::empty() const \
{if (_link) return IlvvFalse;return IlvvTrue;} \
IlvvList& IlvvList::operator<< (ValueType value) \
{ \
   cons(value); \
   return *this; \
}

#define ILVV_LIST_LINK(AType) AType##ListLink

#define ILVV_LIST_BODY(Type,Tag,NullValue) \
ILVV_TMPL_LIST_BODY(ILVV_LIST_LINK(Type),Type##List,Type,Tag,NullValue)

#define ILVV_LIST_DEF(Type,Tag) \
ILVV_TMPL_LIST_DEF(ILVV_LIST_LINK(Type),Type##List,Type,Tag)

#define ILVV_LIST_BODY3(List,Type,Tag,NullValue) \
ILVV_TMPL_LIST_BODY(ILVV_LIST_LINK(List),List,Type,Tag,NullValue)

#define ILVV_LIST_DEF3(List,Type,Tag) \
ILVV_TMPL_LIST_DEF(ILVV_LIST_LINK(List),List,Type,Tag)

#endif
