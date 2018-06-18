// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/linkhand.h
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
// Definition of the IlvGenericLink
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Linkhand_H
#define __Ilv_Grapher_Linkhand_H

#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvLinkHandle : public IlvLinkImage
{
public:
    IlvLinkHandle(IlvDisplay* display,
		  IlvGraphic* object,
		  IlvGraphic* from,
		  IlvGraphic* to,
		  IlvDim      width = 0,
		  IlBoolean   owner = IlTrue,
		  IlvPalette* palette = 0);
    virtual ~IlvLinkHandle();

    IlBoolean		isOwner() const { return _owner; }
    void		setOwner(IlBoolean owner) { _owner = owner; }

    IlvGraphic*		getObject() const { return _object; }

    void		setObject(IlvGraphic* object) { _object = object; }
    IlvDim		getWidth() const { return _width; }
    void		setWidth(IlvDim width) { _width = width; }
    IlBoolean		isUsingLinkPalette() const { return _useLinkPalette; }

    void		useLinkPalette(IlBoolean use)
			{
			    _useLinkPalette = use;
			}

    // Obsolete, use isUsingLinkPalette instead.
    IlBoolean		isDrawPaletteUsed() const
			{
			    return isUsingLinkPalette();
			}
    // Obsolete, use useLinkPalette instead.
    void		useDrawPalette(IlBoolean b) { useLinkPalette(b); }

    virtual IlBoolean	zoomable() const;
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	apply(IlvApplyObject f, IlAny a);
    virtual void	applyReferences(IlvApplyObject f, IlAny a);
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	drawPalette(const IlvPalette* palette,
				    IlvPort* dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion* clip = 0) const;

    // Propagate to referenced graphic if owner
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	setFont(IlvFont* f);
    virtual void	setColorPattern(IlvColorPattern* b);
    virtual void	setGradientPattern(IlvGradientPattern* g);
    virtual void	setPattern(IlvPattern* p);    
    virtual void	setArcMode(IlvArcMode m);
    virtual void	setFillRule(IlvFillRule m);
    virtual void	setFillStyle(IlvFillStyle f);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);    
    virtual void	setPalette(IlvPalette* pal);
    virtual void	setOverwrite(IlBoolean overwrite);
    virtual void	setMode(IlvDrawMode m);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvLinkHandle);

protected:
    virtual IlBoolean	isDirect(const IlvTransformer* t = 0) const;

    IlBoolean		_owner;
    IlvGraphic*		_object;
    IlvDim		_width;
    IlBoolean		_flatObject;
    IlvTransformer	_transformer;
    IlBoolean		_useLinkPalette;
};

ILVGRAPHMODULEINIT(linkhand);
#endif /* !__Ilv_Grapher_Linkhand_H */
