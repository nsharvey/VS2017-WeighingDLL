// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/progdmgr.h
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
// Definition of the IlvProtoGadgetManager class
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Progdmgr_h
#define __Ilv_Protos_Progdmgr_h

#undef  ILVEXPORTPROCLASS
#define ILVEXPORTPROCLASS ILVGDPEXPORTED

#if !defined(__Ilv_Gadmgr_Gadmgr_H)
#include <ilviews/gadmgr/gadmgr.h>
#endif
#if !defined(__Ilv_Protos_Protomgr_H)
#include <ilviews/protos/protomgr.h>
#endif

// ---------------------------------------------------------------------------
// IlvProtoGadgetManager: A sub-class of GadgetManager that handles groups and
//			prototype instances properly.
// IlvProtoGadgetManagerOutputFile
// IlvProtoGadgetManagerInputFile
// ---------------------------------------------------------------------------
ILV_DECLARE_PM_CLASS(IlvProtoGadgetManager, IlvGadgetManager,\
		     IlvProtoGadgetManagerInputFile, IlvGadgetManagerInputFile,\
		     IlvProtoGadgetManagerOutputFile, IlvGadgetManagerOutputFile,\
		     IlvProtoGadgetManagerVSInputFile, IlvValueSourceOutputFile)

#endif /* __Ilv_Protos_Progdmgr_H */
