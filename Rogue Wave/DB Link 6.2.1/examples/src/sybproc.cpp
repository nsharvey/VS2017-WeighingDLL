// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/sybproc.cpp
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
// This program shows how to create then call a stored procedure against
// a SYBASE database with Rogue Wave DB Link.
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
const char* testStr = "if exists (select obj.name \
from sysobjects obj, sysusers owner \
where obj.uid = owner.uid and owner.name = user and \
type = \"P\" and obj.name = \"dbl_proc\") \
Begin	\
drop proc dbl_proc	\
End ";

const char* createStr = "create proc dbl_proc (@intparam int, \
@sintparam smallint output, @floatparam float output, \
@charparam char(20) output) \
as \
select @intparam, @sintparam, @floatparam, @charparam \
select @sintparam = @sintparam + @intparam \
select @floatparam = @floatparam + @intparam \
select @charparam = \"A small string\" \
print \"The procedure dbl_proc has been executed.\"";

// Warning : there are two restrictions when using stored procedures within
//           Db Link on Sybase Client Library :
//            1/ despite the fact the statement must be "parse"d it cannot
//               be executed several times 
//            2/ the "execute" SQL reserved word is mandatory, it is used as
//               the only indicator of a procedure call during the parsing
//               phase. If the procedure call only needs input parameter(s)
//               you can simply use the execute(const char*) member function
//               passing the parameter value(s) in the query string.
//               Example : request->execute("sp_helpdb mydb");
const char* execStr = "execute dbl_proc";

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 2) && (argc != 3)) {
	cout << "Usage: " << argv[0]
	     << " <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }

    IldDisplayHeader("Sybase stored procedure");

    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect("sybase", argv[1]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Create Dbms: ", 1);
    cout << endl;
    if (argc == 3) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }    
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Request allocation failed:", 1);
    
    cout << "Dropping the procedure if it exists." << endl;
    do {
	if (!request->execute(testStr))
	    IldEndSample(dbms, request, 0, "Drop procedure failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;

    cout << "Creating procedure : " << endl
	 << createStr << endl;
    do {
	if (!request->execute(createStr))
	    IldEndSample(dbms, request, 0, "Procedure creation failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    cout << "Parsing procedure call : " << endl
	 << "\t" << execStr << endl;
    do {
	if (!request->parse(execStr))
	    IldEndSample(dbms, request, testStr, "Parsing failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    cout << "Binding parameters : " << endl;
    cout << " @intparam" << endl;
    if (!request->bindParam("@intparam", IldIntegerType))
	IldEndSample(dbms, request, testStr, "Bind of @intparam failed: ", 1);
    cout << " @sintparam" << endl;
    if (!request->bindParam("@sintparam", IldIntegerType, -1, 0, 0, IlTrue))
	IldEndSample(dbms, request, testStr, "Bind of @sintparam failed: ", 1);
    cout << " @floatparam" << endl;
    if (!request->bindParam("@floatparam", IldRealType, -1, 0, 0, IlTrue))
	IldEndSample(dbms, request, testStr,
		     "Bind of @floatparam failed: ", 1);
    cout << " @charparam" << endl;
    if (!request->bindParam("@charparam", IldStringType, 21, 0, 0, IlTrue))
	IldEndSample(dbms, request, testStr, "Bind of @charparam failed: ", 1);
    cout << endl;
    
    cout << "Setting parameter values : " << endl;
    IlInt intpar = 15;
    cout << " @intparam : " << intpar << endl;
    request->setParamValue(intpar, 0);
    IlInt sintpar = 23;
    cout << " @sintparam : " << sintpar << endl;
    request->setParamValue(sintpar, 1);
    double fltpar = (double)3.14159265358979;
    cout << " @floatparam : " << fltpar << endl;
    request->setParamValue(fltpar, 2);
    
    // If somebody can explain this one : on PC, the OUTPUT parameter
    // charparam MUST be bound using a buffer not exclusively composed of null 
    // chars !! 
    // Otherwise, ct_param fails with an INFORMATIONAL message about 
    // parameters names !!!!!!
    const char* charp = "                   ";
    request->setParamValue(charp, 3);
    cout << endl;
  
    cout << "Executing the procedure" << endl;
    do {
	if (!request->execute())
	    IldEndSample(dbms, request, testStr, "Execute failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;
  
    cout << "Results from procedure call : " << endl;
    cout << "\tParameter input values :" << endl;
    cout << "@sintparam  : " << request->getParamIntegerValue(1) << endl;
    cout << "@floatparam : " << request->getParamRealValue(2) << endl;
    cout << "@charparam  : " << request->getParamStringValue(3) << endl;
    cout << endl;
    
    cout << "\tResults sets : " << endl;
    while (request->fetch().hasTuple() || !request->isCompleted())
	if (request->isCompleted()) {
	    if (request->getColCount()) {
		IldPrintTuple(request, IldNames);
		IldPrintTuple(request, IldSeparators);
		do {
		    if (request->isCompleted())
			IldPrintTuple(request);
		} while (request->fetch().hasTuple() ||
			 !request->isCompleted());
		if (request->isErrorRaised())
		    IldEndSample(dbms, request, testStr, "Fetch failed:", 1);
	    } else {
		IlInt count = 0;
		if ((count = request->getStatus()) > 0)
		    cout << count << " modified row" 
			 << ((count > 1) ? "s" : "") << endl;
	    }
	    cout << endl;
	}
    if (request->isErrorRaised())
	IldDisplayError("Fetch failed:", request);
  
    cout << "\tParameter output values :" << endl;
    cout << "@sintparam  : " << request->getParamIntegerValue(1) << endl;
    cout << "@floatparam : " << request->getParamRealValue(2) << endl;
    cout << "@charparam  : " << request->getParamStringValue(3) << endl;
    cout << endl;
    
    if (request->isInformationRaised()) {
	cout << "Information : " << endl;
	cout << "\t" << request->getInformationMessage() << endl;
    }
    cout << endl;
    
    IldEndSample(dbms, request, testStr, "Sybproc demo end.");
}
