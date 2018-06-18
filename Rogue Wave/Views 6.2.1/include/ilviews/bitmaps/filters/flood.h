// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/flood.h
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
// Declaration of Flood Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Flood_H
#define __Ilv_Bitmaps_Filters_Flood_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvFloodFilter : public IlvBitmapFilter
{
public:
    IlvFloodFilter(IlUInt r = 0, 
		   IlUInt g = 0, 
		   IlUInt b = 0, 
		   IlUInt a = 255) 
	: IlvBitmapFilter()
    {
	_r = r;
	_g = g;
	_b = b;
	_a = a;
    }
    inline void		setColor(IlUInt r, 
				 IlUInt g, 
				 IlUInt b, 
				 IlUInt a = 255)
			{
			    _r = r;
			    _g = g;
			    _b = b;
			    _a = a;
			}
    inline void		setR(IlUInt r) { _r = r; }
    inline void		setG(IlUInt g) { _g = g; }
    inline void		setB(IlUInt b) { _b = b; }
    inline void		setA(IlUInt a) { _a = a; }
    inline IlUInt	getR() const { return _r; }
    inline IlUInt	getG() const { return _g; }
    inline IlUInt	getB() const { return _b; }
    inline IlUInt	getA() const { return _a; }
    inline void		getColor(IlUInt& r, 
				 IlUInt& g, 
				 IlUInt& b, 
				 IlUInt& a) const
			{
			    r = _r;
			    g = _g;
			    b = _b;
			    a = _a;
			}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_RValue;
    static IlSymbol*	_GValue;
    static IlSymbol*	_BValue;
    static IlSymbol*	_AValue;

protected:
    IlUInt		_r;
    IlUInt		_g;
    IlUInt		_b;
    IlUInt		_a;
};

ILVFLTMODULETERM(bitmaps_filters_flood);

#endif /* __Ilv_Bitmaps_Filters_Flood_H */
