// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/timescalerow.h
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
// Declaration of the IlvTimeScaleRow class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Timescalerow_H
#define __Ilv_Graphics_Timescalerow_H

#ifndef __Ilv_Base_Graphic_H
#include <ilviews/base/graphic.h>
#endif
#ifndef __Ilv_Graphics_Timeconverter_H
#include <ilviews/graphics/timeconverter.h>
#endif

class IlvTimeScalePaintContext;
class IlvTimeScaleRow;
class IlvTimeScale;
class IlvTimeIterator;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeScaleRowFactory
{
public:
    enum rowtype {
	INVALID = -1,
	MINUTE = 0,
	HOUR,
	HALFDAY,
	DAY,
	WEEK,
	MONTH,
	QUARTER,
	YEAR
    };

    static IlvTimeScaleRow* create(rowtype, IlvTimeScale* parent);
    static IlvTimeScaleRow* read(IlvTimeScale* parent, IlvInputFile&);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeScaleRow
{
    friend class IlvTimeScale;

public:

    IlvTimeScaleRow(IlvTimeScale* parent);

    virtual ~IlvTimeScaleRow();

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile& outfile) const;

    virtual void		read(IlvInputFile& infile);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const = 0;

    virtual IlDate		nextUnitTime(IlDate dateval);

    virtual IlDate		previousUnitTime(IlDate dateval) = 0;

    virtual IlDate		incrementTime(IlDate dateval) = 0;
    virtual IlString		computeDateText(IlDate) const;

    virtual IlInt		getPreferredHeight() const;

    void			setVisible(IlBoolean visible);

    inline IlBoolean		isVisible() { return _visible ; }

    const IlTimeUnit*		getTimeUnit() const;

    IlCalendar*			getCalendar() const;

    IlCalendar*			getCalendar(IlDate time) const;

    void			setTimeScale(IlvTimeScale* timescale);

    inline IlvTimeScale*	getTimeScale() const { return _timescale; }

    IlvPalette*			getPalette() const;

    IlvDisplay*			getDisplay() const;

    void			setTickColor(IlvColor* c);

    IlvColor*			getTickColor() const;

    IlvPalette*			getTickPalette() const;

    void			setTextColor(IlvColor* c);

    IlvColor*			getTextColor() const;

    IlvPalette*			getTextPalette() const;

    void			setTextFont(IlvFont* f);

    IlvFont*			getTextFont() const;

    enum TextPos {
	LEFT,
	RIGHT,
	CENTER
    };

    void			setTextPosition(TextPos pos);

    inline TextPos		getTextPosition() const { return _position; }

    void			setAdditionalString(IlString str);

    inline IlString		getAdditionalString() const
				{
				    return _leftopen;
				}

    void			setIntervalMinWidth(IlInt value);

    inline IlInt		getIntervalMinWidth() const
				{
				    return _threshold;
				}

    inline IlBoolean		isOverlappingLabelAllowed() const
				{
				    return _overlappingLabelAllowed;
				}

    void			setOverlappingLabelAllowed(IlBoolean overlap);

protected:

    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale* scale) const = 0;

    virtual void		draw(IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvTimeScalePaintContext& context,
				     const IlvRect& rect) const;

    virtual void		drawLabel(IlvPort* dst,
					  const IlvTransformer* t,
					  const IlvPoint& prevPos,
					  const IlvPoint& nextPos,
					  IlString text) const;

    virtual void		drawTick(IlvPort* dst,
					 const IlvTransformer* t,
					 const IlvPoint& pos,
					 IlInt height) const;

    void			setTimeUnit(IlTimeUnit* u);


    // Drawing parameters
    IlBoolean			_visible;
    IlvPalette*                 _tickPalette;
    IlvPalette*                 _textPalette;
    TextPos			_position;

    IlBoolean			_overlappingLabelAllowed;

    IlString			_leftopen;

    IlInt			_threshold;

    IlTimeUnit*			_unit;
    IlGregorianCalendar*	_utilCal;
    IlDateErrorCode		_errCode;
    IlvTimeIterator*		_timeIterator;

    IlvTimeScale*		_timescale;
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvYearTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvYearTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvQuarterTimeScaleRow : public IlvTimeScaleRow
{
public:

    IlvQuarterTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

    virtual IlString		computeDateText(IlDate dateval) const;

    void			setYearMode(IlBoolean val);

    inline IlBoolean		isYearMode() { return _yearmode; }

    void			setQuarterShortString(IlString str);

    inline IlString		getQuarterShortString() const
				{
				    return _qsstring;
				}

    void			setQuarterLongString(IlString str);

    inline IlString		getQuarterLongString() const
				{
				    return _qlstring;
				}

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;


    IlBoolean			_yearmode;
    IlString			_qsstring;
    IlString			_qlstring;

    static IlCalendar::EMonths	_qtrbegin[];
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMonthTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvMonthTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;

};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvWeekTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvWeekTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvDayTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvDayTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvHalfDayTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvHalfDayTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;

    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    virtual IlDate		previousUnitTime(IlDate dateval);

    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvHourTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvHourTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;
    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    void			setHourStep(IlInt value);
    inline IlInt		getHourStep() { return _mult; }

    virtual IlDate		previousUnitTime(IlDate dateval);
    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;

    IlInt			_mult;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMinuteTimeScaleRow : public IlvTimeScaleRow
{
public:
    IlvMinuteTimeScaleRow(IlvTimeScale* parent);

    virtual IlvTimeScaleRow*	copy() const;

    virtual void		write(IlvOutputFile&) const;
    virtual void		read(IlvInputFile&);

    virtual IlvTimeScaleRowFactory::rowtype	getType() const;

    void			setMinuteStep(IlInt value);
    inline IlInt		getMinuteStep() { return _mult; }

    virtual IlDate		previousUnitTime(IlDate dateval);
    virtual IlDate		incrementTime(IlDate dateval);

protected:
    virtual IlvTimeScaleRow*	cloneType(IlvTimeScale*) const;

    IlInt			_mult;
    IlvDuration			_duration;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTimeIterator
{
public:
    IlvTimeIterator(IlvTimeScaleRow* parent) : _parent(parent), _t(0) {}

    inline void		start(IlDate scaleStart)
			{
			    _t = _parent->nextUnitTime(scaleStart);
			}

    inline void		next() { _t = _parent->incrementTime(_t); }

    inline IlDate	getTime() { return _t; }

    IlString		getText();

    IlInt		getXLocation();

    IlInt		getXLocation(const IlvTimeScalePaintContext& paintCtx);

    void		clearDateTextCache();

protected:
    IlvTimeScaleRow*	_parent;
    IlDate		_t;
};


#endif /* __Ilv_Graphics_Timescalerow_H */
