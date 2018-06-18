// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/dbstudio/assist.h
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
#ifndef __Ili_Compat_Assist_H
#define __Ili_Compat_Assist_H

#include <ilviews/dataccess/dbstudio/assist.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwOptNavigator IliOptNavigator
#define IlvSwOptNavigNavigation IliOptNavigNavigation
#define IlvSwOptNavigInsert IliOptNavigInsert
#define IlvSwOptNavigDelete IliOptNavigDelete
#define IlvSwOptNavigValidation IliOptNavigValidation
#define IlvSwOptNavigSelect IliOptNavigSelect
#define IlvSwOptNavigClear IliOptNavigClear
#define IlvSwOptNavigPosition IliOptNavigPosition
#define IlvSwOptNavigRowsCount IliOptNavigRowsCount
#define IlvSwOptNavigNbTag IliOptNavigNbTag
#define IlvSwNavigatorPosition IliNavigatorPosition
#define IlvSwNavigPosTop IliNavigPosTop
#define IlvSwNavigPosBottom IliNavigPosBottom
#define IlvSwNavigPosNbTag IliNavigPosNbTag
#define IlvSwLayoutField IliLayoutField
#define IlvSwTopToBottom IliTopToBottom
#define IlvSwLeftToRight IliLeftToRight
#define IlvSwLayoutFieldNbTag IliLayoutFieldNbTag
#define IlvSwColorType IliColorType
#define IlvSwColorTitle IliColorTitle
#define IlvSwColorLabel IliColorLabel
#define IlvSwColorField IliColorField
#define IlvSwColorTypeNbTag IliColorTypeNbTag
#define IlvSwFontType IliFontType
#define IlvSwFontTitle IliFontTitle
#define IlvSwFontLabel IliFontLabel
#define IlvSwFontField IliFontField
#define IlvSwFontTypeNbTag IliFontTypeNbTag
#define IlvSwAssistDefine IliAssistDefine
#define IlvSwAssistDialog IliAssistDialog
#define IlvSwAssistant IliAssistant
#endif

#endif
