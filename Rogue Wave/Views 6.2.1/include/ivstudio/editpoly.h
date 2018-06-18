// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/editpoly.h
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
// Declaration of the IlvStEditPolyPointsInteractor,
//  IlvStEditSplineInteractor classes
// --------------------------------------------------------------------------

#ifndef __IlvSt_Editpoly_H
#define __IlvSt_Editpoly_H

#include <ivstudio/util.h>
#include <ivstudio/stselect.h>
#include <ilviews/graphics/spline.h>
#include <ilviews/base/command.h>

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEditPolyPointsInteractor : public IlvStSubInteractor
{
public:
    IlvStEditPolyPointsInteractor()
	: IlvStSubInteractor(),
	  _command(0),
	  _cmdObserver(0)
    {
	_selected = new IlArray;
    }
    ~IlvStEditPolyPointsInteractor()
    {	delete _selected;
	if (_cmdObserver)
	    delete _cmdObserver;
	if (_command)
	    delete _command;
    }
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void drawGhost();
    void reinitGhost() { IlvStSubInteractor::resetGhost(); }
    virtual void init();
    virtual void abort();

    virtual void doRotate(IlFloat angle);
    virtual void doMovePoints(const IlvPoint& value);
    virtual void doMoveSegment(const IlvPoint& value);
    virtual void doRemovePoint(IlUInt idx);
    virtual void doInsertPoint(const IlvPoint& p, IlUInt idx, IlDouble param=.5);

    IlvCommand* getCommand() { return _command; }
    void setCommand(IlvChangeValueCommand* c) { _command=c;}
protected:
    // status:
    IlBoolean	_draggingPoints;
    IlBoolean	_draggingSegment;
    IlBoolean	_rotating;

    IlArray*	_selected;
    IlInt	_currentSegment;	// index of first point
    IlInt	_currentPoint;
    IlvPoint	_center;
    IlvChangeValueCommand* _command;
    IlvObserver* _cmdObserver;

    virtual void handleDelKeyDown(IlvEvent& event);
    virtual void handleInsKeyDown(IlvEvent& event);
    virtual void handleButtonDown(IlvEvent& event);
    virtual void handleButtonUp(IlvEvent& event);
    virtual void handleButtonDrag(IlvEvent& event);
    static IlInt GetSegmentIndex(const IlvPolyPoints* polypoints,
				 const IlvPoint& p,
				 IlvTransformer* t = 0);
    static IlInt GetPointIndex(const IlvPolyPoints* polypoints,
			       const IlvPoint& p,
			       IlvTransformer* t = 0);
};

//-----------------------------------------------------------
class IlvStEditSplineInteractor : public IlvStEditPolyPointsInteractor
{
public:
    IlvStEditSplineInteractor()
	: IlvStEditPolyPointsInteractor() {}
    //___________________________________________________
    virtual void drawGhost();
    virtual void init();

    virtual void handleButtonDown(IlvEvent&);
    virtual void handleButtonDrag(IlvEvent&);
    virtual void handleButtonUp(IlvEvent&);
protected:
    IlBoolean _draggingOneCtrl;
    IlBoolean _draggingTwoCtrl;
    IlBoolean _closed;
    IlDouble  _startAngle;
    IlDouble  _startOffset;

    virtual void doMovePoints(const IlvPoint& delta);
    virtual void doMoveControlPoint(const IlvPoint& delta);
    virtual void doMoveSegment(const IlvPoint& delta);
    virtual void doInsertPoint(const IlvPoint&, IlUInt idx, IlDouble param=.5);
    virtual void doRemovePoint(IlUInt idx);

public:
    static void MoveBezierControlPoint(IlvPolyPoints* object,
				       const IlvPoint& delta,
				       IlUInt idx,
				       IlBoolean twoCtrl,
				       IlBoolean closed = IlFalse);
    static void MoveBezierPassagePoint(IlvPolyPoints* object,
				       const IlvPoint& delta,
				       IlUInt idx,
				       IlBoolean closed = IlFalse);
};

enum IlvBezierPoint
{
    IlvBezierUnknown=0,
    IlvBezierPassagePoint,
    IlvBezierRightControl,
    IlvBezierLeftControl
};

#define BEZIERWHICHPOINT(cnt, idx, closed) \
((IlTrue == closed)? \
(((IlUInt)(idx) >= (cnt))?IlvBezierUnknown: \
(((idx)%3==0)?IlvBezierPassagePoint: \
(((idx)%3==1)?IlvBezierRightControl: \
(((idx)%3==2)?IlvBezierLeftControl:IlvBezierUnknown)))) \
: \
(((IlUInt)(idx) >= (cnt))?IlvBezierUnknown: \
(((IlUInt)(idx)==(cnt)-1)?IlvBezierPassagePoint: \
(((idx)%3==0)?IlvBezierPassagePoint: \
(((idx)%3==1)?IlvBezierRightControl: \
(((idx)%3==2)?IlvBezierLeftControl:IlvBezierUnknown))))) )


#endif /* !__IlvSt_Editpoly_H */
