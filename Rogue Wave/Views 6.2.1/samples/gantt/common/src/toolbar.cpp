// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/src/toolbar.cpp
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
#include <toolbar.h>
#include <utils.h>
#include <ilviews/gantt/gantt.h>
#include <ilviews/gantt/ganttint.h>
#include <ilviews/gantt/ganttgrd.h>
#include <ilviews/manager/mgrview.h>
#include <ilviews/base/clssinfo.h>
#include <ilviews/base/graphic.h>
#include <ilviews/graphics/io.h>
#include <ilviews/graphics/shadlab.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/amenu.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/bitmaps/png.h>

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// Callbacks forward declaration
//
void ILVCALLBACK OnBorder(IlvGraphic* g,
			  IlAny gantt);
void ILVCALLBACK OnCreateActivity(IlvGraphic* g,
				  IlAny gantt);
void ILVCALLBACK OnCreateBreak(IlvGraphic* g,
			       IlAny gantt);
void ILVCALLBACK OnCreateConstraint(IlvGraphic* g,
				    IlAny gantt);
void ILVCALLBACK OnDragAndDrop(IlvGraphic* g,
			       IlAny gantt);
void ILVCALLBACK OnSelect(IlvGraphic* g,
			  IlAny gantt);
void ILVCALLBACK OnCreateRow(IlvGraphic* g,
			     IlAny gantt);
void ILVCALLBACK OnDeleteRow(IlvGraphic* g,
			     IlAny gantt);
void ILVCALLBACK OnPan(IlvGraphic* g,
		       IlAny gantt);
void ILVCALLBACK OnSetSubNodeGraphicModel(IlvGraphic* g,
					  IlAny gantt);
void ILVCALLBACK OnSetColor(IlvGraphic* g,
			    IlAny gantt);

#if defined(IL_STD)
#  include <cstdio>
IL_STDUSE
#else /* !IL_STD */
#  include <stdio.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
IlvGanttToolBar::IlvGanttToolBar(IlvDisplay* display,
				 IlvGanttChart* gantt)
: IlvToolBar(display, IlvRect(0, 0, 500, 24)),
  _gantt(gantt)
{
    // Read the toolbar object
    IlvToolBar* toolbar =
	(IlvToolBar*)IlvInputFile::ReadObject(display, "toolbar.ilv");
    while (toolbar->getCardinal()) {
	IlvMenuItem* item = toolbar->getItem((IlUShort)0);
	toolbar->removeItem(0, IlFalse);
	insertItem(item);
    }
    resize(toolbar->w(), toolbar->h());
    delete toolbar;

    // Create the menu item selector
    IlSymbol* name = IlSymbol::Get("MenuItemSelector");
    IlvMenuItemSelector* selector = new IlvMenuItemSelector(name);
    selector->addTo(this);
    selector->addItem(IlSymbol::Get("Select"));
    selector->addItem(IlSymbol::Get("Create Activity"));
    selector->addItem(IlSymbol::Get("Create Break"));
    selector->addItem(IlSymbol::Get("Create Constraint"));
    selector->addItem(IlSymbol::Get("Pan & Zoom"));
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setHolder(IlvGraphicHolder* holder)
{
    IlvToolBar::setHolder(holder);
    if (holder != 0 ) {
	holder->registerCallback("OnBorder", OnBorder);
	holder->registerCallback("OnCreateActivity", OnCreateActivity);
	holder->registerCallback("OnCreateBreak", OnCreateBreak);
	holder->registerCallback("OnCreateConstraint", OnCreateConstraint);
	holder->registerCallback("OnDragAndDrop", OnDragAndDrop);
	holder->registerCallback("OnSelect", OnSelect);
	holder->registerCallback("OnPan", OnPan);
	holder->registerCallback("OnCreateRow", OnCreateRow);
	holder->registerCallback("OnDeleteRow", OnDeleteRow);
	holder->registerCallback("OnSetSubNodeGraphicModel",
				 OnSetSubNodeGraphicModel);
	holder->registerCallback("OnSetColor", OnSetColor);
    }
}

// -------------------------------------------------------------------------
void
IlvGanttToolBar::removeAllInteractors() 
{
    IlUShort i;
    for (i = 0; i < 4; i++) {
	IlvManagerViewInteractor* inter =
	    _gantt->getGrapher()->getInteractor(_gantt->getGrapherView(i));
	if (inter) {
	    _gantt->getGrapher()->removeInteractor(
						  _gantt->getGrapherView(i));
	    delete inter;
	}
    }
    for (i = 0; i < 2; i++) {
	IlvManagerViewInteractor* inter =
	    _gantt->getManager()->getInteractor(_gantt->getManagerView(i));
	if (inter) {
	    _gantt->getManager()->removeInteractor(
						  _gantt->getManagerView(i));
	    delete inter;
	}
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setBorder()
{
    IlvMenuItem* item = (IlvMenuItem*)getCallbackItem();
    item->setChecked(!item->isChecked());
    getGanttChart()->setShowingGrapherViewBorders(item->isChecked());
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setCreateActivity() 
{
    removeAllInteractors();
    IlvGrapher* grapher = _gantt->getGrapher();
    for (IlUShort i = 0; i < 4; i++) {
	IlvView* view = _gantt->getGrapherView(i);
	IlvManagerViewInteractor* inter =
	    new IlvGanttAddNodeInteractor(_gantt, grapher, view);
	grapher->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setCreateBreak() 
{
    removeAllInteractors();
    IlvGrapher* grapher = _gantt->getGrapher();
    for (IlUShort i = 0; i < 4; i++) {
	IlvView* view = _gantt->getGrapherView(i);
	IlvManagerViewInteractor* inter =
			new IlvGanttAddNodeInteractor(_gantt, grapher,
						      view,
						      IlvLeftButton, IlTrue);
	grapher->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setCreateConstraint() 
{
    removeAllInteractors();
    IlvGrapher* grapher = _gantt->getGrapher();
    for (IlUShort i = 0; i < 4; i++) {
	IlvView* view = _gantt->getGrapherView(i);
	IlvManagerViewInteractor* inter =
	    new IlvGanttAddLinkInteractor(_gantt, grapher, view);
	grapher->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setSelect() 
{
    IlUShort i;
    removeAllInteractors();
    IlvGrapher* grapher = _gantt->getGrapher();
    for (i = 0; i < 4; i++) {
	IlvView* view = _gantt->getGrapherView(i);
	IlvGanttSelectInteractor* inter =
	    new IlvGanttSelectInteractor(_gantt, grapher, view);
	inter->opaqueMove(IlTrue);
	inter->opaqueReshape(IlTrue);
	grapher->setInteractor(inter);
    }
    IlvManager* manager = _gantt->getManager();
    for (i = 0; i < 2; i++) {
	IlvView* view = _gantt->getManagerView(i);
	IlvGanttSelectInteractor* inter =
	    new IlvGanttSelectInteractor(_gantt, manager, view);
	inter->opaqueMove(IlTrue);
	inter->opaqueReshape(IlTrue);
	manager->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setPan() 
{
    removeAllInteractors();
    IlvGrapher* grapher = _gantt->getGrapher();
    for (IlUShort i = 0; i < 4; i++) {
	IlvView* view = _gantt->getGrapherView(i);
	IlvManagerViewInteractor* inter =
	    new IlvGanttPanZoomInteractor(_gantt, grapher, view);
	grapher->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setDragAndDrop() 
{
    _gantt->allowDragDrop(IlTrue);
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::createRow() 
{
    char name[32];
    sprintf(name, "New line %d", _gantt->rows());
    IlvGanttLine* line = new IlvGanttLine(name, 1);
    _gantt->addLine(line);

    // Ensure that the new line is visible in the first view.
    IlvManager* mgr = _gantt->getManager();
    IlvRect bbox;
    _gantt->rowBBox((IlUShort)(_gantt->rows() - 1), bbox);
    IlvView* view = _gantt->getManagerView(0);
    if (mgr->getTransformer(view)) {
	mgr->getTransformer(view)->apply(bbox);
    }
    _gantt->ensureVisible(mgr, view, IlvPoint(0, bbox.bottom()));
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::deleteRow() 
{
    // Find the selected Gantt lines.
    IlvManager* mgr = _gantt->getManager();
    IlUInt count;
    IlvGraphic* const* selections = mgr->getSelections(count);
    if (!count)  {
	return;
    }
    IlPoolOf(Pointer)::Lock((IlAny*)selections);
    IlList lines;
    for (IlUInt i = 0; i < count; ++i) {
	IlvGanttAbstractObject* o = _gantt->getObject(selections[i]);
	if ((o != 0)
	    && (o->getClassInfo()->isSubtypeOf(IlvGanttLine::ClassInfo()))) {
	    lines.append(o);
	}
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)selections);

    // Delete the Gantt lines found.
    IlvGanttLine* line;
    mgr->initReDraws();
    IlMapList(&lines, IlvGanttLine*, line,
	      _gantt->removeLine(_gantt->getLineRow(line));
	      );
    mgr->reDrawViews();
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setSubNodeGraphicModel()
{
    // Get the graphic object of the current menu item.
    IlvMenuItem* item = (IlvMenuItem*)getCallbackItem();
    IlvGraphic* graphic = item->getGraphic();
    RegisterGanttNameProperty(graphic);
    _gantt->setSubNodeGraphicModel(graphic->copy());

    // Find the selected Gantt subnodes.
    IlvGrapher* grapher = _gantt->getGrapher();
    IlUInt count;
    IlvGraphic* const* selections = grapher->getSelections(count);
    if (!count)  {
	return ;
    }
    IlPoolOf(Pointer)::Lock((IlAny*)selections);
    for (IlUInt i = 0; i < count; ++i) {
	IlvGanttSubNode* subnode =
	    (IlvGanttSubNode*)_gantt->getSubNode(selections[i]);
	if (subnode != 0) {
	    if (!subnode->isBreak()) {
		// Replace the graphic representing the subnode.
		IlvGanttNode* node = subnode->getNode();
		IlvGraphic* activity = graphic->copy();
		IlInt index = node->getSubNodeIndex(subnode);
		OnGanttObjectNameChanged(node, activity, IlvGanttIsNode,
					 &index);
		subnode->setGraphic(activity);
	    }
	}
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)selections);
}

// --------------------------------------------------------------------------
void
IlvGanttToolBar::setColor()
{
    // Get the graphic object of the current menu item.
    IlvMenuItem* item = (IlvMenuItem*)getCallbackItem();
    IlBoolean foreground = item->getName() == 0 ?
      IlFalse : 0 == strcmp(item->getName(), "GridForeground");
    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)item->getGraphic();
    if (foreground) {
	_gantt->getGridPalette()->setForeground(graphic->getBackground());
    }
    else {
	_gantt->getGridPalette()->setBackground(graphic->getBackground());
    }
    if (_gantt->isSubtypeOf(IlvGanttChartForm::ClassInfo()) && IlFalse) {
	IlvGraphic* s = ((IlvGanttChartForm*)_gantt)->getCompositeScale();
	s->setPalette(_gantt->getGridPalette());
    }
    _gantt->getManager()->reDraw();
    _gantt->getGrapher()->reDraw();
}

// --------------------------------------------------------------------------
// The followings are callbacks defined for the toolbar:
// --------------------------------------------------------------------------
void ILVCALLBACK
OnCreateActivity(IlvGraphic* g,
		 IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setCreateActivity();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnCreateBreak(IlvGraphic* g,
	      IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setCreateBreak();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnCreateConstraint(IlvGraphic* g,
		   IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setCreateConstraint();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnSelect(IlvGraphic* g,
	 IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setSelect();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnPan(IlvGraphic* g,
      IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setPan();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnBorder(IlvGraphic* g,
	 IlAny)
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setBorder();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnDragAndDrop(IlvGraphic* g,
	      IlAny) 
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->setDragAndDrop();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnCreateRow(IlvGraphic* g,
	    IlAny) 
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->createRow();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnDeleteRow(IlvGraphic* g,
	    IlAny) 
{
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)g;
    toolbar->deleteRow();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnSetSubNodeGraphicModel(IlvGraphic* g,
			 IlAny) 
{
    IlvAbstractMenu* menu = (IlvAbstractMenu*)g;
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)menu->getParentMenu();
    toolbar->setSubNodeGraphicModel();
}

// --------------------------------------------------------------------------
void ILVCALLBACK
OnSetColor(IlvGraphic* g,
	   IlAny) 
{
    IlvAbstractMenu* menu = (IlvAbstractMenu*)g;
    IlvGanttToolBar* toolbar = (IlvGanttToolBar*)menu->getParentMenu();
    toolbar->setColor();
}
