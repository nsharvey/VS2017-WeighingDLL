// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/error.h
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
// Declaration of the IlvStError class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Error_H
#define __IlvSt_Error_H

#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

class IlvStudio;

typedef enum IlvStErrorType {
    IlvStNoErrorType, 
    IlvStInformation, 
    IlvStWarning, 
    IlvStFatal
} _IlvStErrorType;

class ILVSTUDIOCLASS IlvStError
{
public:
  IlvStError(const char* message = 0,IlvStErrorType type = IlvStInformation,
	     IlBoolean popup = IlFalse);
  ~IlvStError();

  IlvStErrorType getType() const;

  const char* getMessage() const;

  void setMessage(const char* msg) { IlvStSetString(_msg, msg); }
  void setPopup(IlBoolean pp) { _popup = pp; }

  IlBoolean isPopup() const;
private:
  char*          _msg;
  IlvStErrorType _type;
  IlBoolean	 _popup;
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStErrorHistory
{
public:
    IlvStErrorHistory(IlvStudio*, IlUShort max);
    virtual ~IlvStErrorHistory();
    // ____________________________________________________________
    void empty();
    void add(IlvStError* error);
    IlvStError* getLastError();
    void apply(IlvStErrorHistoryFunction, IlAny arg);
    const IlvStError* const* getErrors() const
	{ return (const IlvStError* const*)_errors; }
    IlUShort	getMaxLength() const { return _max; }
    IlUShort	getCurrentIndex() const { return _currentIndex; }
private:
    IlvStudio*	    _editor;
    IlvStError**    _errors;
    IlUShort	    _max;
    IlUShort	    _currentIndex;
};

// --------------------------------------------------------------------------
#endif /* ! __IlvSt_Error_H */

