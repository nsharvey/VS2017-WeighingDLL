// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/inter.h
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
// Declaration of the predefined object interactors.
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Inter_H
#define __Ilv_Graphics_Inter_H

#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvButtonInteractor : public IlvInteractor
{
public:
    IlvButtonInteractor(IlUShort       button = IlvLeftButton,
			IlvApplyObject action = 0,
			IlAny          arg    = 0);

    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);
    inline void		setAction(IlvApplyObject action, IlAny arg = 0)
			{
			    _action  = action;
			    _userarg = arg;
			}
    inline
    IlvApplyObject	getAction() const { return _action; }
    virtual void	doIt(IlvGraphic* obj);

    DeclareInteractorTypeInfo(IlvButtonInteractor);

protected:
    IlUShort		_button;
    IlvApplyObject	_action;
    IlAny		_userarg;
    IlBoolean		_invert;

    IlBoolean		objContains(IlvGraphic*,
				    const IlvEvent&,
				    const IlvTransformer*);
    virtual void	doInvert(IlvGraphic* obj);
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvRepeatButtonInteractor : public IlvButtonInteractor
{
public:
    IlvRepeatButtonInteractor(IlUShort       button = IlvLeftButton,
			      IlvApplyObject action = 0,
			      IlAny          arg    = 0);

    inline IlUInt	getPeriod() const { return _period; }
    inline void		setPeriod(IlUInt p) { _period = p; }

    DeclareInteractorTypeInfo(IlvRepeatButtonInteractor);

protected:
    void		startTimer(IlvGraphic* obj);
    void		stopTimer(IlvGraphic* obj);
    virtual void	doInvert(IlvGraphic* obj);

    IlUInt		_period;
    IlvTimer*		_timer;
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvToggleInteractor : public IlvButtonInteractor
{
public:
    IlvToggleInteractor(IlUShort       button  = IlvLeftButton,
			IlvApplyObject action  = 0,
			IlAny          userarg = 0);

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);

    DeclareInteractorTypeInfoRO(IlvToggleInteractor);
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMoveInteractor : public IlvInteractor
{
public:
    IlvMoveInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);
    virtual void	endOperation();
    virtual void	doIt(IlvGraphic*           object,
			     const IlvPoint&       deltaMove,
			     const IlvTransformer* t = 0);
    virtual void	validate(IlvGraphic*           object,
				 IlvPoint&             p,
				 const IlvTransformer* t = 0);

    virtual void	drawGhost(IlvView*              view,
				  IlvGraphic*           ghost,
				  const IlvPoint&	deltaMove,
				  const IlvTransformer* t);

    DeclareInteractorTypeInfoRO(IlvMoveInteractor);

protected:
    IlvGraphic*		_ghost;
    IlvRect		_initBBox;
    IlvPoint		_deltaEvent;
    IlvPoint		_deltaMove;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReshapeInteractor : public IlvInteractor
{
public:
    IlvReshapeInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);
    virtual void	doIt(IlvGraphic*           object,
			     IlvRect&              rect,
			     const IlvTransformer* t = 0);
    virtual void	validate(IlvGraphic*           obj,
				 IlvRect&              rect,
				 const IlvTransformer* t = 0);

    virtual void	drawGhost(IlvRect& rect, IlvView* view);

    DeclareInteractorTypeInfoRO(IlvReshapeInteractor);

protected:
    IlvRect		_rect;
    IlvRect		_trect;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMoveReshapeInteractor : public IlvInteractor
{
public:
    IlvMoveReshapeInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);
    virtual void	getCallbackTypes(IlUInt&		 count,
					 const char* const**     names,
					 const IlSymbol* const** types) const;
protected:
    IlvMoveInteractor		_move;
    IlvReshapeInteractor	_reshape;

    DeclareInteractorTypeInfoRO(IlvMoveReshapeInteractor);
};


// --------------------------------------------------------------------------
class IlvSmartSet;
class ILVVWSEXPORTED IlvDragDropInteractor : public IlvInteractor
{
public:
    IlvDragDropInteractor(IlvView* target = 0, IlvGraphic* ghost = 0);

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&             event,
				    const IlvTransformer* t);

    virtual void	doIt(IlvView*        target,
			     IlvGraphic*     ghost,
			     const IlvPoint& position);
    virtual void	checkPosition(IlvPoint& position);
    virtual IlBoolean	inTarget(const IlvPoint& point);
    inline void		setTarget(IlvView* target) { _target = target; }
    inline IlvView*	getTarget() const { return _target; }
    virtual void	drawGhost(IlvView*              view,
				  IlvGraphic*           ghost,
				  const IlvPoint&       position,
				  const IlvTransformer* t = 0);
    inline void		setGhost(IlvGraphic* ghost) { _userGhost = ghost; }
    inline IlBoolean	useGhostRectangle() const 
			{
			    return _useGhostRectangle;
			}
    inline void		useGhostRectangle(IlBoolean val) 
			{
			    _useGhostRectangle = val;
			}

    inline IlUShort	getButton() const { return _button; }
    inline void		setButton(IlUShort button) { _button = button; }

    virtual void	smartSetStartDrop(IlvView* target);
    virtual void	smartSetEndDrop(IlvView* target);

    virtual void	endOperation();

    DeclareInteractorTypeInfo(IlvDragDropInteractor);

protected:
    IlvView*		_target;
    IlvGraphic*		_ghost;
    IlvGraphic*		_userGhost;
    IlvPoint		_position;
    IlBoolean		_useGhostRectangle;
    IlvPoint		_deltaEvent;
    IlUShort		_button;
    IlvSmartSet*	_smartSet;
};

ILVVWSMODULEINIT(grinter);

#endif /* __Ilv_Graphics_Inter_H */
