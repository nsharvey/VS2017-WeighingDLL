// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/layer.cpp
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
// Definition of the ResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/layer.h>
#include <vpf/gui/palette.h>
#include <vpf/gui/serialize.h>
#include <vpf/gui/databaselist.h>
#include <vpf/gui/databasereferencer.h>

#include <vpf/string.h>
#include <vpf/featureclass.h>
#include <vpf/coverage.h>
#include <vpf/library.h>
#include <vpf/error.h>

// --------------------------------------------------------------------------
Layer::Layer(const char* name,
	     int visible,
	     VpfFeatureClass* fc,
	     Palette* palette,
	     IlvManagerLayer* layer,
	     const char* filter)
: _name(VpfStrDup(name)),
  _visible(visible),
  _featureClass(fc),
  _palette(palette),
  _filter(VpfStrDup(filter)),
  _dirty(1),
  _managerLayer(layer)
{
    if(_featureClass) {
	// We assume that the feature class belongs to a
	// DatabaseReferencer instead of a regular
	// VpfDatabase. This is a prerequisite.
	DatabaseReferencer* db =
	    (DatabaseReferencer*)(_featureClass->getCoverage()->
				  getLibrary()->getDatabase());
	if (db)
	    db->reference();
    }

    if (_palette)
	_palette->setLayer(this);
}

// --------------------------------------------------------------------------
Layer::~Layer()
{
    DatabaseReferencer* db = 0;
    if (_featureClass) {
	db = (DatabaseReferencer*)(_featureClass->getCoverage()->
				   getLibrary()->getDatabase());
	db->unreference();
    }
    if (_name)
	delete [] _name;
    if (_palette)
	delete _palette;
    if (_filter)
	delete _filter;
}

#if 0
// --------------------------------------------------------------------------
Layer::Layer(IlvDisplay* d, Unserialize& s)
: _name(0),
  _visible(0),
  _featureClass(0),
  _palette(0),
  _filter(0),
  _dirty(1)
{
    static const char* Class = "Layer::Layer";
    VpfError* error = 0;

    VpfInt i;
    char* database;
    char* library;
    char* coverage;
    char* featureClass;

    // Read in data
    s >> _name;
    s >> _visible;

    s >> i;
    if (i) {
	_palette = new Palette(d, s);
	_palette->setLayer(this);
    } else
	_palette = 0;

    s >> database;
    s >> library;
    s >> coverage;
    s >> featureClass;

    if (database && library && coverage && featureClass) 
	_featureClass = DatabaseList::FromName(database,
					       library,
					       coverage,
					       featureClass);
    else
	_featureClass = 0;

    if (!_featureClass) {
	error = new VpfError(Class);
	if (error) {
	    error->getStream() << "Could not find feature class "
			       << (database ? database : "(null)") << "/"
			       << (library ? library : "(null)") << "/"
			       << (coverage ? coverage : "(null)") << "/"
			       << (featureClass ? featureClass : "(null)")
			       << " for "
			       << (_name ? "layer " : "unnamed ")
			       << (_name ? _name : "layer") << ".";
	    VpfErrorReporter::Add(error);
	    setBad();
	}
    }

    s >> _filter;
    if (_featureClass) {
	// We assume that the feature class belongs to a
	// DatabaseReferencer instead of a regular
	// VpfDatabase. This is a prerequisite.
	DatabaseReferencer* db =
	    (DatabaseReferencer*)(_featureClass->getCoverage()->
				  getLibrary()->getDatabase());
	if (db)
	    db->reference();
    }
}


// --------------------------------------------------------------------------
void
Layer::write(Serialize& s) const
{
    s << _name;
    s << _visible;

    if (_palette) {
	s << 1;
	_palette->write(s);
    } else
	s << 0;

    if (_featureClass) {
	s << _featureClass->getCoverage()->
	    getLibrary()->getDatabase()->getName();
	s << _featureClass->getCoverage()->getLibrary()->getName();
	s << _featureClass->getCoverage()->getName();
	s << _featureClass->getName();
    } else {
	s << (char*) 0;
	s << (char*) 0;
	s << (char*) 0;
	s << (char*) 0;
    }
    
    s << _filter;
}
#endif

