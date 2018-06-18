// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/ProjectDocument.cpp
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
// IlogViews 4 generated source file
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <ProjectDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// ProjectDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(ProjectDocument)
IlvDvEndInterface1(IlvDvProjectDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
ProjectDocument::ProjectDocument()
    : IlvDvProjectDocument()
{
}

// --------------------------------------------------------------------------
ProjectDocument::~ProjectDocument()
{
}

// --------------------------------------------------------------------------
// Overridables

IlBoolean
ProjectDocument::initializeDocument(IlAny data)
{
    if (!IlvDvProjectDocument::initializeDocument(data))
        return IlFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlTrue;
}

// --------------------------------------------------------------------------
void
ProjectDocument::clean()
{
    IlvDvProjectDocument::clean();
    // This method is called while destroying the document or
    // before the initializeDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
// IO
void
ProjectDocument::serialize(IlvDvStream& stream)
{
    IlvDvProjectDocument::serialize(stream);
    if (stream.isSaving()) {
        // Here, write data your persistent data
    }
    else {
        // This document has been created while executing command Open
        // Here, read data from stream
    }
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterDynClass(ProjectDocument, IlvDvProjectDocument);

IL_BEGINMODULEINITDEF(ProjectDocument)
    IlvDvPostRegisterDynClass(ProjectDocument, IlvDvProjectDocument);
IL_ENDMODULEINITDEF(ProjectDocument)

#if !defined(ILVBUILDLIBS)
static int ProjectDocument_ini = (IL_MODINIT(ProjectDocument)(), 0);
#endif


