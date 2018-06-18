// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/ildutil.h
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
// This file contains functions used by most of the demo programs:
//
//     + "IldFormatLine" which takes an array of items as argument.
//       Each item has a value, an identation mode (right, left, or
//       middle) and a length.
//       The function fills an output buffer up with item values using
//       formatting information.
//
//     + "IldPrintRelation" uses the previous function to print a
//       relation.
//
//     + "IldPrintTuple" prints a tuple.
//
//     + "IldGetDateTypeName" get date type for various dbms.
//
//     + "IldGetNumericTypeName" get numeric type for various dbms.
//
//     + "IldGetLongBinaryTypeName" get long binary type for various
//                                  dbms.
//
//     + "IldGetLongTextTypeName" get Long text type for various Dbms.
//
//     + "IldEndSample" drops the table and terminates the application,
//                      optionaly displaying a final message.
//
//     + "IldPrintResults" display all rows returned by a query.
//
//     + "IlRunTime" return the clock time for performance measurements
//
// ----------------------------------------------------------------------------

#include <ildblink/dblink.h>
#include <ildblink/dbmsmodl.h>
#include <ildblink/reqmodl.h>

#ifdef IL_STD
# ifndef _CSTDIO_
#  include <cstdio>
# endif
# ifndef _CSTDLIB_
#  include <cstdlib>
# endif
# ifndef _CSTRING_
#  include <cstring>
# endif
# ifndef _IOSTREAM_
#  include <iostream>
# endif
#else
# ifndef _STDIO_H
#  include <stdio.h>
# endif
# ifndef _STDLIB_H
#  include <stdlib.h>
# endif
# ifndef _STRING_H
#  include <string.h>
# endif
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

#ifdef IL_STD
# ifndef _STRSTREAM_
#  include <strstream>
# endif
#else
# ifndef _STRSTREAM_H_
#  ifndef WINDOWS
#   include <strstream.h>
#  else
#   include <strstrea.h>
#  endif
# endif
#endif

IL_STDUSE

// -----------------------------------------------------------------------
// Local types declarations
// -----------------------------------------------------------------------

enum IldIndentType {IldLeft, IldCenter, IldRight};
enum IldPrintMode {IldNames, IldTypes, IldSeparators, IldTupleData};

struct IldItemStruct {
    char*         _buffer;
    int           _width;
    IldIndentType _mode;
    int           _space;
    int           _quote;
};

enum IldAscState {
    IldAscNone,
    IldAscExecute,
    IldAscFetch,
    IldAscInsert,
    IldAscGetPKey,
    IldAscGetFKeys,
    IldAscGetIdxs,
    IldAscGetSpecCols
};

// -----------------------------------------------------------------------
// Prototypes
// -----------------------------------------------------------------------

// ----------------------------
// Deallocate the print buffers
void IldCleanMemory();

// --------------------------
// Prepare a line for display
char*
IldFormatLine(IlInt itemsCount,
	      IldItemStruct* itemsArray,
	      IlBoolean columnSeparator);

// ----------------------------------------
// Print the description of a schema entity
void
IldPrintEntity (const IldSchemaEntity* ent,
		IlBoolean printId,
		ostream& ostr = cout);

// ------------------------------
// Print the fields of a relation
void
IldPrintRelation (const IldRelation& relation,
		  ostream& ostr = cout,
		  IldAscState* state = 0,
		  IlBoolean printRelId = IlFalse);

// ------------------------------------
// Print the description of a procedure
void
IldPrintCallable (const IldCallable* proc,
		  IlBoolean printProcId = IlFalse,
		  ostream& ostr = cout);

// ---------------------------------------
// Print the details of a relation indexes
//void 
//IldPrintIndexes(IldRelation* relation);

// ----------------------------------------------
// Print the contents of all columns from a tuple
void
IldPrintTuple(IldRequest* request,
	      IldPrintMode mode = IldTupleData,
	      ostream& ostr = cout);

// ---------------------
// Print the demo header
void
IldDisplayHeader(const char* title,
		 ostream& ostr = cout);

// -----------
// Print error 
void
IldDisplayError(const char* operation,
		const IldIldBase* ildobj,
		ostream& ostr = cout);

// -----------
// Print warning 
void
IldDisplayWarning(const char* operation,
		  const IldIldBase* ildobj,
		  ostream& ostr = cout);

// -----------
// Print diagnostics (information and error) if any
void
IldDisplayDiags(const char* operation,
		IldIldBase* ildobj,
		ostream& ostr = cout);

// ---------------------------------------------------------
// Convert a datetime object to its printable representation
char* 
IldDateTimeToString(IldDateTime dt);

// ------------------------------------------------
// Output the contents of an object or a collection
void
IldPrintADT(IldADTValue* v,
	    ostream& ostr);

// -------------------------------------
// Returns the full SQL type of a column
char*
IldBuildColType(const IldDescriptor* col);

// -----------------------------------------------------------------
// If connected via ODBC, returns the name of the RDBMS connected to.
char*
IldGetOdbcDbms(IldDbms* dbms);

// --------------------------------
// Returns the Dbms date type name.
const char*
IldGetDateTypeName(IldDbms* dbms);

// -----------------------------------
// Returns the Dbms numeric type name.
const char*
IldGetNumericTypeName(IldDbms* dbms);

// ---------------------------------------
// Returns the Dbms long binary type name.
const char*
IldGetLongBinaryTypeName(IldDbms* dbms);

// -------------------------------------
// Returns the Dbms long text type name.
const char*
IldGetLongTextTypeName(IldDbms* dbms);

// --------------------------------------
// Returns the Dbms Binary LOB type name.
const char*
IldGetBLobTypeName(IldDbms* dbms);

// -----------------------------------------
// Returns the Dbms Character LOB type name.
const char*
IldGetCLobTypeName(IldDbms* dbms);

// ---------------------------------------------------
// Retrieve a line ended by '\n' from an input stream.
// Cf portability problems with istream::getline() function.
char*
getLine(char* buffer, IlInt maxSize, istream& istr);

// ------------------------------------
// Drop the table and terminate the app
void
IldEndSample(IldDbms* dbms,
	     IldRequest* request,
	     const char* dropStr = 0,
	     const char* endMsg = 0,
	     int s = 0);

// -----------------------------------------------------
// Display returned rows (returns 0 if an error occured)
IlInt
IldPrintResults(IldRequest* request,
		ostream& ostr = cout);

// ------------------------------------------------------
// Clock time as a double
IlDouble IlRunTime();
