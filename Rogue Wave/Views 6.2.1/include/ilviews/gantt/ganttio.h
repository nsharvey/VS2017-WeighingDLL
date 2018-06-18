// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gantt/ganttio.h
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
// Declaration of the Gantt Chart Input/Output related classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Gantt_Ganttio_H
#define __Ilv_Gantt_Ganttio_H

#if !defined(__Ilv_Grapher_Io_H)
#include <ilviews/grapher/io.h>
#endif
#if !defined(__Ilv_Gantt_Gantt_H)
#include <ilviews/gantt/gantt.h>
#endif

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttManagerOutputFile : public IlvManagerOutputFile
{
public:
    IlvGanttManagerOutputFile(ILVSTDPREF ostream&  os,
			      const IlvGanttChart* gantt = 0)
	: IlvManagerOutputFile(os, gantt ? gantt->getManager() : 0),
	  _gantt(gantt)
    {}

    inline
    const IlvGanttChart* getGanttChart() const { return _gantt; }
    virtual void	 saveMoreInfo(IlUInt count, IlvGraphic* const* objs);

protected:
    const IlvGanttChart* _gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttManagerInputFile : public IlvManagerInputFile
{
public:
    IlvGanttManagerInputFile(ILVSTDPREF istream&  is,
			     const IlvGanttChart* gantt = 0)
	: IlvManagerInputFile(is, gantt ? gantt->getManager() : 0),
	  _gantt(gantt)
    {}

    inline
    const IlvGanttChart* getGanttChart() const { return _gantt; }
    virtual IlBoolean	 parseBlock(const char*);

protected:
    const IlvGanttChart* _gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttGraphOutputFile : public IlvGraphOutputFile
{
public:
    IlvGanttGraphOutputFile(ILVSTDPREF ostream&  os,
			    const IlvGanttChart* gantt = 0)
	: IlvGraphOutputFile(os, gantt ? gantt->getGrapher() : 0),
	  _gantt(gantt)
    {}

    inline
    const IlvGanttChart* getGanttChart() const { return _gantt; }
    virtual void	 saveMoreInfo(IlUInt count, IlvGraphic* const* objs);

protected:
    const IlvGanttChart* _gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttGraphInputFile : public IlvGraphInputFile
{
public:
    IlvGanttGraphInputFile(ILVSTDPREF istream&  is,
			   const IlvGanttChart* gantt = 0)
	: IlvGraphInputFile(is, gantt ? gantt->getGrapher() : 0),
	  _gantt(gantt)
    {}

    inline
    const IlvGanttChart* getGanttChart() const { return _gantt; }
    virtual IlBoolean	 parseBlock(const char*);

protected:
    const IlvGanttChart* _gantt;
};

#endif /* !__Ilv_Gantt_Ganttio_H */
