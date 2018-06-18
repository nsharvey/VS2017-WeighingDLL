// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/reader.cpp
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
// Definition of the IlvVpfReader class
// --------------------------------------------------------------------------

#include <ilviews/maps/projection/allprojs.h>

#include <vpf/gui/reader.h>
#include <vpf/gui/manager.h>
#include <vpf/gui/layers.h>
#include <vpf/gui/views.h>
#include <vpf/gui/database.h>
#include <vpf/gui/error.h>

#include <ilviews/graphics/label.h>
#include <stdio.h>
#include <ilviews/base/pathname.h>

static const char* GetResourceFileName(IlvDisplay* display,const char*name)
{
    static char path[2048];
    const char* home=display->getEnvOrResource("ILVMAPSHOME");
    sprintf(path,"%s/%s",home?home:".",name);
    if (IlvFileExists(path)) {
	return path;
    } else {
	home=display->getEnvOrResource("ILVHOME");
	sprintf(path,"%s/%s",home?home:".",name);
	if (IlvFileExists(path)) {
	    return path;
	}
    }
    return name;
}

IlvVpfReader::IlvVpfReader(IlvDisplay* display)
: Application(display),
  _display(display)
{
    _container =
	new IlvGadgetContainer(_display,
			       "Rogue Wave Views VPF reader",
			       "Rogue Wave Views Vector Product Format reader",
			       IlvRect(0, 0, 100, 100),
			       IlFalse,
			       IlFalse);
    _container->readFile(GetResourceFileName(display,
					  "tools/readers/vpf/data/reader.ilv"));
    _container->setDestroyCallback(destroyCB, this);
    _container->show();
    _status = (IlvLabel*)_container->getObject("status");

    IlvProjection* projection = new IlvGeographicProjection;

    _manager = new Manager(_display, projection);
    _views = new Views(_container, _manager);
    _layers = new Layers(_container, _manager);
    _database = new Database(_container, _layers);
}

// --------------------------------------------------------------------------
IlvVpfReader::~IlvVpfReader()
{
    if (_manager)
	delete _manager;
    if (_layers)
	delete _layers;
    if (_database)
	delete _database;
    if (_container)
	delete _container;
}

// --------------------------------------------------------------------------
void
IlvVpfReader::destroyCB(IlvView* view, IlvAny arg)
{
    IlvVpfReader* reader = (IlvVpfReader*)arg;
    IlvDisplay* display = view->getDisplay();
    view->hide();
    delete reader;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
void
IlvVpfReader::setBusy(IlBoolean busy)
{
    Application::setBusy(busy);
    _layers->setBusy(busy);
    _database->setBusy(busy);
}

// --------------------------------------------------------------------------
void
IlvVpfReader::setStatus(const char* status)
{
    IlvRect oldbbox;
    IlvRect newbbox;
    _status->boundingBox(oldbbox);
    _status->setLabel(status ? status : "Ready");
    _status->move(oldbbox.x(), oldbbox.y());
    _status->boundingBox(newbbox);
    oldbbox.add(newbbox);
    _container->bufferedDraw(oldbbox);
}

// --------------------------------------------------------------------------
void
IlvVpfReader::handleError()
{
    Error::HandleError(_display, _container);
}
