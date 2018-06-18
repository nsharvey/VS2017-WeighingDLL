// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/custgad/src/main.cpp
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
// Creating a ColoredTreeGadget
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ctxminter.h>
#include <coltree.h>
#include <ilog/pathname.h>

static const char* title = "Rogue Wave Views Gadgets tutorial";

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny)
{
    IlvDisplay* display = top->getDisplay();
    delete top;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static IlvColor*
GetChildrenColor(IlvTreeGadgetItem* item,
		 IlvColor* color)
{
    // Get the item level to choose the right color
    IlvUInt level = item->getLevel();
    // Compute the HSV components of the reference color
    IlvFloat h, s, v;
    color->getHSV(h, s, v);
    // Increase the V component
    v = (IlFloat)IlvMin((IlFloat)1., (IlFloat)(v + level * .08));
    // Return the new color
    return color->getDisplay()->getColor(h, s, v);
}

// --------------------------------------------------------------------------
static IlBoolean
ChangeColor(IlvGadgetItem* item,
	    IlAny arg)
{
    // The argument is a pointer to the ColoredTreeGadget instance
    ColoredTreeGadget* tree = (ColoredTreeGadget*)arg;
    // Change the background of the children of item
    tree->setChildrenBackground((IlvTreeGadgetItem*)item,
				GetChildrenColor((IlvTreeGadgetItem*)item,
						 tree->getBackground()),
				IlFalse);
    // Continue
    return IlTrue;
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    // Create the display connection
    IlvDisplay* display =  new IlvDisplay(title, "", argc, argv);
    if (!display || display->isBad()) {
        if (display)
	    delete display;
	IlvFatalError("Couldn't create display");
	return 1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/gadgets/custgad/data");
    display->prependToPath(localPath);
    
    // Then create container that will hold the colored tree
    IlvGadgetContainer* container =
	new IlvGadgetContainer(display,
			       title,
			       title,
			       IlvRect(120, 0, 600, 520),
			       IlFalse,
			       IlFalse);
    container->setDestroyCallback(Quit);

    // Read the file that contains the colored tree
    container->readFile("coltree.ilv");

    // Retrieve the tree
    ColoredTreeGadget* tree = (ColoredTreeGadget*)container->getObject("Tree");

    // Set the background of the tree to gray
    // This color will be used as the reference color to compute the children
    // colors
    tree->setBackground(display->getColor("gray"));

    // Now change the color of each level of items
    tree->applyToItems(ChangeColor, (IlAny)tree);

    // Set the interactor to let the use change the colors
    tree->setInteractor(new ColoredTreeGadgetInteractor());

    container->show();
    IlvMainLoop();
    return 0;
}
