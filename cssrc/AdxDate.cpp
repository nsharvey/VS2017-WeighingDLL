// AdxDate.cpp
// -----------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <Shlwapi.h>


#include "AdxDate.h"


int isLeapYear(int year) {
  int res = 0;
  if ((year % 4) == 0) 
    if ((year % 100) == 0) 
      if ((year % 400) == 0) 
        res = 1;
      else
        res = 0;
    else  
      res = 1;
  else
    res = 0;
  return res;
}

static int monthLengths[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int monthLength(int mo, int ye) {
  if (mo == 2)
    return (monthLengths[mo-1] + isLeapYear(ye));
  else
    return (monthLengths[mo-1]);
}

void numberToDate(int nb, int ye, int* d, int* mo) {
  int cont=1;
  int i,ml;
  for (i=1; (i<13) && cont; i++) {
    ml = monthLength(i,ye);
    if (nb >= ml) {
      nb -= ml;
    } else {
      *mo = i;
      *d = nb;
      cont = 0;
    }
  }
}



// An explanation of the calculation can be found in PascAlgorithms by
// Edward and Ruth Reingold, Scott-Foresman/Little, Brown, 1988.

int yearDayNumber(int day, int month, int year)
{
  // Return the day number within the year of the date DATE.
  // For example, day-number(1, 1, 1987) returns the value 1,
  // while day-number(12, 31, 1980) returns 366.

  int dayOfYear = day + (31 * (month - 1));
  if (month > 2)
    {
      dayOfYear = dayOfYear-((23 + (4 * month)) / 10);
      if (isLeapYear(year))
	  dayOfYear++;
    }
  return dayOfYear;
}

AdxDate::AdxDate() :
	_absolute (0),
	_hour (0.0),
	_day (0),
	_month (0),
	_year (0),
	_daysInYear (0)
{
	_string = new char[40];
	_temp = new char[20];
}

AdxDate::AdxDate( const AdxDate& date) :
	_absolute			(date._absolute),
	_hour				(date._hour),
	_day				(date._day),
	_month				(date._month),
	_year				(date._year),
	_daysInYear			(date._daysInYear)
{
	_string = new char[40];
	_temp = new char[20];
}

AdxDate::AdxDate( const AdxDate* date) :
	_absolute			(date->_absolute),
	_hour				(date->_hour),
	_day				(date->_day),
	_month				(date->_month),
	_year				(date->_year),
	_daysInYear			(date->_daysInYear)
{
	_string = new char[40];
	_temp = new char[20];
}

AdxDate::AdxDate(double hour, int day, int month, int year) {
	_hour = hour;
	_day = day;
	_month = month;
	_year = year;
  // Ilog Consulting
	updateAbsolute();
/*  int priorYears = year - 1;
	_daysInYear = yearDayNumber(day, month, year);
	 _absolute = (_daysInYear
	  + (365 * priorYears)   // + Days in prior years
	  + (priorYears / 4)     // + Julian leap years
	  - (priorYears / 100)   // - century years
	  + (priorYears / 400)	 // + Gregorian leap years
		+ (hour/24.0));
*/
    // End of Ilog Consulting
//	_string = new char[];
	_string = new char[40];
	_temp = new char[20];
}

AdxDate::AdxDate(double date)
{
    setAbsolute(date);
//  _string = new char[];
	_string = new char[40];
	_temp = new char[20];
}

AdxDate::~AdxDate()
{
	if( _string != NULL)
		delete [] _string;
	if( _temp != NULL)
		delete  [] _temp;
}

void AdxDate::setAbsolute(double date)
  // Compute the year day number corresponding to the absolute DATE.
  // The absolute date is the number of days elapsed since the (imaginary)
  // Gregorian date Sunday, December 31, 1 BC."
  // See the footnote on page 384 of ``Calendrical Calculations, Part II:
  // Three Historical Calendars'' by E. M. Reingold,  N. Dershowitz, and 
  // S. M. Clamen, Software--Practice and Experience, Volume 23, Number 4
  // (April, 1993), pages 383-404 for an explanation.

{
  _absolute = date;
  long ndate = static_cast<long>(floor( date));
  _hour = (date - ndate) * 24.0;

  int d0 = ndate - 1;
  int n400 = d0 / 146097;
  int d1 = d0 % 146097;
  int n100 =  d1 / 36524;
  int d2 = d1 % 36524;
  int n4 = d2 / 1461;
  int d3 = d2 % 1461;
  int n1 = d3 / 365;
  int day = 1 + (d3 % 365);
  int year= (400 * n400) + (100 * n100)+(n4* 4) + n1;
  _year = year;
  if ((n100 == 4) || (n1 == 4)) {
    _day = 31;
    _month = 12;
    _daysInYear = yearDayNumber(31, 12, year);
  } else {
    year = 1 + year;
    int month = 1;
    int mdays=monthLength(month, year);
    while ((mdays < day) && (day = day - mdays)) {
      month++;
      mdays=monthLength(month, year);
    }
    _year = year;
    _month = month;
    _day = day;
    _daysInYear = yearDayNumber(day, month, year);
  }
}

// Ilog Consulting
void AdxDate::updateAbsolute()
{
  int priorYears = _year - 1;
  _daysInYear = yearDayNumber(_day, _month, _year);
  _absolute = (_daysInYear
	       + (365 * priorYears)   // + Days in prior years
	       + (priorYears / 4)     // + Julian leap years
	       - (priorYears / 100)   // - century years
	       + (priorYears / 400)	 // + Gregorian leap years
	       + (_hour/24.0));
}
// end of Ilog Consulting

AdxDate::AdxDate( const char* strDate,
									 DateFormat format,
									 const char separator) :
	_hour (0.0)
{
	size_t yOffset = 0, mOffset = 4, dOffset = 6;
	char ybuf[4], mbuf[2], dbuf[2];

	switch (format) {
		case YYYYMMDD:
			yOffset = 0;
			mOffset = 4;
			dOffset = 6;
			break;
		case DDMMYYYY:
			yOffset = 4;
			dOffset = 0;
			mOffset = 2;
			break;
		case MMDDYYYY:
			yOffset = 4;
			dOffset = 2;
			mOffset = 0;
			break;
		default:
			break;
	}
	if( separator != 0) {
		if( yOffset != 0)
			++yOffset;
		if( mOffset != 0)
			++mOffset;
		if( dOffset != 0)
			++dOffset;
	}

	strncpy( ybuf, strDate + yOffset, 4);
	_year = atol( ybuf);

	strncpy( mbuf, strDate + mOffset, 2);
	_month = atol( mbuf);

	strncpy( dbuf, strDate + dOffset, 2);
	_day = atol( dbuf);

	int priorYears = _year - 1;
	_daysInYear = yearDayNumber(_day, _month, _year);
	_absolute = static_cast<double>(_daysInYear
		+ (365 * priorYears)   // + Days in prior years
		+ (priorYears / 4)     // + Julian leap years
		- (priorYears / 100)   // - century years
		+ (priorYears / 400)); // + Gregorian leap years
	_string = new char[40];
	_temp = new char[20];
}

ostream& operator<<( ostream& os, const AdxDate& date) {
	date.display( os);
	return os;
}

void AdxDate::display( ostream& os) const {
	const char* const  SEP = "";

	os<<getYear()		<<SEP;
	if( getMonth() < 10) {
		os<<"0"<<getMonth()<<SEP;
	} else {
		os<<getMonth()<<SEP;
	}
	if( getDay() < 10) {
		os<<"0"<<getDay()<<flush;
	} else {
		os<<getDay()<<flush;
	}
}

// Ilog Consulting
// Comparaison de dates
int  AdxDate::operator == (const AdxDate& o) const
{
  return (_hour == o._hour &&
	  _day == o._day &&
	  _month == o._month &&
	  _year == o._year);
}

int AdxDate::operator < (const AdxDate& o) const
{
  unsigned long d1 = ((_year << 9) 
		      | (_month << 5) 
		      | _day);
  unsigned long d2 = ((o._year << 9) 
		      | (o._month << 5) 
		      | o._day);
  
  if (d1 < d2) return 1;
  else if (d1 > d2) return 0;
  else
    return (_hour < o._hour);
}

int AdxDate::operator <= (const AdxDate& o) const
{
  unsigned long d1 = ((_year << 9) 
		      | (_month << 5) 
		      | _day);
  unsigned long d2 = ((o._year << 9) 
		      | (o._month << 5) 
		      | o._day);
  
  if (d1 < d2) return 1;
  else if (d1 > d2) return 0;
  else
    return (_hour <= o._hour);
}

int AdxDate::operator > (const AdxDate& o) const {
  return ! operator <= (o);
}

// Retourne le numero du jour dans la semaine
int AdxDate::getWeekDay() const
{
  return ((int)getAbsolute()) % 7 + 1;
}

// Retourne le nombre de jours dans le mois
int AdxDate::getMonthDaysCount () const {
  static int daysCountByMonth[] = 
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if (_month == 2 && isLeapYear(_year))
    return 29;
  else
    return daysCountByMonth[(int)_month - 1];
}

// Ilog Consulting 04/01/2000
void AdxDate::fillFirstJanuary(struct tm* firstJan) const
{
  firstJan->tm_mday = 1;
  firstJan->tm_mon = 0;
  firstJan->tm_year = _year - 1900;   // change 1999 to _year
  firstJan->tm_hour = 0;   // change 5 to 0
  firstJan->tm_min = 0;
  firstJan->tm_sec = 1;
  firstJan->tm_isdst = -1;
}

// End Ilog Consulting 04/01/2000void
void AdxDate::convertDate(struct tm* date) const
{
  date->tm_mday = _day;
  date->tm_mon = _month-1;
  date->tm_year = _year - 1900;
  date->tm_hour = _hour * 100;
  date->tm_min = 0;
  date->tm_sec = 1;
  date->tm_isdst = -1;
}

int AdxDate::getWeekNumber() const
{
  struct tm reference, theDate;
  time_t result;
  int nbweek=-1;
  
  fillFirstJanuary(&reference);
  convertDate(&theDate);
  result = mktime(&theDate);
  if (result != -1) {
    result = mktime(&reference);
    if ((time_t)result != -1) {
      int mday = reference.tm_wday;
      // numero du jour de la presente date dans l'annee
      int yday = theDate.tm_yday+1;
      // Y-a-t-il au moins un jour ouvrable dans la semaine du 1er/01
      int jOuvrable = (mday >= 1 && mday <= 4);
      if (!jOuvrable) {
	// Trouver la date du 1er lundi
	if (mday == 0) // 1er janvier est un dimanche
	  // le 1er lundi est donc 1 jour apres le 1er janvier
	  reference.tm_mday += 1;
	else // 1er janvier est un vendredi ou samedi
	  // le 1er lundi est donc (7 - mday) + 1 jours apres le 1er janvier
	  reference.tm_mday += (7 - mday) + 1;
	// mktime remet a jour la structure avec la date correcte du jour
	result = mktime(&reference);
	if (result != (time_t)-1) {
	  // premier lundi de janvier
	  int firstMonday = reference.tm_mday;
	  // Ilog Consulting 04/01/2000 Correction
	  // Si la date courante est anterieure au 1er lundi de janvier,
	  // alors le numero de semaine de la date courante est le meme que
	  // celui du dernier jour de la precedente annee.
	  AdxDate AdxFirstMonday(0.0, firstMonday, 1, _year);
	  if (*this < AdxFirstMonday) {
	    AdxDate* lastYearDate = new AdxDate(0.0, 31, 12, _year-1);
	    nbweek = lastYearDate->getWeekNumber();
	    delete lastYearDate;
	  }
	  else
	    nbweek = ((yday - firstMonday) / 7) + 1;
	  // End of Ilog Consulting 04/01/2000 Correction
	}
      }
      else { // il existe au moins un jour ouvrable dans l'annee
	// date du 2eme lundi de janvier?
	int diff = 7 - mday + 1;
	// On ajoute le nb de jours necessaires pour arriver au lundi suivant
	reference.tm_mday += diff;
	// mktime remet a jour la structure avec la date correcte du jour
	result = mktime(&reference);
	if (result != (time_t)-1) {
	  int secondMonday = reference.tm_mday;
	  diff = 7 - secondMonday;
	  nbweek = ((yday + diff) / 7) + 1;	
	}
      }
    }
  }
  return nbweek;
}

void AdxDate::nextDay(AdxDate& theDate) const
{
  struct tm date;
  time_t result;
  date.tm_mday = _day;
  date.tm_mon = _month-1;
  date.tm_year = _year - 1900;
  date.tm_hour = _hour * 100;
  date.tm_min = 0;
  date.tm_sec = 1;
  date.tm_isdst = -1;
  result = mktime(&date);
  if (result != -1) {
    date.tm_mday += 1;
    result = mktime(&date);
    if (result != -1) {
      theDate._day = date.tm_mday;
      theDate._month = date.tm_mon + 1;
      theDate._year = date.tm_year + 1900;
      theDate.updateAbsolute();
    }
  }
}

// Ilog Consulting 04/01/2000 Correction
void AdxDate::addNbDays(int nbDays, AdxDate& theDate) const
{
  struct tm date;
  time_t result;
  date.tm_mday = _day;
  date.tm_mon = _month-1;
  date.tm_year = _year - 1900;
  date.tm_hour = _hour * 100;
  date.tm_min = 0;
  date.tm_sec = 1;
  date.tm_isdst = -1;
  date.tm_mday += nbDays;
  result = mktime(&date);
  if (result != -1) {
    theDate._day = date.tm_mday;
    theDate._month = date.tm_mon + 1;
    theDate._year = date.tm_year + 1900;
    theDate.updateAbsolute();
  }
}

char* AdxDate::dateToChar(IlvDateField::IlvDateFieldFormat first,IlvDateField::IlvDateFieldFormat middle,
						 IlvDateField::IlvDateFieldFormat last,char separator){
/*	if( _temp == NULL) 
		_temp = new char[20];
	if( _string == NULL) 
		_string = new char[40];*/
    CString separ;
	separ+=separator;
// creation des 2 premiers caracteres
	if (first == IlvDateField::IlvDateFieldFormat::df_day || 
		first == IlvDateField::IlvDateFieldFormat::df_Day)
	{
		if (getDay() < 10 && first == IlvDateField::IlvDateFieldFormat::df_Day)
		{
			itoa(0,_string,10);
			itoa(getDay(),_temp,10);
			strcat(_string,_temp);
		}
		else
		{
			itoa(getDay(),_string,10);
		}
	}
	if (first == IlvDateField::IlvDateFieldFormat::df_month   ||
		first == IlvDateField::IlvDateFieldFormat::df_Month)
	{
		if (getMonth() < 10 && first == IlvDateField::IlvDateFieldFormat::df_Month)
		{
			itoa(0,_string,10);
			itoa(getMonth(),_temp,10);
			strcat(_string,_temp);
		}
		else
			itoa(getMonth(),_string,10);
	}
	if (first == IlvDateField::IlvDateFieldFormat::df_year   ||
		first == IlvDateField::IlvDateFieldFormat::df_Year)
	{
		if (IlvDateField::IlvDateFieldFormat::df_year)
		{
			itoa(getYear(),_string,10);
			if (StrTrim(_string,"19"))
				if (strlen(_string) == 0)
					strcpy(_string,"19");
			else
			{
				StrTrim(_string,"20");
				if (strlen(_string) == 0)
					strcpy(_string,"20");
			}
		}
		else
			itoa(getYear(),_string,10);
	}
	strcat(_string,separ);
// creation des 2  caracteres suivants
	if (middle == IlvDateField::IlvDateFieldFormat::df_day ||
		middle == IlvDateField::IlvDateFieldFormat::df_Day)
	{
		if (getDay() < 10 && middle == IlvDateField::IlvDateFieldFormat::df_Day)
		{
			itoa(0,_temp,10);
			strcat(_string,_temp);
			itoa(getDay(),_temp,10);
			strcat(_string,_temp);
		}
		else
		{
			itoa(getDay(),_temp,10);
			strcat(_string,_temp);
		}
	}
	if (middle == IlvDateField::IlvDateFieldFormat::df_month   ||
		middle == IlvDateField::IlvDateFieldFormat::df_Month)
	{
		if (getMonth() < 10 && middle == IlvDateField::IlvDateFieldFormat::df_Month)
		{
			itoa(0,_temp,10);
			strcat(_string,_temp);
			itoa(getMonth(),_temp,10);
			strcat(_string,_temp);
		}
		else
		{
			itoa(getMonth(),_temp,10);
			strcat(_string,_temp);
		}
	}
	if (middle == IlvDateField::IlvDateFieldFormat::df_year   ||
		middle == IlvDateField::IlvDateFieldFormat::df_Year)
	{
		if (middle == IlvDateField::IlvDateFieldFormat::df_year)
		{
			itoa(getYear(),_temp,10);
			if (StrTrim(_temp,"19"))
				if (strlen(_temp) == 0)
					strcpy(_temp,"19");
			else
			{
				StrTrim(_temp,"20");
				if (strlen(_temp) == 0)
					strcpy(_temp,"20");
			}
		}
		else
			itoa(getYear(),_temp,10);
		strcat(_string,_temp);
	}
	strcat(_string,separ);
// creation des 2  caracteres suivants
	if (last == IlvDateField::IlvDateFieldFormat::df_day ||
		last == IlvDateField::IlvDateFieldFormat::df_Day)
	{
		if (getDay() < 10 && last == IlvDateField::IlvDateFieldFormat::df_Day)
		{
			itoa(0,_temp,10);
			strcat(_string,_temp);
			itoa(getDay(),_temp,10);
			strcat(_string,_temp);
		}
		else
		{
			itoa(getDay(),_temp,10);
			strcat(_string,_temp);
		}
	}
	if (last == IlvDateField::IlvDateFieldFormat::df_month   ||
		last == IlvDateField::IlvDateFieldFormat::df_Month)
	{
		if (getMonth() < 10 && middle == IlvDateField::IlvDateFieldFormat::df_Month)
		{
			itoa(0,_temp,10);
			strcat(_string,_temp);
			itoa(getMonth(),_temp,10);
			strcat(_string,_temp);
		}
		else
		{
			itoa(getMonth(),_temp,10);
			strcat(_string,_temp);
		}
	}
	if (last == IlvDateField::IlvDateFieldFormat::df_year   ||
		last == IlvDateField::IlvDateFieldFormat::df_Year)
	{
		if (last == IlvDateField::IlvDateFieldFormat::df_year)
		{
			itoa(getYear(),_temp,10);
			if (StrTrim(_temp,"19"))
				if (strlen(_temp) == 0)
					strcpy(_temp,"19");
			else
			{
				StrTrim(_temp,"20");
				if (strlen(_temp) == 0)
					strcpy(_temp,"20");
			}
		}
		else
			itoa(getYear(),_temp,10);
		strcat(_string,_temp);
	}
//	delete [] _temp;
	return _string;
}

// End of Ilog Consulting 04/01/2000 End of Correction
// End of Ilog Consulting
