// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gantt/ganttint.h
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
// Declaration of the Gantt Chart interactors classes
// --------------------------------------------------------------------------

#ifndef __Ilv_Gantt_Ganttint_H
#define __Ilv_Gantt_Ganttint_H

#if !defined(__Ilv_Graphics_Inter_H)
#include <ilviews/graphics/inter.h>
#endif
#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Manager_Selinter_H)
#include <ilviews/manager/selinter.h>
#endif
#if !defined(__Ilv_Ginteract_H)
#include <ilviews/grapher/inters.h>
#endif
#if !defined(__Ilv_Gantt_Gantt_H)
#include <ilviews/gantt/gantt.h>
#endif
#if !defined(__Ilv_Manager_Paninter_H)
#include <ilviews/manager/paninter.h>
#endif

// -------------------
// view interactors
// -------------------
// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttAddNodeInteractor
    : public IlvDragRectangleInteractor
{
public:
    IlvGanttAddNodeInteractor(IlvGanttChart* gantt,
			      IlvView*       view,
			      IlUShort       button  = IlvLeftButton,
			      IlBoolean      asBreak = IlFalse)
	: IlvDragRectangleInteractor(gantt->getGrapher(), view, button),
	  _gantt(gantt),
	  _isBreak(asBreak)
    {}
    IlvGanttAddNodeInteractor(IlvGanttChart* gantt,
			      IlvManager*    mgr, 
			      IlvView*       view,
			      IlUShort       button = IlvLeftButton,
			      IlBoolean      asBreak = IlFalse)
	: IlvDragRectangleInteractor(mgr, view, button),
	  _gantt(gantt),
	  _isBreak(asBreak)
    {}

    // __________________________________________________________________
    inline
    IlvGanttChart*	getGanttChart() const { return _gantt; }
    virtual void	ensureVisible(const IlvPoint& p);
    virtual void	doIt(IlvRect& rect);
    virtual
    IlvGanttNode*	makeNode(IlInt         startMin,
				 IlInt         startMax,
				 IlInt         endMin,
				 IlInt         endMax,
				 IlvGanttLine* line);
    inline void		setAsBreak(IlBoolean asBreak = IlTrue)
			{
			    _isBreak = asBreak;
			}
    inline IlBoolean	isBreak() const { return _isBreak; }

protected:
    IlvGanttChart*	_gantt;
    IlBoolean		_isBreak;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttAddLinkInteractor : public IlvMakeLinkInteractor
{
public:
    IlvGanttAddLinkInteractor(IlvGanttChart* gantt,
			      IlvView*       view,
			      IlBoolean      oriented = IlTrue)
	: IlvMakeLinkInteractor(gantt->getGrapher(), view, oriented),
	  _gantt(gantt)
    {}

    IlvGanttAddLinkInteractor(IlvGanttChart* gantt, 
			      IlvManager*    mgr,
			      IlvView*       view,
			      IlBoolean      oriented = IlTrue)
	: IlvMakeLinkInteractor(mgr, view, oriented),
	  _gantt(gantt)
    {}

    inline
    IlvGanttChart*	getGanttChart() const { return _gantt; }
    virtual void	doIt(IlvGraphic* gfrom, IlvGraphic* gto);
    virtual
    IlvGanttLink*	makeLink(IlvGanttNode* from, IlvGanttNode* to);

protected:
    IlvGanttChart*	_gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttSelectInteractor : public IlvGraphSelectInteractor
{
public:
    IlvGanttSelectInteractor(IlvGanttChart* gantt,
			     IlvView*       view)
	: IlvGraphSelectInteractor(gantt->getGrapher(), view),
	  _gantt(gantt), 
	  _operatOnSet(IlFalse) {}

    IlvGanttSelectInteractor(IlvGanttChart* gantt,
			     IlvManager*    mgr,
			     IlvView*       view)
	: IlvGraphSelectInteractor(mgr, view),
	  _gantt(gantt), _operatOnSet(IlFalse) {}

    inline
    IlvGanttChart*	getGanttChart() const { return _gantt; }
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	drawGhostMove(IlvGraphic* graphic,
				      IlvRegion*  clip = 0);
    virtual void	drawGhostReshape(IlvGraphic* graphic,
					 IlvRegion* clip = 0);
    virtual void	doTranslate(const IlvPoint& p);
    virtual void	doReshape(IlvGraphic* graphic, const IlvRect& rect);
    virtual void	ensureVisible(const IlvPoint& p);
    virtual void	moveNode(IlvGanttNode*  node,
				 IlInt*         startMinArray,
				 IlInt*         startMaxArray,
				 IlInt*         endMinArray,
				 IlInt*         endMaxArray,
				 IlvGanttLine** lines);

    virtual void	moveSubNode(IlvGanttNode* node,
				    IlUShort      idx,
				    IlInt         startMin,
				    IlInt         startMax,
				    IlInt         endMin,
				    IlInt         endMax, 
				    IlvGanttLine* line);
    virtual void	reshapeNode(IlvGanttNode* node,
				    IlInt*        startMinArray,
				    IlInt*        startMaxArray,
				    IlInt*        endMinArray,
				    IlInt*        endMaxArray);

    virtual void	reshapeSubNode(IlvGanttNode* node,
				       IlUShort      idx,
				       IlInt         startMin,
				       IlInt         startMax,
				       IlInt         endMin,
				       IlInt         endMax);

    virtual IlBoolean	beforeReshapeSubNode(IlvGanttNode*    node,
					     IlUShort         i,
					     IlvGanttSubNode* data);
    virtual IlBoolean	afterReshapeSubNode (IlvGanttNode*    node,
					     IlUShort         i,
					     IlvGanttSubNode* data);

    virtual IlBoolean	beforeMoveSubNode(IlvGanttNode*    node,
					  IlUShort         i,
					  IlvGanttSubNode* data);
    virtual IlBoolean	afterMoveSubNode (IlvGanttNode*    node,
					  IlUShort         i,
					  IlvGanttSubNode* data);

protected:
    IlvGanttChart*	_gantt;
    IlBoolean		_operatOnSet;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttZoomInteractor : public IlvDragRectangleInteractor
{
public:
    IlvGanttZoomInteractor(IlvGanttChart* gantt,
			   IlvView*       view, 
			   IlUShort       button = IlvLeftButton)
	: IlvDragRectangleInteractor(gantt->getManager(),
				     view,
				     button,
				     IlFalse),
	_gantt(gantt) {}

    IlvGanttZoomInteractor(IlvGanttChart* gantt, 
			   IlvManager*    mgr,
			   IlvView*       view, 
			   IlUShort       button = IlvLeftButton)
	: IlvDragRectangleInteractor(mgr, view, button, IlFalse)
    {
	_gantt = gantt;
    }
    // __________________________________________________________________
    inline
    IlvGanttChart*	getGanttChart() const { return _gantt; }
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	ensureVisible(const IlvPoint& p);
    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);

protected:
    IlvGanttChart*	_gantt;
};

// -------------------
// Object interactors
// -------------------
// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttDragDropInteractor : public IlvDragDropInteractor
{
public:

    IlvGanttDragDropInteractor(IlvView* target = 0, IlvGraphic* ghost = 0);

    IlvGanttChart*	getGanttChart(const IlvGraphic* obj) const;
    IlvGanttChart*	getTargetGanttChart(const IlvView* targetView) const;
    virtual
    IlvGanttNode*	makeNode(const IlvGanttNode* source,
				 IlInt*              startMinArray,
				 IlInt*              startMaxArray,
				 IlInt*              endMinArray,
				 IlInt*              endMaxArray,
				 IlvGanttLine**      lines,
				 IlUShort*           capacities);
    virtual
    IlvGanttSubNode*	makeSubNode(IlvGanttNode* dst,
				    IlInt         startMin,
				    IlInt         startMax,
				    IlInt         endMin,
				    IlInt         endMax,
				    IlvGanttLine* line,
				    IlUShort      capacity);

    virtual void	dropNode(const IlvGanttNode* source,
				 IlInt*              startMinArray,
				 IlInt*              startMaxArray,
				 IlInt*              endMinArray,
				 IlInt*              endMaxArray,
				 IlvGanttLine**      lines,
				 IlUShort*           capacities);

    virtual void	dropSubNode(IlvGanttNode* dst,
				    IlUShort      idx,
				    IlInt         startMin,
				    IlInt         startMax,
				    IlInt         endMin,
				    IlInt         endMax,
				    IlvGanttLine* line,
				    IlUShort      capacity);

    virtual IlBoolean	handleEvent(IlvGraphic*,
				    IlvEvent&,
				    const IlvTransformer*);

    virtual void	checkPosition(IlvPoint& position);

    virtual void	doIt(IlvView*        target, 
			     IlvGraphic*     ghost, 
			     const IlvPoint& p);
    virtual void	drawGhost(IlvView*	        view, 
				  IlvGraphic*	        g,
				  const IlvPoint&       position, 
				  const IlvTransformer* t = 0);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvGanttDragDropInteractor);

protected:
    IlvGanttChart*	_gantt;
    const IlvTransformer* _t;
    IlBoolean		_operatOnSet;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttScaleInteractor : public IlvInteractor
{
public:
    IlvGanttScaleInteractor();

    IlvGanttChart*	getGanttChart(const IlvGraphic* scale) const;

    // Compat
    IlvGanttChart*	getGanttChart(const IlvContainer*) const;    

    virtual void	drawGhost(IlvContainer*         view, 
				  IlvGraphic*           scale,
				  const IlvRect&        timeRect, 
				  const IlvTransformer* t = 0);

    virtual void	validate(IlvGraphic*    scale, 
				 const IlvRect& timeRect,
				 IlInt&         shownStart,
				 IlInt&         shownEnd);

    virtual IlBoolean	handleEvent(IlvGraphic*           scale, 
				    IlvEvent&             event, 
				    const IlvTransformer* t);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvGanttScaleInteractor);
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttHandleInteractor : public IlvMoveInteractor
{
public:
    IlvGanttHandleInteractor();

    IlvGanttChart*	getGanttChart(const IlvGraphic* handle) const;

    IlvGanttChart*	getGanttChart(const IlvContainer*) const;

    virtual void	drawGhost(IlvView*              view, 
				  IlvGraphic*           ghost,
				  const IlvPoint&       deltaMove,
				  const IlvTransformer* t);

    virtual void	doIt(IlvGraphic*           handle,
			     const IlvPoint&       deltaMove, 
			     const IlvTransformer* t = 0);

    virtual void	validate(IlvGraphic*           handle,
				 IlvPoint&             p,
				 const IlvTransformer* t = 0);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvGanttHandleInteractor);
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttPanZoomInteractor : public IlvPanZoomInteractor
{
public:
    IlvGanttPanZoomInteractor(IlvGanttChart* gantt, 
			      IlvManager*    grapher,
			      IlvView*       view) 
			      :IlvPanZoomInteractor(grapher, view)
    {
	setGanttChart(gantt);
    }

    inline
    IlvGanttChart*	getGanttChart() { return _gantt; }

    inline void		setGanttChart(IlvGanttChart* gantt) { _gantt = gantt; }
    IlBoolean		handleEvent(IlvEvent& event);
    virtual IlBoolean	accept(const IlvGraphic* obj) const;

protected:
    virtual void	doTranslate(IlvPos dx, IlvPos dy, IlBoolean reDraw);
    virtual void	doZoom(const IlvPoint& center,
			       IlFloat         scalex,
			       IlBoolean       reDraw);
protected:
    IlvGanttChart*	_gantt;
    IlvPoint		_unTranslated;
};

ILVGANTTMODULEINIT(ganttint);

#endif /* !__Ilv_Gantt_Ganttint_H */
