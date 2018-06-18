// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/dragint.h
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
// Definition of the IlvViewDragDropInteractor class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv31_Dragint_H
#define __Ilv31_Dragint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewDragDropInteractor
: public IlvViewObjectInteractor {
public:
    IlvViewDragDropInteractor(IlvView* target = 0, IlvGraphic* ghost = 0)
    : _button(IlvLeftButton),
      _ghost(0),
      _userGhost(ghost),
      _target(target),
      _dx(0), _dy(0),
      _position(),
      _useGhostRectangle(IlFalse),
      _tmpGhostRectangle(IlFalse),
      _maxObjects(8),
      _smartSet(0)
    {}
    // ____________________________________________________________
    IlUShort  getButton() const           { return _button;   }
    void      setButton(IlUShort button)  { _button = button; }
    IlvView*  getTarget() const           { return _target; }
    void      setTarget(IlvView* target)  { _target = target; }
    virtual void drawGhost(IlvContainer* view, IlvGraphic* g,
			   const IlvPoint& position,
			   const IlvTransformer* t = 0);
    IlvGraphic* getGhost() const            { return _userGhost; }
    void        setGhost(IlvGraphic* ghost) { _userGhost  = ghost; }
    IlBoolean   useGhostRectangle() const { return _useGhostRectangle; }
    void        useGhostRectangle(IlBoolean v) { _useGhostRectangle = v; }
    IlUInt      getMaxObjects() const    { return _maxObjects; }
    void        setMaxObjects(IlUInt m)  { _maxObjects = m;    }

    virtual void smartSetStartDrop(IlvView* target);
    virtual void smartSetEndDrop(IlvView* target);
    virtual void doIt(IlvView* target, IlvGraphic* ghost,
                      const IlvPoint& position);
    virtual void checkPosition(IlvPoint& position);
    virtual IlBoolean inTarget(const IlvPoint&);
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t);
    virtual void dragStarted(IlUInt, const IlvGraphic* const*);
    virtual const char* className() const;
    IlvSmartSet* getSourceSmartSet() const { return _smartSet; }
protected:
    IlUShort		_button;
    IlvGraphic*		_ghost;
    IlvGraphic*		_userGhost;
    IlvView*		_target;
    IlvPos		_dx, _dy;
    IlvPoint		_position;
    IlBoolean		_useGhostRectangle;
    IlBoolean		_tmpGhostRectangle;
    IlUInt		_maxObjects;
    IlvSmartSet*	_smartSet;

};

ILV31VWSMODULEINIT(dragint);
#endif /* !__Ilv31_Dragint_H */
