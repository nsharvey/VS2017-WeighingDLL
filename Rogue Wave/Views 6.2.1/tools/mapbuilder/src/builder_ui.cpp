// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/builder_ui.cpp
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
// The implementation of MapBuilder UI methods.
// --------------------------------------------------------------------------
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/graphics/lablist.h>
#include <ilviews/manager/magview.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/manager/zoomint.h>
#include <ilviews/maps/format/maploader.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/format/dted/dtedreader.h>
#include <ilviews/maps/format/dted/dtedlayer.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/shpfile.h>
#include <ilviews/maps/format/cadrg/cadrgread.h>
#include <ilviews/maps/format/cadrg/cadrglayer.h>
#include <ilviews/maps/format/cadrg/cadrgtoc.h>
#if defined(HAS_SDO_SUPPORT)
#include <ilviews/maps/format/oracle/objectmodel/8ilayer.h>
#include <ilviews/maps/format/oracle/objectmodel/8iread.h>
#include <ilviews/maps/format/oracle/objectmodel/8iutil.h>
#include <ildblink/ilddbms.h>
#endif
#include <ilviews/maps/gui/scale.h>
#include <ilviews/maps/gui/coordview.h>
#include <ilviews/maps/gui/compass.h>
#include <ilviews/bitmaps/io.h>
#include <ilviews/bitmaps/bmp.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/bitmaps/ppm.h>
#include <ilviews/bitmaps/pbm.h>
#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/bmpread.h>
#include <ilviews/bitmaps/streamer.h>
#include <ilviews/gadgets/vframe.h>
#include "builder.h"
#include "desktop.h"
#include "readctrl.h"
#include "legend.h"

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
#  include <cctype>
IL_STDUSE
#else  /* !IL_STD */
#  include <iostream.h>
#  include <fstream.h>
#  include <ctype.h>
#  include <string.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

#include <ilviews/base/sstream.h>
#if defined(WINDOWS)
#  include <windows.h>
#endif

// --------------------------------------------------------------------------
#if 0
// For debug only
inline IlvString
ToEvendenString(const IlvProjection* object)
{
    if (object) {
	ostrstream  stream;
	object->printPROJ4Descriptor(stream);
	stream << ends;
#if 0
	char* s = stream.str();
#else
	extern char* IlvGetStringFrom(ostrstream&);
	char* s = IlvGetStringFrom(stream);
#endif	

	IlvString   result(s);
	stream.rdbuf()->freeze(0);
	return result;
    }
    IlvString result("NULL");
    return result;
};
#endif

// --------------------------------------------------------------------------
class MyMainMenuBarPane
    : public IlvAbstractBarPane
{
public:
    MyMainMenuBarPane(const char* name, IlvAbstractBar* bar)
    : IlvAbstractBarPane(name, bar) {}
    virtual void setContainer(IlvPanedContainer* container)
	{
	    IlvAbstractBarPane::setContainer(container);
	    if (container) {
		checkLabelOrientation();
	    }
	}
    virtual void orientationChanged()
	{
	    checkLabelOrientation();
	    IlvAbstractBarPane::orientationChanged();
	}
    void checkLabelOrientation()
	{
	    IlvDockable* dockable = IlvDockable::GetDockable(this);
	    getBar()->setLabelOrientation(dockable && dockable->isDocked()
					  ? getBar()->getOrientation()
					  : IlvHorizontal,
					  IlFalse,
					  IlFalse);
	}
};

// --------------------------------------------------------------------------
// Change sensitivity of an item, depending on the current view
class ViewDependentMenuItemSensitivitySelector
    : public MapDesktopManagerListener
{
public:
    ViewDependentMenuItemSensitivitySelector(IlvMenuItem* menuItem,
					     MapBuilder* b)
        : item(menuItem),
	  builder(b)
    { }

    IlvMenuItem* getItem() const { return item; }
    
    virtual void frameSelectionChanged(IlvViewFrame* newFrame,
				       IlvViewFrame* oldFrame)
	{
	    if ((newFrame != 0) &&
		(newFrame->getCurrentState() !=
				    IlvViewFrame::IlvFrameMinimizedState)) {
		if (!getItem()->isSensitive()) {
		    getItem()->setSensitive(IlTrue);
		}
	    }
	    else {
		getItem()->setSensitive(IlFalse);
	    }
	}
    virtual void frameMinimized(IlvViewFrame* frame, int previousState)
	{}
    virtual void frameMaximized(IlvViewFrame* frame, int previousState)
	{
	    if (!getItem()->isSensitive()) {
		getItem()->setSensitive(IlTrue);
	    }
	}
    virtual void frameRestored(IlvViewFrame* frame, int previousState)
	{
	    if (!getItem()->isSensitive()) {
		getItem()->setSensitive(IlTrue);
	    }
	}
private:
    IlvMenuItem* item;
    MapBuilder* builder;
};

// --------------------------------------------------------------------------
// Listener to change view on map gui components
class ViewUpdater
    : public MapDesktopManagerListener
{
public:
    ViewUpdater(MapBuilder* b)
        : builder(b),
	  isNewFrame(IlTrue),
	  mag(0)
    {}
    // This method handles frame selection changes from the desktop manager
    virtual void frameSelectionChanged(IlvViewFrame* newFrame,
				       IlvViewFrame* oldFrame)
    {
	if (oldFrame) {
	    MapBuffer* buffer = builder->getBuffer(oldFrame);
	    IlvManager* manager =  buffer->getManager();
	    abortInteractor(buffer);
	    IlvViewPane* magPane =
	       (IlvViewPane*)builder->getPane(MapBuilder::GetOverviewName());
	    if (manager->getView(magPane->getView())) {
		manager->removeView(magPane->getView());
	    }
	    if (mag) {
		delete mag;
		mag = 0;
	    }
	}
	updateUI(newFrame);
    }
    virtual void frameAdded(IlvViewFrame* frame)
	{ isNewFrame = IlTrue; }
    
    // Updates the UI when a frame is minimized
    virtual void frameMinimized(IlvViewFrame* frame, int previousState)
    {
	if (previousState != IlvViewFrame::IlvFrameMinimizedState) {
	    updateUI(frame);
	}
    }
    // updates the UI when a frame is maximized
    virtual void frameMaximized(IlvViewFrame* frame, int previousState)
    {
	updateUI(frame);
    }
    // updates the UI when a frame is restored
    virtual void frameRestored(IlvViewFrame* frame, int previousState)
    {
	if (previousState == IlvViewFrame::IlvFrameMinimizedState) {
	    updateUI(frame);
	}
    }
private :
    // This method updates the UI, depending of the specified frame
    void updateUI(IlvViewFrame* frame) {
	Legend* legend = (Legend*)
	    ((IlvGraphicPane*)builder->getPane(MapBuilder::GetLegendName()))
				     ->getObject();
	IlvMapScale* scale = (IlvMapScale*)
	    ((IlvGraphicPane*)builder->getPane(MapBuilder::GetScaleName()))
				     ->getObject();
	IlvMapCoordViewer* coords = (IlvMapCoordViewer*)
	    ((IlvGraphicPane*)builder->getPane(MapBuilder::GetCoordName()))
				     ->getObject();
	IlvViewPane* magPane = (IlvViewPane*)builder->getPane(
					      MapBuilder::GetOverviewName());
	if ((frame != 0) &&
	    (frame->getCurrentState() !=
				     IlvViewFrame::IlvFrameMinimizedState)) {
	    if (magPane && builder->getCurrentBuffer()) {
		IlvManager* manager = builder->getCurrentBuffer()
					     ->getManager();
		IlvView* source = magPane->getView();
		if (!manager->getView(source)) {
		    manager->addView(source);
		}
		manager->setDoubleBuffering(source, IlTrue);
		manager->setKeepingAspectRatio(source, IlTrue);
		mag = new IlvManagerMagViewInteractor(manager,
						      source,
				     builder->getCurrentBuffer()->getView());
		IlvRectangle* rect = new IlvRectangle(manager->getDisplay(),
						      IlvRect(0, 0, 50, 50));
		rect->setForeground(manager->getDisplay()->getColor("cyan"));
		mag->setGraphic(rect);
		mag->setAutoZooming(IlTrue);
		mag->setAutoZoomConstrained(IlTrue);
		mag->setAutoTranslating(IlTrue);
		mag->setResizingAllowed(IlTrue);
		manager->setInteractor(mag, source);
		if (!isNewFrame) {
		    mag->resetOverview();
		}
		mag->computeRectangle();
		mag->invalidateGraphic(IlFalse);
		isNewFrame = IlFalse;
	    }
	    if (legend && builder->getCurrentBuffer()) {
		legend->setTargetView(builder->getCurrentBuffer()
					     ->getView());
		legend->reDraw();
	    }
	    if (scale && builder->getCurrentBuffer()) {
		scale->setView(builder->getCurrentBuffer()->getView());
		scale->reDraw();
	    }
	    if (coords && builder->getCurrentBuffer()) {
		coords->setView(builder->getCurrentBuffer()->getView());
		coords->reDraw();
	    }
#if defined(HAS_SDO_SUPPORT)
	    if (builder->_requestController) {
		builder->_requestController->updateController();
	    }
#endif
	}
	else {
	    if (legend) {
		legend->setTargetView(0);
	    }
	    if (scale) {
		scale->setView(0);
	    }
	    if (coords) {
		coords->setView(0);
	    }
#if defined(HAS_SDO_SUPPORT)
	    if (builder->_requestController) {
		builder->_requestController->updateController();
	    }
#endif
	}
    }
    // Removes all interactors from the manager of specified buffer
    void abortInteractor(MapBuffer* buffer) {
	if (buffer) {
	    IlvManager* manager = buffer->getManager();
	    manager->deSelectAll();
	    IlvManagerViewInteractor* inter =
				   manager->getInteractor(buffer->getView());
	    if (inter) {
		inter->abort();
	    }
	}
    }
private:
    MapBuilder* builder;
    IlvManagerMagViewInteractor* mag;
    IlBoolean isNewFrame;
};

// --------------------------------------------------------------------------
// An IlvSelectInteractor that does not allow objects to be edited
class ListBox
    : public IlvContainer
{
public:
    ListBox(IlvView* v)
    : IlvContainer(v->getDisplay(),
		   "Attributes",
		   "Attributes",
		   IlvRect(),
		   IlvNoResizeBorder,
		   IlFalse,
		   IlFalse,
		   v->getSystemView())
    {
	IlvDisplay* display = v->getDisplay();
	_list = new IlvListLabel(display, IlvPoint(), 0, 0, 0);
	addObject(_list);
	setDestroyCallback(destroyCB);
    }
    
    virtual ~ListBox()
    {
	removeObject(_list);
    }
    
    void addLabel(const char* label) {
	_list->addLabel(label);
    }
    
    void clear() {
	_list->setLabels(0, 0);
    }
    
    virtual void show() {
	fitToContents();
	adjust();
	if (!isVisible()) {
	    moveToMouse(IlvTopLeft);
	}
	raise();
	IlvContainer::show();
	_list->reDraw();
    }

    void adjust() {
	IlvRect r;
	boundingBox(r);
	resize(r.w() + 8, r.h() + 8);
	_list->move(4, 4);
    }
private:
    static void
    destroyCB(IlvView* v, IlvAny a) {
	ListBox* view = (ListBox*) v;
	view->hide();
    }

    IlvListLabel* _list;
    IlvButton* _close;
};

// --------------------------------------------------------------------------
class NonEditableSelectInteractor
    : public IlvSelectInteractor
{
public:
    NonEditableSelectInteractor(IlvManager* manager,
				IlvView* view)
    : IlvSelectInteractor(manager,view) {
	_list = new ListBox(view);
    }
    ~NonEditableSelectInteractor() {
	delete _list;
    }
    virtual void doTranslate(const IlvPoint &) { }
    virtual void doReshape(IlvGraphic* ,const IlvRect &) { }
    virtual void drawGhostMove(IlvGraphic* ,IlvRegion* ) { }
    virtual void drawGhostReshape(IlvGraphic*,IlvRegion*) { }
    virtual void detach() {
	_list->hide();
    }
    virtual void abort() {
	_list->hide();
    }
    virtual void doSelect() {
	IlUInt nb = 0;
	IlvGraphic* const* graphics = getManager()->getSelections(nb);
	if (nb != 1) {
	    _list->hide();
	    return;	    
	}
	IlvGraphic* gr = graphics[0];
	showAttributes(gr);
    }
    // Lists the attributes of the given IlvGraphic
    void showAttributes(IlvGraphic* g) {
	if (!g) {
	    return;
	}
	_list->clear();
	char buf[512];
	IlvFeatureAttributeProperty* ap =
	    (IlvFeatureAttributeProperty*)g->
	    getNamedProperty(IlvFeatureAttributeProperty::GetName());
	if (!ap) {
	    return;
	}
	const IlvFeatureAttributeInfo* info = ap->getInfo();
	if (info) {
	    IlUInt count;
	    count = info->getAttributesCount();
	    for (IlUInt i = 0; i < count; i++) {
		buf[0] = 0;
		const char* name = info->getAttributeName(i);
		const IlvMapClassInfo* clsinfo = info->getAttributeClass(i);
		const IlvFeatureAttribute* fa = ap->getAttribute(i);
		if (!fa) {
		    continue;
		}
		if (clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
		    const char *str = ((IlvStringAttribute*)fa)->getValue();
		    if (str) {
			sprintf(buf, "%s: %s", name ? name : "",
				str ? str : "");
		    }
		}
		else if (clsinfo->isSubtypeOf(
					 IlvIntegerAttribute::ClassInfo())) {
		    int in = ((IlvIntegerAttribute*)fa)->getValue();
		    sprintf(buf, "%s: %d", name ? name : "", in);
		}
		else if (clsinfo->isSubtypeOf(
					  IlvDoubleAttribute::ClassInfo())) {
		    double dbl = ((IlvDoubleAttribute*)fa)->getValue();
		    sprintf(buf, "%s: %g", name ? name : "", dbl);
		}
		else if (clsinfo->isSubtypeOf(
					 IlvBooleanAttribute::ClassInfo())) {
		    IlBoolean bo=((IlvBooleanAttribute*)fa)->getValue();
		    sprintf(buf, "%s: %s", name ? name : "",
			    bo ? "true" : "false");
		}
		if (buf[0]) {
		    size_t l = strlen(buf);
		    char* pt = &buf[l - 1];
		    if (*pt == ' ') {
			while((*pt == ' ') && (pt > buf)) {
			    pt --;
			}
			pt ++;
			*pt = 0;
		    }
		    _list->addLabel(buf);
		}
	    }
	}
	_list->show();
    }
private:
    ListBox *_list;
};

// --------------------------------------------------------------------------
// Callbacks
static void
NewMapBufferCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    builder->makeNewBuffer();
    builder->updateBufferDependentUI();
}

// --------------------------------------------------------------------------
static void
SaveBufferAsCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* buffer= builder->getCurrentBuffer();
    if (!buffer) {
	return;
    }
    IlvIFileSelector* selector = builder->getSaveFileBrowser();
    selector->moveToView(builder->getMainWindow());
    const char* selection = selector->get();
    if (selection) {
	if (IlvFileExists(selection)) {
	    IlvIQuestionDialog dialog(selector->getDisplay(),
				      (IlString("Do you want to override ")
				       + IlString(selection)
				       + IlString("?")).getValue(),
				      0,
				      IlvDialogOkCancel,
				      buffer->getView()->getParent()
						       ->getSystemView());
	    dialog.moveToView(builder->getMainWindow());
	    dialog.setTitle("File exists");
	    IlBoolean ok = dialog.get();
	    if (!ok) {
		return;		
	    }
	}
	IlvViewPane* magPane = (IlvViewPane*)builder->getPane(
					      MapBuilder::GetOverviewName());
	IlvManager* m = buffer->getManager();
	IlvView* v = magPane->getView();
	IlvViewFrame* frame=builder->getDesktopManager()->getCurrentFrame();
	// Don't save the overview in the .ilv
	builder->getDesktopManager()->removeFrame(frame);
	if (m->getView(v)) {
	    m->removeView(v);
	}
	buffer->save(selection);
	builder->getDesktopManager()->addFrame(frame);
	frame->setTitle(selection);
    }
}

// --------------------------------------------------------------------------
static void
SaveBufferCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* buffer = builder->getCurrentBuffer();
    if (!buffer) {
	return;
    }
    // saves the manager
    if (!buffer->getFileName()) {
	SaveBufferAsCB(item, arg);
    }
    else {
	buffer->save();
    }
}

// --------------------------------------------------------------------------
static void
LoadMapFileCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    const char* selection = builder->requestForInputMapFile();
    if (selection) {
	builder->loadFile(selection);
    }
}

// --------------------------------------------------------------------------
static void
InsertMapFileCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* buffer= builder->getCurrentBuffer();
    if (!buffer) {
	return;
    }
    const char* selection = builder->requestForInputMapFile();
    if (selection) {
	IlvMapsError status = buffer->loadMap(selection,IlFalse);
	if (status != IlvMaps::NoError()) {
	    const char* msg = IlvMaps::GetErrorMessageId(status);
	    const char* message = "Cannot insert map : %s\n";
	    char* buffer = new char[strlen(message) + strlen(msg) + 1];
	    sprintf(buffer,message,msg);
	    builder->reportError(buffer);
	    delete [] buffer;
	    return;
	}
	else {
	    const char* message = "%s loaded\n";
	    char* buffer = new char[strlen(message) + strlen(selection) + 1];
	    sprintf(buffer,message,selection);
	    builder->reportInfo(buffer);
	    delete[] buffer;
	}
    }
}

#if defined(HAS_SDO_SUPPORT)
// --------------------------------------------------------------------------
static void
DisconnectCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    if (builder->_requestController) {
	builder->_requestController->hide();
    }
    builder->setDbms(0);
    builder->reportInfo("Connection closed\n");
}

// --------------------------------------------------------------------------
static void
ObjectModelCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* buffer= builder->getCurrentBuffer();
    if (!builder->getDbms()) {
	IlvMapsError error = IlvMaps::NoError();
	IldDbms* dbms =
	IlvSDOUtil::GetDbmsFactory()->makeDbms(builder->getDisplay(),
					       0, 0, 0, 0, error);
	if (error != IlvMaps::NoError() && dbms) {
	    // Report error
	    builder->setDbms(0);
	    delete dbms;
	}
	else if (dbms) {
	    if (dbms->isConnected()) {
		IlvMapsError status = IlvMaps::NoError();
		if (IlvSDOUtil::CheckSdoExistence(dbms, status)) {
		    // Methods to be added...
		    builder->reportInfo("Found SDO Package.\n");
		    builder->setDbms(dbms);
		}
		else {
		    builder->reportError(
			 "No SDO Package found. SDO feature deactivated.\n");
		    builder->setDbms(0);
		    return;
		}
	    }
	    else {
		builder->setDbms(0);
		return;
	    }
	}
    } // dbms != 0
    if (builder->getDbms()) {
	ReaderController* rc = builder->_requestController;
	rc->addRendererEditorPage(IlvMapGeometryCollection::ClassInfo());
	IlvMapInfo* info = IlvMapInfo::Get(buffer->getManager());
	if (info == 0) {
	    rc->setRequestingForDestProjection(IlTrue);
	    rc->setRequestingForDestAdapter(IlTrue);
	}
	else {
	    rc->setRequestingForDestProjection(IlFalse);
	    rc->setRequestingForDestAdapter(IlFalse);
	}
	rc->setRequestingForLOD(IlTrue);
	rc->setRequestingForLODTileSize(IlTrue);
	rc->setRequestingForAOI(IlTrue);
	rc->setRequestingForSDOLayer(builder->getDbms());
	rc->setRequestingForAttributes(IlTrue);
	builder->_requestController->show();
    }
}
#endif

// --------------------------------------------------------------------------
static void
CloseBufferCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* buffer= builder->getCurrentBuffer();
    if (buffer && buffer->getFrame()) {
	builder->destroyBuffer(buffer->getFrame());
    }
}

// --------------------------------------------------------------------------
static void
QuitApplicationCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    builder->quit();
}

// --------------------------------------------------------------------------
static void
PanCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    builder->addInteractor(MapBuilder::PanInteractor());
}

// --------------------------------------------------------------------------
static void
SelectCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    builder->addInteractor(MapBuilder::SelectInteractor());
}

// --------------------------------------------------------------------------
static void
ZoomCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* current = builder->getCurrentBuffer();
    if (current) {
	IlvManager* manager = current->getManager();
	IlvView* view = current->getView();
	IlvRect visibleRect;
	view->sizeVisible(visibleRect);
	manager->zoomView(view,
			  IlvPoint(visibleRect.centerx(),
				   visibleRect.centery()),
			  1.5, 1.5);
    }
}

// --------------------------------------------------------------------------
static void
UnZoomCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* current = builder->getCurrentBuffer();
    if (current) {
	IlvManager* manager = current->getManager();
	IlvView* view = current->getView();
	IlvRect visibleRect;
	view->sizeVisible(visibleRect);
	manager->zoomView(view,
			  IlvPoint(visibleRect.centerx(),
				   visibleRect.centery()),
			  (IlvFloat)(1./1.5),
			  (IlvFloat)(1./1.5));
    }
}

// --------------------------------------------------------------------------
static void ZoomIntCB(IlvGraphic* item, IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    builder->addInteractor(MapBuilder::ZoomIntInteractor());
}

// --------------------------------------------------------------------------
static void
ShowAllCB(IlvGraphic* item,IlvAny arg)
{
    MapBuilder* builder = (MapBuilder*)arg;
    MapBuffer* current = builder->getCurrentBuffer();
    if (current) {
	IlvManager* manager = current->getManager();
	IlvView* view = current->getView();
	manager->fitTransformerToContents(view,IlTrue);
    }
}

// --------------------------------------------------------------------------
// Creates the main window
IlvDockableMainWindow*
MapBuilder::createMainWindow(const IlvRect& rect) const
{
    IlvDockableMainWindow*
    mainWindow = new IlvDockableMainWindow(getDisplay(),
					   GetMainWindowName(),
					   getName(),
					   rect,
					   0,
					   IlFalse);
    return mainWindow;
}

// --------------------------------------------------------------------------
// Creates the Panel
void MapBuilder::makePanels()
{
    DockableApplication::makePanels();
    if (!_sdoAvailable) {
	reportInfo(
	      "DBLink package not found. Database connection deactivated\n");
    }
#if defined(HAS_SDO_SUPPORT)
    else {
	_requestController = new SdoReaderController(getDisplay(),
						     0,
						     this);
	_requestController->getContainer()->moveToView(getMainWindow());
	reportInfo("DBLink package found.\n");
    }
#endif
    IlvSystemView v = getMainWindow()->getMainWorkspaceViewPane()
				     ->getView()->getSystemView();
    _loadFileSelector =	new IlvIFileSelector(getDisplay(), ".", "*", 0, v);
    _loadFileSelector->setType(IlvFileSelectorLoad);
    _loadFileSelector->setTitle("Load a map file");
    _saveFileSelector =	new IlvIFileSelector(getDisplay(), ".", "*.ilv", 0,
					     v);
    _saveFileSelector->setTitle("Save .ilv file");
    _saveFileSelector->setType(IlvFileSelectorSave);
}

// --------------------------------------------------------------------------
// Pane visibility listener
class BuilderPaneListener
: public IlvPaneListener
{
public:
    BuilderPaneListener(IlvPopupMenu* menu)
    : _menu(menu)
    {}
    virtual void paneVisibilityChanged()
    {
	// visibility changed -> update menu item
	IlvPane* p = getPane();
	const char* name = p->getName();
	IlvSymbol* sym = IlvGetSymbol(name);
	IlUShort count;
	IlvMenuItem* const* items = _menu->getItems(count);
	for (IlUShort i = 0; i < count; i++) {
	    IlvMenuItem* item = items[i];
	    if (item->hasProperty(sym)) {
		item->setChecked(p->isVisible());
		break;
	    }
	}
    }
protected:
    IlvPopupMenu* _menu;
};

#if defined(WINDOWS)
// --------------------------------------------------------------------------
// Allow drag&drop of files on Windows
static IlvBoolean
DragDropWindowProc(IlvAbstractView*,
		   IlvSystemView,
		   IlvMsgParam msg,
		   IlvWParam wParam,
		   IlvLParam,
		   IlvAny& result,
		   IlvAny arg)
{
    if (msg == WM_DROPFILES) {
    	char filename[2048];
	DragQueryFile((HDROP)IlvCastIlvWParamToIlAny(wParam), 0,
		      filename, 256);
	MapBuilder* builder = (MapBuilder*)arg;
	builder->loadFile(filename);
	result = 0;
	return IlTrue;
    }
    return IlFalse;
} // DragDropWindowProc
#endif

// --------------------------------------------------------------------------
void
MapBuilder::createPanes()
{
    // Create the desktop manager
    desktopManager = new MapDesktopManager(getMainWindow()
					   ->getMainWorkspaceViewPane()
					   ->getView(),
					   this);
    // create and add main menu
    IlvPane* pane;
    IlvDockingPaneLocation* location;
    IlvRect rect;
    IlvPopupMenu* winMenu;
    // Main Menu Bar
    pane = createMainMenuBarPane(GetMainMenuBarName(), &winMenu);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   IlvDockableMainWindow:: // Relative to
				   GetMainWorkspaceName(), // the main work
				   // space pane
				   IlvTop);                // on top of it
    addPane(pane,location);
    pane->addListener(new BuilderPaneListener(winMenu));
    
    // Standard Tool Bar
    pane = createStandardToolBarPane(GetToolBarName());
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   GetMainMenuBarName(), // Relative to
				   // the menu bar
				   IlvBottom);           // below it
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));

    // Overview
    pane = createOverviewPane(GetOverviewName());
    rect.resize(250, 100);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   IlvDockableMainWindow::
						      GetMainWorkspaceName(),
				   IlvLeft,
				   IlvDockingPaneLocation::DockedVertically,
				   IlTrue,
				   &rect,
				   &rect,
				   &rect);
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));
    // Scale pane
    pane = createScalePane(GetScaleName());
    rect.resize(250, 40);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   GetOverviewName(),
				   IlvBottom,
				   IlvDockingPaneLocation::DockedVertically,
				   IlTrue,
				   &rect,
				   &rect,
				   &rect);
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));
    // Coord pane
    pane = createCoordPane(GetCoordName());
    rect.resize(250, 40);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   GetOverviewName(),
				   IlvBottom,
				   IlvDockingPaneLocation::DockedVertically,
				   IlTrue,
				   &rect,
				   &rect,
				   &rect);
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));
    // Legend pane
    pane = createLegendPane(GetLegendName());
    rect.resize(250, 200);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   GetOverviewName(),
				   IlvBottom,
				   IlvDockingPaneLocation::DockedVertically,
				   IlTrue,
				   &rect,
				   &rect,
				   &rect);
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));
    // Status pane
    pane = createStatusPane(GetStatusPaneName());
    rect.resize(600, 50);
    location =
	new IlvDockingPaneLocation(pane->getName(),
				   IlvDockableMainWindow::
						      GetMainWorkspaceName(),
				   IlvBottom,
				   IlvDockingPaneLocation::Docked,
				   IlTrue,
				   &rect,
				   &rect,
				   &rect);
    addPane(pane, location);
    pane->addListener(new BuilderPaneListener(winMenu));
    getMainWindow()->getMainWorkspaceViewPane()->getView()->
	    setBackground(getDisplay()->defaultBackground());
    desktopManager->addListener(new ViewUpdater(this));
#if defined(WINDOWS)
    // Add drag&drop support
    IlvView* view = getMainWindow()->getMainWorkspaceViewPane()->getView();
    HWND winh = (HWND)view->getSystemView();
    DragAcceptFiles(winh, TRUE);
    view->setWindowProc(DragDropWindowProc, (IlvAny)this);
#endif
}

// --------------------------------------------------------------------------
// Create a pane with overview
IlvPane*
MapBuilder::createOverviewPane(const char* name) 
{
   
    IlvViewPane* pane =
	new IlvViewPane(name,
			new IlvView(getMainWindow()
				    ->getMainWorkspaceViewPane()->getView(),
				    IlvRect(0, 0, 1, 1)));
    pane->setMinimumSize(IlvVertical, 80);
    pane->setResizeMode(IlvPane::Resizable);
    return pane;
}

// --------------------------------------------------------------------------
// Create a pane with scale bar
IlvPane*
MapBuilder::createScalePane(const char* name) 
{
    IlvMapScale* scale = new IlvMapScale(getDisplay(), IlvRect(0, 0,
							       250, 40));
    IlvGraphicPane* pane = new IlvGraphicPane(name, scale);
    pane->setMinimumSize(IlvVertical, 40);
    pane->setResizeMode(IlvPane::Resizable);
    return pane;   
}

// --------------------------------------------------------------------------
// Create a pane with coord viewer
IlvPane*
MapBuilder::createCoordPane(const char* name) 
{
    IlvMapCoordViewer* cv = new IlvMapCoordViewer(getDisplay(),
						  IlvRect(0, 0, 250, 40));
    cv->setDisplayMode(IlvMapDMSMode);
    cv->setVertical(IlTrue);
    IlvGraphicPane* pane = new IlvGraphicPane(name, cv);
    pane->setMinimumSize(IlvVertical, 40);
    pane->setResizeMode(IlvPane::Resizable);
    return pane;
}

// --------------------------------------------------------------------------
// Create a pane containing a legend
IlvPane*
MapBuilder::createLegendPane(const char* name)
{
    Legend* legend = new Legend(getDisplay(), IlvRect(0, 0, 1, 1));
    IlvGraphicPane* pane = new IlvGraphicPane(name, legend);
    pane->setResizeMode(IlvPane::Resizable);
    pane->setMinimumSize(IlvVertical, 120);
    return pane;
}

// --------------------------------------------------------------------------
// callback for Pane visibility menu 
static void
PanVisChange(IlvGraphic* g, IlvAny a)
{
    IlUShort count;
    IlvPopupMenu* pop = (IlvPopupMenu*)g;
    int sel = pop->whichSelected();
    IlvMenuItem* item = pop->getItems(count)[sel];
    IlvSymbol* pn = IlvGetSymbol("PaneName");
    IlvSymbol* da = IlvGetSymbol("DockApp");
    if (item->hasProperty(pn) && item->hasProperty(da)) {
	MapBuilder* b = (MapBuilder*)item->getProperty(da);
	const char* s = (const char*)item->getProperty(pn);
	IlvPane* p = b->getPane(s);
	if (p) {
	    if (item->isChecked()) {
		p->hide();
	    }
	    else {
		p->show();
	    }
	    p->getContainer()->updatePanes();
	}
    }
}

// --------------------------------------------------------------------------
// Create main menu
IlvPane*
MapBuilder::createMainMenuBarPane(const char* name,
				  IlvPopupMenu** retWinMenu)
{
    int j; // convenient counter
    // Creates the toolbar    
    const char* labelscon[] = { "File", "Connection", "View"};
    const char* labelsnocon[] = { "File", "View"};
    const char** labels;
    int labelItemNum = 1; // always have a "File" menu
    if (_sdoAvailable) {
	labelItemNum++; // include the "Connection" menu
    }
    labelItemNum++;
    if (_sdoAvailable) {
	labels = labelscon;
    }
    else {
	labels = labelsnocon;
    }
    IlvToolBar* toolbar = new IlvToolBar(getDisplay(),
					 IlvPoint(0, 0),
					 labels,
					 labelItemNum);
    toolbar->setConstraintMode(IlTrue);
    // Create the file menu
    static struct {
	const char* label;
	IlvGraphicCallback callback;
	IlBoolean   sensitive;
    } fileMenuDef[] = {
	{ "New Map buffer",  NewMapBufferCB,    IlTrue  },
	{ "Save"          ,  SaveBufferCB,      IlFalse },
	{ "Save as..."    ,  SaveBufferAsCB,    IlFalse },
	{ "Load file...",    LoadMapFileCB,     IlTrue  },
	{ "Insert map file", InsertMapFileCB,   IlFalse },
	{ "Close",           CloseBufferCB,     IlFalse },
	{ 0, 0 },
	{ "Quit",            QuitApplicationCB, IlTrue  },
    };
    IlvPopupMenu* fileMenu = new IlvPopupMenu(getDisplay());
    for (j = 0; j < 8; j++) {
	if (fileMenuDef[j].label != 0) {
	    IlvMenuItem itemInstance(fileMenuDef[j].label);
	    if (fileMenuDef[j].callback) {
		itemInstance.setClientData((void*)this);
		itemInstance.setCallback(fileMenuDef[j].callback);
	    }
	    fileMenu->addItem(itemInstance); 
	    // now work on the added item
	    IlvMenuItem* item =
		fileMenu->getItem((int)fileMenu->getCardinal()-1);
	    if (!fileMenuDef[j].sensitive) {
		item->setSensitive(IlFalse);
		desktopManager->addListener(new 
		   ViewDependentMenuItemSensitivitySelector(item,this));
	    }
	}
	else {
	    fileMenu->addItem(IlvMenuItem());
	}
    }    
    toolbar->getItem(0)->setMenu(fileMenu, IlFalse);

    // Create the connection menu
    if (_sdoAvailable) {
#if defined(HAS_SDO_SUPPORT)
	static struct {
	    const char* label;
	    IlvGraphicCallback callback;
	    IlBoolean   sensitive;
	} connMenuDef[] = {
	    { "Oracle Object Model",  ObjectModelCB,    IlFalse },
	    { 0, 0 },
	    { "Disconnect",           DisconnectCB, IlFalse },
	};
	IlvPopupMenu* connMenu = new IlvPopupMenu(getDisplay());
	for (j = 0; j < 3; j++) {
	    if (connMenuDef[j].label != 0) {
		IlvMenuItem itemInstance(connMenuDef[j].label);
		if (connMenuDef[j].callback) {
		    itemInstance.setClientData((void*)this);
		    itemInstance.setCallback(connMenuDef[j].callback);
		}
		connMenu->addItem(itemInstance); 
		// now work on the added item
		IlvMenuItem* item =
			   connMenu->getItem((int)connMenu->getCardinal()-1);
	
		if (!connMenuDef[j].sensitive) {
		    item->setSensitive(IlFalse);
		    desktopManager->addListener(new 
		       	ViewDependentMenuItemSensitivitySelector(item,this));
		}
	
	    }
	    else {
		connMenu->addItem(IlvMenuItem());
	    }
	}    
	toolbar->getItem(1)->setMenu(connMenu, IlFalse);
#endif
    } // cas of connection menu to be added

    // Pane visibility menu

    IlvPopupMenu* winMenu = new IlvPopupMenu(getDisplay());
    
    const char* windowsLabel[] 	= {
	GetToolBarName(),
	GetOverviewName(),
	GetScaleName(),
	GetCoordName(),
	GetLegendName(),
	GetStatusPaneName(),
	0
    };
    const char* s;

    IlvSymbol* pn = IlvGetSymbol("PaneName");
    IlvSymbol* da = IlvGetSymbol("DockApp");
	
    for (j = 0; (s = windowsLabel[j]); j++) {
	IlvMenuItem* item  = new IlvMenuItem(s);
	item->setChecked(IlTrue);
	item->addProperty(da, (IlvAny)this);
	item->addProperty(pn, (IlvAny)s);
	item->addProperty(IlvGetSymbol(s), 0);
	item->setCallback(PanVisChange);
	winMenu->insertItem(item);
    }
    *retWinMenu = winMenu;
    toolbar->getItem(labelItemNum - 1)->setMenu(winMenu, IlFalse);
    
    return new MyMainMenuBarPane(name, toolbar);
}

// --------------------------------------------------------------------------
// Create a tool bar
IlvPane*
MapBuilder::createStandardToolBarPane(const char* name)
{
    IlvToolBar* toolbar = new IlvToolBar(getDisplay(), IlvPoint(0, 0));
    static struct {
	const char* bitmap;
	IlvGraphicCallback callback;
	IlBoolean   sensitive;
	const char* tooltip;
	IlBoolean   isToggle;
    } toolbarDef[] = {
	{ "data/maps/new.png",    NewMapBufferCB, IlTrue,
	  "New map", IlFalse },
	{ "data/maps/open.png",   LoadMapFileCB, IlTrue,
	  "Load file", IlFalse },
	{ "data/maps/save.png",   SaveBufferCB, IlFalse,
	  "Save current map", IlFalse},
	{ 0, 0 },
	{ "data/maps/move.png",   PanCB, IlFalse,
	  "Pan current map",IlTrue },
	{ "data/maps/select.png", SelectCB, IlFalse,
	  "Selection", IlTrue },
	{ "data/maps/zoom.png",   ZoomCB, IlFalse,
	  "Zoom in", IlFalse },
	{ "data/maps/unzoom.png", UnZoomCB, IlFalse,
	  "Zoom out", IlFalse } ,
	{ "data/maps/zoomin.png", ZoomIntCB, IlFalse,
	  "Zoom window", IlTrue },
	{ "data/maps/fit.png",    ShowAllCB, IlFalse,
	  "Show all", IlFalse }
    };
    IlvBitmap* bitmap;
    for (IlUInt i = 0; i < 10; i++) {
	if (toolbarDef[i].bitmap == 0) {
	    toolbar->insertItem(new IlvMenuItem());
	}
	else {
	    bitmap = getBitmap(toolbarDef[i].bitmap);
	    if (!bitmap) {
		bitmap = getDisplay()->getDefaultBitmap();
	    }
	    IlvMenuItem itemInstance(bitmap);
	    toolbar->addItem(itemInstance);
	    // now work on the copied item
	    IlvMenuItem* item = toolbar->getItem((IlvUShort)i);
	    item->setClientData((void*)this);
	    if (toolbarDef[i].callback) {
		item->setCallback(toolbarDef[i].callback);
	    }
	    if (!toolbarDef[i].sensitive) {
		item->setSensitive(IlFalse);
		desktopManager->addListener(new 
		ViewDependentMenuItemSensitivitySelector(item,this));
	    }
	    if (toolbarDef[i].tooltip) {
		item->setToolTip(toolbarDef[i].tooltip);
	    }
	}
    }
    toolbar->useToolTips(IlTrue);
    return new IlvAbstractBarPane(name, toolbar);
}

// --------------------------------------------------------------------------
// Create a status pane
IlvPane*
MapBuilder::createStatusPane(const char* name)
{
    _statusText = new IlvText(getDisplay(),IlvPoint(0,0));
    _statusText->setEditable(IlFalse);
    IlvGraphicPane* pane = new IlvGraphicPane(name, _statusText);
    pane->setResizeMode(IlvPane::Resizable);
    return pane;
}

// --------------------------------------------------------------------------
void
MapBuilder::addInteractor(int interactor)
{
    MapBuffer* buffer = 0;
    if (interactor == _currentInteractor) {
	return;
    }
    for (IlUInt i = 0 ; i < bufferList.length(); i++) {
	buffer = bufferList.getValue(i);
	// remove interactor
	IlvManagerViewInteractor* inter =
		      buffer->getManager()->getInteractor(buffer->getView());
	if (inter) {
	    inter->abort();
	    buffer->getManager()->removeInteractor(buffer->getView());
	    delete inter;
	}
	if (interactor == PanInteractor()) {
	    IlvPanZoomInteractor* pan =
			       new IlvPanZoomInteractor(buffer->getManager(),
							buffer->getView());
	    pan->setZoomingRatio((IlvFloat)1.5);
	    pan->setDrawingBitmap(IlTrue);
	    pan->setOpaqueMove(IlFalse);
	    buffer->getManager()->setInteractor(pan, buffer->getView());
	}
	else if (interactor == SelectInteractor()) {
	    NonEditableSelectInteractor* select =
			new NonEditableSelectInteractor(buffer->getManager(),
							buffer->getView());
	    buffer->getManager()->setInteractor(select,buffer->getView());
	}
	else if (interactor == ZoomIntInteractor()) {
	    IlvZoomInteractor* zoom =
				  new IlvZoomInteractor(buffer->getManager(),
							buffer->getView());
	    zoom->setImmediateMode(IlTrue);
	    buffer->getManager()->setInteractor(zoom,buffer->getView());
	}
    }
    _currentInteractor = interactor;
}
			 
// --------------------------------------------------------------------------
const char*
MapBuilder::requestForInputMapFile()
{
    // _loadFileSelector->setPatterns(IlvMapFiltersCount, IlvMapFilters,
    //                                IlvMapFiltersMessage);
    _loadFileSelector->moveToView(getMainWindow());
    const char* selection = _loadFileSelector->get();
    // _loadFileSelector->setPatterns(IlvFileFiltersCount, IlvFileFilters,
    //                                IlvFileFiltersMessage);
    return selection;
}

// --------------------------------------------------------------------------
void
MapBuilder::updateBufferDependentUI()
{
    Legend* legend =
	(Legend*)((IlvGraphicPane*)
		  getPane(MapBuilder::GetLegendName()))->getObject();
    IlvMapScale* scale =
	(IlvMapScale*)((IlvGraphicPane*)getPane(MapBuilder::GetScaleName()))
						->getObject();
    IlvMapCoordViewer* coords = (IlvMapCoordViewer*)((IlvGraphicPane*)
				getPane(MapBuilder::GetCoordName()))
						->getObject();
    if (getCurrentBuffer()) {
	if (legend) {
	    legend->setTargetView(getCurrentBuffer()->getView());
	    legend->reDraw();
	}
	if (scale) {
	    scale->setView(getCurrentBuffer()->getView());
	    scale->reDraw();
	}
	if (coords) {
	    coords->setView(getCurrentBuffer()->getView());
	    coords->reDraw();
	}
    }
    else {
	if (legend) {
	    legend->setTargetView(0);
	}
	if (scale) {
	    scale->setView(0);
	}
	if (coords) {
	    coords->setView(0);
	}
    }
#if defined(HAS_SDO_SUPPORT)
    if (_requestController) {
	_requestController->updateController();
    }
#endif
}

// --------------------------------------------------------------------------
void
MapBuilder::loadFile(const char* selection)
{
    size_t l = strlen (selection);
    if ((l > 4) && !IL_STRCASECMP(selection + l - 4, ".ilv")) {
	MapBuffer* buffer = makeNewBuffer(IlTrue, IlFalse);
	buffer->loadFile(selection);
	Legend* legend =
	    (Legend*)((IlvGraphicPane*)getPane(MapBuilder::GetLegendName()))
						->getObject();
	legend->createAllLegend();
	buffer->getManager()->reDraw();
	getDesktopManager()->getCurrentFrame()->setTitle(selection);
    }
    else {
	MapBuffer* buffer= makeNewBuffer(IlFalse, IlTrue);
	IlvMapsError status = buffer->loadMap(selection, IlTrue);
	if (status != IlvMaps::NoError()) {
	    destroyBuffer(buffer->getFrame());
	    const char* msg = IlvMaps::GetErrorMessageId(status);
	    const char* message = "Cannot load map : %s\n";
	    char* buffer = new char[strlen(message) + strlen(msg) + 1];
	    sprintf(buffer, message, msg);
	    reportError(buffer);
	    delete [] buffer;
	    return;
	}
	else {
	    const char* message = "%s loaded\n";
	    char* buffer = new char[strlen(message) + strlen(selection) + 1];
	    sprintf(buffer, message, selection);
	    reportInfo(buffer);
	    delete [] buffer;
	}	
    }
}
