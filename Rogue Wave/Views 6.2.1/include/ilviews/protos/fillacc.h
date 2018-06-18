// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/fillacc.h
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
// Declaration of the "Fill" accessor
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Fillacc_H
#define __Ilv_Protos_Fillacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif

// ---------------------------------------------------------------------------
// IlvFillAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvFillAccessor : public IlvUserAccessor
{
public:
    IlvFillAccessor(const char* name,
		    const IlvValueTypeClass* type,
		    const char* nodeName,
		    const char* fillerName,
		    const char* angle);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvFillAccessor);

protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlSymbol*		_nodeName;
    IlSymbol*		_fillerName;
    IlSymbol*		_angle;
    IlDouble		_value;
};

IlvDECLAREINITPROCLASS(fillacc)

#endif /* __Ilv_Protos_Fillacc_H */
