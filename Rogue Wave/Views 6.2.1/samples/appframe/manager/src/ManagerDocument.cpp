// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/src/ManagerDocument.cpp
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
// File generated Wed Mar 08 20:35:33 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <ManagerDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// ManagerDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(ManagerDocument)
IlvDvEndInterface1(IlvDvManagerDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
ManagerDocument::ManagerDocument()
: IlvDvManagerDocument()
{
}

// --------------------------------------------------------------------------
ManagerDocument::~ManagerDocument()
{
}

// --------------------------------------------------------------------------
// Overridables

IlvBoolean
ManagerDocument::initializeDocument(IlAny data)
{
    if (!IlvDvManagerDocument::initializeDocument(data))
        return IlFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlTrue;
}

// --------------------------------------------------------------------------
void
ManagerDocument::clean()
{
    IlvDvManagerDocument::clean();
    // This method is called while destroying the document or
    // before the newDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
// IO
void
ManagerDocument::serialize(IlvDvStream& stream)
{
    IlvDvManagerDocument::serialize(stream);
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

IlvDvPreRegisterDynClass(ManagerDocument, IlvDvManagerDocument);

IL_BEGINMODULEINITDEF(ManagerDocument)
    IlvDvPostRegisterDynClass(ManagerDocument, IlvDvManagerDocument);
IL_ENDMODULEINITDEF(ManagerDocument)

#if !defined(ILVBUILDLIBS)
static int ManagerDocument_ini = (IL_MODINIT(ManagerDocument)(), 0);
#endif


