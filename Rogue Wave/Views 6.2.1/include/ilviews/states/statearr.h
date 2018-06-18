// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/statearr.h
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
// Declaration of generic collection classes for states
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Statearr_H
#define __Ilv_States_Statearr_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_States_Gendefs_H)
#  include <ilviews/states/gendefs.h>
#endif
#include <ilviews/macros.h>

// this file defines reallocatable arrays

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuVector {
public:
    //constructors
    IlvSuVector(IlUInt s)
	: _Size(s),
	_Array(s ? new IlAny[s] : 0)
    {}
    IlvSuVector(IlUInt s,
		IlAny*a)
	: _Size(s),
	_Array(a)
    {}
    virtual ~IlvSuVector() { delete[] _Array; }

    //aspects
    ILVSTATES_READONLY(IlUInt, Size);
    ILVSTATES_READONLY(IlAny*, Array);

    //accessors
    IlAny getValAtPos(IlInt) const;
    IlBoolean isInArray(IlInt r) const {
	return (r >= 0) && (r < (IlInt)_Size);
    }
    //modifiers
    void setValAtPos(IlInt,
		     IlAny);
    void cinit(IlUInt = 0,
	       IlInt = 0);
    void reAlloc(IlUInt,
		 IlAny*);
    void reAlloc(IlUInt);
    //policy
    const IlAny& operator[](IlInt i) const { return _Array[i]; }
    IlAny& operator[](IlInt i) { return _Array[i]; }

protected:
    IlUInt _Size;
    IlAny* _Array;
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuStack
: public IlvSuVector
{
 public:
    IlvSuStack(IlInt i = 5,
	       IlInt p = 5)
	: IlvSuVector (i),
	_Top(0),
	_Page(p)
    {}
    virtual ~IlvSuStack() {}
    //accessors
    IlInt getTop() const { return _Top; }
    IlAny getVal() const { return getValAtPos(_Top - 1); }
    IlInt isEmpty() const { return _Top == 0; }
    IlBoolean isInStack(IlInt r) const { return (r >= 0) && (r < getTop()); }
    //modifiers
    void push(IlAny);
    void pop() {
	assert(_Top > 0);
	_Top--;
    }
    //policy
    IlAny popget() {
	IlAny aux = getVal();
	pop();
	return aux;
    }
    IlBoolean findAndPack(IlAny);
    IlBoolean removeLocation(IlInt);
protected:
    IlInt _Top;
    IlInt _Page;
};

#define ILVSTATES_STACKLOOP(name)    { for(IlInt i = 0; i < (name).getTop(); ++i) {
#define ILVSTATES_REVSTACKLOOP(name) { for(IlInt i = (name).getTop()-1; i>=0; --i) {

#define ILVSTATES_ENDLOOP }}

#endif /* !__Ilv_States_Statearr_H */
