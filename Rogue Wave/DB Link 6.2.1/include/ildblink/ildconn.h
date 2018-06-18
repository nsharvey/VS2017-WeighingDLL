// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildconn.h
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
// DB LINK Connection allocation.
// ----------------------------------------------------------------------------
#ifndef __ILD_ILDCONN_H
#define __ILD_ILDCONN_H

#ifndef __ILD_ILD_H
#include <ildblink/ild.h>
#endif

class IldDbms;
class IldDriver;
class IlEnvironment;

typedef IldDbms* (*IldDbmsInitFunc)(IldDriver*,
				    IlBoolean,
				    const char*,
				    const char*,
				    const char*);

typedef void (*IldInitModuleFunc)(const char*,
				  IldDbmsInitFunc);

ILD_EXPORTEDFUNCTION(char**) IldGetDataSources();

ILD_EXPORTEDFUNCTION(IlBoolean)
    IldAllocEnvironment(IlEnvironment*& env);

ILD_EXPORTEDFUNCTION(IldDbms*) IldAllocConnect(const char* dbmsName,
					       const char* connectionStr);

ILD_EXPORTEDFUNCTION(IldDbms*) IldAllocConnect(const char* dbmsName,
					       const char* database,
					       const char* userName,
					       const char* password);

// IldNewDbms kept for backward compatibility.
inline IldDbms*
IldNewDbms(const char* dbmsName,
	   const char* database,
	   const char* userName,
	   const char* password)
{
    return IldAllocConnect(dbmsName, database, userName, password);
}

inline IldDbms*
IldNewDbms(const char* dbmsName,
	   const char* connectionStr)
{
    return IldAllocConnect(dbmsName, connectionStr);
}

#endif // __ILD_ILDCONN_H
