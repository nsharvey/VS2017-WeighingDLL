// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/protos/provrmgr.h
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
// Definition of macros used for Prototypes and variables-enabled managers
// --------------------------------------------------------------------------

#ifndef __Ilv31_Protos_Provrmgr_H
#define __Ilv31_Protos_Provrmgr_H

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// provrmgr.h		Prototype + attributes/variables managers.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#define ILVEXPORTPROCLASS ILV31VRPEXPORTED
#include <ilviews/protos/macros31.h>

#include <ilviews/base/iostream.h>
#include <ilviews/attrmgr.h>
#include <ilviews/protos/protomgr.h>
#include <ilviews/varmgr.h>
#include <ilviews/vrgadmgr.h>

// ---------------------------------------------------------------------------
// IlvProtoAttributeManager
// IlvProtoAttributeManagerOutputFile
// IlvProtoAttributeManagerInputFile
// ---------------------------------------------------------------------------

ILV_DECLARE_PM_CLASS(IlvProtoAttributeManager, IlvAttributeManager,\
		     IlvProtoAttributeManagerInputFile, IlvAttributeManagerInputFile,\
		     IlvProtoAttributeManagerOutputFile, IlvAttributeManagerOutputFile,\
		     IlvProtoAttributeManagerVSInputFile, IlvValueSourceOutputFile)

// ---------------------------------------------------------------------------
// IlvProtoVariableManager
// IlvProtoVariableManagerOutputFile
// IlvProtoVariableManagerInputFile
// ---------------------------------------------------------------------------

ILV_DECLARE_PM_CLASS(IlvProtoVariableManager, IlvVariableManager,\
		     IlvProtoVariableManagerInputFile, IlvVariableManagerInputFile,\
		     IlvProtoVariableManagerOutputFile, IlvVariableManagerOutputFile,\
		     IlvProtoVariableManagerVSInputFile, IlvValueSourceOutputFile)

// ---------------------------------------------------------------------------
// IlvPrototypeVariableGadgetManager
// IlvPrototypeVariableGadgetManagerOutputFile
// IlvPrototypeVariableGadgetManagerInputFile
// ---------------------------------------------------------------------------

ILV_DECLARE_PM_CLASS(IlvPrototypeVariableGadgetManager, IlvVariableGadgetManager,\
		     IlvPrototypeVariableGadgetManagerInputFile, IlvVariableGadgetManagerInputFile,\
		     IlvPrototypeVariableGadgetManagerOutputFile, IlvVariableGadgetManagerOutputFile,\
		     IlvPrototypeVariableGadgetManagerVSInputFile, IlvValueSourceOutputFile)

#endif /* __Ilv_Protos_Provrmgr_H */
