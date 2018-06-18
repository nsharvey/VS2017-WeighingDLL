// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/macros31.h
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
// General purpose macro definitions - compatibility with versions <= 3.1.*
// --------------------------------------------------------------------------

#ifndef __Ilv31_Macros_H
#define __Ilv31_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILV31VWSLIB)
#  define ILV31VWSEXPORTED IL_BASEEXPORTED
#  define ILV31VWSEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILV31VWSEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILV31VWSLIB */

#if !defined(ILV31VWSEXPORTED)
#  define ILV31VWSEXPORTED IL_BASEIMPORTED
#  define ILV31VWSEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILV31VWSEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILV31VWSEXPORTED */

// Static initialization macros
#define ILV31VWSMODULEINIT(m) IL_MODULEINIT(m, ILV31VWSEXPORTED)
#define ILV31VWSMODULETERM(m) IL_MODULETERM(m, ILV31VWSEXPORTED)

#if defined(ILV31EDTLIB)
#  define ILV31EDTEXPORTED IL_BASEEXPORTED
#  define ILV31EDTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILV31EDTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILV31EDTLIB */

#if !defined(ILV31EDTEXPORTED)
#  define ILV31EDTEXPORTED IL_BASEIMPORTED
#  define ILV31EDTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILV31EDTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILV31EDTEXPORTED */

// Static initialization macros
#define ILV31EDTMODULEINIT(m) IL_MODULEINIT(m, ILV31EDTEXPORTED)
#define ILV31EDTMODULETERM(m) IL_MODULETERM(m, ILV31EDTEXPORTED)

#if defined(ILV31GDTLIB)
#  define ILV31GDTEXPORTED IL_BASEEXPORTED
#  define ILV31GDTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILV31GDTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILV31GDTLIB */

#if !defined(ILV31GDTEXPORTED)
#  define ILV31GDTEXPORTED IL_BASEIMPORTED
#  define ILV31GDTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILV31GDTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILV31GDTEXPORTED */

// Static initialization macros
#define ILV31GDTMODULEINIT(m) IL_MODULEINIT(m, ILV31GDTEXPORTED)
#define ILV31GDTMODULETERM(m) IL_MODULETERM(m, ILV31GDTEXPORTED)

#if defined(ILV31VARLIB)
#  define ILV31VAREXPORTED IL_BASEEXPORTED
#  define ILV31VAREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILV31VAREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILV31VARLIB */

#if !defined(ILV31VAREXPORTED)
#  define ILV31VAREXPORTED IL_BASEIMPORTED
#  define ILV31VAREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILV31VAREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILV31VAREXPORTED */

// Static initialization macros
#define ILV31VARMODULEINIT(m) IL_MODULEINIT(m, ILV31VAREXPORTED)
#define ILV31VARMODULETERM(m) IL_MODULETERM(m, ILV31VAREXPORTED)

#endif /* __Ilv31_Macros_H */
