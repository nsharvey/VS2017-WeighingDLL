// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/ilnum.h
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
// Numeric class
// --------------------------------------------------------------------------
#ifndef __Il_IlNum_H
#define __Il_IlNum_H

#ifndef __Il_Macros_H
# include <ilog/macros.h>
#endif

#ifdef IL_STD
# ifndef _CLIMITS_
#  include <climits>
# endif
# ifndef _STRING_
#  include <string>
# endif
# ifndef _CSTRING_
#  include <cstring>
# endif
#else
# ifndef _STRING_H
#  include <string.h>
# endif
#endif

#if !defined(__IlNUMERIC)
#define __IlNUMERIC

#define IL_MAX_NUM_LEN 48

class ILOG_EXPORTED IlNumeric
{
private:
    IlShort	_neg;
    IlShort	_exp;
    char	_digits[IL_MAX_NUM_LEN];

    IlNumeric	add(const IlNumeric& n) const;
    IlNumeric	sub(const IlNumeric& n) const;

    IlBoolean	isGreaterThan(const IlNumeric& n) const;
    IlBoolean	isEqualTo(const IlNumeric& n) const;
    inline
    IlBoolean	isLesserThan(const IlNumeric& n) const;
    IlInt	toDec(char* decDgts) const;

public:
    IlNumeric()
	: _neg(0),
	  _exp(0)
    {
	memset(_digits, 0, IL_MAX_NUM_LEN);
    }
    IlNumeric(const char* value);
    IlNumeric(long value);

    IlNumeric(const IlNumeric&);

    ~IlNumeric() {};
    IlNumeric&	setScale(IlShort scale) ;
    inline
    IlShort	getPrecision() const;
    inline
    IlShort	getScale() const;
    inline
    IlBoolean	isNegative() const;
    inline
    void	negate();
    IlBoolean	set(const char* value);
    IlBoolean	set(long value);
    void	get(char* buffer, IlInt len) const;
    IlBoolean	isZero() const;
    IlBoolean	isInteger() const;
    IlBoolean	isReal() const;
    IlNumeric	abs() const;
    IlNumeric	operator+(const IlNumeric&);
    IlNumeric	operator+(long);
    IlNumeric	operator-(const IlNumeric&);
    IlNumeric	operator*(const IlNumeric&);
    inline
    IlBoolean	operator==(const IlNumeric& n) const;
    inline
    IlBoolean	operator>=(const IlNumeric& n) const;
    inline
    IlBoolean	operator>(const IlNumeric& n) const;
    inline
    IlBoolean	operator<=(const IlNumeric& n) const;
    inline
    IlBoolean	operator<(const IlNumeric& n) const;
    operator	long() const;
    operator	double() const;

    IlNumeric& operator=(const IlNumeric& other);

    void set(const IlNumeric& other);
};

inline IlBoolean
IlNumeric::isLesserThan (const IlNumeric& n) const
{
    return !isGreaterThan(n) || isEqualTo(n);
}
inline IlShort
IlNumeric::getPrecision () const
{
    return (IlShort)strlen(_digits);
}
inline IlShort
IlNumeric::getScale () const
{
    return (IlShort)(getPrecision() - _exp);
}
inline IlBoolean
IlNumeric::isNegative () const
{
    return _neg > 0 ;
}
inline void
IlNumeric::negate ()
{
    _neg = (_neg ? (short) 0 : (short) 1);
}
inline IlBoolean
IlNumeric::operator== (const IlNumeric& n) const
{
    return (int)isEqualTo(n);
}
inline IlBoolean
IlNumeric::operator>= (const IlNumeric& n) const
{
    return (int)isGreaterThan(n);
}
inline IlBoolean
IlNumeric::operator> (const IlNumeric& n) const
{
    return (int)(!isEqualTo(n) && isGreaterThan(n));
}
inline IlBoolean
IlNumeric::operator<= (const IlNumeric& n) const
{
    return (int)isLesserThan(n);
}
inline IlBoolean
IlNumeric::operator< (const IlNumeric& n) const
{
    return (int)(!isEqualTo(n) && isLesserThan(n));
}

#endif /* __IlNUMERIC */

#endif /* __Il_IlNum_H */
