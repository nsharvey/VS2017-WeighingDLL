// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/lighting.h
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
// Declaration of lighting filters 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Lighting_H
#define __Ilv_Bitmaps_Filters_Lighting_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class IlvLightSource;

class ILVFLTEXPORTED IlvLightingFilter : public IlvBitmapFilter
{
public:
    IlvLightingFilter(IlFloat surfaceScale = 1.0,
		      IlvLightSource* light = 0);
    virtual ~IlvLightingFilter();
    inline void		setSurfaceScale(IlFloat scale)
			{
			    _surfaceScale = scale;
			}
    inline IlFloat	getSurfaceScale() const { return _surfaceScale; }
    void		setLightSource(IlvLightSource* light);
    inline IlvLightSource*	getLightSource() const { return _light; }
    IlFloat*		computeBumpMap(const IlvRGBBitmapData* src,
				       IlFloat scaleX,
				       IlFloat scaleY);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_surfaceScaleValue;
    static IlSymbol*	_lightValue;

protected:
    IlFloat		_surfaceScale;
    IlvLightSource*	_light;
};   


class ILVFLTEXPORTED IlvDiffuseLightingFilter : public IlvLightingFilter
{
public:
    IlvDiffuseLightingFilter(IlFloat surfaceScale = 1.0,
			     IlFloat diffuseConstant = 1.0,
			     IlvLightSource* light = 0);
    ~IlvDiffuseLightingFilter();
    inline void		setDiffuseConstant(IlFloat diffuse)
			{
			    _diffuseConstant = diffuse; 
			}
    inline IlFloat	getDiffuseConstant() const { return _diffuseConstant; }
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_diffuseConstantValue;

 protected:
    IlFloat		_diffuseConstant;
};


class ILVFLTEXPORTED IlvSpecularLightingFilter : public IlvLightingFilter
{
public:
    IlvSpecularLightingFilter(IlFloat surfaceScale = 1.0,
			      IlFloat specularConstant = 1.0,
			      IlFloat specularExponent = 1.0,
			      IlvLightSource* light = 0);
    ~IlvSpecularLightingFilter();
    inline void		setSpecularConstant(IlFloat specularConstant)
			{
			    _specularConstant = specularConstant; 
			}
    inline void		setSpecularExponent(IlFloat specularExponent)
			{
			    _specularExponent = specularExponent; 
			}

    inline IlFloat	getSpecularConstant() const
			{
			    return _specularConstant; 
			}
    inline IlFloat	getSpecularExponent() const
			{
			    return _specularExponent; 
			}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_specularConstantValue;
    static IlSymbol*	_specularExponentValue;

 protected:
    IlFloat		_specularConstant;
    IlFloat		_specularExponent;
};

ILVFLTMODULETERM(bitmaps_filters_lighting);

#endif /* __Ilv_Bitmaps_Filters_Lighting_H */
