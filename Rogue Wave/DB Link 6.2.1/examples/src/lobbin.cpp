// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/lobbin.cpp
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
// This program shows how to store into, and retrieve from, a database 
// large amounts of binary data.
//
// Each text is send into one records stored in a table.
// The program creates the table DBLBIN with three fields:
//                  - NAME which identifies the data inside the table.
//                  - TVAL which stores the proper data.
//
// The program takes two files given by the user, and
// saves them in two rows into DBLBIN.
// Then it reads back the two rows from the database
// DBLBIN table and saves them in two temporary files. Those files must
// be identical to the two source files given by the user.
//
// NB: + The type of the column depends on the target RDBMS.
//
// ----------------------------------------------------------------------------

#include "ildutil.h"

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
# ifndef _FSTREAM_
#  include <fstream>
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
# ifndef _FSTREAM_H
#  include <fstream.h>
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
// Ending utility
// -----------------------------------------------------------------------
const char* DropStr = "drop table DBLBIN";

// -----------------------------------------------------------------------
// Asking for files
// If asking for a destination file, and user gave none
// then, on UNIX, use /tmp/bindataX
//       on WINDOWS, use %TMP%\bindataX or %TEMP%\bindataX
// -----------------------------------------------------------------------
void
AskFile(char* fullFileName,
	IlInt pos,
	IlBoolean dest)
{
    if(fullFileName){
	fullFileName[0] = 0;
	if(dest)
	    cout << "Retrieving "
		 << (pos ? "first" : "second")
		 << " data set" << endl;
	cout << "Give the path of the " << (pos ? "first" : "second");
	if(dest){
	    cout << " destination file" << endl;
	    cout << "(Press enter to use default file name) : ";
	} else
	    cout << " source file : ";

	getLine(fullFileName, 128, cin);

	if(!fullFileName[0]) {
	    if(dest){
#ifdef WINDOWS
		char tmpDir[255];
		if (getenv("TEMP"))
		    strcpy(tmpDir, getenv("TEMP"));
		else if (getenv("TMP"))
		    strcpy(tmpDir, getenv("TMP"));
		if (tmpDir)
		    sprintf(fullFileName,"%s\\%s%s", tmpDir,
			    "bindata", (pos ? "1" : "2"));
		else
		    sprintf(fullFileName, "C:\\bindata%s", (pos ? "1" : "2"));
#else
		sprintf(fullFileName, "/tmp/bindata%s", (pos ? "1" : "2"));
#endif
		cout << endl;
		cout << "The destination file is : " << fullFileName << endl;
	    }
	}
    }
}

// -----------------------------------------------------------------------
// IldInsertLongText function
// -----------------------------------------------------------------------
IlBoolean
IldInsertBinary(const char* name,
		IldRequest* request,
		ifstream& inFile,
		const char* lobType)
{
    char str[128];
    ostrstream ostr(str, 128);
    ostr.seekp(ios::beg);
    IlBoolean res = IlTrue;
    IldBytes data;
  
    // Insert a row with a null in BLOB column
    ostr << "insert into DBLBIN values ('" << name
	 << ((strcmp(lobType, "BLOB") ||
	      strncmp(request->getDbms().getName(), "oracle", 6)) ?
	     "', NULL)" : "', EMPTY_BLOB())")
	 << ends;
    do {
	request->execute(str);
    } while (!request->isCompleted());
    if (request->isErrorRaised())
	res = IlFalse;
    else {
	// Prepare the where clause of the update
	ostr.seekp(ios::beg);
	ostr << " NAME = '" << name << "'" << ends;
    
	// Find out file size 
	data._size = (IlUInt)inFile.seekg(0, ios::end).tellg();
	data._value = new IlUChar [(int)data._size + 1];
	if (!data._value) {
	    cout << "Memory exhausted : cannot allocate text buffer" << endl;
	    res = IlFalse;
	} else {
	    // Read in data
	    inFile.seekg(0, ios::beg); // Back to begining of file
	    inFile.read((char*)data._value, (int)data._size);
	    
	    // Proper text insertion : actually updates the row
	    do {
		request->insertBinary(data, "DBLBIN", "TVAL", str);
	    } while (!request->isCompleted());
	    res = !request->isErrorRaised();
	}
	if (data._value)
	    delete [] data._value;
    }
    return res;
}

// -----------------------------------------------------------------------
// main function
// -----------------------------------------------------------------------
int
processLob(char** argv,
	   IldDbms* dbms,
	   const char* lobType)
{
    char str[256];
    char str2[256];
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Request allocation failed:", dbms);
	delete dbms;
	exit (-1);
    }
  
    // Table creation.
    char createStr [256];
    ostrstream ostr(createStr, 256);
    ostr << "create table DBLBIN (NAME char(20), TVAL "
	 << lobType << ")" << ends;
    cout << "Creation of a table : " << createStr << endl;
    do {
	request->execute(createStr);
    } while (!request->isCompleted());
    if (request->isErrorRaised()) {
	IldDisplayError("Cannot create table:", request);
	delete dbms;
	exit (-1);
    }
    cout << endl;

    // Explain what's up
    cout << "You will be prompted for 2 source file paths." << endl;
    cout << "These files should contain some binary data like" << endl;
    cout << "executable code or picture." << endl;
    cout << "Db-Link will insert the contents of the files" << endl;
    cout << "into the database and then ask you for 2 destination files" << endl;
    cout << "in order to save the retrieved data into those files." << endl;
    cout << endl;
  
    // Binary insertions.
    AskFile(str, 1, IlFalse);
    if (!str[0]){
	cout << "Source data file must be provided. Exiting." << endl;
	IldEndSample(dbms, request, DropStr, 0, 1);
    }

    ifstream inFile(str, ios::in
#ifdef WINDOWS
#if !defined(IL_STD) && !defined(__BORLANDC__)
		    | ios::nocreate
#endif
		    | ios::binary
#endif
		    ) ;
    if (!inFile) {
	cout << str << " is either unreadable or unreachable !" << endl;
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    if (!IldInsertBinary("1st Bin", request, inFile, lobType)) {
	IldDisplayError("Cannot insert binary data:", request);
	inFile.close();
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    inFile.close();
    cout << endl;

    AskFile(str, 0, IlFalse);
    if(!str[0]){
	cout << "Source data file must be provided. Exiting." << endl;
	IldEndSample(dbms, request, DropStr, 0, 1);
    }

    inFile.open(str, ios::in
#ifdef WINDOWS
#if !defined(IL_STD) && !defined (__BORLANDC__)
		| ios::nocreate
#endif
		| ios::binary
#endif
		) ;
    if (!inFile) {
	cout << str << " is either unreadable or unreachable !" << endl;
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    if (!IldInsertBinary("2nd Bin", request, inFile, lobType)) {
	IldDisplayError("Cannot insert binary data:", request);
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    inFile.close();
    cout << endl;

    if (dbms->isAsync()) {
	// We may run two queries together.
	// But we have to do it using two different connections.
	IldDbms* dbms2 = IldNewDbms(argv[1], argv[2]);
	if (dbms2->isErrorRaised()) {
	    IldDisplayError("Second connection failed: ", dbms2);
	    delete dbms2;
	    IldEndSample(dbms, request, DropStr, 0, 1);
	} else {
	    if (!dbms2->setAsync(IlTrue)) {
		IldDisplayError("Could not switch Asynchronous mode ON.",
				dbms2);
		delete dbms2;
		exit(1);
	    }
	    if (!dbms2->isAsync()) {
		IldDisplayError("Asynchronous mode is not turned ON.", dbms2);
		delete dbms2;
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	    // Commit is required to access the inserted data from another
	    // request (do not need to do it for mssql).
	    if (strcmp(dbms->getName(), "mssql") && !dbms->commit(request))
		IldDisplayError("Could not commit data.", dbms);
	}
	IldRequest* request2 = dbms2->getFreeRequest();
	IlBoolean error1 = IlFalse,
	    error2 = IlFalse,
	    firstRun = IlTrue; // To control the end of the two queries.
	if (dbms2->isErrorRaised()) {
	    IldDisplayError("Could not get second request", dbms2);
	    delete dbms2;
	    IldEndSample(dbms, request, DropStr, 0, 1);
	}
	// We extract the first data set.
	AskFile(str, 1, IlTrue);

	// We extract the second data set.
	AskFile(str2, 0, IlTrue);

	do {
	    if (firstRun || !request->isCompleted()) {
		error1 = request->getLargeObject("DBLBIN", "TVAL",
						 "NAME = '1st Bin'",
						 str).isErrorRaised();
		if (error1) {
		    IldDisplayError("Selection failed:", request);
		    delete dbms2;
		    IldEndSample(dbms, request, DropStr, 0, 1);
		}
	    }
	    if (firstRun || !request2->isCompleted()) {
		error2 = request2->getLargeObject("DBLBIN", "TVAL",
						  "NAME = '2nd Bin'",
						  str2).isErrorRaised();
		if (error2) {
		    IldDisplayError("Selection failed:", request2);
		    delete dbms2;
		    IldEndSample(dbms, request, DropStr, 0, 1);
		}
	    }
	    firstRun = IlFalse;
	} while (!request->isCompleted() ||
		 !request2->isCompleted());
	delete dbms2;
    } else {
	// We extract the first data set.
	AskFile(str, 1, IlTrue);

	if (!request->getLargeObject("DBLBIN", "TVAL", "NAME = '1st Bin'",
				     str)) {
	    IldDisplayError("Selection failed:", request);
	    IldEndSample(dbms, request, DropStr, 0, 1);
	}
	cout << endl;

	// We extract the first data set.
	AskFile(str, 0, IlTrue);

	if (!request->getLargeObject("DBLBIN", "TVAL", "NAME = '2nd Bin'",
				     str)) {
	    IldDisplayError("Selection failed:", request);
	    IldEndSample(dbms, request, DropStr, 0, 1);
	}
	cout << endl;
    }
    cout << endl;
  
    // Table destruction and disconnection.
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
    return 0;
}
