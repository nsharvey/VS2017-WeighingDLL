// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/include/mysdopan.h
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
//
// --------------------------------------------------------------------------
#ifndef __mysdopan__header__
#define __mysdopan__header__

#include <sdopan.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/maps/coord.h>

#include <ilog/sstream.h>

class IldDbms;
class IldRequest;
class IlvMapFeatureIterator;
class IlvSDOWriter;
class IlvPanZoomInteractor;
class IlvMapFeatureIterator;
class IlvSDOFeatureIterator;
class IlvTileCache;
class IlvManagerMagViewInteractor;
class IlvObjectSDOWriter;
class IlvTiledLayer;
class IlvDefaultSDODbmsFactory;
class IlvMapInfo;
class IlvTileListener;
class IlvFeatureAttributeInfo;
class IlvFeatureAttributeProperty;
class MySelectInteractor;
class IlvZoomInteractor;

// --------------------------------------------------------------------------
class MySdopan
    : public Sdopan
{
public:
   MySdopan(IlvDisplay* display,
             const char* name,
             const char* title,
             IlvRect*    size            = 0,
             IlBoolean  useAccelerators = IlFalse,
             IlBoolean  visible         = IlFalse,
             IlUInt     properties      = 0,
             IlvSystemView transientFor  = 0);

    MySdopan(IlvAbstractView* parent,
             IlvRect* size = 0,
             IlBoolean useacc = IlFalse,
             IlBoolean visible = IlTrue);
    virtual ~MySdopan();

    virtual void init();
    void initDebugView(IlvTiledLayer* layer);
    void fitToTile(IlvTiledLayer* layer);
    void initMagView();

    void setUseExtentOf(IlBoolean b)
	{ _useExtentOf = b; }
    IlBoolean isUseExtentOf()
	{ return _useExtentOf; }
    void setColArraySize(IlInt val)
	{ _colarraysize = (IlUInt)val; }
    IlUInt getColArraySize() const
	{ return _colarraysize; }
    void setTilingLevel(IlInt val)
	{ _tilingLevel = val; }
    IlInt getTilingLevel() const
	{ return _tilingLevel; }
    const char* getFileName() const
	{ return _fileName; }
    const char* getGeometryName()
	{ return _geometryColumnName.getValue(); }
    void setDbms(IldDbms*);
    IldDbms* getDbms() const
	{ return _dbms; }
    void setUserName(const char* name)
	{ _userName = IlString(name); }
    const char* getUserName() const
	{ return _userName; }
    void setLayerName(const char* name)
	{ _layerName = IlString(name); }
    void setGeometryColumnName(const char* name)
	{ _geometryColumnName = IlString(name); }
    const char* getLayerName() const
	{ return _layerName; }
    IlvCoordinate getLayerUpperLeftCorner() const
	{ return _layerUpperLeftCorner; }
    IlvCoordinate getLayerLowerRightCorner() const
	{ return _layerLowerRightCorner; }
    void setLayerUpperLeftCorner(const IlvCoordinate& c)
	{ _layerUpperLeftCorner = c; }
    void setLayerLowerRightCorner(const IlvCoordinate& c)
	{ _layerLowerRightCorner = c; }
    IlvGadgetContainer* getWhichLayerPanel() const
	{ return _whichLayerPanel; }
    IlvGadgetContainer* getNewLayerPanel() const
	{ return _newLayerPanel; }
    IlvGadgetContainer* getTilingPanel() const
	{ return _tilingPanel; }
    IlvGadgetContainer* getColArrayPanel() const
	{ return _colarrayPanel; }

    virtual void lodCB(IlvGraphic*);
    virtual void connectCB(IlvGraphic*);
    virtual void selectCB(IlvGraphic*);
    virtual void eraseCB(IlvGraphic*);
    virtual void dbSaveCB(IlvGraphic*);
    virtual void dbLoadCB(IlvGraphic*);
    virtual void newCB(IlvGraphic*);
    virtual void loadCB(IlvGraphic*);
    virtual void saveCB(IlvGraphic*);
    virtual void panCB(IlvGraphic*);
    virtual void zoomInCB(IlvGraphic*);
    virtual void zoomCB(IlvGraphic*);
    virtual void unzoomCB(IlvGraphic*);
    virtual void fitToSizeCB(IlvGraphic*);
    virtual void computeCB(IlvGraphic*);
    virtual void tracesCB(IlvGraphic*);
    virtual void resetCB(IlvGraphic*);
    virtual void exitCB(IlvGraphic*);
    virtual void openCB(IlvGraphic*);
    virtual void colarrayCB(IlvGraphic*);

    IlBoolean checkDbms();
    void updateGauge(IlvFloat value);
    void initGauge(IlvFloat max);
    virtual void reportError(const char* text);
    virtual void reportDBError(const char* text);
    virtual void reportInfo(const char* text);
    virtual void reportTraces();
    IlInt getAvailableGid(const char* sdoLayerName);
    IldRequest* executeQuery(const char* query, IlUShort colArraySize);
    IlInt writeFeatureIterator(IlvMapFeatureIterator* reader,
			       IlvSDOWriter* writer);
    IlInt writeFeatureIterator(IlvMapFeatureIterator* reader,
			       IlvObjectSDOWriter* writer);
    void whichLayer();
    IlvTileCache* getSDOCache();
    void waitCursor();
    void defaultCursor();

    void initializeFileBrowser();

    MySelectInteractor*        _select;
    IlBoolean                  _isDropping;
    IlvMapFeatureIterator*     _reader;
    IlvFeatureAttributeInfo*   _info;

private:
    static IlvTileCache* _Cache;

    IldDbms*                _dbms;
    IlString                _fileName;
    IlString                _userName;
    IlString                _layerName;
    IlString                _geometryColumnName;
    IlvFileBrowser*         _fileBrowserIlv;
    IlvFileBrowser*         _fileBrowserShp;
    IlvGadgetContainer*     _whichLayerPanel;
    IlvGadgetContainer*     _newLayerPanel;
    IlvGadgetContainer*     _tilingPanel;
    IlvGadgetContainer*     _colarrayPanel;
    IlvView*                _debugView;
    IlvMapFeatureIterator*  _sdoReader;
    IlvPanZoomInteractor*   _pan;
    IlvZoomInteractor*      _zoom;
    IlvManagerMagViewInteractor* _mag;
    IlInt                   _nbFeatures;
    IlInt                   _tilingLevel;
    IlvCoordinate           _layerUpperLeftCorner;
    IlvCoordinate           _layerLowerRightCorner;
    ILVSTDPREF ostrstream   _stream;
    IlvDefaultSDODbmsFactory*  _dbmsFactory;
    IlvMapInfo*                _mapinfo;
    IlvTileListener*           _listener;
    IlUInt                     _colarraysize;
    IlBoolean                  _useExtentOf;
};

// --------------------------------------------------------------------------
class AttributesPanel
    : public IlvGadgetContainer
{
public:
    AttributesPanel(MySdopan* pan, IlvFeatureAttributeProperty* ap);

    void addAttribute(IlString& name, IlString& value);
    void init(MySdopan* pan, IlvFeatureAttributeProperty* ap);

    MySdopan* _pan;
    IlvRect _labelBBox;
};

// --------------------------------------------------------------------------
class MySelectInteractor
    : public IlvSelectInteractor
{
public:
    MySelectInteractor(IlvManager* manager,
		       MySdopan* pan);
    virtual void doSelect();

    MySdopan* _pan;
    AttributesPanel* _attrPan;
};

#endif
