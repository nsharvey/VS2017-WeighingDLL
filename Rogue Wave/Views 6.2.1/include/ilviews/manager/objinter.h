// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/objinter.h
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
// Declaration of the IlvManagerObjectInteractor class and predefined subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Objinter_H
#define __Ilv_Manager_Objinter_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

typedef IlvManagerObjectInteractor* (*IlvManagerInteractorConstructor)();
IL_DEFINEFPTRTOANYCAST(IlvManagerInteractorConstructor);

ILVMGREXPORTEDFUNCTION(int)
IlvRegisterManagerInteractor(const char* name,
			     IlvManagerInteractorConstructor);
ILVMGREXPORTEDFUNCTION(IlvManagerObjectInteractor*)
IlvGetManagerInteractor(const char* name, IlBoolean = IlTrue);
ILVMGREXPORTEDFUNCTION(void)
IlvManagerSaveInteractor(IlvManagerObjectInteractor*, ILVSTDPREF ostream&);
ILVMGREXPORTEDFUNCTION(IlvManagerObjectInteractor*)
IlvManagerReadInteractor(ILVSTDPREF istream&);
ILVMGREXPORTEDFUNCTION(const char* const*)
IlvGetManagerInteractorsArray(IlUInt& count,
			      IlBoolean sortStrings = IlTrue,
			      IlBoolean createArray = IlFalse);

#if !defined(ILVDECLAREMGRINTERACTOR)
#define ILVDECLAREMGRINTERACTOR(name, classname) \
static IlvManagerObjectInteractor* name() { \
    static IlvManagerObjectInteractor* inter=0; \
    return (inter ? inter : (inter = new classname())); }
#endif /* !ILVDECLAREMGRINTERACTOR */

#define IlvLoadMgrInteractor(classname) \
IlvManagerObjectInteractor* _##classname = new classname ()

#endif /* !__Ilv_Manager_Objinter_H */
