// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/icon.h
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
// Declaration of the IlvIcon and IlvTransparent icon class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Icon_H
#define __Ilv_Graphics_Icon_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Util_Animator_H)
#include <ilviews/util/animator.h>
#endif

class IlvIcon;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvIconAnimator : public IlvBitmapAnimator
{
public:
    IlvIconAnimator(IlvAnimationMode	mode   = IlvAnimationForward,
		    IlUInt		period = IlvDefaultAnimationPeriod);

    virtual IlvDisplay*	getDisplay() const;
    virtual IlvBitmap*	getBitmap() const;
    virtual void	initReDraws() const;
    virtual void	invalidateRegion()  const;
    virtual void	reDrawViews() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    inline IlvIcon*	getIcon() const { return _icon; }

    static
    IlvIconAnimator*	GetAnimator(const IlvIcon*);
    static void		SetAnimator(IlvIcon*, IlvIconAnimator*);

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvIconAnimator);

protected:
    IlvIcon*		_icon;
    inline void		setIcon(IlvIcon* icon) { _icon = icon; }
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvIcon : public IlvSimpleGraphic
{
public:
    IlvIcon(IlvDisplay*		display,
	    const IlvPoint&	position,
	    IlvBitmap*		bitmap,
	    IlvPalette*		palette = 0)
	: IlvSimpleGraphic(display, palette),
	  _position(position),
	  _bitmap(0)
    {
	setBitmap(bitmap);
    }
    virtual ~IlvIcon();

    inline IlvBitmap*	getBitmap() const { return _bitmap; }
    virtual IlUInt	getCurrentFrame() const;
    virtual void	setBitmap(IlvBitmap* bitmap);
    virtual IlBoolean	zoomable() const;
    inline IlvDim	width() const { return _bitmap->width();  }
    inline IlvDim	height() const { return _bitmap->height(); }
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t,
			     const IlvRegion*		rect = 0) const;
    virtual void	boundingBox(IlvRect&			rect,
				    const IlvTransformer*	t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t) ;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&		trect,
				   const IlvTransformer*	t = 0) const;
    virtual IlBoolean	inside(const IlvRegion&		trect,
			       const IlvTransformer*	t = 0) const;

    DeclareGraphicAccessors();
    static IlSymbol*	_bitmapValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvIcon);

protected:
    IlvPoint		_position;
    IlvBitmap*		_bitmap;
    void		computeCenter(IlvPoint& p, IlvDim, IlvDim) const;
    virtual void	drawBitmap(IlvPort*,
				   IlvPalette*,
				   const IlvRect&,
				   const IlvRegion* clip = 0) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTransparentIcon : public IlvIcon
{
public:
    IlvTransparentIcon(IlvDisplay*	display,
		       const IlvPoint&	position,
		       IlvBitmap*	bitmap,
		       IlvPalette*	palette = 0);
    IlvTransparentIcon(IlvDisplay*	display,
		       const IlvPoint&	position,
		       IlvBitmap*	bitmap,
		       IlvBitmap*	mask,
		       IlvPalette*	palette = 0);

    inline IlvBitmap*	getMask() const { return getBitmap()->getMask(); }
    void		setMask(IlvBitmap* bitmap);
    virtual void	setBitmap(IlvBitmap* bitmap);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvTransparentIcon);

protected:
    virtual void	drawBitmap(IlvPort*,
				   IlvPalette*,
				   const IlvRect&,
				   const IlvRegion* clip = 0) const;
};

ILVVWSMODULEINIT(g0icon);
#endif /* !__Ilv_Graphics_Icon_H */
