// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/offset.h
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
// Declaration of Offset Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Offset_H
#define __Ilv_Bitmaps_Filters_Offset_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvOffsetFilter : public IlvBitmapFilter
{
 public:
    IlvOffsetFilter(IlInt dx = 0, IlInt dy = 0) 
	: IlvBitmapFilter(),
	  _dx(dx),
	  _dy(dy) {
    }
    inline void		setdX(IlInt dx) { _dx = dx; }
    inline void		setdY(IlInt dy) { _dy = dy; }
    inline void		setdXY(IlInt dx, IlInt dy)
			{
			    _dx = dx;
			    _dy = dy;
			}
    inline IlInt	getdX() const { return _dx; }
    inline IlInt	getdY() const { return _dy; }
    inline void		getdXY(IlInt& dx, IlInt& dy) const
			{
			    dx = _dx;
			    dy = _dy;
			}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_dXValue;
    static IlSymbol*	_dYValue;

 protected:
    IlInt		_dx;
    IlInt		_dy;
};

ILVFLTMODULETERM(bitmaps_filters_offset);

#endif /* __Ilv_Bitmaps_Filters_Offset_H */
