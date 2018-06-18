// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/colmatrix.h
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
// Declaration of color matrix filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Colmatrix_H
#define __Ilv_Bitmaps_Filters_Colmatrix_H

#if !defined(__Ilv_Bitmap_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif

class ILVFLTEXPORTED IlvColorMatrixFilter : public IlvBitmapFilter
{
 public:
    IlvColorMatrixFilter(const IlFloat* values = 0);
    ~IlvColorMatrixFilter();
    void		setValues(const IlFloat* values);
    void		setValues(IlFloat a00,
				  IlFloat a01,
				  IlFloat a02,
				  IlFloat a03,
				  IlFloat a04,
				  IlFloat a10,
				  IlFloat a11,
				  IlFloat a12,
				  IlFloat a13,
				  IlFloat a14, 
				  IlFloat a20,
				  IlFloat a21,
				  IlFloat a22,
				  IlFloat a23,
				  IlFloat a24, 
				  IlFloat a30,
				  IlFloat a31,
				  IlFloat a32,
				  IlFloat a33,
				  IlFloat a34);
    const IlFloat*	getValues(IlUInt& count) const;
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_valuesValue;

 protected:
    IlFloat		_v[20];
};

class ILVFLTEXPORTED IlvSaturationFilter : public IlvColorMatrixFilter
{
public:
    IlvSaturationFilter(IlFloat saturation = 1.0);
    void		setSaturation(IlFloat saturation);
    inline IlFloat	getSaturation() const { return _saturation; }

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_saturationValue;

protected:
    IlFloat		_saturation;
};

class ILVFLTEXPORTED IlvLuminanceToAlphaFilter : public IlvColorMatrixFilter
{
 public:
    IlvLuminanceToAlphaFilter();
    IlvDeclareClassInfo();
};

class ILVFLTEXPORTED IlvHueRotateFilter : public IlvColorMatrixFilter
{
 public:
    IlvHueRotateFilter(IlFloat angle = 0.0);
    void		setAngle(IlFloat angle);
    inline IlFloat	getAngle() const { return _angle; }

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_angleValue;

protected:
    IlFloat		_angle;
};

ILVFLTMODULETERM(bitmaps_filters_colmatrix);

#endif /*  __Ilv_Bitmaps_Filters_Colmatrix_H */
