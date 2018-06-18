// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/rebindcl.cpp
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
// This program demonstrates how to bind a column value to a new buffer
// between each fetch operation.
//
// This is used as an optimization when the column values need to be
// kept in memory by the application.
// In this case, the column values are overwritten by each new fetch
// operation, so the application needs to copy the data it needs to keep,
// at a different buffer location.
// Re-binding the column buffer between each fetch avoid this overhead,
// since each new fetch operation goes to a new address.
//
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _IOSTREAM_
#  include <iostream>
# endif
#else
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------
// Array size
const int nbElem = 10;
// Length of string values
const int strSize = 11;

// Definitions of the requests to be submitted
const char* selectQuery = "select colInt, colChar, colDate from rebindcl";
const char* DropStr = "drop table rebindcl";

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void
InsertData(IldDbms* dbms,
	   IldRequest* request)
{
    int i = 0;
    // Create the table.
    const char* dateTypeName = IldGetDateTypeName(dbms);
    char query[256];
    strcpy(query,
	   "create table rebindcl (colInt int, colChar char(10), colDate ");
    strcat(query, dateTypeName);
    strcat(query, ")");
    if (!request->execute(query))
	IldEndSample(dbms, request, 0, "Could not create table: ", 1);

    // insert data in it :
    IldDateTime dt;
    char string[11];
    char* dbOdbc = IldGetOdbcDbms(dbms);
    dt.setYear(2009);
    dt.setMonth(12);
    dt.setDay(1);
    memset(string, 0, 11);
    // Handle date as object :
    request->setStringDateUse(IlFalse);
    strcpy(query, "insert into rebindcl values (");
    if (!strncmp(dbms->getName(), "oracle", 6) ||
	!IldStrNICaseCmp(dbOdbc, "oracle", 6))
	strcat(query, ":1, :2, :3");
    else
	strcat(query, "?, ?, ?");
    strcat(query, ")");
    delete [] dbOdbc;
    dbOdbc = 0;
    if (!request->parse(query))
	IldEndSample(dbms, request, DropStr, "Could not parse query: ", 1);
    if (!request->bindParam((IlUShort)0, IldIntegerType) ||
	!request->bindParam((IlUShort)1, IldStringType) ||
	!request->bindParam((IlUShort)2, IldDateTimeType))
	IldEndSample(dbms, request, DropStr, "Could not bind parameters: ", 1);
    for (i = 0 ; i < nbElem ; i++) {
	string[i] = (char)('A' + i);
	dt.setDay((unsigned short)(dt.getDay() + 1));
	if (!request->setParamValue((IlInt)i, 0) ||
	    !request->setParamValue(string, 1) ||
	    !request->setParamValue(&dt, 2))
	    IldEndSample(dbms, request, DropStr,
			 "Could not set parameter values: ", 1);
	if (!request->execute(0, 1))
	    IldEndSample(dbms, request, DropStr, "Execute failed: ", 1);
    }
    // Switch date mode back to string mode :
    request->setStringDateUse(IlTrue);
}

// ----------------------------------------------------------------------------
//
// The main problems dealing with date as string are :
// 1) One depends upon the configuration of both client and server sides
// 2) the length of the string returned by the database can change
// from a database to another.
// As a consequence of point 2, it is not possible to set a length value
// here. But the length will be known after the execute.
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    int i = 0;
    IlBoolean multiBuf = IlTrue;
    IlInt colInt[nbElem];
    char  colChar[nbElem][strSize];
    char* colDate[nbElem];

    if (argc < 3 || argc > 4) {
	cout << "Usage : " << argv[0]
	     << " <RDBMS> <connection string> [notMultibuf]" << endl;
	return -1;
    }
    if (argc == 4) // Tells not to use app data spaces.
	multiBuf = IlFalse;

    // Creation of the first DBMS connection =================
    IldDbms* Dbms = IldAllocConnect(argv[1], argv[2]);
    if (Dbms->isErrorRaised())
	IldEndSample(Dbms, 0, 0, "Could not open connection: ", 1);
    
    // Creation of the cursor ===========================
    IldRequest* Request = Dbms->getFreeRequest();
    if (!Request || Dbms->isErrorRaised())
	IldEndSample(Dbms, 0, 0, "Could not get free request: ", 1);
    
    // If this function returns, then everything went OK
    InsertData(Dbms, Request);

    // Perform a select request =======================
    if (!Request->execute(selectQuery))
	IldEndSample(Dbms, Request, DropStr, "Selection failed:", 1);
    
    // Get the length of the string for the date column
    // and allocate the colDate array
    IlUInt dateStrLen = Request->getColSize(2) + 1;
    for (int k = 0 ; k < nbElem; k++)
    	colDate[k] = new char[dateStrLen];
    // Binding output to app data spaces ============================
    if (!Request->bindCol((IlUShort)0, IldIntegerType, &colInt[0]))
	IldEndSample(Dbms, Request, DropStr, "First bind failed.", 1);
    if (!Request->bindCol(1, IldStringType, colChar, strSize))
	IldEndSample(Dbms, Request, DropStr, "Second bind failed.", 1);
    if (!Request->bindCol(2, IldDateType, colDate[0], dateStrLen))
	IldEndSample(Dbms, Request, DropStr, "Third bind failed", 1);
    memset(colDate[0], 0, (size_t)dateStrLen);
    
    // Printing the result of the select request ==============
    i = 0 ;
    cout << "\t Table: rebindcl" << endl;
    IldPrintTuple(Request, IldNames);
    IldPrintTuple(Request, IldSeparators);
    while (Request->fetch().hasTuple()) {
	if (Request->isErrorRaised())
	    break;
	IldPrintTuple(Request);
	if (multiBuf) {
	    i++;
	    if (i == nbElem)
		break;
	    if (!Request->bindCol((IlUShort)0, IldIntegerType, &colInt[i]))
		IldEndSample(Dbms, Request, DropStr, "First bind failed.", 1);
	    if (!Request->bindCol(1, IldStringType, colChar[i], strSize))
		IldEndSample(Dbms, Request, DropStr, "Second bind failed.", 1);
	    if (!Request->bindCol(2, IldDateType, colDate[i], dateStrLen))
		IldEndSample(Dbms, Request, DropStr, "Third bind failed.", 1);
	    memset(colDate[i], 0, (size_t)dateStrLen);
	}
    }
    if (Request->isErrorRaised())
	IldDisplayError("Error in fetch:", Request);
    cout << endl;
    if (multiBuf) {
	// In case an error occured during fetch, we should not try and print 
	// the buffers contents past the last succesfully fetched row.
	int maxElt = i;
	cout << "Buffers contents:" << endl;
	for (i = 0 ; i < maxElt ; i++) {
	    // The quotes show the white chars are kept in string receiving
	    // CHAR SQL data type values.
	    cout << colInt[i] << "\t'"
		 << colChar[i] << "'\t"
		 << colDate[i] << endl;
	}
    }

    for(i = 0; i < nbElem; i++)
    	delete [] colDate[i];
    IldEndSample(Dbms, Request, DropStr, "Cleaning up and exiting.");
}
