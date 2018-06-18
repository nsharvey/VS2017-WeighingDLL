// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gencom.h
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
// Declaration of generic commands
// --------------------------------------------------------------------------
#ifndef __IlvSt_Gencom_H
#define __IlvSt_Cencom_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

extern ILVSTEXPORTEDVAR(const char*) IlvNmOpenDocument;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveDocument;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveDocumentAs;
extern ILVSTEXPORTEDVAR(const char*) IlvNmCloseDocument;
extern ILVSTEXPORTEDVAR(const char*) IlvNmTest;
extern ILVSTEXPORTEDVAR(const char*) IlvNmInspect;

class IlvStudio;

extern void IlvRegisterGenericCommands(IlvStudio*);

#endif /* __IlvSt_Gencom_H */
