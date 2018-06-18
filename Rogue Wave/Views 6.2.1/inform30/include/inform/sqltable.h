// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/sqltable.h
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
#ifndef __Ili_Compat_Sqltable_H
#define __Ili_Compat_Sqltable_H

#include <ilviews/dataccess/sqltable.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwFetchPolicy IliFetchPolicy
#define IlvSwFP_AsNeeded IliFP_AsNeeded
#define IlvSwFP_Immediate IliFP_Immediate
#define IlvSwSQLOrderByType IliSQLOrderByType
#define IlvSwSQLNoOrder IliSQLNoOrder
#define IlvSwSQLAscending IliSQLAscending
#define IlvSwSQLDescending IliSQLDescending
#define IlvSwSQLOperation IliSQLOperation
#define IlvSwSQLScalar IliSQLScalar
#define IlvSwSQLGroupBy IliSQLGroupBy
#define IlvSwSQLCount IliSQLCount
#define IlvSwSQLSum IliSQLSum
#define IlvSwSQLAvg IliSQLAvg
#define IlvSwSQLMin IliSQLMin
#define IlvSwSQLMax IliSQLMax
#define IlvSwSQLJoinType IliSQLJoinType
#define IlvSwInnerJoin IliInnerJoin
#define IlvSwLeftOuterJoin IliLeftOuterJoin
#define IlvSwRightOuterJoin IliRightOuterJoin
#define IlvSwSQLTable IliSQLTable
#endif

#endif




