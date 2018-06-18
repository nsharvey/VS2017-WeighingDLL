// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/buffer.h
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
#ifndef __Ilv31_Variable_Buffer_H
#define __Ilv31_Variable_Buffer_H

#if !defined(__Ilv31_Variable_Assert_H)
#include <ilviews/variable/assert.h>
#endif

#define ILVV_BUFFER_LIST(buf_type) ILVV__##buf_type##__List

#define ILVV_BUFFER_DECL(buf_type,elt_type) \
class ILV31VAREXPORTED ILVV_BUFFER_LIST(buf_type){ \
 public: \
   ILVV_BUFFER_LIST(buf_type)(elt_type, ILVV_BUFFER_LIST(buf_type)* cdr=0); \
   elt_type car() const {return _car;} \
   ILVV_BUFFER_LIST(buf_type)* cdr() const {return _cdr;} \
   void append(ILVV_BUFFER_LIST(buf_type)* l){ILVV_ASSERT(!_cdr);_cdr=l;} \
   ILVV_BUFFER_LIST(buf_type)* copy(); \
 private: \
   elt_type _car; \
   ILVV_BUFFER_LIST(buf_type) *_cdr; \
}; \
class ILV31VAREXPORTED buf_type{ \
 public: \
   buf_type(); \
   buf_type(const buf_type&); \
   ~buf_type(); \
   elt_type pop(); \
   buf_type& push(elt_type); \
   buf_type& operator<<(elt_type); \
   buf_type& operator>>(elt_type&); \
   int eob() const {return _first?0:1;} \
   operator int(){return eob();} \
 private: \
   void operator=(const buf_type&); \
   ILVV_BUFFER_LIST(buf_type) *_first; \
   ILVV_BUFFER_LIST(buf_type) *_current; \
};

#define ILVV_BUFFER_DEF(buf_type,elt_type) \
ILVV_BUFFER_LIST(buf_type)::ILVV_BUFFER_LIST(buf_type)(elt_type e, ILVV_BUFFER_LIST(buf_type)* cdr): _car(e), _cdr(cdr){} \
ILVV_BUFFER_LIST(buf_type)* ILVV_BUFFER_LIST(buf_type)::copy(){ \
   return new ILVV_BUFFER_LIST(buf_type)(_car,_cdr?_cdr->copy():0); \
} \
buf_type::buf_type(): _first(0), _current(0){} \
buf_type::buf_type(const buf_type& rhs): \
_first(rhs._first?rhs._first->copy():0), \
_current(0) \
{ \
   _current=_first; \
   for(;;){ \
      if (_current->cdr()) _current=_current->cdr(); \
      else break; \
   } \
} \
buf_type::~buf_type(){ \
   ILVV_BUFFER_LIST(buf_type)* cursor=_first; \
   ILVV_BUFFER_LIST(buf_type)* next; \
   while(cursor){ \
      next=cursor->cdr(); \
      delete cursor; \
      cursor=next; \
   } \
} \
elt_type buf_type::pop(){ \
   if (!_first){ \
	IlvFatalError("Buffer::pop: pop in empty buffer"); \
   } \
   elt_type e=_first->car(); \
   ILVV_BUFFER_LIST(buf_type)* cursor=_first; \
   if (_first==_current) _current=0; \
   _first=_first->cdr(); \
   delete cursor; \
   return e; \
} \
buf_type& buf_type::push(elt_type e){ \
   if (!_current){ \
      _current=new ILVV_BUFFER_LIST(buf_type)(e); \
      _first=_current; \
      return *this; \
   } \
   ILVV_BUFFER_LIST(buf_type)* b=new ILVV_BUFFER_LIST(buf_type)(e); \
   _current->append(b); \
   _current=b; \
   return *this; \
} \
buf_type& buf_type::operator<<(elt_type e){return push(e);} \
buf_type& buf_type::operator>>(elt_type& e){e=pop();return *this;}

#endif
