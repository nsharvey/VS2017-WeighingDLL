// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/command.h
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
// Declaration of the IlvStCommand class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Command_H
#define __IlvSt_Command_H

#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif

class IlvStError;

class ILVSTUDIOCLASS IlvStCommand
{
public:
  virtual ~IlvStCommand();

  virtual IlvStError* doIt(IlvStudio* editor, IlAny arg) = 0;
  virtual IlvStError* unDo(IlvStudio* editor);
}; // class ILVSTUDIOCLASS IlvStCommand

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStFunction
: public IlvStCommand {
public:
    IlvStFunction(IlvStCommandFunction cb): _callback(cb) {};
    IlvStError* doIt(IlvStudio*, IlAny);
protected:
    IlvStCommandFunction   _callback;
}; // class IlvStCallbackCommand

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCommandPackage
: public IlvStNamedObject {
public:
    IlvStCommandPackage(const char* name) : IlvStNamedObject(name) {};
    virtual IlvStError* execute(IlvStudio*, IlAny caller);
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStStringCommandPackage
: public IlvStCommandPackage
{
public:
    IlvStStringCommandPackage(const char* name, const char* arg);
    virtual ~IlvStStringCommandPackage();
    virtual IlvStError* execute(IlvStudio*, IlAny caller);
protected:
    char* _arg;
};

// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
#endif /* ! __IlvSt_Command_H */
