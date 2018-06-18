// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/gaussian.h
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
// Declaration of Gaussian Blur Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_GaussianBlur_H
#define __Ilv_Bitmaps_Filters_GaussianBlur_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif

class IlvBitmapDataKernel;
class IlvConvolutionFilter;


class ILVFLTEXPORTED IlvGaussianBlurFilter : public IlvBitmapFilter
{
public:
    IlvGaussianBlurFilter(IlFloat deviationX = 1.0,
			  IlFloat deviationY = 1.0);

    ~IlvGaussianBlurFilter();
    inline IlUInt	getRadiusX() const { return _radiusX; }
    inline IlUInt	getRadiusY() const { return _radiusY; }
    inline IlFloat	getDeviationX() const { return _deviationX; }
    inline IlFloat	getDeviationY() const { return _deviationY; }
    void		setDeviationX(IlFloat deviation);
    void		setDeviationY(IlFloat deviation);
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_deviationXValue;
    static IlSymbol*	_deviationYValue;

protected:
    IlvConvolutionFilter*	computeConvolution(IlFloat deviation, 
						   IlUInt& radius,
						   IlBoolean horizontal);
    IlFloat*			computeKernelData(IlUInt radius, 
						  IlFloat deviation);
    IlvBitmapDataKernel*	makeKernel(IlUInt radius, 
					   IlFloat deviation,
					   IlBoolean horzontal);

    IlvConvolutionFilter*	_convolutionX;
    IlvConvolutionFilter*	_convolutionY;
    IlFloat			_deviationX;
    IlFloat			_deviationY;
    IlUInt			_radiusX;
    IlUInt			_radiusY;
};

ILVFLTMODULETERM(bitmaps_filters_gaussian);

#endif /* __Ilv_Bitmaps_Filters_GaussianBlur_H */
