// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/stylist.h
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
// Declaration of the IlvStylist abstract class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Stylist_H
#define __Ilv_Base_Stylist_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#include <list>

class IlvStyleSheet;
class IlvStylable;
class IlvPalette;
class IlvColor;
class IlvFont;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvStylist
{
public:
    typedef std::list<IlvStylist*> List;

    virtual ~IlvStylist();

    virtual IlvStylist*	getParentStylist() const = 0;
    IlBoolean		addStyleSheet(IlvStyleSheet* styleSheet);
    IlBoolean		removeStyleSheet(IlvStyleSheet* styleSheet);

    enum PaletteElements 
    {
	PaletteElementNone		= 0,
	PaletteElementBackgroundColor	= (1 << 0),
	PaletteElementForegroundColor	= (1 << 1),
	PaletteElementFont		= (1 << 2)
    };
    typedef IlUInt Hint;
    static const IlUInt	SwapColorsHint;
    static const IlUInt	TopShadowColorHint;
    static const IlUInt	BottomShadowColorHint;
    static const IlUInt	IntermediateShadowColorHint;

    class ILVDSPEXPORTED Style
    {
    public:
	virtual ~Style();

	static const Style*	Current();
	virtual
	const IlvPalette*	impactPalette(const IlvPalette*,
					      PaletteElements,
					      Hint) const;
	virtual const IlvColor* impactColor(const IlvColor*,
					    Hint) const;
	virtual IlvColor*	getBackground(const IlvStylable*,
					      Hint) const;
	virtual IlvColor*	getForeground(const IlvStylable*,
					      Hint) const;
	virtual IlvFont*	getFont(const IlvStylable*, Hint) const;

	static
	const IlvPalette*	ImpactPalette(const IlvPalette*	source,
					      PaletteElements,
					      Hint);
	static
	const IlvColor*	        ImpactColor(const IlvColor*	source,
					    Hint);
	inline
	const IlvStylable*	getStylable() const { return _stylable; }

    protected:
	Style(const IlvStylable* stylable) : _stylable(stylable) {}

    private:
	const IlvStylable*	_stylable;
	friend struct IlvStyleCache;
    };

    class ILVDSPEXPORTED Push 
    {
    public:
	Push(const IlvStylable*);
	~Push();

	struct		P;
	struct P*	_p;
    };

    Style*		queryStyle(const IlvStylable* stylable) const;
    const IlvPalette*	getStylePalette(const IlvStylable*,
					const IlvPalette* source,
					PaletteElements,
					Hint) const;
    const IlvColor*	getStyleColor(const IlvStylable*,
				      const IlvColor* source,
				      Hint) const;

protected:
    virtual std::list<IlvStyleSheet*>* getStyleSheetList(IlBoolean) const = 0;
    static void		release(std::list<IlvStyleSheet*>*);

private:
    void		addHierarchy(std::list<IlvStyleSheet*>&) const;
    void		removeFromStyleCache(IlBoolean) const;
    void		removeFromStyleCache(IlvStylable*) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvStyleQuery
{
public:
    virtual IlvStylist::Style* query(
		const IlvStylable* stylable,
		const std::list<IlvStyleSheet*>& styleSheets) const = 0;

protected:
    IlvStyleQuery() {}
    virtual ~IlvStyleQuery();

private:
    IlvStyleQuery(const IlvStyleQuery&);

    void operator	=(const IlvStyleQuery&);
};
#endif /* !__Ilv_Base_Stylist_H */
