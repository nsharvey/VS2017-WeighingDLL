// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/layers.h
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
// Declaration of the Layers class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_LAYERS_H
#define VPF_GUI_LAYERS_H

#include <ilviews/gadgets/gadcont.h>
#include <vpf/basictypes.h>

class VpfFeatureClass;
class Manager;
class Palette;
class Layer;
class IlvMatrix;
class IlvSheet;
class IlvButton;
class IlvIFileSelector;

// --------------------------------------------------------------------------
class Layers
{
public:
    Layers(IlvGadgetContainer*, Manager*);
    virtual ~Layers();
    // ____________________________________________________________
    void show();
    void hide();

    void editPalette(IlUShort l);
    Layer* addLayer(VpfFeatureClass*);

    void refresh();
    void save() const;
    void load();
    void extent();

    void push();
    void pop();
    void remove();

    void push(VpfUInt);
    void pop(VpfUInt);
    void remove(VpfUInt);
    void remove(Layer*);
    void removeAll();

    void doUpdate();
    void update();
    void update(VpfUInt);

    VpfUInt getNLayers() const { return _nLayers; }
    const Layer* getLayer(VpfUInt l) const;
    Layer* getLayer(VpfUInt l);
    void setLayer(VpfUInt i, Layer* layer);
    void setBusy(IlBoolean);

    static const IlUShort _NameColumn;
    static const IlUShort _VisibleColumn;
    static const IlUShort _PaletteColumn;
    static const IlUShort _CoverageColumn;
    static const IlUShort _FeatureColumn;
    static const IlUShort _FilterColumn;
    static const IlUShort _NColumns;
    void visible(Layer*, IlBoolean);
protected:
    void editProjection();
    void _setLine(IlUShort l, Layer* layer);

    IlvDisplay*		_display;
    Manager*		_manager;
    IlvGadgetContainer*	_container;
    VpfUInt		_nLayers;
    IlvSheet*		_list;
    IlvButton*		_pop;
    IlvButton*		_push;
    IlvButton*		_remove;
    IlvButton*		_refresh;
    IlvButton*		_save;
    IlvButton*		_extent;
    IlvButton*		_open;
#if 0
    IlvIFileSelector*	_selector;
#endif

    static void NameItemCB(IlvMatrix*, IlUShort, IlUShort, IlvAny);
    static void FilterItemCB(IlvMatrix*, IlUShort, IlUShort, IlvAny);
    static void destroyCB(IlvView*, IlvAny);
};

#endif /* VPF_GUI_LAYERS_H */
