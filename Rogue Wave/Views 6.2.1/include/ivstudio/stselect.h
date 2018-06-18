// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stselect.h
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
// Declaration of IlvStSelectInteractor class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Stselect_H
#define __IlvSt_Stselect_H

#if      !defined(__Ilv_Manager_Selinter_H)
#include <ilviews/manager/selinter.h>
#endif
#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if	 !defined(__Ilv_Manager_Selhook_H)
#include <ilviews/manager/selhook.h>
#endif

class IlvStudio;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSelectionHook
  : public IlvManagerSelectionHook {
public:
  IlvStSelectionHook(IlvStudio* editor);
  IlvStudio* getEditor() const { return _editor; }
  void bufferSelected();
  IlvGraphic* getLastObject() const { return _lastObject; }

  virtual void selectionChangedStart();
  virtual void selectionChangedEnd();
  virtual void selectionChanged(IlvGraphic*, IlBoolean selected);
protected:
  IlvStudio*  _editor;
  IlvGraphic* _lastObject;
  IlvGraphic* _firstObject;
}; // class IlvStSelectionHook

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSelectInteractor
: public IlvSelectInteractor {
public:
    IlvStSelectInteractor(IlvStudio* ed, IlvManager* mgr, IlvView* view)
	: IlvSelectInteractor(mgr, view), _editor(ed) {}
    IlvStSelectInteractor(IlvStudio* ed)
	: IlvSelectInteractor(),_editor(ed) {}
    // ____________________________________________________________
    IlBoolean handleEvent(IlvEvent& event);
    virtual void objectReshaped(IlvGraphic*);
protected:
    virtual void doButtonDown(IlvEvent&);
    virtual void doButtonUp(IlvEvent&);
    virtual void doKeyDown(IlvEvent&);
    virtual void doDoubleClick(IlvEvent&);
    IlvStudio* _editor;
}; // class IlvStSelectInteractor

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStInteractorSet
: public IlvStSelectInteractor {
public:
    IlvStInteractorSet(IlvStudio* editor);
    virtual ~IlvStInteractorSet();
    virtual IlBoolean    handleEvent(IlvEvent& event);
    virtual void    addedToSelection(IlvGraphic* obj);
    virtual void    init();
    void	    registerInteractor(const char*, IlvManagerViewInteractor*);
    IlvManagerViewInteractor* getInteractor(const IlvGraphic*) const;
    void	    setInteractor(IlvManagerViewInteractor* inter);
protected:
    void	    selectInteractor(IlvManagerViewInteractor* inter);
    void	    unSelectInteractor(IlvManagerViewInteractor* inter);
    IlvManagerViewInteractor*	_curInter;
    IlvAList			_interactors;
}; // class IlvStInteractorSet




// --------------------------------------------------------------------------
//  class IlvStSubInteractor
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSubInteractor
: public IlvManagerViewInteractor
{
public:
    IlvStSubInteractor(IlvManager* mgr, IlvView* view)
	: IlvManagerViewInteractor(mgr, view)
    {}
    IlvStSubInteractor() : IlvManagerViewInteractor() {}
    // ____________________________________________________________
    virtual void handleExpose(IlvRegion* clip=0);
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void abort();
    virtual void init();

    virtual void handleButtonDown(IlvEvent& event) = 0;
    virtual void handleButtonUp(IlvEvent& event) = 0;
    virtual void handleButtonDrag(IlvEvent& event) = 0;

    virtual IlvGraphic* selectObject(const IlvPoint&, const IlvClassInfo* ) const;

    static void SetKnobSize(IlUShort size);
    static IlUShort GetKnobSize();
    static void GetKnob(IlvRect&);

    void abort(IlvEvent& event) { abort(); callPrevious(&(event)); }
protected:
    IlvGraphic* _object;
    IlvGraphic* _ghost;

    IlvPoint _firstPosition;
    IlvPoint _lastPosition;

    IlBoolean _dragging;   // for drawGhost
    IlvRegion* _exposeClip;

    virtual void resetGhost();


    static IlUShort _knobSize;
    static IlFloat ComputeAngle(const IlvPoint& center, const IlvPoint& p);
    static IlBoolean IsPointOnSegment(IlvPoint a,
				       IlvPoint b,
				       const IlvPoint& p,
				       IlUInt knobsize = (IlUInt)-1);
};

#endif /* __IlvSt_Stselect_H */
