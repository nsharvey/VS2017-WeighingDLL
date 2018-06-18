// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/ildbin.cpp
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
// This program shows how to store in, and retrieve from, a database large
// amounts of binary data.
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

extern int
processLob(char** argv,
	   IldDbms* dbms,
	   const char* lobType);

// -----------------------------------------------------------------------
// main function
// -----------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0] 
	     << " <RDBMS> <connection string> [async_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }
    IldDisplayHeader("Long binary handling");  
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed", 1);
    cout << endl;
    // Set Autocommit mode ON for ODBC.
    if (!strcmp(argv[1], "odbc"))
	if (!dbms->autoCommitOn())
	    IldEndSample(dbms, 0, 0, "Switch autoCommit mode failed.", 1);
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    char lobType[128];
    ostrstream ostr(lobType, 128);
    ostr << IldGetLongBinaryTypeName(dbms)
	 << (!strcmp(dbms->getName(), "sybase") ||
	     !strcmp(dbms->getName(), "mssql") ? " null" : "") << ends;
    processLob(argv, dbms, lobType);
    return 0;
}
