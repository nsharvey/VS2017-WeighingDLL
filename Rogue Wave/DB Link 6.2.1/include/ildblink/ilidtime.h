// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilidtime.h
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
// Date and Time internationalization
//
// --------------------------------------------------------------------------

#ifndef __Il_Ilidtime_H
#define __Il_Ilidtime_H

#ifndef __Il_Env_H
# include <ildblink/ilenv.h>
#endif

class ILD_EXPORTED IldDateTime {
public:
    IldDateTime(IlEnvironment* envt);
    IldDateTime(IlEnvironment* envt, IldDateTime& dt);
    IldDateTime(IlEnvironment* envt,
		short year,
		IlUShort month,
		IlUShort day,
		IlUShort hour = 0,
		IlUShort minute = 0,
		IlUShort second = 0,
		IlUShort msecond = 0);
    IldDateTime(const IldDateTime& o);

     virtual ~IldDateTime();

    /*
     * \short Indicates if the current object is or is not valid.
     *
     * \return \c IlTrue if the object is not valid
     *   and \c IlFalse otherwise.
     */
    IlBoolean isBad () const
	{ return _bad; }
    short		getYear		() const;
    void		setYear		(short year);
    IlUShort		getMonth	() const;
    void		setMonth	(IlUShort month);
    IlUShort		getDay		() const;
    void		setDay		(IlUShort day);
    IlUShort		getHour		() const;
    void		setHour		(IlUShort hour);
    IlUShort		getMinute	() const;
    void		setMinute	(IlUShort minute);
    IlUShort		getSecond	() const;
    void		setSecond	(IlUShort second);
    IlUShort		getMSecond	() const;
    void		setMSecond	(IlUShort msecond);

    void		setTime		(IlUShort hour,
					 IlUShort minute,
					 IlUShort second,
					 IlUShort msecond = 0);
    IlInt		getTime		() const;
    operator		IlInt		() const;
    void		setDate		(short year,
					 IlUShort month,
					 IlUShort day);
    void		set		(short year,
					 IlUShort month,
					 IlUShort day,
					 IlUShort hour,
					 IlUShort minute,
					 IlUShort second,
					 IlUShort msecond = 0);
    IlBoolean		setNow		();
    IlBoolean		get		(short& y,
					 IlUShort& mth,
					 IlUShort& d,
					 IlUShort& h,
					 IlUShort& m,
					 IlUShort& s,
					 IlUShort& ms);

    /*
     * \short Comparison operator
     *
     * \param other The date and time object to compare with \c this.
     *
     * \return \c IlTrue if the two objects have identical contents
     *   in term of date and time parts.
     * 
     * \note
     * The comparison <b>does not</b> take into account the
     * time zone nor the locale. Only the represented date and time elements 
     * are compared.
     */
    IlBoolean		operator==	(IldDateTime& other);

    IldDateTime& operator=(const IldDateTime& other);

    // Compatibility: DO NOT use in internationalized context
    IldDateTime();
    // Compatibility: DO NOT use in internationalized context
    IldDateTime	(short year,
		 IlUShort month,
		 IlUShort day,
		 IlUShort hour = 0,
		 IlUShort minute = 0,
		 IlUShort second = 0,
		 IlUShort msecond = 0);

    void		setNullPointer(IlBoolean del = IlTrue);
protected:
    IlEnvironment*	_environment;
    IlBoolean		_bad;
    // Compatibility: actually overkill now.
    // These fields are doomed just like the old methods.
    short		_year;
    unsigned short	_month;
    unsigned short	_day;
    unsigned short	_hour;
    unsigned short	_minute;
    unsigned short	_second;
    unsigned short	_msecond;
protected:
    // Internals
    struct		P;
    struct P*		_p;
};
#endif /* !__Il_Ilidtime_H */
