// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/design/include/fixedpin.h
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
// FixedPin class
// Implements pins which are stored as fixed position with respect to the
// bounding box of their associated nodes. This pin class is well suited for
// non-zoomable graphic objects such as IlvIcon.
// --------------------------------------------------------------------------
#ifndef __Ilv_GrapherSamples_Fixedpin_H
#define __Ilv_GrapherSamples_Fixedpin_H

#if !defined(__Ilv_Grapher_Pin_H)
#  include <ilviews/grapher/pin.h>
#endif

class FixedPin
    : public IlvGrapherPin
{
public:
    FixedPin(IlUInt nPins ...);
    virtual ~FixedPin();

    virtual IlUInt getCardinal(const IlvGraphic*,
			       const IlvTransformer*) const;

    virtual IlBoolean getLocation(IlUInt,
				  const IlvGraphic*,
				  const IlvTransformer* t,
				  IlvPoint&) const;
    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(FixedPin);

private:
    IlUInt	    _nPins;
    IlvDeltaPoint*  _deltaPos;
};

#endif /* __Ilv_GrapherSamples_Fixedpin_H */
