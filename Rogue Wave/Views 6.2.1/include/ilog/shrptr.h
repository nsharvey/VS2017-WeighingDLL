// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/shrptr.h
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
// Declaration of the IlSharedPtr template class
// --------------------------------------------------------------------------
#ifndef __Il_Shrptr_H
#define __Il_Shrptr_H

#if !defined(__Il_Macros_H)
#include <ilog/macros.h>
#endif /* !__Il_Macros_H */

// --------------------------------------------------------------------------
template <class T>
class IlSharedPtr
{
    class Counter
    {
    public:
	Counter() : _count(0) {}
	void	increment() { _count++; }
	IlUInt	decrement() { return --_count; }
	IlUInt	_count;
    };

public:
    IlSharedPtr(T* ptr = 0)
	: _ptr(ptr),
	  _counter(new Counter)
    {
	_counter->increment();
    }
    IlSharedPtr(const IlSharedPtr<T>& other)
	: _ptr(other._ptr),
	  _counter(other._counter)
    {
	_counter->increment();
    }
    ~IlSharedPtr()
    {
	if (_counter->decrement() == 0) {
	    delete _ptr;
	    delete _counter;
	}
    }
    T* get() const { return _ptr; }

    IlSharedPtr<T>& operator =(const IlSharedPtr<T>& other)
    {
        if (this != &other) { // No self assignment
            if (_counter->decrement() == 0) {
		delete _ptr;
		delete _counter;
	    }
            _ptr = other._ptr;
            _counter = other._counter;
            _counter->increment();
        }
        return *this;
    }

private:
    T*		_ptr;
    Counter*	_counter;
};

#endif /* !__Il_IlSharedPtr_H */
