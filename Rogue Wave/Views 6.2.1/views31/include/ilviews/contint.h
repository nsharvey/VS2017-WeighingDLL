// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/contint.h
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
// Declaration of predefined IlvViewObjectInteractor classes
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Contint_H
#define __Ilv31_Contint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif

// --------------------------------------------------------------------------
typedef void (* IlvButtonAction)(IlvGraphic*, IlvContainer*, IlAny);
class ILV31VWSEXPORTED IlvViewButtonInteractor
: public IlvViewObjectInteractor {
public:
    IlvViewButtonInteractor(IlvButtonAction action  = 0,
			    IlAny	    userarg = 0)
    : _action(action),
      _userarg(userarg)
    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic*, IlvEvent&, IlvContainer*,
				   IlvTransformer*);
    virtual void doIt(IlvGraphic* obj, IlvContainer* view);
    void setAction(IlvButtonAction action, IlAny userarg = 0)
	{
	    _action  = action;
	    _userarg = userarg;
	}
    IlvButtonAction getAction() const { return _action; }
    virtual const char* className() const;
protected:
    IlvButtonAction	_action;
    IlAny		_userarg;
    IlBoolean objContains(IlvGraphic*           object,
			  IlvEvent&             event,
			  const IlvTransformer* t);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewRepeatButtonInteractor
: public IlvViewButtonInteractor {
public:
    IlvViewRepeatButtonInteractor()
    : IlvViewButtonInteractor(),
      _period(200),
      _invert(IlFalse),
      _button(0),
      _timer(0)
    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic*, IlvEvent&, IlvContainer*,
				  IlvTransformer*);
    virtual const char* className() const;
    IlUInt getPeriod() const    { return _period; }
    void    setPeriod(IlUInt p) { _period = p;    }
protected:
    void startTimer(IlvContainer* cont, IlvGraphic* obj);
    void stopTimer(IlvContainer* cont, IlvGraphic* obj);

    IlUInt	_period;
    IlBoolean	_invert;
    IlUShort	_button;
    IlvTimer*	_timer;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewToggleInteractor
: public IlvViewButtonInteractor {
public:
    IlvViewToggleInteractor(IlvButtonAction action  = 0,
			    IlAny          userarg = 0)
    : IlvViewButtonInteractor(action,userarg)
    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				   IlvContainer* view,
				   IlvTransformer* t);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewMoveInteractor
: public IlvViewObjectInteractor {
public:
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t);
    virtual void doIt(IlvContainer*, IlvGraphic*,
		      IlvPoint&, IlvTransformer* t = 0);
    virtual void validate(IlvContainer*, IlvGraphic*,
			  IlvPoint&, IlvTransformer* t =0);
    virtual const char* className() const;
protected:
    virtual void drawGhost(IlvView* view, IlvGraphic* ghost,
			   IlvPos dx, IlvPos dy,
			   const IlvTransformer* t);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewReshapeInteractor
: public IlvViewObjectInteractor {
public:
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t);
    virtual void doIt(IlvContainer* view, IlvGraphic* ghost,
		      IlvRect& rect);
    virtual void validate(IlvContainer*,IlvGraphic*,IlvRect&);
    virtual const char* className() const;
protected:
    virtual void drawGhost(IlvRect& rect, IlvContainer* view);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewMoveReshapeInteractor
: public IlvViewObjectInteractor {
public:
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t);
    virtual const char* className() const;
protected:
    IlvViewMoveInteractor    _move;
    IlvViewReshapeInteractor _reshape;
};

ILV31VWSMODULEINIT(contint);
#endif /* !__Ilv31_Contint_H */
