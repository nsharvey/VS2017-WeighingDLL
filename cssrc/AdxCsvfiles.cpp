// AdxCsvfiles.cpp
// ---------------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include <fstream>
#include <time.h>
#include <locale.h>

#include "AdxCsvfiles.h"
#include "fexist.h"
#include "stdafx.h"					// 06.04 Unicode
#include "win unicode.h"			// 06.04 Unicode


const int bufferSize = 4095;

using std::ios;
using std::endl;
using std::streampos;

long CountFields(const char* origLine,
                 const char* separators,
                 const char stringDelimiter,
                 const int treatMultipleSeparatorsAsOne) 
{
  long _nbFields = 0;
  int lastCharWasASep = 0;
  size_t lng = strlen(origLine);
  char* line = new char [lng + 1];

  //
  // copies line and replaces all strings between
  // double quotes (") with strings between single quotes (')
  //
  size_t index = 0;
//  int insideAString = 0;
  for (size_t i = 0; i < lng; ++i) {
///////////////////////////////////////////////////////
//MC 2000/09/27 : neutralise traitement des délimiteurs "
//    if (insideAString) {
//      if (origLine[i] == stringDelimiter) {
//        // end of string found
//        insideAString = 0;
//      }
//    } else {
      line[index] = origLine[i];
      index++;
//      if (origLine[i] == stringDelimiter) {
//        // beginning of string found
//        insideAString = 1;
//      }
//    }
///////////////////////////////////////////////////////
  }
  line[index] = '\000';
  lng = strlen(line);

  for (size_t i = 0; i < lng; ++i) {
    // is line[i] a separator
    if (strchr(separators, line[i])) {
      if (!(lastCharWasASep && treatMultipleSeparatorsAsOne)) {
        // each sep defines a field, so we have a new field
        ++_nbFields;
      }
      lastCharWasASep = 1;
    } else {
      lastCharWasASep = 0;
    }
  }
  ++_nbFields;

  delete [] line;
  return _nbFields;
}

//--------------------------------------------------------
//
// class AdxCsvLine
//
AdxCsvLine::AdxCsvLine(const char* origLine, 
             const char* separators, 
             const char decimal, 
             const int treatMultipleSeparatorsAsOne,
             const char stringDelimiter) {

  assert(!strchr(separators, decimal));
  assert(!strchr(separators, stringDelimiter));
  _decimal = decimal;

  _line = new char[strlen(origLine) + 1];
  strcpy(_line, origLine);

  char* line = new char[strlen(origLine) + 1];
  char* lineToBeDeleted = line;
  strcpy(line, origLine);

  // When separators are grouped, we skip
  // those at the beginning and at the end
  if (treatMultipleSeparatorsAsOne) {
    while (strchr(separators, line[0])) {
      line = line + 1;
    }
    while (strchr(separators, line[strlen(line) - 1])) {
      line[strlen(line) - 1] = '\000';
    }
  }

  // Let's deal with the empty lines
  size_t lng = strlen(line);
  if (lng == 0) {
    _nbFields = 0;
    _fields = 0;
    delete [] lineToBeDeleted;
    return;
  }

  // Count the number of fields
  _nbFields = CountFields(line, separators, stringDelimiter, treatMultipleSeparatorsAsOne);

  // build the field structure
  _fields = new char* [_nbFields];


  // scan all the fields
  long indexFields = 0;
  int lastCharWasASep = 0;
  long positionOfBeginning = 0; 
  int insideAString = 0;
  for (size_t i = 0; i < lng; ++i) {
///////////////////////////////////////////////////////
//MC 2000/09/27 : neutralise traitement des délimiteurs "
/*    if (insideAString) {
      if (origLine[i] == stringDelimiter) {
        // end of string found
        insideAString = 0;
      } else {
        continue;
      }
    } else {
      if (origLine[i] == stringDelimiter) {
        // beginning of string found
        insideAString = 1;
        continue;
      }
    }
*/
///////////////////////////////////////////////////////
    // is line[i] a separator
    if (strchr(separators, line[i])) {
      if (!(lastCharWasASep && treatMultipleSeparatorsAsOne)) {
        // each sep defines a field, so we have a new field
        long fieldLength = i - positionOfBeginning;
///////////////////////////////////////////////////////
//MC  2000/09/27: neutralise traitement des délimiteurs "
        // skip the string delimiters
//        if (line[positionOfBeginning] == stringDelimiter) {
//          assert(line[positionOfBeginning + fieldLength - 1] == stringDelimiter);
//          _fields[indexFields] = new char [fieldLength - 1];
//          strncpy(_fields[indexFields], line + positionOfBeginning + 1, fieldLength - 2);
//          _fields[indexFields][fieldLength - 2] = '\000';
//        } else {
          _fields[indexFields] = new char [fieldLength + 1];
          strncpy(_fields[indexFields], line + positionOfBeginning, fieldLength);
          _fields[indexFields][fieldLength] = '\000';
//        }
///////////////////////////////////////////////////////

        ++indexFields;
        positionOfBeginning = i + 1;
      }
      lastCharWasASep = 1;
      if (treatMultipleSeparatorsAsOne) {
        positionOfBeginning = i + 1;
      }
    } else {
      lastCharWasASep = 0;
    }
  }
  // We still have the last field to copy
  if (lastCharWasASep) {
    _fields[indexFields] = new char [1];
    _fields[indexFields][0] = '\000';
  } else {
    long fieldLength = lng - positionOfBeginning;
    _fields[indexFields] = new char [fieldLength + 1];
    strncpy(_fields[indexFields], line + positionOfBeginning, fieldLength);
    _fields[indexFields][fieldLength] = '\000';
  }

  delete [] lineToBeDeleted;
}

AdxCsvLine::~AdxCsvLine() {

  for (long i = 0; i < _nbFields; ++i) {
    delete [] _fields[i];
  }
  delete [] _fields;
  delete [] _line;
}

long AdxCsvLine::getLong(long index) const {
  assert(!isEmpty(index));
  return atol(_fields[index]);
}

double AdxCsvLine::getDouble(long index) const {

  assert(!isEmpty(index));
  double result;
  char* f = new char [strlen(_fields[index]) + 1];
  strcpy(f, _fields[index]);
  if (_decimal != '.') {
    for (size_t i = 0; i < strlen(f); ++i) {
      if (f[i] == _decimal) {
        f[i] = '.';
      }
    }
  }
  result = atof(f); 
  delete f;
  return result;
}

//--------------------------------------------------------
//
// class AdxCsvLineReader
//
AdxCsvFileReader::AdxCsvFileReader(const char* name, 
                                   const char* separators, 
                                   const char decimal, 
                                   const int treatMultipleSeparatorsAsOne,
                                   const char stringDelimiter,
                                   const char* comment) 
{
  _ok = 1;
  _comment = 0;
  _separators = new char[strlen(separators) + 1];
  strcpy(_separators, separators);
  _decimal = decimal;
  _delimiter = stringDelimiter;
  _multipleAsOne = treatMultipleSeparatorsAsOne;
  _line = new char [bufferSize + 1];
  _opened = 0;

  if (!fexist(name)) {
    _ok = 0;
    return;
  }
  _f.open(name, ios::in /*| ios::nocreate*/);
  if (_f.fail()) {
    _ok = 0;
    return;
  }
  _opened = 1;
  goToNextValidLine();
  skipLinesBeginningWith(comment);
}

AdxCsvFileReader::~AdxCsvFileReader() {
  delete [] _separators;
  delete [] _line;
  if (_comment) {
    delete [] _comment;
  }
  if (_opened) {
    _f.close();
  }
}

void AdxCsvFileReader::goToNextValidLine() {
  int goOn;
  do {
    goOn = 0;
    if (!_ok || (_f.eof())) {
      _ok = 0;
      return;
    }
    _f.getline(_line, bufferSize);
    if (_comment) {
      if (strlen(_comment) <= strlen(_line)) {
        if (!strncmp(_comment, _line, strlen(_comment))) {
          goOn = 1;
        }
      }
    }
    if (strlen(_line) == 0) {
      goOn = 1;
    }
  } while (goOn);
}

AdxCsvLine AdxCsvFileReader::operator*() const {
  return AdxCsvLine(_line, _separators, _decimal,  _multipleAsOne, _delimiter);
}

AdxCsvFileReader& AdxCsvFileReader::operator++() {
  goToNextValidLine();
  return *this;
}

void AdxCsvFileReader::skipLinesBeginningWith(const char* comment) {
  if (_comment) {
    delete [] _comment;
  }
  _comment = 0;
  if (comment) {
    _comment = new char [strlen(comment) + 1];
    strcpy(_comment, comment);
    if (!strncmp(_comment, _line, strlen(_comment))) {
      // the current line is a comment
      goToNextValidLine();
    }
  }
}

//--------------------------------------------------------
//
// class AdxCsvLineWriter
//
AdxCsvFileWriter::AdxCsvFileWriter(const char* name,
								   int addAtEof,
								   const char* comment,
		                           const char* separator, 
		                           const char decimal,
								   const char stringDelimiter) 
{
  _ok = 1;
  _fileIsEmpty = 0;
  _comment = new char[strlen(comment) + 1];
  strcpy(_comment, comment);
  _separator = new char[strlen(separator) + 1];
  strcpy(_separator, separator);
  _decimal = decimal;
  _delimiter = stringDelimiter;
  _opened = 0;

  if (addAtEof) {
	 _f.open(name, ios::in|ios::out);
  }
  else {
	 _f.open(name, ios::out);
  }
  if (_f.fail()) {
	 _ok = 0;
	 return;
  }
  else {
    _f.seekp(0, ios::end);
    if( _f.tellp() == static_cast<streampos>( 0) ) {
      _fileIsEmpty = 1;
    }
  }
  _opened = 1;
  _beginLine = 1;
}

AdxCsvFileWriter::~AdxCsvFileWriter() {
  if (_separator) {
	delete [] _separator;
  }
  if (_comment) {
    delete [] _comment;
  }
  if (_opened) {
    _f.close();
  }
}

void
AdxCsvFileWriter::addComment(const char* string, int endLine)
{
	if (!_beginLine) {
		_f<<_separator;
	}
	else {
		_f<<_comment<<" ";
	}
	_f<<string;
	if (endLine) {
		_f<<endl;
		_beginLine = 1;
	}
	else {
		_beginLine = 0;
	}
}

void
AdxCsvFileWriter::addTime(int endLine)
{
   if (!_beginLine) {
		_f<<_separator;
	}

   time_t clk;
	time( &clk);
	tm* now = localtime(&clk);
	int year, month, mday, hour, min, sec;
	// Y2K. not 2098-proof !!
	if( now->tm_year >= 98) {
		year = now->tm_year+1900;
	} else {
		year = now->tm_year+2000;
	}
	month = now->tm_mon+1;
	mday = now->tm_mday;
	hour = now->tm_hour;
	min = now->tm_min;
	sec = now->tm_sec;
  
	char timeString[50];
	sprintf(timeString, "%d/%d/%d:%d:%d:%d", year, month, mday, hour, min, sec);
   _f<<timeString;

	if (endLine) {
		_f<<endl;
		_beginLine = 1;
	}
	else {
		_beginLine = 0;
	}
}

void 
AdxCsvFileWriter::addField(const char* string, int endLine)
{
	if (!_beginLine) {
		_f<<_separator;
	}
	_f<<_delimiter<<string<<_delimiter;
	if (endLine) {
		_f<<endl;
		_beginLine = 1;
	}
	else {
		_beginLine = 0;
	}
}

void 
AdxCsvFileWriter::addField(long value, int endLine)
{
	if (!_beginLine) {
		_f<<_separator;
	}
	_f<<value;
	if (endLine) {
		_f<<endl;
		_beginLine = 1;
	}
	else {
		_beginLine = 0;
	}
}

void 
AdxCsvFileWriter::addField(double value, int endLine)
{
	if (!_beginLine) {
		_f<<_separator;
	}
	_f<<value;
	if (endLine) {
		_f<<endl;
		_beginLine = 1;
	}
	else {
		_beginLine = 0;
	}
}

