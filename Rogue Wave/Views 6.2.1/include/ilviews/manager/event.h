// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/event.h
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
// Declaration of the IlvManagerEventHook class
// Declaration of the IlvManagerAccelerator class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Event_H
#define __Ilv_Manager_Event_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Util_Accel_H)
#include <ilviews/util/accel.h>
#endif

class IlvManager;
class IlvEvent;
class IlvView;
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerEventHook
{
public:
    IlvManagerEventHook()
    : _manager(0),
      _next(0)
    {}
    virtual ~IlvManagerEventHook();
    // ____________________________________________________________
    inline IlvManager*	getManager() const { return _manager;    }
    virtual void	setManager(IlvManager* manager);
    virtual IlBoolean	handleEvent(IlvEvent& event, IlvView* view) = 0;

private:
    IlvManager*          _manager;
    IlvManagerEventHook* _next;

    friend class IlvManager;
};

// --------------------------------------------------------------------------
typedef void (* IlvManagerAcceleratorAction)(IlvManager* manager,
					     IlvView*    view,
					     IlvEvent&   event,
					     IlAny       userArg);
class ILVMGREXPORTED IlvManagerAccelerator
: public IlvAccelerator
{
public:
    IlvManagerAccelerator(IlvManagerAcceleratorAction mgrAction,
			  IlvEventType		      eventType,
			  IlUShort		      eventData    = 0,
			  IlUShort		      modifiers    = 0,
			  IlAny			      userArg      = 0,
			  IlUShort		      optModifiers = 0)
    : IlvAccelerator(eventType,
		     eventData,
		     modifiers,
		     userArg,
		     optModifiers),
      _mgraction(mgrAction)
    {}
    // ____________________________________________________________
    inline IlvManagerAcceleratorAction	action() const { return _mgraction; }
    inline void		setAction(IlvManagerAcceleratorAction mgrAction,
				  IlAny			       userArg)
			{
			    _mgraction = mgrAction;
			    _userArg = userArg;
			}
    inline IlBoolean	match(IlvEventType type,
			      IlUShort     data,
			      IlUShort     modifiers) const
			{
			    return (IlBoolean)
				((type	 == _type) &&
				 (data	 == _data) &&
				 ((_modifiers == IlvForgetModifier) ||
				  (modifiers  == _modifiers)));
			}
    inline IlBoolean	match(IlvEvent& event) const
			{ return match(event.type(),
				       event.button(),
				       event.modifiers());
			}
    inline IlBoolean	match(const IlvManagerAccelerator& accel) const
			{
			    return match(accel.type(),
					 accel.data(),
					 accel.modifiers());
			}
    virtual void	activate(IlvManager* manager,
				 IlvView*    view,
				 IlvEvent&   event);

protected:
    IlvManagerAcceleratorAction _mgraction;
};


#endif /* !__Ilv_Manager_Event_H */
