// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/lights.h
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
// Declaration of lights 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Lights_H
#define __Ilv_Bitmaps_Filters_Lights_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Bitmaps_Lights_H)
#include <ilviews/bitmaps/lights.h>
#endif
#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvDistantLight : public IlvLightSource
{
public:
    IlvDistantLight(IlFloat azimuth = 0.0,
		    IlFloat elevation = 0.0,
		    IlFloat r = 1.0,
		    IlFloat g = 1.0,
		    IlFloat b = 1.0) 
	: IlvLightSource(r, g, b),
	  _azimuth(azimuth),
	  _elevation(elevation)
    {
	update(); 
    }
    inline void		setAzimuth(IlFloat azimuth)
			{
			    _azimuth = azimuth; 
			    update();
			}
    inline IlFloat	getAzimuth() const { return _azimuth; }
    inline void		setElevation(IlFloat elevation)
			{
			    _elevation = elevation; 
			    update();
			}
    inline IlFloat	getElevation() const { return _elevation; }
    void		update();
    void		getLightVector(IlFloat x, 
				       IlFloat y, 
				       IlFloat z, 
				       IlFloat* result);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_azimuthValue;
    static IlSymbol*	_elevationValue;

protected:
    IlFloat		_azimuth;    
    IlFloat		_elevation;
    IlFloat		_lightvector[3];
};


class ILVFLTEXPORTED IlvPointLight : public IlvLightSource
{
public:
    IlvPointLight(IlFloat x = 0.0, 
		  IlFloat y = 0.0, 
		  IlFloat z = 0.0,
		  IlFloat r = 1.0,
		  IlFloat g = 1.0,
		  IlFloat b = 1.0)
	: IlvLightSource(r, g, b),
	  _x(x),
	  _y(y),
	  _z(z)
    {}
    inline void		setX(IlFloat x)
			{
			    _x = x; 
			    update();
			}
    inline void		setY(IlFloat y)
			{
			    _y = y; 
			    update();
			}
    inline void		setZ(IlFloat z)
			{
			    _z = z; 
			    update();
			}
    inline IlFloat	getX() const { return _x; }
    inline IlFloat	getY() const { return _y; }
    inline IlFloat	getZ() const { return _z; }
    void		update();
    virtual void	setXYZ(IlFloat x, IlFloat y, IlFloat z) 
			{ 
			    _x = x; 
			    _y = y; 
			    _z = z; 
			    update();
			}
    virtual void	getXYZ(IlFloat& x, IlFloat& y, IlFloat& z) const
			{
			    x = _x; 
			    y = _y; 
			    z = _z; 
			}
    void		getLightVector(IlFloat x, 
				       IlFloat y, 
				       IlFloat z, 
				       IlFloat* result);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_xValue;
    static IlSymbol*	_yValue;
    static IlSymbol*	_zValue;

 protected:
    IlFloat		_x;
    IlFloat		_y;
    IlFloat		_z;
};

class ILVFLTEXPORTED IlvSpotLight : public IlvPointLight
{
 public:
    IlvSpotLight(IlFloat x = 0.0, 
		 IlFloat y = 0.0, 
		 IlFloat z = 0.0,
		 IlFloat tox = 0.0,		
		 IlFloat toy = 0.0,		
		 IlFloat toz = 0.0,
		 IlFloat specularExponent = 0.0,
		 IlFloat limitingConeAngle = 0.0,
		 IlFloat r = 1.0,
		 IlFloat g = 1.0,
		 IlFloat b = 1.0)
	: IlvPointLight(x, y, z, r, g, b),
	  _tox(tox),
	  _toy(toy),
	  _toz(toz),
	  _specularExponent(specularExponent),
	  _limitingConeAngle(limitingConeAngle) {
	update();
    }
    inline void		setToX(IlFloat tox)
			{
			    _tox = tox; 
			    update();
			}
    inline void		setToY(IlFloat toy)
			{
			    _toy = toy; 
			    update();
			}
    inline void		setToZ(IlFloat toz)
			{
			    _toz = toz; 
			    update();
			}
    inline IlFloat	getToX() const { return _tox; }
    inline IlFloat	getToY() const { return _toy; }
    inline IlFloat	getToZ() const { return _toz; }
    void		update();
    inline void		setToXYZ(IlFloat tox, IlFloat toy, IlFloat toz)
			{
			    _tox = tox; 
			    _toy = toy; 
			    _toz = toz; 
			    update();
			}
    inline void		getToXYZ(IlFloat& tox,
				 IlFloat& toy,
				 IlFloat& toz) const
			{
			    tox = _tox; 
			    toy = _toy; 
			    toz = _toz; 
			}
    inline void		setSpecularExponent(IlFloat exponent)
			{
			    _specularExponent = exponent; 
			    update(); 
			}
    inline void		setLimitingConeAngle(IlFloat coneangle)
			{
			    _limitingConeAngle = coneangle; 
			    update(); 
			}
    inline IlFloat	getSpecularExponent() const
			{
			    return _specularExponent; 
			}
    inline IlFloat	getLimitingConeAngle() const
			{
			    return _limitingConeAngle; 
			}
    void		getLightVector(IlFloat x, 
				       IlFloat y, 
				       IlFloat z, 
				       IlFloat* result);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_toxValue;
    static IlSymbol*	_toyValue;
    static IlSymbol*	_tozValue;
    static IlSymbol*	_specularValue;
    static IlSymbol*	_limitConeAngleValue;

 protected:

    IlFloat		_tox;
    IlFloat		_toy;
    IlFloat		_toz;
    IlFloat		_specularExponent;
    IlFloat		_limitingConeAngle;
    IlFloat		_limitingConeCos;
    IlFloat		_v0;
    IlFloat		_v1;
    IlFloat		_v2;
};

ILVFLTMODULETERM(bitmaps_filters_lights);

#endif /* __Ilv_Bitmaps_Filters_Lights_H */
