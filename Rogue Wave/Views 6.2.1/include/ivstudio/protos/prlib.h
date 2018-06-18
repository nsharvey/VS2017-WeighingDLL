// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/prlib.h
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

#ifndef __prlib_h__
#define __prlib_h__

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// prlib.h		Include file for prstudio's main.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#include <ivstudio/protos/stproto.h>
#include <ivstudio/protos/prgadgets.h>
#include <ivstudio/protos/groupinsp.h>

#include <ilviews/manager/objinter.h>
#include <ilviews/protos/allaccs.h>

#include <ilviews/annotext/annotext.h>
#include <ilviews/annotext/html.h>

#if defined(sun) && !defined(__SVR4)
#include <ivstudio/protos/prlibini.h>
#endif /* SunOS 4 */

#endif /* __prlib_h__ */
