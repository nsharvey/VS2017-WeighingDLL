// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/displace.h
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
// Declaration of Displacement Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Displace_H
#define __Ilv_Bitmaps_Filters_Displace_H

#if !defined(__Ilv_Bitmaps_Algo_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif

class ILVFLTEXPORTED IlvDisplaceFilter : public IlvBitmapFilter
{
public:
    IlvDisplaceFilter(IlFloat scale = 0.0,
		      IlvRGBBitmapData::Channel xChannelSelector = IlvRGBBitmapData::Alpha,
		      IlvRGBBitmapData::Channel yChannelSelector = IlvRGBBitmapData::Alpha);
    virtual ~IlvDisplaceFilter();
    void	setScale(IlFloat scale);
    inline IlFloat	getScale() const { return _scale; }
    void	setXChannelSelector(IlvRGBBitmapData::Channel selector);
    void	setYChannelSelector(IlvRGBBitmapData::Channel selector);
    inline
    IlvRGBBitmapData::Channel	getXChannelSelector() const
				{
				    return _xChannelSelector;
				}
    inline
    IlvRGBBitmapData::Channel	getYChannelSelector() const
				{
				    return _yChannelSelector;
				}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*		_scaleValue;
    static IlSymbol*		_xChannelSelectorValue;
    static IlSymbol*		_yChannelSelectorValue;

protected:
    IlFloat _scale;
    IlvRGBBitmapData::Channel	_xChannelSelector;
    IlvRGBBitmapData::Channel	_yChannelSelector;
};

ILVFLTMODULETERM(bitmaps_filters_displace);

#endif /* __Ilv_Bitmaps_Filters_Displace_H */
