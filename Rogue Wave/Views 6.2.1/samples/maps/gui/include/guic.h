// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/gui/include/guic.h
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
// Declaration of graphical user interface component viewer.
// --------------------------------------------------------------------------
#ifndef _Guic_H
#define _Guic_H

#include <ilviews/manager/manager.h>
#include <ilviews/gadgets/menu.h>

#include <ilviews/maps/gui/scale.h>
#include <ilviews/maps/gui/coordview.h>
#include <ilviews/maps/gui/compass.h>

class ScalePopupInteractor;
class CoordPopupInteractor;
class CompassPopupInteractor;

// --------------------------------------------------------------------------
class Guic
{
public:
    Guic(IlvDisplay* d, char* file);
    ~Guic();

    void mainWindow(char* file);

    void coordView();
    void compassView();
    void scaleView();

    void coordPopup();
    void scalePopup();
    void compassPopup();

    // Scale
    void showScalePopup(const IlvPoint& p)
	{ _scalepop->get(p, _scaleview); }
    IlvManager* getScaleManager() const
	{ return _scalemanager; }
    IlvView* getScaleView() const
	{ return _scaleview; }

    // Coordinate viewer
    void showCoordPopup(const IlvPoint& p)
	{ _coordpop->get(p, _coordview); }
    IlvManager* getCoordManager() const
	{ return _coordmanager; }
    IlvView* getCoordView() const
	{ return _coordview; }

    // Compass
    IlvManager* getCompassManager() const
	{ return _compassmanager; }
    void showCompassPopup(const IlvPoint& p)
	{ _compasspop->get(p, _compassview); }
    IlvView* getCompassView() const
	{ return _compassview; }
    IlvDisplay* getDisplay() const
	{ return _display; }
    void show()
	{
	    _view->show();
	    _scaleview->show();
	    _coordview->show();
	    _compassview->show();
	}

private:
    IlvDisplay* _display;
    IlvView* _view;

    IlvManager* _scalemanager;
    IlvView* _scaleview;
    IlvPopupMenu* _scalepop;
    ScalePopupInteractor* _scaleinter;

    IlvManager* _coordmanager;
    IlvView* _coordview;
    IlvPopupMenu* _coordpop;
    CoordPopupInteractor* _coordinter;

    IlvManager* _compassmanager;
    IlvView* _compassview;
    IlvPopupMenu* _compasspop;
    CompassPopupInteractor* _compassinter;

    IlvMapScale* _scale;
    IlvMapCoordViewer* _coordviewer;
    IlvMapCompass* _compass;

};

// --------------------------------------------------------------------------
class ScalePopupInteractor
    : public IlvManagerViewInteractor
{
public:
    ScalePopupInteractor(Guic* guic);

    virtual void drawGhost();

    virtual IlBoolean handleEvent(IlvEvent& e);
private:
    Guic* _guic;
};

// --------------------------------------------------------------------------
class CoordPopupInteractor
    : public IlvManagerViewInteractor
{
public:
    CoordPopupInteractor(Guic* guic);

    virtual void drawGhost();

    virtual IlBoolean handleEvent(IlvEvent& e);
private:
    Guic* _guic;
};

// --------------------------------------------------------------------------
class CompassPopupInteractor
    : public IlvManagerViewInteractor
{
public:
    CompassPopupInteractor(Guic* guic);

    virtual void drawGhost();

    virtual IlBoolean handleEvent(IlvEvent& e);
private:
    Guic* _guic;
};
#endif
