// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/refcount.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliRefCounted class, code in xutil.cpp
// --------------------------------------------------------------------------
#ifndef __Ili_Refcount_H
#define __Ili_Refcount_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifndef __Ilv_Base_Array_H
#  include <ilviews/base/array.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

class ILV_INF_EXPORTED IliRefCounted
{
 public:
    void lock() const;
    void unLock() const;
    IlInt getRefCount() const { return _refCount; }
    IlInt getLockCount() const { return _refCount; }

 protected:

    IliRefCounted();
    virtual ~IliRefCounted() {}

 private:
    IlInt _refCount;
};

// -------------------------------------------------------------

class ILV_INF_EXPORTED IliRefCountedArray
{
 public:
    IliRefCountedArray() {}
    IliRefCountedArray(const IliRefCountedArray&);
    ~IliRefCountedArray();

    IliRefCountedArray& operator =(const IliRefCountedArray&);

    IlInt count() const;
    IliRefCounted* at(IlInt idx) const;
    IlBoolean contains(const IliRefCounted*) const;
    IlInt indexOf(const IliRefCounted*) const;

    IlInt append(IliRefCounted*);
    IlBoolean insert(IlInt i, IliRefCounted*);

    IlBoolean removeAt(IlInt);
    IlBoolean removeItem(IliRefCounted*);

    void empty();

    IlBoolean push(IliRefCounted*);
    IliRefCounted* pop();
    IliRefCounted* top() const;

 private:
    IlvArray _array;
};

#endif
