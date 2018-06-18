// AdxDate.h
// ---------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#ifndef ADXDATE_H
#define ADXDATE_H

#include <iostream>
#include <time.h>
#include <ilviews/gadgets/datfield.h>

using std::ostream;
using std::flush;

enum DateFormat{
	YYYYMMDD,
	DDMMYYYY,
	MMDDYYYY};

/*enum IlvDateField::IlvDateFieldFormat{
	df_day,
	df_Day,
	df_month,
	df_Month,
	df_month_text,
	df_abbrev_month,
	df_year,
	df_Year
	};*/

//
// Defines an object that can transform
// a date (dd/mm/yyyy) into an integer
// so that you can compute durations in days
//

class AdxDate {

//----------------------------------------------------------
//	
// Properties
//
private:

  double _absolute;
  double _hour;
  int _day;
  int _month;
  int _year;
  int _daysInYear;
  char* _string; 
  char* _temp;

//----------------------------------------------------------
//	
// CTOR - DTOR
//
public:
  AdxDate(double hour, int day, int month, int year);
  AdxDate(double absolute);
  AdxDate( const char* strDate,
     		DateFormat format = YYYYMMDD,
			const char separator = '\000');
  AdxDate( const AdxDate& date);
  AdxDate( const AdxDate* date);
  ~AdxDate();

//private:
  AdxDate();

//----------------------------------------------------------
//	
// specific methods
//
public:

  virtual void display( ostream& os) const;

//----------------------------------------------------------
//	
// operators
//
public:

  friend ostream& operator<<( ostream& os, const AdxDate& date);

//----------------------------------------------------------
//	
// accessors & modifiers
//
public:

  double getAbsolute() const {
    return _absolute;
  }
	double getHour() const {
		return _hour;
	}
  int getDay() const {
    return _day;
  }
  int getMonth() const {
		return _month;
	}
  int getYear() const {
		return _year;
	} 
  int getDaysInYear() const {
		return _daysInYear;
	}
  void setAbsolute(double);

	// Ilog Consulting
	void updateAbsolute();
	int operator == (const AdxDate&) const;
	int operator < (const AdxDate&) const;
	int operator <= (const AdxDate&) const;
	int operator > (const AdxDate&) const;

	// Ilog Consulting:  Here I have modified the private state of these methods into public

//private:
  void setDay(int day) {
		_day = day;
	}
  void setMonth(int month) {
		_month = month;
	}
  void setYear(int year) {
		_year = year;
	}
	void setHour(double hour) {
		_hour = hour;
	}

	// Utilities	
	char* dateToChar(IlvDateField::IlvDateFieldFormat first,IlvDateField::IlvDateFieldFormat middle,
						 IlvDateField::IlvDateFieldFormat last,char separator);
	int getWeekDay() const;
	int getMonthDaysCount () const;
	int getWeekNumber() const;
    // Ilog Consulting 04/01/2000
    void fillFirstJanuary(struct tm* firstJan) const;
    // End of Ilog Consulting 04/01/2000
	void convertDate(struct tm*) const;
	void nextDay(AdxDate&) const;
	void addNbDays(int nbDays, AdxDate& theDate) const;
	// End of Ilog Consulting

};

// Ilog Consulting
extern int isLeapYear(int year);
extern int monthLength(int mo, int ye);
extern void numberToDate(int nb, int ye, int* d, int* mo);
extern int yearDayNumber(int day, int month, int year);
// End of Ilog Consulting


#endif /*ADXDATE_H*/
