// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/dragdrop/src/dragdrop.cpp
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
// Sample that shows how to use the drag&drop feature of the IlvGadgetItem
// --------------------------------------------------------------------------

#include <ilviews/graphics/geomhan.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/itemtool.h>
#include <ilviews/gadgets/splitgad.h>

#define MARGIN 5

// --------------------------------------------------------------------------
// Global variable used to store the target tree gadget during a drag and drop
// operation
// --------------------------------------------------------------------------
IlvTreeGadget* Target = 0;

// --------------------------------------------------------------------------
// Global variable used to store the type of action that will be performed
// at the end of the drag and drop operation : 
// CopyMode = IlTrue ===> The item begin dragged is copied.
// CopyMode = IlFalse ===> The item begin dragged is moved.
// --------------------------------------------------------------------------
IlBoolean CopyMode = IlFalse;

// --------------------------------------------------------------------------
// Callback called during a drag and drop operation.
// It finds the target of the drag and drop operation by using the pointer
// position.
// --------------------------------------------------------------------------
static void
itemDraggedCB(IlvGraphic* g,
	      IlAny /* arg */)
{
    IlvTreeGadget* tree = (IlvTreeGadget*)g;
    IlvDisplay* display = tree->getDisplay();

    // Are we on an item of another tree gadget ?
    IlUShort modifiers;
    IlvPos x, y;
    display->queryPointer(x, y, modifiers);
    IlvPoint p(x, y);
    
    // Should we copy or move the item ?
    CopyMode = (modifiers & IlvCtrlModifier)? IlTrue : IlFalse;

    // Use view coordinates
    IlvView* view = tree->getView();
    IlvRect gbox;
    view->globalBBox(gbox);
    p.translate(-gbox.x(), -gbox.y());

    // Find the target
    IlvContainer* container = IlvContainer::getContainer(tree);
    IlvGraphic* obj = container->contains(p);
    if (obj && obj->isSubtypeOf(IlvTreeGadget::ClassInfo()) && obj != tree) {
	Target = (IlvTreeGadget*)obj;
	IlBoolean button;
	IlvTreeGadgetItem* item =
	    Target->pointToItem(p,
				button,
				Target->getTransformer());
	// Set the drag and drop target item ==> This will highlight it
	Target->setDragDropTarget(button? 0 : (item
					       ? item
					       : Target->getRoot()));
    } else
	Target = 0;
}

// --------------------------------------------------------------------------
// Callback called at the end of a drag and drop operation
// --------------------------------------------------------------------------
static void
endDragCB(IlvGraphic* g,
	  IlAny /* arg */)
{
    IlvTreeGadget* source = (IlvTreeGadget*)g;
    IlvTreeGadgetItem* sourceItem = source->getFirstSelectedItem();
    if (!Target || !sourceItem)
	return;

    // Retrieve the target item
    IlvTreeGadgetItem* targetItem =
	(IlvTreeGadgetItem*)Target->getDragDropTarget();
    if (!targetItem)
	targetItem = Target->getRoot();
    // Reset the drag and drop target
    Target->setDragDropTarget(0);

    // Do the action
    IlvTreeGadgetItem* item;
    if (!CopyMode) {
	item = sourceItem;
	item->detach();
    } else
	item = (IlvTreeGadgetItem*)sourceItem->copy();
    item->deSelect();
    item->highlight(IlFalse);
    targetItem->insertChild(item);

    // Reinit flags
    Target = 0;
    CopyMode = IlFalse;
}

// --------------------------------------------------------------------------
// Global function used to fill the a tree gadget with colored items
// --------------------------------------------------------------------------
IlvTreeGadgetItem*
GetNewTreeHierarchy(IlvTreeGadget* tree,
		    const char* name)
{
    IlvDisplay* display = tree->getDisplay();
    IlvTreeGadgetItem* item = new IlvTreeGadgetItem(name);
    IlvTreeGadgetItem* newItem;
    IlvPalette* palette;

    newItem = new IlvTreeGadgetItem("Leaf 1 (red)");
    palette = display->getPalette(tree->getNormalTextPalette()->
				  getBackground(),
				  display->getColor("red"));
    newItem->setNormalTextPalette(palette);
    item->insertChild(newItem);
    newItem = new IlvTreeGadgetItem("Leaf 2 (dark green)");
    palette = display->getPalette(tree->getNormalTextPalette()->
				  getBackground(),
				  display->getColor("dark green"));
    newItem->setNormalTextPalette(palette);

    item->insertChild(newItem);
    newItem = new IlvTreeGadgetItem("Leaf 3 (blue)");
    palette = display->getPalette(tree->getNormalTextPalette()->
				  getBackground(),
				  display->getColor("blue"));
    newItem->setNormalTextPalette(palette);
    item->insertChild(newItem);
    return item;
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    IlvDisplay* d = view->getDisplay();
    delete view;
    delete d;
    IlvExit(0);
}

// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("DragDrop", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open display...");
	if (display)
	    delete display;
	return 1;
    }

    // Create the main window
    const char* title = "Drag Drop sample"; 
    IlvRect size(0, 0, 320, 240);
    IlvGadgetContainer* container =
	new IlvGadgetContainer(display,
			       title,
			       title,
			       size,
			       IlFalse,
			       IlFalse);
    // Connect a destroy callback
    container->setDestroyCallback(Quit);

    // Add an horizontal guide in the middle of the container
    IlvGadgetHolder* holder = container->getHolder();
    holder->addGuide(IlvHorizontal, size.w() / 2, 100, 50);
    
    // Create a splitter gadget on the new guide
    IlvMakeSplitterGadget(container, IlvHorizontal, 1, 0, 2, 4);

    // Create the first TreeGadget
    IlvTreeGadget* treeGadget =
	new IlvTreeGadget(display,
			  IlvRect(MARGIN,
				  MARGIN,
				  size.w() / 2 - 2 * MARGIN,
				  size.h() - 2 * MARGIN));
    // fill it
    treeGadget->addItem(0, GetNewTreeHierarchy(treeGadget, "First Root"));
    treeGadget->addItem(0, GetNewTreeHierarchy(treeGadget, "Second Root"));
    // add it to the container
    container->addObject(treeGadget);
    // attach it to the container and guide
    holder->attach(treeGadget, IlvHorizontal, 0, 1, 0, 0,  0);
    holder->attach(treeGadget, IlvVertical,   0, 1, 0, 0, (IlUInt)-1);
    // Then connect the callbacks to handle drag and drop
    treeGadget->addCallback(IlvTreeGadget::DragItemCallbackType(),
			    itemDraggedCB);
    treeGadget->addCallback(IlvTreeGadget::EndDragItemCallbackType(),
			    endDragCB);
    // Allow the drag and drop for this tree gadget.
    treeGadget->allowDragDrop(IlTrue);
    // Allow edition too just for fun
    treeGadget->setEditable(IlTrue);

    // Create the second tree gadget
    IlvTreeGadget* treeGadget2 =
	new IlvTreeGadget(display,
			  IlvRect(size.w() / 2 + MARGIN,
				  MARGIN,
				  size.w() / 2 - 2 * MARGIN,
				  size.h() - 2 * MARGIN));
    // fill it
    treeGadget2->addItem(0, GetNewTreeHierarchy(treeGadget2, "First Root"));
    treeGadget2->addItem(0, GetNewTreeHierarchy(treeGadget2, "Second Root"));
    treeGadget2->addItem(0, GetNewTreeHierarchy(treeGadget2, "Third Root"));
    // add it to the container
    container->addObject(treeGadget2);
    // attach it to the container and guide
    holder->attach(treeGadget2, IlvHorizontal, 0, 1, 0, 1,  1);
    holder->attach(treeGadget2, IlvVertical,   0, 1, 0, 0, (IlUInt)-1);
    // Then connect the callbacks to handle drag and drop
    treeGadget2->addCallback(IlvTreeGadget::DragItemCallbackType(),
			     itemDraggedCB);
    treeGadget2->addCallback(IlvTreeGadget::EndDragItemCallbackType(),
			     endDragCB);
    // Allow the drag and drop for this tree gadget.
    treeGadget2->allowDragDrop(IlTrue);
    // Allow edition too just for fun
    treeGadget2->setEditable(IlTrue);
    
    // Show the main window
    container->show();

    IlvMainLoop();
    return 0;
}
