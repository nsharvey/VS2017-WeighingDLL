// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/manager/src/draw.cpp
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
// Small example of a basic drawing editor
// --------------------------------------------------------------------------

#include <ilviews/base/pathname.h>
#include <ilviews/graphics/all.h>
#include <ilviews/graphics/zoomlab.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/manager/all.h>

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/combo.h>

#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/gadmgr/mviselect.h>
#include <ilviews/gadmgr/strinter.h>

#include <ilviews/bitmaps/png.h>

static IlList		allInters;
static const char*	title		= "Simple Drawing Editor";
static const char*	PanelFileName	= "data/mgrdraw.ilv";
static const IlUShort	ColorsCount	= 13;
static const char*	ColorNames[]	= {
    "black",
    "red",
    "lightsteelblue",
    "pink",
    "gold",
    "wheat",
    "cornflowerblue",
    "yellow",
    "palegreen",
    "salmon",
    "magenta",
    "blue",
    "white"
};

// --------------------------------------------------------------------------
class IlvManagerMakeZoomableLabelInteractor
    : public IlvManagerMakeLabelInteractor
{
public:
    IlvManagerMakeZoomableLabelInteractor(IlvManager* manager, IlvView* eview)
        : IlvManagerMakeLabelInteractor(manager, eview)
    {}
    IlvManagerMakeZoomableLabelInteractor()
        : IlvManagerMakeLabelInteractor()
    {}

    virtual void doIt(const char* buffer);
};

// --------------------------------------------------------------------------
void
IlvManagerMakeZoomableLabelInteractor::doIt(const char* buffer)
{
    if (_label)
	IlvManagerMakeLabelInteractor::doIt(buffer);
    else {
	IlvGraphic* obj =
	    new IlvZoomableLabel(manager()->getDisplay(),
				 _position,
				 buffer,
				 manager()->getCreatorPalette());
	manager()->deSelect();
	manager()->addObject(obj);
	manager()->makeSelected(obj);
    }
    callPrevious();
}

// --------------------------------------------------------------------------
// - Quit the application
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny arg)
{
    IlvManager* manager = IL_CAST(IlvManager*, arg);
    manager->setInteractor(0, manager->getFirstView());
    IlvManagerViewInteractor* inter;
    IlMapList(&allInters,
	      IlvManagerViewInteractor*,
	      inter,
	      delete inter);
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Create the editing modes and link them to the toolbar
static void
CreateEditingModes(IlvManager* mgr, IlvView* view, IlvToolBar* toolBar)
{
    IlvMenuItemSelector* selector = 
	IL_CAST(IlvMenuItemSelector*,
		IlvMenuItemSelector::Get(toolBar,
					 IlSymbol::Get("EditingMode",
						       IlFalse)));
    if (!selector)
	return; // Bad data file
    IlvManagerViewInteractorSelector* interSelector =
	new IlvManagerViewInteractorSelector(mgr, view, selector);
    mgr->installViewHook(interSelector);

#define EDITMODE(name, inter)					\
    interSelector->link(IlSymbol::Get(name, IlFalse), inter);	\
    allInters.append((IlAny)inter);
    
    IlvSelectInteractor* select = new IlvSelectInteractor(mgr, view);
    select->opaqueMove(IlTrue);
    select->opaqueReshape(IlTrue);

    EDITMODE("Select", select);
    
    IlvManagerViewInteractor* inter;
    inter = new IlvMakeZoomInteractor(mgr, view);
    EDITMODE("ZoomIn", inter);
    inter = new IlvMakeUnZoomInteractor(mgr, view);
    EDITMODE("ZoomOut", inter);
    
    inter = new IlvMakeLineInteractor(mgr, view);
    EDITMODE("MakeLine", inter);
    inter = new IlvMakeArrowLineInteractor(mgr, view);
    EDITMODE("MakeArrowLine", inter);
   
    inter = new IlvMakeRectangleInteractor(mgr, view);
    EDITMODE("MakeRectangle", inter);
    inter = new IlvMakeFilledRectangleInteractor(mgr, view);
    EDITMODE("MakeFilledRectangle", inter);
    inter = new IlvMakeShadowRectangleInteractor(mgr, view);
    EDITMODE("MakeShadowRectangle", inter);
    inter = new IlvMakeReliefRectangleInteractor(mgr, view);
    EDITMODE("MakeReliefRectangle", inter);
    
    inter = new IlvMakeArcInteractor(mgr, view);
    EDITMODE("MakeArc", inter);
    inter = new IlvMakeFilledArcInteractor(mgr, view);
    EDITMODE("MakeFilledArc", inter);
    
    inter = new IlvMakePolylineInteractor(mgr, view);
    EDITMODE("MakePolyline", inter);
    inter = new IlvMakePolygonInteractor(mgr, view);
    EDITMODE("MakePolygon", inter);
    
    inter = new IlvMakeSplineInteractor(mgr, view);
    EDITMODE("MakeSpline", inter);
    inter = new IlvMakeClosedSplineInteractor(mgr, view);
    EDITMODE("MakeClosedSpline", inter);
    inter = new IlvMakeFilledSplineInteractor(mgr, view);
    EDITMODE("MakeFilledSpline", inter);

    inter = new IlvManagerMakeLabelInteractor(mgr, view);
    EDITMODE("MakeLabel", inter);
    inter = new IlvManagerMakeZoomableLabelInteractor(mgr, view);
    EDITMODE("MakeZoomableLabel", inter);

    inter = new IlvRotateInteractor(mgr, view);
    EDITMODE("Rotate", inter);

    mgr->setInteractor(IL_CAST(IlvManagerViewInteractor*, allInters[0]));
}


// --------------------------------------------------------------------------
// Handling of objects colors.
// --------------------------------------------------------------------------
static void
ApplyValue (IlvGraphic* g, IlAny v)
{
    g->changeValue(*(IlvValue*)v);
}

// --------------------------------------------------------------------------
static void
UpdateCreatorPalette(const IlvToolBar* toolBar) 
{
    IlvManager* mgr = IL_CAST(IlvManager*, toolBar->getClientData());
    IlvColor* fg =
	IL_CAST(IlvColor*,
		toolBar->getItemByName("Foreground")->getClientData());
    IlvColor* bg =
	IL_CAST(IlvColor*,
		toolBar->getItemByName("Background")->getClientData());
    mgr->setCreatorPalette(mgr->getDisplay()->getPalette(bg, fg));
}

// --------------------------------------------------------------------------
static void
ChangeColor(IlvManager* mgr, IlvGadgetItem* item)
{
    const char* valName = !strcmp(item->getName(), "Foreground")
	? "foreground"
	: "background";
    IlvColor* color = IL_CAST(IlvColor*, item->getClientData());
    IlvValue v(valName, color);
    mgr->applyToSelections(ApplyValue, &v, IlTrue);
}

// --------------------------------------------------------------------------
static void
ChangeColorCB(IlvGraphic* g, IlAny) 
{
    IlvManager* mgr = IL_CAST(IlvManager*, g->getClientData());
    IlvGadgetItem* item = IL_CAST(IlvToolBar*, g)->getCallbackItem();
    ChangeColor(mgr, item);
}

// --------------------------------------------------------------------------
static void
ChangeSelectionColorCB(IlvGraphic* g, IlAny arg) 
{
    IlvPopupMenu* menu  = IL_CAST(IlvPopupMenu*, g);
    IlvMenuItem*  item  = IL_CAST(IlvMenuItem*, arg);
    IlvColor*     color =
	IL_CAST(IlvColor*,
		menu->getItem(menu->whichSelected())->getClientData());
    item->getGraphic()->setForeground(color);
    item->setClientData(color);
    item->reDraw();
    ChangeColor(IL_CAST(IlvManager*, g->getClientData()), item);
    UpdateCreatorPalette(IL_CAST(const IlvToolBar*,
				 item->getHolder()->getGadget()));
}

// --------------------------------------------------------------------------
static void
CreateResourceMenus(IlvManager* mgr, IlvView*, IlvToolBar* toolBar)
{
    IlvDisplay* display = toolBar->getDisplay();
    IlvMenuItem* fgItem = 
	IL_CAST(IlvMenuItem*, toolBar->getItemByName("Foreground"));
    IlvPopupMenu* fgMenu = 
	IL_CAST(IlvMenuItem*,
		toolBar->getItemByName("ForegroundMenu"))->getMenu();
    IlvMenuItem* bgItem = 
	IL_CAST(IlvMenuItem*, toolBar->getItemByName("Background"));
    IlvPopupMenu* bgMenu = 
	IL_CAST(IlvMenuItem*,
		toolBar->getItemByName("BackgroundMenu"))->getMenu();

    IlvGadgetItem* fgItems[ColorsCount];
    IlvGadgetItem* bgItems[ColorsCount];
    IlUShort i;
    IlvColor* color;
    IlvPalette* pal;
    for (i = 0; i < ColorsCount; ++i) {
	fgItems[i] = new IlvMenuItem(ColorNames[i]);
	color = display->getColor(ColorNames[i]);
	pal = display->getPalette(0, color);
	fgItems[i]->setGraphic(new IlvFilledRectangle(display,
						      IlvRect(0, 0, 16, 16),
						      pal));
	bgItems[i] = fgItems[i]->copy();
	fgItems[i]->setClientData(color);
	bgItems[i]->setClientData(color);
    }
    fgMenu->setItems(fgItems, ColorsCount);
    bgMenu->setItems(bgItems, ColorsCount);

    fgMenu->addCallback(ChangeSelectionColorCB, fgItem);
    bgMenu->addCallback(ChangeSelectionColorCB, bgItem);
    
    pal = mgr->getCreatorPalette();
    fgItem->getGraphic()->setForeground(pal->getForeground());
    fgItem->setClientData(pal->getForeground());
    bgItem->getGraphic()->setForeground(pal->getBackground());
    bgItem->setClientData(pal->getBackground());
    fgItem->setCallback(ChangeColorCB);
    bgItem->setCallback(ChangeColorCB);

    toolBar->setClientData(mgr);
    fgMenu->setClientData(mgr);
    bgMenu->setClientData(mgr);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Draw", "", argc, argv);
    if (display->isBad()) {
        if (display)
	    delete display;
	IlvFatalError("Could not create display");
	return -1;
    }

    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/manager/manager");
    display->prependToPath(localPath);

    IlvRect size(0, 0, 640, 480);
    IlvGadgetContainer* panel = 
	new IlvGadgetContainer(display, title, title, size, IlFalse, IlFalse);
    panel->allowFocus(IlFalse);

    IlvToolBar* toolBar = 0;
    IlvSCManagerRectangle* mgrRect = 0;
    IlBoolean ok = panel->readFile(PanelFileName);
    if (ok) {
	mgrRect =
	    IL_CAST(IlvSCManagerRectangle*, panel->getObject("ManagerRect"));
	toolBar =
	    IL_CAST(IlvToolBar*, panel->getObject("Toolbar"));
    }        
    
    if (!mgrRect || !toolBar) {
	IlvFatalError("Bad data file %s", PanelFileName);
	delete display;
	return 1;
    }

    IlvManager* mgr  = mgrRect->getManager();
    IlvView* mgrView = mgrRect->getView();  
    mgr->setDoubleBuffering(mgrView, IlTrue);
    CreateEditingModes(mgr, mgrView, toolBar);
    CreateResourceMenus(mgr, mgrView, toolBar);

    panel->setDestroyCallback(Quit, mgr);
    panel->show();
    IlvMainLoop();
    return 0;
}
