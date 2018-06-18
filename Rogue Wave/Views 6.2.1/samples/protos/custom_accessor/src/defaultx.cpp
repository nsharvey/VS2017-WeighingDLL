// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/custom_accessor/src/defaultx.cpp
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
// Definition of IlvStDefaultExtension
// --------------------------------------------------------------------------

#include <ivstudio/defaultx.h>
#include <ivstudio/appli/applix.h>
#include <ivstudio/graphicx.h>
#include <ivstudio/grapher/grapher.h>
#include <ivstudio/gadgets/gadgetx.h>
#include <ivstudio/studio.h>

#ifdef WINDOWS
#include <ivstudio/windows/winext.h>
#endif

// --------------------------------------------------------------------------
static const char* ExtensionName = "DefaultExtension";

// --------------------------------------------------------------------------
IlvStDefaultExtension::IlvStDefaultExtension(IlvStudio* editor)
    : IlvStExtension(ExtensionName, editor)
{
    IlvStApplicationExtension::Make(editor);
    IlvStGraphicExtension::Make(editor);
    IlvStGadgetExtension::Make(editor);
    IlvStGrapherExtension::Make(editor);
#ifdef WINDOWS
    IlvStWindowsExtension::Make(editor);
#endif
} // IlvStDefaultExtension::IlvStDefaultExtension

// --------------------------------------------------------------------------
IlvStDefaultExtension*
IlvStDefaultExtension::Make(IlvStudio* editor)
{
    IlvStDefaultExtension* ext =
	(IlvStDefaultExtension*)editor->getExtension(ExtensionName);
    if (!ext)
	ext = new IlvStDefaultExtension(editor);
    return ext;
}

// --------------------------------------------------------------------------
