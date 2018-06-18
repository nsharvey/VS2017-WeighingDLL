// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/safeptr.h
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
// Declaration of the IlvSafePointer class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Safeptr_H
#define __Ilv_Base_Safeptr_H

#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif

class ILVDSPEXPORTED IlvSafePointer
{
public:
    IlvSafePointer(IlvValueInterface* viewObj, IlAny userData);
    ~IlvSafePointer();
    // ____________________________________________________________
    // Value accessors:
    IlvValue&  queryValue(IlvValue& value) const;
    IlBoolean changeValue(const IlvValue& value);
    void getAccessors(const IlSymbol* const** accessors,
			      const IlvValueTypeClass* const** types,
			      IlUInt& count) const;

    // Lock & unlock:
    void lock() { ++_refcount; }
    void unLock();

    // Embedded data accessors:
    IlvValueInterface* getValueInterface() const { return _intf; }
    void               setValueInterface(IlvValueInterface* intf = 0);
    IlBoolean          isSafe() const { return (_intf==0)?IlFalse:IlTrue; }
    IlAny              getUserData() const { return _userData; }
    void               setUserData(IlAny userData) { _userData = userData; }

private:
    IlvValueInterface* _intf;
    IlAny             _userData;
    IlUInt            _refcount;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvSafePointerHolder
: public IlvHashTable {
public:
    IlvSafePointerHolder(IlUInt size = 16);
    // ____________________________________________________________
    static IlvSafePointerHolder* GetCurrentHolder();
    static IlBoolean            HasCurrentHolder();
    static void                  DeleteCurrentHolder();
    static IlvSafePointer*       GetSafePointerOf(IlvValueInterface* intf);
    static void                  ResetSafePointerOf(const IlvValueInterface* intf);
    static IlvSafePointerHolder* _currentSafePointerHolder;
    // ____________________________________________________________
protected:
    IlvSafePointer* findOrCreateSafePointerOf(IlvValueInterface* intf);
    IlvSafePointer* findSafePointerOf(const IlvValueInterface* intf) const;

};

#endif /* !__Ilv_Base_Safeptr_H */
