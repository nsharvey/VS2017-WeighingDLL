// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/spring/src/centerpin.cpp
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

#include <centerpin.h>

IlvCenterPin::IlvCenterPin(IlvInputFile& input,
			   IlvSymbol* s)
    : IlvGrapherPin(input, s)
{
}

// --------------------------------------------------------------------------
IlvCenterPin::IlvCenterPin(const IlvCenterPin& src)
    : IlvGrapherPin(src)
{
}

// --------------------------------------------------------------------------
IlvUInt 
IlvCenterPin::getCardinal(const IlvGraphic*,
			  const IlvTransformer*) const	
{ 
    return 1; 
}

// --------------------------------------------------------------------------
IlBoolean
IlvCenterPin::getLocation(IlUInt, 
			  const IlvGraphic* node,
			  const IlvTransformer* t, 
			  IlvPoint& where) const
{
    IlvRect bbox;
    node->boundingBox(bbox, t);
    where.move(bbox.centerx(), bbox.centery());
    return IlTrue;
}

// --------------------------------------------------------------------------
IlvPredefinedPropertyIOMembers(IlvCenterPin)
IlvRegisterPropertyClass(IlvCenterPin, IlvGrapherPin);
