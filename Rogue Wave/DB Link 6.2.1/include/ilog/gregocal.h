// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/gregocal.h
// --------------------------------------------------------------------------
/*
******************************************************************************
* Copyright (C) {1997-1999}, International Business Machines Corporation
* and others. All Rights Reserved.
******************************************************************************
*
* File GREGOCAL.H
*
* Modification History:
*
*   Date        Name        Description
*   04/22/97    aliu        Overhauled header.
*    07/28/98    stephen        Sync with JDK 1.2
*    09/04/98    stephen        Re-sync with JDK 8/31 putback
*    09/14/98    stephen        Changed type of kOneDay, kOneWeek to double.
*                            Fixed bug in roll()
*   10/15/99    aliu        Fixed j31, incorrect WEEK_OF_YEAR computation.
*                           Added documentation of WEEK_OF_YEAR computation.
*   10/15/99    aliu        Fixed j32, cannot set date to Feb 29 2000 AD.
*                           {JDK bug 4210209 4209272}
******************************************************************************
*/

#ifndef __Il_Gregocal_H
#define __Il_Gregocal_H

#ifndef __Il_Calendar_H
#include <ilog/calendar.h>
#endif /* !__Il_Calendar_H */

#ifdef IL_STD
#include <cmath>
#else
#include <math.h>
#endif

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlGregorianCalendar : public IlCalendar
{
public:

    enum EEras {
        BC,
        AD
    };

    IlGregorianCalendar(IlDateErrorCode& success);

    IlGregorianCalendar(IlTimeZone* zoneToAdopt, IlDateErrorCode& success);

    IlGregorianCalendar(const IlTimeZone& zone, IlDateErrorCode& success);

    IlGregorianCalendar(const IlLocale& aLocale, IlDateErrorCode& success);

    IlGregorianCalendar(IlTimeZone*		zoneToAdopt,
			const IlLocale&		aLocale,
                        IlDateErrorCode&	success);

    IlGregorianCalendar(const IlTimeZone&	zone,
			const IlLocale&		aLocale,
			IlDateErrorCode&	success);

    IlGregorianCalendar(IlInt			year,
			IlInt			month,
			IlInt			date,
			IlDateErrorCode&	success);

    IlGregorianCalendar(IlInt			year,
			IlInt			month,
			IlInt			date,
			IlInt			hour,
			IlInt			minute,
			IlDateErrorCode&	success);

    IlGregorianCalendar(IlInt			year,
			IlInt			month,
			IlInt			date,
			IlInt			hour,
			IlInt			minute,
			IlInt			second,
			IlDateErrorCode&	success);

    virtual ~IlGregorianCalendar();

    IlGregorianCalendar(const IlGregorianCalendar& source);

    IlGregorianCalendar& operator=(const IlGregorianCalendar& right);

    virtual IlCalendar*	clone(void) const;

    void		setGregorianChange(IlDate		date,
					   IlDateErrorCode&	success);

    IlDate		getGregorianChange(void) const;

    IlBoolean		isLeapYear(IlInt year) const;

    virtual IlBoolean	operator==(const IlCalendar& that) const;

    virtual IlBoolean	equivalentTo(const IlCalendar& other) const;

    virtual void	add(IlDateFields	field,
			    IlInt		amount,
			    IlDateErrorCode&	status);

    virtual void	roll(IlDateFields	field,
			     IlInt		amount,
			     IlDateErrorCode&	status);

    virtual IlInt	getMinimum(IlDateFields field) const;

    virtual IlInt	getMaximum(IlDateFields field) const;

    virtual IlInt	getGreatestMinimum(IlDateFields field) const;

    virtual IlInt	getLeastMaximum(IlDateFields field) const;

    IlInt		getActualMinimum(IlDateFields field) const;

    IlInt		getActualMaximum(IlDateFields field) const;

    virtual IlBoolean	inDaylightTime(IlDateErrorCode& status) const;

protected:

    virtual void	computeFields(IlDateErrorCode& status);

    virtual void	computeTime(IlDateErrorCode& status);

private:

    IlInt		internalGetEra() const;

    // this is 2^52 - 1, the largest allowable mantissa with
    // a 0 exponent in a 64-bit double.
    static const IlDate	EARLIEST_SUPPORTED_MILLIS;
    static const IlDate	LATEST_SUPPORTED_MILLIS;

    IlInt		monthLength(IlInt month) const;
    IlInt		monthLength(IlInt month, IlInt year) const;

    IlInt		yearLength(IlInt year) const;

    IlInt		yearLength(void) const;

    void		pinDayOfMonth(void);


    static double	computeJulianDayOfYear(IlBoolean	isGregorian,
					       IlInt		year,
					       IlBoolean&	isLeap);

    IlInt		computeRelativeDOW() const;
    IlInt		computeRelativeDOW(double julianDay) const;

    IlInt		computeDOYfromWOY(double julianDayOfYear) const;

    double		computeJulianDay(IlBoolean isGregorian, IlInt year);

    void		timeToFields(IlDate		theTime,
				     IlBoolean		quick,
				     IlDateErrorCode&	status);


    IlInt		weekNumber(IlInt date, IlInt day) const;

    IlBoolean		validateFields(void) const;

    IlBoolean		boundsCheck(IlInt value, IlDateFields field) const;

    // This is measured from the standard epoch, not in Julian Days.
    IlDate		fGregorianCutover;

    IlDate		fNormalizedGregorianCutover; // = gregorianCutover;

    IlInt		fGregorianCutoverYear;// = 1582;

    static char		fgClassID;

    static double	millisToJulianDay(IlDate millis);

    static IlDate	julianDayToMillis(double julian);

    static IlUChar	julianDayToDayOfWeek(double julian);

    static double	floorDivide(double numerator, double denominator);

    static IlInt	floorDivide(IlInt numerator, IlInt denominator);

    static IlInt	floorDivide(IlInt numerator,
				    IlInt denominator,
				    IlInt remainder[]);

    static IlInt	floorDivide(double	numerator,
				    IlInt	denominator,
				    IlInt	remainder[]);


    static const IlDate	kPapalCutover; // Cutover decreed by Pope Gregory

    static const IlInt	kJan1_1JulianDay; // January 1, year 1 (Gregorian)
    static const IlInt	kEpochStartAsJulianDay; // January 1, 1970 (Gregorian)
    static const IlInt	kEpochYear;

    static const IlInt	kNumDays [];
    static const IlInt	kLeapNumDays [];
    static const IlInt	kMonthLength [];
    static const IlInt	kLeapMonthLength [];

    static const IlInt	kMinValues [];
    static const IlInt	kLeastMaxValues [];
    static const IlInt	kMaxValues [];

    // Useful millisecond constants
    static const IlInt	kOneSecond;
    static const IlInt	kOneMinute;
    static const IlInt	kOneHour;
    static const double	kOneDay;
    static const double	kOneWeek;
};

// --------------------------------------------------------------------------
inline IlUChar
IlGregorianCalendar::julianDayToDayOfWeek(double julian)
{
    // If julian is negative, then julian%7 will be negative, so we adjust
    // accordingly.  We add 1 because Julian day 0 is Monday.
    signed char dayOfWeek = (signed char) fmod(julian + 1, 7);

    IlUChar result = IL_CAST(IlUChar,
			     dayOfWeek + ((dayOfWeek < 0)
					  ? (7 + SUNDAY)
					  : SUNDAY));
    return result;
}

#endif /* !__Il_Gregocal_H */
