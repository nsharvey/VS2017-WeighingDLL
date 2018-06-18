// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/pool.h
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
// Declaration of memory pools for common usage.
// Defined in library <display>
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Pool_H
#define __Ilv_Util_Pool_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#define IL_POOL_EXPORTED ILVDSPEXPORTED
#if !defined(__Il_Pool_H)
#include <ilog/pool.h>
#endif

#define IlvPoolOf IlPoolOf
#define IlvPoolOfDeclarePoolOf IlDeclarePoolOf
#define IlvDefinePoolOf  IlDefinePoolOf

#if !defined(_Ilv_Base_Geometry_H)
#include <ilviews/base/geometry.h>
#endif

IlDeclareExpPoolOf(IlvPoint,       IlvPoint,      ILVDSPEXPORTED);
IlDeclareExpPoolOf(IlvRect,        IlvRect,      ILVDSPEXPORTED);
IlDeclareExpPoolOf(IlvFloatPoint,  IlvFloatPoint, ILVDSPEXPORTED);
IlDeclareExpPoolOf(IlvDoublePoint, IlvDoublePoint, ILVDSPEXPORTED);
#define IlvPointPool IlIlvPointPool
#define IlvRectPool IlIlvRectPool
#define IlvPointerPool IlPointerPool

#endif /* !__Ilv_Util_Pool_H */
