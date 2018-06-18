// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/decimal.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDecimal class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Decimal_H
#define __Ili_Decimal_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Refcount_H
#  include <ilviews/dataccess/refcount.h>
#endif

// --------------------------------------------------------------------------
class IliDecimalIpl
: public IliRefCounted
{
public:
    IliDecimalIpl()
    : IliRefCounted()
    {}

    virtual IlBoolean	isEqualTo(const IliDecimalIpl*) const = 0;
    virtual int		compareTo(const IliDecimalIpl*) const = 0;

protected:
    virtual ~IliDecimalIpl();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDecimal
{
public:
    IliDecimal();

    IliDecimal(IlInt val);
    IliDecimal(IlDouble val);
    IliDecimal(const IliDecimal&);
    IliDecimal(IliDecimalIpl*);
    virtual ~IliDecimal();

    enum Tag {
	MaxPrecision = 40,
	MaxStringLength = 50
    };

    const IliDecimal& operator=(const IliDecimal& dec);
    const IliDecimal& operator=(IlInt val);
    const IliDecimal& operator=(IlDouble val);
    const IliDecimal& operator=(IliDecimalIpl*);
    IlInt		getSign() const;
    IlInt		getPrecision() const;
    IlInt		getScale() const;
    IlBoolean		setString(const char* value);
    char*		toString(char* buffer, int size) const;

    IliDecimal		abs() const;
    IliDecimal operator-() const;
    IliDecimal operator+(const IliDecimal& dec) const;
    IliDecimal operator-(const IliDecimal& dec) const;
    IliDecimal operator*(const IliDecimal& dec) const;

    int			compareTo(const IliDecimal& dec) const;

    int operator==(const IliDecimal& dec) const;
    int operator!=(const IliDecimal& dec) const;
    int operator>=(const IliDecimal& dec) const;
    int operator>(const IliDecimal& dec) const;
    int operator<=(const IliDecimal& dec) const;
    int operator<(const IliDecimal& dec) const;

    IlBoolean		fitsInInteger() const;
    IlBoolean		fitsInDouble() const;
    IlBoolean		toInteger(IlInt& buff) const;
    IlBoolean		toDouble(IlDouble& val) const;

    IlInt		asInt() const;
    IlDouble		asDouble() const;

    operator const IliDecimalIpl*() const;
    operator IliDecimalIpl*();

#ifdef _DEBUG
    static void		UnitaryTest(IL_STDPREF ostream&);
#endif

private:
    IliDecimalIpl*	_ipl;

    void		newIpl();
    void		setIpl(IliDecimalIpl*);
};

IliModuleDECL_exp(ILV_INF_EXPORTED, IliDecimal);

#endif /* !__Ili_Decimal_H */
