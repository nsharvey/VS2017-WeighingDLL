// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/oracurs.cpp
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
// Since Oracle stored procedures can not return a results set, here is 
// demonstrated how to get an undefined number of rows returned.
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _CSTDIO_
#  include <cstdio>
# endif
# ifndef _CSTDLIB_
#  include <cstdlib>
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
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

IL_STDUSE

// ----------------------------------------------------------------------------
// SQL queries
// ----------------------------------------------------------------------------
const char* createTbl = "create table curstab (col1 varchar(12), col2 \
number(9))";

const char* insertTbl = "insert into curstab values (:1, :2)";

const char* packDecl = "CREATE OR REPLACE PACKAGE my_curs AS\
  TYPE Ctabrec IS record (col1 curstab.col1%type,\
                          col2 curstab.col2%type);\
  TYPE curstype is ref cursor return ctabrec;\
\
  PROCEDURE cursproc(\
            curs in out curstype,\
            num in number);\
END my_curs;";

const char* packBody = "CREATE OR REPLACE PACKAGE BODY my_curs AS\
  PROCEDURE cursproc (curs in out curstype,\
		      num in number) IS\
  BEGIN\
   open curs for \
   select col1, col2 from curstab \
   where col2 > num; \
  END cursproc;\
END my_curs;";

const char* PlSqlBlock = "\
BEGIN \
my_curs.cursproc(:CURS, :NUM); \
END;";

const char* packDrop = "drop package my_curs";
const char* tabDrop = "drop table curstab";

// ----------------------------------------------------------------------------
// Cleaning up
// ----------------------------------------------------------------------------
void
DropTable (IldDbms* dbms)
{
    if (!dbms->execute(tabDrop))
	IldDisplayError("Cannot drop table", dbms);
}

void 
Ending (IldDbms* dbms,
	IldRequest* request,
	const char* msg,
	int status)
{
    if (!dbms)
	cout << "Internal Error: Null Dbms!" << endl;
    else {
	if (dbms && dbms->isErrorRaised())
	    IldDisplayError(msg, dbms);
	else if (request && request->isErrorRaised())
	    IldDisplayError(msg, request);
	else 
	    cout << msg << endl;
	if (!dbms->execute(packDrop))
	    IldDisplayError("Cannot drop package", dbms);
	DropTable(dbms);
    }
    IldEndSample(dbms, request, 0, 0, status);
}

// --------------------------------------------------------------------
// main function
// --------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if (argc != 3) {
	cout << "Usage: (only Oracle) " << argv[0]
	     << " oracle" << " <connection string>" << endl;
	return 1;
    }
    IldDisplayHeader("Oracle stored procedure returning a cursor");
  
    // ------------------------------------
    // Connection and cursor allocation
    // ------------------------------------
    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed: ", 1);
    
    // ------------------------------------
    // Create and populate table
    // ------------------------------------
    cout << "Table creation: " << createTbl << endl;
    if (!request->execute(createTbl))
	IldEndSample(dbms, request, 0, "Cannot create table", 1);
    if (!request->parse(insertTbl))
	IldEndSample(dbms, request, tabDrop, "Insert parsing failed", 1);
    if (!request->bindParam((IlUShort)0, IldStringType, 12))
	IldEndSample(dbms, request, tabDrop, "Bind param #0 failed", 1);
    if (!request->bindParam(1, IldIntegerType))
	IldEndSample(dbms, request, tabDrop, "Bind param #1 failed", 1);

    const char* col1Values[] = {"One", "Two", "Three", "Four"};
    IlInt i = 0;
    for (; i < 4 ; ++i) {
	request->setParamValue(col1Values[i], 0);
	request->setParamValue(i, 1);
	if (!request->execute())
	    IldEndSample(dbms, request, tabDrop, "Execute failed", 1);
    }
  
    // ------------------------------------
    // Create package declaration and body
    // ------------------------------------
    cout << "Package creation" << endl;
    if (!request->execute(packDecl))
	IldEndSample(dbms, request, tabDrop, "Package declaration failed:", 1);
    cout << "Package body creation" << endl;
    if (!request->execute(packBody))
	Ending(dbms, request, "Package body creation failed:", 1);
  
    // ------------------------------------
    // Stored procedure call
    // ------------------------------------
    cout << "Parsing PL/SQL block : " << PlSqlBlock << endl;
    if (!request->parse(PlSqlBlock))
	Ending(dbms, request, "Parse failed: ", 1);
    
    cout << "Binding parameter :CURS of type cursor" << endl;
    if (!request->bindParam(":CURS", IldCursorType))
	Ending(dbms, request, "Binding CURS: ", 1);
    
    cout << "Binding parameter :NUM of type integer" << endl;
    if (!request->bindParam(":NUM", IldIntegerType))
	Ending(dbms, request, "Binding :NUM ", 1);
    
    request->setParamValue((IlInt)2, 1);
    cout << "Executing procedure call" << endl;
    if (!request->execute())
	Ending(dbms, request, "Execution failed: ", 1);
  
    // ------------------------------------
    // Results from returned cursor
    // ------------------------------------
    cout << "Results from procedure call : " << endl;
    IldRequest* r2 = request->getParamCursorValue(0);
    if (!r2->isErrorRaised()) {
	if (!r2->fetch())
	    IldDisplayError("Fetch failed", r2);
	else if (r2->hasTuple()) {
	    IldPrintTuple(r2, IldNames);
	    IldPrintTuple(r2, IldSeparators);
	    IldPrintTuple(r2);
	    while (r2->fetch().hasTuple())
		IldPrintTuple(r2);
	    if (r2->isErrorRaised())
		IldDisplayError("Fetch failed:", r2);
	}
    } else
	IldDisplayError("Procedure cursor: ", r2);    

    // Clean up and exit
    Ending(dbms, request, "End of sample: exiting ...", 0);
}
