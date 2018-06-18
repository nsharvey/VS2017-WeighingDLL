// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildval.h
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
// Values class for ADT
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDVAL_H
#define __ILD_ILDVAL_H

#ifndef __Il_INum_H
#   include <ildblink/ilinum.h>
#endif
#ifndef __Il_Ilidtime_H
#   include <ildblink/ilidtime.h>
#endif
#ifndef __ILD_ILDENT_H
#   include <ildblink/ildent.h>
#endif

#ifndef __Il_Array_H
#   include <ilog/array.h>
#endif

class IldADTDescriptor;
class IldADTValue;

// ----------------------------------------------------------------------------
// Polymorphic value class
// ----------------------------------------------------------------------------
class ILD_EXPORTED IldValue {

protected:
    IldColumnType _type;
    union {
		IlAny a;
		IlUChar b;
		IlInt i;
		double d;
		char*  s;
		IldBytes* bs;
		IlNumeric* n;
		IldDateTime* dt;
		IldADTValue* v;
    }		_val;
    IlBoolean	_null;

    void          clear           ();
    IlBoolean     checkIndex      (IlUShort);

public:
	IldValue	();
	IldValue	(IlUChar);
	IldValue	(IlInt);
	IldValue	(double);
	IldValue	(const char*,
				 int size = 0);
	IldValue	(const IldBytes&);
	IldValue	(const IldDateTime&);
	IldValue	(const IlNumeric&);
	IldValue	(IldADTValue*);
	IldValue	(IlAny);
    virtual 
	~IldValue       ();
    inline
	IlBoolean		isNull          ();
    inline
	void		setType		(IldColumnType t);
    inline
	IldColumnType	getType         () const;
    inline
	IlAny		getAny		() const;
    inline
	IlUChar		getByte         () const;
    inline
	IlAny		getByteAddr     () const;
    inline
	IlInt		getInteger      () const;
    inline
	IlAny		getIntAddr      () const;
    inline
	double		getReal         () const;
    inline
	IlAny		getRealAddr     () const;
    inline
	const char*	getString       () const;
    inline
	const char*	getPurgedString () const;
    inline
	IldBytes		getBytes	() const;
    inline
	IldBytes*	getBytesAddr	() const;
    inline
	IlNumeric		getNumeric	() const;
    inline
	IlNumeric*	getNumericAddr	() const;
    inline
	IldDateTime	getDateTime     () const;
    inline
	IldDateTime* getDateTimeAddr	() const;
    inline
	IldADTValue*	getADTValue     () const;
    inline
	void		setNull         (IlBoolean null);
    IlBoolean		set             (IlUChar b);
    IlBoolean		set             (IlInt i);
    IlBoolean		set             (double d);
    IlBoolean		set             (const char* s,
									 int size = 0);
    IlBoolean		set             (const IldBytes*);
    IlBoolean		set             (const IlNumeric*);
    IlBoolean		set             (const IldDateTime*);
    IlBoolean		set             (IldADTValue*);
    IlBoolean		set		(IlAny);

};

// ----------------------------------------------------------------------------
inline void
IldValue::setType(IldColumnType t)
{
	_type = t;
}

inline IldColumnType 
IldValue::getType () const
{
    return _type;
}

inline IlBoolean
IldValue::isNull ()
{
    return _null;
}

inline IlAny
IldValue::getAny () const
{
    return _val.a;
}

inline IlUChar
IldValue::getByte () const
{
    return _val.b;
}

inline IlAny
IldValue::getByteAddr () const
{
	return (IlAny)&_val.b;
}

inline IlInt
IldValue::getInteger () const
{
    return _val.i;
}

inline IlAny
IldValue::getIntAddr () const
{
	return (IlAny)&_val.i;
}

inline double
IldValue::getReal () const
{
    return _val.d;
}

inline IlAny
IldValue::getRealAddr () const
{
  return (IlAny)&_val.d;
}

inline const char*
IldValue::getString () const
{
    return _val.s;
}

inline const char*
IldValue::getPurgedString () const
{
    return (const char*)IldStrRTrim(_val.s, (IlUInt)strlen(_val.s));
}

inline IldBytes
IldValue::getBytes () const
{
    return *_val.bs;
}

inline IldBytes*
IldValue::getBytesAddr () const
{
    return _val.bs;
}

inline IlNumeric
IldValue::getNumeric  () const
{
    return *_val.n;
}

inline IlNumeric*
IldValue::getNumericAddr  () const
{
	return _val.n;
}

inline IldDateTime
IldValue::getDateTime() const
{
	return *_val.dt;
}

inline IldDateTime*
IldValue::getDateTimeAddr () const
{
	return _val.dt; 
}

inline IldADTValue*
IldValue::getADTValue () const
{
    return _val.v;
}

inline void
IldValue::setNull (IlBoolean null)
{
    _null = null;
}

#endif // __ILD_ILDVAL_H
