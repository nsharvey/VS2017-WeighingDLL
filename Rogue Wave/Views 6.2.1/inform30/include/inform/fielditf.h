// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/fielditf.h
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
#ifndef __Ili_Compat_Fielditf_H
#define __Ili_Compat_Fielditf_H

#include <ilviews/dataccess/fielditf.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwFieldItf IliFieldItf
#define IlvSwIsAField IliIsAField
#define IlvSwGraphicToField IliGraphicToField
#define IlvSwFieldAccessorTag IliFieldAccessorTag
#define IlvSwAccValue IliAccValue
#define IlvSwAccAlignment IliAccAlignment
#define IlvSwAccDataSourceColumnName IliAccDataSourceColumnName
#define IlvSwAccCompletion IliAccCompletion
#define IlvSwAccContrained IliAccContrained
#define IlvSwAccDataSourceName IliAccDataSourceName
#define IlvSwAccForeignDataSourceName IliAccForeignDataSourceName
#define IlvSwAccForeignDisplayColumnName IliAccForeignDisplayColumnName
#define IlvSwAccForeignValueColumnName IliAccForeignValueColumnName
#define IlvSwAccFormat IliAccFormat
#define IlvSwAccInputModified IliAccInputModified
#define IlvSwAccLabel IliAccLabel
#define IlvSwAccMask IliAccMask
#define IlvSwAccMaxLength IliAccMaxLength
#define IlvSwAccReadOnly IliAccReadOnly
#define IlvSwAccVisibleRowsCount IliAccVisibleRowsCount
#define IlvSwAccTagsCount IliAccTagsCount
#define IlvSwSupportsAccessors IliSupportsAccessors
#define IlvSwInputPolicy IliInputPolicy
#define IlvSwDefaultInputPolicy IliDefaultInputPolicy
#define IlvSwStandardInputPolicy IliStandardInputPolicy
#define IlvSwLocalInputPolicy IliLocalInputPolicy
#endif

#endif
