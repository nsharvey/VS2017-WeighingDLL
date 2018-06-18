// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/transparent/src/transp.cpp
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
// Definition of the UpDownField class
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/graphics/relfline.h>
#include <ilviews/graphics/label.h>
#include <ilviews/gadgets/ctoggle.h>
#include <ilviews/ilv.h>
#include <ilog/pathname.h>
#include <ilviews/bitmaps/png.h>

IL_STDUSE

#if defined(IL_STD)
#include <fstream>
#include <cstdlib>
#else
#include <fstream.h>
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
   IlvDisplay* display = view->getDisplay();
   delete view;
   delete display;
   IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Recompute(IlvGraphic*,
	  IlAny args)
{
    IlvNumberField** fields = (IlvNumberField**)args;
    IlBoolean error;
    fields[2]->setValue(fields[0]->getIntValue(error) +
			fields[1]->getIntValue(error));
    fields[2]->reDraw();
}

// **************************************************************************
// C++ Entry Point
// **************************************************************************
static const char title[] = "Transparency";
int
main(int argc ,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (!display || display->isBad()) {
        if (display)
	    delete display;
        IlvFatalError("Couldn't create display");
        exit(-1);
    }
    // Add the sample directory to the display path
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/gadgets/transparent");
    display->prependToPath(localPath);

    IlvBitmap* bitmap = display->readBitmap("data/poolbg.png");
    bitmap->lock();
    if (!bitmap) {
	IlvFatalError("Couldn't open background bitmap");
	delete display;
	IlvExit(0);
    }
    IlvFont* largeFont = display->defaultLargeFont();
    IlvGadgetContainer* cont =
	new IlvGadgetContainer(display, title, title,
			       IlvRect(0, 0, 200, 122), IlFalse, IlFalse);
    cont->setBackgroundBitmap(bitmap);
    bitmap->unLock();
    IlvNumberField* field1 = new IlvNumberField(display,
						(IlInt)123,
						IlvRect(90, 10, 70, 30));
    field1->setFont(largeFont);
    field1->setTransparent(IlTrue);
    cont->addObject(field1);
    IlvNumberField* field2 = new IlvNumberField(display,
						(IlInt)321,
						IlvRect(90, 45, 70, 30));
    field2->setFont(largeFont);
    field2->setTransparent(IlTrue);
    cont->addObject(field2);
    cont->addObject(new IlvReliefLine(display,
				      IlvPoint( 90, 80),
				      IlvPoint(160, 80)));
    IlvNumberField* field3 = new IlvNumberField(display,
						(IlInt)444,
						IlvRect(90, 85, 70, 30));
    field3->setFont(largeFont);
    field3->setEditable(IlFalse);
    field3->setThickness(0);
    field3->setTransparent(IlTrue);
    cont->addObject(field3);

    IlAny args[3];
    args[0] = field1;
    args[1] = field2;
    args[2] = field3;
    field1->setChangeCallback(Recompute, (IlAny)args);
    field2->setChangeCallback(Recompute, (IlAny)args);

    IlvLabel* label = new IlvLabel(display, IlvPoint(60, 50), "+");
    label->setFont(largeFont);
    cont->addObject(label);
    label = new IlvLabel(display, IlvPoint(60, 105), "=");
    label->setFont(largeFont);
    cont->addObject(label);

    IlvColoredToggle c(display,IlvPoint(), "test");

    cont->setDestroyCallback(Quit);
    cont->show();
    IlvMainLoop();
    return 0;
}
