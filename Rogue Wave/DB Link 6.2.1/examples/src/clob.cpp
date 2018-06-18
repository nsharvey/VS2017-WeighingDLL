// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/clob.cpp
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
// NB: + This is the same example as ildtext.cpp, but using the new
//       Oracle8 / Informix9 CLOB data type..
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
#endif

IL_STDUSE

extern int processLob(char** argv, IldDbms* dbms, const char* lobType);

// -----------------------------------------------------------------------
// main function
// -----------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    static const char* lobType = "CLOB" ;
    // For DB2, we have to specify max LOB size:
    static const char* db2LobType = "CLOB(2M)";
    static const char* mysqlLobType = "BLOB";
    if (((argc != 3) && (argc != 4)) ||
	((argc > 1) && (strncmp(argv[1], "db2", 3) &&
			strncmp(argv[1], "informix", 8) &&
			strncmp(argv[1], "oracle", 6) &&
			strcmp(argv[1], "mysql")))) {
	cout << "Usage: " << argv[0]
	     << " {db2[9x]} | informix[9] | oracle{9 | 10 | 11}} <connection string> [async_mode_ON]"
	     << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }
  
    IldDisplayHeader("CLOB handling");
  
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed", 1);
    cout << endl;
    
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    const char* useLobType = 0;
    if (!strncmp(dbms->getName(), "db2", 3))
	useLobType = db2LobType;
    else if (!strcmp(dbms->getName(), "mysql"))
	useLobType = mysqlLobType;
    else
	useLobType = lobType;
    processLob(argv, dbms, useLobType);
    return 0;
}
