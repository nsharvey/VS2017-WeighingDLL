// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inout.h
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
// Declaration of IO utilities
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inout_H
#define __IlvSt_Inout_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if defined(ILVSTD)
#include <cstring>
#else  /* !ILVSTD */
#include <string.h>
#endif /* !ILVSTD */
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

class IlvValue;

extern ILVSTEXPORTEDFUNC(char*) IlvStRead(ILVSTDPREF istream& istrm,
		       char* buffer,
		       size_t count,
		       const char* delims);
extern ILVSTEXPORTEDFUNC(char*) IlvStReadSymbol(ILVSTDPREF istream& istrm, char* buffer, size_t count);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStReadBoolean(ILVSTDPREF istream&, char* buffer, size_t count);
extern ILVSTEXPORTEDFUNC(void) IlvStEatWhite(ILVSTDPREF istream&);
extern ILVSTEXPORTEDFUNC(void) IlvStSetPrintPropertyWidth(IlShort val);
extern ILVSTEXPORTEDFUNC(IlShort) IlvStGetPrintPropertyWidth();
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream& ostrm,
			       const char* prop,
			       const char* value);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteIdentifierProperty(ILVSTDPREF ostream& ostrm,
					 const char* prop,
					 const char* value);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream& ostrm,
			       const char* prop,
			       IlUShort count,
			       const char* const* values);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream& ostrm,
			       const char* prop,
			       IlBoolean value,
			       IlBoolean defval);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream&, const char* prop, IlSymbol*);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream&, const char* prop, IlInt);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream&, const char* prop, float value);
extern ILVSTEXPORTEDFUNC(void) IlvStWriteProperty(ILVSTDPREF ostream&, IlvValue*);

#endif /* __IlvSt_Inout_H */
