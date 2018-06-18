// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/scrollhk.cpp
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
// Using the grapher to demonstrate ManagerHooks in a Motif application
// --------------------------------------------------------------------------

#include <ilviews/manager/all.h>
#include <ilviews/grapher/grapher.h>
#include <ilviews/grapher/inters.h>
#include <ilviews/graphics/all.h>
#include <ilviews/grapher/polylink.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xm/Xm.h>
#include <Xm/ScrolledW.h>
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <X11/StringDefs.h>

// --------------------------------------------------------------------------
// ScrollViewHook to attach scrollbars to an IlvView
// --------------------------------------------------------------------------
class ScrollViewHook
: public IlvManagerViewHook {
public:
    ScrollViewHook(IlvManager*   mgr,
		   IlvView*      view,
		   IlvSystemView vscroll,
		   IlvSystemView hscroll)
    : IlvManagerViewHook(mgr, view),
      _previousx(0),
      _previousy(0),
      _verticalSB(vscroll),
      _horizontalSB(hscroll)
    {
	initScrollBars();
    }
    // ____________________________________________________________
    virtual void transformerChanged(const IlvTransformer*,
				    const IlvTransformer*)
	{ adjustScrollBars(); }
    virtual void viewResized()
	{ adjustScrollBars(); }
    virtual void contentsChanged()
	{ adjustScrollBars(); }
    void initScrollBars();
    void adjustView();
    void adjustScrollBars();
protected:
    IlvPos        _previousx;
    IlvPos        _previousy;
    IlvSystemView _verticalSB;
    IlvSystemView _horizontalSB;
};

// --------------------------------------------------------------------------
// Quit from the Window Manager
// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny grapher)
{
    delete (IlvGrapher*)grapher;
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
AddTree(IlvGrapher* grapher)
{
    IlvDisplay* display = grapher->getDisplay();
    // Create a large tree
    char buffer[80];
    IlvGraphic* son,
              * node,
              * root = new IlvReliefLabel(display, IlvPoint(0,0), "Root");
    grapher->addNode(root, IlFalse, 1);
    for (int i = 0; i < 10; i++) {
	sprintf(buffer, "Node%d", i);
	node = new IlvLabel(display, IlvPoint(0, 0), buffer);
	grapher->addNode(node, IlFalse, 1);
	grapher->addLink(new IlvLinkImage(display, IlTrue, root, node),
			 IlFalse, 0);
	for (int j = 0; j < 10; j++) {
	    sprintf(buffer, "leaf %d", j);
	    son = new IlvLabel(display, IlvPoint(0, 0), buffer);
	    grapher->addNode(son, IlFalse, 1);
	    grapher->addLink(new IlvLinkImage(display, IlFalse, node, son),
			     IlFalse, 0);
	}
    }
    grapher->moveObject(root,   0, 200, IlFalse);
    grapher->nodeXPretty(root, 40,  20, IlFalse);
    // Readin a predefined graph
    grapher->read("graph.ilv");
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("IlvDemo", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create IlvDisplay");
	delete display;
	IlvExit(-1);
    }
    IlvGrapher* grapher = new IlvGrapher(display, 3);
    IlvView* topview = new IlvView(display, "Grapher", "Grapher",
				   IlvRect(100, 100, 640, 480), IlFalse);
    topview->setDestroyCallback(Quit, grapher);
    Widget scrollw = XtVaCreateManagedWidget("scrollw",
					     xmScrolledWindowWidgetClass,
					     (Widget)topview->getSystemView(),
					     XtNwidth, 640,
					     XtNheight, 480,
					     XmNtopAttachment, XmATTACH_FORM,
					     XmNleftAttachment, XmATTACH_FORM,
					     XmNbottomAttachment, XmATTACH_FORM,
					     XmNrightAttachment, XmATTACH_FORM,
					     XmNscrollingPolicy,
					     XmAPPLICATION_DEFINED,
					     (IlAny)0);
    Widget vscroll = XtVaCreateManagedWidget("vert", xmScrollBarWidgetClass,
					     scrollw,
					     XmNorientation, XmVERTICAL,
					     (IlAny)0);
    Widget hscroll = XtVaCreateManagedWidget("horiz", xmScrollBarWidgetClass,
					     scrollw,
					     XmNorientation, XmHORIZONTAL,
					     (IlAny)0);
    IlvView* grapherview = new IlvView(display, scrollw,
				       IlvRect(0, 0, 600, 500));
    XmScrolledWindowSetAreas(scrollw, hscroll, vscroll,
			     (Widget)grapherview->getSystemView());
    grapher->addView(grapherview);
    AddTree(grapher);

    topview->show();
    ScrollViewHook scrollHook(grapher, grapherview, vscroll, hscroll);
    grapher->installViewHook(&scrollHook);
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
void
ScrollViewHook::adjustScrollBars()
{
    IlvRect bbox;
    getManager()->computeBBox(bbox,
			      getManager()->getTransformer(getView()));
    IlvDim w, h;
    getView()->size(w, h);
    IlvRect visibleRect(0, 0, w, h);
    bbox.add(visibleRect); // In case the view is larger than its contents
    _previousx = -bbox.x();
    _previousy = -bbox.y();
    // Initialize ScrollBars
    XtVaSetValues((Widget)_verticalSB,
		  XmNminimum, 0,
		  XmNmaximum, bbox.h(),
		  XmNsliderSize, h,
		  XmNvalue, _previousy,
		  XmNpageIncrement, h / 2,
		  (IlAny)0);
    XtVaSetValues((Widget)_horizontalSB,
		  XmNminimum, 0,
		  XmNmaximum, bbox.w(),
		  XmNsliderSize, w,
		  XmNvalue, _previousx,
		  XmNpageIncrement, w / 2,
		  (IlAny)0);
}

// --------------------------------------------------------------------------
void
ScrollViewHook::adjustView()
{
    // Compute Scrollbars positions
    int scrollX, scrollY;
    int sd, in, p;
    XmScrollBarGetValues((Widget)_verticalSB, &scrollY, &sd, &in, &p);
    XmScrollBarGetValues((Widget)_horizontalSB, &scrollX, &sd, &in, &p);
    getManager()->translateView(getView(), -(scrollX - _previousx),
				-(scrollY - _previousy));
    IlvRect bbox;
    getManager()->computeBBox(bbox,
			      getManager()->getTransformer(getView()));
    IlvDim w,h;
    getView()->size(w, h);
    IlvRect visibleRect(0, 0, w, h);
    bbox.add(visibleRect); // In case the view is larger than its contents
    _previousx = - bbox.x();
    _previousy = - bbox.y();
}

// --------------------------------------------------------------------------
static void
ScrollVertical(Widget ,
	       XtPointer cdata,
	       XtPointer)
{
    ((ScrollViewHook*)cdata)->adjustView();
}

// --------------------------------------------------------------------------
static void
ScrollHorizontal(Widget,
		 XtPointer cdata,
		 XtPointer)
{
    ((ScrollViewHook*)cdata)->adjustView();
}

// --------------------------------------------------------------------------
void
ScrollViewHook::initScrollBars()
{
    XtAddCallback((Widget)_verticalSB, XmNdragCallback, ScrollVertical,
		  (XtPointer)this);
    XtAddCallback((Widget)_horizontalSB, XmNdragCallback, ScrollHorizontal,
		  (XtPointer)this);
    XtAddCallback((Widget)_verticalSB, XmNvalueChangedCallback,
		  ScrollVertical, (XtPointer)this);
    XtAddCallback((Widget)_horizontalSB, XmNvalueChangedCallback,
		  ScrollHorizontal, (XtPointer)this);
    adjustScrollBars();
}
