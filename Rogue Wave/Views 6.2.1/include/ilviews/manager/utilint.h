// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/utilint.h
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
// Declaration of predefined useful interactor classes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Utilint_H
#define __Ilv_Manager_Utilint_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeBitmapInteractor
    : public IlvDragRectangleInteractor
{
public:
    IlvMakeBitmapInteractor(IlvManager* manager,
			    IlvView*    view,
			    IlBoolean   zoomable = IlFalse)
	: IlvDragRectangleInteractor(manager, view),
	  _zoomable(zoomable)
    {}
    IlvMakeBitmapInteractor(IlBoolean zoomable = IlFalse)
	: IlvDragRectangleInteractor(), _zoomable(zoomable)
    {}

    virtual void	doIt(IlvRect& rect);

    IlvMakeBitmapInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlBoolean		_zoomable;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvHandleMoveInteractor
    : public IlvManagerViewInteractor
{
public:
    IlvHandleMoveInteractor(IlvManager* manager,
			    IlvView*    view)
	: IlvManagerViewInteractor(manager, view),
	  _previous(0)
    {}
    IlvHandleMoveInteractor() : IlvManagerViewInteractor(), _previous(0) {}

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	leaveGraphic(IlvGraphic*);
    virtual void	enterGraphic(IlvGraphic*, const IlvPoint&);

    IlvHandleMoveInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvGraphic*		_previous;
};


ILVMGRMODULEINIT(m0_utilint);

#endif /* !__Ilv_Manager_Utilint_H */
