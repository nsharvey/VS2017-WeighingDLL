// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/transform.h
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
// Declaration of bitmap data transformation algorithms in IlogViews
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Transform_H
#define __Ilv_Bitmaps_Transform_H

#if !defined(__Ilv_Bitmap_Algo_H)
#include <ilviews/bitmaps/algo.h>
#endif

class IlvRGBBitmapData;

class ILVDSPEXPORTED IlvBitmapDataTransform : public IlvBitmapDataAlgorithm
{
public:
    IlvBitmapDataTransform();

    IlvRGBBitmapData*	integralRotate(IlvRGBBitmapData*, IlUInt numrot);
    IlvRGBBitmapData*	shearX(IlvRGBBitmapData*,
			       IlInt angle,
			       IlBoolean antialias);
    IlvRGBBitmapData*	shearY(IlvRGBBitmapData*,
			       IlInt angle,
			       IlBoolean antialias);
    IlvRGBBitmapData*	rotate(IlvRGBBitmapData*,
			       IlInt angle, 
			       IlBoolean antialias);
    IlvBitmapData*	flipHorizontally(IlvBitmapData*);
    IlvBitmapData*	flipVertically(IlvBitmapData*);
    void		setBackgroundColor(IlUChar a,
					   IlUChar r,
					   IlUChar g,
					   IlUChar b);
    void		setBackgroundIndex(IlUInt idx);

protected:
    IlUChar		_a;
    IlUChar		_r;
    IlUChar		_g;
    IlUChar		_b;
    IlUInt		_idx;
};

#endif /* __Ilv_Bitmaps_Transform_H */
