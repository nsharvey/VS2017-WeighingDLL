// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/src/main.cpp
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
#include <app.h>

#if defined(IL_STD)
#  include <cstring>
IL_STDUSE
#else
#  include <string.h>
#endif

#define ILI_CUSTOM_NEW_DBMS_NEEDED

#include <ilviews/dataccess/home.h>
#include <ilviews/dataccess/format.h>
#include <ilviews/dataccess/gcallbak.h>
#include <ilviews/gadgets/scrdlg.h>

#include <ilviews/dataccess/dbms/session.h>

#if defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
#  include <ildblink/dblink.h>
static IldDbms* ILVCALLBACK 
CustomNewDbms(const char* dbms, const char* params)
{
    return IldAllocConnect(dbms, params);
}
#endif

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
#if defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
    IliSQLSession::SetNewDbmsFunction(CustomNewDbms);
#endif
    IliSQLSession::RegisterSession("Main", "null", "");
    IliSQLSession *sess = IliSQLSession::GetRegisteredSession("Main");

    IlvSetLanguage();
    DbApp* appli = new DbApp("withDbApp", 0, argc, argv);
    if (!appli->getDisplay()) {
        return -1;
    }
    appli->beforeRunning();
    IlPathName localPath(appli->getDisplay()->getHomePath());
    localPath.addDirectory("samples/dataccess/withdb/data");
    appli->getDisplay()->prependToPath(localPath);
    sess->queryConnect(appli->getDisplay(), NULL);
    appli->run();
    return 0;
}

