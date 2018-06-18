// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/atmacros.h
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
// Equivalent of ilviews/macros.h for the IlvAnnoText package
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Atmacros_H
#define __Ilv_Annotext_Atmacros_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif

typedef IlUInt IlvATPos;

#if defined(ILVATLIB)
#  define ILVATEXPORTED IL_BASEEXPORTED
#  define ILVATEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVATEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVATLIB */
#  define ILVATEXPORTED IL_BASEIMPORTED
#  define ILVATEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVATEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVATLIB */

// Static initialization macros
#define ILVATMODULEINIT(m) IL_MODULEINIT(m, ILVATEXPORTED)
#define ILVATMODULETERM(m) IL_MODULETERM(m, ILVATEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvatext.lib")
#endif

#endif /* !__Ilv_Annotext_Atmacros_H */
