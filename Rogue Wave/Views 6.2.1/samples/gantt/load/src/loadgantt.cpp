// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/load/src/loadgantt.cpp
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

#include <ilviews/grapher/grapher.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/filesel.h>
#include <ilviews/gadgets/iprompt.h>
#include <ilviews/gantt/ganttint.h>
#include <loadgantt.h>

#if defined(IL_STD)
#include <fstream>
#include <cstdio>
#include <cstdlib>
IL_STDUSE
#else
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
static void ILVCALLBACK
gtDeleteSelections(IlvManager*,
		   IlvView*,
		   IlvEvent&,
		   IlAny arg)
{
	((IlvGanttChart*)arg)->deleteSelections();
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
gtDeleteLine(IlvManager* mgr,
	     IlvView* view,
	     IlvEvent& event,
	     IlAny arg)
{
    IlvGanttChart* gantt = (IlvGanttChart*)arg;
    IlvPoint p(0, event.y());
    IlvTransformer* t = mgr->getTransformer(view);
    if (t)
      t->inverse(p);
    IlUShort row;
    if (gantt->yToRow(p.y(), row)) {
	IlvGanttLine* line = gantt->getLine(row);
	if (line) gantt->removeLine(row);
    }
}

// --------------------------------------------------------------------------
// Destroy callback
// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvView* top,
     IlAny)
{
    IlvDisplay* display = top->getDisplay();
    delete top;
    delete display;
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtCopy(IlvManager* mgr,
       IlvView*,
       IlvEvent&,
       IlAny arg)
{
    LoadGanttChart* gantt = (LoadGanttChart*)arg;
    LoadGanttChart* copy = (LoadGanttChart*)gantt->copy();
    copy->move(0, 0);
    IlvRect bbox;
    copy->boundingBox(bbox);
    IlvGadgetContainer* top = new IlvGadgetContainer(mgr->getDisplay(),
						     "Gantt Chart",
						     "Gantt Chart", bbox,
						     IlFalse, IlFalse);
    IlvSetAttachment(copy, IlvTop, IlvFixedAttach);
    IlvSetAttachment(copy, IlvBottom, IlvFixedAttach);
    IlvSetAttachment(copy, IlvLeft, IlvFixedAttach);
    IlvSetAttachment(copy, IlvRight, IlvFixedAttach);
    IlvSetAttachment(copy, IlvVertical, IlvElasticAttach);
    IlvSetAttachment(copy, IlvHorizontal, IlvElasticAttach);
    top->addObject(copy);
    top->setDestroyCallback(Quit, 0);
    top->show();
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtPSDump(IlvManager* mgr,
	 IlvView*,
	 IlvEvent&,
	 IlAny arg)
{
    IlvIFileSelector selector(mgr->getDisplay(), "/tmp", "*.ps");
    selector.setTitle("Dump Gantt chart");
    const char* filename = selector.get(IlTrue);
    ((IlvGanttChart*)arg)->psDump(filename);
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtSaveAll(IlvManager*,
	  IlvView* view,
	  IlvEvent&,
	  IlAny arg)
{
    LoadGanttChart* gantt = (LoadGanttChart*)arg;
    IlvIFileSelector selector(view->getDisplay(), "/tmp", "*.ilv");
    selector.setTitle("Save Gantt Objects");
    const char* filename = selector.get(IlTrue);
    if (filename) {
	ofstream stream(filename, IlvBinaryOutputStreamMode);
	if (!stream) {
	    IlvWarning("gtSaveAll: Bad file\n");
	    return;
	}
	IlvOutputFile os(stream);
	gantt->saveObjects(os);
    }
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtSetObjectName(IlvManager* mgr,
		IlvView* view,
		IlvEvent& event,
		IlAny arg)
{
    IlvPoint p(event.x(), event.y());
    IlvGraphic* graphic = mgr->lastContains(p, view);
    if (graphic) {
	IlvGanttChart* gantt = (IlvGanttChart*)arg;
	IlvGanttAbstractObject* object = gantt->getObject(graphic);
	if (object) {
	    char buffer[100];
	    const char* name = object->getName();
	    sprintf(buffer, "Name: %s", name ? name : "");
	    IlvIPromptString dialog(mgr->getDisplay(), buffer);
	    dialog.setTitle("Gantt object name");
	    dialog.setString(object->getName());
	    dialog.move(IlvPoint(event.gx(), event.gy()));
	    name = dialog.get(IlTrue);
	    if (name && *name && !gantt->setObjectName(object, name))
		IlvWarning("Not a valid object name");
	}
    }
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtAddLine(IlvManager* mgr,
	  IlvView* view,
	  IlvEvent& event,
	  IlAny arg)
{
    IlvGanttChart* gantt = (IlvGanttChart*)arg;
    char name[15];
    sprintf(name, "line%d", rand());
    IlvGanttLine* line = new IlvGanttLine(name, 1);
    gantt->addLine(line);
    IlvRect bbox;
    gantt->rowBBox((IlUShort)(gantt->rows() - 1), bbox);
    if (mgr->getTransformer(view))
	mgr->getTransformer(view)->apply(bbox);
    gantt->ensureVisible(mgr, view, IlvPoint(event.x(), bbox.bottom()));
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtMoveLine(IlvManager* mgr,
	   IlvView* view,
	   IlvEvent& event,
	   IlAny arg)
{
    IlvGanttChart* gantt = (IlvGanttChart*)arg;
    IlvPoint p(0, event.y());
    IlvTransformer* t = mgr->getTransformer(view);
    if (t)
	t->inverse(p);
    IlvUShort row;
    if (gantt->yToRow(p.y(), row)) {
	IlvGanttLine* line = gantt->getLine(row);
	if (line) {
	    IlvUShort toRow = (IlvUShort)(rand() % ( (IlInt)(gantt->rows())));
	    if (gantt->swapLines(line, gantt->getLine(toRow)))
		IlvPrint("Line located at row %hu is moved to row %hu",
			 row, toRow);
	}
    }
}

// -------------------------------------------------------------------------
static void ILVCALLBACK
gtSwapGrid(IlvManager*,
	   IlvView*,
	   IlvEvent&,
	   IlAny arg)
{
    IlvGanttChart* gantt = (IlvGanttChart*)arg;
    gantt->showGrid(!gantt->isShowingGrid());
}

// -------------------------------------------------------------------------
// Works only if links are managed in layer 2
static void ILVCALLBACK
gtSwapLink(IlvManager* mgr,
	   IlvView* view,
	   IlvEvent&,
	   IlAny)
{
    IlvBoolean visible = (IlvBoolean)!(mgr->isVisible(view, 2));
    mgr->setVisible(view, 2, visible);
    mgr->draw(view, IlTrue);
}

// -------------------------------------------------------------------------
LoadGanttInfo::LoadGanttInfo(IlInt load,
			     const IlvRect& rect)
{
    _count = 1;
    _alloc = 50;
    _loads = new IlInt[_alloc];
    _rects = new IlvRect[_alloc];
    for (IlUShort i = 0; i < 4; ++i) {
	_fromIndex[i] = 0;
	_toIndex[i] = 0;
    }
    _loads[0] = load;
    _rects[0] = rect;
}

// -------------------------------------------------------------------------
LoadGanttInfo::~LoadGanttInfo()
{
    delete [] _loads;
    delete [] _rects;
}

// --------------------------------------------------------------------------
LoadGanttChart::LoadGanttChart(IlvInputFile& is,
			       IlvPalette* palette)
    : IlvGanttChart(is, palette)
{
    is.getStream() >> _gridThickness;
    makeLoadPalettes(palette->getDisplay());
}

// --------------------------------------------------------------------------
LoadGanttChart::LoadGanttChart(const LoadGanttChart& source)
    : IlvGanttChart(source),
      _gridThickness(source._gridThickness)
{
    makeLoadPalettes(getDisplay());
}

// -------------------------------------------------------------------------
LoadGanttChart::~LoadGanttChart()
{
    for (IlUShort i = 0; i < _lcount; ++i)
	delete _info[i];
    delete [] _info;
    _optLoadPalette->unLock();
    _overLoadPalette->unLock();
    _underLoadPalette->unLock();
    if (!_view)
	return;
    IlvManagerViewInteractor* inter;
    for (IlUShort vi = 0; vi < 2; ++vi) {
	inter = _manager->getInteractor(_mgrview[vi]);
	if (inter) {
	    _manager->removeInteractor(_mgrview[vi]);
	    delete inter;
	}
	for (IlUShort hi = 0; hi < 2; ++hi) {
	    inter = _grapher->getInteractor(_gphview[2 * vi + hi]);
	    if (inter) {
		_grapher->removeInteractor(_gphview[2 * vi + hi]);
		delete inter;
	    }
	}
    }
}

// -------------------------------------------------------------------------
void
LoadGanttChart::makeLoadPalettes(IlvDisplay* display)
{
    _loadAlloc = 100;
    _info = new LoadGanttInfo*[_loadAlloc];
    _removedLine = 0;
    IlvColor* blue  = display->getColor("orange");
    IlvColor* red   = display->getColor("orangered");
    IlvColor* green = display->getColor("darkseagreen2");
    _optLoadPalette =
	display->getPalette(_palette->getBackground(),
			    blue ? blue : _palette->getForeground());
    _overLoadPalette =
	display->getPalette(_palette->getBackground(),
			    red ? red : _palette->getForeground());
    _underLoadPalette =
	display->getPalette(_palette->getBackground(),
			    green ? green : _palette->getForeground());
    _optLoadPalette->lock();
    _overLoadPalette->lock();
    _underLoadPalette->lock();
}

// --------------------------------------------------------------------------
IlvPalette*
LoadGanttChart::loadPalette(IlUShort /* row */,
			    IlInt load) const
{
    return ((load == 0) ? _optLoadPalette :
	    ((load < 0) ? _overLoadPalette : _underLoadPalette));
}

// --------------------------------------------------------------------------
void
LoadGanttChart::insertLoadRect(IlUShort row,
			       IlUShort index,
			       IlInt load,
			       const IlvRect& rect)
{
    if (++_info[row]->_count == _info[row]->_alloc) {
	_info[row]->_alloc += (IlUShort)50;
	IlInt*   newLoads = new IlInt[_info[row]->_alloc];
	IlvRect*  newRects = new IlvRect[_info[row]->_alloc];
	for (IlUShort i = 0; i < IlUShort(_info[row]->_count - 1UL); ++i) {
	    newLoads[i] = _info[row]->_loads[i];
	    newRects[i] = _info[row]->_rects[i];
	}
	delete [] _info[row]->_loads;
	delete [] _info[row]->_rects;
	_info[row]->_loads = newLoads;
	_info[row]->_rects = newRects;
    }
    for (IlUShort i = (IlUShort)(_info[row]->_count - 1); i > index; --i) {
	_info[row]->_loads[i] = _info[row]->_loads[i - 1];
	_info[row]->_rects[i] = _info[row]->_rects[i - 1];
    }
    _info[row]->_loads[index] = load;
    _info[row]->_rects[index] = rect;
}

// --------------------------------------------------------------------------
void
LoadGanttChart::removeLoadRect(IlUShort row,
			       IlUShort index)
{
    --(_info[row]->_count);
    for (IlUShort i = index; i < _info[row]->_count; ++i) {
	_info[row]->_loads[i] = _info[row]->_loads[i + 1];
	_info[row]->_rects[i] = _info[row]->_rects[i + 1];
    }
}

// --------------------------------------------------------------------------
void
LoadGanttChart::updateLoad(IlUShort row,
			   IlInt start,
			   IlInt end,
			   IlInt deltaLoad)
{
    if (!deltaLoad || start >= end || start < _start || end > _end)
	return;
    IlUShort from, to;
    IlUShort i;
    for (i = 0; i < _info[row]->_count; ++i)
	if (_info[row]->_rects[i].right() > start)
	    break;
    for (from = i; i < _info[row]->_count; ++i)
	if (_info[row]->_rects[i].right() >= end)
	    break;
    for (to = i, i = from + 1; i < to; ++i)
	_info[row]->_loads[i] += deltaLoad;
    if (from == to) {
	if (end < _info[row]->_rects[to].right()) {
	    if (start > _info[row]->_rects[to].x() ||
		!((to > 0) && (_info[row]->_loads[to-1] ==
			       _info[row]->_loads[to] + deltaLoad))) {
		insertLoadRect(row, to + 1, _info[row]->_loads[to],
			       IlvRect(end, _info[row]->_rects[to].y(),(IlvDim)
				       (_info[row]->_rects[to].right() - end),
				       _info[row]->_rects[to].h()));
		_info[row]->_rects[to].w((IlvDim)(end - start));
	    } else {
		_info[row]->_rects[to].w((IlvDim)
					 (_info[row]->_rects[to].right()
					  - end));
		_info[row]->_rects[to].x(end);
		_info[row]->_rects[to - 1].w((IlvDim)
					   (end 
					    - _info[row]->_rects[to - 1].x()));
		_info[row]->_loads[to] -= deltaLoad;
	    }
	}
	_info[row]->_loads[to] += deltaLoad;
	if (start > _info[row]->_rects[to].x()) {
	    IlvPos x = _info[row]->_rects[to].x();
	    _info[row]->_rects[to].x(start);
	    _info[row]->_rects[to].w((IlvDim)(end - start));
	    insertLoadRect(row, to, _info[row]->_loads[to] - deltaLoad,
			   IlvRect(x, _info[row]->_rects[to].y(),
				   (IlvDim)(start - x),
				   _info[row]->_rects[to].h()));
	}
    } else {
	if (end < _info[row]->_rects[to].right()) {
	    insertLoadRect(row, to + 1, _info[row]->_loads[to],
			   IlvRect(end, _info[row]->_rects[to].y(), (IlvDim)
				   (_info[row]->_rects[to].right() - end),
				   _info[row]->_rects[to].h()));
	    _info[row]->_rects[to].w((IlvDim)
				     (end - _info[row]->_rects[to].x()));
	} else
	  if ((to + 1 < _info[row]->_count) &&
	      (_info[row]->_loads[to] + deltaLoad
	       == _info[row]->_loads[to + 1])) {
	    IlvPos right = _info[row]->_rects[to + 1].right();
	    removeLoadRect(row, to + 1);
	    _info[row]->_rects[to].w((IlvDim)(right -
					      _info[row]->_rects[to].x()));
	    }
	_info[row]->_loads[to] += deltaLoad;
	if (start > _info[row]->_rects[from].x()) {
	    insertLoadRect(row, from + 1,
			   _info[row]->_loads[from] + deltaLoad,
			   IlvRect(start, _info[row]->_rects[from].y(),(IlvDim)
				   (_info[row]->_rects[from].right() - start),
				   _info[row]->_rects[from].h()));
	    _info[row]->_rects[from].w((IlvDim)(start -
						_info[row]->_rects[from].x()));
	} else {
	    _info[row]->_loads[from] += deltaLoad;
	    if ((from > 0) &&
		(_info[row]->_loads[from] == _info[row]->_loads[from - 1])) {
		IlvPos right = _info[row]->_rects[from].right();
		removeLoadRect(row, from);
		_info[row]->_rects[from - 1].w((IlvDim)
					       (right -
						_info[row]->_rects[from - 1].x()));
	    }
	}
    }
}

// -------------------------------------------------------------------------
void
LoadGanttChart::insertLine(IlvGanttLine* line,
			   IlUShort row,
			   IlBoolean redraw,
			   int layer)
{
    if (redraw)
	_grapher->initReDraws();
    IlvGanttChart::insertLine(line, row, redraw, layer);
    row = getLineRow(line); // row may be modified by insertLine
    if (_lcount == _loadAlloc) {
	_loadAlloc += (IlUShort)100;
	LoadGanttInfo** newInfo = new LoadGanttInfo*[_loadAlloc];
	for (IlUShort i = 0; i < IlUShort(_lcount - 1UL); ++i)
	    newInfo[i] = _info[i];
	delete [] _info;
	_info = newInfo;
    }
    IlvPos dy = _lpos[row + 1]-_lpos[row];
    for (IlUShort i = IlUShort(_lcount - 1UL); i > row; --i) {
	_info[i] = _info[i - 1];
	for (IlUShort j = 0; j < _info[i]->_count; ++j)
	    _info[i]->_rects[j].translate(0, dy);
    }
    IlvRect rect(_start, _lpos[row], (IlvDim)(_end - _start), _gridThickness);
    _info[row] = new LoadGanttInfo(line->getCapacity(), rect);
    if (redraw)
	_grapher->reDrawViews();
}

// --------------------------------------------------------------------------
IlBoolean
LoadGanttChart::removeLine(IlUShort row,
			   IlBoolean redraw,
			   IlBoolean destroyIt)
{
    if (redraw)
	_grapher->initReDraws();
    IlvPos dy = _lpos[row] - _lpos[row + 1];
    _removedLine = _lines[row];
    IlvBoolean isRemoved = IlvGanttChart::removeLine(row, redraw, destroyIt);
    _removedLine = 0;
    if (isRemoved) {
	delete _info[row];
	for (IlUShort i = row; i < _lcount; ++i) {
	    _info[i] = _info[i + 1];
	    for (IlUShort j = 0; j < _info[i]->_count; ++j)
		_info[i]->_rects[j].translate(0, dy);
	}
    }
    if (redraw)
	_grapher->reDrawViews();
    return isRemoved;
}

// -------------------------------------------------------------------------
IlBoolean
LoadGanttChart::moveLine(IlvGanttLine* line,
			 IlUShort row,
			 IlBoolean redraw)
{
    IlUShort oldrow = getLineRow(line);
    if (redraw)
	_grapher->initReDraws();
    IlBoolean isMoved = IlvGanttChart::moveLine(line, row, redraw);
    if (isMoved) {
	IlvPos dy, rowH = (IlvPos)(_lpos[row + 1] - _lpos[row]);
	IlUShort i, j;
	LoadGanttInfo* info = _info[oldrow];
	if (row > oldrow) {
	    dy = (IlvPos)_lpos[row] - (IlvPos)_lpos[oldrow];
	    for (i = oldrow; i < row; ++i) {
		_info[i] = _info[i + 1];
		for (j = 0; j < _info[i]->_count; ++j)
		    _info[i]->_rects[j].translate(0, -rowH);
	    }
	} else {
	    dy = (IlvPos)_lpos[row + 1] - (IlvPos)_lpos[oldrow + 1];
	    for (i = oldrow; i > row; --i) {
		_info[i] = _info[i - 1];
		for (j = 0; j < _info[i]->_count; ++j)
		    _info[i]->_rects[j].translate(0, rowH);
	    }
	}
	_info[row] = info;
	for (j = 0; j < _info[row]->_count; ++j)
	    _info[row]->_rects[j].translate(0, dy);
    }
    if (redraw)
	_grapher->reDrawViews();
    return isMoved;
}

// -------------------------------------------------------------------------
IlBoolean
LoadGanttChart::swapLines(IlvGanttLine* line1,
			  IlvGanttLine* line2,
			  IlBoolean redraw)
{
    if (redraw)
	_grapher->initReDraws();
    IlvBoolean areSwapped = IlvGanttChart::swapLines(line1, line2, redraw);
    if (areSwapped) {
	IlUShort row1 = getLineRow(line1),
	    row2 = getLineRow(line2);
	if (row1 > row2) { //  row1 < row2
	    IlUShort tmp = row1;
	    row1 = row2;
	    row2 = tmp;
	}
	IlvDim rowH1 = (IlvDim)(_lpos[row1 + 1] - _lpos[row1]),
	    rowH2 = (IlvDim)(_lpos[row2 + 1] - _lpos[row2]);
	LoadGanttInfo* info1 = _info[row1];
	_info[row1] = _info[row2];
	_info[row2] = info1;
	IlvPos dy = (IlvPos)(_lpos[row2] - _lpos[row1]);
	IlUShort j;
	for (j = 0; j < _info[row2]->_count; ++j)
	    _info[row2]->_rects[j].translate(0, dy);
	if (rowH1 != rowH2) {
	  IlvPos delta = (IlvPos)(rowH2 - rowH1);
	    dy += delta;
	    for (IlUShort row = row1 + 1; row < row2; ++row)
		for (IlUShort i = 0; i < _info[row]->_count; ++i)
		    _info[row]->_rects[i].translate(0, -delta);
	}
	for (j = 0; j < _info[row1]->_count; ++j)
	    _info[row1]->_rects[j].translate(0, -dy);
	IlvRect rect(_start, _lpos[row1],
		     (IlvDim)(_end - _start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
	rect.y(_lpos[row2]);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    if (redraw)
	_grapher->reDrawViews();
    return areSwapped;
}

// --------------------------------------------------------------------------
void
LoadGanttChart::rowResized(IlUShort row,
			   IlvPos dh) const
{
    for (IlUShort i = row + 1; i < _lcount; ++i)
	for (IlUShort j = 0; j < _info[i]->_count; ++j)
	    _info[i]->_rects[j].translate(0, dh);
}

// --------------------------------------------------------------------------
void
LoadGanttChart::addNode(IlvGanttNode* node,
			IlBoolean redraw, int layer)
{
    if (redraw)
	_grapher->initReDraws();
    IlvGanttChart::addNode(node, redraw, layer);
    IlvGanttSubNode* subNode;
    IlInt start, end;
    IlvRect rect;
    IlUShort row;
    for (IlUShort i = 0; i < node->getCardinal(); ++i) {
	subNode = node->getSubNode(i);
	if (subNode->getGraphic()) {
	    getSubNodeDrawnStartEnd(node, i, start, end);
	    row = getLineRow(subNode->getLine());
	    updateLoad(row, start, end, -(IlInt)subNode->getCapacity());
	    rect.moveResize(start, _lpos[row],
			    (IlvDim)(end - start), _gridThickness);
	    if (redraw)
		_grapher->invalidateRegion(rect);
	}
    }
    if (redraw)
	_grapher->reDrawViews();
}

// --------------------------------------------------------------------------
IlvBoolean
LoadGanttChart::removeNode(IlvGanttNode* node,
			   IlBoolean redraw,
			   IlBoolean destroyIt)
{
    IlvGanttSubNode* subNode;
    IlUShort count = node->getCardinal();
    IlInt*    starts = new IlvInt[count];
    IlInt*    ends   = new IlvInt[count];
    IlUShort* rows   = new IlvUShort[count];
    IlUShort* capacities = new IlvUShort[count];
    IlUShort realCount;
    IlUShort i;
    for (realCount = 0, i = 0; i < count; ++i) {
	subNode = node->getSubNode(i);
	if (subNode->getGraphic() && _removedLine != subNode->getLine()) {
	    getSubNodeDrawnStartEnd(node, i,
				    starts[realCount], ends[realCount]);
	    rows[realCount] = getLineRow(subNode->getLine());
	    capacities[realCount++] = subNode->getCapacity();
	}
    }
    if (redraw)
	_grapher->initReDraws();
    IlBoolean isRemoved = IlvGanttChart::removeNode(node, redraw, destroyIt);
    if (isRemoved) {
	IlvRect rect;
	for (i = 0; i < realCount; ++i) {
	    updateLoad(rows[i], starts[i], ends[i], capacities[i]);
	    rect.moveResize(starts[i], _lpos[rows[i]],
			    (IlvDim)(ends[i] - starts[i]), _gridThickness);
	    if (redraw)
		_grapher->invalidateRegion(rect);
	}
    }
    if (redraw)
	_grapher->reDrawViews();
    delete [] starts;
    delete [] ends;
    delete [] capacities;
    delete [] rows;
    return isRemoved;
}

// --------------------------------------------------------------------------
IlBoolean
LoadGanttChart::addSubNode(IlvGanttNode* node,
			   IlvGanttSubNode* subNode,
			   IlBoolean redraw,
			   int layer)
{
    if (redraw)
	_grapher->initReDraws();
    IlBoolean isAdded =
	IlvGanttChart::addSubNode(node, subNode, redraw, layer);
    if (isAdded && subNode->getGraphic()) {
	IlInt start, end;
	IlUShort row = getLineRow(subNode->getLine());
	getSubNodeDrawnStartEnd(node, (IlUShort)(node->getCardinal() - 1),
				start, end);
	updateLoad(row, start, end, -(IlInt)subNode->getCapacity());
	IlvRect rect(start, _lpos[row], (IlvDim)(end - start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    if (redraw)
	_grapher->reDrawViews();
    return isAdded;
}

// --------------------------------------------------------------------------
IlBoolean
LoadGanttChart::removeSubNodes(IlvGanttNode* node,
			       IlUShort* indexArray,
			       IlUShort rmCount,
			       IlBoolean redraw,
			       IlBoolean destroyIt)
{
    if (rmCount == 0)
	return IlFalse;
    IlvGanttSubNode* subNode;
    IlInt*    starts = new IlInt[rmCount];
    IlInt*    ends   = new IlInt[rmCount];
    IlUShort* rows   = new IlUShort[rmCount];
    IlUShort* capacities = new IlUShort[rmCount];
    IlUShort realCount;
    IlUShort i;
    for (realCount = 0, i = 0; i < rmCount; ++i) {
	subNode = node->getSubNode(indexArray[i]);
	if (subNode->getGraphic() && _removedLine != subNode->getLine()) {
	    getSubNodeDrawnStartEnd(node, indexArray[i],
				    starts[realCount], ends[realCount]);
	    rows[realCount] = getLineRow(subNode->getLine());
	    capacities[realCount++] = subNode->getCapacity();
	}
    }
    if (redraw)
	_grapher->initReDraws();
    IlBoolean isRemoved =
	IlvGanttChart::removeSubNodes(node, indexArray,
				      rmCount, redraw, destroyIt);
    if (isRemoved) {
	IlvRect rect;
	for (i = 0; i < realCount; ++i) {
	    updateLoad(rows[i], starts[i], ends[i], capacities[i]);
	    rect.moveResize(starts[i], _lpos[rows[i]],
			    (IlvDim)(ends[i] - starts[i]), _gridThickness);
	    if (redraw)
		_grapher->invalidateRegion(rect);
	}
    }
    if (redraw)
	_grapher->reDrawViews();
    delete [] starts;
    delete [] ends;
    delete [] capacities;
    delete [] rows;
    return isRemoved;
}

// -------------------------------------------------------------------------
void
LoadGanttChart::setSubNodeValues(IlvGanttNode* node,
				 IlUShort i,
				 IlInt startMin,
				 IlInt startMax,
				 IlInt endMin,
				 IlInt endMax,
				 IlvGanttLine* line,
				 IlUShort capacity,
				 IlBoolean redraw)
{
    IlvGanttSubNode* subNode = node->getSubNode(i);
    if (redraw)
	_grapher->initReDraws();
    IlvRect rect;
    IlInt start, end;
    if (subNode->getGraphic()) {
	IlvGanttLine* oldLine = subNode->getLine();
	IlUShort oldRow = getLineRow(oldLine);
	IlUShort oldCapacity = subNode->getCapacity();
	getSubNodeDrawnStartEnd(node, i, start, end);
	updateLoad(oldRow, start, end, oldCapacity);
	rect.moveResize(start, _lpos[oldRow],
			(IlvDim)(end - start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    IlvGanttChart::setSubNodeValues(node, i, startMin, startMax,
				    endMin, endMax, line, capacity, redraw);
    if (subNode->getGraphic()) {
	getSubNodeDrawnStartEnd(node, i, start, end);
	IlUShort row = getLineRow(line);
	updateLoad(row, start, end, -(IlInt)capacity);
	rect.moveResize(start, _lpos[row],
			(IlvDim)(end - start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    _grapher->reDrawViews();
}

// --------------------------------------------------------------------------
void
LoadGanttChart::setNodeDrawMode(IlvGanttNode* node,
				IlvGanttNodeDrawMode mode,
				IlBoolean redraw)
{
    if (node->getDrawMode() == mode)
	return;
    IlvGanttSubNode* subNode;
    IlInt start, end;
    IlUShort row;
    IlvRect rect;
    if (redraw)
	_grapher->initReDraws();
    IlUShort i;
    for (i = 0; i < node->getCardinal(); ++i) {
	subNode = node->getSubNode(i);
	if (!subNode->getGraphic())
	    continue;
	getSubNodeDrawnStartEnd(node, i, start, end);
	row = getLineRow(subNode->getLine());
	updateLoad(row, start, end, subNode->getCapacity());
	rect.moveResize(start, _lpos[row],
			(IlvDim)(end - start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    IlvGanttChart::setNodeDrawMode(node, mode, redraw);
    for (i = 0; i < node->getCardinal(); ++i) {
	subNode = node->getSubNode(i);
	if (!subNode->getGraphic())
	    continue;
	getSubNodeDrawnStartEnd(node, i, start, end);
	row = getLineRow(subNode->getLine());
	updateLoad(row, start, end, -(IlvInt)subNode->getCapacity());
	rect.moveResize(start, _lpos[row],
			(IlvDim)(end - start), _gridThickness);
	if (redraw)
	    _grapher->invalidateRegion(rect);
    }
    if (redraw)
	_grapher->reDrawViews();
}

// -------------------------------------------------------------------------
void
LoadGanttChart::drawGrid(IlvPort* dst,
			 IlUShort ix,
			 IlBoolean skipCompute,
			 const IlvRegion* clip,
			 IlvTransformer*,
			 IlvDirection)
{
    if (!_showGrid || !_view)
	return;
    if (!skipCompute)
	computeGridPoints(ix);
    IlvUShort numXPoints = _numXPoints[ix],
      numYPoints = _numYPoints[ix];
    if (!numXPoints || !numYPoints)
	return;
    IlUShort fvRow = firstVisibleRow(ix / 2);
    IlUShort lvRow = lastVisibleRow(ix / 2);
    IlUShort visibleRows = IlvMin((IlUShort)(lvRow + 2), _lcount);
    if (!skipCompute) {
	IlvInt start = _shownStart[ix % 2],
	  end = _shownEnd[ix % 2];
	for (IlUShort row = fvRow; row < visibleRows; ++row) {
	    IlUShort j;
	    for (j = 0; j < _info[row]->_count; ++j)
		if (_info[row]->_rects[j].right() > start)
		    break;
	    _info[row]->_fromIndex[ix] = j;
	    for ( ; j < _info[row]->_count; ++j)
		if (_info[row]->_rects[j].right() >= end)
		    break;
	    _info[row]->_toIndex[ix] = j;
	}
    }
    IlvPushClip palettePushClip(*getGridPalette(), clip);
    IlvPushClip optLoadPalettePushClip(*_optLoadPalette, clip);
    IlvPushClip overLoadPalettePushClip(*_overLoadPalette, clip);
    IlvPushClip underLoadPalettePushClip(*_underLoadPalette, clip);
    
    IlvPoint* xpoints = _gridXPoints[ix],
        * ypoints = _gridYPoints[ix];
    IlvPos xend = xpoints[numXPoints - 1].x(),
        yend = ypoints[numYPoints - 1].y();
    IlUShort i;
    for (i = 0; i < numXPoints; ++i)
	dst->drawLine(getGridPalette(), xpoints[i],
		      IlvPoint(xpoints[i].x(), yend));
    IlvDim w, h;
    _gphview[ix]->size(w, h);
    IlvRect rect, viewRect(0, 0, w, h);
    IlvTransformer* t = _grapher->getTransformer(_gphview[ix]);
    for (IlvUShort row = fvRow; row < visibleRows; ++row)
	for (i = _info[row]->_fromIndex[ix];
	     i <= _info[row]->_toIndex[ix]; ++i) {
	    rect = _info[row]->_rects[i];
	    if (t)
		t->apply(rect);
	    if (rect.h() == 0)
		rect.h(1);
	    rect.intersection(viewRect);
	    dst->fillRectangle(loadPalette(row, _info[row]->_loads[i]), rect);
	}
    dst->drawLine(getGridPalette(),
		  ypoints[numYPoints - 1],
		  IlvPoint(xend, ypoints[numYPoints - 1].y()));
}

// -------------------------------------------------------------------------
void
LoadGanttChart::installAccelerators()
{
    IlvGanttChart::installAccelerators();
#define addAcc(f,t,k,m,a) _grapher->addAccelerator(f,t,k,m,a)
    addAcc(gtSwapGrid,         IlvKeyDown, 'G', 0, this);
    addAcc(gtSwapLink,         IlvKeyDown, 'L', 0, this);
    addAcc(gtDeleteSelections, IlvKeyDown, IlvDeleteKey, 0, this);
#undef addAcc
#define addAcc(f,t,k,m,a)  _grapher->addAccelerator(f,t,k,m,a),  _manager->addAccelerator(f,t,k,m,a)
    addAcc(gtAddLine,          IlvKeyDown,     'R', 0, this);
    addAcc(gtDeleteLine,       IlvKeyDown,     'K', 0, this);
    addAcc(gtSetObjectName,    IlvDoubleClick, IlvLeftButton, 0, this);
    addAcc(gtSaveAll,          IlvKeyDown,     'S', 0, this);
    addAcc(gtCopy,             IlvKeyDown,     'D', 0, this);
    addAcc(gtPSDump,           IlvKeyDown,     'P', 0, this);
    addAcc(gtMoveLine,         IlvKeyDown,     'M', 0, this);
#undef addAcc
}

// --------------------------------------------------------------------------
void
LoadGanttChart::setZoomInteractor()
{
    if (!getGadgetContainer())
	return;
    IlvGanttZoomInteractor* zoomInter;
    for (IlUShort i = 0; i < 2; ++i) {
	zoomInter = new IlvGanttZoomInteractor(this, _manager, _mgrview[i]);
	_manager->setInteractor(zoomInter);
    }
}

IlvPredefinedIOMembers(LoadGanttChart)
// --------------------------------------------------------------------------
void
LoadGanttChart::write(IlvOutputFile& os) const
{
    IlvGanttChart::write(os);
    os.getStream() << IlvSpc() << _gridThickness;
}

// --------------------------------------------------------------------------
#if defined(linux) || defined(__TCPLUSPLUS__)
IlvPreRegisterClass(LoadGanttChart);
static int initLoadGanttChart()
{ IlvPostRegisterClass(LoadGanttChart, IlvGanttChart); return 0; }
static int _initLoadGanttChart = initLoadGanttChart();
#else  /* !linux && !defined(__TCPLUSPLUS__) */
IlvRegisterClass(LoadGanttChart, IlvGanttChart);
#endif /* !linux && !defined(__TCPLUSPLUS__)*/
