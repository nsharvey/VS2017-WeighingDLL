// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/all.h
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
//
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_All_H
#define __Ilv31_Variable_All_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Boolean_H)
#include <ilviews/variable/boolean.h>
#endif
#if !defined(__Ilv31_Variable_Streams_H)
#include <ilviews/variable/streams.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

enum IlvvDiscriminant
{
   ILVV_UNDEF,
   ILVV_UCHAR,  // unsigned char
   ILVV_CHAR,   // char
   ILVV_USHORT, // unsigned short
   ILVV_SHORT,  // short
   ILVV_UINT,   // unsigned int
   ILVV_INT,    // int
   ILVV_ULONG,  // unsigned long
   ILVV_LONG,   // long
   ILVV_FLOAT,  // float
   ILVV_DOUBLE, // double
   ILVV_CHARP   // char*
};

// signed fundamentals do not seem to be different
// on compilers <= 3.0.1
class ILV31VAREXPORTED IlvvFundamental
{
public:
    IlvvFundamental(): _discriminant(ILVV_UNDEF) { _value._ulong = 0;}
    // if char*, must copy it
    IlvvFundamental(const IlvvFundamental&);
    IlvvFundamental& operator=(const IlvvFundamental&);
    // if char*, must delete it
    ~IlvvFundamental()
	{ if (_discriminant==ILVV_CHARP) delete [] _value._charp; }
    // ____________________________________________________________
    IlvvFundamental(char);
    IlvvFundamental(unsigned char);
    IlvvFundamental(short);
    IlvvFundamental(unsigned short);
    IlvvFundamental(int);
    IlvvFundamental(unsigned int);
    IlvvFundamental(long);
    IlvvFundamental(unsigned long);
    IlvvFundamental(float);
    IlvvFundamental(double);
    IlvvFundamental(char*);
    IlvvDiscriminant getDiscriminant() const;
    // casting functions
    IlvvFundamental charCast() const;
    IlvvFundamental ucharCast() const;
    IlvvFundamental shortCast() const;
    IlvvFundamental ushortCast() const;
    IlvvFundamental intCast() const;
    IlvvFundamental uintCast() const;
    IlvvFundamental longCast() const;
    IlvvFundamental ulongCast() const;
    IlvvFundamental floatCast() const;
    IlvvFundamental doubleCast() const;
    IlvvFundamental charpCast() const;
    // these conversion operators perform dynamic typecheck
    // and possibly promotion of types (e.g.: char to int)
    operator char() const;
    operator unsigned char() const;
    operator short() const;
    operator unsigned short() const;
    operator int() const;
    operator unsigned int() const;
    operator long() const;
    operator unsigned long() const;
    operator float() const;
    operator double() const;
    operator char*() const;
    IlvvFundamental operator-() const;
    unsigned char operator!() const;
    IlvvFundamental operator~() const;
    IlvvFundamental operator+(const IlvvFundamental&) const;
    IlvvFundamental operator-(const IlvvFundamental&) const;
    IlvvFundamental operator*(const IlvvFundamental&) const;
    IlvvFundamental operator/(const IlvvFundamental&) const;
    unsigned char operator<(const IlvvFundamental&) const;
    unsigned char operator>(const IlvvFundamental&) const;
    unsigned char operator<=(const IlvvFundamental&) const;
    unsigned char operator>=(const IlvvFundamental&) const;
    unsigned char operator||(const IlvvFundamental&) const;
    unsigned char operator&&(const IlvvFundamental&) const;
    IlvvFundamental operator|(const IlvvFundamental&) const;
    IlvvFundamental operator&(const IlvvFundamental&) const;
    IlvvFundamental operator^(const IlvvFundamental&) const;
    IlvvFundamental operator%(const IlvvFundamental&) const;
    IlvvFundamental operator<<(const IlvvFundamental&) const;
    IlvvFundamental operator>>(const IlvvFundamental&) const;
    unsigned char operator==(const IlvvFundamental&) const;
    unsigned char operator!=(const IlvvFundamental&) const;
    IlvvFundamental harmonize(const IlvvFundamental&) const;
    static void setTypecheckFailed(void (*)());
    static void (*getTypecheckFailed())();
    static void typecheckFailed();
    static IlvvFundamental undef;
private:
   IlvvDiscriminant _discriminant;
   union {
	char           _char;
	unsigned char  _uchar;
	short          _short;
	unsigned short _ushort;
	long           _long;
	unsigned long  _ulong;
	int            _int;
	unsigned int   _uint;
	float          _float;
	double         _double;
	char*          _charp;
   } _value;
   static void (*_typecheckFailed)();
};

IlvvOStream& operator<<(IlvvOStream&, const IlvvFundamental&);
#if defined(ILVV_USE_STREAMPATCH)
ILVSTDPREF ostream& operator<<(ILVSTDPREF ostream&, const IlvvFundamental&);
#endif

#endif
