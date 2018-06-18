// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/memory.h
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
// Declaration of memory management functions
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Memory_H
#define __Ilv_Base_Memory_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Il_Memory_H)
#  include <ilog/memory.h>
#endif
#if !defined(__Ilv_Util_Pool_H)
#  include <ilviews/util/pool.h>
#endif

#define IlvMalloc  IlMalloc
#define IlvRealloc IlRealloc
#define IlvFree    IlFree
#define IlvMemMove IlMemMove
#define ILVMALLOC  IL_MALLOC
#define ILVREALLOC IL_REALLOC
#define ILVSTRCASECMP  IL_STRCASECMP
#define ILVSTRNCASECMP IL_STRNCASECMP

#define IlvAllocPoints(n) IlPoolOf(IlvPoint)::Alloc(n)

#endif /* !__Ilv_Base_Memory_H */
