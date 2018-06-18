// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/oraproc.cpp
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
// This sample illustrates calling an ORACLE stored procedures using DB Link.
//
// The procedure takes four parameters:
//     the first one is a scalar integer and is used as an index into an array,
//     the second one is an array which gets modified by the procedure.
//     the third one is the size of the second array.
//     the fourth one is the second array, an array of integers.
//
// Parameter bindings:
// -------------------
// The parameter array size is mandatory since one of the parameter is of 
// an array type.
// The size of the bigger array has to be used to set the parameter array
// size.
// Since the first parameter is a scalar and is not null, its bind call does 
// not need to use the optional arguments for the null indicator, the input/
// output status, nor the array size. The user address of the value buffer is
// given but, because it is a fixed size value type, the default value for 
// size (-1) is given: DB Link will take care of the actual size.
// For the second parameter, a specific array size is given, using the seventh
// argument in the bind call. That size is smaller than the maximum.
// Due to the procedure execution, it is clear that the actual value of the 
// first parameter must be smaller or equal to the actual array size of the
// second parameter.
//
// Procedure execution:
// --------------------
// The procedure sets some values for some elements of the array but it also 
// sets an element to the null value as one can see when the returned array is
// printed.
//
// Remarks:
// --------
// The actual procedure call must be enclosed in an anonymous PL/SQL block.
//
// The values of the parameters are retrieved using DB Link API but the user 
// memory slots can also be accessed directly.
//
// The "nullness" of the value is tested through the DB Link API but can have 
// been checked by directly accessing the value of the user indicators which 
// where bind in.
//
// The first argument does not require that a user allocated memory space be 
// bound.
//
// The third argument of the binding of the second parameter is the actual
// user side size of ONE element of the array.
//
// The sixth arguments of the binding of the second parameter is ignored by 
// DB Link for Oracle thus its value could have been set to IldFalse without
// any change in the execution behaviour.
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
const char* packDecl = "CREATE OR REPLACE PACKAGE dbl_pckg AS\
  TYPE CharArray IS TABLE OF VARCHAR2(20)\
       INDEX BY BINARY_INTEGER;\
  TYPE IntArray IS TABLE OF INTEGER \
       INDEX BY BINARY_INTEGER ; \
\
  PROCEDURE dbl_proc(\
            myIndex in Integer,\
            myArray in out CharArray, \
            secondIndex in Integer, \
            secondArray in out IntArray);\
END dbl_pckg;";

const char* packBody = "CREATE OR REPLACE PACKAGE BODY dbl_pckg AS\
  PROCEDURE dbl_proc (myIndex in Integer,\
		      myArray in out CharArray, \
                      secondIndex in Integer, \
                      secondArray in out IntArray) IS\
  BEGIN\
    myArray(1) := null;\
    for i in 2..myIndex loop\
	myArray(i) := concat('myArray', to_char(i));\
    end loop;\
    for i in 1..secondIndex-1 loop \
        secondArray(i) := 10 * i ; \
    end loop; \
    secondArray(secondIndex) := null ; \
  END dbl_proc;\
END dbl_pckg;";

const char* PlSqlBlock = "\
BEGIN \
dbl_pckg.dbl_proc(:index, :array, :secondIndex, :secondArray); \
END;";

const char* packDrop = "drop package dbl_pckg";

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if (argc != 3) {
	cout << "Usage: " << argv[0]
	     << "oracle{9|10|11} <connection string>" << endl;
	return 1;
    }
    IldDisplayHeader("Oracle stored procedure");
  
    // ----------------------------------------
    // Connection
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed: ", 1);

  
    // ----------------------------------------
    // User memory spaces
    const int max = 21;
    const int nb_elem = 5;
    const int nb_elem2 = 10;
    const int max_nb_elem = nb_elem > nb_elem2 ? nb_elem : nb_elem2;
    char Names[nb_elem][max]; // Buffer for the table of strings.
    short iNames[nb_elem];     // Indicators for the table of strings
    IlInt integers[nb_elem2]; // Buffer for the table of integers.
    short iIntegers[nb_elem2]; // Indicators for the table of integers.
    IlInt theIndex = (IlInt)nb_elem;
    IlInt theSecondIndex = (IlInt)nb_elem2;
  
    memset(Names, 0, max * nb_elem);
    memset(iNames, 0, nb_elem);
    memset(integers, 0, nb_elem2 * sizeof(IlInt));
    memset(iIntegers, 0, nb_elem2);

    // ----------------------------------------
    // Create package declaration and body
    cout << "Procedure creation." << endl;
    if (!request->execute(packDecl))
	IldEndSample(dbms, request, 0, "Package declaration failed:", 1);
    if (!request->execute(packBody))
	IldEndSample(dbms, request, packDrop,
		     "Package body creation failed:", 1);
    cout << endl;
  
    // ----------------------------------------
    request->setParamArraySize(max_nb_elem) ;
    cout << "Parsing procedure call: " << PlSqlBlock << endl;
    if (!request->parse(PlSqlBlock))
	IldEndSample(dbms, request, packDrop, "Parse failed:", 1);
  
    // ----------------------------------------
    cout << "Binding parameter :INDEX of type integer" << endl;
    if (!request->bindParam(":INDEX", IldIntegerType, -1, &theIndex))
	IldEndSample(dbms, request, packDrop, "Binding index:", 1);
    cout << "Binding parameter :ARRAY of type array of varchar" << endl;
    if (!request->bindParam(":ARRAY", IldStringType,
			    (IlInt)(max * sizeof(char)), Names,
			    iNames, IlTrue, nb_elem))
	IldEndSample(dbms, request, packDrop, "Binding array:", 1);
    cout << "Binding parameter :SECONDINDEX of type integer" << endl ;
    if (!request->bindParam(":SECONDINDEX", IldIntegerType,
			    -1, &theSecondIndex))
	IldEndSample(dbms, request, packDrop, "Binding second index : ", 1);
    cout << "Binding parameter :SECONDARRAY of type array of integers" << endl;
    if (!request->bindParam(":SECONDARRAY", IldIntegerType,
			    (IlInt)sizeof(IlInt), integers,
			    iIntegers, IlTrue, nb_elem2))
	IldEndSample(dbms, request, packDrop, "Binding second array:", 1);

    // ----------------------------------------
    cout << "Executing procedure call" << endl;
    if (!request->execute())
	IldEndSample(dbms, request, packDrop, "Execution failed:", 1);
    cout << endl;

    // ----------------------------------------
    // Results
    cout << "Results from procedure call:" << endl;
    cout << ":index is " << request->getParamIntegerValue(0) << endl;
    int i = 0;
    cout << ":array is : " << endl ;
    for (i = 0 ; i < theIndex ; ++i) {
	cout << "\tNames[" << i << "]= ";
	if (request->isParamNull((IlUShort)1, (IlUShort)i))
	    cout << "null";
	else
	    cout << request->getParamStringValue((IlUShort)1, (IlUShort)i);
	cout << endl;
    }
    cout << ":secondIndex is " << request->getParamIntegerValue(2) << endl;
    cout << ":secondArray is : " << endl;
    for (i = 0 ; i < theSecondIndex ; ++i) {
	cout << "\tIntegers[" << i << "] = ";
	if (request->isParamNull((IlUShort)3, (IlUShort)i))
	    cout << "null";
	else
	    cout << request->getParamIntegerValue((IlUShort)3, (IlUShort)i);
	cout << endl;
    }
    
    // Cleaning up and exiting
    IldEndSample(dbms, request, packDrop, "End of sample");
}
