// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/layers.cpp
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
// Definition of the Layers class
// --------------------------------------------------------------------------

#include <vpf/gui/layers.h>
#include <vpf/gui/layer.h>
#include <vpf/gui/manager.h>
#include <vpf/gui/application.h>
#include <vpf/gui/serialize.h>
#include <vpf/gui/arearesourcedialog.h>
#include <vpf/gui/lineresourcedialog.h>
#include <vpf/gui/pointresourcedialog.h>
#include <vpf/gui/textresourcedialog.h>
#include <vpf/gui/extentdialog.h>
#include <vpf/gui/palette.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/sheet.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/gadgets/filesel.h>

#include <vpf/basictypes.h>
#include <vpf/featureclass.h>
#include <vpf/feature.h>
#include <vpf/featureitem.h>
#include <vpf/featuretype.h>
#include <vpf/area.h>
#include <vpf/segment.h>
#include <vpf/point.h>
#include <vpf/text.h>
#include <vpf/coverage.h>
#include <vpf/library.h>
#include <vpf/database.h>
#include <vpf/error.h>

#if defined(ILVSTD)
# include <fstream>
# include <cstdio>
ILVSTDUSE
#else
# include <fstream.h>
# include <stdio.h>
#endif

const IlUShort Layers::_NameColumn= 0;
const IlUShort Layers::_VisibleColumn = 1;
const IlUShort Layers::_PaletteColumn = 2;
const IlUShort Layers::_CoverageColumn = 3;
const IlUShort Layers::_FeatureColumn = 4;
const IlUShort Layers::_FilterColumn = 5;
const IlUShort Layers::_NColumns = 6;

// --------------------------------------------------------------------------
static void
ExtentCB(IlvGraphic*, IlvAny arg)
{
    Layers* layers = (Layers*) arg;
    if (layers)
	layers->extent();
}

// --------------------------------------------------------------------------
static void
ListCB(IlvGraphic* g, IlvAny arg)
{
    IlvSheet* sheet = (IlvSheet*) g;
    IlUShort c, r;
    Layers* gl = (Layers*) arg;

    if (!sheet->getFirstSelected(c, r) || !r) {
	gl->update();
	return;
    }

    gl->update(r - 1);

    if (c == Layers::_FilterColumn)
	return;

    switch (c) {
    case Layers::_PaletteColumn:
	gl->editPalette(r - 1);
	break;
    default:
	;
    }
}

// --------------------------------------------------------------------------
static void
LoadCB(IlvGraphic*, IlvAny arg)
{
    Layers* layers = (Layers*) arg;
    if (layers)
	layers->load();
    Application::GetApplication()->handleError();
}

// --------------------------------------------------------------------------
static void
PopCB(IlvGraphic* g, IlvAny arg)
{
    Layers* gl = (Layers*)arg;
    gl->pop();
}

// --------------------------------------------------------------------------
static void
PushCB(IlvGraphic* g, IlvAny arg)
{
    Layers* gl = (Layers*) arg;
    gl->push();
}

// --------------------------------------------------------------------------
static void
RefreshCB(IlvGraphic*, IlvAny arg)
{
    Layers* layers = (Layers*)arg;
    if (layers)
	layers->refresh();
}

// --------------------------------------------------------------------------
static void
RemoveCB(IlvGraphic* g, IlvAny arg)
{
    Layers* gl = (Layers*) arg;
    gl->remove();
}

// --------------------------------------------------------------------------
static void
SaveCB(IlvGraphic*, IlvAny arg)
{
    Layers* layers = (Layers*) arg;
    if (layers)
	layers->save();
    Application::GetApplication()->handleError();
}

// --------------------------------------------------------------------------
static void
VisibleItemCB(IlvGraphic* g, IlvAny arg)
{
    IlvToggle* toggle = (IlvToggle*) g;
    Layers* layers = (Layers*) arg;

    if (g && layers)
	layers->visible((Layer*)toggle->getClientData(), toggle->getState());
}

// --------------------------------------------------------------------------
Layers::Layers(IlvGadgetContainer* container, Manager* manager)
: _display(container->getDisplay()),
  _manager(manager),
  _container(container),
  _nLayers(0),
  _list((IlvSheet*)container->getObject("list")),
  _pop((IlvButton*)container->getObject("pop")),
  _push((IlvButton*)container->getObject("push")),
  _remove((IlvButton*)container->getObject("delete")),
  _refresh((IlvButton*)container->getObject("refresh")),
  _save((IlvButton*)container->getObject("save")),
  _extent((IlvButton*)container->getObject("extent")),
  _open((IlvButton*)container->getObject("open"))
#if 0
    , _selector(new IlvIFileSelector(container->getDisplay(), ".", "*.vls"))
#endif
{
    if (_refresh) {
	_refresh->setCallback(RefreshCB, this);
	_refresh->setSensitive(IlFalse);
    }
    if (_extent)
	_extent->setCallback(ExtentCB, this);
    if (_pop) {
	_pop->setCallback(PopCB, this);
	_pop->setSensitive(IlFalse);
    }
    if (_push) {
	_push->setCallback(PushCB, this);
	_push->setSensitive(IlFalse);
    }
    if (_remove) {
	_remove->setCallback(RemoveCB, this);
	_remove->setSensitive(IlFalse);
    }
    if (_save) {
	_save->setCallback(SaveCB, this);
	_save->setSensitive(IlFalse);
    }
    if (_open) {
	_open->setCallback(LoadCB, this);
	_open->setSensitive(IlTrue); // Temporary until loading works well
    }
    if (_list) {
	_list->setExclusive(IlTrue);
	_list->setBrowseMode(IlFalse);
	_list->allowEdit(IlTrue);
	_list->setDirectEditionMode(IlTrue);
	_list->autoFitToSize(IlTrue);
	_list->adjustLast(IlTrue);
	_list->showGrid(IlFalse);
	_list->setCallback(ListCB, this);
    }
} 

// --------------------------------------------------------------------------
Layers::~Layers()
{
}

// --------------------------------------------------------------------------
void
Layers::doUpdate()
{
    IlUShort c, r;
    if (_list->getFirstSelected(c, r))
	if (r)
	    update(r - 1);
	else
	    update();
    else
	update();
}

// --------------------------------------------------------------------------
void
Layers::update()
{
    _push->setSensitive(IlFalse);
    _pop->setSensitive(IlFalse);
    _remove->setSensitive(IlFalse);
    _save->setSensitive(IlFalse);
    _refresh->setSensitive(_nLayers > 0);

    _push->reDraw();
    _pop->reDraw();
    _remove->reDraw();
    _save->reDraw();
    _refresh->reDraw();
}

// --------------------------------------------------------------------------
void
Layers::update(VpfUInt layer)
{
  _push->setSensitive(layer < _nLayers - 1);
  _pop->setSensitive(layer > 0);
  _remove->setSensitive(IlTrue);
  _save->setSensitive(IlTrue);
  _refresh->setSensitive(IlTrue);

  _push->reDraw();
  _pop->reDraw();
  _remove->reDraw();
  _save->reDraw();
  _refresh->reDraw();
}

// --------------------------------------------------------------------------
void
Layers::show()
{
    _container->show();
}

// --------------------------------------------------------------------------
void
Layers::hide()
{
    _container->hide();
}

// --------------------------------------------------------------------------
const Layer*
Layers::getLayer(VpfUInt i) const
{
    return (Layer*)_list->getItemData(_NameColumn, i+1);
}

// --------------------------------------------------------------------------
Layer*
Layers::getLayer(VpfUInt i)
{
    return (Layer*)_list->getItemData(_NameColumn, i+1);
}

// --------------------------------------------------------------------------
void
Layers::setLayer(VpfUInt i, Layer* layer)
{
    _list->setItemData(_NameColumn, i+1, layer);
}

// --------------------------------------------------------------------------
Layer*
Layers::addLayer(VpfFeatureClass* fc)
{
    _list->insertRow(1);
    _nLayers++;
    
    // if (_nLayers > 1)
    IlUInt	newLayerIndex = 0;
    _manager->addLayer(newLayerIndex);
    
    Layer*	layer = new Layer("noname", 1, fc, new Palette(_display),
				  _manager->getManagerLayer(newLayerIndex),
				  "*");
    _setLine(1, layer); 
    _list->reDraw();

    doUpdate();
    return layer;
}

// --------------------------------------------------------------------------
void
Layers::pop()
{
    IlUShort c, r;
    if (!_list->getFirstSelected(c, r))
	return;
    if (r == 0)
	return;
    pop(r - 1);
}

// --------------------------------------------------------------------------
void
Layers::pop(VpfUInt i)
{
    if ((i == 0) || ( i >= _nLayers))
	return;

    Layer* a = getLayer(i);
    Layer* b = getLayer(i - 1);

    _setLine(i + 1, b);
    _setLine(i, a);

    _manager->swapLayers(_manager->getLayerIndex(a->getManagerLayer()),
			 _manager->getLayerIndex(b->getManagerLayer()));

    _list->deSelect();
    _list->setItemSelected(0, i);
    _list->reDraw();
    update(i - 1);
}

// --------------------------------------------------------------------------
void
Layers::push()
{
    IlUShort c, r;
    if (!_list->getFirstSelected(c, r))
	return;
    if (r == 0)
	return;
    push(r - 1);
}

// --------------------------------------------------------------------------
void
Layers::push(VpfUInt i)
{
    if (i >= _nLayers - 1)
	return;

    Layer* a = getLayer(i);
    Layer* b = getLayer(i + 1);

    _setLine(i + 1, b);
    _setLine(i + 2, a);

    _manager->swapLayers(_manager->getLayerIndex(a->getManagerLayer()),
			 _manager->getLayerIndex(b->getManagerLayer()));

    _list->deSelect();
    _list->setItemSelected(0, i + 2);
    _list->reDraw();

    update(i + 1);
}

// --------------------------------------------------------------------------
void
Layers::remove()
{
    IlUShort c, r;
    if (!_list->getFirstSelected(c, r))
	return;
    if (r == 0)
	return;
    remove(r - 1);
}

// --------------------------------------------------------------------------
void
Layers::remove(VpfUInt i)
{
    if (i >= _nLayers) 
	return;

    Layer* a = getLayer(i);
    _list->removeRow(i + 1);
    delete a;

    _nLayers--;

    _manager->removeLayer(_manager->getLayerIndex(a->getManagerLayer()));
    _list->deSelect();
    _list->reDraw();
    update();
}

void
Layers::remove(Layer* layer)
{
    for(VpfUInt i = _nLayers; i; i--) {
	Layer*	l = getLayer(i);
	
	if(l == layer) {
	    _list->removeRow(i+1);
	    _manager->removeLayer(_manager->getLayerIndex(layer->getManagerLayer()));
	    _list->deSelect();
	    _list->reDraw();
	    update();
	    break;
	}
    }
}

// --------------------------------------------------------------------------
void
Layers::removeAll()
{
    Layer* a = 0;
    
    while (_nLayers) {
	a = getLayer(_nLayers);
	_list->removeRow(_nLayers + 1);
	_manager->removeLayer(_manager->getLayerIndex(a->getManagerLayer()));
	delete a;
	_nLayers--;
    }

    _manager->deleteAll(IlTrue, IlTrue);

    _list->deSelect();
    _list->reDraw();
    update();
}

// --------------------------------------------------------------------------
void
Layers::_setLine(IlUShort l, Layer* layer)
{
    VpfFeatureClass* fc = layer->getFeatureClass();
    VpfCoverage* coverage = fc? fc->getCoverage() : 0;
    VpfLibrary* library = coverage? coverage->getLibrary() : 0;
    VpfDatabase* database = library ? library->getDatabase() : 0;

    _list->set(_NameColumn, l, new IlvLabelMatrixItem(layer->getName()));

    IlvToggle* gadget = new IlvToggle(_display, IlvPoint(0, 0), "");
    gadget->setRadio(IlFalse);
    gadget->setState(layer->isVisible() ? IlTrue : IlFalse);
    gadget->setClientData(layer);
    gadget->setCallback(VisibleItemCB, this);

    IlvGraphic* pg = 0;
    Palette* palette = layer->getPalette();

    if(fc) {
	const VpfFeatureType* type = fc->getType();
	
	if (type == VpfFeatureType::Point)
	    pg = new IlvMarker(_display, IlvPoint(0, 0),
			       palette->getMarkerType(),
			       palette->getMarkerSize(),
			       palette->getPalette());
	else if (type == VpfFeatureType::Line)
	    pg = new IlvLine(_display, IlvPoint(0, 0), IlvPoint(32, 32),
			     palette->getPalette());
	else if (type == VpfFeatureType::Area)
	    pg = new IlvFilledRectangle(_display, IlvRect(0, 0, 32, 32),
					palette->getPalette());
	else if (type == VpfFeatureType::Text)
	    pg = new IlvLabel(_display, IlvPoint(0, 0), "Aa",
			      palette->getPalette());
	else pg = new IlvLabel(_display, IlvPoint(0, 0), "?");
    }
    else
	pg = new IlvLabel(_display, IlvPoint(0,0), "?");
 
    _list->set(_VisibleColumn, l, new IlvGadgetMatrixItem(gadget));
    _list->set(_PaletteColumn, l, new IlvGraphicMatrixItem(pg));

    if(database && library) {
	char* coverageFullName = new char[strlen(database->getName()) +
					 strlen(library->getName()) +
					 strlen(coverage->getName()) + 3];
	strcpy(coverageFullName, database->getName());
	strcat(coverageFullName, "/");
	strcat(coverageFullName, library->getName());
	strcat(coverageFullName, "/");
	strcat(coverageFullName, coverage->getName());
	_list->set(_CoverageColumn, l,
		   new IlvLabelMatrixItem(coverageFullName));
	delete [] coverageFullName;
    }
    else
	_list->set(_CoverageColumn, l, new IlvLabelMatrixItem("<layer>"));

    if(fc)
	_list->set(_FeatureColumn, l, new IlvLabelMatrixItem(fc->getName()));
    else
	_list->set(_FeatureColumn, l, new IlvLabelMatrixItem(""));
		   
    _list->set(_FilterColumn, l, new IlvLabelMatrixItem(layer->getFilter()));

    IlUShort i = 0;
    for (i = 0; i < _NColumns; i++) {
	_list->setItemAlignment(i, l, IlvLeft);
	_list->setItemFillingBackground(i, l, IlFalse);
    }

    for (i = _VisibleColumn; i < _FilterColumn; i++)
	_list->setItemReadOnly(i, l, IlTrue);

    setLayer(l - 1, layer);

    _list->setItemCallback(_NameColumn, l, NameItemCB, layer);
    _list->setItemCallback(_FilterColumn, l, FilterItemCB, layer);
}

// --------------------------------------------------------------------------
void
Layers::visible(Layer* layer, IlBoolean state)
{
    if (!layer)
	return;

    int found = 0;

    for (VpfUInt i = 0; i < _nLayers; i++) {
	if (getLayer(i) == layer) {
	    layer->setVisible(state);
	    VpfUInt index = _manager->getLayerIndex(layer->getManagerLayer());
	    _manager->setVisible(index, state);
	    _manager->reDraw();
	    break;
	}
    }
}

// --------------------------------------------------------------------------
void
Layers::NameItemCB(IlvMatrix* m, IlUShort c, IlUShort r, IlvAny arg)
{
    Layer* layer = (Layer*) arg;
    const char* name = m->getItem(c, r)->getLabel();
    layer->setName(name);
}

// --------------------------------------------------------------------------
void
Layers::FilterItemCB(IlvMatrix* m, IlUShort c, IlUShort r, IlvAny arg)
{
    Layer* layer = (Layer*) arg;
    const char* filter = m->getItem(c, r)->getLabel();
    layer->setFilter(filter);
}

// --------------------------------------------------------------------------
void
Layers::editPalette(IlUShort l)
{
    ResourceDialog* d = 0;
    const Layer* layer = getLayer(l);
    VpfFeatureClass* fc = layer->getFeatureClass();
    
    if(! fc)
	return;
    
    Palette* palette = layer->getPalette();
    const VpfFeatureType* type = fc->getType();

    if (type == VpfFeatureType::Area) {
	d = new AreaResourceDialog(_display, layer->getName(), palette);
    } else
    if (type == VpfFeatureType::Line) {
	d = new LineResourceDialog(_display, layer->getName(), palette);
    } else
    if (type == VpfFeatureType::Point) {
	d = new PointResourceDialog(_display, layer->getName(), palette);
    } else
    if (type == VpfFeatureType::Text) {
	d = new TextResourceDialog(_display, layer->getName(), palette);
    }

    if (d) {
	d->moveToMouse();
	d->wait(IlFalse, 0);
	IlvGraphic* g =
	    ((IlvGraphicMatrixItem*)_list->getItem(_PaletteColumn, l+1))->
	         getGraphic();
	g->setPalette(palette->getPalette());
	if (type == VpfFeatureType::Point) {
	    ((IlvMarker*)g)->setType(palette->getMarkerType());
	    ((IlvMarker*)g)->setSize(palette->getMarkerSize());
	}
	_list->reDraw();
    }
}

// --------------------------------------------------------------------------
void
Layers::refresh()
{
    VpfFeatureClass* _item = 0;
    VpfFeature* f = 0;
    const char* filterText = 0;
    Palette* palette = 0;
    const VpfFeatureType* type = 0;
    char buffer[200];
    int result = 0;
    VpfError* error = 0;
    static const char* Class = "Layers::refresh";

    Application::GetApplication()->setBusy(IlTrue);
    _manager->startUpdate();

    for (IlUShort i = 0; i < _nLayers; i++) {
	Layer* layer = getLayer(i);
	
	if (!layer || !layer->isDirty())
	    continue;

	_item = layer->getFeatureClass();
	if(! _item)
	    continue;

	const VpfUInt	layerIndex =  _manager->getLayerIndex(layer->getManagerLayer());
		    
	_manager->deleteAll(layerIndex, IlTrue, IlTrue);

	filterText = layer->getFilter();
	type = _item->getType();

	palette = layer->getPalette();

	if (type == VpfFeatureType::Point)
	    f = new VpfPointFeature(_item, _manager->getExtent());
	else
	if (type == VpfFeatureType::Line)
	    f = new VpfLineFeature(_item, _manager->getExtent(),
				   VpfFeature::Intersects);
	else
	if (type == VpfFeatureType::Area)
	    f = new VpfAreaFeature(_item, _manager->getExtent(),
				   VpfFeature::Intersects);      
	else
	if (type == VpfFeatureType::Text)
	    f = new VpfTextFeature(_item, _manager->getExtent());

	if (f) {
	    result = f->select((!filterText || !filterText[0])
			       ? "*"
			       : filterText);

	    if (!result) {
		VpfFeatureItem* item = 0;
		VpfUInt n = 0;
		VpfUInt count = f->getNSelected();
		item = f->getNextObject();
		while (item) {
		    _display->readAndDispatchEvents();
		    sprintf(buffer,
			    "Reading %slayer #%d %s (%d/%d)",
			    layer->getName() ? "" : "unnamed",
			    i,
			    layer->getName() ? layer->getName() : "",
			    n + 1,
			    count);
		    Application::GetApplication()->setStatus(buffer);

		    if (type == VpfFeatureType::Point)
			_manager->add((VpfPoint*)item, palette,layerIndex);
		    else
		    if (type == VpfFeatureType::Line)
			_manager->add((VpfSegment*)item, palette,layerIndex);
		    else
		    if (type == VpfFeatureType::Area)
			_manager->add((VpfArea*)item, palette,layerIndex);
		    else
		    if (type == VpfFeatureType::Text)
			_manager->add((VpfText*)item, palette,layerIndex);
		    delete item;
		    n++;
		    item = f->getNextObject();
		} // while item
	    } // if !result
	    
	    delete f;

	    if (result) {
		error = new VpfError(Class);
		if (error) {
		    error->getStream() << "Query for layer #" << i << " ";
		    if (layer->getName())
			error->getStream() << layer->getName() << " ";
		    error->getStream() << "failed.";
		    VpfErrorReporter::Add(error);
		}
		break;
	    } else
		layer->setDirty(0);
	    
	} // if f
    } // for i

    _manager->endUpdate();
    Application::GetApplication()->setBusy(IlFalse);
    Application::GetApplication()->setStatus();
    Application::GetApplication()->handleError();
}


// --------------------------------------------------------------------------
void
Layers::save() const
{
#if 0
    const char* name = 0;

    if (!_selector)
	return;

    _selector->setTitle("Save VPF layer set");
    _selector->moveToMouse();
    name = _selector->get();
    if (!name || !name[0])
  	return;

#ifdef WIN32
    ofstream s(name, ios::binary);
#else
    ofstream s(name);
#endif
    Serialize gs(s);
    gs << "Layers" << _nLayers;
    for (IlUShort i = 0; i < _nLayers; i++) {
	const Layer* layer = getLayer(i);
	if (!layer)
	    continue;
	layer->write(gs);
    }
    s.close();
#endif

    _manager->saveVpf();
}

// --------------------------------------------------------------------------
void
Layers::load()
{
#if 1
    _manager->loadVpf(this);
#else
    static const char* Class = "Layers::load";
    VpfError* error = 0;
    const char* name = 0;

    if (!_selector)
	return;

    _selector->setTitle("Load VPF layer set");
    _selector->moveToMouse();
    name = _selector->get();
    if (!name || !name[0])
  	return;

#ifdef WIN32
    ifstream s(name, ios::binary);
#else
    ifstream s(name);
#endif
    Unserialize gs(s);

    char* gl;
    gs >> gl;
    if (strcmp(gl, "Layers")) {
	error = new VpfError(Class);
	if (error) {
	    error->getStream() << "The file " << name << " is not a "
			       << "VPF layer set.";
	    VpfErrorReporter::Add(error);
	}
	return;
    }
  
    removeAll();

    gs >> _nLayers;
    _list->insertRow(1, _nLayers);

    for (IlUShort i = 0; i < _nLayers;) {
	Layer* layer = new Layer(_display, gs);
	VpfFeatureClass* fc = (layer || layer->isBad())
	    ? layer->getFeatureClass()
	    : 0;

	if (fc)
	    _setLine(++i, layer);
	else {
	    error = new VpfError(Class);
	    if (error) {
		error->getStream() << "Skipped layer #" << i;
		if (layer && layer->getName())
		    error->getStream() << " " << layer->getName();
		error->getStream() << ".";
		VpfErrorReporter::Add(error);
	    }
	    if (layer)
		delete layer;
	    _nLayers--;
	}
    }

    if (_nLayers > (unsigned int) _manager->getNumLayers())
	for (int i = _nLayers; i < _manager->getNumLayers(); i++)
	    _manager->removeLayer();
    else
	_manager->setNumLayers(_nLayers);

    s.close();
    _list->reDraw();
    update();
#endif
}

// --------------------------------------------------------------------------
void
Layers::extent()
{
    ExtentDialog* d = new ExtentDialog(_display, _manager->getExtent());
    d->moveToMouse();
    d->wait(IlFalse, 0);
    _manager->setExtent(d->getExtent());

    for (IlUShort i = 0; i < _nLayers; i++) {
	Layer* layer = getLayer(i);
	if (!layer)
	    continue;
	layer->setDirty(1);
    }
}

// --------------------------------------------------------------------------
void
Layers::setBusy(IlBoolean busy) 
{
    if (busy) {
	_list->setSensitive(IlFalse);
	_list->reDraw();
	_extent->setSensitive(IlFalse);
	_extent->reDraw();
	_open->setSensitive(IlFalse);
	_open->reDraw();
	_push->setSensitive(IlFalse);
	_push->reDraw();
	_pop->setSensitive(IlFalse);
	_pop->reDraw();
	_remove->setSensitive(IlFalse);
	_remove->reDraw();
	_save->setSensitive(IlFalse);
	_save->reDraw();
	_refresh->setSensitive(IlFalse);
	_refresh->reDraw();
    } else {
	_list->setSensitive(IlTrue);
	_list->reDraw();
	_extent->setSensitive(IlTrue);
	_extent->reDraw();

	// Temporary, layers loading does not work very well yet
	_open->setSensitive(IlTrue);
	_open->reDraw();
	doUpdate();
    }
}


