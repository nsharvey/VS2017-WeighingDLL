// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/label.h
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
// Declaration of the IlvLabel and IlvFilledLabel classed
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Label_H
#define __Ilv_Graphics_Label_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvLabel : public IlvSimpleGraphic
{
public:
    IlvLabel(IlvDisplay*	display,
	     const IlvPoint&	point,
	     const char*	label,
	     IlvPalette*	palette = 0);
    IlvLabel(IlvDisplay*	display,
	     IlvPos		x,
	     IlvPos		y,
	     const char*	label,
	     IlvPalette*	palette = 0);
    virtual ~IlvLabel();

    inline const char*	getLabel() const { return _label; }
    virtual void	setLabel(const char* label);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	boundingBox(IlvRect&, const IlvTransformer* = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&,
				   const IlvTransformer* = 0) const;
    virtual IlBoolean	inside(const IlvRegion&,
			       const IlvTransformer* = 0) const;
    virtual IlBoolean	zoomable() const;
    virtual void	print(ILVSTDPREF ostream&, int = 0) const;
    virtual void	setCenter(const IlvPoint& p);
    virtual void	setFont(IlvFont*);
    virtual void	setPalette(IlvPalette*);

    DeclareGraphicAccessors();

    static IlSymbol*	_labelValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvLabel);

protected:
    void		computeSize(int = -1);

    IlvPoint		_center;
    IlvDim		_w;
    IlvDim		_h;
    char*		_label;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledLabel : public IlvLabel
{
public:
    IlvFilledLabel(IlvDisplay*		display,
		   const IlvPoint&	point,
		   const char*		label,
		   IlvPalette*		palette = 0)
	: IlvLabel(display, point, label, palette)
    {}

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFilledLabel);
};

ILVVWSMODULEINIT(g0label);
#endif /* !__Ilv_Graphics_Label_H */
