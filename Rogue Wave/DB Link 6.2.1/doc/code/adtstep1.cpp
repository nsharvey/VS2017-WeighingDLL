// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/adtstep1.cpp
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
#include <stdlib.h>

#include <ildblink/dblink.h>

// Functions defined in ADTCommon.cpp
extern void Ending(IldDbms* dbms);
extern void IldDisplayError(const char* operation,
			    const IldIldBase* ildObj);
extern char* checkCase(char* name,
		       IldDbms* dbms,
		       IldBoolean itself = IldTrue);
extern void createADT(IldDbms* dbms);
extern IldDbms* checkUsageOk(int argc,
			     char* argv[]);

// Functions defined in this file: forward declaration due to cross-reference
void displayDesc(IldDbms* dbms,
		 const IldDescriptor* desc);
void displayADT(IldDbms* dbms,
		IldADTDescriptor* adt);

// ----------------------------------------------------------------------------
void displayDesc(IldDbms* dbms,
		 const IldDescriptor* desc)
{
    cout << desc->getName() << " ";
    switch (desc->getType()) {
    case IldObjectType:
    case IldCollectionType:
	if (desc->getADTDescriptor()->isNamedType())
	    cout << "'" << desc->getSqlTypeName() << "' : ";
	displayADT(dbms, desc->getADTDescriptor());
	break;
    case IldStringType:
	cout << desc->getSqlTypeName() << " (" << desc->getSize() << ")";
	break;
    case IldIntegerType:
	cout << desc->getSqlTypeName();
	break;
    default:
	cout << "Other type : " << desc->getType() << endl;
    }
}

// ----------------------------------------------------------------------------
void displayADT(IldDbms* dbms,
		IldADTDescriptor* adt)
{
    IldUShort i = 0;
    switch (adt->getType()) {
    case IldADTObject: {
	const IldDescriptor* const* elts = 0;
	cout << "Object (";
	// We can access the various elements of the object:
	elts = adt->getAttributes();
	for (i = 0 ; i < adt->getAttributesCount() ; i++) {
	    displayDesc(dbms, elts[i]);
	    if (i < adt->getAttributesCount() - 1)
		cout << ", ";
	}
	cout << ")";
	break;
    }
    case IldADTList:
    case IldADTArray: {
	const IldDescriptor* desc = adt->getCollectionAttribute();
	if (adt->getType() == IldADTList)
	    cout << "List of {";
	else
	    cout << "List[" << adt->getCollMaxSize() << "] of {";
	displayDesc(dbms, desc);
	cout << "}";
	break;
    }
    default:
	cout << "Unexpected ADT Type." << endl;
    }
}

// ----------------------------------------------------------------------------
void runStep1(IldDbms* dbms)
{
    char ADTName[20];
    if (!strcmp(dbms->getName(), "informix9"))
	strcpy(ADTName, "BRIDGE");
    else
	// Oracle :
	strcpy(ADTName, "BRIDGELST");
    IldADTDescriptor* adt = 0;
    if (!(adt = dbms->readAbstractType(checkCase(ADTName, dbms)))) {
	IldDisplayError("Could not get ADT description : ", dbms);
	Ending(dbms);
	exit(-1);
    }
    cout << ADTName << " : ";
    displayADT(dbms, adt);
    cout << endl;
    delete adt;
}

// ----------------------------------------------------------------------------
int main(int argc,
	 char* argv[])
{
    // Check program arguments are OK, and open the connection.
    IldDbms* dbms = checkUsageOk(argc, argv);

    createADT(dbms);

    runStep1(dbms);

    Ending(dbms);

    cout << "Leaving the program ..." << endl;

    return 0;
}
