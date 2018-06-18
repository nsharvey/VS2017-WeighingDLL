// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/accels.h
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
// Declaration of the IlvATAccelerator class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Accels_H
#define __Ilv_Annotext_Accels_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif
#if !defined(__Ilv_Util_Accel_H)
#  include <ilviews/util/accel.h>
#endif
#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif

class ILVATEXPORTED IlvAnnoText;

typedef void (* IlvATAction)(IlvAnnoText*, IlvEvent&, IlAny);

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATAccelerator : public IlvAccelerator
{
public:
    IlvATAccelerator(IlvATAction  atAction		= 0,
		     IlvEventType type			= (IlvEventType)0,
		     IlUShort     data			= 0,
		     IlUShort     modifiers		= 0,
		     IlAny        userArg		= 0,
		     IlUShort     modifiersToIgnore	= 0)

    : IlvAccelerator(type, data, modifiers, userArg, modifiersToIgnore),
      _action(atAction)
     {}

    virtual void	activate(IlvAnnoText* atext, IlvEvent& event) const;
    inline IlvATAction	action() const { return _action; }
    inline void		setAction(IlvATAction atAction, IlAny userArg)
			{
			    _action = atAction;
			    _userArg = userArg;
			}

protected:
    IlvATAction		_action;
};

#endif /* !__Ilv_Annotext_Accels_H */
