// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/readbm.cpp
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
// Reading bitmap files. 
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/icon.h>

#if defined NOT_USING_MODULES
// When linking statically use this macro and link with appropriate
// libraries.
#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/bitmaps/ppm.h>
#include <ilviews/bitmaps/bmp.h>
#include <ilviews/bitmaps/rgb.h>
#include <ilviews/bitmaps/tiff.h>
#include <ilviews/bitmaps/wbmp.h>
#endif

#define FILENAME   "bigrwlogo.png"
#define BACKGROUND "greenstone.bmp"

// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static const char* title = "Rogue Wave Views sample: readbm";
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvRect dims(0, 0, 800, 500);
    IlvDisplay* display = new IlvDisplay("ReadBm", "", argc, argv);
    if (!display || display->isBad()) {
	delete display;
	IlvFatalError("Could not open display");
	return -1;
    }
    
    const char* buf = display->getEnvOrResource("ILVHOME");
    if (buf) {
	IlString path(buf);
	path += "/samples/foundation/bitmaps/data";
        display->prependToPath(path);
    }
   
    IlvContainer* container =
	new IlvContainer(display , title, title, dims, IlFalse, IlFalse);
    container->setBackgroundBitmap(display->readBitmap(BACKGROUND));
    IlvMoveInteractor* move = new IlvMoveInteractor();

    container->setDestroyCallback(Quit);

    IlvIcon* icon;
    if (argc >= 2) {
	for (IlInt i = 1; i < argc; ++i) {
	    IlvBitmap* bitmap = display->readBitmap(argv[i]);
	    if (bitmap) {
		bitmap->computeMask();
		icon = bitmap->getMask()
		    ? new IlvTransparentIcon(display, 
					     IlvPoint(0, 0), 
					     bitmap)
		    : new IlvIcon(display,
				  IlvPoint(0, 0), 
				  bitmap);
		icon->setInteractor(move);
		container->addObject(icon);
	    }
	}
    }
    else {
	icon = new IlvIcon(display, 
			   IlvPoint(0, 0), 
			   display->readBitmap(FILENAME));
	icon->setInteractor(move);
	container->addObject(icon);
    }
    container->setDoubleBuffering(IlTrue);
    container->show();
    IlvMainLoop();
    
    return 0;
}
