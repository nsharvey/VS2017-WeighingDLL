// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/cellpal.h
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
// Declaration of the IlvCellPalette class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Cellpal_H
#define __Ilv1X_Cellpal_H

#if !defined(__Ilv_Cellmgr_H)
#include <ilviews/cellmgr.h>
#endif
#if !defined(__Ilv_Contint_H)
#include <ilviews/contint.h>
#endif
#if !defined(__Ilv_Gview_H)
#include <ilviews/gview.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

class IlvCellColumnViewInteractor;

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvCellPalette
{
public:
    IlvCellPalette(IlvCellManager* manager,
		   const IlvRect&  size,
		   IlvBoolean      visible=IlvTrue);
    ~IlvCellPalette();
    // ____________________________________________________________
    void background(IlvBoolean fillbackground)
	{ _fillbackground = fillbackground; }
    IlvBoolean isBackground() const { return _fillbackground; }
    void show();
    void show(IlvPos x,IlvPos y);
    void hide();
    void destroy();

    void callCallback(IlvPattern*);
    void callCallback(IlvColor*);
    void callCallback(IlvFillStyle);
    void callCallback(IlvFont*);
protected:
    IlvCellColumnViewInteractor* _interactor;
    IlvTopView*                  _topview;
    IlvBoolean                   _fillbackground;
    IlvCellManager*              _manager;
};

ILV1XVWSMODULEINIT(cellpal);

#endif /* !__Ilv1X_Cellpal_H */
