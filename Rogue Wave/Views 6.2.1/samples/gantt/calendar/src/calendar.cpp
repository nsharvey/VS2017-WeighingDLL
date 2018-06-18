// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/calendar/src/calendar.cpp
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

#include <stdio.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gantt/ganttfrm.h>
#include <ilviews/gantt/ganttgrd.h>
#include <toolbar.h>
#include <utils.h>

// --------------------------------------------------------------------------
static const char* title = "Rogue Wave Views Gantt calendar sample";

// --------------------------------------------------------------------------
// Specify the range and the step of the gantt and the node minimum size
static IlInt    start          = 0L;
static IlInt    end            = 91*24L;
static IlUShort step           = (IlUShort)24L;
static IlInt    subNodeMinSize = 18L;

// --------------------------------------------------------------------------
IlvGraphic*
CreateResourceGraphicModel(IlvDisplay* display)
{
    IlvRect rect(0, 0, 800, 40);
    IlvPalette*	palette = display->defaultPalette();
    palette->lock();
    IlvGanttResourceLine* matrix =
	new IlvGanttResourceLine(display,
				 rect,
				 4,
				 1,
				 IlvDefaultMatrixWidth,
				 IlvDefaultMatrixWidth,
				 IlvDefaultGadgetThickness,
				 IlFalse, IlFalse,
				 palette);
    palette->unLock();

    matrix->useRelief(IlFalse);
    matrix->setTransparent(IlTrue);

    matrix->add(new IlvLabelMatrixItem(""));
    matrix->add(new IlvLabelMatrixItem(""));
    matrix->add(new IlvLabelMatrixItem(""));
    matrix->add(new IlvLabelMatrixItem(""));

    matrix->setTransparent(IlTrue);
    matrix->showFrame(IlFalse, IlFalse);
    matrix->setItemAlignment(0, 0, IlvLeft);

    matrix->setItemReadOnly(0,0, IlFalse);

    matrix->allowEdit(IlTrue);
    matrix->setDirectEditionMode(IlTrue);

    matrix->showGrid(IlFalse);
    matrix->setSpacing(0);
    matrix->setThickness(0);

    matrix->setExclusive(IlTrue);

    matrix->resizeColumn(1, 196);
    matrix->resizeColumn(2, 80);
    matrix->resizeColumn(3, 32);
    matrix->resizeColumn(4, 32);

    RegisterGanttNameProperty(matrix);
    return matrix;
}

// --------------------------------------------------------------------------
IlvTimeConverter* CreateTimeConverter()
{
    IlDateErrorCode error(IL_DATE_ZERO_ERROR);
    IlGregorianCalendar cal(error);
    cal.set(2002, 0, 1, 0, 0, 0);
    IlvLinearTimeConverter* tc = new IlvLinearTimeConverter();
    tc->setReferenceTime(cal.getTime(error));
    tc->setUnitDuration(IlvDuration(60.0 * 60.0 * 1000.0));
    return tc;
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateCompositeScale(IlvDisplay* display, IlvTimeConverter* converter)
{
    IlvTimeScale* tscale =
	new IlvCalendarScale(display, IlvRect(start, -100, end - start, 40));
    IlDateErrorCode error(IL_DATE_ZERO_ERROR);
    IlGregorianCalendar cal(error);
    cal.set(2002, 0, 1, 0, 0, 0);
    tscale->setTimeConverter(converter);
    tscale->setVisibleTime(cal.getTime(error));
    tscale->setVisibleDuration(IlvDuration(91.0 * 24.0 * 60.0 * 60.0 * 1000.0));
    return tscale;
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateRowGrid(IlvGanttChart* gantt, IlvTimeConverter* converter)
{
    IlvRect area;
    gantt->getWorkArea(area);
    IlvTimeScale* tscale = new IlvGanttCalendarGrid(gantt);
    IlDateErrorCode error(IL_DATE_ZERO_ERROR);
    IlGregorianCalendar cal(error);
    cal.set(2002, 0, 1, 0, 0, 0);
    tscale->setTimeConverter(converter);
    tscale->setVisibleTime(cal.getTime(error));
    tscale->setVisibleDuration(IlvDuration(91.0 * 24.0 * 60.0 * 60.0 * 1000.0));
    tscale->setLabelVisible(IlFalse);
    tscale->setSeparatorVisible(IlFalse);
    return tscale;
}

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

    // Add the path to the toolbar files
    AppendGanttDataPath(display);

    // Create the main view
    // Target only the 'main' screen
    IlvRect mainScreenLocation(0, 0, 100, 100);
    IlvRect screenBbox;
    display->screenBBox(screenBbox, IlFalse, &mainScreenLocation);
    IlvRect size(32, 32, screenBbox.w() - 64, screenBbox.h() - 64);
    IlvGadgetContainer* top = new IlvGadgetContainer(display,
						     "Gantt Chart",
						     title,
						     size);

    // Create the Gantt chart form
    IlvGanttChartForm* gantt =
	new IlvGanttChartForm(display,
			      IlvRect(0, 32, size.w(), size.h() - 32),
			      start,
			      end,
			      start + 30 * 24,
			      start + 50 * 24,
			      step,
			      277,
			      0,
			      16,
			      40,
			      IlvScrollBar::getDefaultSize(display,
							   IlvVertical),
			      1);
    gantt->setSubNodeMinimumSize(subNodeMinSize);

    // Set line, node, and break graphic models
    gantt->setLineGraphicModel(CreateResourceGraphicModel(display));
    gantt->setSubNodeGraphicModel(CreateSubNodeGraphicModel(display));
    gantt->setBreakGraphicModel(CreateBreakGraphicModel(display));
    gantt->setLinkGraphicModel(CreateLinkGraphicModel(display));

    // Create the common time converter
    IlvTimeConverter* converter = CreateTimeConverter();

    // Specify the timescale
    gantt->setCompositeScale(CreateCompositeScale(display, converter));

    // Populate the Gantt chart with data
    PopulateGanttChart(gantt, start, end, subNodeMinSize);

    // Attach the Gantt chart
    IlvSetAttachment(gantt, IlvTop, IlvFixedAttach, 32);
    IlvSetAttachment(gantt, IlvBottom, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvLeft, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvRight, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvVertical, IlvElasticAttach);
    IlvSetAttachment(gantt, IlvHorizontal, IlvElasticAttach);
    top->addObject(gantt);
    top->setObjectName(gantt, "gantt");

    // Enable tooltips
    IlvToolTip::Enable(IlTrue);

    // Create the toolbar
    IlvGanttToolBar* toolbar = new IlvGanttToolBar(display, gantt);
    toolbar->w(size.w());
    top->addObject(toolbar);
    gantt->setBackground(toolbar->getBackground());

    // Disable the default grids
    gantt->showGrid(IlvFalse, IlvFalse);

    // Install the Quit callback and show the main view
    top->setDestroyCallback(Quit, 0);
    top->show();

    // Customize the resource header
    if (gantt->getResourceHeader()) {
        gantt->getResourceHeader()->getItem(0, 0)->setLabel("Title");
        gantt->getResourceHeader()->getItem(1, 0)->setLabel("Capacity");
    }

    // Create a special grid for the resources
    IlvGanttResourceGrid* lineGrid =
	new IlvGanttResourceGrid(gantt, gantt->getGridPalette());
    gantt->setLineGrid(lineGrid);

    // Create the calendar grid
    gantt->setRowGrid(CreateRowGrid(gantt, converter));

    // Customize the background colors of the views
    IlvColor* white = display->getColor("white");
    gantt->getManagerView(0)->setBackground(white);
    gantt->getManagerView(1)->setBackground(white);
    IlvColor* back = gantt->verticalSplitter(0)->getBackground();
    gantt->getScaleView(0)->setBackground(back);
    gantt->getScaleView(1)->setBackground(back);
    gantt->setDoubleBuffering(IlTrue);

    IlvMainLoop();
    return 0;
}

