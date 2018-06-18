// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildtrace.h
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
// Trace mechanism and context
// --------------------------------------------------------------------------*/


#ifndef __ILD_ILDTRACE_H
#define __ILD_ILDTRACE_H

/*
  =============================================================================
  Trace context
  ============================================================================
*/
typedef struct _IldTraceContext {
    IlUShort	_level;
#ifdef __cplusplus
    IL_STDPREF ostream*	_ostr;
#else
    void* _xx;
#endif
} IldTraceContext;

/* 
 * Return the context if it exists.
 */
#ifdef __cplusplus
extern "C" {
#endif
ILD_EXPORTEDFUNCTION(IldTraceContext*)
    IldGetTraceContext();
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
ILD_EXPORTEDFUNCTION(void)
    IldPrintTrace(IlUShort level,
		  int line,
		  int nbArgs,
		  ...);
#ifdef __cplusplus
}
#endif

ILD_EXPORTEDFUNCTION(IldTraceContext*)
    IldSetTraceContext(IlUShort,
#ifdef __cplusplus
		       IL_STDPREF ostream*
#else
		       void* xxx
#endif
		       );

ILD_EXPORTEDFUNCTION(int)
     IldSetTraceLevel(IlUShort);

ILD_EXPORTEDFUNCTION(int)
     IldSetTraceStream(
#ifdef __cplusplus
		       IL_STDPREF ostream*
#else
		       void* xxx
#endif
		       );
/*
  =============================================================================
  Tracing 
  =============================================================================
*/
#define TRCANY 0
#define TRCCHR 1
#define TRCSTR 2
#define TRCINT 3
#define TRCFLT 4
#define TRCEND 5
#define TRCENT 6
#define TRCEXT 7

/* Trace levels */
#define IldTraceNone (IlUShort)0
/* documented API */
#define IldTraceAPI (IlUShort)1
/* All functions in derived classes (dbms and request) */
#define IldTraceFuns (IlUShort)2
/* DB Link kernel (all result, parameter sets and metadata classes) */
#define IldTraceKernel (IlUShort)4
/* Internal functions (undocumented functions) */
#define IldTraceIntern (IlUShort)8
/* RDBMS API level (client libraries) */
#define IldTraceNative (IlUShort)16

/* The followings are intentionally undocumented */
#define PRINTTRACE(args) if (IldGetTraceContext()) {IldPrintTrace args; }
#define TRACEBEXIT(level, fun) \
    PRINTTRACE((level, __LINE__, 2, TRCEXT, fun, TRCINT, (IlInt)_errorRaised))
#define TRACEENTRY(level, func) \
    PRINTTRACE((level, __LINE__, 2, TRCENT, func, TRCEND))
#define TRACEEXIT(level, func) \
    PRINTTRACE((level, __LINE__, 2, TRCEXT, func, TRCEND))

#endif
