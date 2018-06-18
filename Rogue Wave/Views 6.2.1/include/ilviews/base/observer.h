// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/observer.h
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
// Declaration of the IlvObserver and IlvObservable classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Observer_H
#define __Ilv_Base_Observer_H

#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Base_Smartptr_H)
#include <ilviews/base/smartptr.h>
#endif

class IlvObservable;

class ILVVWSEXPORTED IlvObserver
{
public:
    IlvObserver()
    : _observables()
    {
    }
    virtual ~IlvObserver();
    // ____________________________________________________________

    virtual void	update(IlvObservable* o, IlAny arg);
    virtual void	attach(IlvObservable* o);
    virtual void	detach(IlvObservable* o);
    IlBoolean		observes(IlvObservable* o) const;

protected:
    IlList		_observables;
};

class ILVVWSEXPORTED IlvObservable : public IlvSmartData
{
    friend class IlvObserver;
public:
    IlvObservable()
    : _observers(),
      _locked(0)
    {
    }
    virtual ~IlvObservable();
    // ____________________________________________________________

    virtual void	notify(IlAny arg = 0);

protected:
    IlList		_observers;
    IlUInt		_locked;

private:
    void		add_observer(IlvObserver*);
    void		remove_observer(IlvObserver*);
};

#endif /* !__Ilv_Base_Observer_H */
