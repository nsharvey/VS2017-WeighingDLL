// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/ddinter.h
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
// Declaration of the IlvManagerViewDragDropInteractor class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Ddinter_H
#define __Ilv_Manager_Ddinter_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

#define ILVMVDDIINIT \
_dx(0), _dy(0), _location(), _object(0), _userGhost(ghost), _ghost(0), \
_button(button), _useGhostRectangle(IlFalse), _tmpGhostRectangle(IlFalse), \
_target(target), _maxSelections(5)

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerViewDragDropInteractor
: public IlvManagerViewInteractor
{
public:
    IlvManagerViewDragDropInteractor(IlvManager* manager,
				     IlvView*    view,
				     IlvView*    target = 0,
				     IlvGraphic* ghost  = 0,
				     IlUShort    button = IlvLeftButton)
    : IlvManagerViewInteractor(manager, view), ILVMVDDIINIT {}
    IlvManagerViewDragDropInteractor(IlvView*    target = 0,
				     IlvGraphic* ghost  = 0,
				     IlUShort   button = IlvLeftButton)
    : IlvManagerViewInteractor(), ILVMVDDIINIT {}
    // ____________________________________________________________
    inline IlUShort	getButton() const { return _button; }
    inline void		setButton(IlUShort button) { _button = button; }
    inline IlvGraphic*	getGhost() const { return _userGhost; }
    void		setGhost(IlvGraphic* ghost);
    inline IlvView*	getTarget() const { return _target; }
    inline void		setTarget(IlvView* target) { _target = target; }
    inline IlUInt	getMaxSelections() const { return _maxSelections; }
    inline void		setMaxSelections(IlUInt m) { _maxSelections = m; }
    virtual void	drawGhost();
    virtual void	init();
    virtual void	abort() ;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	doIt(IlvView*        target,
			     IlvGraphic*     ghost,
			     const IlvPoint& position) const = 0;
    virtual IlBoolean	inTarget(const IlvPoint& position);
    virtual void	checkLocation(IlvPoint& position);
    virtual IlBoolean	dragStarted(IlUInt       count,
				    IlvGraphic** objects) const;

    IlvManagerViewDragDropInteractor(IlvInputFile&);
    IlvDeclareLazyClassInfo();

protected:
    IlvPos		_dx, _dy;
    IlvPoint		_location;
    IlvGraphic*		_object,
	      *		_userGhost,
	      *		_ghost;
    IlUShort		_button;
    IlBoolean		_useGhostRectangle;
    IlBoolean		_tmpGhostRectangle;
    IlvView*		_target;
    IlUInt		_maxSelections;
    static IlSymbol*	_setSymbol;
};

ILVMGRMODULEINIT(m0_ddinter);

#endif /* !__Ilv_Manager_Ddinter_H */
