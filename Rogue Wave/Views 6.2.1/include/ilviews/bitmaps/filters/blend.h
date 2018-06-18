// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/blend.h
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
// Declaration of Blend Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Blend_H
#define __Ilv_Bitmaps_Filters_Blend_H

#if !defined(__Ilv_Bitmaps_Algo_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvBlendFilter : public IlvBitmapFilter
{
public:
     enum BlendMode {
	 Normal,
	Multiply,
	Screen,
	Darken,
	Lighten 
    };
    IlvBlendFilter(BlendMode mode = Normal);
    ~IlvBlendFilter();
    void		setMode(BlendMode mode);
    inline BlendMode	getMode() const { return _mode; }
    IlvBitmapData*	apply(IlUInt count = 0, 
			      const IlvBitmapData** datas = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlvSymbol*	_modeValue;

 protected:
    BlendMode		_mode;
};

ILVFLTMODULETERM(bitmaps_filters_blend);

#endif /* __Ilv_Bitmaps_Filters_Blend_H */

