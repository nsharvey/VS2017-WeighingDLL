// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/handle.h
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
// Declaration of the IlvGraphicHandle and predefined subtypes classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Handle_H
#define __Ilv_Graphics_Handle_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicHandle : public IlvGraphic
{
public:
    IlvGraphicHandle(IlvGraphic* object, IlBoolean  owner = IlFalse)
	: IlvGraphic(),
	  _object(object),
	  _owner(owner),
	  _alpha(IlvFullIntensity)
    {}
    virtual ~IlvGraphicHandle();

    inline IlBoolean	isOwner() const { return _owner; }
    inline void		setOwner(IlBoolean flag) { _owner = flag; }
    inline IlvGraphic*	getObject() const { return _object; }
    inline void		setObject(IlvGraphic* object) { _object = object; }
    virtual void	apply(IlvApplyObject function, IlAny userArg);
    virtual void	applyReferences(IlvApplyObject	function,
					IlAny		userArg);

    DeclareGraphicAccessors();
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlvDisplay*	getDisplay() const;
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	setFont(IlvFont* f);
    virtual void	setColorPattern(IlvColorPattern* b);
    virtual void	setPattern(IlvPattern* p);
    virtual void	setGradientPattern(IlvGradientPattern* g);
    virtual void	setMode(IlvDrawMode m);
    virtual void	setArcMode(IlvArcMode m);
    virtual void	setFillRule(IlvFillRule m);
    virtual void	setFillStyle(IlvFillStyle f);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);
    virtual void	setOverwrite(IlBoolean overwrite);
    virtual void	setAlpha(IlvIntensity alpha);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);
    virtual
    IlvIntensity	getAlpha() const;
    IlvAntialiasingMode	getAntialiasingMode() const;
    virtual IlUShort	getLineWidth() const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&	 tregion,
				   const IlvTransformer* t = 0) const;
    virtual IlBoolean	inside(const IlvRegion&		tregion,
			       const IlvTransformer*	t = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*		  dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion*	  clip = 0) const;
    virtual void	setPalette(IlvPalette* pal);
    virtual void	invert(IlBoolean temp = IlFalse);
    virtual IlBoolean	zoomable() const;
    virtual void	boundingBox(IlvRect&			r,
				    const IlvTransformer*	t = 0) const;
    virtual
    IlvLookFeelHandler* getLookFeelHandler() const;
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	computeFocusRegion(IlvRegion&		 r,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* = 0)const;
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual IlBoolean	handleAccelerator(IlvEvent&) const;
    virtual IlBoolean	allowToolTip() const;
    virtual IlBoolean	classFocusable() const;
    virtual
    IlvGraphicHolder*	getHolder() const;
    virtual void	setHolder(IlvGraphicHolder* holder);

    virtual void	applyTransform(const IlvTransformer* t) ;
    virtual void	print(ILVSTDPREF ostream&, int level = 0) const;

    DeclareInterface(Shape);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGraphicHandle);

    static IlSymbol*	_graphicValue;
    static IlSymbol*	_ownerValue;

private:
    IlvGraphicHandle() {} //forbidden

protected:
    IlvGraphic*		_object;
    IlBoolean		_owner;
    IlvIntensity	_alpha;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTransformedGraphic : public IlvGraphicHandle
{
public:
    IlvTransformedGraphic(IlvGraphic* obj, IlBoolean owner = IlFalse)
	: IlvGraphicHandle(obj, owner),
	  _transformer(),
	  _subHolder(0)
    {}
    IlvTransformedGraphic(IlvGraphic*		obj,
			  const IlvTransformer&	t,
			  IlBoolean		owner = IlFalse)
	: IlvGraphicHandle(obj, owner),
	  _transformer(t),
	  _subHolder(0)
    {}
    ~IlvTransformedGraphic()
    {
	if (getObject() && _subHolder
	    && getObject()->getHolder()==_subHolder)
	    getObject()->setHolder(0);
	if (_subHolder)
	    delete _subHolder;
    }

    virtual IlBoolean	intersects(const IlvRegion&		tregion,
				   const IlvTransformer*	t = 0) const;
    virtual IlBoolean	inside(const IlvRegion&		tregion,
			       const IlvTransformer*	t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    virtual void	computeFocusRegion(IlvRegion&		 r,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* = 0)const;
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*		  dst,
				    const IlvTransformer* t    = 0,
				    const IlvRegion*	  clip = 0) const;
    virtual void	boundingBox(IlvRect&		  r,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    inline
    const IlvTransformer& getTransformer() const { return _transformer; }
    inline void		setTransformer(const IlvTransformer& t)
			{
			    _transformer = t;
			}
    void		setHolder(IlvGraphicHolder*);

    DeclareInterface(Shape);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvTransformedGraphic);

protected:
    IlvTransformer		_transformer;
    IlvSubGraphicHolder*	_subHolder;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFixedSizeGraphic : public IlvGraphicHandle
{
public:
    IlvFixedSizeGraphic(IlvGraphic*	obj,
			IlBoolean	owner    = IlFalse,
			IlvPosition	position = IlvBadPosition,
			const IlvPoint*	point    = 0);

    void		computeTransformer(IlvPoint		 point,
					   IlvTransformer&	 tt,
					   const IlvTransformer* t) const;
    virtual IlBoolean	zoomable() const;
    virtual void	applyTransform(const IlvTransformer* t);
    IlBoolean		contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    IlBoolean		intersects(const IlvRegion&	 tregion,
				   const IlvTransformer* t = 0) const;
    IlBoolean		inside(const IlvRegion&		tregion,
			       const IlvTransformer*	t = 0) const;
    virtual void	computeFocusRegion(IlvRegion&		 r,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* = 0)const;
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*		  dst,
				    const IlvTransformer* t    = 0,
				    const IlvRegion*	  clip = 0) const;
    virtual void	boundingBox(IlvRect&		  r,
				    const IlvTransformer* t = 0) const;
    inline IlvPosition	getPosition() const { return _position; }
    inline void		setPosition(IlvPosition position)
			{
			    _position = position;
			    computePosition(_point);
			}
    inline
    const IlvPoint&	getPoint() const { return _point; }
    inline void		setPoint(const IlvPoint& p) { _point = p; }

    DeclareInterface(Shape);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvFixedSizeGraphic);

protected:
    IlvPoint		_point;
    IlvPosition		_position;

    void		computePosition(IlvPoint& point);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicInstance : public IlvTransformedGraphic
{
public:
    IlvGraphicInstance(IlvGraphic*	obj,
		       IlvPalette*	palette,
		       IlBoolean	owner = IlFalse)
	: IlvTransformedGraphic(obj, owner),
	  _palette(palette)
    {
	_palette->lock();
    }
    IlvGraphicInstance(IlvGraphic*		obj,
		       const IlvTransformer&	t,
		       IlvPalette*		palette,
		       IlBoolean		owner = IlFalse)
	: IlvTransformedGraphic(obj, t, owner),
	  _palette(palette)
    {
	_palette->lock();
    }
    virtual ~IlvGraphicInstance();

    virtual IlvDisplay*	getDisplay() const;
    inline IlvColor*	getBackground() const
			{
			    return _palette->getBackground();
			}
    inline IlvColor*	getForeground() const
			{
			    return _palette->getForeground();
			}
    inline IlvFont*	getFont() const { return _palette->getFont(); }
    inline IlvPattern*	getPattern() const { return _palette->getPattern(); }
    inline
    IlvColorPattern*	getColorPattern() const
			{
			    return _palette->getColorPattern();
			}
    inline
    IlvGradientPattern*	getGradientPattern() const
			{
			    return _palette->getGradientPattern();
			}
    inline
    IlvLineStyle*	getLineStyle() const
			{
			    return _palette->getLineStyle();
			}
    inline IlBoolean	getOverwrite() const 
			{
			    return _palette->getOverwrite();
			}
    inline IlvDrawMode	getMode() const { return _palette->getMode(); }
    inline IlvFillStyle	getFillStyle() const
			{
			    return _palette->getFillStyle();
			}
    IlUShort		getLineWidth() const;
    inline unsigned int	getPlaneMask() const
			{
			    return _palette->getPlaneMask();
			}
    inline IlvArcMode	getArcMode() const { return _palette->getArcMode(); }
    inline IlvFillRule	getFillRule() const { return _palette->getFillRule(); }
    inline IlvPalette*	getPalette() const { return _palette; }
    IlvAntialiasingMode	getAntialiasingMode() const;
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	setFont(IlvFont* f);
    virtual void	setColorPattern(IlvColorPattern* b);
    virtual void	setPattern(IlvPattern* p);
    virtual void	setGradientPattern(IlvGradientPattern* g);
    virtual void	setMode(IlvDrawMode m);
    virtual void	setArcMode(IlvArcMode m);
    virtual void	setFillRule(IlvFillRule m);
    virtual void	setFillStyle(IlvFillStyle f);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	invert(IlBoolean temp = IlFalse);
    void		setPalette(IlvPalette* palette);
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*		  dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion*	  clip = 0) const;
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGraphicInstance);

protected:
    IlvPalette*		_palette;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTransformedGraphicHolder : public IlvSubGraphicHolder
{
public:
    IlvTransformedGraphicHolder(IlvDisplay* d, IlvTransformedGraphic* g)
	: IlvSubGraphicHolder(d, g),
	  _cachedTform(0),
	  _cachedInner(),
	  _cachedOuter()
    {}
    ~IlvTransformedGraphicHolder()
    {
	if (_cachedTform)
	    delete _cachedTform;
    }

    IlvTransformer*	getTransformer() const;
    IlvTransformer*	getLocalTransformer() const;
    IlUInt		getCardinal();
    IlvGraphic*		getChild(IlUInt);
    IlBoolean		isChild(IlvGraphic*);

protected:
    inline
    IlvTransformedGraphic* tgraphic() const
			{
			    return (IlvTransformedGraphic*) _parentG;
			}
    IlvTransformer*	_cachedTform;
    IlvTransformer	_cachedInner;
    IlvTransformer	_cachedOuter;
};

ILVVWSMODULEINIT(g0handle);
#endif /* !__Ilv_Graphics_Handle_H */
