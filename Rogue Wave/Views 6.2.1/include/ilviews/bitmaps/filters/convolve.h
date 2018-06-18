// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/convolve.h
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
// Declaration of Convolution Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Convolution_H
#define __Ilv_Bitmaps_Filters_Convolution_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Kernel_H)
#include <ilviews/bitmaps/filters/kernel.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif



// --------------------------------------------------------------------------
class ILVFLTEXPORTED IlvConvolutionFilter : public IlvBitmapFilter
{
public:
    IlvConvolutionFilter(IlvBitmapDataKernel* kernel = 0,
			 IlFloat divisor = 0,
			 IlFloat bias = 0.0);
    ~IlvConvolutionFilter();
    void			setKernel(IlvBitmapDataKernel* kernel);
    IlvBitmapDataKernel*	getKernel() const;
    void			setDivisor(IlFloat divisor);
    IlFloat			getDivisor() const;
    void			setBias(IlFloat bias);
    IlFloat			getBias() const;

    enum EdgeMode {
	Duplicate,
	Wrap,
	None
    };
    void		setEdgeMode(IlvConvolutionFilter::EdgeMode mode);
    IlvConvolutionFilter::EdgeMode	getEdgeMode() const;
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_divisorValue;
    static IlSymbol*	_biasValue;
    static IlSymbol*	_orderXValue;
    static IlSymbol*	_orderYValue;
    static IlSymbol*	_kernelMatrixValue;

protected:
    void		getRowData(IlInt row, 
				   IlUChar* dst, 
				   IlUInt dstwidth,
				   IlUInt border,
				   IlvRGBBitmapData* src);

    IlvBitmapDataKernel*		_kernel;
    IlFloat				_divisor;
    IlFloat				_bias;
    IlvConvolutionFilter::EdgeMode	_edgemode;
};

ILVFLTMODULETERM(bitmaps_filters_convolution);

#endif /* __Ilv_Bitmaps_Filters_Convolution_H */
