// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/blob.cpp
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
// This program shows how to store and restore large amounts of binary data.
//
// Each text is sent into one record stored in a table.
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
// NB: + The type of the column BLOB is a feature of Oracle and Informix IUS
//        only.
//     + It may store twice the capacity of a raw : 4 Gb.
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

extern int processLob(char** argv,
		      IldDbms* dbms,
		      const char* lobType);

// -----------------------------------------------------------------------
// main function
// -----------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    static const char* lobType = "BLOB" ;
    // For DB2, we have to specify max LOB size :
    static const char* db2LobType = "BLOB(2M)" ;
    if (((argc != 3) && (argc != 4)) ||
	((argc > 1) && (strncmp(argv[1], "db2", 3) &&
			strncmp(argv[1], "informix", 8) &&
			strncmp(argv[1], "oracle", 6) &&
			strcmp(argv[1], "mysql")))) {
	cout << "Usage: " << argv[0]
	     << " {db2[9x]|informix[9]|oracle{11 | 10 | 9}} <connection string> [async_mode_ON]"
	     << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl ;
	return 1;
    }
  
    IldDisplayHeader("BLOB handling");
  
    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
  
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    const char* useLobType = 0;
    if (!strncmp(dbms->getName(), "db2", 3))
	useLobType = db2LobType;
    else
	useLobType = lobType;
    processLob(argv, dbms, useLobType);
    return 0;
}
