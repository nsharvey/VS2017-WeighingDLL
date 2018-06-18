// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/dblink.h
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
// Global include for end users
// ----------------------------------------------------------------------------

#ifndef __ILD_DBLINK_H
#define __ILD_DBLINK_H

#ifndef __ILD_ILDCONN_H
#include <ildblink/ildconn.h>
#endif
#ifndef __ILD_ILDDESC_H
# include <ildblink/ilddesc.h>
#endif
#ifndef __ILD_ILDENT_H
# include <ildblink/ildent.h>
#endif
#ifndef __ILD_ILDSYN_H
# include <ildblink/ildsyn.h>
#endif
#ifndef __ILD_ILDARG_H
# include <ildblink/ildarg.h>
#endif
#ifndef __ILD_ILDCALL_H
# include <ildblink/ildcall.h>
#endif
#ifndef __ILD_ILDADTD_H
# include <ildblink/ildadtd.h>
#endif
#ifndef __ILD_DBERR_H
#include <ildblink/dberr.h>
#endif
#ifndef __ILD_ILDVAL_H
#include <ildblink/ildval.h>
#endif
#ifndef __ILD_ILDADTVAL_H
#include <ildblink/ildadtval.h>
#endif

// ============================================================================
// Initialize DBLink threading environment
// ============================================================================
ILD_EXPORTEDFUNCTION(void) IldInitThreading();

// ============================================================================
// DB Link full version identifier
// ============================================================================
ILD_EXPORTEDFUNCTION(const char*) IldVersion();

// ============================================================================
// DB Link patch level
// ============================================================================
ILD_EXPORTEDFUNCTION(IlInt) IldPatchLevel();

// ============================================================================
// DB Link modules initialisation.
// ============================================================================
ILD_EXPORTEDFUNCTION(void) IldInitModule(const char* modName,
					    IldDbmsInitFunc initFunc);

// ============================================================================
// IldNewDbms inline function.
// ============================================================================
#ifdef ILDDB2
ILD_EXPORTEDFUNCTION(void) IldDb2InitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDINFORMIX
ILD_EXPORTEDFUNCTION(void) IldInformixInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDMSSQL
ILD_EXPORTEDFUNCTION(void) IldMssqlInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDMYSQL
ILD_EXPORTEDFUNCTION(void) IldMysqlInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDODBC
ILD_EXPORTEDFUNCTION(void) IldOdbcInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDOLEDB
ILD_EXPORTEDFUNCTION(void) IldOledbInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDOPING
ILD_EXPORTEDFUNCTION(void) IldOIInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDORACLE
ILD_EXPORTEDFUNCTION(void) IldOracleInitModule(IldInitModuleFunc initFunc);
#endif
#ifdef ILDSYBASE
ILD_EXPORTEDFUNCTION(void) IldSybaseInitModule(IldInitModuleFunc initFunc);
#endif

ILD_EXPORTEDFUNCTION(IlBoolean) IldCheckLinkMode();

inline void IldInitDbmsModule()
{
#ifdef ILDDB2
   IldDb2InitModule(IldInitModule);
#endif
#ifdef ILDINFORMIX
   IldInformixInitModule(IldInitModule);
#endif
#ifdef ILDMYSQL
   IldMysqlInitModule(IldInitModule);
#endif
#ifdef ILDODBC
   IldOdbcInitModule(IldInitModule);
#endif
#ifdef ILDOLEDB
   IldOledbInitModule(IldInitModule);
#endif
#ifdef ILDOPING
   IldOIInitModule(IldInitModule);
#endif
#ifdef ILDORACLE
   IldOracleInitModule(IldInitModule);
#endif
#ifdef ILDSYBASE
   IldSybaseInitModule(IldInitModule);
#endif
   IldCheckLinkMode();

}

static class IldInitDBLink {
public:
  IldInitDBLink() {
    IldInitDbmsModule();
  }
} _IldInitDBL;

#endif //__ILD_DBLINK_H
