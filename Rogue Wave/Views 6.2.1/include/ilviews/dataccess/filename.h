// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/filename.h
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
// Declaration of the IliFileName class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Filename_H
#define __Ili_Filename_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#include <ctime>
#else
#include <time.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

class ILV_INF_EXPORTED IliFileName {
public:
  IliFileName (const char* = 0);
  IliFileName (const IliFileName&);

  IliFileName& operator = (const IliFileName& o);

  IlBoolean isEmpty () const { return _pathname.isNull(); }
  void set (const char*);
  void empty ();
  void resetTime ();

  const char* getFilePart () const;
  const char* getDirectoryPart () const;
  const char* getPathName () const;

  IlBoolean exists () const;
  IlBoolean isReadable () const;
  IlBoolean isWritable () const;
  IlBoolean hasChangedOnDisk () const;

  void forceExtension (const char* extension);

protected:
  IliString _filePart;
  IliString _directoryPart;
  IliString _pathname;
  time_t _mtime;
};

#endif




