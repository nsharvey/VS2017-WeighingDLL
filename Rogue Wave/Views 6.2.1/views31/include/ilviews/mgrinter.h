// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/mgrinter.h
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
// Declaration of the IlvManagerChartInteractor
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Mgrinter_H
#define __Ilv31_Mgrinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv31_Chart_H)
#include <ilviews/chart.h>
#endif
#if !defined(__Ilv_Graphics_Gauge_H)
#include <ilviews/graphics/gauge.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerGaugeInteractor
: public IlvManagerObjectInteractor
{
public:
    // ____________________________________________________________
    virtual IlBoolean   handleEvent(IlvManager*     manager,
				    IlvGraphic*     obj,
				    IlvEvent&       event,
				    IlvView*        view,
				    IlvTransformer* t = 0);
    virtual void        valueChanged(IlvManager* manager,
				     IlvGauge*   gauge,
				     IlInt      value);
    virtual void        draggedValueChanged(IlvManager* manager,
					    IlvGauge*   gauge,
					    IlInt      value);
    virtual IlBoolean   invalidValueSet(IlvManager*, IlvGauge*, IlInt);
    virtual IlBoolean   accept(const IlvGraphic*) const;
    virtual const char* className() const;

protected:
    virtual void        doChange(IlvManager* manager,
				 IlvGauge*   gauge,
				 IlInt      value);
};
ILV31VWSMODULEINIT(mgrgaugeinter);

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerChartInteractorSelectPoint
: public IlvManagerObjectInteractor
{
public:
    IlvManagerChartInteractorSelectPoint(IlUInt button = IlvLeftButton)
    : _whichButton(button)
    {}
    virtual IlBoolean   handleEvent(IlvManager*     manager,
				    IlvGraphic*     obj,
				    IlvEvent&       event,
				    IlvView*        view,
				    IlvTransformer* t = 0);
    virtual void        doIt(IlvManager* manager,
			     IlvChart*   chart,
			     IlUInt     index);
    virtual IlBoolean   accept(const IlvGraphic*) const;
    virtual const char* className() const;

protected:
    IlUInt	_whichButton;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerChartInteractorDragPoint
: public IlvManagerObjectInteractor
{
public:
    IlvManagerChartInteractorDragPoint(IlUInt button = IlvLeftButton)
    : _whichButton(button)
    {}
    // ____________________________________________________________
    virtual void        validate(IlvChart*       chart,
				 IlUInt          index,
				 IlvPoint&       point,
				 IlvTransformer* t);
    virtual IlBoolean   handleEvent(IlvManager*     manager,
				    IlvGraphic*     obj,
				    IlvEvent&       event,
				    IlvView*        view,
				    IlvTransformer* t = 0);
    virtual void        doIt(IlvManager* manager,
			     IlvChart*   chart,
			     IlUInt     index,
			     IlvPoint&   point);
    virtual const char* className() const;
    virtual void        drawGhost(IlvView* view, IlvPoint& p);
    virtual IlBoolean   accept(const IlvGraphic*) const;

protected:
    IlUInt	_whichButton;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerChartInteractorDragXPoint
: public IlvManagerChartInteractorDragPoint
{
public:
    IlvManagerChartInteractorDragXPoint(IlUInt button = IlvLeftButton)
    : IlvManagerChartInteractorDragPoint(button)
    {}
    // ____________________________________________________________
    virtual void validate(IlvChart*       chart,
			  IlUInt         num,
			  IlvPoint&       point,
			  IlvTransformer* t);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerChartInteractorDragYPoint
: public IlvManagerChartInteractorDragPoint
{
public:
    IlvManagerChartInteractorDragYPoint(IlUInt button = IlvLeftButton)
        : IlvManagerChartInteractorDragPoint(button) {}

    virtual void        validate(IlvChart*       chart,
				 IlUInt         num,
				 IlvPoint&       point,
				 IlvTransformer* t);
    virtual const char* className() const;
};

ILV31VWSMODULEINIT(mgroldchartinter);
#endif /* !__Ilv31_Mgrinter_H */
