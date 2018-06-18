// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/macros.h
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
// Declaration of miscellaneous macros
// --------------------------------------------------------------------------
#ifndef __Ili_Macros_H
#define __Ili_Macros_H

// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------
#define ILIBF(n) : n

// --------------------------------------------------------------------------
// Macros
// --------------------------------------------------------------------------
#if !defined(IL_STD) && defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5 
#  include <iostream.h>
#  if 1
     using std::streampos;
     using std::ws;
#  endif
#endif

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

// Dll export macros

#if defined(WINDOWS) && defined(ILVDLL)
#  if !defined(ILINODLL)
#    if !defined(ILIDLL)
#      define ILIDLL
#    endif
#  endif
#endif

#if defined(WINDOWS) && defined(ILIDLL)
#  if defined(__TCPLUSPLUS__)
#      define ILI_BASE_EXPORTED        _export
#      define ILI_BASE_IMPORTED        _import
#      define ILV_DEF_EXPORTEDFN(type)   type ILI_BASE_EXPORTED
#      define ILV_DEF_IMPORTEDFN(type)   type ILI_BASE_IMPORTED
#  elif defined(_MSC_VER)
#    if defined(WIN32)
#      define ILI_BASE_EXPORTED        _declspec(dllexport)
#      define ILI_BASE_IMPORTED        _declspec(dllimport)
#      define ILV_DEF_EXPORTEDFN(type)   ILI_BASE_EXPORTED type
#      define ILV_DEF_IMPORTEDFN(type)   ILI_BASE_IMPORTED type
#    else // WIN32
#      define ILI_BASE_EXPORTED        _export
#      define ILI_BASE_IMPORTED        _import
#      define ILV_DEF_EXPORTEDFN(type)   type ILI_BASE_EXPORTED
#      define ILV_DEF_IMPORTEDFN(type)   type ILI_BASE_IMPORTED
#    endif // WIN32
#  endif
#endif // WINDOWS && ILIDLL

#if !defined(ILI_BASE_EXPORTED)
#  define ILI_BASE_EXPORTED
#endif

#if !defined(ILI_BASE_IMPORTED)
#  define ILI_BASE_IMPORTED
#endif

#if !defined(ILV_DEF_EXPORTEDFN)
#  define ILV_DEF_EXPORTEDFN(type) type
#endif

#if !defined(ILV_DEF_IMPORTEDFN)
#  define ILV_DEF_IMPORTEDFN(type) type
#endif

// ----------------------------------------------------------

#if defined(ILVLIB_dataccess)
#  define ILV_INF_EXPORTED ILI_BASE_EXPORTED
#  define ILV_INF_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_INF_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbgadget)
#  define ILV_DBG_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBG_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBG_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbsqlgad)
#  define ILV_DBSQLG_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSQLG_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSQLG_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstudio)
#  define ILV_DBS_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBS_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBS_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstgant)
#  define ILV_DBSGANTT_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSGANTT_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSGANTT_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstgrap)
#  define ILV_DBSGRAPH_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSGRAPH_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSGRAPH_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstchart)
#  define ILV_DBSTCHART_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSTCHART_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSTCHART_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstchart30)
#  define ILV_DBSCHART_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSCHART_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSCHART_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbstsql)
#  define ILV_DBSSQL_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBSSQL_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBSSQL_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbaccess)
#  define ILV_DBI_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBI_EXPORTEDFN(type) ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBI_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbchart)
#  define ILV_DACHART_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DACHART_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DACHART_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbchart30)
#  define ILV_DBCHART_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBCHART_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBCHART_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbgantt)
#  define ILV_DBGANTT_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBGANTT_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBGANTT_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_dbgraphe)
#  define ILV_DBGRAPHE_EXPORTED ILI_BASE_EXPORTED
#  define ILV_DBGRAPHE_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_DBGRAPHE_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

// -------------------------------------------------

#if !defined(ILV_INF_EXPORTED)
#  define ILV_INF_EXPORTED ILI_BASE_IMPORTED
#  define ILV_INF_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_INF_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBG_EXPORTED)
#  define ILV_DBG_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBG_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBG_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSQLG_EXPORTED)
#  define ILV_DBSQLG_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSQLG_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSQLG_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBS_EXPORTED)
#  define ILV_DBS_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBS_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBS_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSGANTT_EXPORTED)
#  define ILV_DBSGANTT_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSGANTT_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSGANTT_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSGRAPH_EXPORTED)
#  define ILV_DBSGRAPH_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSGRAPH_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSGRAPH_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSTCHART_EXPORTED)
#  define ILV_DBSTCHART_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSTCHART_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSTCHART_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSCHART_EXPORTED)
#  define ILV_DBSCHART_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSCHART_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSCHART_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBSSQL_EXPORTED)
#  define ILV_DBSSQL_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBSSQL_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBSSQL_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBI_EXPORTED)
#  define ILV_DBI_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBI_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBI_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DACHART_EXPORTED)
#  define ILV_DACHART_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DACHART_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DACHART_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBCHART_EXPORTED)
#  define ILV_DBCHART_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBCHART_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBCHART_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBGANTT_EXPORTED)
#  define ILV_DBGANTT_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBGANTT_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBGANTT_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_DBGRAPHE_EXPORTED)
#  define ILV_DBGRAPHE_EXPORTED ILI_BASE_IMPORTED
#  define ILV_DBGRAPHE_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_DBGRAPHE_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

// -------------------------------------------------

#if defined(WINDOWS) && !defined(WIN32)
#  define ILI_NOSTATICDATA
#endif

#endif
