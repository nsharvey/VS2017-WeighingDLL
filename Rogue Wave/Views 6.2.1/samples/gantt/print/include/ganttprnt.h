// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/print/include/ganttprnt.h
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
// Gantt printing class
// --------------------------------------------------------------------------

#ifndef __GanttPrinting__header__
#define __GanttPrinting__header__

#include <ilviews/gantt/gantt.h>

// --------------------------------------------------------------------------
class GanttChartPrintingUtility
{
public:

    // ----------------------------------------------------------------------
    GanttChartPrintingUtility(IlvGanttChart * gantt);
    
    virtual ~GanttChartPrintingUtility();

    // ----------------------------------------------------------------------
    virtual void printGantt();

    inline void setGantt(IlvGanttChart* gantt) {_gantt = gantt;}

    inline IlvGanttChart* getGantt() {return _gantt;}

protected:
    virtual void printPage( IlvRect pageSize, 
                            IlvPort* port, 
                            IlUShort fromLine, 
                            IlUShort toLine );
               
    virtual void printScale(IlvRect pageSize,
                            IlvPort* port );

    virtual void printLines(IlvRect pageSize,
			    IlvPort* port, 
			    IlUShort fromLine, 
			    IlUShort toLine );

    virtual void printActivities(IlvRect pageSize, 
				 IlvPort* port, 
				 IlUShort fromLine, 
				 IlUShort toLine );

    IlvGanttChart* _gantt;
};

#endif // !__GanttPrinting__header__
