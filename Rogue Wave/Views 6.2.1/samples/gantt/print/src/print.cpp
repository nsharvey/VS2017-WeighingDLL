// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/print/src/print.cpp
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
// Gantt printing sample  
// --------------------------------------------------------------------------
//
// This sample prints a gantt chart using PostScript or Windows printer. It 
// uses a class called GanttChartPrintingUtility.
//
// Multiple page printing is handled by this class. On each page, the gantt 
// lines and scale are printed according to the visible part of the
// gantt chart
// --------------------------------------------------------------------------

#include <ilviews/graphics/attach.h>
#include <ilviews/gantt/ganttfrm.h>
#include <ilviews/gantt/ganttgrd.h>
#include <ilviews/gantt/ganttint.h>
#include <ilviews/gadgets/button.h>
#include <ganttprnt.h>

// --------------------------------------------------------------------------
static const char* title = "Rogue Wave Views Gantt printing sample";

// --------------------------------------------------------------------------
// Specify the range and the step of the gantt and the node minimum size
static void
buttonCallback(IlvGraphic* obj, IlAny arg) 
{
    IlvGanttChart * gantt = (IlvGanttChart *)arg;        
    GanttChartPrintingUtility* ganttPrint =
        new GanttChartPrintingUtility(gantt);    
    ganttPrint->printGantt();
}

// --------------------------------------------------------------------------
// Utility function
static void
PopulateGanttChart(IlvGanttChart * gantt)
{
    // Creating lines
    IlvGanttLine* line1 = new IlvGanttLine("line1", 1);
    IlvGanttLine* line2 = new IlvGanttLine("line2", 1);
    IlvGanttLine* line3 = new IlvGanttLine("line3", 1);
    IlvGanttLine* line4 = new IlvGanttLine("line4", 1);
    IlvGanttLine* line5 = new IlvGanttLine("line5", 1);
    IlvGanttLine* line6 = new IlvGanttLine("line6", 1);
    IlvGanttLine* line7 = new IlvGanttLine("line7", 1);
    IlvGanttLine* line8 = new IlvGanttLine("line8", 1);
    IlvGanttLine* line9 = new IlvGanttLine("line9", 1);
    IlvGanttLine* line10 = new IlvGanttLine("line10", 1);
    IlvGanttLine* line11 = new IlvGanttLine("line11", 1);
    IlvGanttLine* line12 = new IlvGanttLine("line12", 1);
    IlvGanttLine* line13 = new IlvGanttLine("line13", 1);
    IlvGanttLine* line14 = new IlvGanttLine("line14", 1);
    IlvGanttLine* line15 = new IlvGanttLine("line15", 1);
    IlvGanttLine* line16 = new IlvGanttLine("line16", 1);
    IlvGanttLine* line17 = new IlvGanttLine("line17", 1);
    IlvGanttLine* line18 = new IlvGanttLine("line18", 1);
    IlvGanttLine* line19 = new IlvGanttLine("line19", 1);
    IlvGanttLine* line20 = new IlvGanttLine("line20", 1);
    IlvGanttLine* line21 = new IlvGanttLine("line21", 1);
    IlvGanttLine* line22 = new IlvGanttLine("line22", 1);
    IlvGanttLine* line23 = new IlvGanttLine("line23", 1);
    IlvGanttLine* line24 = new IlvGanttLine("line24", 1);
    IlvGanttLine* line25 = new IlvGanttLine("line25", 1);
    IlvGanttLine* line26 = new IlvGanttLine("line26", 1);
    IlvGanttLine* line27 = new IlvGanttLine("line27", 1);
    IlvGanttLine* line28 = new IlvGanttLine("line28", 1);
    IlvGanttLine* line29 = new IlvGanttLine("line29", 1);
    IlvGanttLine* line30 = new IlvGanttLine("line30", 1);
    IlvGanttLine* line31 = new IlvGanttLine("line31", 1);
    IlvGanttLine* line32 = new IlvGanttLine("line32", 1);
    IlvGanttLine* line33 = new IlvGanttLine("line33", 1);
    IlvGanttLine* line34 = new IlvGanttLine("line34", 1);
    IlvGanttLine* line35 = new IlvGanttLine("line35", 1);
    IlvGanttLine* line36 = new IlvGanttLine("line36", 1);
    
    // Creating nodes
    IlvGanttSubNode* subnode1 =
	new IlvGanttSubNode(0, 0, 600, 600, line1);
    IlvGanttSubNode* subnode2 =
	new IlvGanttSubNode(200, 200, 800, 800, line3);
    IlvGanttSubNode* subnode3 =
	new IlvGanttSubNode(400, 400, 1000, 1000, line6);
    IlvGanttSubNode* subnode4 =
	new IlvGanttSubNode(600, 600, 1200, 1200, line9);
    IlvGanttSubNode* subnode5 =
	new IlvGanttSubNode(100, 100, 500, 500, line12);
    IlvGanttSubNode* subnode6 =
	new IlvGanttSubNode(300, 300, 700, 700, line15);
    IlvGanttSubNode* subnode7 =
	new IlvGanttSubNode(500, 500, 900, 900, line18);
    IlvGanttSubNode* subnode8 =
	new IlvGanttSubNode(700, 700, 1100, 1100, line24);
    IlvGanttSubNode* subnode9 =
	new IlvGanttSubNode(0, 0, 800, 800, line30);
    IlvGanttSubNode* subnode10 =
	new IlvGanttSubNode(400, 400, 1200, 1200, line36);
    IlvGanttNode* node1 =
	new IlvGanttNode("node1", IlTrue, 1, subnode1);
    IlvGanttNode* node2 =
	new IlvGanttNode("node2", IlTrue, 1, subnode2);
    IlvGanttNode* node3 =
	new IlvGanttNode("node3", IlTrue, 3, subnode3, subnode4, subnode5);
    IlvGanttNode* node4 =
	new IlvGanttNode("node4", IlTrue, 2, subnode6, subnode7);
    IlvGanttNode* node5 =
	new IlvGanttNode("node5", IlTrue, 1, subnode8);
    IlvGanttNode* node6 =
	new IlvGanttNode("node6", IlTrue, 1, subnode9);
    IlvGanttNode* node7 =
	new IlvGanttNode("node7", IlTrue, 1, subnode10);

    // Adding all to Gantt Gadget
    gantt->addLine(line1, IlFalse);
    gantt->addLine(line2, IlFalse);
    gantt->addLine(line3, IlFalse);
    gantt->addLine(line4, IlFalse);
    gantt->addLine(line5, IlFalse);
    gantt->addLine(line6, IlFalse);
    gantt->addLine(line7, IlFalse);
    gantt->addLine(line8, IlFalse);
    gantt->addLine(line9, IlFalse);
    gantt->addLine(line10, IlFalse);
    gantt->addLine(line11, IlFalse);
    gantt->addLine(line12, IlFalse);
    gantt->addLine(line13, IlFalse);
    gantt->addLine(line14, IlFalse);
    gantt->addLine(line15, IlFalse);
    gantt->addLine(line16, IlFalse);
    gantt->addLine(line17, IlFalse);
    gantt->addLine(line18, IlFalse);
    gantt->addLine(line19, IlFalse);
    gantt->addLine(line20, IlFalse);
    gantt->addLine(line21, IlFalse);
    gantt->addLine(line22, IlFalse);
    gantt->addLine(line23, IlFalse);
    gantt->addLine(line24, IlFalse);
    gantt->addLine(line25, IlFalse);
    gantt->addLine(line26, IlFalse);
    gantt->addLine(line27, IlFalse);
    gantt->addLine(line28, IlFalse);
    gantt->addLine(line29, IlFalse);
    gantt->addLine(line30, IlFalse);
    gantt->addLine(line31, IlFalse);
    gantt->addLine(line32, IlFalse);
    gantt->addLine(line33, IlFalse);
    gantt->addLine(line34, IlFalse);
    gantt->addLine(line35, IlFalse);
    gantt->addLine(line36, IlFalse);
    gantt->addNode(node1, IlFalse);
    gantt->addNode(node2, IlFalse);
    gantt->addNode(node3, IlFalse);
    gantt->addNode(node4, IlFalse);
    gantt->addNode(node5, IlFalse);
    gantt->addNode(node6, IlFalse);
    gantt->addNode(node7, IlFalse);
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view, IlAny arg)
{
    IlvDisplay* display = view->getDisplay();
    IlvGanttChart* gantt = (IlvGanttChart*)arg;
    if (gantt && gantt->getGadgetContainer()) {
        IlvView* ganttView;
        IlvManagerViewInteractor* inter;
        for (IlUShort i = 0; i < 2; i++) {
            ganttView = gantt->getManagerView(i);
            inter = gantt->getManager()->getInteractor(ganttView);
            if (inter) {
                gantt->getManager()->removeInteractor(ganttView);
                delete inter;
            }
        }
    }
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
SetZoomInteractor(IlvGanttChart* gantt)
{
    if (!gantt->getGadgetContainer())
	return;
    IlvGanttZoomInteractor* zoomInter;
    for (IlUShort i = 0; i < 2; i++) {
        zoomInter = new IlvGanttZoomInteractor(gantt,
					       gantt->getManager(),
					       gantt->getManagerView(i));
        gantt->getManager()->setInteractor(zoomInter);
    }
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlInt    start          = 0L;
    IlInt    end            = 1200L;
    IlUShort step           = (IlUShort)50L;
    IlInt    subNodeMinSize = 18L;
    
    // Create the display
    IlvDisplay* display = new IlvDisplay("Gantt", 0, argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        if (display)
	    delete display;
        return -1;
    }
    
    // Create the main view
    IlvRect size(50, 50, 800, 600);
    IlvGadgetContainer* top =
	new IlvGadgetContainer(display, "Printing", title, size);
    
    // Create the Gantt chart 
    IlvGanttChart* gantt =
	new IlvGanttChart(display,
			  IlvRect(0, 32, size.w(), size.h() - 32),
			  start,
			  end, 
			  start,
			  end,
			  step,
			  277,
			  0,
			  16,
			  40,
			  IlvScrollBar::getDefaultSize(display, IlvVertical),
			  1);
    gantt->setSubNodeMinimumSize(subNodeMinSize);
    
    // Add a button and its callback
    IlvButton* button =
	new IlvButton(display, "Print the gantt", IlvRect(0, 0, 100, 20));
    button->setCallback(buttonCallback, gantt);
    top->addObject(button);
        
    // Attach the Gantt chart
    IlvSetAttachment(gantt, IlvTop, IlvFixedAttach, 32);
    IlvSetAttachment(gantt, IlvBottom, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvLeft, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvRight, IlvFixedAttach);
    IlvSetAttachment(gantt, IlvVertical, IlvElasticAttach);
    IlvSetAttachment(gantt, IlvHorizontal, IlvElasticAttach);
        
    // Populate the Gantt chart with data
    PopulateGanttChart(gantt);
    
    top->addObject(gantt);
    top->setObjectName(gantt, "gantt");
    
    // Enable tooltips
    IlvToolTip::Enable(IlTrue);
    
    // Install the Quit callback and show the main view
    top->setDestroyCallback(Quit, gantt);
    top->show();
    
    // Customize the background colors of the views
    IlvColor* white = display->getColor("white");
    gantt->getManagerView(0)->setBackground(white);
    gantt->getManagerView(1)->setBackground(white);
    gantt->setDoubleBuffering(IlTrue);
    
    SetZoomInteractor(gantt);
    
    IlvMainLoop();
    return 0;
}
