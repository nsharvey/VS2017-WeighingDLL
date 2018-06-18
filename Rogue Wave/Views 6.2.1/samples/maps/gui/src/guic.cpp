// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/gui/src/guic.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Implementation of graphical user interface component viewer.
// --------------------------------------------------------------------------
#include <ilviews/manager/paninter.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/polyline.h>

#include <guic.h>

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
using namespace std;
#else
#  include <iostream.h>
#  include <fstream.h>
#  include <stdio.h>
#  include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Exit called from the destroy callback. Do some cleanup.
// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    Guic* guic = (Guic*)a;
    delete guic->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Quit from accelerator
// --------------------------------------------------------------------------
static void
Quit(IlvManager* m, IlvView* view, IlvEvent&, IlvAny a)
{
    delete m->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Rotate the map. Called from an accelerator
// --------------------------------------------------------------------------
static void
Rotate(IlvManager* m, IlvView* v, IlvEvent&, IlvAny a)
{
    IlvRect r;
    v->sizeVisible(r);
    IlvTransformer t;
    t.rotate((IlvTransfoParam)r.centerx(),
	     (IlvTransfoParam)r.centery(), 10.);
    m->addTransformer(v, &t);
    m->draw(v, IlTrue);
}

// --------------------------------------------------------------------------
// Resize the IlvGraphic if the view is resized
// --------------------------------------------------------------------------
static void
Resize(IlvView* view, IlvRect& r, IlvAny a)
{
    IlvGraphic* gr = (IlvGraphic*)a;
    r.move(0, 0);
    gr->moveResize(r);
    IlvGraphicHolder* gh = gr->getHolder();
    if (gh) {
	gh->initRedraws();
	gh->invalidateRegion(gr);
	gh->reDrawViews();
    }
}

// --------------------------------------------------------------------------
// Coordviewer popup callback
// --------------------------------------------------------------------------
static void
CoordCallback(IlvGraphic* gr, IlvAny a)
{
    IlUShort count;
    IlvPopupMenu* pop = (IlvPopupMenu*)gr;
    int sel = pop->whichSelected();

    IlvMenuItem* item = pop->getItems(count)[sel];

    IlvSymbol* what;

    what = IlvGetSymbol("Coordviewer");
    IlvMapCoordViewer* coord = (IlvMapCoordViewer*)item->getProperty(what);
    if (!coord) {
	return;
    }

    what = IlvGetSymbol("Vertical");
    if (item->hasProperty(what)) {
	IlBoolean set = !item->isChecked();
	coord->setVertical(set, IlTrue);
	item->setChecked(set);
	return;
    }

    what = IlvGetSymbol("ShowEasting");
    if (item->hasProperty(what)) {
	IlBoolean set = !item->isChecked();
	coord->setDisplayingEasting(set, IlTrue);
	item->setChecked(set);
	return;
    }

    what = IlvGetSymbol("ShowNorthing");
    if (item->hasProperty(what)) {
	IlBoolean set = !item->isChecked();
	coord->setDisplayingNorthing(set, IlTrue);
	item->setChecked(set);
	return;
    }
}

// --------------------------------------------------------------------------
// Scale popup callback
// --------------------------------------------------------------------------
static void
ScaleCallback(IlvGraphic* gr, IlvAny a)
{
    IlUShort count;
    IlvPopupMenu* pop = (IlvPopupMenu*)gr;
    int sel = pop->whichSelected();

    IlvMenuItem* item = pop->getItems(count)[sel];

    IlvSymbol* what;

    what = IlvGetSymbol("Scale");
    IlvMapScale* scale = (IlvMapScale*)item->getProperty(what);
    if (!scale) {
	return;
    }

    what = IlvGetSymbol("TextValue");
    if (item->hasProperty(what)) {
	IlvMapScaleTextMode mode =
	    (IlvMapScaleTextMode)IlCastIlAnyToIlInt(item->getProperty(what));
	scale->setScaleTextMode(mode);
	scale->reDraw();
	return;
    }

    what = IlvGetSymbol("BarStyle");
    if (item->hasProperty(what)) {
	IlvMapDefaultScaleBarStyle style = (IlvMapDefaultScaleBarStyle)
		IlCastIlAnyToIlInt(item->getProperty(what));

	IlvMapDefaultScaleBar* bar = (IlvMapDefaultScaleBar*)
		scale->getGraphic();

	bar->setStyle(style);
	scale->reDraw();
    }
}

// --------------------------------------------------------------------------
// compass popup callback
// --------------------------------------------------------------------------
static void
CompassCallback(IlvGraphic* gr, IlvAny a)
{
    IlvPopupMenu* pop = (IlvPopupMenu*)gr;
    int sel = pop->whichSelected();

    IlUShort count;
    IlvMenuItem* item = pop->getItems(count)[sel];
    for (int i = 0; i < count; i++) {
	pop->getItem(i)->setChecked(IlFalse);
    }
    IlvSymbol* what;

    what = IlvGetSymbol("Needle");
    IlvMapDefaultNeedle* needle =
	(IlvMapDefaultNeedle*)item->getProperty(what);
    if (!needle) {
	return;
    }

    what = IlvGetSymbol("Style");

    if (item->hasProperty(what)) {
	IlvMapDefaultNeedleStyle style = (IlvMapDefaultNeedleStyle)
		IlCastIlAnyToIlInt(item->getProperty(what));

	item->setChecked(IlTrue);

	needle->setStyle(style);

	IlvSymbol* c = IlvGetSymbol("Compass");
	if (item->hasProperty(c)) {
	    IlvMapCompass* compass = (IlvMapCompass*)item->getProperty(c);
	    if (compass) {
		compass->reDraw();
	    }
	}
	return;
    }
}

// --------------------------------------------------------------------------
// Guic
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Create a view where to put the map.
// Create three views with a coordviewer, a scale and a compass.
// --------------------------------------------------------------------------
Guic::Guic(IlvDisplay* d, char* file)
    : _display(d)
{
    mainWindow(file);
    coordView();
    scaleView();
    compassView();
}

// --------------------------------------------------------------------------
Guic::~Guic()
{
}

// --------------------------------------------------------------------------
// The main window holds a map.
// --------------------------------------------------------------------------
void
Guic::mainWindow(char* file)
{
    _view = new IlvView(_display,
			"World",
			"World",
			IlvRect(0, 0, 400, 300),
			IlFalse, IlFalse);
    IlvManager* manager = new IlvManager(_display);
    ifstream stream(_display->findInPath(file));
    manager->read(stream);
    manager->addView(_view);
    manager->setKeepingAspectRatio(_view, IlTrue);
    manager->fitTransformerToContents(_view, IlTrue, IlTrue);
    IlvPanZoomInteractor* pzi = new IlvPanZoomInteractor(manager, _view);
    manager->setInteractor(pzi, _view);

    IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
    if (mapinfo == 0) {
	mapinfo = new IlvMapInfo(new IlvGeographicProjection());
	mapinfo->attach(manager);
    }
    manager->addAccelerator(Quit, IlvKeyUp, 'q');
    manager->addAccelerator(Rotate, IlvKeyUp, 'o');
    _view->setDestroyCallback(Exit, (IlvAny)this);
}

// --------------------------------------------------------------------------
// IlvMapCoordViewer
// --------------------------------------------------------------------------
void
Guic::coordView()
{
    IlvRect r(420, 0, 200, 50);
    _coordviewer = new IlvMapCoordViewer(_display, r);
    IlvFont* font = _display->getFont("new century schoolbook", 12);
    if (font) {
	_coordviewer->setFont(font);
    }
    _coordviewer->setDisplayMode(IlvMapDMSMode);
    _coordviewer->setVertical(IlTrue);

    _coordview = new IlvView(_display,
			     "IlvMapCoordViewer",
			     "IlvMapCoordViewer",
			     r, IlFalse);
    _coordmanager = new IlvManager(_display);
    _coordmanager->addView(_coordview);
    _coordmanager->addObject(_coordviewer);

    _coordviewer->setView(_view);
    coordPopup();
    _coordview->setResizeCallback(Resize, (IlvAny)_coordviewer);
}

// --------------------------------------------------------------------------
// IlvMapCompass
// --------------------------------------------------------------------------
void
Guic::compassView()
{
    IlvRect r(420, 100, 200, 70);
    _compass = new IlvMapCompass(_display, r);

    _compassview = new IlvView(_display,
			       "IlvMapCompass",
			       "IlvMapCompass",
			       r, IlFalse);
    _compassmanager = new IlvManager(_display);
    _compassmanager->addView(_compassview);
    _compassmanager->addObject(_compass);

    _compass->setView(_view);
    compassPopup();
    _compassview->setResizeCallback(Resize, (IlvAny)_compass);
}

// --------------------------------------------------------------------------
// IlvMapScale
// --------------------------------------------------------------------------
void
Guic::scaleView()
{
    IlvRect r(0, 330, 200, 50);

    _scale = new IlvMapScale(_display, r);
    _scaleview = new IlvView(_display,
			     "IlvMapScale",
			     "IlvMapScale",
			     r, IlFalse);
    _scalemanager = new IlvManager(_display);
    _scalemanager->addView(_scaleview);
    _scalemanager->addObject(_scale);
    _scale->setView(_view);
    scalePopup();
    _scaleview->setResizeCallback(Resize, (IlvAny)_scale);
}

// --------------------------------------------------------------------------
// Coordviewer popup can change orientation, easting/northing visibility
// --------------------------------------------------------------------------
void
Guic::coordPopup()
{
    _coordpop = new IlvPopupMenu(_display);
    IlvMenuItem* item ;

    item = new IlvMenuItem("Horizontal");
    item->addProperty(IlvGetSymbol("Coordviewer"), (IlvAny)_coordviewer);
    item->addProperty(IlvGetSymbol("Vertical"), (IlvAny)IlFalse);
    item->setCallback(CoordCallback);
    item->setChecked(IlTrue);
    _coordpop->insertItem(item);

    item = new IlvMenuItem("Show Easting");
    item->addProperty(IlvGetSymbol("Coordviewer"), (IlvAny)_coordviewer);
    item->addProperty(IlvGetSymbol("ShowEasting"), (IlvAny)IlFalse);
    item->setChecked(IlTrue);
    item->setCallback(CoordCallback);
    _coordpop->insertItem(item);

    item = new IlvMenuItem("Show Northing");
    item->addProperty(IlvGetSymbol("Coordviewer"), (IlvAny)_coordviewer);
    item->addProperty(IlvGetSymbol("ShowNorthing"), (IlvAny)IlTrue);
    item->setChecked(IlTrue);
    item->setCallback(CoordCallback);
    _coordpop->insertItem(item);

    _coordinter = new CoordPopupInteractor(this);
    _coordmanager->setInteractor(_coordinter, _coordview);
}


// --------------------------------------------------------------------------
// Scale popup
// --------------------------------------------------------------------------
void
Guic::scalePopup()
{
    IlvMapDefaultScaleBar* sb;
    IlvMapScale* sc;

    _scalepop = new IlvPopupMenu(_display);

    IlvMenuItem* item ;
    IlvRect r(0, 0, 128, 32);

    sc = new IlvMapScale(_display, r, IlvMapScaleUniqueLabel);
    sc->setView(_view);

    item = new IlvMenuItem(sc);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("TextValue"),
		      (IlvAny)IlvMapScaleUniqueLabel);
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sc = new IlvMapScale(_display, r, IlvMapScaleThreeLabels);
    sc->setView(_view);
    item = new IlvMenuItem(sc);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("TextValue"),
		      (IlvAny)IlvMapScaleThreeLabels);
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    item = new IlvMenuItem();
    _scalepop->insertItem(item);

    r.resize(128, 12);
    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarEmpty);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarOdd);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarEven);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5,
				   IlvMapScaleBarDoubleEmpty);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarDoubleOdd);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarDoubleEven);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarBottomLine);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    sb = new IlvMapDefaultScaleBar(_display, r, 5, IlvMapScaleBarCenterLine);
    item = new IlvMenuItem( sb);
    item->addProperty(IlvGetSymbol("Scale"), (IlvAny)_scale);
    item->addProperty(IlvGetSymbol("BarStyle"), (IlvAny)sb->getStyle());
    item->setCallback(ScaleCallback);
    _scalepop->insertItem(item);

    _scaleinter = new ScalePopupInteractor(this);
    _scalemanager->setInteractor(_scaleinter, _scaleview);
}

// --------------------------------------------------------------------------
// Compass popup
// --------------------------------------------------------------------------
void
Guic::compassPopup()
{
    _compasspop = new IlvPopupMenu(_display);
    IlvMenuItem* item ;
    IlvPopupMenu* sub;
    IlvMapDefaultNeedleStyle style;

    style = ((IlvMapDefaultNeedle*)_compass->getGeographicNeedle())
	->getStyle();
    sub = new IlvPopupMenu(_display);
    item = new IlvMenuItem("IlvMapSimpleNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getGeographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapSimpleNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapSimpleNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCompassNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getGeographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapCompassNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCompassNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCrossNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getGeographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapCrossNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCrossNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCompassRoseNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getGeographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"),
		      (IlvAny)IlvMapCompassRoseNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCompassRoseNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("Cartographic Style");
    _compasspop->insertItem(item);
    item->setMenu(sub, IlFalse);

    style = ((IlvMapDefaultNeedle*)_compass->getCartographicNeedle())
	->getStyle();

    sub = new IlvPopupMenu(_display);
    item = new IlvMenuItem("IlvMapSimpleNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getCartographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapSimpleNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapSimpleNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCompassNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getCartographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapCompassNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCompassNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCrossNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getCartographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"), (IlvAny)IlvMapCrossNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCrossNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("IlvMapCompassRoseNeedle");
    item->addProperty(IlvGetSymbol("Needle"),
		      (IlvAny)_compass->getCartographicNeedle());
    item->addProperty(IlvGetSymbol("Compass"),(IlvAny)_compass);
    item->addProperty(IlvGetSymbol("Style"),
		      (IlvAny)IlvMapCompassRoseNeedle);
    item->setCallback(CompassCallback);
    item->setChecked(style == IlvMapCompassRoseNeedle);
    sub->insertItem(item);

    item = new IlvMenuItem("Geographic Style");
    _compasspop->insertItem(item);
    item->setMenu(sub, IlFalse);

    _compassinter = new CompassPopupInteractor(this);
    _compassmanager->setInteractor(_compassinter, _compassview);
}

// --------------------------------------------------------------------------
// ScalePopupInteractor
// --------------------------------------------------------------------------
ScalePopupInteractor::ScalePopupInteractor(Guic* guic)
    : IlvManagerViewInteractor(guic->getScaleManager(),
			       guic->getScaleView()),
     _guic(guic)
{
}

// --------------------------------------------------------------------------
void
ScalePopupInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
IlBoolean
ScalePopupInteractor::handleEvent(IlvEvent& e)
{
    if (e.type() == IlvButtonUp) {
	_guic->showScalePopup(IlvPoint(e.gx(), e.gy()));
	return IlTrue;
    }
    return getManager()->shortCut(e, getView());
}

// --------------------------------------------------------------------------
// CoordPopupInteractor
// --------------------------------------------------------------------------
CoordPopupInteractor::CoordPopupInteractor(Guic* guic)
    : IlvManagerViewInteractor(guic->getCoordManager(),
			       guic->getCoordView()),
     _guic(guic)
{
}

// --------------------------------------------------------------------------
void
CoordPopupInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
IlBoolean
CoordPopupInteractor::handleEvent(IlvEvent& e)
{
    if (e.type() == IlvButtonUp) {
	_guic->showCoordPopup(IlvPoint(e.gx(), e.gy()));
	return IlTrue;
    }
    return getManager()->shortCut(e, getView());
}

// --------------------------------------------------------------------------
// CompassPopupInteractor
// --------------------------------------------------------------------------
CompassPopupInteractor::CompassPopupInteractor(Guic* guic)
    : IlvManagerViewInteractor(guic->getCompassManager(),
			       guic->getCompassView()),
     _guic(guic)
{
}

// --------------------------------------------------------------------------
void
CompassPopupInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
IlBoolean
CompassPopupInteractor::handleEvent(IlvEvent& e)
{
    if (e.type() == IlvButtonUp) {
	_guic->showCompassPopup(IlvPoint(e.gx(), e.gy()));
	return IlTrue;
    }
    return getManager()->shortCut(e, getView());
}
