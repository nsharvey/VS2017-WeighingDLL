// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/message.h
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
// Declaration of the IlvStSubscription and IlvStMessage classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Message_H
#define __IlvSt_Message_H

#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

class IlvStMessage;

class ILVSTUDIOCLASS IlvStSubscription
{
public:
  IlvStSubscription(IlAny receiver);

    // ____________________________________________________________
  virtual ~IlvStSubscription();

  virtual void doIt(IlvStudio* editor,const IlvStMessage* msg,IlAny arg) = 0;

  IlAny getReceiver() const;

private:
  IlAny _receiver;
}; // IlvStSubscription

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStMessageCallback: public IlvStSubscription
{
public:
    IlvStMessageCallback(IlAny receiver, IlvStMessageCallbackType callback)
    : IlvStSubscription(receiver),
      _callback(callback) {}
    // ____________________________________________________________
    void doIt(IlvStudio*, const IlvStMessage*, IlAny arg);
private:
    IlvStMessageCallbackType _callback;
}; // IlvStMessageCallback

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStMessage:
public IlvStNamedObject
{
public:
  IlvStMessage(const char* name)
    : IlvStNamedObject(name),
      _subscriptions() {}
  ~IlvStMessage();

  void subscribe(IlvStSubscription* sub);

  void unSubscribe(IlAny, IlBoolean destroy = IlTrue);
  void broadcast(IlvStudio* editor, IlAny sender, IlAny arg) const;
private:
  IlvArray _subscriptions;
}; // class IlvStMessage

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStMessages
{
public:
    IlvStMessages();
    virtual ~IlvStMessages();
    // ____________________________________________________________
    void broadcast(IlvStudio*	editor,
		   const char* 	msgname,
		   IlAny 	caller = 0,
		   IlAny 	arg = 0)
    	{ broadcast(editor, get(msgname), caller, arg); }
    void broadcast(IlvStudio*,
		   const IlvStMessage*,
		   IlAny caller = 0,
		   IlAny arg = 0);
    IlvStMessage*	get(const char* name);
    void		add(IlvStMessage*);
    void 		subscribe(const char*, IlvStSubscription*);
    IlBoolean		isQueuing() const { return _queuing; }
    void		setQueuing(IlBoolean val) { _queuing = val; }
    void		flush(IlvStudio*);
protected:
    IlvStHash 	_table;
    IlvArray	_msgQueue;
    IlBoolean	_queuing    ILVSTBF;
};

// --------------------------------------------------------------------------
#endif /* ! __IlvSt_Message_H */
