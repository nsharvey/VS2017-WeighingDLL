// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/dbutil.h
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
// Array manager classes
// ----------------------------------------------------------------------------

#ifndef __ILD_DBUTIL_H
#define __ILD_DBUTIL_H

#ifndef __ILD_ILD_H
#include <ildblink/ild.h>
#endif

// ============================================================================
// Portable utility functions
// ============================================================================

// Ignore case compare
ILD_EXPORTEDFUNCTION(int)    IldStrICaseCmp  (const char* s1,
					      const char* s2);
ILD_EXPORTEDFUNCTION(int)    IldStrNICaseCmp (const char* s1,
					      const char* s2,
					      int n);
// String uppercase
ILD_EXPORTEDFUNCTION(int)    IldUpperCaseStr (char* s1,
					      const char* s2);
// String lowercase
ILD_EXPORTEDFUNCTION(int)    IldLowerCaseStr (char* s1,
					      const char* s2);
// Right trim of string
ILD_EXPORTEDFUNCTION(char*)  IldStrRTrim     (char* s,
					      IlUInt max = ILD_FIELD_SIZE);

// ============================================================================
// IldPtrArray class.
// ============================================================================
class ILD_EXPORTED IldPtrArray {
 private:
    IlAny**	_arrayPtr;
    IlAny*	_array;
    IlUInt	_arraySize;
    IlUInt	_cardinal;
    IlBoolean	_owner;

    IldPtrArray  (IldPtrArray&)
	{}
    IldPtrArray& operator=    (IldPtrArray&)
	{ return *this; }

 public:
		IldPtrArray  ();
		IldPtrArray  (IlAny*&,
			      IlUInt = 0,
			      IlBoolean = IlTrue);
    virtual
		~IldPtrArray ();
    inline
    IlBoolean    isOwner      () const;
    inline
    void         setOwner     (IlBoolean);
    inline
    IlAny*       getArray     () const;
    inline
    IlUInt       getArraySize () const;
    inline
    IlUInt       getCardinal  () const;
    inline
    IldPtrArray& setCardinal  (IlUInt);
    inline
    IlAny        operator []  (IlUInt index) const;
    inline
    IlAny        get          (IlUInt i) const;
    IlBoolean    increase     ();
    IlBoolean    add          (IlAny);
    IldPtrArray& reverse      ();
    IlBoolean    remove       (IlUInt);
    IlBoolean    remove       (IlAny);
    IlBoolean    end          ();
};

// ----------------------------------------------------------------------------
// Inlines for class IldPtrArray
// ----------------------------------------------------------------------------
inline IlBoolean
IldPtrArray::isOwner () const
{
    return _owner;
}

inline void
IldPtrArray::setOwner (IlBoolean owns)
{
    _owner = owns;
}

inline IlAny*
IldPtrArray::getArray () const
{
    return _array;
}

inline IlUInt
IldPtrArray::getArraySize () const
{
    return _arraySize;
}

inline IlUInt
IldPtrArray::getCardinal () const
{
    return _cardinal;
}

// Used to create and initialize an IldPtrArray object using
// an already existing array.
inline IldPtrArray&
IldPtrArray::setCardinal (IlUInt cardinal)
{
    _cardinal = (cardinal <= _arraySize ? cardinal : _cardinal);
    return *this;
}

inline IlAny
IldPtrArray::operator[] (IlUInt i) const
{
    return _array[i];
}

inline IlAny
IldPtrArray::get (IlUInt i) const
{
    return _array[i];
}

// ============================================================================
// IldDynArray class.
// ============================================================================
class ILD_EXPORTED IldDynArray {
 private:
    IlAny*	_array;
    IlBoolean*	_used;
    IlUInt	_size;
    IlUInt	_cardinal;

		IldDynArray   (IldDynArray&)
		    {};
    IldDynArray& operator =    (IldDynArray&)
	{ return *this; }
    IlInt        findFree      () const;
    IlBoolean    grow          ();
    IlBoolean    shrink        ();

 public:
		IldDynArray   (IlUInt = 0);
    virtual
		~IldDynArray  ();
    inline
    IlUInt       getSize       () const;
    inline
    IlUInt       getCardinal   () const;
    IlUInt       getNbOfValues () const;
    IlBoolean    add           (IlAny);
    IlInt        set           (IlAny);
    IlAny        get           (IlUInt) const;
    IlInt        get           (IlAny) const;

    IldDynArray& reverse       ();
    IlBoolean    remove        (IlUInt);
    IlBoolean    remove        (IlAny);
};

// ----------------------------------------------------------------------------
// Inlines for class IldDynArray
// ----------------------------------------------------------------------------
inline IlUInt
IldDynArray::getSize () const 
{
    return _size;
}

inline IlUInt
IldDynArray::getCardinal () const
{
    return _cardinal;
}

#endif // __ILD_DBUTIL_H
