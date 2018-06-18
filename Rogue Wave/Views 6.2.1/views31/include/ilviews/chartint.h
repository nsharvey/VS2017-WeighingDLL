// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/chartint.h
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
// Declaration of predefined view object interactors for charts
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Chartint_H
#define __Ilv31_Chartint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv31_Chart_H)
#include <ilviews/chart.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewChartInteractorSelectPoint
: public IlvViewObjectInteractor {
public:
    IlvViewChartInteractorSelectPoint(IlUInt whichButton = IlvLeftButton)
    : _whichButton(whichButton),
      _size(4)
    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t=0);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual void doIt(IlvContainer*, IlvChart* chart, IlUInt num);
    virtual const char* className() const;
    virtual void drawGhost(IlvContainer* view, IlvPoint& p);
    void setSize(IlvDim size) { _size = size; }
protected:
    IlUInt	 _whichButton;
    IlvDim	 _size;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewChartInteractorDragPoint
: public IlvViewObjectInteractor {
public:
    IlvViewChartInteractorDragPoint(IlUInt whichButton = IlvLeftButton)
    : _whichButton(whichButton),
      _size(4)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvChart*, IlUInt, IlvPoint&);
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view, IlvTransformer* t=0);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual void doIt(IlvContainer*, IlvChart*, IlUInt, IlvPoint&);
    virtual void drawGhost(IlvContainer* view, IlvPoint& p);
    void setSize(IlvDim size) { _size = size; }
    virtual const char* className() const;
 protected:
    IlUInt _whichButton;
    IlvDim  _size;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewChartInteractorDragXPoint
: public IlvViewChartInteractorDragPoint {
public:
    IlvViewChartInteractorDragXPoint(IlUInt whichButton = IlvLeftButton)
    : IlvViewChartInteractorDragPoint(whichButton)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvChart* chart,
			  IlUInt num, IlvPoint& point);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewChartInteractorDragYPoint
: public IlvViewChartInteractorDragPoint {
public:
    IlvViewChartInteractorDragYPoint(IlUInt whichButton=IlvLeftButton)
    : IlvViewChartInteractorDragPoint(whichButton)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvChart*, IlUInt num, IlvPoint&);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewStackedChartInteractorDragPoint
: public IlvViewObjectInteractor {
public:
    IlvViewStackedChartInteractorDragPoint(IlUInt whichButton=IlvLeftButton)
    : _whichButton(whichButton),
      _size(4)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvStackedChart*,
			  IlvChartData*, IlUInt, IlvPoint&);
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view, IlvTransformer* t=0);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual void doIt(IlvContainer*, IlvStackedChart*, IlvChartData*,
		      IlUInt num, IlvPoint& point);
    virtual void drawGhost(IlvContainer* view, IlvPoint& p);
    void setSize(IlvDim size) { _size = size; }
    virtual const char* className() const;
protected:
    IlUInt	_whichButton;
    IlvDim	_size;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewStackedChartInteractorDragYPoint
: public IlvViewStackedChartInteractorDragPoint {
public:
    IlvViewStackedChartInteractorDragYPoint(IlUInt b = IlvLeftButton)
    : IlvViewStackedChartInteractorDragPoint(b)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvStackedChart*,
			  IlvChartData*, IlUInt num, IlvPoint&);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewStackedChartInteractorDragXPoint
    : public IlvViewStackedChartInteractorDragPoint {
public:
    IlvViewStackedChartInteractorDragXPoint(IlUInt b = IlvLeftButton)
    : IlvViewStackedChartInteractorDragPoint(b)
    {}
    // ____________________________________________________________
    virtual void validate(IlvContainer*, IlvStackedChart*,
			  IlvChartData*, IlUInt num, IlvPoint&);
    virtual const char* className() const;
};

ILV31VWSMODULEINIT(chartint);
#endif /* !__Ilv31_Chartint_H */
