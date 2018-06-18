// AdxCsvfiles.h
// -------------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#ifndef ADXCSVFILES_H
#define ADXCSVFILES_H

#include "stdafx.h"
#include <cassert>
#include <fstream>

using std::ifstream;
using std::fstream;

//
// Two classes are defined : AdxCsvFileReader and AdxCsvLine
// They are intended to be used to read CSV files (eg from Excel)
// but can be useful for any file in which values are delimited
// by separating characters.
//
// AdxCsvFileReader acts as an iterator on a file, returning instances
// of AdxCsvLine. Each instance of AdxCsvLine allows access to each
// token as a char*, a long or a double. 
//

//
// An object to split a string in tokens
//
// Features :
//   - Several specified separators
//   - The decimal point can be any character (intended for
//     files where the comma is the decimal point)
//   - Multiple separators can be merged and treated as one
//     In this case, leading and trailing separators are skipped
//   - Separators inside a string can be dealt with if this string
//     is surrounded by string delimiters (" by default)
//

//
// Examples (" are not part of the string, but for readability) :
//
// "a"    =>  1 field, "a"
// "a,a"  =>  2 fields, "a" "a"
// "a,"   =>  2 fields, "a" ""
// "a,,"  =>  3 fields, "a" "" ""
// ",a,"  =>  3 fields, "" "a" ""
// "a,,a" =>  3 fields, "a" "" "a"
//
// Multiple separators as one are mainly inteded for the case
// when spaces and tabs are used as separators
// if multiple separators are treated as one, the example above become
//
// "a"    =>  1 field,  "a"
// "a,a"  =>  2 fields, "a" "a"
// "a,"   =>  1 field,  "a"
// "a,,"  =>  1 field,  "a"
// ",a,"  =>  1 field,  "a"
// "a,,a" =>  2 fields, "a" "a"
//
// Another example :
// 
// AdxCsvLine l ("2,3;3,5", ";", ',') will give
// 2 fields, l.getDouble(0) == 2.3 and l.getDouble(1) == 3.5
//
// An exemple a string delimiter
// AdxCsvLine l ("\"camion 3,5 T\",3.5", ",", '.', 0, '"') will give
// 2 fields, "camion 3,5 T" (without ") and l.getDouble(1) == 3.5
// but
// AdxCsvLine l ("\"camion 3,5 T\",3.5", ",", '.', 0) will give
// 3 fields, "\"camion 3" for the first, "5 T\"" the second and l.getDouble(2) == 3.5
// 

class AdxCsvLine {

private:
  char*  _line;
  char** _fields;
  long   _nbFields;
  long   _isEmpty;
  char   _decimal;


public:
  AdxCsvLine(const char* line,
////////////////////////////////////////////////////////////
//MC 2000/09/27 : impose séparateur unique à ;
//             const char* separators = ",;", 
             const char* separators = ";", 
////////////////////////////////////////////////////////////
             const char decimal = '.', 
             const int treatMultipleSeparatorsAsOne = 0,
             const char stringDelimiter = '\000');
  ~AdxCsvLine();
  AdxCsvLine(AdxCsvLine& value);

  // Number of distinct (maybe empty) fields
  inline long getNbOfFields() const {return _nbFields;};
  
  // are all the field empty
  inline int isEmpty() const {return _isEmpty;}
  // is this field empty
  inline int isEmpty(long index) const {return (strlen(_fields[index]) == 0);}

  // access to the whole line
  inline const char* getString() const {return _line;}
  // access to the fields
  // fields are numbered starting with 0
  inline const char* operator[] (long index) const {return getString(index);}
  inline const char* getString(long index) const {return _fields[index];}
  // for all other access methods, the field must not be empty
  long getLong(long index) const ;
  double getDouble(long index) const;
};

//
// An "iterator" on the lines of a file
// Lines beginning by a specified substring can be skipped
// Empty lines (strlen == 0) are always skipped
//

class AdxCsvFileReader 
{
private:
  char* _comment;
  char* _separators;
  char _decimal;
  char _delimiter;
  int _multipleAsOne;
  ifstream _f;

  char* _line;
  int _ok;
  int _opened;

public:
  AdxCsvFileReader(const char* name, 
                   // The separators to be used for breaking a line into tokens
////////////////////////////////////////////////////////////
//MC  2000/09/27: impose séparateur unique à ;
//                   const char* separators = ",;", 
                   const char* separators = ";", 
////////////////////////////////////////////////////////////
                   // The decimal point used in the file
                   const char decimal = '.', 
                   // if set to non null, sequences of (maybe different) separators
                   // are considered as one separator
                   const int treatMultipleSeparatorsAsOne = 0,
                   // The char that begins and ends strings
                   const char stringDelimiter = '"',
                   // the substring that a comment line begins with
                   const char* skipLinesBeginningWith = 0);
  ~AdxCsvFileReader();

  // Comment skipping
  // if the parameter is null, no lines are skipped
  // The default is that no lines are skipped
  // All blank lines are always skipped
  void skipLinesBeginningWith(const char* comment = "//");

  // Does the file still has lines to be read
  inline int ok() const {return _ok;}
  // Access to the current line
  AdxCsvLine operator*() const;
  inline const char* getRealLine() const {assert(ok()); return (const char*) _line;}
  // go to next line
  AdxCsvFileReader& operator++();

private:
  void goToNextValidLine();
};

class AdxCsvFileWriter 
{
private:
  char* _comment;
  char* _separator;
  char _decimal;
  char _delimiter;
  fstream _f;

  int _ok;
  int _opened;
  int _beginLine;
  int _fileIsEmpty;

public:
  AdxCsvFileWriter(const char* name,
				   // file opening mode 
				   int addAtEof, 
				   // the comment string
				   const char* comment = "//", 
               // the separators string
               const char* separators = ";", 
               // The decimal point
               const char decimal = '.', 
               // The char that begins and ends strings
               const char stringDelimiter = '"');
  
  ~AdxCsvFileWriter();

  // Does the file still has lines to be read
  inline int ok() const {return _ok;}
  inline int fileIsEmpty() const {return _fileIsEmpty;}

  // add comments, ans differents fields
  void addComment(const char* string, int endLine = 1);
  void addTime(int endLine = 1);
  void addField(const char* string, int endLine = 1);
  void addField(long value, int endLine = 1);
  void addField(double value, int endLine = 1);
};
 
#endif
