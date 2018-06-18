// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/hash.h
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
// Encapsulation of the IlHashTable and related classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Hash_H
#define __Ilv_Base_Hash_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Il_Hash_H)
#include <ilog/hash.h>
#endif

#define IlvHashTable       IlHashTable
#define IlvStringHashTable IlStringHashTable
#define IlvSymbol          IlSymbol
#define IlvGetSymbol       IlGetSymbol

#define IlvDefineLazySymbol(function, string) \
IlSymbol* function() { static IlSymbol* s = IlGetSymbol(string); return s; }
#endif /* !__Ilv_Base_Hash_H */
