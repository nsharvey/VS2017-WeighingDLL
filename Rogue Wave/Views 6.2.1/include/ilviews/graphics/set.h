// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/set.h
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
// Declaration of the IlvGraphicSet class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Set_H
#define __Ilv_Graphics_Set_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif

#define IlvDefaultSetSpacing 4

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicSet : public IlvGraphic
{
public:
    IlvGraphicSet() : _list(), _alpha(IlvFullIntensity) {}
    IlvGraphicSet(int num ...);
    ~IlvGraphicSet();

    void		emptyList();
    virtual IlvDisplay*	getDisplay() const;
    inline IlList*	getList() { return &_list; }

    virtual void	apply(IlvApplyObject function, IlAny arg);
    virtual void	applyReferences(IlvApplyObject function , IlAny arg);
    inline IlUInt	getCardinal() const { return _list.getLength(); }
    inline IlvGraphic* const*	getObjects(IlUInt& count) const
	{ return getChildren(count); }
    inline IlvGraphic*	getObject(IlUInt index) const
	{ return (IlvGraphic*)_list.getValue(index); }
    inline IlInt	getIndex(IlvGraphic* object) const
	{ return getChildIndex(object); }
    void		setObject(IlUInt index, IlvGraphic* object);
    IlvGraphic*		firstContains(const IlvPoint&		p,
				      const IlvPoint&		tp,
				      const IlvTransformer*	t = 0) const;
    IlvGraphic*		firstIntersects(const IlvRegion&      region,
					const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&,
				   const IlvTransformer* = 0) const;
    virtual IlBoolean	inside(const IlvRegion&,
			       const IlvTransformer* = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion*      = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*,
				    const IlvTransformer* = 0,
				    const IlvRegion*      = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual void	symmetry(IlvDirection);
    virtual IlBoolean	zoomable() const;
    virtual void	setHolder(IlvGraphicHolder*);
    virtual IlUInt	getChildCount() const;
    virtual IlvGraphic*	getChildAt(IlUInt) const;
    virtual IlvGraphic*	getChildByName(const char*) const;
    virtual IlInt	getChildIndex(const IlvGraphic*) const;
    virtual void	removeObject(IlvGraphic* object);
    virtual void	insertObject(IlvGraphic* object);
    virtual void	addObject(IlvGraphic* obj);
    virtual void	setPalette(IlvPalette*);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setPattern(IlvPattern*);
    virtual void	setGradientPattern(IlvGradientPattern*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	invert(IlBoolean = IlFalse);
    virtual
    IlvIntensity	getAlpha() const;
    virtual IlUShort	getLineWidth() const;
    void		align(IlvPosition align = IlvLeft);
    void		sameWidth(IlvDim width);
    void		sameHeight(IlvDim height);
    void		row(IlvDeltaPos spacing = IlvDefaultSetSpacing);
    void		column(IlvDeltaPos spacing = IlvDefaultSetSpacing);
    virtual void	print(ILVSTDPREF ostream&, int = 0) const;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    static IlSymbol*	GetCardinalValue();
    static IlSymbol*	GetGetObjectAtMethod();

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGraphicSet);

protected:
    IlList		_list;
    IlvIntensity	_alpha;
};

ILVVWSMODULEINIT(g0set);
#endif /* !__Ilv_Graphics_Set_H */
