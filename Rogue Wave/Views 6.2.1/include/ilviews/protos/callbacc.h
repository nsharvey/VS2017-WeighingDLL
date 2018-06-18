// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/callbacc.h
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
// Declaration of the accessor for connecting an output value to a callback.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Callbacc_H
#define __Ilv_Protos_Callbacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv_Protos_Grphnode_H)
#include <ilviews/protos/grphnode.h>
#endif

// ---------------------------------------------------------------------------
// IlvCallbackAccessor: output a value when a callback is called
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvCallbackAccessor : public IlvUserAccessor
{
public:
    IlvCallbackAccessor(const char* name,
			const IlvValueTypeClass* type,
			const char* nodename,
			const char* callback,
			const char* queryacc);
    virtual ~IlvCallbackAccessor();

    virtual IlBoolean	isOutputValue(const IlSymbol* name) const;

    static void		CallbackProc(IlvGraphic* obj, IlAny arg);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvCallbackAccessor);

protected:
    virtual void	initialize(const IlvAccessorHolder* object);

    void		initCallback(const IlvAccessorHolder* object,
				     IlBoolean remove = IlFalse);

    IlSymbol*			_nodename;
    IlSymbol*			_callback;
    IlSymbol*			_queryacc;
    const IlvAccessorHolder*	_object;
};

IlvDECLAREINITPROCLASS(callbacc)

#endif /* __Ilv_Protos_Callbacc_H */
