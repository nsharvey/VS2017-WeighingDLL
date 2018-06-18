// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/winxp.h
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
//  Declaration of the ILVWINDOWSXPLOOK symbol
// --------------------------------------------------------------------------


#ifndef __Ilv_Winxp_H
#define __Ilv_Winxp_H

#include <ilviews/win95.h>

#if !defined(ILVWINDOWSXPLOOK) && !defined(IL_BUILDINGMODULE) && !defined(IL_BUILDLIBS)&& !defined(ILVBUILDLIBS) && !defined(IL_DLL) && !defined(ILVDLL) && defined(WINDOWS)
#define ILVWINDOWSXPLOOK
#endif

#endif /* __Ilv_Winxp_H */