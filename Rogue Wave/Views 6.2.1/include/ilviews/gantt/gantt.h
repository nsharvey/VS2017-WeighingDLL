// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gantt/gantt.h
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
// Declaration of the Gantt Chart related classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Gantt_Gantt_H
#define __Ilv_Gantt_Gantt_H

#include <stdarg.h>
#include <ilviews/base/value.h>
#include <ilviews/manager/manager.h>
#include <ilviews/grapher/grapher.h>
#include <ilviews/grapher/links.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/scrollb.h>
#include <ilviews/graphics/scale.h>

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvgantt.lib")
#endif

#if defined(ILVGTLIB)
#define ILVGTEXPORTED IL_BASEEXPORTED
#define ILVGTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#define ILVGTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVGTLIB */
#define ILVGTEXPORTED IL_BASEIMPORTED
#define ILVGTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#define ILVGTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVGTLIB */

// Static initialization macros
#define ILVGTMODULEINIT(m) IL_MODULEINIT(m, ILVGTEXPORTED)
#define ILVGTMODULETERM(m) IL_MODULETERM(m, ILVGTEXPORTED)

#define ILVGANTTMODULEINIT(m) IL_MODULEINIT(g4##m, ILVGTEXPORTED)
#define ILVGANTTMODULETERM(m) IL_MODULETERM(g4##m, ILVGTEXPORTED)

class IlvGanttAbstractObject;
class IlvGanttChart;
class IlvGanttNode;
class IlvGanttSubNode;

typedef enum IlvGanttObjectType {
    IlvGanttIsLine,
    IlvGanttIsNode,
    IlvGanttIsLink
} _IlvGanttObjectType;

typedef enum IlvGanttLinkType {
    IlvStartsAfterEnd,
    IlvStartsAfterStart,
    IlvEndsAfterStart,
    IlvEndsAfterEnd,
    IlvStartsAtEnd,
    IlvStartsAtStart,
    IlvEndsAtStart,
    IlvEndsAtEnd
} _IlvGanttLinkType;

typedef enum IlvGanttNodeDrawMode {
    IlvGanttNodeDrawMin,
    IlvGanttNodeDrawMax,
    IlvGanttNodeDrawComplete,
    IlvGanttNodeDrawDefault
}  _IlvGanttNodeDrawMode;

typedef void (* IlvGanttSetGraphicName)(IlvGanttAbstractObject*,
					IlvGraphic*,
					IlvGanttObjectType, IlAny);

IL_DEFINEFPTRTOANYCAST(IlvGanttSetGraphicName);

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttAbstractObject
    : public IlvValueInterface
{
public:
    IlvGanttAbstractObject(const char* name    = 0,
			   IlBoolean   copy    = IlTrue,
			   IlvGraphic* graphic = 0)
	: _graphic(graphic),
	  _name(0),
	  _clientData(0)
    {
	setName(name, copy);
    }
    virtual ~IlvGanttAbstractObject();
    virtual void	setGraphic(IlvGraphic* graphic,
				   IlBoolean destroyOld = IlTrue,
				   IlBoolean redraw = IlTrue);
    inline IlvGraphic*	getGraphic() const  { return _graphic; }
    void		setName(const char* name, IlBoolean copy = IlTrue);
    inline const char*	getName() const { return _name; }
    inline void		setClientData(IlAny data) { _clientData = data; }
    inline IlAny	getClientData() const { return _clientData; }

    // --- value accessors ---
    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlBoolean	beforeChangeValues(const IlvValue* =0, IlUShort = 0);
    virtual void	afterChangeValues(const IlvValue* =0, IlUShort = 0);

    IlvDeclareLazyClassInfo();

    static IlSymbol*	_graphicValue;

protected:
    IlvGraphic*		_graphic;
    char*		_name;
    IlAny		_clientData;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttLine
    : public IlvGanttAbstractObject
{
public:
    IlvGanttLine(const char* name,
		 IlUShort capacity = 1,
		 IlBoolean copy = IlTrue,
		 IlvGraphic* graphic = 0)
	: IlvGanttAbstractObject(name, copy, graphic),
	  _capacity(capacity)
    {}
    ~IlvGanttLine();

    inline IlUShort	getCapacity() const { return _capacity; }
    inline void		setCapacity(IlUShort capacity) 
	{ _capacity = capacity; }
    inline IlUInt	subNodeCount() const
	{ return _subNodes.length(); }
    void		assignSubNode(IlvGanttSubNode* subNode);
    void		removeSubNode(IlvGanttSubNode* subNode);

    // --- value accessors ---
    DeclareViewAccessors();
    IlvDeclareLazyClassInfo();

    static IlSymbol*	_capacityValue;

protected:
    IlUShort		_capacity;
    IlList		_subNodes;
};

// --------------------------------------------------------------------------
#define ILVGANTT_NOTHING  0L
#define ILVGANTT_STARTMIN 1L
#define ILVGANTT_STARTMAX 2L
#define ILVGANTT_ENDMIN   4L
#define ILVGANTT_ENDMAX   8L
#define ILVGANTT_STARTEND (1L + 2L + 4L + 8L)
#define ILVGANTT_LINE    16L

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttSubNode
    : public IlvGanttAbstractObject
{
public:
    IlvGanttSubNode(IlInt		startMin = 0,
		    IlInt		startMax = 0,
		    IlInt		endMin = 0,
		    IlInt		endMax = 0,
		    IlvGanttLine*	line = 0,
		    IlUShort		capacity = 1,
		    IlvGraphic*		graphic = 0,
		    IlBoolean		asBreak = IlFalse);

    IlvGanttSubNode(IlvGanttSubNode*	srcSubNode);
    ~IlvGanttSubNode();

    inline IlInt	getStartMin() const { return _startMin; }
    inline IlInt	getStartMax() const { return _startMax; }
    inline IlInt	getEndMin() const { return _endMin; }
    inline IlInt	getEndMax() const { return _endMax; }
    IlBoolean		setValues(IlInt startMin,
				  IlInt startMax,
				  IlInt endMin,
				  IlInt endMax);
    IlBoolean		setStartMin(IlInt startMin);
    IlBoolean		setStartMax(IlInt startMax);
    IlBoolean		setEndMin(IlInt endMin);
    IlBoolean		setEndMax(IlInt endMax);

    virtual void	setGraphic(IlvGraphic*,
				   IlBoolean destroyOld = IlTrue,
				   IlBoolean redraw = IlTrue);
    void		refresh(IlBoolean redraw = IlTrue);
    inline
    IlvGanttLine*	getLine() const { return _line; }
    IlvGanttNode*	getNode() const;
    IlUShort		getIndex() const;
    IlvGanttChart*	getGantt() const;
    void		setLine(IlvGanttLine* line);
    inline IlUShort	getCapacity() const { return _capacity; }
    inline void		setCapacity(IlUShort capacity) 
	{ _capacity = capacity; }
    inline void		setAsBreak(IlBoolean asBreak = IlTrue)
	{ _isBreak = asBreak; }
    inline IlBoolean	isBreak() const { return _isBreak; }
    inline void		setLock(IlInt lock) { _lock  = lock; }
    inline void		addLock(IlInt lock) { _lock |= lock; }
    inline void		removeLock(IlInt lock) { _lock ^= lock; }
    inline IlInt	getLock() const { return _lock;}
    static IlBoolean	valuesAreValid(IlInt startMin,
				       IlInt startMax,
				       IlInt endMin,
				       IlInt endMax);
    IlBoolean		valuesAreValid();
    IlInt		whichValuesAreLocked(IlInt startMin,
					     IlInt startMax,
					     IlInt endMin,
					     IlInt endMax,
					     IlvGanttLine* line);
    IlInt		whichValuesAreLocked(IlvGanttSubNode* subNode);
    IlBoolean		applyToValues(IlvTransformer* t,
				      IlvGanttNodeDrawMode drawMode);
    IlBoolean		setDrawnStartEnd(IlInt start,
					 IlInt end,
					 IlvDirection side,
					 IlvGanttNodeDrawMode drawMode);
    void		getDrawnStartEnd(IlInt& start,
					 IlInt& end,
					 IlvGanttNodeDrawMode drawMode) const;
    IlInt		getDrawnSpan(IlvGanttNodeDrawMode drawMode) const;
    IlInt		getSmallestDrawnSpan() const;
    inline IlBoolean	getModified() const { return _modified; }
    inline void		setModified(IlBoolean modified = IlTrue)
	{ _modified = modified; }

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_startMinValue;
    static IlSymbol*	_startMaxValue;
    static IlSymbol*	_endMinValue;
    static IlSymbol*	_endMaxValue;
    static IlSymbol*	_lineValue;
    static IlSymbol*	_nodeValue;
    static IlSymbol*	_capacityValue;
    static IlSymbol*	_isBreakValue;
    static IlSymbol*	_lockValue;
    static IlSymbol*	_modifiedValue;
    static IlSymbol*	_setValuesMethod;

    IlvDeclareLazyClassInfo();

protected:
    IlInt		_startMin;
    IlInt		_startMax;
    IlInt		_endMin;
    IlInt		_endMax;
    IlvGanttLine*	_line;
    IlUShort		_capacity;
    IlBoolean		_isBreak;
    IlInt		_lock;
    IlBoolean		_modified;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttSubNodeHook
{
public:
    IlvGanttSubNodeHook(IlvGanttChart* gantt);

    void		setGanttChart(IlvGanttChart* gantt);
    inline IlvGanttChart*	getGanttChart() const { return _gantt; }

    virtual IlBoolean	beforeReshape(IlvGanttNode* node,
				      IlUShort i,
				      IlvGanttSubNode* data);
    virtual IlBoolean	afterReshape(IlvGanttNode* node,
				     IlUShort i,
				     IlvGanttSubNode* data);
    virtual IlBoolean	beforeMove(IlvGanttNode* node,
				   IlUShort i,
				   IlvGanttSubNode* data);
    virtual IlBoolean	afterMove(IlvGanttNode* node,
				  IlUShort i,
				  IlvGanttSubNode* data);
    virtual IlBoolean	afterAdd(IlvGanttNode* node, IlvGanttSubNode* data);

private:
    IlvGanttChart*	_gantt;
};


// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttNode
    : public IlvGanttAbstractObject
{
public:
    IlvGanttNode(const char* name,
		 IlBoolean copy = IlTrue,
		 IlBoolean asBreak = IlFalse);
    IlvGanttNode(const char* name, IlBoolean copy, IlUInt count ...);
    virtual ~IlvGanttNode();
    inline IlUShort	getCardinal() const { return _count; }
    inline IlvGanttSubNode* const*	getSubNodes(IlUShort& count) const
	{
	    count = _count;
	    return _subNodes;
	}
    inline IlvGanttSubNode*	getSubNode(IlUShort index) const
	{ return _subNodes[index]; }
    IlUShort		getSubNodeIndex(const IlvGanttSubNode*) const;
    void		addSubNode(IlvGanttSubNode* subnode);
    void		removeSubNode(IlUShort index);
    IlvGraphic*		updateGraphic();
    inline IlvGraphic*	getSubGraphicModel() const
	{ return _subGraphicModel; }
    void		setSubGraphicModel(IlvGraphic* graphic,
					   IlBoolean destroyOld = IlTrue);
    inline void		setDrawMode(IlvGanttNodeDrawMode mode) 
	{ _drawMode = mode; }
    inline IlvGanttNodeDrawMode	getDrawMode() const { return _drawMode; }
    inline void		setAsBreak(IlBoolean asBreak = IlTrue)
	{ _isBreak = asBreak; }
    IlBoolean		isBreak() const { return _isBreak; }

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_subGraphicModelValue;
    static IlSymbol*	_cardinalValue;
    static IlSymbol*	_drawModeValue;
    static IlSymbol*	_isBreakValue;
    static IlSymbol*	_addSubNodeMethod;
    static IlSymbol*	_removeSubNodeMethod;
    static IlSymbol*	_getSubNodeMethod;

    IlvDeclareLazyClassInfo();

protected:
    IlvGraphic*			_subGraphicModel;
    IlvGanttSubNode**		_subNodes;
    IlUShort			_count;
    IlUShort			_alloc;
    IlvGanttNodeDrawMode	_drawMode;
    IlBoolean			_isBreak;

private:
    IlvGanttNode(const IlvGanttNode&) // forbidden
    : IlvGanttAbstractObject() {}  
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttLink
    : public IlvGanttAbstractObject
{
public:
    IlvGanttLink(IlvGanttNode* from,
		 IlvGanttNode* to,
		 IlvGanttLinkType type = IlvStartsAfterEnd,
		 IlInt delay = 0,
		 IlvGraphic* graphic = 0)
	: IlvGanttAbstractObject(0, IlFalse, graphic),
	  _from(from),
	  _to(to),
	  _type(type),
	  _delay(delay)
    {}
    inline IlvGanttNode*	getFrom() const { return _from; }
    inline IlvGanttNode*	getTo() const { return _to; }
    inline IlvGanttLinkType	getType() const { return _type; }
    inline IlInt		getDelay() const { return _delay; }
    void		setFrom(IlvGanttNode* from,
				IlBoolean redraw = IlTrue);
    void		setTo(IlvGanttNode* to, IlBoolean redraw = IlTrue);
    void		setType(IlvGanttLinkType type,
				IlBoolean redraw = IlTrue);
    void		setDelay(IlInt delay, IlBoolean redraw = IlTrue);

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_fromValue;
    static IlSymbol*	_toValue;
    static IlSymbol*	_typeValue;
    static IlSymbol*	_delayValue;

    IlvDeclareLazyClassInfo();

protected:
    IlvGanttNode*	_from;
    IlvGanttNode*	_to;
    IlvGanttLinkType	_type;
    IlInt		_delay;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttGridViewHook
    : public IlvManagerViewHook
{
public:
    IlvGanttGridViewHook(IlvGanttChart* gantt, IlvManager* mgr,
			 IlvView* view)
	: IlvManagerViewHook(mgr, view),
	  _gantt(gantt),
	  _skipCompute(IlFalse),
	  _drawGridBefore(IlTrue),
	  _gridDirections((IlvDirection)(IlvHorizontal|IlvVertical))
    {}

    virtual void	transformerChanged(const IlvTransformer* current,
					   const IlvTransformer* previous)
			{
			    _skipCompute = IlFalse;
			}
    virtual void	contentsChanged() { _skipCompute = IlFalse; }
    virtual void	beforeDraw(IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* r = 0,
				   const IlvRegion* clip = 0);
    virtual void	afterDraw(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* region = 0,
				  const IlvRegion* clip = 0);
    virtual void	drawGrid(IlvPort* dst, const IlvRegion* clip = 0);
    inline void		skipCompute(IlBoolean flag) { _skipCompute = flag; }
    inline IlBoolean	isDrawGridBefore() const { return _drawGridBefore; }
    inline void		setDrawGridBefore(IlBoolean before)
	{ _drawGridBefore = before; }
    inline IlvDirection	getGridDirections() const { return _gridDirections; }
    inline void		setGridDirections(IlvDirection dirs)
	{ _gridDirections = dirs; }
    virtual void	viewResized();

protected:
    IlvGanttChart*	_gantt;
    IlBoolean		_skipCompute;
    IlBoolean		_drawGridBefore;
    IlvDirection	_gridDirections;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttScrollViewHook
    : public IlvManagerViewHook
{
public:
    IlvGanttScrollViewHook(IlvGanttChart* gantt,
			   IlvManager* grapher,
			   IlvView* view);
    virtual void	transformerChanged(const IlvTransformer* current,
					   const IlvTransformer* previous)
			{
			    adjustScrollBars();
			}
    virtual void	viewResized() { adjustScrollBars(); }
    virtual void	contentsChanged();
    virtual void	adjustViews(IlUShort index, IlvDirection dir);
    virtual void	adjustScrollBars();

protected:
    IlvPos		_previousx[2];
    IlvPos		_previousy[2];
    IlvGanttChart*	_gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvStackNode
{
public:
    IlvStackNode() { _data = 0; _below = 0; }

    inline void		storeData(IlAny data) { _data = data; }
    inline void		storeBelow(IlvStackNode *next) { _below = next; }
    inline IlAny	getData() const { return _data; }
    inline IlvStackNode* getNext() const { return _below; }

protected:
    IlAny		_data;	// data
    IlvStackNode*	_below;	// next node of stack (link list)
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvStack
{
public:
    IlvStack() : _top(0) {}
    virtual ~IlvStack();		// in case stack is not empty

    IlBoolean		push(IlAny);	// push data onto stack
    IlAny		pop();	        // pop data off from stack
    IlBoolean		isEmpty() const;

protected:
    IlvStackNode*	_top;		// stack head
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttChart
    : public IlvGadgetContainerRectangle
{
public:
    IlvGanttChart(IlvDisplay*	display,
		  const IlvRect& rect,
		  IlInt		start,
		  IlInt		end,
		  IlInt		shownStart,
		  IlInt		shownEnd,
		  IlUShort	step,
		  IlvDim	rowSize,
		  IlvDim	lineInfoSize	= 0,
		  IlvDim	unitSize	= 20,
		  IlvDim	scaleH		= 32,
		  IlvDim	sbSize		= 16,
		  IlUShort	spacing		= 4,
		  IlUShort	vwSpacing	= 20,
		  IlUShort	margin		= 0,
		  IlvDim	handleSize	= 8,
		  IlvPosition	hasScale	= IlvTop,
		  IlvPosition	hasHSB		= IlvBottom,
		  IlvPosition	hasVSB		= IlvRight,
		  int		numLayers	= 5,
		  IlBoolean	useAcc		= IlTrue,
		  IlvPalette*	palette		= 0);
    virtual ~IlvGanttChart();

    static IlSymbol*	_ganttProperty;
    static IlSymbol*	_objectProperty;
    static IlSymbol*	_subNodeProperty;
    static IlSymbol*	_rowProperty;
    static IlSymbol*	_nameProperty;

    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	makeView(IlvPort* dst, const IlvTransformer* t = 0);
    virtual void	handleResize(const IlvRect& newsize);
    virtual void	handleReshape(const IlvPoint& handlePosition);
    virtual void	ensureVisible(IlvManager* manager,
				      IlvView* view,
				      const IlvPoint& point,
				      IlBoolean redraw = IlTrue);
    virtual void	setPalette(IlvPalette*);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    IlvPalette*		getGridPalette() const;
    void		setGridPalette(IlvPalette* palette);
    inline IlvGrapher*	getGrapher() const { return _grapher; }
    inline IlvView*	getGrapherView(IlUShort index) const
	{ return _gphview[index]; }
    inline IlvManager*	getManager() const { return _manager; }
    inline IlvView*	getManagerView(IlUShort index) const
	{ return _mgrview[index]; }
    inline IlvScale*	getScale(IlUShort index) const
	{ return _scale[index]; }
    virtual IlvScale*	createScale(IlvDisplay* display,
				    const IlvPoint& origin,
				    IlvDim size,
				    IlInt start,
				    IlInt end,
				    IlUShort step,
				    IlvPosition p = IlvTop) const;
    virtual void	updateScale(IlvScale* scale,
				    IlBoolean redraw = IlTrue) const;
    inline IlvScrollBar* getHorizontalScrollBar(IlUShort index) const
	{ return _hsb[index]; }
    inline IlvScrollBar* getVerticalScrollBar(IlUShort index) const
	{ return _vsb[index]; }
    inline IlvFilledRectangle*	getHandle() const { return _handle; }
    void		moveHandle(const IlvPoint& position);
    void		validateHandlePosition(IlvPoint& position);
    inline void		grapherViewsBBox(IlvRect& bbox) const
	{ bbox = _viewsrect; }
    IlUShort		viewIndex(const IlvView*, IlUShort& count) const;
    inline void		resetView() { _view = 0; }
    inline IlvGanttScrollViewHook* getScrollHook(IlUShort index) const
	{ return _scrollHook[index]; }
    inline IlvGanttGridViewHook* getGridHook(IlUShort index) const
	{ return _gridHook[index]; }
    virtual IlvGanttScrollViewHook*	createScrollHook(IlvGrapher* grapher,
							 IlvView* view);
    virtual IlvGanttGridViewHook*	createGridHook(IlvGrapher* grapher,
						       IlvView* view);
    virtual void	removeHooks();
    void		setContentsChangedUpdate(IlBoolean flag);
    inline IlInt	contentsChangedUpdateCount() const
	{ return _updateCount; }
    inline IlBoolean	isShowingGrid() const  { return _showGrid; }
    inline IlBoolean	isShowingGrapherViewBorders() const 
			{
			    return _showingGrapherViewBorders;
			}
    void		setShowingGrapherViewBorders(IlBoolean flag,
						     IlBoolean redraw=IlTrue);
    void		showGrid(IlBoolean flag, IlBoolean redraw = IlTrue);
    void		computeGridPoints(IlUShort index);
    virtual void	drawGrid(IlvPort* dst,
				 IlUShort index,
				 IlBoolean skipCompute = IlFalse,
				 const IlvRegion* clip = 0,
				 IlvTransformer* trans = 0,
				 IlvDirection direction = (IlvDirection)
				 (IlvHorizontal|IlvVertical));

    inline static IlSymbol*	ganttProperty()
	{ return _ganttProperty; }
    inline static IlSymbol*	objectProperty()
	{ return _objectProperty; }
    inline static IlSymbol*	subNodeProperty()
	{ return _subNodeProperty; }
    inline static IlSymbol*	rowProperty()
	{ return _rowProperty; }
    inline static IlSymbol*	nameProperty()
	{ return _nameProperty; }
    inline void		allowDragDrop(IlBoolean flag) 
	{ _allowDragDrop = flag; }
    inline IlBoolean	allowDragDrop() const { return _allowDragDrop; }
    inline void		compactLines(IlBoolean v, IlBoolean = IlTrue)
	{ _compactLines = v; }
    virtual IlBoolean	isValidStep(IlUShort step)
	{
		return ((step > 0) &&
			((IlInt)step <= (_end - _start)/2) &&
			((_end - _start) ==
			 (IlInt)
			 ((_end - _start)/(IlInt)step)*step));
	}
    inline IlUShort	getStep(IlUShort index) const
	{ return _step[index]; }
    IlBoolean		setStep(IlUShort index,
				IlUShort step,
				IlBoolean redraw = IlTrue);
    void		pushDeltaStep(IlUShort hi, IlUShort deltaStep);
    IlUShort		popDeltaStep(IlUShort hi);
    inline IlInt	getStart() const { return _start; }
    inline IlInt	getEnd() const { return _end; }
    IlBoolean		setStartEnd(IlInt start,
				    IlInt end,
				    IlUShort step,
				    IlBoolean redraw = IlTrue);
    virtual void	drawContents(IlvPort* dst,
				     const IlvRect& size,
				     const IlvRegion* clip) const;
    void		drawManagerViewContents(IlUShort i,
						IlvPort* dst,
						const IlvRect& size,
						const IlvRegion* clip) const;
    void		drawGrapherViewContents(IlUShort i,
						IlvPort* dst,
						const IlvRect& size,
						const IlvRegion* clip) const;
    inline IlInt	getShownStart(IlUShort index) const
	{ return _shownStart[index]; }
    inline IlInt	getShownEnd(IlUShort index) const
	{ return _shownEnd[index]; }
    inline void		setShownStart(IlUShort hi, IlInt start)
	{ _shownStart[hi] = start; }
    inline void		setShownEnd(IlUShort hi, IlInt end)
	{ _shownEnd[hi] = end; }
    void		showInterval(IlUShort index,
				     IlInt shownStart,
				     IlInt shownEnd,
				     IlBoolean redraw = IlTrue);
    inline IlUShort	getSpacing() const
	{ return _spacing; }
    inline IlUShort	getViewSpacing() const
	{ return _vwspacing; }
    inline IlvDim	getLineInfoSize() const
	{ return _lineInfoSize; }
    inline IlvDim	getUnitSize() const
	{ return _unitsize; }
    inline IlvDim	getUnitHeight() const
	{ return _unitsize + _spacing; }
    virtual void	installAccelerators();
    void		computeGrapherViewTransformer(IlUShort index,
						      IlvTransformer& t) const;
    void		refreshGrapherViewTransformer(IlUShort index,
						      IlBoolean redraw) const;
    virtual void	translateViews(IlUShort index,
				       IlvPos deltaCol,
				       IlvPos deltaRow,
				       IlBoolean redraw = IlTrue);
    void		scrollViews(IlUShort index,
				    IlvPos columns,
				    IlUShort row,
				    IlvPos units = 0,
				    IlBoolean redraw = IlTrue);
    void		scrollViews(IlUShort index,
				    IlvPoint* origin,
				    IlBoolean redraw = IlTrue);
    IlBoolean		zoomViews(IlUShort index,
				  IlvDirection dir,
				  IlvRect* viewRect,
				  IlBoolean redraw);
    virtual IlBoolean	zoomViews(IlUShort index,
				  IlvDirection dir,
				  IlUShort fromCol,
				  IlUShort toCol,
				  IlUShort fromRow,
				  IlUShort toRow,
				  IlBoolean redraw = IlTrue);
    virtual void	fitViewsTransformerToContents(IlUShort index,
						      IlvDirection dir,
						      IlBoolean redraw=IlTrue);
    virtual void	resetViewsTransformer(IlUShort index,
					      IlBoolean redraw = IlTrue);
    void		adjustViews();
    void		addLine(IlvGanttLine* line,
				IlBoolean redraw = IlTrue,
				int layer = 1);
    virtual void	insertLine(IlvGanttLine* line,
				   IlUShort row,
				   IlBoolean redraw = IlTrue,
				   int layer = 1);
    virtual IlBoolean	moveLine(IlvGanttLine* line,
				 IlUShort row,
				 IlBoolean redraw = IlTrue);
    virtual IlBoolean	swapLines(IlvGanttLine* line1,
				  IlvGanttLine* line2,
				  IlBoolean redraw = IlTrue);
    virtual void	addNode(IlvGanttNode* node,
				IlBoolean redraw = IlTrue,
				int layer = 3);
    virtual void	addLink(IlvGanttLink* link,
				IlBoolean redraw = IlTrue,
				int layer = 2);
    virtual IlBoolean	addSubNode(IlvGanttNode* node,
				   IlvGanttSubNode* subNode,
				   IlBoolean redraw = IlTrue,
				   int layer = 3);
    virtual IlBoolean	removeLine(IlUShort row,
				   IlBoolean redraw = IlTrue,
				   IlBoolean destroy = IlTrue);
    virtual IlBoolean	removeNode(IlvGanttNode* node,
				   IlBoolean redraw = IlTrue,
				   IlBoolean destroy = IlTrue);
    virtual IlBoolean	removeLink(IlvGanttLink* link,
				   IlBoolean redraw = IlTrue,
				   IlBoolean destroy = IlTrue);
    virtual IlBoolean	removeSubNodes(IlvGanttNode* node,
				       IlUShort* indexArray,
				       IlUShort num,
				       IlBoolean redraw = IlTrue,
				       IlBoolean destroy = IlTrue);
    virtual IlvPos	compactRow(IlUShort row, IlBoolean redraw=IlTrue);
    virtual IlBoolean	prettyRowBBox(IlUShort& row,
				      IlvRect& prettyBox,
				      IlBoolean redraw=IlTrue);
    IlUShort*		getRowsOfNode(IlUShort& rowsCount,
				      IlvGanttNode* node,
				      IlUShort* indexArray = 0,
				      IlUShort rmCount = 0);
    IlvGanttNode**	getNodes(IlUInt& count) const;
    IlvGanttNode*	getNode(IlUInt index) const;
    IlvGanttLink*	getLink(IlUInt index) const;
    inline IlUInt	nodesCount() const { return _nodes.length(); }
    inline IlUInt	linksCount() const { return _links.length(); }
    IlBoolean	       isManaged(const IlvGanttAbstractObject* object) const;
    IlvGanttAbstractObject*	getObject(const IlvGraphic* graphic) const;
    IlvGanttAbstractObject*	getObject(const char* name) const;
    IlvGanttSubNode*	getSubNode(const IlvGraphic* graphic) const;
    const char*		getObjectName(const IlvGanttAbstractObject* obj) const;
    IlBoolean		setObjectName(IlvGanttAbstractObject* object,
				      const char* name,
				      IlBoolean redraw = IlTrue);
    virtual void	registerObjectName(IlvGanttAbstractObject*);
    virtual void	cleanObject(IlvGanttAbstractObject*);
    virtual void	lineBBox(IlUShort row, IlvRect& bbox) const;
    IlvPos		getColumnPosition(IlUShort hi, IlvPos col) const;
    IlvPos		getLinePosition(IlUShort row, IlvPos units = 0) const;
    IlvPos		yToPosition(IlvPos y,
				    IlUShort& row,
				    IlvPos& units) const;
    IlvPos		snapX(IlUShort hi, IlvPos x) const;
    IlvPos		snapY(IlvPos y) const;
    void		snapRect(IlUShort hi, IlvRect& rect) const;
    IlvPoint		getPosition(IlUShort hi,
				    IlvPos col,
				    IlUShort row,
				    IlvPos units = 0) const;
    IlvGanttLine**	getLines(IlUShort& count) const;
    inline IlvGanttLine*	getLine(IlUShort row) const
	{ return (row < _lcount) ? _lines[row] : 0; }
    IlUShort		getLineRow(const IlvGanttLine* line) const;
    IlInt		getLineLoad(IlUShort row, IlInt time) const;
    inline void		 setFreeLine(IlvGanttLine* line)
	{ _freeLine = line; }
    inline IlvGanttLine* getFreeLine() const
	{ return _freeLine; }
    inline IlUShort	rows() const { return _lcount; }
    IlvPos		columns(IlUShort hi) const;
    void		rowBBox(IlUShort row, IlvRect& bbox) const;
    virtual void	rowResized(IlUShort row, IlvPos dh) const;
    void		translateRows(IlUShort row,
				      IlvPos dh,
				      IlBoolean redraw = IlTrue);
    IlUShort		firstRow(IlUShort vi) const;
    IlUShort		firstVisibleRow(IlUShort index) const;
    IlUShort		lastRow(IlUShort vi) const;
    IlUShort		lastVisibleRow(IlUShort index) const;
    IlBoolean		yToRow(IlvPos y, IlUShort& row) const;
    IlUShort		yToClosestRow(IlvPos y) const;
    IlvPos		yToSubNodeY(IlvPos y) const;
    IlvGanttSubNode**	getLineSubNodes(IlUInt& count, IlUShort row) const;
    virtual void	subNodeBBox(const IlvGanttNode* node,
				    IlUShort index,
				    IlvRect& bbox) const;

    virtual void	prettySubNodeBBox(IlvGanttNode* node,
					  IlUShort index,
					  IlvRect& bbox,
					  IlBoolean redraw = IlTrue);
    virtual void	setSubNodeValues(IlvGanttNode* node,
					 IlUShort index,
					 IlInt startMin,
					 IlInt startMax,
					 IlInt endMin,
					 IlInt endMax,
					 IlvGanttLine* line,
					 IlUShort capacity,
					 IlBoolean redraw = IlTrue);
    void		refreshSubNode(IlvGanttSubNode* subnode,
				       IlBoolean redraw = IlTrue);
    virtual void	setNodeDrawMode(IlvGanttNode* node,
					IlvGanttNodeDrawMode mode,
					IlBoolean redraw = IlTrue);
    void		setNodeDrawMode(IlvGanttNodeDrawMode mode,
					IlBoolean redraw = IlTrue);
    inline IlvGanttNodeDrawMode	getNodeDrawMode() const
	{ return _nodeDrawMode; }
    void		getSubNodeDrawnStartEnd(const IlvGanttNode* node,
						IlUShort index,
						IlInt& start,
						IlInt& end) const;
    void		showFreeNodes(IlBoolean flag,
				      IlBoolean redraw = IlTrue);
    inline IlBoolean	 isShowingFreeNodes() const
	{ return _showFreeNodes; }
    inline const IlList* getEmptyNodes() const
	{ return &_emptyNodes; }
    inline IlvGraphic*	getSubNodeGraphicModel() const
	{ return _subNodeGraphicModel; }
    IlvGraphic*		setSubNodeGraphicModel(IlvGraphic* model,
					       IlBoolean deleteOld = IlTrue);
    inline IlvGraphic*	getLineGraphicModel() const
	{ return _lineGraphicModel; }
    IlvGraphic*		setLineGraphicModel(IlvGraphic* model,
					    IlBoolean deleteOld = IlTrue);
    IlvGraphic*		setLineGrid(IlvGraphic* compoGrid,
				    IlBoolean redraw = IlTrue,
				    IlInt layer = 0);
    IlvGraphic*		getLineGrid() const;
    IlvGraphic*		setRowGrid(IlvGraphic* compoGrid,
				   IlBoolean redraw = IlTrue,
				   IlInt layer = 0);
    IlvGraphic*		getRowGrid() const;
    inline IlvGraphic*	getLinkGraphicModel() const
	{ return _linkGraphicModel; }
    void		setLinkGraphicModel(IlvGraphic* model,
					    IlBoolean deleteOld = IlTrue);
    inline IlvGraphic*	getBreakGraphicModel() const
	{ return _breakGraphicModel; }
    void		setBreakGraphicModel(IlvGraphic* model,
					     IlBoolean destroyOld = IlTrue);
    virtual void	deleteAll(IlBoolean destroy,
				  IlBoolean redraw = IlTrue);
    virtual void	deleteNodes(IlBoolean destroy,
				    IlBoolean redraw = IlTrue);
    virtual void	deleteSelections(IlBoolean redraw = IlTrue);
    virtual void	psDump(const char* filename,
			       IlUInt xmargin = 20,
			       IlUInt ymargin   = 20,
			       IlBoolean rotate = IlTrue) const;
    void		setObjectFileName(const char* name);
    void		readObjectFile(IlBoolean redraw = IlTrue);
    virtual char*	save(IlUInt& count) const;
    virtual void	load(const char* str);
    virtual void	saveObjects(IlvOutputFile& file) const;
    virtual void	loadObjects(IlvInputFile& file);

    inline IlInt	getGridLayer()  const { return _gridLayer;  }  // 1
    inline IlInt	getNodeLayer()  const { return _nodeLayer;  }  // 3
    inline IlInt	getBreakLayer() const { return _breakLayer; }  // 4

    inline IlvPalette*	getHiliteBackGroundPalette() const
	{ return _hiliteBGPalette; }
    inline void		setHiliteBackGroundPalette(IlvPalette* bgPal)
	{ _hiliteBGPalette = bgPal; }
    inline IlBoolean	getHiliteState() const { return _hiliteState; }
    inline void		  setHiliteState(IlBoolean hilite = IlTrue)
	{ _hiliteState=hilite; }
    inline const IlvList* getHiliteList() const
	{ return &_hiliteList; }
    inline void		emptyHiliteList() { _hiliteList.empty(); }
    inline void		addSubNodeToHiliteList(IlvGanttSubNode* subnode)
	{ _hiliteList.append((IlAny)subnode); }
    inline IlInt	getSubNodeMinimumSize() const
	{ return _subNodeMinimumSize; }
    inline void		setSubNodeMinimumSize(IlInt size)
	{ _subNodeMinimumSize = size; }
    inline IlInt	getVersion() const { return _version; }
    inline void		setVersion(IlInt version) { _version = version; }
    inline IlvGanttSubNodeHook*	getSubNodeHook() { return _subNodeHook;}
    IlvGanttSubNodeHook*	setSubNodeHook(IlvGanttSubNodeHook* hook);
    IlvRect&		getWorkArea(IlvRect& area) const;
    virtual IlvRect&	getLineArea(IlvRect& area) const;
    static IlSymbol*	WorkAreaCallbackType();
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**)const;
    virtual void	setDoubleBuffering(IlBoolean doubleBuffer);
    inline IlBoolean	isDoubleBuffering() const { return _doubleBuffer; }

    DeclareGraphicAccessors();

    virtual IlBoolean getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_startValue;
    static IlSymbol*	_endValue;
    static IlSymbol*	_getShownStartMethod;
    static IlSymbol*	_getShownEndMethod;
    static IlSymbol*	_setStartEndMethod;
    static IlSymbol*	_showIntervalMethod;
    static IlSymbol*	_getStepMethod;
    static IlSymbol*	_setStepMethod;
    static IlSymbol*	_getGrapherViewMethod;
    static IlSymbol*	_getManagerViewMethod;
    static IlSymbol*	_getScaleMethod;
    static IlSymbol*	_getHorizontalScrollBarMethod;
    static IlSymbol*	_getVerticalScrollBarMethod;
    static IlSymbol*	_handleValue;
    static IlSymbol*	_handlePositionValue;
    static IlSymbol*	_handleSizeValue;
    static IlSymbol*	_showGridValue;
    static IlSymbol*	_getGrapherViewBBoxMethod;
    static IlSymbol*	_getManagerViewBBoxMethod;
    static IlSymbol*	_unitSizeValue;
    static IlSymbol*	_unitSpacingValue;
    static IlSymbol*	_viewSpacingValue;
    static IlSymbol*	_offsetValue;
    static IlSymbol*	_objectFileNameValue;
    static IlSymbol*	_lineCountValue;
    static IlSymbol*	_linkCountValue;
    static IlSymbol*	_nodeCountValue;
    static IlSymbol*	_nodeDrawModeValue;
    static IlSymbol*	_allowDragDropValue;
    static IlSymbol*	_subNodeGraphicModelValue;
    static IlSymbol*	_lineGraphicModelValue;
    static IlSymbol*	_linkGraphicModelValue;
    static IlSymbol*	_breakGraphicModelValue;
    static IlSymbol*	_subNodeMinimumSizeValue;
    static IlSymbol*	_gridLayerValue;
    static IlSymbol*	_linkLayerValue;
    static IlSymbol*	_nodeLayerValue;
    static IlSymbol*	_breakLayerValue;
    static IlSymbol*	_addLineMethod;
    static IlSymbol*	_getLineMethod;
    static IlSymbol*	_removeLineMethod;
    static IlSymbol*	_moveLineMethod;
    static IlSymbol*	_swapLinesMethod;
    static IlSymbol*	_getLineRowMethod;
    static IlSymbol*	_getLineSubNodeMethod;
    static IlSymbol*	_getLineLoadMethod;
    static IlSymbol*	_addNodeMethod;
    static IlSymbol*	_getNodeMethod;
    static IlSymbol*	_removeNodeMethod;
    static IlSymbol*	_removeAllNodeMethod;
    static IlSymbol*	_addSubNodeMethod;
    static IlSymbol*	_removeSubNodeMethod;
    static IlSymbol*	_addLinkMethod;
    static IlSymbol*	_getLinkMethod;
    static IlSymbol*	_removeLinkMethod;
    static IlSymbol*	_getObjectMethod;
    static IlSymbol*	_deleteAllMethod;
    static IlSymbol*	_compactRowMethod;
    static IlSymbol*	_workAreaCallbackType;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGanttChart);

protected:
    IlvGraphic*		addSubNodeGraphic(IlvGanttNode* node,
					  IlUShort index,
					  IlBoolean redraw, int layer);
protected:
    IlInt			_start;
    IlInt			_end;
    IlInt			_shownStart[2];
    IlInt			_shownEnd[2];
    IlUShort			_step[2];
    IlInt			_iShownStart;
    IlInt			_iShownEnd;
    IlUShort			_iStep;
    IlvStack			_stepStack[2];
    IlvGrapher*			_grapher;
    IlvView*			_gphview[4];
    IlvManager*			_manager;
    IlvView*			_mgrview[2];
    IlvScale*			_scale[2];
    IlvScrollBar*		_hsb[2];
    IlvScrollBar*		_vsb[2];
    IlvFilledRectangle*		_handle;
    IlvGanttScrollViewHook*	_scrollHook[4];
    IlvGanttGridViewHook*	_gridHook[4];
    IlvPoint*			_gridXPoints[4];
    IlvPoint*			_gridYPoints[4];
    IlUShort			_numXPoints[4];
    IlUShort			_numYPoints[4];
    IlvPosition			_hasHSB;
    IlvPosition			_hasVSB;
    IlvPosition			_hasScale;
    IlBoolean			_showGrid;
    IlBoolean			_showingGrapherViewBorders;
    IlvRect			_viewsrect;
    IlvRect			_gphvrect[4];
    IlvRect			_mgrvrect[2];
    IlvRect			_scalrect[2];
    IlvRect			_hsbrect[2];
    IlvRect			_vsbrect[2];
    IlvRect			_handrect;
    IlvDim			_handsize;
    IlvPoint			_handpoint;
    IlFloat			_lastWRate[2];
    IlFloat			_lastHRate[2];
    IlvDim			_lineInfoSize;
    IlvDim			_unitsize;
    IlUShort			_spacing;
    IlUShort			_vwspacing;
    IlUShort			_offset;
    IlvPalette*			_invertedPalette;
    char*			_objectFileName;
    IlvStringHashTable*		_names;
    IlList			_links;
    IlList			_nodes;
    IlList			_emptyNodes; // managed without graphics
    IlvGanttLine**		_lines;
    IlvGanttLine*		_freeLine;
    IlvDim*			_lpos;
    IlUShort			_lcount;
    IlUShort			_lalloc;
    IlvGanttNodeDrawMode	_nodeDrawMode;
    IlBoolean			_compactLines;
    IlBoolean			_showFreeNodes;
    IlBoolean			_allowDragDrop;
    IlvGraphic*			_lineGraphicModel;
    IlvGraphic*			_subNodeGraphicModel;
    IlvGraphic*			_linkGraphicModel;
    IlvGraphic*			_breakGraphicModel;
    IlvGraphic*			_lineGrid;
    IlvGraphic*			_rowGrid;
    IlBoolean			_useacc;
    IlInt			_updateCount;
    IlInt			_backGroundLayer;  // 0
    IlInt			_gridLayer;        // 1
    IlInt			_linkLayer;        // 2
    IlInt			_nodeLayer;        // 3
    IlInt			_breakLayer;       // 4
    IlvPalette*			_hiliteBGPalette;
    IlvPalette*			_gridPalette;
    IlBoolean			_hiliteState;
    IlList			_hiliteList;
    IlvGanttSubNodeHook*	_subNodeHook;
    IlInt			_subNodeMinimumSize;
    IlInt			_version; // 2 for Views 2.4
    IlBoolean			_doubleBuffer;

    void		init(IlvDim rowsize,
			     IlvDim scaleH,
			     IlvDim sbsize,
			     int numLayers,
			     IlUShort rows);
    void		doLayout(IlvDim rowsize,
				 IlvDim scaleH,
				 IlvDim sbsize);
    void		redoLayout();
    void		computePalettes();
    void		moveResizeViews(IlvPos viewX,
					IlvPos viewY,
					IlvDim* viewW,
					IlvDim* viewH);
    IlvGraphic*		makeSubNodeGraphic(IlvGanttNode*,
					   IlUShort i,
					   IlBoolean redraw = IlTrue);
    void		getSubNodeDrawnStartEnd(const IlvGanttNode*,
						const IlvGanttSubNode*,
						IlInt& start,
						IlInt& end) const;
    void		deleteObjects(IlBoolean destroy = IlTrue);
    void		deleteNodeObjects(IlBoolean destroy = IlTrue);
    IlList*		getLinks(const IlvGanttNode*,
				 IlBoolean isFrom = IlTrue,
				 IlBoolean isTo = IlTrue) const;
    virtual void	initHooks();
    IlvPalette*		createGridPalette();
};

ILVGANTTMODULEINIT(gantt);

#endif /* !__Ilv_Gantt_Gantt_H */
