// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/macrosadv.h
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
// General purpose macro definitions for Rogue Wave Views
// Windows XP advanced look & feel handlers
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Winxp_Macrosadv_H
#define __Ilv_Gadgets_Winxp_Macrosadv_H

#if !defined(__Ilv_Gadgets_Winxp_Macros_H)
#  include <ilviews/gadgets/winxp/macros.h>
#endif

#if defined(ILVADVWXPLOOKLIB)
#  define ILVADVWXPLOOKEXPORTED IL_BASEEXPORTED
#  define ILVADVWXPLOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVWXPLOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVADVWXPLOOKLIB */

#if !defined(ILVADVWXPLOOKEXPORTED)
#  define ILVADVWXPLOOKEXPORTED IL_BASEIMPORTED
#  define ILVADVWXPLOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVWXPLOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVADVWXPLOOKEXPORTED */

// Static initialization macros
#define ILVADVWXPLOOKMODULEINIT(m) IL_MODULEINIT(m, ILVADVWXPLOOKEXPORTED)
#define ILVADVWXPLOOKMODULETERM(m) IL_MODULETERM(m, ILVADVWXPLOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvawxplook.lib")
#endif

#endif /* __Ilv_Gadgets_Winxp_Macrosadv_H */
