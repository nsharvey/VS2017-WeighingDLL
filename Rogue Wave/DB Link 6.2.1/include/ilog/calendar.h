// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/calendar.h
// --------------------------------------------------------------------------
/*
*****************************************************************************
*   Copyright (C) 1997-1999, International Business Machines
*   Corporation and others.  All Rights Reserved.
*****************************************************************************
*
* File CALENDAR.H
*
* Modification History:
*
*   Date        Name        Description
*   04/22/97    aliu        Expanded and corrected comments and other header
*                           contents.
*   05/01/97    aliu        Made equals(), before(), after() arguments const.
*   05/20/97    aliu        Replaced fAreFieldsSet with fAreFieldsInSync and
*                           fAreAllFieldsSet.
*   07/27/98    stephen     Sync up with JDK 1.2
*   11/15/99    weiv        added YEAR_WOY and DOW_LOCAL
*                           to IlDateFields
*****************************************************************************
*/

#ifndef __Il_Calendar_H
#define __Il_Calendar_H

class IlLocale;

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif
#if !defined(__Il_String_H)
#  include <ilog/string.h>
#endif

typedef IlDouble IlDate;


enum IlDateErrorCode {
    IL_DATE_ERROR_INFO_START        = -128,
    IL_DATE_USING_FALLBACK_ERROR    = -128,
    IL_DATE_USING_DEFAULT_ERROR     = -127,
    IL_DATE_SAFECLONE_ALLOCATED_ERROR = -126,
    IL_DATE_ERROR_INFO_LIMIT,
    IL_DATE_ZERO_ERROR              =  0,
    IL_DATE_ILLEGAL_ARGUMENT_ERROR  =  1,
    IL_DATE_MISSING_RESOURCE_ERROR  =  2,
    IL_DATE_INVALID_FORMAT_ERROR    =  3,
    IL_DATE_FILE_ACCESS_ERROR       =  4,
    IL_DATE_INTERNAL_PROGRAM_ERROR  =  5,
    IL_DATE_MESSAGE_PARSE_ERROR     =  6,
    IL_DATE_MEMORY_ALLOCATION_ERROR =  7,
    IL_DATE_INDEX_OUTOFBOUNDS_ERROR =  8,
    IL_DATE_PARSE_ERROR             =  9,
    IL_DATE_INVALID_CHAR_FOUND      = 10,
    IL_DATE_TRUNCATED_CHAR_FOUND    = 11,
    IL_DATE_ILLEGAL_CHAR_FOUND      = 12,
    IL_DATE_INVALID_TABLE_FORMAT    = 13,
    IL_DATE_INVALID_TABLE_FILE      = 14,
    IL_DATE_BUFFER_OVERFLOW_ERROR   = 15,
    IL_DATE_UNSUPPORTED_ERROR       = 16,
    IL_DATE_RESOURCE_TYPE_MISMATCH  = 17,
    IL_DATE_ILLEGAL_ESCAPE_SEQUENCE = 18,
    IL_DATE_UNSUPPORTED_ESCAPE_SEQUENCE = 19,
    IL_DATE_NO_SPACE_AVAILABLE      = 20,
    IL_DATE_ERROR_LIMIT
};

#define IL_DATE_FAILURE(x) ((x)>IL_DATE_ZERO_ERROR)

#define IL_DATE_SUCCESS(x) ((x)<=IL_DATE_ZERO_ERROR)

#define IL_DATE_MILLIS_PER_SECOND        (1000)

#define IL_DATE_MILLIS_PER_MINUTE       (60000)

#define IL_DATE_MILLIS_PER_HOUR       (3600000)

#define IL_DATE_MILLIS_PER_DAY       (86400000)


class ILOG_EXPORTED IlTimeZone
{
public:
    enum TimeMode {
        WALL_TIME = 0,
        STANDARD_TIME,
        UTC_TIME
    };

    enum EMode
    {
        DOM_MODE = 1,
        DOW_IN_MONTH_MODE,
        DOW_GE_DOM_MODE,
        DOW_LE_DOM_MODE
    };



    IlTimeZone();
    IlTimeZone*		clone() const;
    IlBoolean		operator==(const IlTimeZone&) const;
    IlInt		getRawOffset() const;
    IlBoolean		useDaylightTime() const;

    IlInt		getOffset(IlUChar era,
				  IlInt year,
				  IlInt month,
				  IlInt day,
				  IlUChar dayOfWeek,
				  IlInt millis,
				  IlInt monthLength,
				  IlDateErrorCode& status) const;

    IlInt		getOffset(IlUChar era,
				  IlInt year,
				  IlInt month,
				  IlInt day,
				  IlUChar dayOfWeek,
				  IlInt milliseconds,
				  IlInt monthLength,
				  IlInt prevMonthLength,
				  IlDateErrorCode& status) const;

    IlInt		compareToRule(char month,
				      char monthLen,
				      char prevMonthLen,
				      char dayOfMonth,
				      char dayOfWeek,
				      IlInt millis,
				      IlInt millisDelta,
				      EMode ruleMode,
				      char ruleMonth,
				      char ruleDayOfWeek,
				      char ruleDay,
				      IlInt ruleMillis) const;

    static IlTimeZone*	createDefault();

protected:

    // the month, day, DOW, and time DST starts
    char		_startMonth, _startDay, _startDayOfWeek;
    IlInt		_startTime;

    // Mode for startTime, endTime; see TimeMode
    TimeMode		_startTimeMode, _endTimeMode;

    // the month, day, DOW, and time DST ends
    char		_endMonth, _endDay, _endDayOfWeek;
    IlInt		_endTime;

    IlInt		_startYear;   // the year these DST rules took effect
    IlInt		_rawOffset;   // the IlTimeZone raw GMT offset
    IlBoolean		_useDaylight; // uses DST or not
    static const char	staticMonthLength[12]; // lengths of the months

    // flags indicating what kind of rules the DST rules are
    EMode		_startMode, _endMode;

    IlInt		_dstSavings;
};


class ILOG_EXPORTED IlCalendar
{
public:

#if defined(ERA)
/* ERA conflicts with XPG4 macro (cf AIX 5.1 /usr/include/langinfo.h) */
#define IL_TMP_ERA ERA
#undef ERA
#endif

    enum IlDateFields {
        ERA,
        YEAR,
        MONTH,
        WEEK_OF_YEAR,
        WEEK_OF_MONTH,
        DATE,
        DAY_OF_YEAR,
        DAY_OF_WEEK,
        DAY_OF_WEEK_IN_MONTH,
        AM_PM,
        HOUR,
        HOUR_OF_DAY,
        MINUTE,
        SECOND,
        MILLISECOND,
        ZONE_OFFSET,
        DST_OFFSET,
	// here will go names for 'Y' and 'e'
        YEAR_WOY,  // 'Y' Example: 1..big number
        DOW_LOCAL, // 'e' Example: 1..7
        FIELD_COUNT,

        DAY_OF_MONTH = DATE   // Synonyms
    };

#if defined(IL_TMP_ERA)
/* ERA conflicts with XPG4 macro (cf AIX 5.1 /usr/include/langinfo.h) */
#define ERA IL_TMP_ERA
#endif

    enum EDaysOfWeek {
        SUNDAY = 1,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    };

    enum EMonths {
        JANUARY,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER,
        UNDECIMBER
    };

    enum EAmpm {
        AM,
        PM
    };

    virtual ~IlCalendar();

    virtual IlCalendar*	clone() const = 0;
    static IlCalendar*	createInstance(IlDateErrorCode& success);
    static IlCalendar*	createInstance(IlTimeZone* zoneToAdopt,
				       IlDateErrorCode& success);
    static IlCalendar*	createInstance(const IlTimeZone& zone,
				       IlDateErrorCode& success);

    static IlCalendar*	createInstance(const IlLocale& aLocale,
				       IlDateErrorCode& success);
    static IlCalendar*	createInstance(IlTimeZone* zoneToAdopt,
				       const IlLocale& aLocale,
				       IlDateErrorCode& success);
    static IlCalendar*	createInstance(const IlTimeZone& zoneToAdopt,
				       const IlLocale& aLocale,
				       IlDateErrorCode& success);
    static IlDate	getNow();
    inline IlDate	getTime(IlDateErrorCode& status) const
	{ return getTimeInMillis(status); }
    inline void		setTime(IlDate date, IlDateErrorCode& status)
	{ setTimeInMillis(date, status); }
    virtual IlBoolean	operator==(const IlCalendar& that) const;
    inline IlBoolean	operator!=(const IlCalendar& that) const
	{ return !operator==(that); }
    IlBoolean		equals(const IlCalendar& when,
			       IlDateErrorCode& status) const;
    IlBoolean		before(const IlCalendar& when,
			       IlDateErrorCode& status) const;
    IlBoolean		after(const IlCalendar& when,
			      IlDateErrorCode& status) const;
    virtual IlBoolean	equivalentTo(const IlCalendar& other) const;
    virtual void	add(IlDateFields field,
			    IlInt amount,
			    IlDateErrorCode& status) = 0;
    inline void		roll(IlDateFields field,
			     IlBoolean up,
			     IlDateErrorCode& status)
	{ roll(field, (IlInt)(up ? +1 : -1), status); }
    virtual void	roll(IlDateFields field,
			     IlInt amount,
			     IlDateErrorCode& status) = 0;
    virtual IlInt	fieldDifference(IlDate when,
					IlDateFields field,
					IlDateErrorCode& status);
    void		adoptTimeZone(IlTimeZone* value);
    void		setTimeZone(const IlTimeZone& zone);
    const IlTimeZone&	getTimeZone() const;
    IlTimeZone*		orphanTimeZone();
    virtual IlBoolean	inDaylightTime(IlDateErrorCode& status) const = 0;
    void		setLenient(IlBoolean lenient);
    IlBoolean		isLenient() const;
    void		setFirstDayOfWeek(EDaysOfWeek value);
    EDaysOfWeek		getFirstDayOfWeek() const;
    void		setMinimalDaysInFirstWeek(IlUChar value);
    IlUChar		getMinimalDaysInFirstWeek() const;

    virtual IlInt	getMinimum(IlDateFields field) const = 0;

    virtual IlInt	getMaximum(IlDateFields field) const = 0;

    virtual IlInt	getGreatestMinimum(IlDateFields field) const = 0;

    virtual IlInt	getLeastMaximum(IlDateFields field) const = 0;

    IlInt		getActualMinimum(IlDateFields field,
					 IlDateErrorCode& status) const;

    IlInt		getActualMaximum(IlDateFields field,
					 IlDateErrorCode& status) const;

    IlInt		get(IlDateFields field,
			    IlDateErrorCode& status) const;

    IlBoolean		isSet(IlDateFields field) const;

    void		set(IlDateFields field, IlInt value);

    void		set(IlInt year, IlInt month, IlInt date);

    void		set(IlInt year,
			    IlInt month,
			    IlInt date,
			    IlInt hour,
			    IlInt minute);

    void		set(IlInt year,
			    IlInt month,
			    IlInt date,
			    IlInt hour,
			    IlInt minute,
			    IlInt second);

    IlDate		set(const char* date,
			    IlDateErrorCode& status);

    void		clear();

    void		clear(IlDateFields field);

protected:
    IlCalendar(IlDateErrorCode& success);
    IlCalendar(const IlCalendar& source);
    IlCalendar(IlTimeZone*      zone,
	       const IlLocale&  locale,
	       IlDateErrorCode& success);
    IlCalendar(const IlTimeZone& zone,
	       const IlLocale&   locale,
               IlDateErrorCode&  success);

    IlCalendar&		operator=(const IlCalendar& right);
    virtual void	computeTime(IlDateErrorCode& status) = 0;
    virtual void	computeFields(IlDateErrorCode& status) = 0;
    double		getTimeInMillis(IlDateErrorCode& status) const;
    void		setTimeInMillis(double millis,
					IlDateErrorCode& status);
    void		complete(IlDateErrorCode& status);
    inline IlInt	internalGet(IlDateFields field) const
	{ return fFields[field]; }

    inline void		internalSet(IlDateFields field, IlInt value)
	{ fFields[field] = value; }

protected:
    IlBoolean		fIsTimeSet;
    IlBoolean		fAreFieldsSet;
    IlBoolean		fAreAllFieldsSet;
    inline IlDate	internalGetTime() const { return fTime; }
    inline void		internalSetTime(IlDate time) { fTime = time; }
    IlInt		fFields[FIELD_COUNT];
    IlBoolean		fIsSet[FIELD_COUNT];
    // Special values of stamp[]
    enum {
        kUnset                 = 0,
        kInternallySet,
        kMinimumUserStamp
    };
    IlInt		fStamp[FIELD_COUNT];
private:
    // The next available value for stamp[]
    IlInt		fNextStamp;// = kMinimumUserStamp;
    // Current time set for the calendar.
    IlDate		fTime;
    // See setLenient()
    IlBoolean		fLenient;
    /*
     * Time zone affects the time calculation done by
     * IlCalendar. IlCalendar subclasses use the time zone data to
     * produce the local time.
     */
    IlTimeZone*		fZone;
    /*
     * Both firstDayOfWeek and minimalDaysInFirstWeek are
     * locale-dependent. They are used to figure out the week count
     * for a specific date for a given locale. These must be set when
     * a IlCalendar is constructed. For example, in US locale,
     * firstDayOfWeek is SUNDAY;
     * minimalDaysInFirstWeek is 1. They are used to figure out the
     * week count for a specific date for a given locale.
     * These must be set when a IlCalendar is constructed.
     */
    EDaysOfWeek		fFirstDayOfWeek;
    IlUChar		fMinimalDaysInFirstWeek;
    void		setWeekCountData(const IlLocale& desiredLocale,
					 IlDateErrorCode& success);
    void		updateTime(IlDateErrorCode& status);
    static IlInt	stringToDayNumber(const IlString& string,
					  IlDateErrorCode& status);
    static const char*	kDateTimeElements;
};

// -------------------------------------

#endif /* __Il_Calendar_H */
