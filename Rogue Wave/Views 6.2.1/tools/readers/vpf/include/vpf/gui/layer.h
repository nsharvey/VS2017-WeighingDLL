// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/layer.h
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
// Declaration of the Layer class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_LAYER_H
#define VPF_GUI_LAYER_H

class VpfFeatureClass;
class Palette;
class Serialize;
class Unserialize;
class IlvManagerLayer;

#include <ilviews/base/view.h>
#include <vpf/string.h>

// --------------------------------------------------------------------------
class Layer
{
public:
    Layer(const char*		name,
	  int			visible,
	  VpfFeatureClass*	fc,
	  Palette*		palette,
	  IlvManagerLayer*	managerLayer,
	  const char*		filter = "*");
#if 0
    Layer(IlvDisplay*, Unserialize&);
#endif
    ~Layer();
    // ____________________________________________________________
    int isBad() const { return (_featureClass == 0); }
    void setBad() { _featureClass = 0; }

    const char* getName() const { return _name; }
    void setName(const char* name)
	{ if (_name) delete [] _name; _name = VpfStrDup(name); }

    int isVisible() const { return _visible; }
    void setVisible(int v) { _visible = v; }

    VpfFeatureClass* getFeatureClass() const { return _featureClass; }
    Palette* getPalette() const { return _palette; }

    const char* getFilter() const { return _filter; }
    void setFilter(const char* filter)
	{
	    _dirty = 1;
	    if (_filter)
		delete [] _filter;
	    _filter = VpfStrDup(filter);
	}

    int isDirty() const { return _dirty; }
    void setDirty(int dirty) { _dirty = dirty; }

#if 0
    void write(Serialize&) const;
#endif
    IlvManagerLayer*	getManagerLayer() const { return _managerLayer; }
protected:
    char*		_name;
    int			_visible;
    VpfFeatureClass*	_featureClass;
    Palette*		_palette;
    char*		_filter;
    int			_dirty;
    IlvManagerLayer*	_managerLayer;
};

#endif /* VPF_GUI_LAYER_H */
