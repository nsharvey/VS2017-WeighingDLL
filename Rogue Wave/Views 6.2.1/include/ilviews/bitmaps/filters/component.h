// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/component.h
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
// Declaration of component transfer filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Component_H
#define __Ilv_Bitmaps_Filters_Component_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Transfer_H)
#include <ilviews/bitmaps/filters/transfer.h>
#endif


class ILVFLTEXPORTED IlvComponentTransferFilter : public IlvBitmapFilter
{
public:
    IlvComponentTransferFilter();
    ~IlvComponentTransferFilter();
    void		setRedFunction(IlvTransferFunction* redFunction);  
    void		setGreenFunction(IlvTransferFunction* greenFunction);  
    void		setBlueFunction(IlvTransferFunction* blueFunction);  
    void		setAlphaFunction(IlvTransferFunction* alphaFunction);
    IlvTransferFunction*	getRedFunction() const;
    IlvTransferFunction*	getGreenFunction() const;
    IlvTransferFunction*	getBlueFunction() const;
    IlvTransferFunction*	getAlphaFunction() const;

    IlvBitmapData*		apply(IlUInt count = 0, 
				      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*		_rFunctionValue;
    static IlSymbol*		_gFunctionValue;
    static IlSymbol*		_bFunctionValue;
    static IlSymbol*		_aFunctionValue;

protected:
    IlvTransferFunction*	_redFunction;
    IlvTransferFunction*	_greenFunction;
    IlvTransferFunction*	_blueFunction;
    IlvTransferFunction*	_alphaFunction;
};

ILVFLTMODULETERM(bitmaps_filters_component);

#endif /* __Ilv_Bitmaps_Filters_Component_H */
