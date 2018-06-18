// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/compose.h
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
// Declaration of Porter-Duff Compose Filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Compose_H
#define __Ilv_Bitmaps_Filters_Compose_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvComposeFilter : public IlvBitmapFilter
{
 public:
    enum Operator {
	Over,
	In,
	Out,
	Atop,
	Xor,
	Arithmetic 
    };
    IlvComposeFilter(Operator op = Over,
		     IlFloat k1 = 0.0,
		     IlFloat k2 = 0.0,
		     IlFloat k3 = 0.0,
		     IlFloat k4 = 0.0);
    ~IlvComposeFilter();
    void		setOperator(Operator op);
    Operator		getOperator() const;
    inline IlFloat	getK1() const { return _k1; }
    inline IlFloat	getK2() const { return _k2; }
    inline IlFloat	getK3() const { return _k3; }
    inline IlFloat	getK4() const { return _k4; }
    inline void		setK1(IlFloat k1) { _k1 = k1; }
    inline void		setK2(IlFloat k2) { _k2 = k2; }
    inline void		setK3(IlFloat k3) { _k3 = k3; }
    inline void		setK4(IlFloat k4) { _k4 = k4; }
    inline void		getArithmeticValues(IlFloat& k1,
					    IlFloat& k2,
					    IlFloat& k3,
					    IlFloat& k4) const
			{
			    k1 = _k1;
			    k2 = _k2;
			    k3 = _k3;
			    k4 = _k4;
			}
    inline void		setArithmeticValues(IlFloat k1,
					    IlFloat k2,
					    IlFloat k3,
					    IlFloat k4)
			{
			    _k1 = k1;
			    _k2 = k2;
			    _k3 = k3;
			    _k4 = k4;
			}
    IlvBitmapData*	apply(IlUInt count = 0,
			      const IlvBitmapData** inputs = 0);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_operatorValue;
    static IlSymbol*	_k1Value;
    static IlSymbol*	_k2Value;
    static IlSymbol*	_k3Value;
    static IlSymbol*	_k4Value;

 protected:
    Operator		_operator;
    IlFloat		_k1;
    IlFloat		_k2;
    IlFloat		_k3;
    IlFloat		_k4;
};

ILVFLTMODULETERM(bitmaps_filters_compose);

#endif /* __Ilv_Bitmaps_Filters_Compose_H */
