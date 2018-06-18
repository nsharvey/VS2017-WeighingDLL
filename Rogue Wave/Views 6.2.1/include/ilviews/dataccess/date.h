// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/date.h
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
// Declaration of the IliDate class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Date_H
#define __Ili_Date_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#include <ctime>
#include <iostream>
#else
#include <time.h>
#include <iostream.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

#ifndef __Ili_Cstenum_H
#  include <ilviews/dataccess/cstenum.h>
#endif

struct IliTimeRecord
{
    IlUChar _hour          : 5;   // 0..23
    IlUChar _minutes       : 6;   // 0..59
    IlUChar _seconds       : 6;   // 0..59
    IlUShort _milliseconds : 10;  // 0..999
};

struct IliDateRecord
{
    IlInt _year            : 32;  // 1..2000000000
    IlUChar _month         : 4;   // 1..12
    IlUChar _day           : 5;   // 1..31
    IlUChar _hour          : 5;   // 0..23
    IlUChar _minutes       : 6;   // 0..59
    IlUChar _seconds       : 6;   // 0..59
    IlUShort _milliseconds : 10;  // 0..999

    IliTimeRecord getTimeRecord() const;
};

class ILV_INF_EXPORTED IliTime
{
public:
    IliTime();

    IliTime(IlInt hour,IlInt minu,IlInt sec);

    IliTime(const IliTime& time);

    IliTime(const IliTimeRecord&);
    ~IliTime() {}

    void		read(IL_STDPREF istream& input);
    void		write(IL_STDPREF ostream& output) const;

    IliTime& operator	=(const IliTime& time);

    IliTime& operator	=(const IliTimeRecord&);

    int operator	==(const IliTime& time) const;

    int operator	!=(const IliTime& time) const;

    int operator	<(const IliTime& time) const;

    int operator	<=(const IliTime& time) const;

    int operator	>(const IliTime& time) const;

    int operator	>=(const IliTime& time) const;

    IlBoolean		hasTime() const;

    IlInt		getHour() const; // 0-23

    void		setHour(IlInt h);

    IlInt		getMinutes() const; // 0-59

    void		setMinutes(IlInt m);

    IlInt		getSeconds() const;  // 0-59

    void		setSeconds(IlInt s);

    IlInt		getMilliseconds() const; // 0..999
    void		setMilliseconds(IlInt ms);

    operator const IliTimeRecord&() const { return _dr; }

    static const IliTime& GetDefault();

protected:
    IliTimeRecord	_dr;
    friend class IliDate;
};

#if defined(__hpux) && __cplusplus == 1L
typedef struct tm IliStructTm;
#endif

class ILV_INF_EXPORTED IliDate
{
public:
    IliDate();

    IliDate(IlInt y,IlInt mo,IlInt d,IlInt h = 0,IlInt m = 0,IlInt s = 0);

    IliDate(const IliTime&);
    IliDate(const IliDate&);
    IliDate(const IliDateRecord&);
    ~IliDate() {}

    void		read(IL_STDPREF istream& input);

    void		write(IL_STDPREF ostream& output) const;

#if !defined(__hpux) || __cplusplus > 1L
    operator struct tm() const;
#else
    operator IliStructTm() const;
#endif

    IliDate& operator	=(const struct tm& t);

    IliDate& operator	=(const IliTime&);

    IlBoolean		hasDate() const;
    IlBoolean		hasTime() const;

    IliDate& operator	=(const IliDate& d);
    IliDate& operator	=(const IliDateRecord&);

    int operator	==(const IliDate& d) const;

    int operator	!=(const IliDate& d) const;

    int operator	<(const IliDate& d) const;

    int operator	<=(const IliDate& d) const;

    int operator	>(const IliDate& d) const;

    int operator	>=(const IliDate& d) const;

    IlInt		getYear() const;  // eg 1964

    void		setYear(IlInt y);

    IlInt		getMonth() const;  // 1-12

    void		setMonth(IlInt m);

    IlInt		getMonthDay() const;  // 1-31

    void		setMonthDay(IlInt md);

    IlBoolean		isLeapYear() const;
    IlBoolean		isLeap() const;

    IlBoolean		isDayValid() const;

    IlInt		getMonthDaysCount() const;

    IlInt		getFirstYearDayOfMonth() const; // 1..366

    IlInt		getYearDay() const;  // 1-366

    IlInt		getWeekDay() const;  // 1-7

    IlInt		getQuarter() const;  // 1-4

    IlInt		getYearWeek() const; // 1..52

    IlInt		getHour() const; // 0-23

    void		setHour(IlInt h);

    IlInt		getMinutes() const; // 0-59

    void		setMinutes(IlInt m);

    IlInt		getSeconds() const;  // 0-59

    void		setSeconds(IlInt s);

    IlInt		getMilliseconds() const; // 0..999
    void		setMilliseconds(IlInt ms);

    IlInt operator	[](IliDateInfo ndx) const;

    IliTime		getTime() const;
    void		setTime(const IliTime&);

    operator const IliDateRecord&() const { return _dr; }

    static const IliDate& GetDefault();

    void		addNumeric(IlInt val = 1);
    void		addYear();
    void		addMonth();
    void		addDay(IlInt days = 1);
    void		addHour(IlInt val);
    void		addMinute(IlInt val);
    void		addSecond(IlInt val);
    void		set(IlInt,
			    IlInt,
			    IlInt,
			    IlInt = 0,
			    IlInt = 0,
			    IlInt = 0,
			    IlInt = 0);
    IlBoolean		isLeap(IlInt y) const;

    IlInt		getDayCount() const;
    IlInt		getDiffDays(IliDate&) const;
    IlInt		getDiffMonths(const IliDate& d) const;

protected:
    IliDateRecord	_dr;

    IlInt		getAbsoluteDate() const;
    void		setAbsoluteDate(IlInt absDate);

    IlInt		getJulianDate() const;
    void		setJulianDate(IlInt julDate);

    static IlInt	JulianToAbsoluteDate(IlInt julianDate);
    static IlInt	AbsoluteToJulianDate(IlInt absDate);

    friend class IliTime;
};

#endif
