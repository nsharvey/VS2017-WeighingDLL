// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/manager.cpp
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
static const char* _data = "// Ilv Version: 2.0\n// File generated: Mon May  9 21:00:57 1994\n//  IlvGadgetManagerOutput\nPalettes 4\n3 54227 54227 54227  0 0 0  default 0 solid solid  0 0 0 \n2 48830 48830 48830  0 0 0  %helvetica-14- 0 solid solid  0 0 0 \n0 48830 48830 48830  0 0 0  %helvetica-14-B 0 solid solid  0 0 0 \n1 52368 52992 52992  0 0 0  default 0 solid solid  0 0 0 \nIlvObjects 9\n2 { 0 0 IlvButton 15 25 95 30 2 Y \"Show All\"  } 64 \"Button\"  4 \"showall\"   \n2 { 1 0 IlvButton 15 474 95 30 2 Y \"Quit\"  } 64 \"Button\"  132 \"quit\"  1  16  \n2 { 2 1 IlvManagerRectangle 123 19 477 501  } 32 \"mgr\"  960   1  0 1  0 2 2  \n2 { 3 0 IlvButton 15 430 95 30 2 Y \"Zoom Out\"  } 64 \"RButton\"  4 \"zoomout\"   \n2 { 4 0 IlvButton 15 369 95 30 2 Y \"Zoom In\"  } 64 \"RButton\"  4 \"zoomin\"   \n2 { 5 0 IlvGraphicSet 2\n2 IlvGadget 37 97 49 31 2  \n3 IlvPolygon 3 43 122 \n61 103 80 122  \n } 64 \"RButton\"  4 \"up\"   \n2 { 6 0 IlvGraphicSet 2\n2 IlvGadget 37 159 49 31 2  \n3 IlvPolygon 3 43 165 \n61 184 80 165  \n } 64 \"RButton\"  4 \"down\"   \n2 { 7 0 IlvGraphicSet 2\n2 IlvGadget 87 120 31 49 2  \n3 IlvPolygon 3 93 125 \n93 163 112 143  \n } 64 \"RButton\"  4 \"right\"   \n2 { 8 0 IlvGraphicSet 2\n2 IlvGadget 3 120 31 49 2  \n3 IlvPolygon 3 28 125 \n28 163 9 143  \n } 64 \"RButton\"  4 \"left\"   \n//Size 600 520\n";

#include <ilviews/contint.h>
#include <ilviews/allmgr.h>
#include <ilviews/allobj.h>
#include <ilviews/attach.h>
#include <ilviews/rectmgr.h>
#include <ilviews/sstream.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#if defined(ILVSTD)
using std::istrstream;
#endif

// --------------------------------------------------------------------------
// Quit from Window manager
static void ILVCALLBACK
Quit(IlvView* container, IlvAny)
{
    IlvDisplay* d = container->getDisplay();
    delete container;
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvGraphic* g, IlvAny)
{
    Quit(IlvContainer::getContainer(g), 0);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ShowAll(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    rectmgr->getManager()->fitTransformerToContents(rectmgr->getView(),
						    IlvTrue);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ScrollLeft(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->translateView(view, -(IlvPos)view->width()/3,0);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ScrollRight(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->translateView(view, (IlvPos)view->width()/3,0);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ScrollUp(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->translateView(view, 0, -(IlvPos)view->height()/3);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ScrollDown(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->translateView(view, 0, (IlvPos)view->height()/3);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ZoomIn(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->zoomView(view,
				    IlvPoint(view->width()/2,
					     view->height()/2),
				    (IlvFloat)2,
				    (IlvFloat)2);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ZoomOut(IlvGraphic* g, IlvAny)
{
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)IlvContainer::getContainer(g)->getObject("mgr");
    IlvView* view=rectmgr->getView();
    rectmgr->getManager()->zoomView(view,
				    IlvPoint(view->width()/2,
					     view->height()/2),
				    (IlvFloat)0.5,
				    (IlvFloat)0.5);
}

// --------------------------------------------------------------------------
static void
PopupManager(IlvDisplay* display)
{
    // Create a top view that contains the manager with 3 layers ~~~~~~~~~~
    IlvContainer* container = new IlvGadgetContainer(display,
						     "Manager Demo",
						     "Manager Demo",
						     IlvRect(0, 0, 400, 400),
						     IlvFalse, IlvFalse);
    istrstream stream((char*)_data); //(char*) for SunCC2.1
    container->read(stream);
    container->draw();
    IlvManagerRectangle* rectmgr =
	(IlvManagerRectangle*)container->getObject("mgr");
    IlvManager* manager     = rectmgr->getManager();
    IlvView*    managerview = rectmgr->getView();
    managerview->setBackground(display->getColor("blue"));
    manager->read("../DCW/browse.ilv");
    manager->fitTransformerToContents(managerview,IlvTrue);
    container->setDestroyCallback(Quit, manager);
    container->registerCallback("showall", ShowAll);
    container->registerCallback("zoomin",  ZoomIn);
    container->registerCallback("zoomout", ZoomOut);
    container->registerCallback("left",    ScrollLeft);
    container->registerCallback("up",      ScrollUp);
    container->registerCallback("right",   ScrollRight);
    container->registerCallback("down",    ScrollDown);
    container->registerCallback("quit",    Quit);
    container->show();
}

// **************************************************************************
int
main(int argc, char* argv[])
{
    // Create display connection ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvDisplay* display =  new IlvDisplay("IlvDemo", "", argc, argv);
    if (!display || display->isBad()) {
	if (display)
	    delete display;
	IlvFatalError("Couldn't create display");
	return 1;
    }
    PopupManager(display);
    IlvMainLoop();
    return 0;
}
