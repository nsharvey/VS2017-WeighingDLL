// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/manager.cpp
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
// Definition of the Manager class
// --------------------------------------------------------------------------

#include <vpf/gui/manager.h>
#include <vpf/gui/palette.h>
#include <vpf/gui/layers.h>
#include <vpf/gui/layer.h>

#include <vpf/area.h>
#include <vpf/segment.h>
#include <vpf/text.h>
#include <vpf/point.h>

#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/mapinfo.h>

#include <ilviews/graphics/polyline.h>
#include <ilviews/manager/quadtree.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/gadgets/stdialog.h>

#include <ilviews/gadgets/fbrowser.h>
#if defined(ILVSTD)
# include <fstream>
# include <cstdio>
ILVSTDUSE
#else
# include <fstream.h>
# include <stdio.h>
#endif

// --------------------------------------------------------------------------
class ManagerViewHook
: public IlvManagerViewHook
{
public:
    ManagerViewHook(Manager* manager, IlvView* view);
    ~ManagerViewHook();

    virtual void transformerChanged(const IlvTransformer*,
				    const IlvTransformer*);
    virtual void viewResized();
    virtual void setCallback(void (*)(IlvView*, IlvAny), IlvAny = 0);
protected:
    void (*_callback)(IlvView*, IlvAny);
    IlvAny _callbackArg;
};

// --------------------------------------------------------------------------
ManagerViewHook::ManagerViewHook(Manager* manager, IlvView* view)
: IlvManagerViewHook(manager, view),
  _callback(0),
  _callbackArg(0)
{
}

// --------------------------------------------------------------------------
ManagerViewHook::~ManagerViewHook()
{
}

// --------------------------------------------------------------------------
void
ManagerViewHook::setCallback(void (*callback)(IlvView*, IlvAny), IlvAny arg)
{
    _callback = callback;
    _callbackArg = arg;
}

// --------------------------------------------------------------------------
void
ManagerViewHook::transformerChanged(const IlvTransformer* current,
				    const IlvTransformer* previous)
{
    IlvRect rect;
    char buffer[80];
    Manager* _Manager = (Manager*)getManager();

    getView()->boundingBox(rect);

    const IlvMapInfo* mapinfo = _Manager->getMapInfo();
    current->inverse(rect);
    IlvCoordinate c1;
    IlvCoordinate c2;
    mapinfo->inverse(IlvPoint(rect.x(), rect.y()), c1);
    mapinfo->inverse(IlvPoint(rect.x()+rect.w(), rect.y()+rect.h()), c2);
    sprintf(buffer,
	    "(%.3f, %.3f)-(%.3f, %.3f)",
	    c1.getX(), c1.getY(),
	    c2.getX(), c2.getY());
    getView()->setTitle(buffer);
    if (_callback)
	_callback(getView(), _callbackArg);
}

// --------------------------------------------------------------------------
void
ManagerViewHook::viewResized()
{
    if (_callback)
	_callback(getView(), _callbackArg);
}

// --------------------------------------------------------------------------
Manager::Manager(IlvDisplay* display, IlvProjection* projection)
: IlvManager(display, 1),
  _mapInfo(0),
  _extent(VpfCoordinate(-180.0, -90.0), VpfCoordinate(180.0, 90.0))
{
    addAccelerator(SaveAccelerator, IlvKeyDown, 's', 0, this);
    addAccelerator(SaveAccelerator, IlvKeyDown, 'S', 0, this);
    
    _mapInfo = new IlvMapInfo(projection);
    _mapInfo->attach(this);
}

// --------------------------------------------------------------------------
Manager::~Manager()
{
    ;
}

//-----------------------------------------------------------------------------
const IlvMapInfo*
Manager::getMapInfo()
{
    return _mapInfo;
}

// --------------------------------------------------------------------------
void
Manager::DestroyCB(IlvView* view, IlvAny)
{
    view->hide();
}

// --------------------------------------------------------------------------
IlvView*
Manager::installView(void (*callback)(IlvView*, IlvAny), IlvAny arg)
{
    IlvView* view = new IlvView(getDisplay(),
				"mgrview",
				"View",
				IlvRect(100, 100, 600, 400),
				IlFalse);

    setKeepingAspectRatio(view, IlTrue);
    IlvManager::addView(view);
    view->setDestroyCallback(DestroyCB);

    //setInteractor(new IlvSelectInteractor(this, view), view);
    
    ManagerViewHook* hook = new ManagerViewHook(this, view);
    hook->setCallback(callback, arg);
    installViewHook(hook);


    //
    // use the adapter to center the view!
    //
    IlvCoordinate ul(_extent.getMinLongitude(), _extent.getMaxLatitude());
    IlvCoordinate lr(_extent.getMaxLongitude(), _extent.getMinLatitude());
    
    _mapInfo->getProjection()->forward(ul, ul);
    _mapInfo->getProjection()->forward(lr, lr);
    _mapInfo->getAdapter()->fitTransformerToRect(view,ul, lr);

    view->show();

    return view;
}


/*void
Manager::emptyLayer(VpfUInt layer) {
  _manager->deleteAll(layer, IlTrue, IlTrue);
}
*/

//-----------------------------------------------------------------------------
void
Manager::forward(const IlvCoordinate&	coordinate,
		 IlvPoint&		point)
{
    IlvCoordinate radians(IlvMaps::DegreeToRadian(coordinate.getX()),
			  IlvMaps::DegreeToRadian(coordinate.getY()));


    _mapInfo->forward(radians, point);
}

// --------------------------------------------------------------------------
void
Manager::add(VpfSegment* segment, Palette* palette, VpfUInt layer)
{
    VpfUInt nCoordinates = segment->getNCoordinates();
    VpfUInt tableCoordinates = 0;
    IlvPoint* points = new IlvPoint[nCoordinates];

    VpfCoordinate* previousCoord = segment->getCoordinate(0);

    forward(*previousCoord, points[0]);
    tableCoordinates++;

    for (VpfUInt j = 1; j < nCoordinates; j++) {
	VpfCoordinate* coord = segment->getCoordinate(j);

	if ((!coord->isNormal() && previousCoord->isNormal()) ||
	    (coord->isNormal() && !previousCoord->isNormal())) {
	    // Feature items might cross the +-180 meridian.
	    // This is not especially nice, but it is so.
	    // To cope with this, we have to split the segment.

	    double dLat = coord->getLatitude() -
		previousCoord->getLatitude();
	    double dLon = coord->getLongitude() -
		previousCoord->getLongitude();
	    VpfCoordinate end;

	    if (previousCoord->getLongitude() <= 180.0) {
		// This is a -180 positive crossing.  
		end.set(-180.0, previousCoord->getLatitude() +
			(-180.0 - previousCoord->getLongitude()) *
			(dLat / dLon));
	    } else
	    if (previousCoord->getLongitude() > 180.0) {
		// This is a +180 negative crossing
		end.set(180.0, previousCoord->getLatitude() +
			(previousCoord->getLongitude() - 180.0) *
			(dLat / dLon));
	    } else
	    if (coord->getLongitude() <= 180.0) {
		// This is a -180 negative crossing;
		end.set(-180.0, previousCoord->getLatitude() +
			(-180.0 - previousCoord->getLongitude()) *
			(dLat / dLon));
	    } else {
		// This is a +180 positive crossing;
		end.set(180.0, previousCoord->getLatitude() +
			(previousCoord->getLongitude() + 180.0) *
			(dLat / dLon));
	    }
	    forward(end, points[tableCoordinates++]);

	    IlvPolyline* g = new IlvPolyline(getDisplay(), tableCoordinates,
					     points, palette->getPalette());
	    delete [] points;
	    invalidateRegion(g);
	    addObject(g, IlFalse, layer);

	    points = new IlvPoint[nCoordinates - j + 2];
	    tableCoordinates = 0;
	    VpfCoordinate begin(- end.getLongitude(), end.getLatitude());
	    forward(begin, points[tableCoordinates++]);
	    forward(*coord, points[tableCoordinates++]);
	} else {
	    forward(*coord, points[tableCoordinates++]);
	}

	previousCoord = coord;
    }

    IlvPolyline* g = new IlvPolyline(getDisplay(), tableCoordinates,
				     points, palette->getPalette());
    delete [] points;
    invalidateRegion(g);
    addObject(g, IlFalse, layer);
}

// --------------------------------------------------------------------------
void
Manager::add(VpfRing* ring, Palette* palette, VpfUInt layer)
{
    VpfUInt nSegments = ring->getNSegments();
    VpfUInt nCoordinates = 0;
    VpfUInt i;
    for (i = 0; i < nSegments; i++)
	nCoordinates += ring->getSegment(i)->getNCoordinates();

    IlvPoint* points = new IlvPoint[nCoordinates];

    VpfUInt currentCoord = 0;
    for (i = 0; i < nSegments; i++) {
	VpfSegment* segment = ring->getSegment(i);
	VpfUInt coordsInSeg = segment->getNCoordinates();
	for (VpfUInt j = 0; j < coordsInSeg; j++) {
	    VpfCoordinate* coord = segment->getCoordinate(j);
	    forward(*coord, points[currentCoord++]);
	}
    }

    // Nota bene: It seems we might reach a limitation of windows 95 here.
    //            That system does not know how to draw polygons with more
    //            than 8191 points properly.
    //            There is a workaround, but it is a very complex one, so
    //            we let this AS IS for the moment.
    IlvPolygon* g = new IlvPolygon(getDisplay(), currentCoord, points,
				   palette->getPalette());
    invalidateRegion(g);
    addObject(g, IlFalse, layer);

    delete [] points;
}

// --------------------------------------------------------------------------
void
Manager::add(VpfArea* area, Palette* palette, VpfUInt layer)
{
    if (!area)
	return;
    VpfUInt nRings = area->getNRings();
    for (VpfUInt i = 0; i < nRings; i++) {
	VpfRing* ring = area->getRing(i);
	if (ring) {
	    add(ring, palette, layer);
	}
    }
}

// --------------------------------------------------------------------------
void
Manager::add(VpfText* text, Palette* palette, VpfUInt layer)
{
    if (!text)
	return;

    IlvPoint point;
    VpfCoordinate* coord = text->getCoordinate();

    forward(*coord, point);

    IlvLabel* g = new IlvLabel(getDisplay(), point, text->getText(),
			       palette->getPalette());
    invalidateRegion(g);
    addObject(g, IlFalse, layer);
}

// --------------------------------------------------------------------------
void
Manager::add(VpfPoint* point, Palette* palette, VpfUInt layer)
{
    if (!point)
	return;

    IlvPoint p;
    VpfCoordinate* coord = point->getCoordinate();

    forward(*coord, p);

    IlvMarker* g = new IlvMarker(getDisplay(), p, palette->getMarkerType(),
				 palette->getMarkerSize(),
				 palette->getPalette());
    invalidateRegion(g);
    addObject(g, IlFalse, layer);
}

// --------------------------------------------------------------------------
void
Manager::startUpdate()
{
    initReDraws();
    IlvSetOptimizeMode(IlTrue);
}

// --------------------------------------------------------------------------
void
Manager::endUpdate()
{
    reDrawViews();
    IlvSetOptimizeMode(IlFalse);
}

// --------------------------------------------------------------------------
void
Manager::saveVpf() const
{
    static IlvFileBrowser* fileoutselector = 0;
    if (!fileoutselector) {
	fileoutselector = new IlvFileBrowser(getDisplay(), 0);
	fileoutselector->setFilter("*.ilv");
	fileoutselector->setDirectory(".");
	fileoutselector->setType(IlvFileSelectorSave);
	fileoutselector->setTitle("Save Rogue Wave Views file");
    }
    
    const char* filename = fileoutselector->get();
    if (!filename || !filename[0])
	return;
    
    ofstream out(filename
#if defined(WINDOWS) || defined(PM)
		 , ios::binary
#endif /* WINDOWS || PM */
		 );
    if (!out) {
	IlvPrint("Couldn't open file %s for writing", filename);
	return;
    }
    
    IlvManager::save(out);
}

//-----------------------------------------------------------------------------
void
Manager::loadVpf(Layers* layers)
{
    static IlvFileBrowser*	fileinselector = 0;

    if(! fileinselector) {
	fileinselector = new IlvFileBrowser(getDisplay(), 0);
	fileinselector->setFilter("*.ilv");
	fileinselector->setDirectory(".");
	fileinselector->setType(IlvFileSelectorLoad);
	fileinselector->setTitle("Load Rogue Wave Views file");
    }
    const char *filename = fileinselector->get();

    if(!filename || !filename[0])
	return;

    IlvManager	mgr(getDisplay(), 2, IlTrue,
		    (IlUShort) ~0, (IlUShort) ~0);
	
	
    mgr.read(filename);

    IlvMapInfo*		mapInfo = IlvMapInfo::Get(&mgr);

    if(! mapInfo) {
	IlvIQuestionDialog	msg(getDisplay(),
				    "The loaded file has no mapInfo\n\
Do you want to continue?");
	msg.showModal();

	if(msg.wasCanceled())
	    return;
    }
    else {
	const IlvProjection*	projection = mapInfo->getProjection();

	IlvClassInfo*	classInfo = projection->getClassInfo();
    
	if(classInfo !=
	   IlvGeographicProjection::ClassInfo()) {
	    char buffer[1024];
	    sprintf(buffer,
		    "The projection (%s) used in file %s\
is not a geographic projection\n\
The loaded graphics will probably be misaligned.\n\
Do you want to continue?",
		    ((IlvProjectionClassInfo*)classInfo)->getProjectionName(),
		    filename);
		
	    IlvIQuestionDialog	msg(getDisplay(), buffer);

	    msg.showModal();
	    if(msg.wasCanceled())
		return;
	}
    }

    const IlUInt	numLayers = mgr.getNumLayers();
	
    for(IlUInt sourceLayerIndex = 0;
	sourceLayerIndex < numLayers;
	sourceLayerIndex++) {
	IlUInt		numLoadedObjects = 0;
	IlvGraphic* const *	const objects = mgr.getObjects(sourceLayerIndex,
							       numLoadedObjects);
	    
	if(numLoadedObjects) {
	    Layer*		layer = layers->addLayer(0);
	    int		destinationIndex
		= getLayerIndex(layer->getManagerLayer());

	    for(size_t i = 0; i < numLoadedObjects; i++) {
		mgr.removeObject(objects[i], IlFalse, IlFalse);
		addObject(objects[i], IlFalse, destinationIndex);
	    }
	}
    }
    reDraw();
}

// --------------------------------------------------------------------------
void
Manager::SaveAccelerator(IlvManager*, IlvView*, IlvEvent&, IlvAny arg)
{
    ((Manager*)arg)->saveVpf();
}
