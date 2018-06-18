// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/errcodes.h
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
#ifndef __Ili_Compat_Errcodes_H
#define __Ili_Compat_Errcodes_H

#include <ilviews/dataccess/errcodes.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwErrorCodeTag IliErrorCodeTag
#define IlvSw_UndefinedError Ili_UndefinedError
#define IlvSw_UnexpectedError Ili_UnexpectedError
#define IlvSw_IncorrectValueError Ili_IncorrectValueError
#define IlvSw_TableIsReadOnlyError Ili_TableIsReadOnlyError
#define IlvSw_DuplicateRowError Ili_DuplicateRowError
#define IlvSw_NullColumnError Ili_NullColumnError
#define IlvSw_ColumnLengthError Ili_ColumnLengthError
#define IlvSw_InvalidRowNumber Ili_InvalidRowNumber
#define IlvSw_InvalidTableBuffer Ili_InvalidTableBuffer
#define IlvSw_IncorrectTableAlias Ili_IncorrectTableAlias
#define IlvSw_InvalidParameterType Ili_InvalidParameterType
#define IlvSw_UndefinedQuery Ili_UndefinedQuery
#define IlvSw_RowsCountLimitExceeded Ili_RowsCountLimitExceeded
#define IlvSw_ColumnTypeMismatch Ili_ColumnTypeMismatch
#define IlvSw_ColumnNotInQuery Ili_ColumnNotInQuery
#define IlvSw_FetchPendingError Ili_FetchPendingError
#define IlvSw_SQLRowNotFoundError Ili_SQLRowNotFoundError
#define IlvSw_SQLRowChangedSinceFetch Ili_SQLRowChangedSinceFetch
#define IlvSw_UndefinedSQLSessionError Ili_UndefinedSQLSessionError
#define IlvSw_CannotAllocateSQLCursorError Ili_CannotAllocateSQLCursorError
#define IlvSw_GroupedQueryIsReadOnlyError Ili_GroupedQueryIsReadOnlyError
#define IlvSw_NotAllColumnsAreUpdatableError Ili_NotAllColumnsAreUpdatableError
#define IlvSw_DatabaseRowIsNotUniqueUpdateError Ili_DatabaseRowIsNotUniqueUpdateError
#define IlvSw_DatabaseRowIsNotUniqueSelectError Ili_DatabaseRowIsNotUniqueSelectError
#define IlvSw_AlreadyConnectedError Ili_AlreadyConnectedError
#define IlvSw_NotConnectedError Ili_NotConnectedError
#define IlvSw_TableWithoutColumnsError Ili_TableWithoutColumnsError
#define IlvSw_TableWithoutNameError Ili_TableWithoutNameError
#define IlvSw_ColumnWithoutNameError Ili_ColumnWithoutNameError
#define IlvSw_ColumnWithoutTypeError Ili_ColumnWithoutTypeError
#define IlvSw_ErrorCodesCount Ili_ErrorCodesCount
#define IlvSwFormatErrorMessage IliFormatErrorMessage
#define IlvSwGetErrorText IliGetErrorText
#endif

#endif
