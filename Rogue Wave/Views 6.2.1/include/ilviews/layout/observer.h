// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/observer.h
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
// Declaration of the IlvGraphModelObserver class
// Declaration of the IlvGraphLayoutObserver class
// Declaration of the IlvGraphLayoutTransformerObserver class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Observer_H
#define __Ilv_Layout_Observer_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif /* __Ilv_Base_Clssinfo_H */

#if !defined(__Ilv_Layout_Gphadapt_H)
#include <ilviews/layout/gphadapt.h>
#endif /* __Ilv_Layout_Gphadapt_H */

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

#if !defined(__Ilv_Grapher_Observer_H)
#include <ilviews/grapher/observer.h>
#endif /* __Ilv_Grapher_Observer_H */

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGrapherAdapterObserver
: public IlvManagerObserver
{
public:
    IlvGrapherAdapterObserver(IlvGraphModel* layout);
    virtual ~IlvGrapherAdapterObserver();

    virtual void update(IlvObservable* o, IlAny arg);

private:
    IlvGraphModel* _model;
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphLayoutObserver
: public IlvManagerObserver
{
public:
    IlvGraphLayoutObserver(IlvGraphLayout* layout);
    virtual ~IlvGraphLayoutObserver();

    virtual void update(IlvObservable* o, IlAny arg);

private:
    IlvGraphLayout* _layout;
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphLayoutTransformerObserver
: public IlvManagerObserver
{
public:
    IlvGraphLayoutTransformerObserver(IlvGrapherAdapter*,
                                      IlvView* views,
                                      IlUInt interestMask = IlvMgrMsgSetTransformer);
    virtual ~IlvGraphLayoutTransformerObserver();

    virtual void update(IlvObservable* o, IlAny arg);

private:
    IlvGrapherAdapter* _adapter;
};

ILVGRLMODULEINIT(l_observer)
#endif /* !__Ilv_Layout_Observer_H */
