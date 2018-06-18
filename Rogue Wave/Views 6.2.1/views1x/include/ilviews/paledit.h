// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/paledit.h
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
// Declaration of the IlvPaletteSelector class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Paledit_H
#define __Ilv1X_Paledit_H

#if !defined(__Ilv_Gview_H)
#include <ilviews/gview.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

class  IlvColumnViewInteractor;

class  IlvPaletteSelector;
typedef void (*IlvDestroyPaletteSelector)(IlvPaletteSelector*,IlvAny);

class  IlvRowColumnView;
// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvPaletteSelector
{
public:
    IlvPaletteSelector(IlvDisplay*    display,
		      const IlvRect& size,
		      IlvBoolean     visible=IlvTrue);
    IlvPaletteSelector(IlvDisplay*    display,
		      IlvSystemView  xany);
    IlvPaletteSelector(IlvDisplay*    display,
		      IlvRowColumnView *);
    virtual ~IlvPaletteSelector();
    // ____________________________________________________________
    void background(IlvBoolean fillbackground)
    	{ _fillbackground = fillbackground; }
    virtual void destroy();
    virtual void callCallback(IlvPattern*)   {}
    virtual void callCallback(IlvLineStyle*) {}
    virtual void callCallback(IlvUShort)     {}
    virtual void callCallback(IlvColor*)     {}
    virtual void callCallback(IlvArcMode)    {}
    virtual void callCallback(IlvFillRule)   {}
    virtual void callCallback(IlvFillStyle)  {}
    IlvBoolean isBackground() const { return _fillbackground; }
    void show();
    void show(IlvPos x,IlvPos y);
    void hide();
    void setDestroyPaletteCallback(IlvDestroyPaletteSelector, IlvAny =0);
protected:
    IlvDisplay* _display;
    IlvColumnViewInteractor*  _interactor;
    IlvTopView*               _topview;
    IlvBoolean                _fillbackground;
    IlvDestroyPaletteSelector _destroyPaletteCallback;
    IlvAny                    _argPaletteCallback;
    void init(IlvRowColumnView*);
};

ILV1XVWSMODULEINIT(paledit);

#endif /* !__Ilv1X_Paledit_H  */
