// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/rotinter.h
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
// Declaration of the IlvRotateInteractor class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Rotint_H
#define __Ilv_Manager_Rotint_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvRotateInteractor
: public IlvManagerViewInteractor
{
public:
    IlvRotateInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view), _rotating(IlFalse) {}
    IlvRotateInteractor()
	: IlvManagerViewInteractor(), _rotating(IlFalse) {}
    // ____________________________________________________________
    IlBoolean	handleEvent(IlvEvent& event);
    void		init();
    void		drawGhost();
    void		abort() ;
    virtual void	doIt(IlFloat angle);

    IlvRotateInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void		handleButtonDown(IlvEvent&);
    void		handleButtonDragged(IlvEvent&);
    void		handleButtonUp(IlvEvent&);

    IlvPoint		_centerpoint;
    IlvPoint		_firstpoint;
    IlvPoint		_currentpoint;
    IlBoolean		_rotating;
};

ILVMGRMODULEINIT(m0_rotinter);

#endif /* !__Ilv_Manager_Rotint_H */
