// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/objinter.h
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
// Declaration of the IlvManagerObjectInteractor class and predefined subtypes
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Objinter_H
#define __Ilv31_Objinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Manager_Objinter_H)
#include <ilviews/manager/objinter.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerButtonInteractor
: public IlvManagerObjectInteractor {
public:
    IlvManagerButtonInteractor(IlvApplyObject action  = 0,
			       IlAny          arg     = 0)
    : _action(action),
      _userarg(arg)
    {}
    // ____________________________________________________________
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    void                setAction(IlvApplyObject action, IlAny arg = 0)
    {
	_action  = action;
	_userarg = arg;
    }
    IlvApplyObject      getAction() const { return _action; }
    virtual void        doIt(IlvGraphic* obj);
    virtual const char* className() const;

protected:
    IlvApplyObject	_action;
    IlAny		_userarg;
    IlBoolean objContains(IlvGraphic*, IlvEvent&,
			  const IlvTransformer*);
};


// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerRepeatButtonInteractor
: public IlvManagerButtonInteractor {
public:
    IlvManagerRepeatButtonInteractor()
    : IlvManagerButtonInteractor(),
      _period(200),
      _invert(IlFalse),
      _button(0),
      _timer(0)
    {}
    // ____________________________________________________________
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual const char* className() const;
    IlUInt             getPeriod() const    { return _period; }
    void                setPeriod(IlUInt p) { _period = p;    }

protected:
    void                startTimer(IlvManager* mgr, IlvGraphic* obj);
    void                stopTimer(IlvManager* mgr, IlvGraphic* obj);

    IlUInt	        _period;
    IlBoolean	        _invert;
    IlUShort	        _button;
    IlvTimer*	        _timer;
};


// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerToggleInteractor
: public IlvManagerButtonInteractor {
public:
    IlvManagerToggleInteractor(IlvApplyObject action  = 0,
			       IlAny          userarg = 0)
    : IlvManagerButtonInteractor(action,userarg)
    {}
    // ____________________________________________________________
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerMoveInteractor
: public IlvManagerObjectInteractor
{
public:
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual void        doIt(IlvManager*     manager,
			     IlvGraphic*     object,
			     IlvPoint&       position,
			     IlvTransformer* t = 0);
    virtual void        validate(IlvManager*     manager,
				 IlvGraphic*     object,
				 IlvPoint&       position,
				 IlvTransformer* t = 0);
    virtual const char* className() const;
    virtual void        drawGhost(IlvView*              view,
				  IlvGraphic*           ghost,
				  IlvPos                dx,
				  IlvPos                dy,
				  const IlvTransformer* t);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerReshapeInteractor
: public IlvManagerObjectInteractor
{
public:
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual void        doIt(IlvManager*     manager,
			     IlvGraphic*     object,
			     IlvRect&        rect,
			     IlvTransformer* t = 0);
    virtual void        validate(IlvManager*     manager,
				 IlvGraphic*     obj,
				 IlvRect&        rect,
				 IlvTransformer* t = 0);
    virtual const char* className() const;
    virtual void        drawGhost(IlvRect& rect, IlvView* view);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerMoveReshapeInteractor
: public IlvManagerObjectInteractor
{
public:
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual const char* className() const;

protected:
    IlvManagerMoveInteractor	_move;
    IlvManagerReshapeInteractor	_reshape;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerDragDropInteractor
: public IlvManagerObjectInteractor
{
public:
    IlvManagerDragDropInteractor(IlvView* target = 0, IlvGraphic* ghost = 0)
    : _target(target),
      _ghost(ghost),
      _position(),
      _useGhostRectangle(IlFalse) {}
    // ____________________________________________________________
    virtual IlBoolean  handleEvent(IlvManager*     manager,
				   IlvGraphic*     obj,
				   IlvEvent&       event,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual const char* className() const;
    virtual void        doIt(IlvView*        target,
			     IlvGraphic*     ghost,
			     const IlvPoint& position);
    virtual void        checkPosition(IlvPoint& position);
    virtual IlBoolean   inTarget(const IlvPoint& point);
    void                setTarget(IlvView* target)  { _target = target; }
    IlvView*            getTarget() const           { return _target;   }
    virtual void        drawGhost(IlvView*              view,
				  IlvGraphic*           ghost,
				  const IlvPoint&       position,
				  const IlvTransformer* t = 0);
    void                setGhost(IlvGraphic* ghost) { _ghost = ghost;  }
    IlBoolean          useGhostRectangle() const {
	return _useGhostRectangle;
    }
    void                useGhostRectangle(IlBoolean val) {
	                  _useGhostRectangle = val;
                        }

protected:
    IlvView*	        _target;
    IlvGraphic*	        _ghost;
    IlvPoint	        _position;
    IlBoolean	        _useGhostRectangle;
};

ILV31VWSMODULEINIT(objinter);
#endif /* !__Ilv31_Objinter_H */
