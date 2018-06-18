// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/stylable.h
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
// Declaration of the IlvStylable abstract class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Stylable_H
#define __Ilv_Base_Stylable_H

#if !defined(__Ilv_Base_Stylist_H)
#  include <ilviews/base/stylist.h>
#endif

class IlvDisplay;
class IlvPalette;
class IlvStylist;
class IlSymbol;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvStylable
{
public:
    IlvStylable() {}
    virtual ~IlvStylable();

    virtual IlvDisplay*	getStylableDisplay() const = 0;
    virtual IlvStylist*	getStylist() const = 0;
    virtual const char*	getStylableClassName() const;
    virtual const char*	getStylableName() const;
    virtual const IlSymbol* const* getStylableTags(IlUInt& nTags) const;
    virtual const IlvStylable* getStylableParent() const;
    /*
     * TODO [AME]: Remove this method when possible
     */
    virtual const IlvStylable*	getStylable() const;

    enum State
    {
	EmptyState	= 0,
	HasNameState	= (1 << 0),
	HasFocusState	= (1 << 1),
	IsHoverState	= (1 << 2),
	IsActiveState	= (1 << 3),
	IsEnabledState	= (1 << 4),
	IsCheckedState	= (1 << 5)
    };
    virtual State	getStylableState() const;

    const IlvPalette*
	getStylePalette(const IlvPalette*		source,
			IlvStylist::PaletteElements	elements,
			IlvStylist::Hint		hint = 0) const;

    const IlvColor*	getStyleColor(const IlvColor*	source,
				      IlvStylist::Hint	hint = 0) const;

    // Convenient method to allow the use of bitwise operators
    inline const IlvPalette*	getStylePalette(const IlvPalette* s,
						int		  e,
						IlvStylist::Hint  h =0) const
	{
	    return getStylePalette(s,
				   IL_CAST(IlvStylist::PaletteElements, e),
				   h);
	}
};

// --------------------------------------------------------------------------
inline IlvStylable::State
operator&(IlvStylable::State a, IlvStylable::State b)
{
    return IL_CAST(IlvStylable::State, IL_CAST(int, a) & IL_CAST(int, b));
}

// --------------------------------------------------------------------------
inline IlvStylable::State
operator|(IlvStylable::State a, IlvStylable::State b)
{
    return IL_CAST(IlvStylable::State, IL_CAST(int, a) | IL_CAST(int, b));
}

// --------------------------------------------------------------------------
inline IlvStylable::State&
operator|=(IlvStylable::State& a, IlvStylable::State b)
{
    IlvStylable::State r = a | b;
    return a = r;
}

#endif /* !__Ilv_Base_Stylable_H */
