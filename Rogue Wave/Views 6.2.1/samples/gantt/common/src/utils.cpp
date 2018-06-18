// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/src/utils.cpp
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
// Utility Functions for Gantt Chart samples.
// --------------------------------------------------------------------------
#include <utils.h>
#include <tooltip.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/graphics/shadlab.h> 

#if defined(IL_STD)
#  include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#  include <stdio.h>
#endif /* IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// This function is called when a Gantt object (line, subnode, link) is
// added to the Gantt chart, or the name of the Gantt object is changed.
void
OnGanttObjectNameChanged(IlvGanttAbstractObject* object,
			 IlvGraphic*		 graphic,
			 IlvGanttObjectType	 type,
			 IlAny			 index)
{
    if (graphic->getClassInfo()->isSubtypeOf(IlvMatrix::ClassInfo())) {
	if (type == IlvGanttIsLine ) {
	    IlvMatrix* matrix = (IlvMatrix*)graphic;
	    IlvAbstractMatrixItem*  item;
	    item = matrix->getItem(0, 0);
	    item->setLabel(object->getName());
	    item = matrix->getItem(1, 0);
	    char buffer[16];
	    sprintf(buffer, "%d", ((IlvGanttLine*)object)->getCapacity());
	    item->setLabel(buffer);
	}
    }
    else if(graphic->getClassInfo()
	    ->isSubtypeOf(IlvMessageLabel::ClassInfo())) {
	IlvMessageLabel* label = (IlvMessageLabel*)graphic;
	label->setLabel(object->getName());
    }
    else if(graphic->getClassInfo()
	    ->isSubtypeOf(IlvShadowLabel::ClassInfo())) {
	IlvShadowLabel* label = (IlvShadowLabel*)graphic;
	label->setLabel(object->getName());
    }

    if (type == IlvGanttIsNode ) {
	IlvGanttNode* node = (IlvGanttNode*)object;
	IlvGanttSubNode* subnode = node->getSubNode(*((IlUShort*)index));
	graphic->setNamedProperty(new IlvGanttSubNodeToolTip(subnode));
    }
}

// --------------------------------------------------------------------------
void RegisterGanttNameProperty(IlvGraphic* graphic) 
{
    // Test if the Gantt name property is added to the IlvGraphic.
    IlvGanttSetGraphicName function =
	IL_FPTRTOANYCAST(IlvGanttSetGraphicName)
	(graphic->getClassProperty(IlvGanttChart::nameProperty(), IlTrue));
    if (function) {
	return;
    }

    graphic->AddProperty(IlvGanttChart::nameProperty(), (IlAny)
	IL_FPTRTOANYCAST(IlvGanttSetGraphicName)(OnGanttObjectNameChanged));
}

// --------------------------------------------------------------------------
void
AppendGanttDataPath(IlvDisplay* display)
{
    const char* ilvhome = display->getHome();
    if (ilvhome) {
	char path[1024];
	sprintf(path, "%s/samples/gantt/data", ilvhome);
	display->appendToPath(path);
    }
}

// --------------------------------------------------------------------------
void ILVCALLBACK
Quit(IlvView* view, IlAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Populates the Gantt chart with data.
void
PopulateGanttChart(IlvGanttChart* gantt)
{
    // Creating lines
    IlvGanttLine* line0 = new IlvGanttLine("Line  0", 1);
    IlvGanttLine* line1 = new IlvGanttLine("Line  1", 1);
    IlvGanttLine* line2 = new IlvGanttLine("Line  2", 3);
    IlvGanttLine* line3 = new IlvGanttLine("Line  3", 1);
    IlvGanttLine* line4 = new IlvGanttLine("Line  4", 2);
    IlvGanttLine* line5 = new IlvGanttLine("Line  5", 1);
    IlvGanttLine* line6 = new IlvGanttLine("Line  6", 3);
    IlvGanttLine* line7 = new IlvGanttLine("Line  7", 1);
    IlvGanttLine* line8 = new IlvGanttLine("Line  8", 2);
    IlvGanttLine* line9 = new IlvGanttLine("Line  9", 1);
    IlvGanttLine* lineA = new IlvGanttLine("Line 11", 2);
    IlvGanttLine* lineB = new IlvGanttLine("Line 12", 1);
    // Creating nodes
    IlvGanttSubNode* subnode1 = new IlvGanttSubNode( 50,  60,  70,  75,
						    line1);
    IlvGanttSubNode* subnode2 = new IlvGanttSubNode(100, 100, 120, 120,
						    line1);
    IlvGanttSubNode* subnode3 = new IlvGanttSubNode(250, 260, 300, 310,
						    line2);
    IlvGanttSubNode* subnode4 = new IlvGanttSubNode(100, 125, 150, 175,
						    line2);
    IlvGanttSubNode* subnode5 = new IlvGanttSubNode(320, 330, 400, 440,
						    line3);
    IlvGanttSubNode* subnode6 = new IlvGanttSubNode(250, 250, 350, 375,
						    line4);
    IlvGanttSubNode* subnode7 = new IlvGanttSubNode(425, 425, 475, 475,
						    line5);
    IlvGanttSubNode* subnode8 = new IlvGanttSubNode(400, 400, 500, 500,
						    lineA);
    IlvGanttSubNode* subnode9 = new IlvGanttSubNode(450, 450, 480, 480,
						    lineB);
    IlvGanttSubNode* subnodeA = new IlvGanttSubNode(300, 300, 360, 360,
						    line4);
    IlvGanttNode* node1 = new IlvGanttNode("node1", IlvTrue,
					   2, subnode1, subnode2);
    IlvGanttNode* node2 = new IlvGanttNode("node2", IlvTrue, 1, subnode3);
    IlvGanttNode* node3 = new IlvGanttNode("node3", IlvTrue,
					   3, subnode4, subnode5, subnode6);
    IlvGanttNode* node4 = new IlvGanttNode("node4", IlvTrue,
					   2, subnode7, subnode8);
    IlvGanttNode* node5 = new IlvGanttNode("node5", IlvTrue,
					   2, subnode9, subnodeA);
    // Creating links
    IlvGanttLink* link1 = new IlvGanttLink(node1, node2,
					   IlvStartsAfterEnd, 10);
    // Adding all to Gantt Gadget
    gantt->addLine(line0, IlFalse);
    gantt->addLine(line1, IlFalse);
    gantt->addLine(line2, IlFalse);
    gantt->addLine(line3, IlFalse);
    gantt->addLine(line4, IlFalse);
    gantt->addLine(line5, IlFalse);
    gantt->addLine(line6, IlFalse);
    gantt->addLine(line7, IlFalse);
    gantt->addLine(line8, IlFalse);
    gantt->addLine(line9, IlFalse);
    gantt->addLine(lineA, IlFalse);
    gantt->addLine(lineB, IlFalse);

    gantt->addNode(node1, IlFalse);
    gantt->addNode(node2, IlFalse);
    gantt->addNode(node3, IlFalse);
    gantt->addNode(node4, IlFalse);
    gantt->addNode(node5, IlFalse);

    gantt->addLink(link1, IlFalse);
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateBreakGraphicModel(IlvDisplay* display)
{
    IlvPalette* transPal = display->getPalette(display->getColor("green"),
					       display->getColor("white"),
					       display->getPattern("gray"));
    transPal->lock();
    transPal->setMode(IlvModeAnd);
    IlvRect box(0, 0, 120, 24);
    IlvGraphic* model =  new IlvFilledRectangle(display, box, transPal);
    transPal->unLock();
    return model;
}

// --------------------------------------------------------------------------
// Line names
static const char* linesArray[] = {
    "Sales person",
    "Product designer",
    "Industrial graphic artist",
    "Product design manager",
    "Purchasing manager",
    "Sales manager",
    "Quality manager",
    "Product developer"
};

// --------------------------------------------------------------------------
// Node names
static const char* nodesArray[] = {
    "Contract",
    "Contract receipt",
    "Preliminary design",
    "Critical design review",
    "Final design",
    "Final design revision",
    "Final technical specifications",
    "Design approval",
    "Prototyping and instrument testing",
    "Prototyping and mount testing",
    "Production prototyping",
    "Quality assurance",
    "Production resources",
    "First item production",
    "Large-scale production",
    "Customer shipment"
};

// --------------------------------------------------------------------------
void
PopulateGanttChart(IlvGanttChart* gantt,
		   IlInt start,
		   IlInt end,
		   IlInt subNodeMinSize)
{
#define NUM_LINES 50
#define NUM_SUBNODES 200

    // Creating lines
    char buffer[256];
    int numFields = sizeof(linesArray) / sizeof(char*);
    IlvGanttLine* lines[NUM_LINES];
    int i;
    for (i = 0; i < NUM_LINES; ++i) {
	sprintf(buffer, "%s%d",
		linesArray[i % numFields], i / numFields + 1);
	lines[i] = new IlvGanttLine(buffer, (IlvUShort)(rand() % 7 + 1));
    }

    // Creating nodes
    IlvGanttSubNode* subnodes[NUM_SUBNODES];
    IlInt startEnd[4];
    int index;
    for (i = 0; i < NUM_SUBNODES; ++i) {
	startEnd[0] = start
	    + rand() % ((end - start) - (end - start) / 12 - 24);
	startEnd[1] = (startEnd[0] + rand() % 12);
	startEnd[2] = (startEnd[1]
		       + rand() % ((end - start) / 12) + subNodeMinSize);
	startEnd[3] = (startEnd[2] + rand() % 12);
	index = rand() % NUM_LINES;
	subnodes[i] = new IlvGanttSubNode(startEnd[0], startEnd[1],
					  startEnd[2], startEnd[3],
					  lines[index],
					  (IlUShort)((rand() % 3) + 1));
    }
    numFields = sizeof(nodesArray) / sizeof(char*);
    IlvGanttNode* nodes[NUM_SUBNODES];
    int last = 0;
    for (i = 0; i < NUM_SUBNODES; ++i) {
	sprintf(buffer, "%s%d",
		nodesArray[i % numFields], i / numFields + 1);
	nodes[i] = new IlvGanttNode(buffer);
	index = (rand() % 3) + 1;
	for (int j = last; j < last + index && j < NUM_SUBNODES; ++j) {
	    nodes[i]->addSubNode(subnodes[j]);
	}
	last += index;
	if (last + 1 >= NUM_SUBNODES) {
	    break;
	}
    }
    int NUM_NODES = IlvMin(NUM_SUBNODES, i + 1);
    // Adding all to the Gantt chart
    IlvSetContentsChangedUpdate(IlFalse);
    for (i = 0; i < NUM_LINES; ++i) {
	gantt->addLine(lines[i], IlFalse);
    }
    for (i = 0; i < NUM_NODES; ++i) {
	gantt->addNode(nodes[i], IlFalse);
    }
    IlvSetContentsChangedUpdate(IlTrue);
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateSubNodeGraphicModel(IlvDisplay* display)
{
    IlvColor* khaki = display->getColor("khaki");
    IlvColor* navy = display->getColor("navy");
    IlvPalette* palette = display->getPalette(khaki, navy);
    palette->lock();
    IlvGraphic* model = new IlvShadowLabel(display, "",
					   IlvRect(0, 0, 100, 20),
					   1, IlvBottomRight, palette);
    palette->unLock();
    RegisterGanttNameProperty(model);
    return model;
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateLineGraphicModel(IlvDisplay* display)
{
    IlvColor* white = display->getColor("white");
    IlvColor* black = display->getColor("black");
    IlvPalette* palette = display->getPalette(black, white);
    palette->lock();
    IlvMessageLabel* model = new IlvMessageLabel(display,  "", 
						 IlvRect(0, 0, 100, 20),
						 IlvRight, 0, palette);
    palette->unLock();
    model->setOpaque(IlFalse);
    RegisterGanttNameProperty(model);
    return model;
}

// --------------------------------------------------------------------------
IlvGraphic*
CreateLinkGraphicModel(IlvDisplay* display)
{
    IlvColor* red = display->getColor("red");
    IlvColor* black = display->getColor("black");
    IlvPalette* palette = display->getPalette(black, red);
    palette->lock();
    IlvGraphic* model = new IlvDoubleLinkImage(display, IlTrue, 0, 0,
					       palette);
    palette->unLock();
    return model;
}
