// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/transition.h
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
// Miscellaneous classes to handle transitions between two bitmap data.
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Transition_H
#define __Ilv_Bitmaps_Transition_H

#include <ilviews/bitmaps/data.h>
#include <ilog/array.h>

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBitmapTransition
{
public:
    IlvBitmapTransition() {}
    virtual ~IlvBitmapTransition();

    virtual void computeTransitionBitmapData(IlDouble oldRate,
					     IlDouble newRate,
					     const IlvRGBBitmapData& src,
					     const IlvRGBBitmapData& dst,
					     IlvRGBBitmapData& current,
					     IlvRegion& region) const = 0;
    static void Draw(IlvPort& dst,
		     const IlvPoint& at,
		     const IlvBitmapData& src,
		     const IlvRegion& region);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvAlphaBitmapTransition
: public IlvBitmapTransition
{
public:
    IlvAlphaBitmapTransition()
    : IlvBitmapTransition()
    {}

    virtual void computeTransitionBitmapData(IlDouble,
					     IlDouble,
					     const IlvRGBBitmapData&,
					     const IlvRGBBitmapData&,
					     IlvRGBBitmapData&,
					     IlvRegion&) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvSimpleBitmapTransition
: public IlvBitmapTransition
{
public:
    enum Transition {
	HorizontalTransition = 0x0001,
	VerticalTransition   = 0x0002,
	WipeLeft             = 0x0011,
	WipeRight            = 0x0021,
	WipeDown             = 0x0012,
	WipeUp               = 0x0022,
	BlindsHorizontal     = 0x0031, // Not implemented
	BlindsVertical       = 0x0032, // Not implemented
	BoxIn                = 0x0013,
	BoxOut               = 0x0023,
	SplitHorizontalIn    = 0x0041,
	SplitHorizontalOut   = 0x0051,
	SplitVerticalIn      = 0x0042,
	SplitVerticalOut     = 0x0052,
	StripLeftDown        = 0x0033, // Not implemented
	StripLeftUp          = 0x0043, // Not implemented
	StripRightDown       = 0x0053, // Not implemented
	StripRightUp         = 0x0063, // Not implemented
	SnailIn              = 0x0073,
	SnailOut             = 0x0083, // Not implemented
	BandVerticalIn       = 0x0062,
	BandHorizontalIn     = 0x0061
    };

    IlvSimpleBitmapTransition(Transition type)
    : IlvBitmapTransition(),
      _type(type)
    {}

    virtual void computeTransitionBitmapData(IlDouble,
					     IlDouble,
					     const IlvRGBBitmapData&,
					     const IlvRGBBitmapData&,
					     IlvRGBBitmapData&,
					     IlvRegion&) const;
    virtual void computeRect(const IlvRect&,
			     IlDouble,
			     IlvRegion&) const;

protected:
    Transition _type;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDissolveBitmapTransition
: public IlvBitmapTransition
{
public:
    IlvDissolveBitmapTransition(IlvDim size = 0);
    ~IlvDissolveBitmapTransition();

    virtual void computeTransitionBitmapData(IlDouble,
					     IlDouble,
					     const IlvRGBBitmapData&,
					     const IlvRGBBitmapData&,
					     IlvRGBBitmapData&,
					     IlvRegion&) const;
protected:
    IlvDim		_size;
    IL_MUTABLE IlArray  _cache;

    class Infos;
    Infos*	getInfos(IlvDim width, IlvDim height) const;
};

#endif /* !__Ilv_Bitmaps_Transition_H */
