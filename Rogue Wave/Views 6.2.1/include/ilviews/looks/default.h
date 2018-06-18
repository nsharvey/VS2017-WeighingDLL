// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/default.h
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
// Default look registration
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Default_H
#define __Ilv_Looks_Default_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif

#if defined(WINDOWS)
#  if !defined(__Ilv_Windows_H)
#    include <ilviews/windows.h>
#  endif
#  if defined(WIN32)
#    if !defined(__Ilv_Win95_H)
#      include <ilviews/win95.h>
#    endif
#    if (WINVER >= 0x501)
#      if !defined(__Ilv_Winxp_H)
#        include <ilviews/winxp.h>
#      endif
#    endif /* WINVER >= 0x501 */
#  endif /* WIN32 */
#else /* !WINDOWS */
#  if !defined(__Ilv_Vx_H)
#    include <ilviews/vx.h>
#  endif
#endif /* !WINDOWS */

// --------------------------------------------------------------------------
#if defined(ILVMOTIFLOOK)
#  if !defined(__Ilv_Looks_Motif_H)
#    include <ilviews/looks/motif.h>
#  endif
#endif
#if defined(ILVWINDOWSLOOK)
#  if !defined(__Ilv_Looks_Windows_H)
#    include <ilviews/looks/windows.h>
#  endif
#endif
#if defined(ILVWINDOWS95LOOK)
#  if !defined(__Ilv_Looks_Win95_H)
#    include <ilviews/looks/win95.h>
#  endif
#endif
#if defined(ILVVXLOOK)
#  if !defined(__Ilv_Looks_Vx_H)
#    include <ilviews/looks/vx.h>
#  endif
#endif
#if defined(ILVWINDOWSXPLOOK)
#  if !defined(__Ilv_Looks_Winxp_H)
#    include <ilviews/looks/winxp.h>
#  endif
#endif

#endif /* !__Ilv_Looks_Default_H */
