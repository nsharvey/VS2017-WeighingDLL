// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildconst.h
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
// Rogue Wave DB Link : ISO/IEC CLI like constants
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDCONST_H
#define __ILD_ILDCONST_H

#ifndef __ILD_ILD_H
#include <ildblink/ild.h>
#endif

/* ----------------------------------------------------------------------------
// Environment Attributes
// (not used because always true)
// --------------------------------------------------------------------------*/
const IlInt ILD_NULL_TERM = 10001;

/* ----------------------------------------------------------------------------
// Connection Attributes
// (not used, reserved for future)
// --------------------------------------------------------------------------*/
const IlInt ILD_POP_IPD    = 10001;

/* ----------------------------------------------------------------------------
// Statement Attributes
// (not used, reserved for future)
// --------------------------------------------------------------------------*/
const IlInt ILD_APD_HANDLE = 10011;
const IlInt ILD_ARD_HANDLE = 10010;
const IlInt ILD_IPD_HANDLE = 10013;
const IlInt ILD_IRD_HANDLE = 10012;
const IlInt ILD_CUR_SCROLL = -1;
const IlInt ILD_CUR_SENSIT = -2;

/* ----------------------------------------------------------------------------
// Implementation information = CLI code	//Return type
// --------------------------------------------------------------------------*/
enum IldInfoItem {
  IldMaxDriverConnections,		/*  0	SmallInt  */
  IldMaxConcurrentActivities,		/*  1	SmallInt  */
  IldDataSourceName,			/*  2	Char(128) */
  IldFetchDirection = 8,		/*  8	Int       */
  IldServerName = 13,			/* 13	Char(128) */
  IldDBMSName = 17,			/* 17	Char(254) */
  IldDBMSVersion = 18,			/* 18	Char(254) */
  IldCursorCommitBehavior = 23,		/* 23	SmallInt  */
  IldDataSourceReadOnly = 25,		/* 25	Char(1)   */
  IldDefTransactionIsolation = 26,	/* 26	Int       */
  IldIdentifierCase = 28,		/* 28	SmallInt  */
  IldMaxColumnNameLength = 30,		/* 30	SmallInt  */
  IldMaxCursorNameLength = 31,		/* 31	SmallInt  */
  IldMaxSchemaNameLength = 32,		/* 32	SmallInt  */
  IldMaxCatalogNameLength = 34,		/* 34	SmallInt  */
  IldMaxTableNameLength = 35,		/* 35	SmallInt  */
  IldScrollConcurrency = 43,		/* 43	Int       */
  IldTransactionCapable = 46,		/* 46	SmallInt  */
  IldUserName = 47,			/* 47	Char(128) */
  IldTransactionIsolationOpt = 72,	/* 72	Int       */
  IldIntegrity = 73,			/* 73	Char(1)   */
  IldGetDataExtension = 81,		/* 81	Int       */
  IldNullCollation = 85,		/* 85	SmallInt  */
  IldAlterTable = 86,			/* 86	Int       */
  IldOrderByColumnsInSelect = 90,	/* 90	Char(1)   */
  IldSpecialCharacters = 94,		/* 94	Char(254) */
  IldMaxColumnsInGroupBy = 97,		/* 97	SmallInt  */
  IldMaxColumnsInOrderBy = 99,		/* 99	SmallInt  */
  IldMaxColumnsInSelect = 100,		/*100	SmallInt  */
  IldMaxColumnsInTable = 101,		/*101	SmallInt  */
  IldMaxStatementLength = 105,		/*105	SmallInt  */
  IldMaxTablesInSelect = 106,		/*106	SmallInt  */
  IldMaxUserNameLength = 107,		/*107	SmallInt  */
  IldOuterJoinCapabilities = 115,	/*115	SmallInt  */
  IldCursorSensitivity = 10001,		/*10001	Int       */
  IldDescribeParameter = 10002,		/*10002	Char(1)   */
  IldCatalogName = 10003,		/*10003	Char(1)   */
  IldCollatingSequence = 10004,		/*10004	Char(254) */
  IldMaxIdentifierLength = 10005	/*10005	SmallInt  */
};

/* ----------------------------------------------------------------------------
// GetInfo : AlterTable
// --------------------------------------------------------------------------*/
const IlInt IldAlterTableAddColumn = 1;
const IlInt IldAlterTableDropColumn = 2;
const IlInt IldAlterTableAlterColumn = 4;
const IlInt IldAlterTableAddConstraint = 8;
const IlInt IldAlterTableDropConstraint = 16;

/* ----------------------------------------------------------------------------
// GetInfo : Cursor Commit Behavior
// --------------------------------------------------------------------------*/
const IlInt IldCurBehaviorDelete   = 0;
const IlInt IldCurBehaviorClose    = 1;
const IlInt IldCurBehaviorPreserve = 2;

/* ----------------------------------------------------------------------------
// GetInfo : Fetch Direction
// --------------------------------------------------------------------------*/
const IlInt IldFetchDirectionNext  = 1;
const IlInt IldFetchDirectionFirst = 2;
const IlInt IldFetchDirectionLast  = 4;
const IlInt IldFetchDirectionPrior = 8;
const IlInt IldFetchDirectionAbsolute = 16;
const IlInt IldFetchDirectionRelative = 32;

/* ----------------------------------------------------------------------------
// GetInfo : GetData Extension
// --------------------------------------------------------------------------*/
const IlInt IldGetDataAnyColumn = 1;
const IlInt IldGetDataAnyOrder = 2;

/* ----------------------------------------------------------------------------
// GetInfo : Identifier Case
// --------------------------------------------------------------------------*/
const IlInt IldIdentifierUpper = 1;
const IlInt IldIdentifierLower = 2;
const IlInt IldIdentifierSensitive = 3;
const IlInt IldIdentifierMixed = 4;

/* ----------------------------------------------------------------------------
// GetInfo : Outer Join Capabilities
// --------------------------------------------------------------------------*/
const IlInt IldOuterJoinLeft = 1;
const IlInt IldOuterJoinRight = 2;
const IlInt IldOuterJoinFull = 4;
const IlInt IldOuterJoinNested = 8;
const IlInt IldOuterJoinNotOrdered = 16;
const IlInt IldOuterJoinInner = 32;
const IlInt IldOuterJoinAllOps = 64;

/* ----------------------------------------------------------------------------
// GetInfo : Scroll Concurrency
// --------------------------------------------------------------------------*/
const IlInt IldScrollReadOnly = 1;
const IlInt IldScrollLock = 2;
const IlInt IldScrollOptRowver = 4;
const IlInt IldScrollOptValues = 8;

/* ----------------------------------------------------------------------------
// GetInfo : Transaction Capable
// --------------------------------------------------------------------------*/
const IlInt IldTransCapableNone = 0;
const IlInt IldTransCapableDML = 1;
const IlInt IldTransCapableAll = 2;
const IlInt IldTransCapableDDLCommit = 3;
const IlInt IldTransCapableDDLIgnore = 4;

/* ----------------------------------------------------------------------------
// GetInfo : Transaction Isolation
// --------------------------------------------------------------------------*/
const IlInt IldTransIsolReadUncommitted = 1;
const IlInt IldTransIsolReadCommitted = 2;
const IlInt IldTransIsolRepeatableRead = 3;
const IlInt IldTransIsolSerializable = 4;

/* ----------------------------------------------------------------------------
// GetInfo : Null Collation
// --------------------------------------------------------------------------*/
const IlInt IldNullCollateHigh = 0;
const IlInt IldNullCollateLow = 1;

/* ----------------------------------------------------------------------------
// GetInfo : Cursor Sensitivity
// --------------------------------------------------------------------------*/
const IlInt IldCursorAsensitive = 0 ;
const IlInt IldCursorInsensitive = 1 ;
const IlInt IldCursorSensitive = 2 ;

/* ----------------------------------------------------------------------------
// GetTypeInfo: Type Codes
// --------------------------------------------------------------------------*/
const short IldSQLCursor		= -9;	/* Oracle cursor        */
const short IldSQLBFile			= -8;	/* Oracle BFILE        */
const short IldSQLMoney			= -7;
const short IldSQLByte			= -6;
const short IldSQLVarBin		= -3;
const short IldSQLBin			= -2;

const short IldSQLAllTypes		= 0;	/* CLI: SQL_ALL_TYPES   */
const short IldSQLChar			= 1;	/* CLI: SQL_CHAR        */
const short IldSQLNumeric		= 2;	/* CLI: SQL_NUMERIC     */
const short IldSQLDecimal		= 3;	/* CLI: SQL_DECIMAL     */
const short IldSQLInteger		= 4;	/* CLI: SQL_INTEGER     */
const short IldSQLSmallint		= 5;	/* CLI: SQL_SMALLINT    */
const short IldSQLFloat			= 6;	/* CLI: SQL_FLOAT       */
const short IldSQLReal			= 7;	/* CLI: SQL_REAL        */
const short IldSQLDouble		= 8;	/* CLI: SQL_DOUBLE      */
const short IldSQLDateTime		= 9;	/* CLI: SQL_DATETIME    */
const short IldSQLInterval		= 10;	/* CLI: SQL_INTERVAL    */
/* Not defined : 11    */
const short IldSQLVarchar		= 12;	/* CLI: SQL_VARCHAR     */
/* Not defined : 13    */
const short IldSQLBit			= 14;	/* CLI: SQL_BIT         */
const short IldSQLBitVarying		= 15;	/* CLI: SQL_BIT_VARYING */
const short IldSQLBoolean		= 16;	/* CLI: SQL_BOOLEAN     */
const short IldSQLNamedType		= 17;	/* CLI: SQL_UDT         */
const short IldSQLNamedTypeRef		= 18;	/* CLI: SQL_UDT_LOCATOR */
const short IldSQLRow			= 19;	/* CLI: SQL_ROW         */
const short IldSQLRef			= 20;	/* CLI: SQL_REF         */
/* Not defined: 21-24 */
const short IldSQLBigint		= 25;	/* CLI: SQL_BIGINT      */
/* Not defined: 26-29 */
const short IldSQLLongBin		= 30;	/* CLI: SQL_BLOB        */
const short IldSQLBLOB			= 31;	/* CLI: SQL_BLOB_LOCATOR*/
/* Not defined : 32-39 */
const short IldSQLText			= 40;	/* CLI: SQL_CLOB        */
const short IldSQLCLOB			= 41;	/* CLI: SQL_CLOB_LOCATOR*/

const short IldSQLDate			= 91;	/* CLI: SQL_TYPE_DATE   */
const short IldSQLTime			= 92;	/* CLI: SQL_TYPE_TIME   */
const short IldSQLTimestamp		= 93;	/* CLI: SQL_TYPE_TIMESTAMP*/
const short IldSQLTimeTZ		= 94;	/* CLI: SQL_TYPE_TIME_WITH_TIMEZONE*/
const short IldSQLTimestampTZ		= 95;	/* CLI: SQL_TYPE_TIMESTAMP_WITH_TIMEZONE*/
const short IldSQLIntervalYear		= 101;	/* CLI: SQL_INTERVAL_YEAR*/
const short IldSQLIntervalMonth		= 102;	/* CLI: SQL_INTERVAL_MONTH*/
const short IldSQLIntervalDay		= 103;	/* CLI: SQL_INTERVAL_DAY*/
const short IldSQLIntervalHour		= 104;	/* CLI: SQL_INTERVAL_HOUR*/
const short IldSQLIntervalMinute	= 105;	/* CLI: SQL_INTERVAL_MINUTE*/
const short IldSQLIntervalSecomd	= 106;	/* CLI: SQL_INTERVAL_SECOND*/
const short IldSQLIntervalYM		= 107;	/* CLI: SQL_INTERVAL_YEAR_TO_MONTH*/
const short IldSQLIntervalDH		= 108;	/* CLI: SQL_INTERVAL_DAY_TO_HOUR*/
const short IldSQLIntervalDM		= 109;	/* CLI: SQL_INTERVAL_DAY_TO_MINUTE*/
const short IldSQLIntervalDS		= 110;	/* CLI: SQL_INTERVAL_DAY_TO_SECOND*/
const short IldSQLIntervalHM		= 111;	/* CLI: SQL_INTERVAL_HOUR_TO_MINUTE*/
const short IldSQLIntervalHS		= 112;	/* CLI: SQL_INTERVAL_HOUR_TO_SECOND*/
const short IldSQLIntervalMS		= 113;	/* CLI: SQL_INTERVAL_MINUTE_TO_SECOND*/

#define IldSQLMinType			IldSQLCursor
#define IldSQLMaxType			IldSQLIntervalMS

#endif /* __ILD_ILDCONST_H */
