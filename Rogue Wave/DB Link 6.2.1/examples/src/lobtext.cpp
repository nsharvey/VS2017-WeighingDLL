// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/lobtext.cpp
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
// This program shows how to store and restore large amounts of text.
//
// Each text is send into one record stored in a table.
// The program creates the table DBLTEXT with three fields:
//                  - NAME which identifies the data inside the table.
//                  - VALUE which stores the records themselves.
//
// The program takes the texts from two files given by the user, and
// saves them in two records into DBLTEXT.
// Then it reads back the two records from the database
// DBLTEXT table and saves them in two temporary files. Those files must
// be identical to the two source files given by the user.
//
// NB: + The type of the column depends on the target RDBMS.
//     + The array fetch feature must not be used here: the file contents 
//       will be retrieved using piece-wise fetch.
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
const char* DropStr = "drop table DBLTEXT";

// -----------------------------------------------------------------------
// Asking for files
// If asking for a destination file, and user gave none
// then, on UNIX, use /tmp/textdataX
//       on WINDOWS, use %TMP%\bindataX or %TEMP%\bindataX
// -----------------------------------------------------------------------
void
AskFile(char* fullFileName,
	IlInt pos,
	IlBoolean dest)
{
    if (fullFileName){
	fullFileName[0] = 0;
	if (dest)
	    cout << "Retrieving "
		 << (pos ? "first" : "second")
		 << " data set" << endl;
	cout << "Give the path of the " << (pos ? "first" : "second");
	if (dest){
	    cout << " destination file" << endl;
	    cout << "(Press enter to use default file name) : ";
	} else
	    cout << " source file : ";
    
	getLine(fullFileName, 128, cin);

	if (!fullFileName[0]) {
	    if (dest){
#ifdef WINDOWS
		char tmpDir[255];
		if (getenv("TEMP"))
		    strcpy(tmpDir, getenv("TEMP"));
		else if (getenv("TMP"))
		    strcpy(tmpDir, getenv("TMP"));
		if (tmpDir)
		    sprintf(fullFileName,"%s\\%s%s%s", tmpDir,
			    "text", (pos ? "1" : "2"), ".txt");
		else
		    sprintf(fullFileName, "C:\\text%s%s", (pos ? "1" : "2"),
			    ".txt");
#else
		sprintf(fullFileName, "/tmp/text%s%s", (pos ? "1" : "2"),
			".txt");
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
IldInsertLongText(const char* name,
		  IldRequest* request,
		  ifstream& inFile,
		  const char* lobType)
{
    char str[128];
    ostrstream ostr(str, 128);
    ostr.seekp(ios::beg);
    IlBoolean res = IlTrue;
  
    // Insert a row with a null in CLOB column
    ostr << "insert into DBLTEXT values ('" << name
	 << ((strcmp(lobType, "CLOB") ||
	      (strncmp(request->getDbms().getName(), "oracle", 6))) ?
	     "', NULL)" : "', EMPTY_CLOB())")
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
	int len = (int)inFile.seekg(0, ios::end).tellg();
	char* buff = new char [len + 1];
	if (!buff) {
	    cout << "Memory exhausted : cannot allocate text buffer" << endl;
	    res = IlFalse;
	} else {
	    // Read in data
	    inFile.seekg(0, ios::beg); // Back to begining of file
	    inFile.read(buff, len);
      
	    // Proper text insertion : actually updates the row
	    do {
		if (!request->insertLongText(buff, len, "DBLTEXT", "TVAL", str))
		    res = IlFalse;
	    } while (!request->isCompleted());
	}
	if (buff) 
	    delete [] buff;
    }
    return res;
}

// -----------------------------------------------------------------------
// Run text LOB example
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

    do {
	request->execute("drop table DBLTEXT");
    } while (!request->isCompleted());

    // Table creation.
    char createStr [256];
    ostrstream ostr(createStr, 256);
    ostr << "create table DBLTEXT (NAME char(20), TVAL "
	 << lobType << ")" << ends;
    cout << "Creation of a table : " << createStr << endl;    
    do {
	if (!request->execute(createStr)) {
	    IldDisplayError("Cannot create table:", request);
	    delete dbms;
	    exit (-1);
	}
    } while (!request->isCompleted());
    cout << endl;
  
    // A small text insertion :
    // A straight insert of a BLOB is not allowed with Informix
    const char* insStr = 0;
    if (strcmp(lobType, "CLOB") ||
	(strncmp(request->getDbms().getName(), "oracle", 6)))
	insStr = "insert into DBLTEXT (NAME) values ('A Text')";
    else
	insStr = "insert into DBLTEXT values ('A Text', EMPTY_CLOB())";
    cout << "First insert a small text : " << insStr << endl;
    do {
	if (!request->execute(insStr)) {
	    IldDisplayError("First insertion failed: ", request);
	    IldEndSample(dbms, request, DropStr, 0, 1);
	}
    } while (!request->isCompleted());
    do {
	if (!request->insertLongText("A short long text", 17,
				     "DBLTEXT", "TVAL", "NAME = 'A Text'")) {
	    IldDisplayError("First text update failed: ", request);
	    IldEndSample(dbms, request, DropStr, 0, 1);
	}
    } while (!request->isCompleted());
    cout << endl;
  
    // Explain what's up
    cout << "You will be prompted for 2 file paths." << endl;
    cout << "These files should contain some text." << endl;
    cout << "Db-Link will insert the contents of the files" << endl;
    cout << "into the database  and then ask you for 2 destination files"
	 << endl;
    cout << "in order to save the retrieved data into those files." << endl;
    cout << endl;
  
    // Text insertions.
    AskFile(str, 1, IlFalse);
    if (!str[0])
	IldEndSample(dbms, request, DropStr, 0, 1);
    ifstream inFile(str, ios::in
#ifdef WINDOWS
#if !defined(IL_STD) && !defined(__BORLANDC__)
		    | ios::nocreate
#endif
		    | ios::binary
#endif
		    );
    if (!inFile) {
	cout << str << " is either unreadable or unreachable !" << endl;
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    if (!IldInsertLongText("1st Text", request, inFile, lobType)) {
	IldDisplayError("Cannot insert text:", request);
	inFile.close();
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    inFile.close();
    cout << endl;
  
    AskFile(str, 0, IlFalse);
    if (!str[0])
	IldEndSample(dbms, request, DropStr, 0, 1);
    inFile.open(str, ios::in
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
    if (!IldInsertLongText("2nd Text", request, inFile, lobType)) {
	IldDisplayError("Cannot insert text:", request);
	IldEndSample(dbms, request, DropStr, 0, 1);
    }
    cout << endl;

    // !!! getColLongTextValue() can not be executed on a CLOB type.
    if (strncmp(lobType, "CLOB", 4)) {
	// We extract and print the first text.  
	cout << "Retrieving the small text : " << endl;
	do {
	    if (!request->execute("select TVAL, NAME from DBLTEXT where NAME='A Text'")) {
		IldDisplayError("Selection failed: ", request);
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	} while (!request->isCompleted());
	IlInt size = 0;
	while (request->fetch().hasTuple() ||
	       !request->isCompleted())
	    if (request->isCompleted()) {
		const char* s = request->getColLongTextValue(0, 0, &size);
		cout << (s ? s : "") << endl;
		if (request->isErrorRaised())
		    IldDisplayError("GetLongText failed:", request);
		else
		    cout << "Size: " << size << endl;
	    }
	cout << endl;
    }
  
    IldDbms* dbms2 = 0;
    IldRequest* request2 = 0;
    if (!dbms->isAsync())
	request2 = request;
    else {
	// We may run the two requests together,
	// But we have to do it using two different connections.
	dbms2 = IldNewDbms(argv[1], argv[2]);
	if (dbms2->isErrorRaised()) {
	    IldDisplayError("Second connection failed :", dbms2);
	    delete dbms2;
	    IldEndSample(dbms, request, DropStr, 0, 1);
	} else {
	    if (!dbms2->setAsync(IlTrue)) {
		IldDisplayError("Could not switch Asynchronous mode ON.",
				dbms2);
		delete dbms2;
		IldEndSample(dbms, request, DropStr, 0, 1);
		exit(1);
	    }
	    if (!dbms2->isAsync()) {
		IldDisplayError("Asynchronous mode is not turned ON.", dbms2);
		delete dbms2;
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	    request2 = dbms2->getFreeRequest();
	    if (dbms2->isErrorRaised()) {
		IldDisplayError("Could not get second request", dbms2);
		delete dbms2;
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	    // For some Dbms, commit is required to access the inserted data
	    // from an other request.
	    if (strncmp(dbms->getName(), "mssql", 5))
		if (!dbms->commit(request))
		    IldDisplayError("Could not commit data.", dbms);
	}
    }
    IlBoolean firstRun = IlTrue; // To control the end of the two
    // queries when they are ran asynchronously together.
    do {
	// We extract the first big text.
	if (firstRun)
	    AskFile(str, 1, IlTrue);
	if (firstRun || !request->isCompleted())
	    if (!request->getLargeObject("DBLTEXT", "TVAL", "NAME = '1st Text'",
					 str)) {
		IldDisplayError("Text retrieval failed:", request);
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	if (firstRun)
	    cout << endl;
  
	// We extract the 2nd text.
	if (firstRun)
	    AskFile(str2, 0, IlTrue);
	if (firstRun || !request2->isCompleted())
	    if (!request2->getLargeObject("DBLTEXT", "TVAL", "NAME = '2nd Text'",
					  str2)) {
		IldDisplayError("Text retrieval failed:", request2);
		IldEndSample(dbms, request, DropStr, 0, 1);
	    }
	if (firstRun) {
	    cout << endl;
	    firstRun = IlFalse ;
	}
    } while (!request->isCompleted() ||
	     !request2->isCompleted());
    if (dbms2)
	delete dbms2;
  
    request->closeCursor();
    // Table destruction and disconnection.
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
    return 0;
}
