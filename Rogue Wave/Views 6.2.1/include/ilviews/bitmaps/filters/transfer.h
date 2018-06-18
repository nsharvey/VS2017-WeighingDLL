// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/transfer.h
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
// Declaration of component transfer classes 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Transfer_H
#define __Ilv_Bitmaps_Filters_Transfer_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

#if !defined(__Ilv_Bitmaps_Transfer_H)
#include <ilviews/bitmaps/transfer.h>
#endif
#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvIdentityTransfer : public IlvTransferFunction
{
public:
    IlvIdentityTransfer();
    IlvDeclareClassInfo();

private:
    void		buildLookUpTable();
};


class ILVFLTEXPORTED IlvLinearTransfer : public IlvTransferFunction
{
public:
    IlvLinearTransfer(IlFloat slope = 1.0, IlFloat intercept = 0.0);
    void		setValues(IlFloat slope, IlFloat intercept);
    void		setSlope(IlFloat slope);
    void		setIntercept(IlFloat intercept);
    IlFloat		getSlope() const;
    IlFloat		getIntercept() const;

    static IlSymbol*	_slopeValue;
    static IlSymbol*	_interceptValue;

    DeclareValueAccessors();
    IlvDeclareClassInfo();

protected:
    IlFloat		_slope;
    IlFloat		_intercept;

private:
    void		buildLookUpTable();
};

class ILVFLTEXPORTED IlvTableTransfer : public IlvTransferFunction
{
public:
    IlvTableTransfer();
    IlvTableTransfer(IlUInt length, const IlFloat* values);
    ~IlvTableTransfer();
    void		setValues(IlUInt length, const IlFloat* values);
    const IlFloat*	getValues(IlUInt& count) const;

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_tableValue;

protected:
    IlFloat*		_tableValues;
    IlUInt		_length;

private:
    void		buildLookUpTable();
};

class ILVFLTEXPORTED IlvDiscreteTransfer : public IlvTransferFunction
{
public:
    IlvDiscreteTransfer();
    IlvDiscreteTransfer(IlUInt length, const IlFloat* values);
    ~IlvDiscreteTransfer();
    void		setValues(IlUInt length, const IlFloat* values);
    const IlFloat*	getValues(IlUInt& count) const;

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_tableValue;

private:
    void		buildLookUpTable();

    IlFloat*		_tableValues;
    IlUInt		_length;
};


class ILVFLTEXPORTED IlvGammaTransfer : public IlvTransferFunction
{
public:
    IlvGammaTransfer(IlFloat amplitude = 1.0,
		     IlFloat exponent = 1.0, 
		     IlFloat offset = 0.0);
    void		setValues(IlFloat amplitude,
				  IlFloat exponent,
				  IlFloat offset);
    void		setAmplitude(IlFloat amplitude);
    void		setExponent(IlFloat exponent);
    void		setOffset(IlFloat offset);
    IlFloat		getAmplitude() const;
    IlFloat		getExponent() const;
    IlFloat		getOffset() const;

    static IlSymbol*	_amplitudeValue;
    static IlSymbol*	_exponentValue;
    static IlSymbol*	_offsetValue;

    DeclareValueAccessors();
    IlvDeclareClassInfo();

 private:
    void		buildLookUpTable();

    IlFloat		_amplitude;
    IlFloat		_exponent;
    IlFloat		_offset;
};

ILVFLTMODULETERM(bitmaps_filters_transfer);

#endif /* __Ilv_Bitmaps_Filters_Transfer_H */
