// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/loadOnDemand.cpp
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

#include <ilviews/manager/manager.h>
#include <ilviews/manager/magview.h>
#include <ilviews/base/link.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/label.h>
#include <ilviews/maps/graphics/maplabel.h>
#include <ilviews/maps/graphics/mapgenpath.h>

#include <ilviews/maps/format/dted/dtedreader.h>
#include <ilviews/maps/format/dted/dtedlayer.h>
#include <ilviews/maps/tiling/tilectrl.h>

// --------------------------------------------------------------------------
class TileLoader : public IlvTileLoader
{
public:
    TileLoader(IlvDisplay*);
    virtual IlvMapsError load(IlvTile* tile);
    virtual void release(IlvTile* tile);
    virtual IlBoolean isPersistent() const;
private:
    IlvDisplay* _display;
};


// --------------------------------------------------------------------------
TileLoader::TileLoader(IlvDisplay* display)
    :IlvTileLoader(),
     _display(display)
{
}

// --------------------------------------------------------------------------
IlvMapsError
TileLoader::load(IlvTile* tile)
{
    IlvRect rbbox;
    tile->boundingBox(rbbox);
    IlvRectangle *rect = new IlvRectangle(_display, rbbox);
    tile->addObject(rect);

    IlString str;
    str += "(";
    str += IlString(tile->getColumn());
    str += ", ";
    str += IlString(tile->getRow());
    str += ")";
    
    IlvMapLabel* label = new IlvMapLabel(_display,
                                      IlvPoint(),
                                      IlvPoint(),
                                      IlvCenter,
                                      10,
                                      str.getValue());    
    IlvRect lbbox;
    label->boundingBox(lbbox);
    IlvPos cx = rbbox.x() + rbbox.w() / 2;
    IlvPos cy = rbbox.y() + rbbox.h() / 2;
    label->move(cx - lbbox.w() / 2,
                cy - lbbox.h() / 2);
    tile->addObject(label);
     
    tile->loadComplete();
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
void
TileLoader::release(IlvTile* tile) {   
    tile->deleteAll();      
}

    
// --------------------------------------------------------------------------
IlBoolean
TileLoader::isPersistent() const {
    return IlFalse;
}

// --------------------------------------------------------------------------
class TileCache;

// --------------------------------------------------------------------------
class TiledLayer : public IlvTiledLayer
{
public:
    TiledLayer(IlvDisplay* display, IlvTileCache* cache = 0);
private:
    IlvTileLoader* _tileLoader;
};

// --------------------------------------------------------------------------
TiledLayer::TiledLayer(IlvDisplay* display, IlvTileCache* cache)
    :IlvTiledLayer(IlvRect(0, 0, 20, 20), cache)
{
    IlvTileController* ctrl;
    ctrl = getTileController();
    if(ctrl) {
	_tileLoader = new TileLoader(display);
	ctrl->setTileLoader(_tileLoader);
	ctrl->enableStart(IlvRect(0, 0, 20, 20),
			  IlvRect(0, 0, 20, 20));
    }
}

// --------------------------------------------------------------------------
class TileCache : public IlvTileCache
{
public:
    TileCache(int size);
    TileCache(IlvInputFile& file);
    virtual void tileAboutToLoad(IlvTile *);    
    virtual void tileCached(IlvTile *);
    virtual void tileRetrieved(class IlvTile *);
    virtual void controllerDeleted(IlvTileController *);
    virtual void write(IlvOutputFile& output) const;
private:
    int _size;
    IlList _tiles;
};

// --------------------------------------------------------------------------
TileCache::TileCache(int size)
    :IlvTileCache(),
     _size(size)
{
}

// --------------------------------------------------------------------------
TileCache::TileCache(IlvInputFile& file)
    :IlvTileCache()
{
    file.getStream() >> _size;
}

// --------------------------------------------------------------------------
void
TileCache::write(IlvOutputFile& output)  const
{
    output.getStream() << _size;
}

// --------------------------------------------------------------------------
void
TileCache::tileCached(IlvTile *tile)
{
    _tiles.append(tile);
}

// --------------------------------------------------------------------------
void
TileCache::tileRetrieved(IlvTile* tile)
{
    _tiles.remove(tile);
}

// --------------------------------------------------------------------------
void
TileCache::tileAboutToLoad(IlvTile *tile)
{
    int toRemove = _tiles.length() - _size;
    if (toRemove <= 0)
      return;
    for (int i = toRemove; i > 0; i--) {
        IlvTile* current = (IlvTile*)_tiles[0];
        _tiles.remove(current);
        releaseTile(current);
    }
}

// --------------------------------------------------------------------------
void
TileCache::controllerDeleted(IlvTileController* controller)
{
    IlvLink* l;
    l = _tiles.getFirst();
    IlvTile* tile;
    while (l) {
        tile = (IlvTile*) l->getValue();
        l = l->getNext();
        if (tile->getController() == controller)
            _tiles.remove(tile);
    }
}

// --------------------------------------------------------------------------
class Listener : public IlvTileListener
{
public:
    Listener(IlvManager*, IlvView*);
    virtual void tileChanged(IlvTile* tile,
			     IlvTileStatus oldStatus,
			     IlvTileStatus newStatus);
    virtual void beginGroupedNotification(IlvTileController *);
    virtual void endGroupedNotification(IlvTileController *);
    virtual void controllerDeleted(IlvTileController *);
private:
    IlvManager* _manager;
    IlvView* _view;
};

// --------------------------------------------------------------------------
Listener::Listener(IlvManager* manager,
		   IlvView* view)
    :IlvTileListener(),
     _manager(manager),
     _view(view)
{
}

// --------------------------------------------------------------------------
static const char*
toString(IlvTileStatus status)
{
    switch(status) {
    case IlvTileEmpty:
        return "IlvTileEmpty";
    case IlvTileLocked:
        return "IlvTileLocked";
    case IlvTileCached:
        return "IlvTileCached";
    case IlvTileDeleted:
        return "IlvTileDeleted";
    default:
	return "??";
    }
}

// --------------------------------------------------------------------------
void
Listener::tileChanged(IlvTile* tile,
                          IlvTileStatus oldStatus,
                          IlvTileStatus newStatus)
{
    IlvPrint("tile %d %d status changed from %s to %s",
             tile->getRow(), tile->getColumn(),
             toString(oldStatus),
             toString(newStatus));
}

// --------------------------------------------------------------------------
void
Listener::beginGroupedNotification(IlvTileController* t)
{
}

// --------------------------------------------------------------------------
void
Listener::endGroupedNotification(IlvTileController* t)
{
}

// --------------------------------------------------------------------------
void
Listener::controllerDeleted(IlvTileController* controller)
{
    
}

// --------------------------------------------------------------------------
class SimpleLod
{
public:
    SimpleLod(IlvDisplay* display);
    void show();
    void makeWindow();
    void tiledLayer();
    void displayTileStatus(int row, int col);
    void debugView();
    void magView();
    void listener();
private:
    IlvDisplay* _display;
    IlvManager* _manager;
    IlvView* _view;
    IlvTiledLayer* _tiledLayer;
    IlvManagerMagViewInteractor* _magvint;
    IlvView* _debug;
    Listener* _listener;
};

// --------------------------------------------------------------------------
void
SimpleLod::displayTileStatus(int row, int col)
{
    IlvTile* tile = _tiledLayer->getTileController()->getTile(col, row);
    if (!tile)
       IlvPrint("The tile  %d %d is not yet loaded",
                col, row);
    else {
        IlvTileStatus status;
        status = tile->getStatus();
        switch(status) {
        case IlvTileEmpty:
            IlvPrint("The tile %d %d is empty", col, row);
            break;
        case IlvTileLocked:
            IlvPrint("The tile  %d %d is locked", col, row);
            break;
        case IlvTileCached:
            IlvPrint("The tile  %d %d is cached", col, row);
            break;
        case IlvTileDeleted:
            IlvPrint("The tile  %d %d is deleted", col, row);
            break;
        }
    }
}

// --------------------------------------------------------------------------
SimpleLod::SimpleLod(IlvDisplay* display)
    :_display(display),
     _manager(0),
     _view(0),
     _tiledLayer(0),
     _magvint(0),
     _debug(0),
     _listener(0)
{
    makeWindow();
    tiledLayer();
    debugView();
    magView();
    listener();
}

// --------------------------------------------------------------------------
void
SimpleLod::show()
{
    _view->show();
    if(_debug)
	_debug->show();
}

// --------------------------------------------------------------------------
void
SimpleLod::debugView() {
    _debug = new IlvView(_display,
                         "DebugView",
                         "DebugView",
                         IlvRect(450, 0, 100, 100),
                         IlFalse, IlFalse);
    _manager->addView(_debug);
    _tiledLayer->setDebugView(_debug);
}

// --------------------------------------------------------------------------
void
SimpleLod::magView()
{
    _magvint = new IlvManagerMagViewInteractor(_manager, _debug, _view);

    _magvint->setAutoZooming(IlTrue);
    _magvint->setAutoTranslating(IlTrue);
    _magvint->setResizingAllowed(IlTrue);

    _manager->setInteractor(_magvint, _debug);
}

// --------------------------------------------------------------------------
void
SimpleLod::listener()
{
    _listener = new Listener(_manager, _view);
    _tiledLayer->getTileController()->addTileListener(_listener);
}

// --------------------------------------------------------------------------
static void
Exit(IlvView* view, IlvAny a)
{
    IlvDisplay* display = view->getDisplay();
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
void
SimpleLod::makeWindow()
{
    _manager = new IlvManager(_display);
    _view = new IlvView(_display, "SimpleLod", "SimpleLod",
			IlvRect(0, 0, 400, 300), IlFalse);
    _manager->addView(_view);
    _view->setDestroyCallback(Exit, 0);
}

// --------------------------------------------------------------------------
void
SimpleLod::tiledLayer()
{
     _tiledLayer = new TiledLayer(_display,
				   new TileCache(50));
     IlvMapsError status;
     status = _tiledLayer->getInitStatus();
     if(status != IlvMaps::NoError()) {
	 IlvPrint("IlvTILEDLayer -> %s",
		  IlvMaps::GetErrorMessage(status, _display));
     } else {
	 _manager->addLayer(_tiledLayer);
	 _tiledLayer->fitTransformerToTile(_view, 0, 0);
	 _tiledLayer->start();
     }
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay(argv[0], "", argc, argv);
    if(display -> isBad()) {
	IlvPrint("Can't open display");
	delete display;
	exit(1);
    }

    SimpleLod tl(display);
    tl.show();
    
    IlvMainLoop();

    exit(0);
}

