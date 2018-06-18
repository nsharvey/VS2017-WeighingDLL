// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/hvalitf.h
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
// Declaration of the IlvJSHValueInterface class
// Defined in library ilvjs
// --------------------------------------------------------------------------
#ifndef __Ilv_JSHValItf_H
#define __Ilv_JSHValItf_H

#include <ilviews/base/value.h>
#include <ilviews/jvscript/macros.h>
#include <iljscript/hvalue.h>

// --------------------------------------------------------------------------
// temparary defintion for dll version compilation
class ILVJSLEXPORTED IljHValuePtr;
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
class ILVJSLEXPORTED IlvJSHValueInterface
    : public IlvValueInterface
{
public:
    IlvJSHValueInterface(const IljHValuePtr hvalue);

    virtual void	lock();
    virtual void	unLock();

    const IljHValuePtr&	getHValue() const { return _hValPtr; }

    // --- Value accessors ---
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static  void	GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    IlvDeclareClassInfo();
    IlBoolean		callFunction(const IlvValue& vargs);

protected:
    IljHValuePtr	_hValPtr;
    IlInt		_refCount;
};

#endif /* !__Ilv_JSHValItf_H */
