// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/dbms/session.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
#ifndef __Ili_Compat_Session_H
#define __Ili_Compat_Session_H

#include <ilviews/dataccess/dbms/session.h>

#ifdef ILI_COMPAT_PREFIX
// -- 1.1 Compatibility
#define IlvSwQueryConnectFlag  IliSQLQueryConnectFlag
#define IlvSwQueryPasswordOnly IliSQLQueryPasswordOnly
#define IlvSwQueryIfNeeded     IliSQLQueryIfNeeded
#define IlvSwQueryAlways       IliSQLQueryAlways
// -- 2.0 Comaptibility
#define ILVSWINITDBMS ILIINITDBMS
#define IlvSwSQLQueryConnectFlag IliSQLQueryConnectFlag
#define IlvSwSQLQueryPasswordOnly IliSQLQueryPasswordOnly
#define IlvSwSQLQueryIfNeeded IliSQLQueryIfNeeded
#define IlvSwSQLQueryAlways IliSQLQueryAlways
#define IlvSwSQLSessionEvent IliSQLSessionEvent
#define IlvSwSQLSessionDisconnect IliSQLSessionDisconnect
#define IlvSwSQLSessionCommit IliSQLSessionCommit
#define IlvSwSQLSessionRollback IliSQLSessionRollback
#define IlvSwSQLSessionCallback IliSQLSessionCallback
#define IlvSwSQLSession IliSQLSession
#ifdef ILI_DBMS_DEFINED
#  define ILVSW_DBMS_DEFINED
#endif
#endif

#endif
