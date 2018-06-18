// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/contain/inter.h
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
// Declaration of predefined IlvViewObjectInteractor classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Contain_Inter_H
#define __Ilv_Contain_Inter_H

#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif

typedef IlvViewObjectInteractor* (*IlvViewInteractorConstructor)();
IL_DEFINEFPTRTOANYCAST(IlvViewInteractorConstructor);

ILVVWSEXPORTEDFUNCTION(int)
IlvRegisterViewInteractor(const char* name, IlvViewInteractorConstructor);
ILVVWSEXPORTEDFUNCTION(void)
IlvViewSaveInteractor(IlvViewObjectInteractor*, ILVSTDPREF ostream&);
ILVVWSEXPORTEDFUNCTION(IlvViewObjectInteractor*)
IlvViewReadInteractor(ILVSTDPREF istream&);

#if !defined(ILVDECLAREVIEWINTERACTOR)
#define ILVDECLAREVIEWINTERACTOR(name, classname) \
   static IlvViewObjectInteractor* name () { \
	  static IlvViewObjectInteractor* inter=0; \
	  if (!inter) inter = new classname (); \
	  return inter;}
#endif /* !ILVDECLAREVIEWINTERACTOR */

#define IlvLoadViewInteractor(classname) \
IlvViewObjectInteractor* _##classname = new classname ()

#endif /* !__Ilv_Contain_Inter_H */
