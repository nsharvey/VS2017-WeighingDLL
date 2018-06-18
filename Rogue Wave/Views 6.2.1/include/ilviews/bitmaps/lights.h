// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/lights.h
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
#ifndef __Ilv_Bitmaps_Lights_H
#define __Ilv_Bitmaps_Lights_H

#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif


class ILVDSPEXPORTED IlvLightSource : public IlvValueInterface
{
public:
    IlvLightSource(IlFloat r = 1.0, 
		   IlFloat g = 1.0, 
		   IlFloat b = 1.0);
    virtual ~IlvLightSource();
    inline IlFloat	getR() const { return _r; };
    inline IlFloat	getG() const { return _g; };
    inline IlFloat	getB() const { return _b; };
    inline void		setR(IlFloat r) { _r = r; }
    inline void		setG(IlFloat g) { _g = g; }
    inline void		setB(IlFloat b) { _b = b; }
    virtual void	update();
    virtual void	getLightVector(IlFloat x, 
				       IlFloat y, 
				       IlFloat z, 
				       IlFloat* result);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_rValue;
    static IlSymbol*	_gValue;
    static IlSymbol*	_bValue;

    static IlvLightSource*	Create(const char* name);

protected:
    IlFloat		_r;
    IlFloat		_g;
    IlFloat		_b;
};

ILVDSPMODULEINIT(bitmaps_lights);
#endif /* __Ilv_Bitmaps_Lights_H */
