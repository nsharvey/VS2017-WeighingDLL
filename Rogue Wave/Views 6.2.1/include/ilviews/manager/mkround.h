// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkround.h
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
// Declaration of the IlvMakeRoundRectangleInteractor and
// IlvMakeFilledRoundRectangleInteractor classes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkround_H
#define __Ilv_Manager_Mkround_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Graphics_Roundrec_H)
#include <ilviews/graphics/roundrec.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeRoundRectangleInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeRoundRectangleInteractor(IlvManager* manager,
				    IlvView*    view,
				    IlUShort    button = IlvLeftButton,
				    IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(manager, view, button, snap) {}
    IlvMakeRoundRectangleInteractor(IlUShort    button = IlvLeftButton,
				    IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(button, snap) {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);

    IlvMakeRoundRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeFilledRoundRectangleInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeFilledRoundRectangleInteractor(IlvManager* manager,
					  IlvView*    view,
					  IlUShort    button = IlvLeftButton,
					  IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(manager, view, button, snap) {}
    IlvMakeFilledRoundRectangleInteractor(IlUShort    button = IlvLeftButton,
					  IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(button, snap) {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);

    IlvMakeFilledRoundRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

ILVMGRMODULEINIT(m0_mkround);

#endif /* !__Ilv_Manager_Mkround_H */
