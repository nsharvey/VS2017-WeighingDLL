// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/text/src/TextDocument.cpp
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
// File generated Thu Mar 09 20:27:35 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <TextDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// TextDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(TextDocument)
IlvDvEndInterface1(IlvDvTextDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
TextDocument::TextDocument()
: IlvDvTextDocument()
{
}

// --------------------------------------------------------------------------
TextDocument::~TextDocument()
{
}

// --------------------------------------------------------------------------
// Overridables

IlvBoolean
TextDocument::initializeDocument(IlAny data)
{
    if (!IlvDvTextDocument::initializeDocument(data))
        return IlFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlTrue;
}

// --------------------------------------------------------------------------
void
TextDocument::clean()
{
    IlvDvTextDocument::clean();
    // This method is called while destroying the document or
    // before the initializeDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
// IO
void
TextDocument::serialize(IlvDvStream& stream)
{
    IlvDvTextDocument::serialize(stream);
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

IlvDvPreRegisterDynClass(TextDocument, IlvDvTextDocument);

IL_BEGINMODULEINITDEF(TextDocument)
    IlvDvPostRegisterDynClass(TextDocument, IlvDvTextDocument);
IL_ENDMODULEINITDEF(TextDocument)

#if !defined(ILVBUILDLIBS)
static int TextDocument_ini = (IL_MODINIT(TextDocument)(), 0);
#endif
