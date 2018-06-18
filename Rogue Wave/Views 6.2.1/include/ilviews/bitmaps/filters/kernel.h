// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/kernel.h
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
// Declaration of kernel 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Kernel_H
#define __Ilv_Bitmaps_Filters_Kernel_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvBitmapDataKernel : public IlvValueInterface
{
 public:
    enum KernelHint {
	Normal,
	Nice
    };
    IlvBitmapDataKernel();
    IlvBitmapDataKernel(IlUInt width, IlUInt height, const IlFloat* values);
    IlvBitmapDataKernel(IlUInt width, IlUInt height, const char* values);
    virtual ~IlvBitmapDataKernel();
    void		setValues(IlUInt width,
				  IlUInt height,
				  const IlFloat* values);
    void		setValues(IlUInt width, 
				  IlUInt height, 
				  const char* values);
    void		setWidth(IlUInt width);
    void		setHeight(IlUInt height);
    void		setKernelString(const char* values);
    const char*		getKernelString();
    IlUInt		getWidth() const;
    IlUInt		getHeight() const;
    const IlFloat*	getKernelValues(IlUInt& width, IlUInt& height) const;
    inline KernelHint	getHints() const { return _hints; }
    inline void		setHints(KernelHint hints) { _hints = hints; }
    virtual IlUInt	getXOrigin() const;
    virtual IlUInt	getYOrigin() const;

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol* _widthValue;
    static IlSymbol* _heightValue;
    static IlSymbol* _valuesValue;

protected:
    IlUInt		_width;
    IlUInt		_height;
    IlFloat*		_values;
    KernelHint		_hints;

private:
    char*		_kernelstring;
};

ILVFLTMODULETERM(bitmaps_filters_kernel);

#endif /* __Ilv_Bitmaps_Filters_Kernel_H */
