// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/util.h
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
#ifndef __Ili_Compat_Util_H
#define __Ili_Compat_Util_H

#include <ilviews/dataccess/util.h>

#ifdef ILI_COMPAT_PREFIX
#  define IlvSwOnError         IliOnError
#  define IlvSwWriteString     IliWriteString
#  define IlvSwReadString      IliReadString
#  define IlvSwReadIdentifier  IliReadIdentifier
#  define IlvSwShrinkRect      IliShrinkRect
#  define IlvSwSetRectRight    IliSetRectRight
#  define IlvSwSetRectLeft     IliSetRectLeft
#  define IlvSwSetRectTop      IliSetRectTop
#  define IlvSwSetRectBottom   IliSetRectBottom
#  define IlvSwCenterInView    IliCenterInView
#  define IlvSwForceButtonUp   IliForceButtonUp
#  define IlvSwErrorBox        IliErrorBox
#  define IlvSwMessageBox      IliMessageBox
#  define IlvSwAskYesNo        IliAskYesNo
#  define IlvSwAskYesNoCancel  IliAskYesNoCancel
#  define IlvSwCopyAttachments IliCopyAttachments
#  define IlvSwFillDialog      IliFillDialog
#  define IlvSwSortArray       IliSortArray
#endif

#endif
