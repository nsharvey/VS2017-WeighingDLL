// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/load/include/loadgantt.h
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

#ifndef __loadgantt__header__
#define __loadgantt__header__

#include <ilviews/gantt/gantt.h>

class LoadGanttChart;
// --------------------------------------------------------------------------
class LoadGanttInfo
{
friend class LoadGanttChart;
public:
    LoadGanttInfo(IlvInt load,
		  const IlvRect& rect);
    virtual ~LoadGanttInfo();
protected:
    IlvRect*     _rects;
    IlvInt*      _loads;
    IlUShort     _fromIndex[4];
    IlUShort     _toIndex[4];
    IlUShort     _count;
    IlUShort     _alloc;
};

// --------------------------------------------------------------------------
class LoadGanttChart
    : public IlvGanttChart
{
public:
    LoadGanttChart(IlvDisplay*    display,
		   const IlvRect& rect,
		   IlInt          start,
		   IlInt          end,
		   IlInt          shownStart,
		   IlInt          shownEnd,
		   IlUShort       step,
		   IlvDim         rowsize,
		   IlvDim         unitsize = 15,
		   IlUShort       gridThickness = 3,
		   IlvPalette*    palette = 0)
	: IlvGanttChart(display, rect, start, end,
			shownStart, shownEnd, step, rowsize, 0, unitsize,
			32, 16,	4, 8, 0, 12, IlvTop, IlvBottom, IlvRight,
			4, IlTrue, palette), _gridThickness(gridThickness)
    {
        makeLoadPalettes(display);
    }
    virtual ~LoadGanttChart();
    // ___________________________________________________
    virtual IlvPalette* loadPalette(IlUShort row,
				    IlInt load) const;
    void updateLoad(IlUShort row,
		    IlInt start,
		    IlInt end,
		    IlInt dload);
    void setZoomInteractor();
    virtual void drawGrid(IlvPort* dst,
			  IlUShort index,
			  IlBoolean skipCompute = IlFalse,
			  const IlvRegion* clip = 0,
			  IlvTransformer* t = 0,
			  IlvDirection d = 
			      (IlvDirection)(IlvHorizontal|IlvVertical));
    virtual void installAccelerators();
    virtual void insertLine(IlvGanttLine*,
			    IlUShort row,
			    IlBoolean redraw = IlTrue,
			    int layer = -1);
    virtual void addNode(IlvGanttNode*,
			 IlBoolean redraw = IlTrue,
			 int layer = 3);
    virtual IlBoolean removeLine(IlUShort row,
				 IlBoolean redraw = IlTrue,
				 IlBoolean destroyIt = IlTrue);
    virtual IlBoolean removeNode(IlvGanttNode*,
				 IlBoolean redraw = IlTrue,
				 IlBoolean destroyIt = IlTrue);
    virtual IlBoolean addSubNode(IlvGanttNode*,
				 IlvGanttSubNode*,
				 IlBoolean redraw = IlTrue,
				 int layer = 3);
    virtual IlBoolean removeSubNodes(IlvGanttNode*,
				     IlUShort* indexArray,
				     IlUShort num,
				     IlBoolean redraw = IlTrue,
				     IlBoolean destroyIt = IlTrue);
    virtual void setSubNodeValues(IlvGanttNode*,
				  IlUShort i,
				  IlInt startMin,
				  IlInt startMax,
				  IlInt endMin,
				  IlInt endMax,
				  IlvGanttLine*,
				  IlUShort capacity,
				  IlBoolean redraw = IlTrue);
    virtual void setNodeDrawMode(IlvGanttNode*,
				 IlvGanttNodeDrawMode,
				 IlBoolean redraw = IlTrue);
    virtual void rowResized(IlUShort row,
			    IlvPos dh) const;
    virtual IlBoolean moveLine(IlvGanttLine* line,
			       IlUShort row,
			       IlBoolean redraw = IlTrue);
    virtual IlBoolean swapLines(IlvGanttLine* line1,
				IlvGanttLine* line2,
				IlBoolean redraw = IlvTrue);
    DeclareTypeInfo();
    DeclareIOConstructors(LoadGanttChart);

protected:
    IlvPalette*     _optLoadPalette;
    IlvPalette*     _overLoadPalette;
    IlvPalette*     _underLoadPalette;
    LoadGanttInfo** _info;
    IlUShort        _loadAlloc;
    IlUShort        _gridThickness;
    IlvGanttLine*   _removedLine;
    void makeLoadPalettes(IlvDisplay*);
    void insertLoadRect(IlUShort row,
			IlUShort index,
			IlInt load,
			const IlvRect& rect);
    void removeLoadRect(IlUShort row,
			IlUShort index);
};

#endif /* !__loadgantt__header__*/
