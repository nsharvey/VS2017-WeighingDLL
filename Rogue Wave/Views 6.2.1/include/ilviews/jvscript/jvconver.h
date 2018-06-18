// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/jvconver.h
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
// Declaration of the IlvJSCommonDialog class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Jvscript_JvConver_H
#define __Ilv_Jvscript_JvConver_H

#include <ilviews/base/value.h>
#include <ilviews/base/list.h>
#include <iljscript/hvalue.h>
#include <iljscript/vm.h>

#if !defined(__Ilv_Jvscript_Macros_H)
#include <ilviews/jvscript/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVJSLEXPORTED IlvJvConverter
{
public:
    IlvJvConverter(IlBoolean autoRegist = IlFalse);
    virtual ~IlvJvConverter();

    static IljVirtualMachine* GetCurrentVM();
    static IlvList*	GetConverters() {return _converters;}
    static IljStatus	VValueToHValue(const IlvValue& vval,
				       IljHValuePtr& hval);
    static IljStatus	HValueToVValue(const IljHValuePtr& hval,
				       IlvValue& vval);
    static IljStatus	VArgsToHArgs(const IlvValue& value,
				     IljHValuePtr* args,
				     int nargs);
    static IljStatus	HArgsToVArgs(const IljHValuePtr* args,
				     int nargs,
				     IlvValue& value);

    static void		Register(const IlvJvConverter* conv);
    static IlvList*	_converters;

    virtual IljStatus	toIljHValue(const IlvValue& vval,
				    IljHValuePtr& hval) const;
    virtual IljStatus	toIlvValue(const IljHValuePtr& hval,
				   IlvValue& vval) const;

    // errors  handlers
    // static IljStatus BadValueError(const IljHValuePtr& val);
    // static IljStatus UnSupportedViewsValueTypeError(const IlvValue& val);

    static inline IlInt	GetError() { return _errorID; }
    static inline IlInt	GetErrorInfo() { return _errorInfo; }
    static void		SetError(IlInt errorID = 0, IlInt errorInfo = 0);
    static IljStatus	OnRuntimeError(IlInt errorID, IlInt errorInfo = 0);
    static IlInt	_errorID;
    static IlInt	_errorInfo;
};

#endif /* !__Ilv_Jvscript_JvConver_H */
