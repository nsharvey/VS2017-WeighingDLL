// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/intrface/geomitf.h
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
// Declaration of the interface classes for IlvPoint and IlvRect
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Itf_Geomitf_H
#define __Ilv_Itf_Geomitf_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPointInterface
    : public IlvPoint,
      public IlvValueInterface
{
public:
    IlvPointInterface(IlvPos x = 0, IlvPos y = 0);
    IlvPointInterface(const IlvPoint& point);

    virtual void	lock();
    virtual void	unLock();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_xValue;
    static IlSymbol*	_yValue;

    DeclareValueAccessors();
    IlvDeclareClassInfo();

protected:
    IlInt		_refCount;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRectInterface
    : public IlvRect,
      public IlvValueInterface
{
public:
    IlvRectInterface(IlvPos x = 0, IlvPos y = 0, IlvDim w = 1, IlvDim h = 1);
    IlvRectInterface(const IlvRect& rect);

    virtual void	lock();
    virtual void	unLock();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_xValue;
    static IlSymbol*	_yValue;
    static IlSymbol*	_wValue;
    static IlSymbol*	_hValue;
    static IlSymbol*	_bottomValue;
    static IlSymbol*	_rightValue;

    DeclareValueAccessors();
    IlvDeclareClassInfo();

protected:
    IlInt		_refCount;
};

ILVDSPMODULEINIT(geomitf);
#endif /* !__Ilv_Itf_Geomitf_H */
