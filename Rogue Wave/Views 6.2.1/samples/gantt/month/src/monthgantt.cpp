// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/month/src/monthgantt.cpp
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
//
// --------------------------------------------------------------------------

#include <ilviews/grapher/grapher.h>
#include <ilviews/graphics/scale.h>
#include <ilviews/gantt/gantt.h>
#include <monthgantt.h>

#if defined(IL_STD)
#include <cstdio>
#include <cstring>
#include <iostream>
IL_STDUSE
#else  /* !IL_STD */
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
struct MONTHGANTTDATA {
    IlUShort count;
    char**    labels;
};

// --------------------------------------------------------------------------
static const char* daysArray[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

// --------------------------------------------------------------------------
IlvBoolean
IlvGanttComputeDay(IlUShort month,
		   IlUShort year,
		   IlUShort& day,
		   IlInt& start,
		   IlInt& end,
		   IlUShort& step)
{
    static IlUShort monthdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    if (year <= 1752) {
	IlvWarning("Bad Year Argument : should be greater than 1752");
	return IlFalse;
    }
    if ((month < 1) || (month > 12)) {
	IlvWarning("Bad Month Argument");
	return IlFalse;
    }
    start = 0;
    step  = 24;
    IlBoolean isFeb29 = (!(year % 4) && ((year % 100) || !(year % 400)));
    if (month == 2)
	end = (isFeb29 ? 29 : 28) * 24;
    else {
	end = (((month == 4)||(month == 6)||(month == 9)||(month == 11))?
	       30 : 31) * 24;
    }
    IlUInt days = (IlUInt)((((IlInt)year - 1753) * 365) +
			   (((IlInt)year - 1753) /   4) -
			   (((IlInt)year - 1701) / 100) +
			   (((IlInt)year - 1601) / 400));
    if (isFeb29)
	monthdays[1] = 29;
    for (IlUShort i = 1; i < month; ++i)
	days += monthdays[i - 1];
    day = (IlUShort)((days + 2) % 7);
    if (day == 0)
	day = 7;
    return IlTrue;
}

// --------------------------------------------------------------------------
static void
SetScaleLabels(IlvGraphic* scale,
	       IlAny arg)
{
    MONTHGANTTDATA* data = (MONTHGANTTDATA*)arg;
    ((IlvRectangularScale*)scale)->setLabels(data->count,
					     (const char**)data->labels);
}

// --------------------------------------------------------------------------
MonthGanttChart::MonthGanttChart(IlvInputFile& is,
				 IlvPalette* palette)
    : LoadGanttChart(is, palette)
{
    is.getStream() >> _day;
}

// --------------------------------------------------------------------------
MonthGanttChart::MonthGanttChart(const MonthGanttChart& source)
    : LoadGanttChart(source), _day(source._day)
{
}

// --------------------------------------------------------------------------
MonthGanttChart::~MonthGanttChart()
{
}

// --------------------------------------------------------------------------
//$doc:CrSc
IlvScale*
MonthGanttChart::createScale(IlvDisplay* display,
			     const IlvPoint& orig,
                             IlvDim size,
			     IlInt start,
			     IlInt end,
                             IlUShort step,
			     IlvPosition position) const
{
    IlUShort count;
    char* labels[32];

    // Internal method to create every label displayed on the scale
    computeScaleLabels(start, end, step, count, labels);
    // Create the scale object
    IlvRectangularScale* scale =
        new IlvRectangularScale(display, orig, size, labels,
                                IlvHorizontal, position, count,
                                12, 10, 5, getPalette());

    // Labels will be centered
    scale->centerLabels(IlTrue);

    // Labels cannot overlap
    scale->drawOverlappingLabels(IlFalse);

    // Clean memory
    for (IlUShort i = 0; i < count; ++i)
        delete labels[i];

    return scale;
}
//end:CrSc

// --------------------------------------------------------------------------
void
MonthGanttChart::computeScaleLabels(IlInt start,
				    IlInt end,
				    IlUShort step,
				    IlUShort& count,
				    char** labels) const
{
    count = (IlUShort)(((end - start) / (IlInt)step) + 1);
    IlUShort day = (IlUShort)((start - _start) / 24);
    long dayInWeek = (long)(((IlInt)day + (IlInt)_day - 1) % 7);
    char dayNum[4];
    for (long i = 0; i < (long)count; ++i) {
	labels[i] = new char[strlen(daysArray[(i + dayInWeek) % 7]) + 4];
	strcpy(labels[i], daysArray[(i + dayInWeek) % 7]);
	sprintf(dayNum, ":%ld", i + day + 1);
	strcat(labels[i], dayNum);
    }
    if (end == _end) {
	labels[count - 1][4] = '1';
	labels[count - 1][5] = 0;
    }
}

// --------------------------------------------------------------------------
//$doc:UpSc
void
MonthGanttChart::updateScale(IlvScale* scale,
			     IlBoolean redraw) const
{
    IlvContainer* container = getGadgetContainer();
    IlUShort count;

    // Get index of the scale to be updated (0 if it is the left scale,
    // 1 if it is the right scale)
    IlvUShort hi = (IlUShort)((scale == getScale(0)) ? 0 : 1);

    // Get the labels to be displayed
    char* labels[32];
    computeScaleLabels(getShownStart(hi), getShownEnd(hi),
                       getStep(hi), count, labels);

    MONTHGANTTDATA arg;
    arg.count  = count;
    arg.labels = labels;
    container->applyToObject(scale, SetScaleLabels, &arg, redraw);

    // Clean memory
    for (IlUShort i = 0; i < count; ++i)
        delete labels[i];
}
//end:UpSc

// --------------------------------------------------------------------------
//$doc:DrGr
void
MonthGanttChart::drawGrid(IlvPort* dst,
			  IlUShort ix,
                          IlBoolean skipCompute,
			  const IlvRegion* clip,
			  IlvTransformer*,
			  IlvDirection)
{
  if (!isShowingGrid() || !getGadgetContainer() || rows() == 0)
    return;

  IlvColor* foreground = getGridPalette()->getBackground();
  IlvColor* background = getGridPalette()->getForeground();
  IlvPalette* holidayPalette = getDisplay()->getPalette(background, foreground);
  holidayPalette->lock();
  {
    IlvPushClip pushClip(*holidayPalette, clip);

    // The time graduation (step) is 1 hour, 24 means 24 hours per day
    IlUShort dayInWeek,
      startDay = (IlUShort)((getShownStart(ix & 1) - getStart()) / 24),
      endDay = (IlUShort)(getShownEnd((ix & 1) - getStart()) / 24);
    IlUShort fvRow = firstVisibleRow(ix / 2);
    IlUShort lvRow = lastVisibleRow(ix / 2);
    IlUShort toRow = IlvMin((IlUShort)(lvRow + 2), rows());

    // Gets the current grapher view transformer
    IlvTransformer* t = getGrapher()->getTransformer(getGrapherView(ix));
    IlvRect rect;

    // In the visible part, check if there is a Sunday or a Saturday
    // and fill the grapher view regions that correspond to these
    // days with a specific pattern (holidayPalette)
    IlvRect fromRect, toRect;
    rowBBox(fvRow, fromRect);
    rowBBox(toRow, toRect);
    for (IlUShort day = startDay; day < endDay; ++day) {
      dayInWeek = (IlUShort)(((IlInt)day + (IlInt)_day - 1) % 7);
      if ((dayInWeek == 6) || (dayInWeek == 0)) {
	rect.moveResize(day * 24, fromRect.y(),
			(IlvDim)getStep(ix & 1),
			(IlvDim)(toRect.y() - fromRect.y()));
	if (t)
	  t->apply(rect);
	dst->fillRectangle(holidayPalette, rect);
      }
    }
    LoadGanttChart::drawGrid(dst, ix, skipCompute, clip);
  }
  holidayPalette->unLock();
}
//end:DrGr

IlvPredefinedIOMembers(MonthGanttChart)
// --------------------------------------------------------------------------
void
MonthGanttChart::write(IlvOutputFile& os) const
{
    LoadGanttChart::write(os);
    os.getStream() << IlvSpc() << _day << IlvSpc();
}

// --------------------------------------------------------------------------
#if defined(linux) || defined(__TCPLUSPLUS__)
IlvPreRegisterClass(MonthGanttChart);
static int initMonthGanttChart()
{ IlvPostRegisterClass(MonthGanttChart, LoadGanttChart); return 0; }
static int _initMonthGanttChart = initMonthGanttChart();
#else  /* !linux && !defined(__TCPLUSPLUS__) */
IlvRegisterClass(MonthGanttChart, LoadGanttChart);
#endif /* !linux && !defined(__TCPLUSPLUS__) */
