// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapDocument.cpp
// IlogViews 4 generated source file
// File generated Tue Jun 13 15:11:29 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <BitmapDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// BitmapDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(BitmapDocument)
IlvDvEndInterface1(IlvDvDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
BitmapDocument::BitmapDocument()
: IlvDvDocument()
{
}

// --------------------------------------------------------------------------
BitmapDocument::~BitmapDocument()
{
}

// --------------------------------------------------------------------------
// Overridables

IlvBoolean
BitmapDocument::initializeDocument(IlvAny data)
{
    if (!IlvDvDocument::initializeDocument(data))
        return IlvFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlvTrue;
}

// --------------------------------------------------------------------------
void
BitmapDocument::clean()
{
    IlvDvDocument::clean();
    // This method is called while destroying the document or
    // before the initializeDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
// IO
void
BitmapDocument::serialize(IlvDvStream& stream)
{
    IlvDvDocument::serialize(stream);
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

IlvDvPreRegisterDynClass(BitmapDocument, IlvDvDocument);

IL_BEGINMODULEINITDEF(BitmapDocument)
    IlvDvPostRegisterDynClass(BitmapDocument, IlvDvDocument);
IL_ENDMODULEINITDEF(BitmapDocument)

#if !defined(ILVBUILDLIBS)
static int BitmapDocument_ini = (IL_MODINIT(BitmapDocument)(), 0);
#endif


