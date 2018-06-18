// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/list.h
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
// Declaration of state lists
// Defined in library ilvstates
// --------------------------------------------------------------------------
#ifndef __Ilv_States_List_H
#define __Ilv_States_List_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif

// the lists :
// the idea is that since a list has no built in iteration feature
// then there is no more in a list than a pointer to its head.

// so there is no reason to distinguish between links and lists
// the type is thus unified and IlvSuList provides both fields,
// next is real and head is a virtual field in this implementation

// there is no information hiding here because linked lists are a simple
// and obvious matter, and the user should not suspect the existence of
// uncontrollable features

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuList
{
    // IlvSuList is the base class for all possible linkable cell IlvSuLists
    // class IlvSuList implements the typeof a "same type" pointing class
public:
    //everything is public in this very simple class
    // the reason is that the programmer expects to know exactly what
    // this type does
    IlvSuList* _Next;
    //constructors
    IlvSuList(IlvSuList* n = 0) : _Next (n) {}
    ~IlvSuList() {}; // not virtual here for space efficiency
    //accessors
    IlvSuList*  getNext() const { return _Next;}
    IlvSuList*  getHead() const { return _Next;}
    IlBoolean 	isEmpty () const { return _Next == 0;}
    //modifiers
    void 	setNext(IlvSuList *p) { _Next = p;}
    void 	setHead(IlvSuList *p) { _Next = p;}
    //usage
    IlvSuList*& next();
    IlvSuList*& head();
};

// --------------------------------------------------------------------------
// the selffield macro is used by IlvSuList subclasses to implement
// a self casting accessor to the "next" field
// requirements :
// typedef inherited : the superclass which implements next
// typedef self : a pointer to the class type
#define selffield(field) self get##field() const \
{\
    return (self)inherited::get##field();\
}
#endif /* !__Ilv_States_List_H */
