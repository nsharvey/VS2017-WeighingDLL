// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/trace.h
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
// Declaration of the IlvSuTrace class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Trace_H
#define __Ilv_States_Trace_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif

// this file implements a trace feature
// a IlvSuTrace instance displays a string when constructed
// and also when deleted
// It can thus be used to trace the entry and exit of blocks.
// the use of the destructor permits not to care for how many return
// statements there are

// The TR macro below builds such an object in a simple way
#if !defined(DEBUG)
#  if !defined(NDEBUG)
#    define NDEBUG
#  endif /* NDEBUG */
#else  /* !DEBUG */
#  undef NDEBUG
#endif /* !DEBUG */
#ifdef NDEBUG
#  define NTRACE
#endif

#if !defined(NTRACE)
#  if !defined(__iostream_h__)
#    if defined(ILVSTD)
#      include <iostream>
#    else  /* !ILVSTD */
#      include <iostream.h>
#    endif /* !ILVSTD */
#    define __iostream_h__
#  endif
#  define ILVSTATES_FULLTRACE(expr) cout <<  #expr " IS: " << expr << endl;
#  define ILVSTATES_TRACE(expr) cout << expr << endl;
#else  /* NTRACE */
#  define ILVSTATES_FULLTRACE(ignore)
#  define ILVSTATES_TRACE(ignore)
#endif /* NTRACE */

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSuTrace
{
    char* _block;
    char* _file;
    int	  _line;
public:
    IlvSuTrace(char* b, char* f, int l)
    : _block(b),
      _file(f),
      _line(l)
    {
#if !defined(NTRACE)
	cout << ">> " << b << " in file " << f << " line " << l << endl;
#endif /* !NTRACE */
    }
    ~IlvSuTrace()
    {
#if !defined(NTRACE)
	cout << "<<" << _block << endl;
#endif /* !NTRACE */
    }
};

#ifndef NTRACE
#define ILVSTATES_TR(n) IlvSuTrace __trace_block__(#n,__FILE__,__LINE__);
#else
#define ILVSTATES_TR(ignore)
#endif
#endif /* __Ilv_States_Trace_H */
