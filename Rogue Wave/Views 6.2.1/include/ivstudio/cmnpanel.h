// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/cmnpanel.h
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
// Declaration of common panels
// --------------------------------------------------------------------------
#ifndef __IlvSt_Cmnpanel_H
#define __IlvSt_Cmnpanel_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
class IlvStudio;

extern ILVSTEXPORTEDFUNC(void) IlvStMakeCommonPanels(IlvStudio*);
extern ILVSTEXPORTEDFUNC(void) IlvStRegisterCommonPanelCommands(IlvStudio*);

extern ILVEXPORTEDDEF(const char*) IlvNmToggleGrid;
extern ILVEXPORTEDDEF(const char*) IlvNmToggleActiveGrid;
extern ILVEXPORTEDDEF(const char*) IlvNmToggleForegroundGrid;

#endif /* __IlvSt_Cmnpanel_H */
