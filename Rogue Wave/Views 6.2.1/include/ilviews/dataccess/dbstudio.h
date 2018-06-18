// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio.h
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
// Declaration of the IliDbStudio class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstudio_H
#define __Ili_Dbstudio_H

#if !defined(ILVNOJS)
#  include <ilviews/jvscript/script.h>
#endif

#ifndef __IlvSt_Lib_H
#  include <ivstudio/lib.h>
#endif

#ifndef __IlvSt_Stprop_H
#  include <ivstudio/stprop.h>
#endif

#ifndef __IlvSt_Option_H
#  include <ivstudio/option.h>
#endif

#ifndef __Ili_Allgad_H
#  include <ilviews/dataccess/gadgets/allgad.h>
#endif

#ifndef __Ili_Dbstinit_H
#  include <ilviews/dataccess/dbstudio/dbstinit.h>
#endif

// --- Script language ---
#if defined(ILVNOJS)
static void InitScriptLanguage(IlvStudio*)  {}
#else // ILVNOJS
#include <ivstudio/jslib.h>
static void
InitScriptLanguage(IlvStudio* editor) {
  new IlvStScripts(editor);
}
#endif // ILVNOJS

#endif

