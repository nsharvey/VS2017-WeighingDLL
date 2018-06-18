// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/stack.h
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
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Stack_H
#define __Ilv31_Variable_Stack_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Compilrs_H)
#include <ilviews/variable/compilrs.h>
#endif
#include <ilviews/variable/assert.h>
#include <ilviews/variable/boolean.h>

#define ILVV_TMPL_STACK_DEF(IlvvLink,IlvvStack,ValueType)\
class ILV31VAREXPORTED IlvvLink \
{ \
  private: \
    ValueType _value; \
    IlvvLink* _next; \
    IlvvLink(const IlvvLink&); \
  public : \
    IlvvLink(ValueType value, IlvvLink* next=0); \
    ~IlvvLink(); \
    ValueType car(); \
    IlvvLink* cdr(); \
    int getLength() const; \
}; \
class ILV31VAREXPORTED IlvvStack \
{ \
 private: \
    IlvvLink* _link; \
    IlvvStack(const IlvvStack&); \
    IlvvStack& operator=(const IlvvStack&); \
 public: \
    ~IlvvStack(); \
    IlvvStack(); \
    IlvvStack(ValueType value); \
    ValueType top() const; \
    ValueType pop(); \
    IlvvStack& clear(); \
    IlvvStack& push(ValueType value); \
    IlvvBoolean empty() const; \
    IlvvStack& operator<<(ValueType value); \
    IlvvStack& operator>>(ValueType& value); \
    IlvvStack& operator<<(IlvvStack&); \
    int getSize() const {return _link?_link->getLength():0;} \
};

// the copy constructors for IlvvLink and IlvvStack are defined for g++
#define ILVV_TMPL_STACK_BODY(IlvvLink,IlvvStack,ValueType)\
IlvvLink::IlvvLink(ValueType value, IlvvLink* next): _value(value), _next(next){} \
IlvvLink::IlvvLink(const IlvvLink&){} \
IlvvLink::~IlvvLink(){} \
ValueType IlvvLink::car(){return _value;} \
IlvvLink* IlvvLink::cdr(){return _next;} \
int IlvvLink::getLength() const { \
  int len=1; \
  IlvvLink *l=_next; \
  while(l){len++;l=l->cdr();} \
  return len; \
} \
IlvvStack::IlvvStack(): _link(0){} \
IlvvStack::IlvvStack(const IlvvStack&){} \
IlvvStack::IlvvStack(ValueType v): _link(0){operator<<(v);} \
IlvvStack::~IlvvStack(){ \
IlvvLink* p = _link; \
  IlvvLink* next ; \
  while(p){ \
    next = p->cdr(); \
    delete p; \
    p = next; \
  } \
} \
IlvvStack& IlvvStack::push(ValueType value){ \
  _link = new IlvvLink(value, _link); \
  return *this; \
} \
ValueType IlvvStack::top() const{ \
  ILVV_ASSERT(_link); \
  return _link->car(); \
} \
ValueType IlvvStack::pop(){ \
  ILVV_ASSERT(_link); \
  ValueType v = _link->car(); \
  IlvvLink* p = _link->cdr(); \
  delete _link ; \
  _link = p; \
  return v; \
} \
IlvvBoolean IlvvStack::empty() const{return _link?IlvvFalse:IlvvTrue;} \
IlvvStack& IlvvStack::clear(){while(_link) pop();return *this;} \
IlvvStack& IlvvStack::operator<<(ValueType value){push(value);return *this;} \
IlvvStack& IlvvStack::operator>>(ValueType& value){value=pop();return *this;} \
IlvvStack& IlvvStack::operator<<(IlvvStack& s) \
{ \
  ValueType v; \
  while(!s.empty()){s>>v;push(v);} \
  return *this; \
}

#define ILVV_STACK_BODY(Type) \
ILVV_TMPL_STACK_BODY(Type##StackLink,Type##Stack,Type)

#define ILVV_STACK_DEF(Type) \
ILVV_TMPL_STACK_DEF(Type##StackLink,Type##Stack,Type)

#define ILVV_STACK_BODY2(Stack,Type) \
ILVV_TMPL_STACK_BODY(Stack##StackLink,Stack,Type)

#define ILVV_STACK_DEF2(Stack,Type) \
ILVV_TMPL_STACK_DEF(Stack##StackLink,Stack,Type)

ILVV_STACK_DEF2(IlvvCharPStack,char*)

#endif
