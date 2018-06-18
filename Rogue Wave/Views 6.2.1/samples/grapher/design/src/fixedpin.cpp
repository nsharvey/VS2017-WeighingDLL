// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/design/src/fixedpin.cpp
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
// 
// --------------------------------------------------------------------------

#include <fixedpin.h>

#if defined(IL_STD)
IL_STDUSE
#include <fstream>
#include <cstdarg>
#include <cstring>
#else
#include <fstream.h>
#include <stdarg.h>
#include <string.h>
#endif

// --------------------------------------------------------------------------
// - Constructors
FixedPin::FixedPin(IlUInt nPins ...)
    : IlvGrapherPin(),
      _nPins(nPins),
      _deltaPos(0)
{
    va_list ap;
    va_start(ap, nPins);
    _deltaPos  = new IlvDeltaPoint[nPins];
    IlvDeltaPos delta;
    for (IlUInt i = 0; i < nPins; ++i) {
	delta = IL_CAST(IlvDeltaPos, va_arg(ap, int));
	_deltaPos[i].x(delta);
	delta = IL_CAST(IlvDeltaPos, va_arg(ap, int));
	_deltaPos[i].y(delta);
    }
    va_end(ap);
}

// --------------------------------------------------------------------------
FixedPin::FixedPin(IlvInputFile& input,
		   IlvSymbol* s)
    : IlvGrapherPin(input, s),
      _nPins(0),
      _deltaPos(0)
{
    input.getStream() >> _nPins;
    if (_nPins) {
	_deltaPos  = new IlvDeltaPoint[_nPins];
	for (IlUInt i = 0; i < _nPins; ++i)
	    input.getStream() >> _deltaPos[i];
    }
}

// --------------------------------------------------------------------------
FixedPin::FixedPin(const FixedPin& src)
    : IlvGrapherPin(src),
      _nPins(src._nPins),
      _deltaPos(0)
{
    if (_nPins) {
	_deltaPos  = new IlvDeltaPoint[_nPins];
	memcpy(_deltaPos, src._deltaPos, _nPins * sizeof(IlvDeltaPoint));
    }
}

// --------------------------------------------------------------------------
FixedPin::~FixedPin()
{
    delete [] _deltaPos;    
}

// --------------------------------------------------------------------------
// - 
IlUInt 
FixedPin::getCardinal(const IlvGraphic*,
		      const IlvTransformer*) const	
{ 
    return _nPins; 
}

// --------------------------------------------------------------------------
IlBoolean
FixedPin::getLocation(IlUInt idx, 
		      const IlvGraphic* node,
		      const IlvTransformer* t,
		      IlvPoint& where) const
{
    if (idx > _nPins)
	return IlFalse;
    IlvRect bbox;
    node->boundingBox(bbox, t);
    where = bbox.upperLeft();
    where += _deltaPos[idx];
    return IlTrue;
}

// --------------------------------------------------------------------------
void
FixedPin::write(IlvOutputFile& output) const
{
    output.getStream() << IlvSpc() << _nPins;
    for (IlUInt i = 0; i < _nPins; ++i)
	output.getStream() << IlvSpc() << _deltaPos[i];
}

// --------------------------------------------------------------------------
IlvPredefinedPropertyIOMembers(FixedPin)
IlvPreRegisterPropertyClass(FixedPin);
static int initPin()
{
    IlvPostRegisterPropertyClass(FixedPin, IlvGrapherPin);
    return 0;
}
static int _initPin = initPin();
