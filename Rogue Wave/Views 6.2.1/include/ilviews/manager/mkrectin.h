// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkrectin.h
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
// Declaration of the IlvMakeRectangleInteractor class and its subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkrectin_H
#define __Ilv_Manager_Mkrectin_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeRectangleInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeRectangleInteractor(IlvManager* manager, IlvView* view)
	: IlvDragRectangleInteractor(manager, view) {}
    IlvMakeRectangleInteractor()
	: IlvDragRectangleInteractor() {}
    // ____________________________________________________________
    virtual void	doIt(IlvRect& rect);
    void		addRectangle(IlvGraphic* graphic);

    IlvMakeRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeFilledRectangleInteractor
: public IlvMakeRectangleInteractor
{
public:
    IlvMakeFilledRectangleInteractor(IlvManager* manager, IlvView* view)
	: IlvMakeRectangleInteractor(manager, view) {}
    IlvMakeFilledRectangleInteractor()
	: IlvMakeRectangleInteractor() {}
    // ____________________________________________________________
    void		drawGhost();
    virtual void	doIt(IlvRect& rect);

    IlvMakeFilledRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeObjectInteractor
: public IlvMakeRectangleInteractor
{
public:
    IlvMakeObjectInteractor(IlvManager* manager,
			    IlvView*    view,
			    IlvGraphic* model = 0)
	: IlvMakeRectangleInteractor(manager, view)
	{ _object = model ? model->copy() : 0; }
    IlvMakeObjectInteractor(IlvGraphic* model = 0)
	: IlvMakeRectangleInteractor()
	{ _object = model ? model->copy() : 0; }
    ~IlvMakeObjectInteractor();
    // ____________________________________________________________
    virtual void	doIt(IlvRect& rect);
    inline IlvGraphic*	getObject() { return _object; }
    inline void		setObject(IlvGraphic* model)
			{
			    delete _object;
			    _object = model ? model->copy() : 0;
			}

    IlvMakeObjectInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvGraphic*		_object;
};

ILVMGRMODULEINIT(m0_mkrectin);

#endif /* !__Ilv_Manager_Mkrectin_H */
