// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/progdcnt.h
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
// Prototype containers.
// ---------------------------------------------------------------------------
#ifndef __Ilv_Protos_Progdcnt_H
#define __Ilv_Protos_Progdcnt_H

#undef  ILVEXPORTPROCLASS
#define ILVEXPORTPROCLASS ILVGDPEXPORTED

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Protos_Proto_H)
#include <ilviews/protos/proto.h>
#endif
#if !defined(__Ilv_Protos_Progdmgr_h)
#include <ilviews/protos/progdmgr.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
// ---------------------------------------------------------------------------
// Container classes (for Studio code generation).
// ---------------------------------------------------------------------------

ILV_DECLARE_PC_CLASS(IlvProtoGadgetContainer, IlvGadgetContainer,\
		     IlvProtoGadgetViewInputFile, IlvGadgetViewInputFile,\
		     IlvProtoGadgetViewVSInputFile)

#endif /* !__Ilv_Protos_Progdcnt_H */
