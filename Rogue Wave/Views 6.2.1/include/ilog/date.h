// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/date.h
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
// Declaration of the IlDate class
// --------------------------------------------------------------------------
#ifndef __Il_Date_H
#define __Il_Date_H

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif
#if !defined(__Il_Calendar_H)
#  include <ilog/calendar.h>
#endif

#ifdef IL_STD
#include <ctime>
#include <iostream>
#else
#include <time.h>
#include <iostream.h>
#endif

class IlTimeUnit;
class IlGregorianCalendar;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlPredefinedUnits
{
public:
    IlPredefinedUnits();

    IlTimeUnit*		getNextUnit();
    inline IlTimeUnit*		operator[](IlUInt i)
	{ return _units[i]; }
    static inline unsigned int	nbUnits()
	{ return _nbUnits; }
    inline void		reset()
	{ _currentUnitIdx = 0; }
protected:
    IlUInt		_currentUnitIdx;
    IlTimeUnit**	_units;
    static const IlUInt	_nbUnits;
private:
    IlPredefinedUnits(const IlPredefinedUnits&); // No copy constructor
};


class IlCalendar;
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnit
{
public:
    IlTimeUnit();
    virtual ~IlTimeUnit() {}

    virtual void	snapToPreviousTimeUnit(IlCalendar& date) const = 0;
    virtual void	addTimeUnit(IlCalendar& date) const = 0;
    virtual IlDouble	getMillis() const = 0;
    virtual char*	toString(IlDouble date) const = 0;
    virtual IlTimeUnit*	copy() const = 0;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitMilliSecond : public IlTimeUnit
{
public:
    IlTimeUnitMilliSecond();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitSecond : public IlTimeUnit
{
public:
    IlTimeUnitSecond();

    virtual void	snapToPreviousTimeUnit(IlCalendar& date) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitMinute : public IlTimeUnit
{
public:
    IlTimeUnitMinute();

    virtual void	snapToPreviousTimeUnit(IlCalendar& date) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitHour : public IlTimeUnit
{
public:
    IlTimeUnitHour();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitDay : public IlTimeUnit
{
public:
    IlTimeUnitDay();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitWeek : public IlTimeUnit
{
public:
    IlTimeUnitWeek();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitMonth : public IlTimeUnit
{
public:
    IlTimeUnitMonth();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitQuarter : public IlTimeUnit
{
public:
    IlTimeUnitQuarter();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlTimeUnitYear : public IlTimeUnit
{
public:
    IlTimeUnitYear();

    virtual void	snapToPreviousTimeUnit(IlCalendar& cal) const;
    virtual void	addTimeUnit(IlCalendar& date) const;
    virtual IlDouble	getMillis() const;
    virtual char*	toString(IlDate date) const;
    virtual IlTimeUnit*	copy() const;
};

#endif /* !__Il_Date_H */
