// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/custgad/src/ctxminter.cpp
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
// Definition of the ContextualMenuInteractor
//--------------------------------------------------------------------------

#include <ctxminter.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/graphics/rectangl.h>

//--------------------------------------------------------------------------
IlBoolean
ContextualMenuInteractor::handleEvent(IlvGraphic* obj,
				      IlvEvent& event,
				      const IlvTransformer* t)
{
    // Check that the object is a gadget
    IlvGadget* gadget = accept(obj) ? IL_CAST(IlvGadget*, obj) : 0;
    if (gadget && gadget->isActive()) {
	// Is it time to display the contextual menu ?
	if (shouldShowMenu(obj, event, t)) {
	    // Get the menu
	    IlvPopupMenu* menu = getMenu(obj, event, t);
	    // Show it
	    if (menu) {
		menu->get(IlvPoint(event.gx(), event.gy()),
			  /* transient */ 0);
		return IlTrue;
	    }
	}
    }
    // Default behaviour of the gadget
    return IlvGadgetInteractor::handleEvent(obj, event, t);
}

//--------------------------------------------------------------------------
IlBoolean
ContextualMenuInteractor::shouldShowMenu(IlvGraphic*,
					 IlvEvent& event,
					 const IlvTransformer*) const
{
    // The contextual menu is displayed by default when the right button
    // is released.
    return event.type() == IlvButtonUp && event.button() == IlvRightButton;
}

// --------------------------------------------------------------------------
static IlvSymbol*
GetSelectedItemSymbol()
{
    // This symbol is used to connect the contextual menu with the item that
    // asked for it.
    static IlvSymbol* symbol = IlvGetSymbol("SelectedItemBackground");
    return symbol;
}

//--------------------------------------------------------------------------
static void
ChangeColor(IlvGraphic* g,
	    IlAny arg)
{
    IlvPopupMenu* menu = (IlvPopupMenu*)g;
    // Retrieve the selected item of the pop-up menu
    IlvShort selected = menu->whichSelected();
    if (selected != -1) {
	// Retrieve its graphical representation
	IlvSimpleGraphic* graphic =
	    (IlvSimpleGraphic*)menu->getItem(selected)->getGraphic();
	// Use the second argument of the callback : A pointer to the colored
	// tree gadget object.
	ColoredTreeGadget* tree = (ColoredTreeGadget*)arg;
	// Retrieve the item whose color is going to be changed
	IlvTreeGadgetItem* item =
	    ColoredTreeGadgetInteractor::GetSelectedItem(menu);
	// Change the color of all the children of the parent item
	if (item && item->getParent())
	    tree->setChildrenBackground(item->getParent(),
					graphic
					? graphic->getForeground()
					: (IlvColor*)0);
    }
}

//--------------------------------------------------------------------------
void
ColoredTreeGadgetInteractor::SetSelectedItem(IlvPopupMenu* menu,
					     ColoredTreeGadget* tree,
					     IlvTreeGadgetItem* item)
{
    // Set it the callback that will change the item color.
    menu->setCallback(ChangeColor, (IlAny)tree);
    // Sets the item that asked for the contextual menu as a property of the
    // menu. It will be used in the callback of the menu.
    menu->setProperty(GetSelectedItemSymbol(), (IlAny)item);
}

//--------------------------------------------------------------------------
IlvTreeGadgetItem*
ColoredTreeGadgetInteractor::GetSelectedItem(const IlvPopupMenu* menu)
{
    // Retrieve the item that asked for the specified pop-up menu
    return (IlvTreeGadgetItem*)menu->getProperty(GetSelectedItemSymbol());
}

//--------------------------------------------------------------------------
static void
AddColor(IlvPopupMenu* menu,
	 const char* color)
{
    // This static function is used to fill the contextual menu.
    IlvDisplay* display = menu->getDisplay();
    // A menu item is created with the specified color name
    IlvMenuItem* item = new IlvMenuItem(color ? color : "None");
    if (color) {
	// An IlvFilledRectangle object is created with the specfied color
	IlvPalette* palette = display->getPalette(0, display->getColor(color));
	IlvFilledRectangle* rectangle =
	    new IlvFilledRectangle(display,
				   IlvRect(0, 0, 20, 20),
				   palette);
	// The IlvFilledRectangle object is set as the picture of the item.
	item->setGraphic(rectangle);
    }
    // The item is inserted into the pop-up menu.
    menu->insertItem(item);
}

//--------------------------------------------------------------------------
IlvPopupMenu*
ColoredTreeGadgetInteractor::getMenu(IlvGraphic* graphic,
				     IlvEvent& event,
				     const IlvTransformer* t) const
{
    ColoredTreeGadget* tree = (ColoredTreeGadget*)graphic;
    // Find the item located at the event location
    IlvTreeGadgetItem* item = tree->pointToItemLine(IlvPoint(event.x(),
							     event.y()),
						    (IlvTransformer*)t);
    if (!item)
	return 0;
    
    // Create the menu if needed
    static IlvPopupMenu* menu = 0;
    if (!menu) {
	// Create the pop-up menu
	menu = new IlvPopupMenu(tree->getDisplay());
	// Fill it with predefined colors
	AddColor(menu, 0);
	AddColor(menu, "yellow");
	AddColor(menu, "green");
	AddColor(menu, "red");
	AddColor(menu, "blue");
	AddColor(menu, "gray");
	AddColor(menu, "brown");
    }
    // Set the item that asked for the contextual menu so that the menu
    // will be able to use it later
    SetSelectedItem(menu, tree, item);
    // Return the menu
    return menu;
}
