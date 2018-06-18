// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/im.h
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
// Declaration of useful classes for Input method management.
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Im_H
#define __Ilv_Util_Im_H

#if !defined(_Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

class IlSymbol;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvImValue
{
public:
    IlvImValue() : _name(0), _value(0) {}
    IlvImValue(const char* name, IlAny value);
    // ____________________________________________________________
    inline IlSymbol*	getName()  const { return _name; }
    inline IlAny	getValue() const { return _value; }
    void		set(const char* name, IlAny value);

private:
    IlSymbol*		_name;
    IlAny		_value;
};

ILVDSPEXPORTEDFUNCTION(IlUShort) _IlvGetMaxCharSize();
ILVDSPEXPORTEDFUNCTION(IlBoolean) _IlvNeedToSendIMEvent();

#endif /* !__Ilv_Util_Im_H */
