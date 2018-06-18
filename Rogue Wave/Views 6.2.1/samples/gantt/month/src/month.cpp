// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/month/src/month.cpp
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

#include <ilviews/base/memory.h>
#include <ilviews/grapher/grapher.h>
#include <ilviews/graphics/set.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gantt/ganttint.h>
#include <ilviews/gantt/ganttgrd.h>
#include <monthgantt.h>
#include <month.h>

#if defined(IL_STD)
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>
IL_STDUSE
#else  /* !IL_STD */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#endif /* !IL_STD */

static const char* title = "Rogue Wave Views Gantt month demo";

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Create the display
    IlvDisplay* display = new IlvDisplay(title, 0, argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        if (display)
	    delete display;
        return -1;
    }

    // Add the path to toolbar files
    AppendGanttDataPath(display);

    // Creating top view
    IlvGadgetContainer* top =
        new IlvGadgetContainer(display,
			       "GanttChart",
			       title,
			       IlvRect(200, 100, 720, 376),
			       IlFalse);
    top->setDestroyCallback(Quit);

    IlInt start, end;
    IlUShort step, day;
    IlvGanttComputeDay(3, 2002, day, start, end, step);

    // Creating Chart
    MonthGanttChart* gantt =
        new MonthGanttChart(display,
			    IlvRect(0, 32, 720, 344),
			    start,
			    end,
			    step,
			    day,
			    160);

    // Create the toolbar
    IlvGanttToolBar* toolbar = new MonthToolBar(display, gantt);
    top->addObject(toolbar);

    // Specify the new graphic models
    gantt->setSubNodeGraphicModel(CreateSubNodeGraphicModel(display));
    gantt->setLineGraphicModel(CreateLineGraphicModel(display));
    gantt->setLinkGraphicModel(CreateDoubleLinkGraphicModel(display));
    gantt->setBreakGraphicModel(CreateBreakGraphicModel(display));

    // Populate the Gantt chart with data
    PopulateGanttChart(gantt, start, end, 12L);

    // Add horizontal grids
    IlvColor* steelblue3 = display->getColor("steelblue3");
    IlvColor* midnightblue = display->getColor("midnightblue");
    IlvPalette* gridPal = display->getPalette(steelblue3, midnightblue);
    IlvGanttLineGrid* linGrid = new IlvGanttLineReliefGrid(gantt, gridPal);
    gantt->setLineGrid(linGrid, IlFalse, 0);

    // Attach the toolbar
    IlvSetAttachment(toolbar, IlvTop, IlvFixedAttach, 0);
    IlvSetAttachment(toolbar, IlvLeft, IlvFixedAttach);
    IlvSetAttachment(toolbar, IlvRight, IlvFixedAttach);
    IlvSetAttachment(toolbar, IlvHorizontal, IlvElasticAttach);

    // Attach the Gantt chart
    IlvSetAttachment(gantt, IlvTop, IlvFixedAttach, 32);
    IlvSetAttachment(gantt, IlvBottom, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvLeft, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvRight, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvVertical, IlvElasticAttach);
    IlvSetAttachment(gantt, IlvHorizontal, IlvElasticAttach);

    // Add the Gantt chart
    top->addObject(gantt);
    // Showing top view
    top->show();
    
    // Color customizations
    IlvColor* cyan = display->getColor("cyan");
    IlvColor* darkorange = display->getColor("darkorange");
    IlvColor* steelblue4 = display->getColor("steelblue4");
    IlvPalette* pal = display->getPalette(cyan, darkorange);
    gantt->getScale(0)->setPalette(pal);
    gantt->getScale(1)->setPalette(pal);
    gantt->setBackground(steelblue4);
    gantt->getManagerView(0)->setBackground(steelblue4);
    gantt->getManagerView(1)->setBackground(steelblue4);
    IlvColor* antiquewhite = display->getColor("antiquewhite");
    gantt->getGridPalette()->setBackground(antiquewhite);

    // Enable the default grid
    gantt->showGrid(IlTrue, IlTrue);

    // Enable double buffering
    gantt->setDoubleBuffering(IlTrue);

    // Make only one view visible
    gantt->moveHandle(IlvPoint(2000, 2000));

    // Running main loop
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
IlUShort
MonthToolBar::getLinkType()
{
    if (!_dialog) {
	_dialog = new IlvDialog(getDisplay(),
				"Link Type",
				"Link Type",
				"linkty.ilv",
				0 /* IlvNoResizeBorder */,
				0,
				getHolder()->getView()->getSystemView());
	IlvSelector* selector = (IlvSelector*)_dialog->getObject("selector");
	selector->setSelected(selector->getObject(0));
    }
    _dialog->setFocus(_dialog->getObject("apply"));
    _dialog->moveToMouse();
    _dialog->showModal();
    return ((IlvSelector*)_dialog->getObject("selector"))->whichSelected();
}

// --------------------------------------------------------------------------
MonthToolBar::MonthToolBar(IlvDisplay* display, IlvGanttChart* gantt)
    : IlvGanttToolBar(display, gantt),
      _dialog(0)
{
}

// --------------------------------------------------------------------------
MonthToolBar::~MonthToolBar()
{
    if (_dialog)
	delete _dialog;
}

// --------------------------------------------------------------------------
void
MonthToolBar::setCreateConstraint()
{
    removeAllInteractors();
    IlvGanttLinkType type = (IlvGanttLinkType)getLinkType();
    IlvGrapher* grapher = getGanttChart()->getGrapher();
    for (IlUShort i = 0; i < 4; i++) {
	IlvView* view = getGanttChart()->getGrapherView(i);
	IlvManagerViewInteractor* inter =
	    new AddLinkInteractor(getGanttChart(), grapher, view, type);
	grapher->setInteractor(inter);
    }
}

// --------------------------------------------------------------------------
void
DoubleLink::draw(IlvPort* dst,
		 const IlvTransformer* t,
		 const IlvRegion* clip) const
{
    IlUInt   nPoints;
    IlvPoint* points = getLinkPoints(nPoints, t);
    IlvPushClip pushClip(*_palette, clip);
    dst->drawPolyLine(_palette, nPoints, points);
    if (_oriented) {
	dst->drawArrow(_palette,
		       points[nPoints - 2],
		       points[nPoints - 1],
		       1.0);
    }
}

// --------------------------------------------------------------------------
void
DoubleLink::boundingBox(IlvRect& rect, const IlvTransformer* t) const
{
    IlvNDoubleLinkImage::boundingBox(rect, t);
    IlUShort lw = getPalette()->getLineWidth();
    rect.translate(-(IlvPos)lw, -(IlvPos)lw);
    rect.grow((IlvDim)(2 * lw), (IlvDim)(2 * lw));
}

// ---------------------------------------------------------------------------
IlvPoint*
DoubleLink::getLinkPoints(IlUInt& nPoints, const IlvTransformer* t) const
{
    IlvSymbol* symbol = IlvGetSymbol("Gantt", IlvFalse);
    IlvGanttChart* gantt;
    IlvGanttLink* link;
    if (!symbol ||
	((gantt = (IlvGanttChart*)getProperty(symbol)) == 0) ||
	((link = (IlvGanttLink*)gantt->getObject(this)) == 0))
	return IlvNDoubleLinkImage::getLinkPoints(nPoints, t);
    nPoints = 4;
    IlvPoint* points = IlvAllocPoints(4);
    IlvRect fromrect, torect;
    getFrom()->boundingBox(fromrect, t);
    getTo()->boundingBox(torect, t);
    IlvPos midx;
    switch (link->getType()) {
    case IlvStartsAfterEnd:
    case IlvStartsAtEnd:
	midx = (fromrect.right()+torect.x())/2;
	points[0].move(fromrect.right(), fromrect.centery());
	points[1].move(midx, fromrect.centery());
	points[2].move(midx, torect.centery());
	points[3].move(torect.x(), torect.centery());
	break;
    case IlvStartsAfterStart:
    case IlvStartsAtStart:
	midx = IlvMin(fromrect.x(), torect.x()) - 6;
	points[0].move(fromrect.x(), fromrect.centery());
	points[1].move(midx, fromrect.centery());
	points[2].move(midx, torect.centery());
	points[3].move(torect.x(), torect.centery());
	break;
    case IlvEndsAfterStart:
    case IlvEndsAtStart:
	midx = (fromrect.x()+torect.right())/2;
	points[0].move(fromrect.x(), fromrect.centery());
	points[1].move(midx, fromrect.centery());
	points[2].move(midx, torect.centery());
	points[3].move(torect.right(), torect.centery());
	break;
    case IlvEndsAfterEnd:
    case IlvEndsAtEnd:
	midx = IlvMax(fromrect.right(), torect.right()) + 6;
	points[0].move(fromrect.right(), fromrect.centery());
	points[1].move(midx, fromrect.centery());
	points[2].move(midx, torect.centery());
	points[3].move(torect.right(), torect.centery());
	break;
    }
    return points;
}

// --------------------------------------------------------------------------
IlvGraphic*
DoubleLink::copy() const
{
    return new DoubleLink(getDisplay(), _oriented, 0, 0, getPalette());
}

// --------------------------------------------------------------------------
IlvGraphic*
DoubleLink::read(IlvInputFile &is, IlvPalette *pal)
{
    int ir;
    is.getStream() >> ir;
    IlBoolean oriented = ir ? IlTrue : IlFalse;
    IlvGraphic * from, * to;
    from = is.readReference(pal->getDisplay());
    to   = is.readReference(pal->getDisplay());
    return new DoubleLink(pal->getDisplay(), oriented, from, to, pal);
}

// --------------------------------------------------------------------------
IlvGanttLink*
AddLinkInteractor::makeLink(IlvGanttNode* from, IlvGanttNode* to)
{
    return new IlvGanttLink(from, to, _type);
}

// --------------------------------------------------------------------------
//$doc:CrLGrM
IlvGraphic*
CreateDoubleLinkGraphicModel(IlvDisplay* display)
{
    IlvColor* red = display->getColor("red");
    IlvColor* black = display->getColor("black");
    IlvPalette* palette = display->getPalette(black, red);
    palette->lock();
    IlvGraphic* model = new DoubleLink(display, IlTrue, 0,0, palette);
    palette->unLock();
    return model;
}
//end:CrLGrM

// --------------------------------------------------------------------------
#if defined(linux) || defined(__TCPLUSPLUS__)
IlvPreRegisterClass(DoubleLink);
static int initDoubleLink()
{ IlvPostRegisterClass(DoubleLink, IlvNDoubleLinkImage); return 0; }
static int _initDoubleLink = initDoubleLink();
#else  /* !linux && !defined(__TCPLUSPLUS__) */
IlvRegisterClass(DoubleLink, IlvNDoubleLinkImage);
#endif /* !linux && !defined(__TCPLUSPLUS__) */
