// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/ATLstep2/ctrl.cpp
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
#include "ctrl.h"
#include <ilviews/graphics/inter.h>
#include <ilviews/manager/all.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/graphics/all.h>	// Force to link all the graphic objects.
#include <ilviews/gadgets/all.h>	// Force to link all the gadget objects.

namespace {
const char CtrlDataFile[] = "data/ctrl.ilv";
const char MgrDataFile[]  = "data/browse.ilv";
const char ManagerName[]  = "Manager";

// --------------------------------------------------------------------------
// Quit from Window manager
void ILVCALLBACK
Quit(IlvView* container, IlvAny)
{
    IlvDisplay* d = container->getDisplay();
    delete container;
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
Quit(IlvGraphic* g, IlvAny)
{
    Quit(IlvContainer::getContainer(g), 0);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ShowAll(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    ctrl->getManager()->fitTransformerToContents(ctrl->getManagerView(),
						 IlvTrue);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ScrollLeft(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->translateView(view, -(IlvPos)view->width()/3,0);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ScrollRight(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->translateView(view, (IlvPos)view->width()/3,0);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ScrollUp(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->translateView(view, 0, -(IlvPos)view->height()/3);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ScrollDown(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->translateView(view, 0, (IlvPos)view->height()/3);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ZoomIn(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->zoomView(view,
				 IlvPoint(view->width()/2, view->height()/2),
				 (IlvFloat)2,
				 (IlvFloat)2);
}

// --------------------------------------------------------------------------
void ILVCALLBACK
ZoomOut(IlvGraphic* g, IlvAny)
{
    Ctrl* ctrl = static_cast<Ctrl*>(IlvContainer::getContainer(g));
    IlvView* view = ctrl->getManagerView();
    ctrl->getManager()->zoomView(view,
				 IlvPoint(view->width()/2, view->height()/2),
				 (IlvFloat)0.5,
				 (IlvFloat)0.5);
}
} // End anonym namespace.

// --------------------------------------------------------------------------
Ctrl::Ctrl(IlvDisplay* display, const IlvRect& size, const char* filename)
: IlvGadgetContainer(display,
		     "Manager Demo",
		     "Manager Demo",
		     size,
		     IlvFalse,
		     IlvFalse)
{
    init(filename);
    setDestroyCallback(Quit, _manager);
}

// --------------------------------------------------------------------------
Ctrl::Ctrl(IlvDisplay*		display,
	   IlvSystemView	parent,
	   const IlvRect&	size,
	   const char*		filename)
    : IlvGadgetContainer(display, parent, size)
{
    init(filename);
    // No need for quit.
    IlvGraphic* quit = getObject("Quit");
    setVisible(quit, IlvFalse, IlvTrue);
}

// --------------------------------------------------------------------------
Ctrl::Ctrl(IlvDisplay* display, IlvSystemView parent, const char* filename)
    : IlvGadgetContainer(display, parent)
{
    init(filename);
    // No need for quit.
    IlvGraphic* quit = getObject("Quit");
    setVisible(quit, IlvFalse, IlvTrue);
}

// --------------------------------------------------------------------------
void
Ctrl::init(const char* filename)
{
    readFile(CtrlDataFile);
    draw();
    _managerRectangle = (IlvManagerRectangle*)getObject("Manager");
    _manager	      = _managerRectangle->getManager();
    _managerView      = _managerRectangle->getView();
    _managerView->setBackground(getDisplay()->getColor("blue"));
    _manager->read((filename && *filename) ? filename : MgrDataFile);
    _manager->fitTransformerToContents(_managerView, IlvTrue);
    registerCallback("showall", ShowAll);
    registerCallback("zoomin",  ZoomIn);
    registerCallback("zoomout", ZoomOut);
    registerCallback("left",    ScrollLeft);
    registerCallback("up",      ScrollUp);
    registerCallback("right",   ScrollRight);
    registerCallback("down",    ScrollDown);
    registerCallback("quit",    Quit);
    show();
}
