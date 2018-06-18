// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/format.h
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
#ifndef __Ili_Compat_Format_H
#define __Ili_Compat_Format_H

#include <ilviews/dataccess/format.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwFormatType IliFormatType
#define IlvSwNullFormatType IliNullFormatType
#define IlvSwStringFormatType IliStringFormatType
#define IlvSwNumberFormatType IliNumberFormatType
#define IlvSwDateFormatType IliDateFormatType
#define IlvSwCurrencyPosition IliCurrencyPosition
#define IlvSwCP_AtLeft_NoSpace IliCP_AtLeft_NoSpace
#define IlvSwCP_AtLeft_Space IliCP_AtLeft_Space
#define IlvSwCP_AtRight_NoSpace IliCP_AtRight_NoSpace
#define IlvSwCP_AtRight_Space IliCP_AtRight_Space
#define IlvSwFormatCategory IliFormatCategory
#define IlvSwSystemFormat IliSystemFormat
#define IlvSwApplicationFormat IliApplicationFormat
#define IlvSwUserFormat IliUserFormat
#define IlvSwFormatAliasEntry IliFormatAliasEntry
#define IlvSwFormatIpl IliFormatIpl
#define IlvSwFormatLangSettings IliFormatLangSettings
#define IlvSwFormat IliFormat
#endif

#endif

