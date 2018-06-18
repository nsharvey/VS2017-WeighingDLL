// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/sqlprop.h
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
// Declaration of the IliSQLApplicationProperties class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqlprop_H
#define __Ili_Sqlprop_H

#ifndef __IlvSt_Edappli_H
#include <ivstudio/edappli.h>
#endif

#ifndef __Ili_Dbmsdriv_H
#include <ilviews/dataccess/dbms/dbmsdriv.h>
#endif

#ifndef __Ili_Session_H
#include <ilviews/dataccess/dbms/session.h>
#endif

#ifndef __IlvSt_Stdesc_H
#  include <ivstudio/stdesc.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Cxncombo_H
#  include <ilviews/dataccess/gadgets/cxncombo.h>
#endif

#ifndef __Ili_Appprop_H
#  include <ilviews/dataccess/dbstudio/appprop.h>
#endif

class ILV_DBSSQL_EXPORTED IliSQLApplicationProperties
  : public IliApplicationProperties
{
public:
  IliSQLApplicationProperties ();
  ~IliSQLApplicationProperties ();

  static void InstallSessions (IlvStAppDescriptor*, IlvDisplay*);
  static IliTable* MakeSessionsTable (IlvDisplay*);
  static void ReadSessionsTable (IlvStAppDescriptor* appli,IliTable* fmt);
  static IlInt GetSessionsCount (IlvStAppDescriptor* appli);
  static void RemoveRegisteredSessions ();
  static void RegisterSessions (IliTable* sessions);
};

#endif
