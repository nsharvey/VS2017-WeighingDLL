// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ild.h
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
// Documented types and structs
//
// BEWARE: This file is included by some C files, so no C++ syntax here !
// ----------------------------------------------------------------------------

#ifndef __ILD_ILD_H
#define __ILD_ILD_H

#ifndef __Il_Macros_H
# include <ilog/macros.h>
#endif

#if defined(ILDLIB)
# define ILD_EXPORTED               IL_BASEEXPORTED
# define ILD_EXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !DBLINKLIB */
# define ILD_EXPORTED               IL_BASEIMPORTED
# define ILD_EXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILDLIB */

 /*
  =============================================================================
  Constants
  =============================================================================
 */
#define ILD_ERRMSG_SIZE	1024
#define ILD_SQLS_SIZE	6

/* Greater than any supported RDBMS and aligned */
#define ILD_NAME_SIZE	32
#define ILD_FIELD_SIZE	256

#define ILD_LONG_SIZE	65536

#define ILD_NO_DATA	100

#define ILD_PQ_SIZE 512

/*
  =============================================================================
  Scalar types
  =============================================================================
*/

enum IldEntityType {
  IldUnknownEntity,
  IldTableEntity,
  IldViewEntity,
  IldADTEntity,
  IldCallableEntity,
  IldSynonymEntity
};

enum IldKeyType {
  IldPrimaryKey,
  IldForeignKey,
  IldIndexKey,
  IldSpecialColumn
};

enum IldColumnType {
  IldMoneyType,
  IldByteType,
  IldBinaryType,
  IldLongTextType,
  IldUnknownType,
  IldNumericType,
  IldIntegerType,
  IldRealType,
  IldStringType,
  IldDateType,
  IldDateTimeType,
  IldObjectType,     /* Oracle: object Informix:[named] row                */
  IldCollectionType, /* Oracle: varray, table Informix: list, set, multiset */
  IldRefType,        /* Oracle: ref                                   */
  IldCLOBType,
  IldBLOBType,
  IldCursorType,     /* Oracle: cursor returned from stored procedure */
  IldDecfloatType    /* DB2 9.x: decfloat type */
};

enum IldADTType {
  IldADTNone,		/* Internal error !				*/
  IldADTArray,		/* Ora: varray, limited number of elts		*/
  IldADTObject,		/* Ora: object ; Infx:[named] row		*/
  IldADTTable,		/* Ora: nested table				*/
  IldADTList		/* Infx: list, set, multiset			*/
};


enum IldErrorOrigin {
  IldUnknownOrigin,
  IldDbLink,
  IldClientAPI,
  IldRDBMServer
};

/*
  =============================================================================
  Internal Db Link errors and warnings.
  =============================================================================
*/
#define ILD_ALREADY_CONNECTED	-1
#define ILD_DBMS_NOT_CONNECTED	-2
#define ILD_DBMS_FATAL_ERROR	-3
#define ILD_UNKNOWN_TYPE		-4
#define ILD_REQUEST_REQUIRED	-5
#define ILD_TYPE_MISMATCH		-6
#define ILD_MEMORY_EXHAUSTED	-7
#define ILD_OUT_OF_RANGE		-8
#define ILD_NO_MORE_TUPLES		-9
#define ILD_UNKNOWN_ENTITY		-10
#define ILD_NOT_IMPLEMENTED		-11
#define ILD_BAD_DB_SPEC			-12
#define ILD_UNKNOWN_RDBMS		-13
#define ILD_NO_TRANLOG			-14 /* Infx specific */
#define ILD_STATE				-15
#define ILD_SEVERITY			-16
#define ILD_USING_ERROR_DBMS	-17
#define ILD_USING_ERROR_REQUEST -18
#define ILD_BAD_COLUMN_NAME		-19
#define ILD_BAD_COLUMN_INDEX	-20
#define ILD_CANNOT_RESIZE_TUPLE	-21
#define ILD_BAD_VARIABLE_SIZE	-22
#define ILD_BAD_EXECUTE_COUNT	-23
#define ILD_BAD_FILE			-24
#define ILD_NO_REPORTER			-25
#define ILD_INVALID_SEQUENCE	-26
#define ILD_INVALID_HANDLE		-27
#define ILD_UNKNOWN_CODE		-28
#define ILD_NO_HANDLER			-29
#define ILD_CTXT_ALLOC			-30
#define ILD_CTXT_INIT			-31
#define ILD_CON_ALLOC			-32
#define ILD_CON_INIT			-33
#define ILD_CMD_ALLOC			-34
#define ILD_CMD_INIT			-35
#define ILD_CBCK_INIT			-36
#define ILD_NUM_CONVERT			-37
#define ILD_DATE_CONVERT		-38
#define ILD_MAX_CURS_LEN		-39
#define ILD_RDBMS_CONN			-40
#define ILD_LIB_NLNKD			-41
#define ILD_NO_DYN_LIB			-42
#define ILD_LIB_MSMTCH			-43
#define ILD_UNKN_ERRMSG			-44
#define ILD_UNCHGEABLE			-45
#define ILD_OFFSET				-46
#define ILD_IGN_EXT_ROWS		-47
#define ILD_NOT_SCROLL_MODE		-48
#define ILD_UNDEF_LINK_MODE		-49
#define ILD_INVALID_PARAMETER	-50
#define ILD_NO_DATA_FOUND		-51
#define ILD_TRUNCATED			-52
#define ILD_BAD_DB_NAME			-53
#define ILD_OS_ERROR			-54
#define ILD_ENV_NFOUND			-55
#define ILD_INTERNAL_ERR		-56
#define ILD_NULL_VALUE			-57

#define ILD_MAX_ERR_CODE		ILD_NULL_VALUE - 1

/*
  =============================================================================
  Db Link function Ids.
  =============================================================================
 */
enum IldFuncId {
  ILD_D_START_TRANSACTION = 1,
  ILD_D_COMMIT,
  ILD_D_ROLLBACK,
  ILD_D_AUTO_COMMIT_ON,
  ILD_D_AUTO_COMMIT_OFF,
  ILD_D_SET_TRANSACTION_READONLY,
  ILD_D_FREE_NAMES,
  ILD_D_GET_FREE_REQUEST,
  ILD_D_GET_NUM_ENTITIES,
  ILD_D_GET_RELATION,
  ILD_D_GET_PROCEDURE,
  ILD_D_GET_ADT,
  ILD_D_GET_SYNONYM,
  ILD_D_GET_NUMBER_OF_ACTIVE_CONN,
  ILD_D_GET_NAME,
  ILD_D_GET_USER,
  ILD_D_GET_DBMS_VERSIONS,
  ILD_D_GET_DBMS_VERSION,
  ILD_D_GET_DATABASE,
  ILD_D_GET_DBMS_SERVER,
  ILD_D_CONNECT,
  ILD_D_DISCONNECT,
  ILD_D_IS_CONNECTED,
  ILD_D_IS_TRANSACTION_ENABLED,
  ILD_D_GET_HOOK,
  ILD_D_SET_HOOK,
  ILD_D_READ_OWNERS,
  ILD_D_READ_ENTITY_NAMES,
  ILD_D_READ_TABLE_PRIVILEGES,
  ILD_D_READ_RELATION_NAMES,
  ILD_D_READ_RELATION_OWNERS,
  ILD_D_READ_PROCEDURE_NAMES,
  ILD_D_READ_ABSTRACT_TYPE_NAMES,
  ILD_D_READ_SYNONYM_NAMES,
  ILD_D_DBMS,
  ILD_D_TILDE_DBMS,
  ILD_D_EXECUTE,
  ILD_D_GET_INFO,
  ILD_D_SET_REPORTER,
  ILD_D_GET_TYPE_INFO,
  ILD_D_FREE_TYPE_INFO,
  ILD_D_READ_PKEY,
  ILD_D_READ_FKEYS,
  ILD_D_READ_INDEXES,
  ILD_D_READ_SCOLS,
  ILD_D_SET_TIMEOUT,
  ILD_D_SET_ASYNC,
  ILD_D_SET_ERROR_REP,
  ILD_D_CANCEL,
  ILD_D_REMOVE_ENTITY,
  ILD_D_SUBSCRIBE_EVENT,
  ILD_D_UNSUBSCRIBE_EVENT,
  ILD_D_GET_ERROR_REPORTER,
  ILD_D_IS_COMPLETED,
  ILD_R_REQUEST,
  ILD_R_TILDE_REQUEST,
  ILD_R_RELEASE,
  ILD_R_SET_COL_ARRAY_SIZE,
  ILD_R_REMOVE_COL_ARRAY_SIZE,
  ILD_R_SET_COL_POS,
  ILD_R_SET_PARAM_ARRAY_SIZE,
  ILD_R_REMOVE_PARAM_ARRAY_SIZE,
  ILD_R_GET_COL_DESC,
  ILD_R_GET_COL_INDEX,
  ILD_R_GET_COL_SIZE,
  ILD_R_GET_COL_NAME,
  ILD_R_GET_PARAM_DESC,
  ILD_R_GET_PARAM_INDEX,
  ILD_R_GET_PARAM_NAME,
  ILD_R_GET_PARAM_TYPE,
  ILD_R_GET_PARAM_SQLTYPE,
  ILD_R_GET_PARAM_SQLTYPE_NAME,
  ILD_R_GET_PARAM_SIZE,
  ILD_R_GET_PARAM_BUFFER_SIZE,
  ILD_R_BIND_COL,
  ILD_R_BIND_PARAM,
  ILD_R_EXECUTE,
  ILD_R_FETCH,
  ILD_R_INSERT_LONGTEXT,
  ILD_R_INSERT_BINARY,
  ILD_R_IS_COL_NULL,
  ILD_R_GET_COL_ADT,
  ILD_R_GET_COL_BINARY,
  ILD_R_GET_COL_BYTE,
  ILD_R_GET_COL_DATE,
  ILD_R_GET_COL_DATETIME,
  ILD_R_GET_COL_INTEGER,
  ILD_R_GET_COL_LONGTEXT,
  ILD_R_GET_COL_MONEY,
  ILD_R_GET_COL_NUMERIC,
  ILD_R_GET_COL_REAL,
  ILD_R_GET_COL_REF,
  ILD_R_GET_COL_STRING,
  ILD_R_PARSE,
  ILD_R_SET_PARAM_VALUE,
  ILD_R_SET_PARAM_NULL,
  ILD_R_IS_PARAM_NULL,
  ILD_R_GET_PARAM_ADT,
  ILD_R_GET_PARAM_BINARY,
  ILD_R_GET_PARAM_BYTE,
  ILD_R_GET_PARAM_CURSOR,
  ILD_R_GET_PARAM_DATE,
  ILD_R_GET_PARAM_DATETIME,
  ILD_R_GET_PARAM_INTEGER,
  ILD_R_GET_PARAM_LONGTEXT,
  ILD_R_GET_PARAM_MONEY,
  ILD_R_GET_PARAM_NUMERIC,
  ILD_R_GET_PARAM_REAL,
  ILD_R_GET_PARAM_REF,
  ILD_R_GET_PARAM_STRING,
  ILD_R_IS_NULL_INDICATOR_ON,
  ILD_R_HAS_TUPLE,
  ILD_R_GET_STATUS,
  ILD_R_GET_HOOK,
  ILD_R_GET_LARGE_OBJECT,
  ILD_R_CLOSE_CURSOR,
  ILD_R_SET_REPORTER,
  ILD_R_SET_CURSOR_NAME,
  ILD_R_SET_READONLY,
  ILD_R_SET_CURSOR_MODE_ON,
  ILD_R_SET_SCROLLABLE,
  ILD_R_FETCH_SCROLL,
  ILD_R_GET_ERROR_REPORTER,
  ILD_R_IS_COMPLETED,
  ILD_DR_DRIVER
} ;


#define DEBUGPRINT(args)
#define BOOLEXIT(l, f)
#define DEBUGENTRY(l, f)
#define DEBUGEXIT(l, f)

/*
  =============================================================================
  Structured type for long binary data
  =============================================================================
  */
#if defined(__cplusplus) || defined(DOXYGEN_GENERATION)
struct IldBytes {
  IlUInt  _size;
  IlUChar* _value;
};
#endif

#endif /* __ILD_ILD_H */
