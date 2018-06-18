// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/gview.h
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
// Declaration of the IlvGridView class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Gview_H
#define __Ilv1X_Gview_H

#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Grid_H)
#include <ilviews/grid.h>
#endif
#if !defined(__Ilv_Gridint_H)
#include <ilviews/gridint.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvGridView
: public IlvContainer {
public:
    IlvGridView(IlvCompositeAbstractView* parent,
		const IlvRect&            dims,
		unsigned short           nbcol,
		unsigned short           nbrow,
		IlvPalette*               palette = 0,
		IlvGridSelectionType      seltype = IlvGridMultipleSelection,
		IlvBoolean                visible = IlvTrue)
    : IlvContainer(parent, dims, IlvFalse,visible) {
	IlvRect rect;
	sizeVisible(rect); // because of Windows
	_grid = new IlvGridObj(getDisplay(),
			       rect, nbcol, nbrow, seltype, palette);
	addObject(_grid,IlvFalse);
	IlvRect bbox;
	_grid->boundingBox(bbox,_transformer);
	IlvFloat sx=(IlvFloat)rect.w()/(IlvFloat)bbox.w();
	IlvFloat sy=(IlvFloat)rect.h()/(IlvFloat)bbox.h();
	IlvTransformer t(sx, (IlvFloat)0, (IlvFloat)0, sy,
			 (IlvFloat)0, (IlvFloat)0);
	addTransformer(t);
	initCutAndPaste();
    }
    IlvGridView(IlvDisplay*          display,
		IlvSystemView        parent,
		const IlvRect&       dims,
		unsigned short      nbcol,
		unsigned short      nbrow,
		IlvPalette*          palette = 0,
		IlvGridSelectionType seltype = IlvGridMultipleSelection,
		IlvBoolean           visible = IlvTrue)
    : IlvContainer(display, parent, dims, IlvFalse,visible) {
	IlvRect rect;
	sizeVisible(rect); // because of Windows
	_grid = new IlvGridObj(display,
			       rect, nbcol, nbrow, seltype, palette);
	addObject(_grid,IlvFalse);
	IlvRect bbox;
	_grid->boundingBox(bbox,_transformer);
	IlvFloat sx = (IlvFloat)rect.w()/(IlvFloat)bbox.w();
	IlvFloat sy = (IlvFloat)rect.h()/(IlvFloat)bbox.h();
	IlvTransformer t(sx, (IlvFloat)0, (IlvFloat)0, sy,
			 (IlvFloat)0, (IlvFloat)0);
	addTransformer(t);
	initCutAndPaste();
    }
    IlvGridView(IlvDisplay*          display,
		IlvSystemView        available,
		unsigned short      nbcol,
		unsigned short      nbrow,
		IlvPalette*          palette = 0,
		IlvGridSelectionType seltype = IlvGridMultipleSelection)
    : IlvContainer(display, available,IlvFalse) {
	IlvDim w, h;
	size(w, h);
	IlvRect dims(0, 0, w, h);
	_grid = new IlvGridObj(display,
			       dims, nbcol, nbrow, seltype, palette);
	addObject(_grid,IlvFalse);
	initCutAndPaste();
    }
    // ____________________________________________________________
    static IlvViewGridInteractor* _gridInteractor;
    IlvGridObj* grid() const { return _grid; }
    virtual void handleResize(IlvRect& rect);
    virtual void handleInput(IlvEvent&);
    // Overload operator -> for operations on GridObj
    IlvGridObj* operator->() const { return _grid; }
protected:
    IlvGridObj* _grid;
    void initCutAndPaste();
};

ILV1XVWSMODULEINIT(gview);

#endif /* !__Ilv1X_Gview_H */
