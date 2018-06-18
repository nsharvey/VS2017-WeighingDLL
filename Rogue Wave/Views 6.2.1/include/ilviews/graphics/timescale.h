// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/timescale.h
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
// Declaration of the IlvTimeScale class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Timescale_H
#define __Ilv_Graphics_Timescale_H

#ifndef __Ilv_Base_Graphic_H
#include <ilviews/base/graphic.h>
#endif
#ifndef __Ilv_Graphics_Timeconverter_H
#include <ilviews/graphics/timeconverter.h>
#endif

class IlvTimeScaleRow;
class IlvTimeScalePaintContext;
class IlvTimeScale;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeUtil
{
public:
    static void		minuteFloor(IlCalendar& calendar);

    static void		hourFloor(IlCalendar& calendar);

    static void		halfDayFloor(IlCalendar& calendar);

    static void		dayFloor(IlCalendar& calendar);

    static void		weekFloor(IlCalendar& calendar);

    static void		monthFloor(IlCalendar& calendar);

    static void		yearFloor(IlCalendar& calendar);

    static IlDate	add(IlDate date, IlvDuration delta);

    static IlDate	subtract(IlDate date, IlvDuration delta);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeInterval
{
public:
    IlvTimeInterval(IlDate startTime, IlDate endTime);

    IlvTimeInterval(IlDate, IlvDuration, IlBoolean);

    inline IlDate	getStart() { return _start; }

    inline void		setStart(IlDate start) { _start = start; normalize(); }

    inline IlDate	getEnd() { return _end; }
    inline void		setEnd(IlDate end) { _end = end; normalize(); }

    inline void		setInterval(IlDate start, IlDate end)
			{
			    _start = start;
			    _end = end; normalize();
			}

    inline void		setIntervalDuration(IlDate start, IlvDuration duration)
			{
			    setInterval(start,
					IlvTimeUtil::add(start, duration));
			}

    
    inline IlvDuration	getDuration()
			{
			    return IlvTimeUtil::subtract(_end, _start);
			}

    inline void		setDuration(IlvDuration duration)
			{
			    setEnd(IlvTimeUtil::add(_start, duration));
			}

protected:

    void		normalize();

    IlDate		_start;
    IlDate		_end;
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeScrollable
{
public:
    virtual ~IlvTimeScrollable();

    virtual IlDate	getMinVisibleTime() const = 0;

    virtual void	setMinVisibleTime(IlDate d) = 0;

    virtual IlDate	getMaxVisibleTime() const = 0;

    virtual void	setMaxVisibleTime(IlDate d) = 0;

    virtual IlDate	getVisibleTime() const = 0;

    virtual void	setVisibleTime(IlDate time) = 0;

    virtual IlvDuration	getVisibleDuration() const = 0;

    virtual void	setVisibleDuration(IlvDuration duration) = 0;

    virtual
    IlvTimeInterval	getVisibleInterval() const = 0;

    virtual void	setVisibleInterval(IlDate time,
					   IlvDuration duration) = 0;
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeScalePaintContext
{
public:

    IlvTimeScalePaintContext(IlDate              visibleTime,
                             IlvDuration         duration,
                             IlDouble            XTranslation = 0.0,
                             IlDouble            XZoomFactor = 1.0,
                             IlvFont*            font = 0);

    IlvTimeScalePaintContext(const IlvTimeScale* tscale);

    IlvTimeScalePaintContext(const IlvTimeScalePaintContext&);
    virtual ~IlvTimeScalePaintContext();

    inline IlDouble	getXTranslation() const { return _XTranslation; }

    inline void		setXTranslation(IlDouble translation)
			{
			    _XTranslation = translation;
			}

    inline IlDouble	getXZoomFactor() const { return _XZoomFactor; }

    inline void		setXZoomFactor(IlDouble factor)
			{
			    _XZoomFactor = factor;
			}

    inline IlDouble	transform(IlDouble x) const
			{
			    return x * _XZoomFactor + _XTranslation;
			}

    inline IlDouble	inverseTransform(IlDouble x) const
			{
			    return (x - _XTranslation) / _XZoomFactor;
			}

    inline IlDate	getVisibleTime() const { return _time; }

    void		setVisibleTime(IlDate time);

    inline IlvDuration	getVisibleDuration() const { return _duration; }

    inline void		setVisibleDuration(IlvDuration duration)
			{
			    _duration = duration;
			}

    inline IlvFont*	getFont() const { return _font; }

    void		setFont(IlvFont* font);

protected:

    IlDate		_time;		// Start of the time interval drawn.
    IlvDuration		_duration;	// Duration of the time interval drawn.
    IlDouble		_XTranslation;	// Horizontal translation
    IlDouble		_XZoomFactor;	// Horizontal zoom factor
    IlvFont*		_font;		// Font used to draw the labels
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeScale
    : public IlvSimpleGraphic, public IlvTimeScrollable
{
    friend class IlvTimeScalePaintContext;

public:
    IlvTimeScale(IlvDisplay*    display,
                 const IlvRect& drawrect,
                 IlvPalette*    palette = 0);

    ~IlvTimeScale();

    IlvTimeScalePaintContext*	getPaintContext();

    IlvTimeScalePaintContext*	createPaintContext(IlDate      start,
						   IlvDuration duration,
						   IlvRect     viewport);

    virtual void	addRow(IlvTimeScaleRow* row);

    virtual IlBoolean	removeRow(IlvTimeScaleRow* row);

    virtual
    IlvTimeScaleRow*	getRow(IlInt index) const;

    virtual void	setRow(IlInt index, IlvTimeScaleRow* row);

    virtual IlInt	getIndex(IlvTimeScaleRow* row) const;

    virtual IlDate	getTime(IlInt x);

    virtual IlInt	getLocation(IlDate time);

    virtual IlInt	getLocation(IlDate time,
				    const IlvTimeScalePaintContext& context);

    inline IlUInt	getCardinal() const { return _list.getLength(); }

    virtual void	showRow(IlvTimeScaleRow* row);

    virtual void	hideRow(IlvTimeScaleRow* row);

    virtual void	showRow(IlInt index);

    virtual void	hideRow(IlInt index);

    // Internal methods
    virtual void	move(IlvPos x, IlvPos y);
    virtual void	boundingBox(IlvRect&              r,
				    const IlvTransformer* t = 0) const;

    void		syncOffset();
    IlDouble		computeOffset(IlDate   start,
				      IlDouble zoomFactor) const;
    void		syncZoomFactor();
    double		computeZoomFactor(IlDate   start,
					  IlDouble duration,
					  int      width);

    //--------------- IlvTimeScrollable interface
    virtual IlDate	getMinVisibleTime() const;
    virtual void	setMinVisibleTime(IlDate d);

    virtual IlDate	getMaxVisibleTime() const;
    virtual void	setMaxVisibleTime(IlDate d);

    virtual IlDate	getVisibleTime() const;
    virtual void	setVisibleTime(IlDate time);

    virtual IlvDuration	getVisibleDuration() const;
    virtual void	setVisibleDuration(IlvDuration duration);

    virtual
    IlvTimeInterval	getVisibleInterval() const;
    virtual void	setVisibleInterval(IlDate      time,
						   IlvDuration duration);
    //--------------- IlvTimeScrollable interface

    inline
    IlvTimeConverter*	getTimeConverter() const { return _timeConverter; }
    void		setTimeConverter(IlvTimeConverter* t);

    inline IlCalendar*	getCalendar() { return _calendar; }

    IlCalendar*		getCalendar(IlDate time);

    inline IlDouble	getZoomFactor() const { return _zoomFactor; }
    inline IlDouble	getOffset() const { return _offset; }

    //
    // IlvGraphic methods
    //

    void		draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion * = 0) const;
    void		applyTransform(const IlvTransformer*);

    inline IlBoolean	isLabelVisible() const { return _showLabel; }

    inline void		setLabelVisible(IlBoolean visible)
			{
			    _showLabel = visible;
			}
    inline IlBoolean	isSeparatorVisible() const
			{
			    return _showSeparator;
			}
    inline void		setSeparatorVisible(IlBoolean visible)
			{
			    _showSeparator = visible;
			}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvTimeScale);

protected:

    virtual void	drawWithContext(IlvPort* p,
					const IlvTransformer* t,
					const IlvTimeScalePaintContext&) const;

    virtual void	drawRows(IlvPort* p, const IlvTransformer* t) const;

    virtual void	drawSeparator(IlvPort*,
				      const IlvTransformer* t,
				      IlInt                 x,
				      IlInt                 y,
				      IlInt                 width) const;

    void		shiftRows(IlInt index, IlvDim height);

    // The beginning of the displayed time interval.
    IlDate		_time;

    // The duration of the displayed time interval.
    IlDate		_duration;

    IlvTimeConverter*	_timeConverter;

    // The horizontal zoom factor
    IlDouble		_zoomFactor;
    IlDouble		_offset;

    // for IlCalendar
    IlGregorianCalendar* _calendar;
    IlGregorianCalendar* _calendarClone;

    IlDate		_min;
    IlDate		_max;

    IlvRect		_drawrect;
    IlBoolean		_showLabel;
    IlBoolean		_showSeparator;

    // Rows list
    IlList		_list;
};

ILVVWSMODULEINIT(g0timescale);

#endif /* __Ilv_Graphics_Timescale_H */
