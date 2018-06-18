// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/runner/src/main.cpp
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
#define ILI_CUSTOM_NEW_DBMS_NEEDED

#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/jvscript/script.h>

#if defined(IL_STD) || defined(ILVSTD)
#  include <cstring>
#  include <fstream>
#else
#  include <string.h>
#  include <fstream.h>
#endif

#ifdef IL_STD
#include <strstream>
#else
#ifdef ILVFATFILENAMES
#  include <strstrea.h>
#else
#  include <strstream.h>
#endif
#endif

#include <ilviews/dataccess/home.h>
#include <ilviews/dataccess/format.h>
#include <ilviews/dataccess/inpmask.h>
#include <ilviews/dataccess/gcallbak.h>
#include <ilviews/dataccess/dbms/session.h>
#include <ilviews/dataccess/gadgets/allgad.h>
#include <ilviews/dataccess/dbstudio/appprop.h>
#include <ilviews/dataccess/dbstudio/sqlprop.h>
#include "main.h"

IL_STDUSE

#if defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
#  include <ildblink/dblink.h>
static IldDbms* ILVCALLBACK 
CustomNewDbms (const char* dbms, const char* params) {
    return IldNewDbms(dbms, params);
}
#endif

// --------------------------------------------------------------------------
static void ILVCALLBACK 
InitDataAccess (IlvDisplay* display) {
  IliAppendDataAccessPath(display);
  IliFormat::ReadMessageDatabase(display, "dataccess/dataccess.dbm");
  IliFormat::ReadMessageDatabase(display, "dataccess/date.dbm");
  IliFormat::ConnectToMessageDatabase(display);
  IliErrorMessage::ConnectToMessageDatabase(display);
  IliFormat::ReadMessageDatabase(display,"dataccess/dblink.dbm");
  IliSQLSession::ConnectToMessageDatabase(display);
  #if defined(ILI_CUSTOM_NEW_DBMS_NEEDED)
    IliSQLSession::SetNewDbmsFunction(CustomNewDbms);
  #endif
}

// --------------------------------------------------------------------------
static IlvBoolean
InputFileName(IlvDisplay* dpy, IliString& filename) {
  const char* filters[1];
  const char* messages[1];
  filters[0] = "*.iva";
  messages[0] = "Application Files (*.iva)";
  IlvFileBrowser dlg(dpy,
		     NULL,
		     "",                    /* dir           */
		     1,                     /* filters count */
		     filters,               /* filters       */
		     messages,              /* messages      */
		     IlvUseDefault);
  dlg.setType(IlvFileSelectorLoad);
  dlg.setDirectory("../data");
  dlg.moveToScreen(IlvCenter,
		   0,
		   0,
		   IlvTrue);
  const char* fname = dlg.get();
  if (fname && *fname) {
    filename = fname;
    return IlvTrue;
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
static void
ErrorBox(IlvDisplay* display, const char* msg) {
  IlvIErrorDialog dlg(display, msg);
  dlg.moveToScreen(IlvCenter,
		   0,
		   0,
		   IlvTrue);
  dlg.get();
}

// --------------------------------------------------------------------------
static void
Usage(IlvDisplay* display) {
  ErrorBox(display, "usage: runner [-noexitpanel] [filename.iva]");
}

// --------------------------------------------------------------------------

static void
ReadPropertySetDefinitions(IlvDisplay* display) {
  const char* home = display->getHome();
  if (home) {
    IliString path;
    path << home << "/studio/data/ivstudio";
    display->appendToPath((const char*)path);
  }

  IliString filename = display->findInPath("stprops.opt");

  IlvStTopPropertySet global(IlvGetSymbol("runner"));
  IlvBoolean result = global.readFile((const char*)filename);
  IlvArray array;
  global.takeAll(array);
}

// --------------------------------------------------------------------------
Runner::Runner(const char* appName,
	       const char* displayName,
	       int argc,
	       char** argv)
: IlvStudioApplication(appName, displayName, argc, argv)
{
    if (getDisplay())
        InitDataAccess(getDisplay());
}

// --------------------------------------------------------------------------
Runner::Runner(IlvDisplay* display,
	       const char* appName)
: IlvStudioApplication(display, appName, IlvTrue)
{
    if (getDisplay())
        InitDataAccess(getDisplay());
}

// --------------------------------------------------------------------------
Runner::~Runner()
{}

// --------------------------------------------------------------------------
IlvBoolean
Runner::readFile(const char* fname) {
   IlvBoolean ok = IlvStudioApplication::read(fname, IlvFalse);
   getDescriptor()->setFileName(fname);
   IlvScriptContext::GetGlobal()->bind(this, "Application");

   return ok;
}

// --------------------------------------------------------------------------
IlvBoolean 
Runner::read(istream& file) {
  IlvBoolean res = IlvStudioApplication::read(file);
  if (res) {
    IlvStAppDescriptor *desc = getDescriptor();
    IliApplicationProperties::InstallNumbers(desc);
    IliApplicationProperties::InstallDates(desc);
    IliApplicationProperties::InstallFormatAliases(desc, getDisplay());
    IliApplicationProperties::InstallMaskAliases(desc, getDisplay());
    IliSQLApplicationProperties::InstallSessions(desc, getDisplay());
  }
  return res;
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
extern "C" IlvBoolean IlvSetLanguage();

int main (int argc, char* argv[]) {
  IlvBoolean exitPanel = IlvTrue;
  IliString filename;
  
  // --- Display ---
  IlvDisplay* display = new IlvDisplay("runner", "", argc, argv);
  if (display->isBad()) {
    IlvFatalError("Couldn't open display");
    delete display;
    return -1;
  }
  
  ReadPropertySetDefinitions(display);

  // --- Parse Arguments ---
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-noexitpanel") == 0)
      exitPanel = IlvFalse;
    else if (!filename.isNull()) {
      Usage(display);
      return -1;
    }
    else
      filename = argv[i];
  }
  if (filename.isNull()) {
    if (!InputFileName(display, filename))
      return 0;
  }
  
  IlvSetLanguage();
  Runner* runner = new Runner(display, "runner");
  if (!runner->getDisplay())
    return -1;

  runner->setUsingExitPanel(exitPanel);
  if (runner->readFile(filename))
    runner->run();
  else {
    IliString msg;
    msg << "File not found: " << filename;
    ErrorBox(display, msg);
    return -1;
  }

  IlvStProperty::GlobalClean();

  return 0;
}


