// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/factory.h
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
// Declaration of the IlvApplication class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_JvScript_Factory_H
#define __Ilv_JvScript_Factory_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Jvscript_Macros_H)
#include <ilviews/jvscript/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVJSLEXPORTED IlvJSFactory
    : public IlvValueInterface
{
public:
    IlvJSFactory(IlvDisplay* display);
    ~IlvJSFactory();

    virtual void	lock();
    virtual void	unLock();
    // --- Value accessors ---
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static  void	GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    IlvDisplay*		getDisplay()  const { return _display; }
protected:
    IlInt		_refCount;
    IlvDisplay*		_display;
};

#endif /* !__Ilv_JvScript_Factory_H */
