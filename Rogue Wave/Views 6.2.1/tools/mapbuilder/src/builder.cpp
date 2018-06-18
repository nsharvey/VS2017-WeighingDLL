// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/builder.cpp
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
// The implementation of MapBuilder methods.
// --------------------------------------------------------------------------
#include <ilviews/bitmaps/io.h>
#include <ilviews/maps/gui/scale.h>
#include <ilviews/maps/gui/compass.h>
#include <ilviews/maps/gui/coordview.h>
#include <ilviews/manager/magview.h>
#if defined(HAS_SDO_SUPPORT)
#include <ildblink/ilddbms.h>
#endif

#include <legend.h>
#include <builder.h>

#if defined(IL_STD)
#  include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#  if !defined(WINDOWS)
#    include <strings.h>
#  endif /* !WINDOWS */
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// Callbacks
static void
ViewFrameDestroyCB(IlvView* view, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    IlvMapScale* scale = (IlvMapScale*)
	      ((IlvGraphicPane*)builder->getPane(MapBuilder::GetScaleName()))
				      ->getObject();
    if (scale) {
	scale->setView(0);
    }
    IlvMapCoordViewer* coords = (IlvMapCoordViewer*)
	((IlvGraphicPane*)builder->getPane(MapBuilder::GetCoordName()))
				 ->getObject();
    IlvViewPane* magPane = (IlvViewPane*)builder->getPane(
					      MapBuilder::GetOverviewName());
    IlvManager* manager = 0;
    IlvManagerMagViewInteractor* mag = 0;
    if (magPane && magPane->getView()) {
        manager = (IlvManager*)magPane->getView()->getProperty(
						    IlvGetSymbol("Manager"));
    }
    if (manager) {
        mag = (IlvManagerMagViewInteractor*)manager->getInteractor(
							 magPane->getView());
    }
    if (mag) {
	mag->abort();
    }
    if (manager && manager->getView(magPane->getView())) {
	manager->removeView(magPane->getView());
    }
    if (mag) {
	delete mag;
	mag = 0;
    }
    if (coords) {
	coords->setView(0);
    }
    builder->destroyBuffer(view, IlTrue);
    if (magPane && magPane->getView()) {
        magPane->getView()->erase(IlTrue);
    }
}

// --------------------------------------------------------------------------
MapBuilder::MapBuilder(const char* name,
		       const char* displayName,
		       int argc,
		       char** argv)
: DockableApplication(name,displayName,argc,argv),
#if HAS_SDO_SUPPORT
  _requestController(0),
#endif
  desktopManager(0),
  bufferList(),
  _currentInteractor(0),
  _sdoAvailable(IlFalse),
#if HAS_SDO_SUPPORT
  _dbms(0),
  _dbmsFactory(0),
#endif
  _statusText(0)
{
#if HAS_SDO_SUPPORT
    if (IlvSDOUtil::EnableDbLink() == IlvMaps::NoError()) {
	_sdoAvailable = IlTrue;
	_dbmsFactory = new IlvDefaultSDODbmsFactory(this);
	IlvSDOUtil::SetDbmsFactory(_dbmsFactory);
    }
#endif
}

// --------------------------------------------------------------------------
MapBuilder::~MapBuilder()
{
}

// --------------------------------------------------------------------------
// Buffer management
MapBuffer*
MapBuilder::makeNewBuffer(IlBoolean visible, IlBoolean destroy)
{
    // Remove all interactors
    for (IlUInt i = 0 ; i < bufferList.length(); i++) {
	MapBuffer* buffer = bufferList.getValue(i);
	IlvManagerViewInteractor* inter =
		      buffer->getManager()->getInteractor(buffer->getView());
	if (inter) {
	    inter->abort();
	    buffer->getManager()->removeInteractor(buffer->getView());
	    delete inter;
	}
    }
    _currentInteractor = 0;
    // Create the new buffer
    MapBuffer* buffer = new MapBuffer(this, desktopManager);
    if (destroy) {
	buffer->getManager()->removeLayer(0);
    }
    bufferList.append(buffer);
    buffer->getFrame()->setDestroyCallback(ViewFrameDestroyCB, this);
    if (visible) {
	buffer->setVisible(IlTrue);
    }
    buffer->getView()->setName("");
    return buffer;
}

// --------------------------------------------------------------------------
IlBoolean
MapBuilder::destroyBuffer(IlvView* view, IlBoolean destroyFrame)
{
    IlvUInt length = bufferList.length();
    // Find the buffer
    MapBuffer* b = 0;
    addInteractor(0); // Delete
    for (IlUInt i = 0; i < length; i++) {
	b = bufferList.getValue(i);
	if (b->getFrame() == view) {
	    Legend* legend =
		(Legend*)((IlvGraphicPane*)getPane(
				  MapBuilder::GetLegendName()))->getObject();
	    IlvMapScale* scale =
		(IlvMapScale*)((IlvGraphicPane*)getPane(
				   MapBuilder::GetScaleName()))->getObject();
	    IlvMapCoordViewer* coords =
		(IlvMapCoordViewer*)((IlvGraphicPane*)getPane(
				   MapBuilder::GetCoordName()))->getObject();
	    if (legend) {
		legend->setTargetView(0);
	    }
	    if (scale) {
		scale->setView(0);
	    }
	    if (coords) {
		coords->setView(0);
	    }
	    bufferList.remove(b);
	    if (destroyFrame) {
		b->destroyFrame();
	    }
	    delete b;
	    return IlTrue;
	}
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
MapBuffer*
MapBuilder::getCurrentBuffer()
{
    const IlvViewFrame* currentFrame = desktopManager->getCurrentFrame();
    if (currentFrame) {
	for (IlUInt i = 0; i < bufferList.length(); i++) {
	    if (bufferList.getValue(i)->getFrame() == currentFrame) {
		return bufferList.getValue(i);
	    }
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
MapBuffer*
MapBuilder::getBuffer(IlvViewFrame* frame)
{
    if (frame) {
	MapBuffer* buffer = 0;
	IlUInt len = bufferList.length();    
	for (IlUInt i = 0; i < len; i++) {
	    buffer = bufferList.getValue(i);
	    if (buffer->getFrame() == frame) {
		return buffer;
	    }
	}
    }
    return 0;
}

#if HAS_SDO_SUPPORT
// --------------------------------------------------------------------------
void
MapBuilder::setDbms(IldDbms* dbms)
{
    _dbms = dbms;
}
#endif

// --------------------------------------------------------------------------
void
MapBuilder::quit()
{
    IlUInt length = bufferList.length();
    for (IlUInt i = 0 ; i < length; i++) {
	MapBuffer* buffer = bufferList.getValue(0);
	destroyBuffer(buffer->getFrame(), IlFalse);
    }
#if HAS_SDO_SUPPORT
    if (_requestController) {
	delete _requestController;
    }
    if (_dbms) {
	delete _dbms;
    }
    if (_dbmsFactory) {
	delete _dbmsFactory;
    }
#endif
    delete _loadFileSelector;
    delete _saveFileSelector;
    _loadFileSelector = 0;
    _saveFileSelector = 0;
    updateOptions();
    saveOptions();
    DockableApplication::quit();
}

// --------------------------------------------------------------------------
void
MapBuilder::reportInfo(const char* message)
{
    IlvTextLocation tl(_statusText->getNumberOfLines()-1, 0);
    _statusText->insertText(message, tl);
    IlvTextLocation tv(_statusText->getNumberOfLines()-1, 0);
    _statusText->ensureVisible(tv);
    _statusText->reDraw();
}

// --------------------------------------------------------------------------
void
MapBuilder::reportError(const char* message)
{
    const char* error = "Error: %s\n";
    char* buffer = new char[strlen(message) + strlen(error) + 1];
    sprintf(buffer, error, message);
    reportInfo(buffer);
    delete [] buffer;
}
