// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/xlib/src/mpanim.cpp
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
// Demonstration of the multi-planes animation in Rogue Wave Views
// --------------------------------------------------------------------------

#include <ilviews/manager/manager.h>
#include <ilviews/graphics/holder.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/X11/config.h>
#include <ilviews/X11/colormap.h>
#include <ilviews/manager/layer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USEMGRLAYER

// This flag indicates, if non-null, that we want to use the bitPlanes
// group feature of Rogue Wave Views.
static int useBitPlanes = 1;

// Default files to be loaded.

// Background map filename. Overloaded by the '-map' option
#define DEFAULTMAPFILENAME "../DCW/europe.ilv"
// Foreground object filename. Overloaded by the '-anim' option
#define DEFAULTANIMFILENAME "plane.ilv"
// Scale to be applied to the animation. Overloaded by the '-scale' option
#define DEFAULTSCALE 1.

// --------------------------------------------------------------------------
// Display configuration:
// Try to allocate at least 2 bitPlanes groups, with 3 planes for the
// background and 2 for the foreground.
// --------------------------------------------------------------------------
static void
DisplayConfigCallback(IlvDisplayConfig* param)
{
    IlvXDisplayConfig* config = (IlvXDisplayConfig*)param;

    // Get the list of all available Visuals of the PseudoColor class
    // that are 8 bits deep
    int nVisuals;
    Visual* const* visuals =
	config->getVisualList(nVisuals, PseudoColor, 8);

    // If there are, set the first one as the default
    if (nVisuals)
	config->setVisual(visuals[0]);

    // If the current visual is not PseudoColor, disable the bitplanes groups
    if (config->getVisual()->c_class != PseudoColor) {
	IlvFatalError("BitPlanes can be created only on PseudoColor visuals");
	IlvPrint("Resuming without the BitPlanes feature");
	useBitPlanes = 0;
    } else {
	// Create a default colormap instead of the Display's default
	config->createColormap();
	// Create the bitplanes groups, and check the status.
	// 2 groups, with 3 bits for the background, and 2 for
	// the foreground.
	if (config->createBitPlanesGroups(2, 3, 2) < 2) {
	    IlvFatalError("Couldn't create at least 2 bitplane groups");
	    useBitPlanes = 0;
	}
    }
}

// --------------------------------------------------------------------------
// Application cleanup.
static void
Quit(IlvView* view,
     IlAny manager)
{
    IlvDisplay*  d = view->getDisplay();
    delete (IlvManager*)manager;
    delete view;
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// "Animation" interactor.
// It is a regular "MoveInteractor", but it only acts on the bitPlanes group
// number 1.
// --------------------------------------------------------------------------
class MoveInteractor
    : public IlvInteractor
{
public:
    MoveInteractor(IlvPalette* palette)
        : IlvInteractor(),
	  _initialized(IlFalse),
	  _x(0),
	  _y(0),
	  _palette(palette) {}
    virtual IlBoolean handleEvent(IlvGraphic*,
				  IlvEvent&,
				  const IlvTransformer*);
private:
    IlBoolean	_initialized;
    IlvPos	_x, _y;
    IlvPalette* _palette;
};

IlBoolean
MoveInteractor::handleEvent(IlvGraphic* obj,
			    IlvEvent& event,
			    const IlvTransformer* t)
{
    switch (event.type()) {
    case IlvButtonDown: {
	if (_initialized)
	    return IlFalse;
	_x = event.x();
	_y = event.y();
	_initialized = IlTrue;
	return IlTrue;
    }
    case IlvButtonDragged: {
	if (!_initialized)
	    return IlFalse;
	IlvRect bbox;
	obj->boundingBox(bbox);
	IlvPoint p1(bbox.centerx(), bbox.centery()),
	         p2(p1);
	if (t)
	    t->apply(p1);
	p1.translate(event.x()-_x, event.y()-_y);
	if (t)
	    t->inverse(p1);
#if defined(USEMGRLAYER)
	obj->getHolder()->translateObject(obj,
					  p1.x() - p2.x(), p1.y() - p2.y(),
					  IlTrue);
#else  /* USEMGRLAYER */
	if (useBitPlanes) {
	    // This will later be made easier, by means of a relationship
	    // between the Manager layers and the bitPlanes groups.
	    IlvRect eraseBbox;
	    obj->boundingBox(eraseBbox, t);
	    eraseBbox.w(eraseBbox.w() + 1);
	    eraseBbox.h(eraseBbox.h() + 1);
	    // Erase initial location of the animated object
	    view->getDisplay()->fillRectangle(view, _palette, eraseBbox);
	    // Translate the object (no redraw)
	    manager->translateObject(obj, p1.x() - p2.x(), p1.y() - p2.y(),
				     IlFalse);
	    // Draw the object at its new location
	    obj->draw(view, t);
	} else
	    manager->translateObject(obj, p1.x() - p2.x(), p1.y() - p2.y());
#endif /* USEMGRLAYER */
	_x = event.x();
	_y = event.y();
	return IlTrue;
    }
    case IlvButtonUp:
	if (!_initialized)
	    return IlFalse;
	_initialized = IlFalse;
	return IlTrue;
    default:;
    }
    return IlFalse;
}

// **************************************************************************
// C++ entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    char* mapfile = 0,
	* animfile = 0;
    double scale = DEFAULTSCALE;
    int useDoubleBuffering = 1;
    for (int argloop = 1; argloop < argc; argloop++)
	if (argv[argloop]) {
	    if (!strcmp(argv[argloop], "-display"))
		argloop++;
	    else
	    if (!strncmp(argv[argloop], "-nom", 4)) {
		useBitPlanes = 0;
		useDoubleBuffering = 1;
	    } else
	    if (!strncmp(argv[argloop], "-nod", 4)) {
		useDoubleBuffering = 0;
		useBitPlanes = 0;
	    } else
	    if (!strcmp(argv[argloop], "-map")) {
		mapfile = argv[++argloop];
		scale = 1.;
	    } else
	    if (!strcmp(argv[argloop], "-anim")) {
		animfile = argv[++argloop];
		scale = 1.;
	    } else
	    if (!strcmp(argv[argloop], "-scale")) {
		scale = atof(argv[++argloop]);
		if (!scale)
		  scale = 1.;
	    } else {
		IlvFatalError("Usage: %s [-nom[ultiplanes]] [-nod[oublebuffering]]",
			      argv[0]);
		IlvExit(-1);
	    }
	}
    // Connect to the display system ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvDisplay* display = new IlvDisplay("BitPlanesAnimationTest", "",
					 argc, argv,
					 useBitPlanes ?
					 DisplayConfigCallback :
					 (IlvDisplayConfigCallback)0);
    // Check its validity ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (!display || display->isBad()) {
	delete display;
	IlvFatalError("Couldn't open display");
	return -1;
    }
    IlvView* view = new IlvView(display,
				"Bitplanes animation Test",
				"Bitplanes animation Test",
				IlvRect(0, 0,
					display->screenWidth(),
					display->screenHeight()),
				IlFalse);
    IlvManager* manager = new IlvManager(display);

    manager->addView(view);
    view->setDestroyCallback(Quit, manager);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Load the foreground
    if (useBitPlanes)
        display->setBitPlanesGroup(1);
    manager->read(animfile ? animfile : DEFAULTANIMFILENAME);
    // Create a GraphicSet that contains all loaded objects.
    IlvUInt nObjects;
    IlvGraphic** objects = (IlvGraphic**)manager->getObjects(nObjects);
    IlvGraphicSet* set = new IlvGraphicSet();
    for (IlvUInt loop = 0; loop < nObjects; loop++) {
	manager->removeObject(objects[loop], IlFalse, IlFalse);
	set->addObject(objects[loop]);
    }
    if (scale != 1.)
	set->scale(scale, scale);
    if (useBitPlanes)
	display->setBitPlanesGroup();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Load the background (MAP is supposed to be 3 layers deep)
    if (useBitPlanes)
	display->setBitPlanesGroup(0);
    manager->read(mapfile ? mapfile : DEFAULTMAPFILENAME);
    if (useBitPlanes)
	display->setBitPlanesGroup();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Store the foreground in layer 4
    manager->addObject(set, IlFalse, 4);
#if defined(USEMGRLAYER)
    // Associate Layer 4 and BitPlanesGroup 1
    if (useBitPlanes)
	manager->getManagerLayer(4)->setBitPlanesGroup(1);
#endif /* USEMGRLAYER */

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Set the interactor for move.
    // If we're using the bitPlanes groups, then query the palette that
    // erases the bitplane 1. It will be used by the interactor.
    set->setInteractor(new MoveInteractor(useBitPlanes
					  ? display->getXConfig()->
					    getTransparentPalette(1)
					  : 0));

    manager->fitTransformerToContents(view);
    if (useDoubleBuffering)
	manager->setDoubleBuffering(view, IlTrue);
    view->show();

    IlvMainLoop();
    return 0;
}
