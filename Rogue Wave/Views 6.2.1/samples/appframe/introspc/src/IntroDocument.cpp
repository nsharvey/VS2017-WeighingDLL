// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/src/IntroDocument.cpp
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
// File generated Thu Mar 09 20:08:53 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <IntroDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// IntroDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(IntroDocument)
    Field(NameField, _name, const char*)
    Field(X, _x, IlInt)
    Field(Y, _y, IlInt)
    Field(IsScaling, _isScaling, IlBoolean)
    Field(ScaleFactor, _scaleFactor, IlFloat)
    Field(Price, _price, IlDouble)
    Method1(SetName, setName, const char*, Name)
    TypedMethod(GetName, getName, const char*)
    Method2(SetScaleFactor, setScaleFactor, IlBoolean, IsScaling, IlFloat, ScaleFactor)
    TypedMethod1(SetPrice, setPrice, IlDouble, Price, IlDouble)
    Action(RefreshValues, refreshValues)
IlvDvEndInterface1(IlvDvDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
IntroDocument::IntroDocument()
    : IlvDvDocument(),
      _name("Default name"),
      _x(12),
      _y(27),
      _isScaling(IlTrue),
      _scaleFactor((IlFloat)45.23),
      _price((IlDouble)456123.123)
{
}

// --------------------------------------------------------------------------
IntroDocument::~IntroDocument()
{
}

// --------------------------------------------------------------------------
// Overridables

IlBoolean
IntroDocument::initializeDocument(IlAny data)
{
    if (!IlvDvDocument::initializeDocument(data))
        return IlFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlTrue;
}

// --------------------------------------------------------------------------
void
IntroDocument::clean()
{
    IlvDvDocument::clean();
    // This method is called while destroying the document or
    // before the newDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
void
IntroDocument::setName(const char* name)
{
    _name = name;
}

// --------------------------------------------------------------------------
const char*
IntroDocument::getName()
{
    return _name;
}

// --------------------------------------------------------------------------
void
IntroDocument::setScaleFactor(IlBoolean isScaling,
			      IlFloat scaleFactor)
{
    _isScaling   = isScaling;
    _scaleFactor = scaleFactor;
}

// --------------------------------------------------------------------------
IlDouble
IntroDocument::setPrice(IlDouble price)
{
    IlDouble oldPrice = _price;
    _price = price;
    return oldPrice;
}

// --------------------------------------------------------------------------
void
IntroDocument::refreshValues()
{
    notifyViews(IlvGetSymbol("RefreshValues"), getCurrentCallerView());
}

// --------------------------------------------------------------------------
// IO
void
IntroDocument::serialize(IlvDvStream& stream)
{
    IlvDvDocument::serialize(stream);

    stream.serialize(_name);
    if (stream.isSaving()) {
        stream << _x << _y << _isScaling << _scaleFactor << _price;
    }
    else {
        stream >> _x >> _y >> _isScaling >> _scaleFactor >> _price;
    }
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterDynClass(IntroDocument, IlvDvDocument);

IL_BEGINMODULEINITDEF(IntroDocument)
    IlvDvPostRegisterDynClass(IntroDocument, IlvDvDocument);
IL_ENDMODULEINITDEF(IntroDocument)

#if !defined(ILVBUILDLIBS)
static int IntroDocument_ini = (IL_MODINIT(IntroDocument)(), 0);
#endif


