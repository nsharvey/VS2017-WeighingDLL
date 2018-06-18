// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/macros1x.h
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
// Rogue Wave Views compatibility package.
// General purpose macro definitions - compatibility with versions < 2.0
// --------------------------------------------------------------------------

#ifndef __Ilv1x_Macros_H
#define __Ilv1x_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVVIEWS1X)
#  define ILV1XVWSEXPORTED IL_BASEEXPORTED
#  define ILV1XVWSEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILV1XVWSEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILV1XVWSLIB */

#if !defined(ILV1XVWSEXPORTED)
#  define ILV1XVWSEXPORTED IL_BASEIMPORTED
#  define ILV1XVWSEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILV1XVWSEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILV1XVWSEXPORTED */

// Static initialization macros
#define ILV1XVWSMODULEINIT(m) IL_MODULEINIT(m, ILV1XVWSEXPORTED)
#define ILV1XVWSMODULETERM(m) IL_MODULETERM(m, ILV1XVWSEXPORTED)

#endif /* __Ilv1X_Macros_H */
