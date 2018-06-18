// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/simple/src/simple.cpp
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

#include <ilviews/graphics/attach.h>
#include <ilviews/gantt/ganttgrd.h>
#include <toolbar.h>
#include <utils.h>

static const char* title = "Rogue Wave Views Gantt chart simple demo";
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
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
			       IlvFalse);
    top->setDestroyCallback(Quit);

    // Creating Chart
    IlvGanttChart* gantt =
	new IlvGanttChart(display,
			  IlvRect(0, 32, 720, 344),
			  0,
			  500,
			  80,
			  420,
			  10,
			  80,
			  0,
			  14,
			  24,
			  12,
			  2,
			  6,
			  0,
			  10);

    // Create the toolbar
    IlvGanttToolBar* toolbar = new IlvGanttToolBar(display, gantt);
    top->addObject(toolbar);

    // Specify the new graphic models
    gantt->setSubNodeGraphicModel(CreateSubNodeGraphicModel(display));
    gantt->setLineGraphicModel(CreateLineGraphicModel(display));
    gantt->setLinkGraphicModel(CreateLinkGraphicModel(display));
    gantt->setBreakGraphicModel(CreateBreakGraphicModel(display));

    // Populate the Gantt chart with data
    PopulateGanttChart(gantt);

    // Disable the default grid
    gantt->showGrid(IlFalse, IlFalse);
    // Add horizontal grids
    IlvColor* steelblue3 = display->getColor("steelblue3");
    IlvColor* midnightblue = display->getColor("midnightblue");
    IlvPalette* gridPal = display->getPalette(steelblue3, midnightblue);
    IlvGanttLineGrid* linGrid = new IlvGanttLineReliefGrid(gantt, gridPal);
    gantt->setLineGrid(linGrid, IlFalse, 0);
    IlvGanttRowGrid* rowGrid = new IlvGanttRowGrid(gantt);
    gantt->setRowGrid(rowGrid, IlFalse, 0);

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

    // Make only one view visible
    gantt->moveHandle(IlvPoint(2000, 2000));
    
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
    gantt->setDoubleBuffering(IlTrue);

    // Running main loop
    IlvMainLoop();
    return 0;
}
