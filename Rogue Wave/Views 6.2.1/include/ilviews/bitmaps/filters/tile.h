// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/tile.h
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
// Declaration of Tiling Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Tile_H
#define __Ilv_Bitmaps_Filters_Tile_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvTileFilter : public IlvBitmapFilter
{
 public:
    IlvTileFilter(IlInt offsetx = 0, IlInt offsety = 0) 
	: IlvBitmapFilter(),
	  _offsetx(offsetx),
	  _offsety(offsety)
    {}
    inline void		setOffsetX(IlInt offset) { _offsetx = offset; }
    inline void		setOffsetY(IlInt offset) { _offsety = offset; }
    inline void		setOffsets(IlInt offsetx, IlInt offsety)
			{
			    _offsetx = offsetx;
			    _offsety = offsety;
			}
    inline IlInt	getOffsetX() const { return _offsetx; }
    inline IlInt	getOffsetY() const { return _offsety; }
    inline void		getOffsets(IlInt& offsetx, IlInt& offsety) const
			{
			    offsetx = _offsetx;
			    offsety = _offsety;
			}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_offsetXValue;
    static IlSymbol*	_offsetYValue;

 protected:
    IlInt		_offsetx;
    IlInt		_offsety;
};

ILVFLTMODULETERM(bitmaps_filters_tile);

#endif /* __Ilv_Bitmaps_Filters_Tile_H */
