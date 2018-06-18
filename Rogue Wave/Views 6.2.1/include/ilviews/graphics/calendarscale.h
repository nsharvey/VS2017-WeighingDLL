// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/calendarscale.h
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
// Declaration of the IlvCalendarScale class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Calendarscale_H
#define __Ilv_Graphics_Calendarscale_H

#ifndef __Ilv_Graphics_Timescale_H
#include <ilviews/graphics/timescale.h>
#endif
#ifndef __Ilv_Graphics_Timescalerow_H
#include <ilviews/graphics/timescalerow.h>
#endif

class ILVVWSEXPORTED IlvCalendarScale : public IlvTimeScale
{
public:
    IlvCalendarScale(IlvDisplay*     display,
                      const IlvRect& drawrect,
                      IlvPalette*    palette = 0);

    ~IlvCalendarScale();

    virtual void	setRow(IlInt index, IlvTimeScaleRow* row);

    void		setVisibleDuration(IlvDuration duration);

    void		setVisibleInterval(IlDate time, IlvDuration duration);

    inline void		hidePredefinedRow(IlInt index)
			{
			    hideRow(getPredefinedRow(index));
			}

    inline void		showPredefinedRow(IlInt index)
			{
			    showRow(getPredefinedRow(index));
			}

    IlvTimeScaleRow*	getPredefinedRow(IlInt index);

    IlInt		getPredefinedRowCount();

    enum Rows {
	DECADE  = 0,
	YEAR    = 1,
	QUARTER = 2,
	MONTH   = 3,
	WEEK    = 4,
	DAY     = 5,
	HOUR    = 6,
	MINUTE  = 7,
	LASTROW
    };

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvCalendarScale);

protected:
    virtual void	drawRows(IlvPort* p, const IlvTransformer* t) const;

    virtual void	adjustRowVisibility(const IlvTransformer* t);

private:
    void		init();
    IlDouble		getSizeOf(IlCalendar::IlDateFields unit);
    IlDouble		getYearSize();
    IlDouble		getQuarterSize();
    IlDouble		getMonthSize();
    IlDouble		getWeekSize();
    IlDouble		getDaySize();
    IlDouble		getHourSize();
    IlDouble		getMinuteSize();
    int			getCharWidth();
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvCalendarTimeScaleRow : public IlvYearTimeScaleRow
{
public:
    IlvCalendarTimeScaleRow(IlvTimeScale* parent);

    inline IlInt		getYearStep() { return _step; }
    void			setYearStep(IlInt step);
    virtual IlDate		previousUnitTime(IlDate time);
    virtual IlDate		incrementTime(IlDate time);
    virtual IlString		computeDateText(IlDate time) const;
    virtual IlvTimeScaleRow*	copy() const;

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;

private:
    IlInt			_step;
};

ILVVWSMODULEINIT(g0calendarscale);

#endif /* __Ilv_Graphics_Calendarscale_H */
