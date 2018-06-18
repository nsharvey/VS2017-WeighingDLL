// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/jsacc.h
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
// Declaration of the JavaScript accessor
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Jsacc_H
#define __Ilv_Protos_Jsacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

// ---------------------------------------------------------------------------
// IlvJavaScriptAccessor	Call a JavaScript function.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvJavaScriptAccessor : public IlvUserAccessor
{
public:
    IlvJavaScriptAccessor(const char* name,
			  const IlvValueTypeClass* type,
			  IlvDisplay* display,
			  const char* setScriptName,
			  const char* getScriptName);

    virtual void		initialize(const IlvAccessorHolder* object);
    inline const IlSymbol*	getFunction() { return _getScriptName; }
    inline const IlSymbol*	setFunction() { return _setScriptName; }

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvJavaScriptAccessor);

protected:
    IlSymbol*			_setScriptName;
    IlSymbol*			_getScriptName;
    IlvDisplay*			_display;
    const char*			_path;

    virtual IlBoolean		changeValue(IlvAccessorHolder* object,
					    const IlvValue& val);
    virtual IlvValue&		queryValue(const IlvAccessorHolder* object,
					   IlvValue& val) const;
};

// Hook used to control the script debugger in prstudio.
//

typedef int (*_IlvProtoScriptDebugHook)(int code, int v, IlAny arg);

#define JS_HOOK_ARE_SCRIPTS_DISABLED	1
#define JS_HOOK_DISABLE_DEBUG		2
#define JS_HOOK_RESET_DEBUG		3
#define JS_HOOK_SCRIPT_ERROR		4

extern ILVPROEXPORTEDFUNCTION(void)
    _IlvSetProtoScriptDebugHook(_IlvProtoScriptDebugHook, IlAny);

IlvDECLAREINITPROCLASS(jsacc)

#endif /* __Ilv_Protos_Jsacc_H */
