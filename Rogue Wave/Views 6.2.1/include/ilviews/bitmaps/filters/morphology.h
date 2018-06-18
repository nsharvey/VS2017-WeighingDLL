// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/morphology.h
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
// Declaration of Morphology Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Morphology_H
#define __Ilv_Bitmaps_Filters_Morphology_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvMorphologyFilter : public IlvBitmapFilter
{
public:
    enum Operator {
	Erode,
	Dilate
    };
    IlvMorphologyFilter(IlUInt radiusX = 0,
			IlUInt radiusY = 0,
			Operator op = Erode);
    ~IlvMorphologyFilter();
    inline IlUInt	getRadiusX() const { return _radiusX; }
    inline IlUInt	getRadiusY() const { return _radiusY; }
    IlUInt		getRangeX() const;
    IlUInt		getRangeY() const;
    inline Operator	getOperator() const { return _operator; }
    void		setRadiusX(IlUInt radius);
    void		setRadiusY(IlUInt radius);
    void		setOperator(Operator op);
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_radiusXValue;
    static IlSymbol*	_radiusYValue;
    static IlSymbol*	_operatorValue;
protected:
    IlvRGBBitmapData*	fastErode(IlvRGBBitmapData* src);
    IlvRGBBitmapData*	fastDilate(IlvRGBBitmapData* src);
    IlvRGBBitmapData*	slowErodeDilate(IlvRGBBitmapData* src);

    IlUInt		_radiusX;
    IlUInt		_radiusY;
    Operator		_operator;
};

ILVFLTMODULETERM(bitmaps_filters_morphology);

#endif /* __Ilv_Bitmaps_Filters_Morphology_H */
