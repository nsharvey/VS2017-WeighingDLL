// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/comgint.h
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
// Definitions of an manager object interactor class that communicates with
// the ActiveX control associated to an IlvGraphicCOMAdapter.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Comgint_H
#define __Ilv_Windows_Comgint_H

#if !defined(__Ilv_Windows_Macros_H)
#include <ilviews/windows/macros.h>
#endif /* !__Ilv_Windows_Macros_H */
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif

// -------------------------------------------------------------------------
class ILVCOMEXPORTED IlvGraphicComAdapterInteractor
: public IlvInteractor
{
public:
    IlvGraphicComAdapterInteractor()
    : IlvInteractor()
    {}

    virtual IlBoolean handleEvent(IlvGraphic*		 graphic,
				   IlvEvent&		 event,
				   const IlvTransformer* t = 0);
    virtual IlBoolean  accept(const IlvGraphic*) const;

    DeclareInteractorTypeInfo(IlvGraphicComAdapterInteractor);
};

ILVCOMMODULEINIT(cominter);

#endif /* __Ilv_Windows_Comgint_H */
