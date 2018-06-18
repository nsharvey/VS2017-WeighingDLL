// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/runner/include/main.h
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
#ifndef __main__header__
#define __main__header__

#include <ilviews/gadgets/gadgets.h>

#include <ivstudio/studapp.h>

#ifndef __Ili_Allgad_H
#  include <ilviews/dataccess/gadgets/allgad.h>
#endif

#ifndef __Ili_Dbgantt_H
#  include <ilviews/dataccess/gadgets/dbgantt/dbgantt.h>
#endif

#ifndef __Ili_Dbgraphe_H
#  include <ilviews/dataccess/gadgets/dbgraphe.h>
#endif

#ifndef __Ili_Cxncombo_H
#  include <ilviews/dataccess/gadgets/cxncombo.h>
#endif

#ifndef __Ili_Repview_H
#  include <ilviews/dataccess/gadgets/sqlrepvw.h>
#endif

#ifndef __Ili_Sqldtsrc_H
#  include <ilviews/dataccess/gadgets/sqldtsrc.h>
#endif

#ifdef IL_STD
#include <fstream>
#else
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class Runner: public IlvStudioApplication 
{
public:
  Runner(const char* appName,
	 const char* displayName = 0,
	 int argc = 0,
	 char** argv = 0);
  Runner(IlvDisplay* display,
	 const char* appName);
  ~Runner();
  
  virtual IlvBoolean	read(IL_STDPREF istream&);
  IlvBoolean		readFile(const char* fname);
};

#endif /* !__main__header__*/
