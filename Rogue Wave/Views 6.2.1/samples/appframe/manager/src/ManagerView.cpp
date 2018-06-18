// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/src/ManagerView.cpp
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
// IlogViews 4 generated source file
// File generated Wed Mar 08 20:35:33 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <ManagerView.h>
#include <ManagerDocument.h>
#include <ilviews/appframe/command.h>
#include <selinter.h>
#include <mgercmd.h>

// --------------------------------------------------------------------------
// MakeSelection

IlvDrawSelection*
MakeSelection(IlvManager* manager,
	      IlvGraphic* graphic)
{
    return new IlvReshapeSelection(
		    manager->getDisplay(),
		    graphic,
		    IlvDefaultSelectionSize,
		    (IlvPalette*)
			manager->getProperty(
				IlvGetSymbol("UnactiveSelectionPalette")));
}

// --------------------------------------------------------------------------
// ManagerView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(ManagerView)
    Action(Delete, deleteSelectedGraphics)
    RefreshAction(Delete, deleteUI)
    Action(Cut, cut)
    RefreshAction(Cut, deleteUI)
    Action(Paste, paste)
    Action(LayoutLeftAlign, alignLeft)
    Action(LayoutRightAlign, alignRight)
    Action(LayoutTopAlign, alignTop)
    Action(LayoutBottomAlign, alignBottom)
    Action(LayoutSameWidth, sameWidth)
    Action(LayoutSameHeight, sameHeight)
    Action(LayoutCenterVerticaly, centerVerticaly)
    Action(LayoutCenterHorizontaly, centerHorizontaly)
    RefreshAction(LayoutLeftAlign, alignmentUI)
    RefreshAction(LayoutRightAlign, alignmentUI)
    RefreshAction(LayoutTopAlign, alignmentUI)
    RefreshAction(LayoutBottomAlign, alignmentUI)
    RefreshAction(LayoutSameWidth, alignmentUI)
    RefreshAction(LayoutSameHeight, alignmentUI)
    RefreshAction(LayoutCenterVerticaly, alignmentUI)
    RefreshAction(LayoutCenterHorizontaly, alignmentUI)
    Action(Undo, undo)
    RefreshAction(Undo, setUndoUI)
    Action(Redo, redo)
    RefreshAction(Redo, setRedoUI)
IlvDvEndInterface1(IlvDvManagerView)

// --------------------------------------------------------------------------
// Constructor / destructor
ManagerView::ManagerView(IlvGadgetContainer* parent)
  : IlvDvManagerView(parent),
    _activeSelection(0),
    _activePalette(0),
    _unactivePalette(0)
{
    IlvDisplay* display = parent->getDisplay();
    _activePalette = display->getPalette(display->getColor("Blue"),
					 display->getColor("Black"));
    if (_activePalette)
	_activePalette->lock();

    _unactivePalette = display->getPalette(display->getColor("White"),
					   display->getColor("Black"));
    if (_unactivePalette)
	_unactivePalette->lock();
}

// --------------------------------------------------------------------------
ManagerView::~ManagerView()
{
    if (_activePalette)
	_activePalette->unLock();
    if (_unactivePalette)
	_unactivePalette->unLock();
}

// --------------------------------------------------------------------------
// Overridables
void
ManagerView::initializeView()
{
    IlvDvManagerView::initializeView();

    IlvDvManagerDocument* document = getManagerDocument();
    IlvManager* manager = document->getManager();
    
    // Attach a select Interactor to the view
    IlvAbstractView* view = IlvDvManagerView::getDvView();
    SelectInteractor* inter = new SelectInteractor(manager, this);
    manager->setInteractor(inter, (IlvView*)view);

    // Add selection
    manager->addProperty(IlvGetSymbol("UnactiveSelectionPalette"),
			 (IlAny)_unactivePalette);
    manager->addProperty(IlvGetSymbol("ActiveSelectionPalette"),
			 (IlAny)_activePalette);

    manager->setMakeSelection(MakeSelection);
}

// --------------------------------------------------------------------------
// Basic properties
ManagerDocument*
ManagerView::getManagerDocument() const
{
    return (ManagerDocument*)getDocument();
}

// --------------------------------------------------------------------------
void
ManagerView::deleteSelectedGraphics()
{
    if (!getManager()->numberOfSelections())
	return;
    getDocument()->doCommand(
	    new ManagerDeleteCommand(this, _activeSelection));
    _activeSelection = 0;
}

// --------------------------------------------------------------------------
void
ManagerView::cut()
{
    if (!getManager()->numberOfSelections())
	return;
    getManager()->copyToClipboard();
    deleteSelectedGraphics();
}

// --------------------------------------------------------------------------
void
ManagerView::paste()
{
    IlvView* view = (IlvView*)getDvView();
    IlvPos x, y;
    IlUShort unused;
    getDisplay()->queryPointer(x, y, unused);
    IlvRect bbox;
    view->globalBBox(bbox);
    IlvPoint newPosition(x - bbox.left(), y - bbox.top());
    if ((newPosition.x() < 0) || (newPosition.y() < 0) ||
	(newPosition.x() >= (IlvPos)view->width()) ||
	(newPosition.y() >= (IlvPos)view->height()))
        newPosition.move(0, 0);
    getManager()->pasteFromClipboard(view, newPosition);

    // Set active last inserted object
    IlvUInt nSelections;
    IlvGraphic* const* selections = getManager()->getSelections(nSelections);
    if (nSelections) {
	IlvGraphic* graphic = selections[nSelections - 1];
	_activeSelection = 0;
	setActiveSelection(graphic);
    }
}

// --------------------------------------------------------------------------
void
ManagerView::deleteUI(IlvDvActionDescriptor* desc)
{
    desc->setValid(getManager() && getManager()->numberOfSelections());
}

// --------------------------------------------------------------------------
// align
void
ManagerView::align(IlvPosition side)
{
    IlvUInt nbSelection =
	getManager()? getManager()->numberOfSelections() : 0;
    if (nbSelection < 2)
	return;
    getDocument()->doCommand(
	new ManagerAlignCommand(getManager(), _activeSelection, side));
}

// --------------------------------------------------------------------------
// alignLeft
void
ManagerView::alignLeft()
{
    align(IlvLeft);
}

// --------------------------------------------------------------------------
void
ManagerView::alignRight()
{
    align(IlvRight);
}

// --------------------------------------------------------------------------
void
ManagerView::alignTop()
{
    align(IlvTop);
}

// --------------------------------------------------------------------------
void
ManagerView::alignBottom()
{
    align(IlvBottom);
}

// --------------------------------------------------------------------------
void
ManagerView::sameWidth()
{
    align(IlvHorizontal);
}

// --------------------------------------------------------------------------
void
ManagerView::sameHeight()
{
    align(IlvVertical);
}

// --------------------------------------------------------------------------
void
ManagerView::centerVerticaly()
{
    align(ManagerAlignCommand::CenterVerticaly);
}

// --------------------------------------------------------------------------
void
ManagerView::centerHorizontaly()
{
    align(ManagerAlignCommand::CenterHorizontaly);
}

// --------------------------------------------------------------------------
void
ManagerView::alignmentUI(IlvDvActionDescriptor* desc) const
{
    IlvManager* manager = getManager();
    IlUInt nbSelection = manager->numberOfSelections();
    desc->setValid(nbSelection > 1);
}

// --------------------------------------------------------------------------
void
ManagerView::reDrawSelection(IlvDrawSelection* drawSelection)
{
    IlvRect bbox;
    drawSelection->boundingBox(bbox,
	getManager()->getTransformer((IlvView*)getDvView()));
    getManager()->bufferedDraw((IlvView*)getDvView(), bbox);
}

// --------------------------------------------------------------------------
void
ManagerView::setActiveSelection(IlvGraphic* graphic)
{
    if (graphic == _activeSelection)
	return;
    unactiveSelection();
    _activeSelection = graphic;
    IlvDrawSelection* drawSelection =
		    getManager()->getSelection(_activeSelection);
    if (drawSelection) {
	drawSelection->setPalette(_activePalette);
	reDrawSelection(drawSelection);
    }
}

// --------------------------------------------------------------------------
void
ManagerView::unactiveSelection()
{
    if (!_activeSelection)
	return;
    IlvDrawSelection* drawSelection =
		    getManager()->getSelection(_activeSelection);
    if (drawSelection) {
	drawSelection->setPalette(_unactivePalette);
	reDrawSelection(drawSelection);
    }
}

// --------------------------------------------------------------------------
void
ManagerView::removedFromSelection(IlvGraphic* graphic)
{
    if (graphic == _activeSelection) {
	IlUInt count;
	IlvGraphic* const* selections = getManager()->getSelections(count);
	if (count) {
	    _activeSelection = 0;
	    setActiveSelection(selections[count - 1]);
	} else
	    _activeSelection = 0;
    }
}

// --------------------------------------------------------------------------
void
ManagerView::doTranslate(const IlvPoint& point)
{
    IlvTransformer* t = getManager()->getTransformer(this);
    getDocument()->doCommand(
		new TranslateSelectionCommand(getManager(), point, t));
}

// --------------------------------------------------------------------------
void
ManagerView::doReshape(IlvGraphic* graphic,
		       const IlvRect& rect)
{
    getDocument()->doCommand(
		new ReshapeCommand(getManager(), graphic, rect));
}

// --------------------------------------------------------------------------
void
ManagerView::selectionChanged()
{
    getDvApplication()->refreshAction("LayoutLeftAlign");
    getDvApplication()->refreshAction("LayoutRightAlign");
    getDvApplication()->refreshAction("LayoutTopAlign");
    getDvApplication()->refreshAction("LayoutBottomAlign");
    getDvApplication()->refreshAction("LayoutSameWidth");
    getDvApplication()->refreshAction("LayoutSameHeight");
    getDvApplication()->refreshAction("LayoutCenterVerticaly");
    getDvApplication()->refreshAction("LayoutCenterHorizontaly");
}

// --------------------------------------------------------------------------
void
ManagerView::undo()
{
    getDocument()->IlvDvDocument::undo();
}

// --------------------------------------------------------------------------
void
ManagerView::setUndoUI(IlvDvActionDescriptor* desc)
{
    desc->setValid(getDocument()->canUndo());
}


// --------------------------------------------------------------------------
void
ManagerView::setRedoUI(IlvDvActionDescriptor* desc)
{
    desc->setValid(getDocument()->canRedo());
}

// --------------------------------------------------------------------------
void
ManagerView::redo()
{
    getDocument()->IlvDvDocument::redo();
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterViewClass(ManagerView, IlvDvManagerView);

IL_BEGINMODULEINITDEF(ManagerView)
    IlvDvPostRegisterViewClass(ManagerView, IlvDvManagerView);
IL_ENDMODULEINITDEF(ManagerView)

#if !defined(ILVBUILDLIBS)
static int ManagerView_ini = (IL_MODINIT(ManagerView)(), 0);
#endif
