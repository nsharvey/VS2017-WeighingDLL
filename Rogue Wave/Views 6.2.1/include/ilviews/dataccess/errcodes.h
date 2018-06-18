// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/errcodes.h
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
#ifndef __Ili_Errcodes_H
#define __Ili_Errcodes_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

enum IliErrorCodeTag {
  Ili_UndefinedError,

  // catch all
  Ili_UnexpectedError,
  Ili_FunctionCallSequenceError,

  // user input errors
  Ili_IncorrectValueError,

  // IliTable errors
  Ili_TableIsReadOnlyError,
  Ili_DuplicateRowError,
  Ili_NullColumnError,
  Ili_ColumnLengthError,
  Ili_InvalidRowNumber,
  Ili_InvalidTableBuffer,

  // IliSQLTableInspector errors
  Ili_IncorrectTableAlias,
  Ili_InvalidParameterType,

  // IliSQLTable errors
  Ili_UndefinedQuery,
  Ili_RowsCountLimitExceeded,
  Ili_ColumnTypeMismatch,
  Ili_ColumnNotInQuery,
  Ili_FetchPendingError,
  Ili_SQLRowNotFoundError,
  Ili_SQLRowChangedSinceFetch,
  Ili_UndefinedSQLSessionError,
  Ili_CannotAllocateSQLCursorError,
  Ili_GroupedQueryIsReadOnlyError,
  Ili_NotAllColumnsAreUpdatableError,
  Ili_DatabaseRowIsNotUniqueUpdateError,
  Ili_DatabaseRowIsNotUniqueSelectError,
  Ili_OperationNotSupportedInQueryMode,

  // IliSQLSession errors
  Ili_AlreadyConnectedError,
  Ili_NotConnectedError,
  Ili_SQLSessionNotInAsyncMode,
  Ili_SQLSessionInAsyncMode,

  // IliSQLTableDef errors
  Ili_TableWithoutColumnsError,
  Ili_TableWithoutNameError,
  Ili_ColumnWithoutNameError,
  Ili_ColumnWithoutTypeError,

  Ili_ErrorCodesCount
};

ILV_INF_EXPORTEDFN(void)
IliFormatErrorMessage (IliString& dest,IliErrorCodeTag tag,
		       const char* arg1 = 0,IlInt arg2 = 0);

ILV_INF_EXPORTEDFN(void)
IliFormatErrorMessage (IliString& dest,IliErrorCodeTag tag,
		       const char* arg1,const char* arg2);

ILV_INF_EXPORTEDFN(const char*)
IliGetErrorText(IliErrorCodeTag tag);

ILV_INF_EXPORTEDFN(void)
IliSetErrorText(IliErrorCodeTag tag, const char* text);

// --

IliModuleDECL_exp(ILV_INF_EXPORTED,IliErrorCode);

#endif
