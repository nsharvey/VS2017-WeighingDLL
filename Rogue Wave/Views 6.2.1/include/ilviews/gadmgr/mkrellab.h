// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/mkrellab.h
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
// Declaration of the IlvMakeReliefLabelInteractor and
// IlvMakeShadowLabelInteractor classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Mkrellab_H
#define __Ilv_Gadmgr_Mkrellab_H

#if !defined(__Ilv_Gadmgr_Strinter_H)
#include <ilviews/gadmgr/strinter.h>
#endif
#if !defined(__Ilv_Graphics_Relflab_H)
#include <ilviews/graphics/relflab.h>
#endif
#if !defined(__Ilv_Graphics_Shadlab_H)
#include <ilviews/graphics/shadlab.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvMakeReliefLabelInteractor
    : public IlvManagerMakeStringInteractor
{
public:
    IlvMakeReliefLabelInteractor(IlvManager* manager,
				 IlvView* view)
	: IlvManagerMakeStringInteractor(manager, view) {}
    // ____________________________________________________________
    IlBoolean       accept(IlvPoint& p);
    void            doIt(const char* );

protected:
    IlvReliefLabel* _label;
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvMakeShadowLabelInteractor
: public IlvManagerMakeStringInteractor
{
public:
    IlvMakeShadowLabelInteractor(IlvManager* manager,
				 IlvView* view)
	: IlvManagerMakeStringInteractor(manager, view) {}
    // ____________________________________________________________
    IlBoolean       accept(IlvPoint& p);
    void            doIt(const char*);

protected:
    IlvShadowLabel* _label;
};

#endif /* !__Ilv_Gadmgr_Mkrellab_H */
