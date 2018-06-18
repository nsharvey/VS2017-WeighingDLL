// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/dbms/dbmsdriv.h
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
#ifndef __Ili_Compat_Dbmsdriv_H
#define __Ili_Compat_Dbmsdriv_H

#include <ilviews/dataccess/dbms/dbmsdriv.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbmsDriverId IliDbmsDriverId
#define IlvSwDriver_Null IliDriver_Null
#define IlvSwDriver_Oracle IliDriver_Oracle
#define IlvSwDriver_Oracle73 IliDriver_Oracle73
#define IlvSwDriver_Oracle8 IliDriver_Oracle8
#define IlvSwDriver_Ingres IliDriver_OpIngres
#define IlvSwDriver_Informix IliDriver_Informix
#define IlvSwDriver_Informix72 IliDriver_Informix72
#define IlvSwDriver_Sybase IliDriver_Sybase
#define IlvSwDriver_Odbc IliDriver_Odbc
#define IlvSwDriver_Count IliDriver_Count
#define IlvSwCaseSensitivity IliCaseSensitivity
#define IlvSwCaseSensitive IliCaseSensitive
#define IlvSwUppercase IliUppercase
#define IlvSwLowercase IliLowercase
#define IlvSwOuterJoinStyle IliOuterJoinStyle
#define IlvSwOJ_InWherePar IliOJ_InWherePar
#define IlvSwOJ_InFromPart IliOJ_InFromPart
#define IlvSwOJ_InBothParts IliOJ_InBothParts
#define IlvSwGetDriverInfoFn IliGetDriverInfoFn
#define IlvSwReadDbmsDriverErrorMessagesFn IliReadDbmsDriverErrorMessagesFn
#define IlvSwFromItem IliFromItem
#define IlvSwOuterJoinDesc IliOuterJoinDesc
#define IlvSwDbmsDriver IliDbmsDriver
#endif

#endif



