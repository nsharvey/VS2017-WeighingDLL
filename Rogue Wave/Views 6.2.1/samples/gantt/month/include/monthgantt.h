// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/month/include/monthgantt.h
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

#ifndef __monthgantt__header__
#define __monthgantt__header__

#include <loadgantt.h>

// --------------------------------------------------------------------------
//$doc:Decl
class MonthGanttChart
    : public LoadGanttChart
{
public:
    MonthGanttChart(IlvDisplay*    display,
		    const IlvRect& rect,
                    IlInt          start,
		    IlInt          end,
                    IlUShort       step,
		    IlUShort       day,
                    IlvDim         rowsize,
		    IlvDim         unitsize = 16,
                    IlUShort       gridThickness = 3,
		    IlvPalette*    palette = 0)
        : LoadGanttChart(display, rect, start, end, start, start + 7 * 24,
                         step, rowsize, unitsize, gridThickness, palette),
            _day(day) {}
    virtual ~MonthGanttChart();
    // ___________________________________________________
    virtual void drawGrid(IlvPort* dst,
			  IlUShort index,
                          IlBoolean skipCompute = IlFalse,
                          const IlvRegion* clip = 0,
			  IlvTransformer* t = 0,
			  IlvDirection d =
			      (IlvDirection)(IlvHorizontal|IlvVertical));
    virtual IlvScale* createScale(IlvDisplay*,
				  const IlvPoint& orig,
                                  IlvDim size,
				  IlInt start,
				  IlInt end,
                                  IlUShort step,
				  IlvPosition p = IlvTop) const;
    virtual void  updateScale(IlvScale*,
			      IlBoolean redraw = IlTrue) const;
    void computeScaleLabels(IlInt start,
			    IlInt end,
			    IlUShort step,
                            IlUShort& count,
			    char** labels) const;
    IlUShort getDay() const { return _day; }
    DeclareTypeInfo();
    DeclareIOConstructors(MonthGanttChart);
protected:
    IlUShort   _day;
};
//end:Decl

extern IlvBoolean
IlvGanttComputeDay(IlUShort month,
		   IlUShort year,
		   IlUShort& day,
		   IlInt& start,
		   IlInt& end,
		   IlUShort& step);

#endif /* !__monthgantt__header__*/
