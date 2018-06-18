// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/accel.h
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
// Declaration of the IlvAccelerator class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Accel_H
#define __Ilv_Util_Accel_H

#if !defined(__Ilv_Base_Event_H)
#include <ilviews/base/event.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAccelerator
{
public:
    virtual ~IlvAccelerator() {}
    // ____________________________________________________________
    inline IlvEventType	type() const { return _type; }
    inline IlUShort	data() const { return _data; }
    inline IlUShort	modifiers() const { return _modifiers; }
    inline IlAny	userArg() const { return _userArg; }
    inline IlUShort	modMask() const { return _modMask; }
    inline void		setModMask(IlUShort modifiersToIgnore)
			{
			    _modMask =
				IlUShort(modifiersToIgnore & ~_modifiers);
			}
    inline IlBoolean	match(IlvEventType type,
			      IlUShort    data,
			      IlUShort    modifiers) const
			{
			    return (IlBoolean)
				((type == _type) &&
				 (data == _data) &&
				 ((_modifiers == IlvForgetModifier) ||
				  (modifiers == _modifiers)));
			}
    inline IlBoolean	trigger(IlvEventType type,
				IlUShort    data,
				IlUShort    modifiers) const
			{
			    return (IlBoolean)
				((type == _type) &&
				 (data == _data) &&
				 ((_modifiers == IlvForgetModifier) ||
				  ((modifiers & ~_modMask) == _modifiers)));
			}

protected:
    IlvAccelerator(IlvEventType	type,
		   IlUShort     data,
		   IlUShort     modifiers,
		   IlAny        userArg,
		   IlUShort	modifiersToIgnore)
    : _type(type),
      _data(data),
      _modifiers(modifiers),
      _userArg(userArg),
      _modMask(IlUShort(modifiersToIgnore & ~modifiers))
    {}

    IlvEventType	_type;
    IlUShort		_data;
    IlUShort		_modifiers;
    IlAny		_userArg;
    IlUShort		_modMask;
};


#endif /* !__Ilv_Util_Accel_H */
