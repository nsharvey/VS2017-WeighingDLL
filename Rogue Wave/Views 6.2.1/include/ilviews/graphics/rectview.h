// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/rectview.h
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
// Declaration of the IlvViewRectangle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Rectview_H
#define __Ilv_Graphics_Rectview_H

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvViewRectangle : public IlvFilledRectangle
{
public:
    IlvViewRectangle(IlvDisplay*	display,
		     const IlvRect&	rect,
		     IlvPalette*	palette = 0);
    ~IlvViewRectangle();

    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	makeView(IlvPort*		dst,
				 const IlvTransformer*	t = 0);
    virtual IlvView*	createView(IlvAbstractView*	parent,
				   const IlvRect&	size);
    virtual void	drawContents(IlvPort*		dst,
				     const IlvRect&	size,
				     const IlvRegion*	clip) const;
    virtual IlvView*	getView() const;
    virtual void	setView(IlvView* view);
    void		show();
    void		hide();
    virtual void	setHolder(IlvGadgetHolder* holder);
    inline IlBoolean	isDrawingContents() const
			{
			    return (_DrawContents && _drawContents)
				? IlTrue
				: IlFalse;
			}
    inline void		mustDrawContents(IlBoolean d) { _drawContents = d; }
    inline IlBoolean	isVisible() const { return _isVisible; }
    virtual void	setVisible(IlBoolean value);
    virtual void	setBackground(IlvColor*);
    virtual void	setPalette(IlvPalette*);
    virtual void	viewDeleted();
    void		updateViewGeometry();
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvViewRectangle);

    inline static IlBoolean	IsDrawingContents() { return _DrawContents; }
    inline static void	MustDrawContents(IlBoolean d) { _DrawContents = d; }

    static IlBoolean	_DrawContents;

protected:
    IlvView*		_view;
    IlBoolean		_isVisible;
    IlBoolean		_drawContents;

public:
    DeclareGraphicAccessors();
    static IlSymbol*	_viewValue;
};

ILVVWSMODULEINIT(g0rectview);
#endif /* __Ilv_Graphics_Rectview_H */
