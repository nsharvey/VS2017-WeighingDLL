// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/gendefs.h
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
// Declaration of internal macros
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Gendefs_H
#define __Ilv_States_Gendefs_H

#if !defined(__assert_h__)
#  define __assert_h__
#  include <assert.h>
#endif
#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif

#include <ilviews/macros.h>

#ifndef NULL
#  define NULL 0
#endif

#define ILVSTATES_ONDEBUG ILVTRACE

// to stop a program at end under windows
#define ILVSTATES_PAUSE cout << "Paused. Ok? "; {char tab; cin >> tab; }

#define ILVSTATES_READONLY(type, field) \
type get##field() const { return _##field; }
#define ILVSTATES_WRITEONLY(type, field) \
void  set##field(type field) { _##field = field; }
#define ILVSTATES_READWRITE(type, field) \
ILVSTATES_READONLY(type, field) ILVSTATES_WRITEONLY(type, field)

#endif /* !__Ilv_States_Gendefs_H */
