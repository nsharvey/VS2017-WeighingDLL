// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/fixquant.h
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
// Declaration of fixed colormap color quantization 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Fixedquant_H
#define __Ilv_Bitmaps_Fixedquant_H

#if !defined(__Ilv_Bitmaps_Quantize_H)
#include <ilviews/bitmaps/quantize.h>
#endif

class IlvColorMap;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFixedQuantizer : public IlvQuantizer
{
 public:
    IlvFixedQuantizer(IlvColorMap* cmap = 0);
    ~IlvFixedQuantizer();

    void		setColorMap(IlvColorMap* cmap);
    IlvColorMap*	getColorMap() const;
    IlvColorMap*	computeColorMap(const IlvBitmapData* data,
					IlUInt numcolors);

 protected:
    IlvColorMap*	_cmap;
};    

#endif /* __Ilv_Bitmaps_Fixedquant_H */
