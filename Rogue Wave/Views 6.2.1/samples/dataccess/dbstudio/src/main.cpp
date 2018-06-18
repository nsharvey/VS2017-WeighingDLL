// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/dbstudio/src/main.cpp
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

#if !defined(ILVNODEFAULTLOOK)
#include <ilviews/windows.h>
#include <ilviews/win95.h>
#include <ilviews/motif.h>
#endif
#include <ivstudio/stlibini.h>
#include <ilviews/base/error.h>

#ifdef IL_STD
#include <clocale>
#else
#include <locale.h>
#endif


//---- To Use Old Charts ----
// To use the old charts with Dbstudio, you must:
// * Define the flag ILI_USE_OLD_CHARTS at the beginning of this source file.
// The code line is: #define ILI_USE_OLD_CHARTS
// * Modify the makefile of dbstudio to:
//   - Add the views31 library.
//   - Replace the dbchart library by dbchart30 library.
//   - Replace the dbstchart library by dbstchart30 library.
//   - Supress the ilvcharts and ilvstcharts libraries.
//   - Add the include path for chart: 
//     $(ILVHOME)/inform30/include
//   - Add the include path for Views 3.1: 
//     $(ILVHOME)/views31/include
//   - Add the library path for chart: 
//     $(ILVHOME)/inform30/lib/$(PLATFORM)/$(FORMAT)
//   - Add the studio library path for chart: 
//     $(ILVHOME)/inform30/studio/$(PLATFORM)/$(FORMAT)
//   - Add the library path for libraries of Views 3.1: 
//     $(ILVHOME)/views31/lib/$(PLATFORM)/$(FORMAT)
// NOTE: You can not create a dbstudio with the both versions of chart.
// * 
//----

#ifndef __Ili_Dbstudio_H
#  include <ilviews/dataccess/dbstudio.h>
#endif

#ifndef __Ili_Dbstgrap_H
#  include <ilviews/dataccess/dbstudio/dbstgrap.h>
#endif

#ifdef ILI_USE_OLD_CHARTS
#  include <inform/dbstudio/dbstoldchart.h>
#else
#  ifndef __Ili_Dbstchart_H
#    include <ilviews/dataccess/dbstudio/dbstchart.h>
#  endif
#endif

#ifndef __Ili_Dbstgant_H
#  include <ilviews/dataccess/dbstudio/dbstgant.h>
#endif

#ifndef __Ili_Dbstsql_H
#  include <ilviews/dataccess/dbstudio/dbstsql.h>
#endif


extern "C" {
  ILVDSPEXPORTEDFUNCTION(IlBoolean) IlvSetLanguage();
}

// --------------------------------------------------------------------------
// main
// --------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  // --- set locale according to environment variables ---
  IlvSetLanguage();

  // --- Display ---
  IlvDisplay* display = new IlvDisplay("dbstudio", "", argc, argv);
  if (display->isBad()) {
    IlvFatalError("Couldn't open display");
    delete display;
    return 1;
  }

  // --- Dbms ---
  BindDbmsDrivers();

  // ---- Create and initialize the editor ---
  IlvStudio* editor = new IlvStudio(display, argc, argv);
  if (editor->isBad()) {
    IlvFatalError("Could not initialize the editor");
    delete display;
    return 2;
  }

  InitScriptLanguage(editor);
  new IliDataAccessExtension(editor);
  new IliSQLExtension(editor);
#ifdef ILI_USE_OLD_CHARTS
  new IliDbGrapherExtension(editor);
  new IliDbGanttExtension(editor);
  new IliDbOldChartExtension(editor);
#else
  new IliChartExtension(editor);
  new IliDbGrapherExtension(editor);
  new IliDbGanttExtension(editor);
#endif

  editor->initialize();
  editor->parseArguments();
  editor->mainLoop();

  return 0;
}





