// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gantt/ganttgrd.h
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
// Declaration of the Gantt Chart interactors classes
// --------------------------------------------------------------------------

#ifndef __Ilv_Gantt_Ganttgrd_H
#define __Ilv_Gantt_Ganttgrd_H

#include <ilviews/gantt/gantt.h>
#include <ilviews/gantt/ganttfrm.h>
#include <ilviews/graphics/shadrect.h>
#include <ilviews/graphics/calendarscale.h>

class ILVGTEXPORTED IlvGanttHorizontalGridImpl
{
public:
    IlvGanttHorizontalGridImpl() {}

    virtual
    IlvGanttChart*	getGanttChart() const = 0;

    virtual void	getGridArea(IlvRect& area) const = 0;

    virtual IlvPalette*	getForegroundPalette() const = 0;

    virtual IlvPalette*	getBackgroundPalette() const = 0;

    virtual void	drawGrid(IlvPort* port,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;

    virtual void	drawLine(IlvPort* port, 
				 const IlvPalette* palette,
				 const IlvTransformer* t,
				 IlvPoint& from,
				 IlvPoint& to) const;

    virtual void	fillGrid(IlvPort* port,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

class ILVGTEXPORTED IlvGanttHorizontalGrid
    : public IlvGanttHorizontalGridImpl,
      public IlvSimpleGraphic
{
public:
    IlvGanttHorizontalGrid(IlvGanttChart* gantt,
   			   const IlvRect& rect,			   
			   IlvPalette*    palette = 0);
    ~IlvGanttHorizontalGrid();

    virtual
    IlvGanttChart*	getGanttChart() const;
    virtual void	getGridArea(IlvRect& area) const;
    virtual IlvPalette*	getForegroundPalette() const;
    virtual IlvPalette*	getBackgroundPalette() const;
    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort* port,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual IlvGraphic*	copy() const;
    virtual void	write(IlvOutputFile& output) const;

protected:
    IlvGanttChart*	_gantt;
    IlvPalette*		_inverted;
    IlvRect		_drawrect;
};

class ILVGTEXPORTED IlvGanttLineGrid : public IlvGanttHorizontalGrid
{
public:
    IlvGanttLineGrid(IlvGanttChart* gantt, IlvPalette* palette = 0);

    IlvGanttLineGrid(IlvGanttChart* gantt,
   		     const IlvRect& rect,			   
		     IlvPalette*    palette = 0);
};

class ILVGTEXPORTED IlvGanttLineReliefGrid : public IlvGanttLineGrid
{
public:
    IlvGanttLineReliefGrid(IlvGanttChart* gantt, IlvPalette* gridPal);

    virtual void	drawLine(IlvPort* port, 
				 const IlvPalette* palette,
				 const IlvTransformer* t,
				 IlvPoint& from,
				 IlvPoint& to) const;

    virtual void	fillGrid(IlvPort* port,
				 const IlvTransformer* t,
				 const IlvRegion* clip) const;
};

class ILVGTEXPORTED IlvGanttResourceGrid : public IlvGanttLineGrid
{
public:
    IlvGanttResourceGrid(IlvGanttChartForm* gantt, IlvPalette* palette = 0);

    virtual void	drawGrid(IlvPort* port,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

class ILVGTEXPORTED IlvGanttRowGrid : public IlvGanttHorizontalGrid
{
public:
    IlvGanttRowGrid(IlvGanttChart* gantt, IlvPalette* palette = 0);

    virtual void	drawGrid(IlvPort* port,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

class ILVGTEXPORTED IlvGanttCalendarGrid
    : public IlvGanttHorizontalGridImpl,
      public IlvCalendarScale
{
public:
    IlvGanttCalendarGrid(IlvGanttChart* gantt, IlvPalette* palette = 0);

    IlvGanttCalendarGrid(IlvGanttChart* gantt,
   			 const IlvRect& rect,			   
			 IlvPalette* palette = 0);
    ~IlvGanttCalendarGrid();

    virtual
    IlvGanttChart*	getGanttChart() const;
    virtual void	getGridArea(IlvRect& area) const;
    virtual IlvPalette*	getForegroundPalette() const;
    virtual IlvPalette*	getBackgroundPalette() const;

    virtual void	draw(IlvPort* port,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

protected:
    virtual void	adjustRowVisibility(const IlvTransformer* t);

protected:
    IlvGanttChart*	_gantt;
    IlvPalette*		_inverted;
};

#endif /* !__Ilv_Gantt_Ganttgrd_H*/
