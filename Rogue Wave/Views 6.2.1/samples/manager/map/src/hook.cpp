// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/map/src/hook.cpp
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
// Definition of the Map Hook
// --------------------------------------------------------------------------

#include "hook.h"
#include <ilviews/manager/layer.h>

// --------------------------------------------------------------------------
IlvMapHook::IlvMapHook(IlvManager* mgr,
		       IlvView*    view,
		       IlUShort   startLayer,
		       IlUShort   endLayer)
    : IlvManagerViewHook(mgr, view),
      _startLayer(startLayer),
      _endLayer(endLayer)
{
    if (endLayer == 0)
	_endLayer = _startLayer;
    // Create the bitmap and draw onto it
    _bitmap = new IlvBitmap(getManager()->getDisplay(),
			    view->width(),
			    view->height(),
			    view->depth());
    _palette = 0;
    setBackground(view->getBackground());
}

// --------------------------------------------------------------------------
IlvMapHook::~IlvMapHook()
{
    delete _bitmap;
    _palette->unLock();
}

// --------------------------------------------------------------------------
void
IlvMapHook::setBackground(IlvColor* color)
{
    if (_palette)
	_palette->unLock();
    IlvPalette* palette=color->getDisplay()->defaultPalette();
    _palette = color->getDisplay()->getPalette(palette->getBackground(),
					       color,
					       palette->getPattern(),
					       palette->getColorPattern(),
					       palette->getFont(),
					       palette->getLineStyle(),
					       palette->getLineWidth(),
					       palette->getFillStyle(),
					       palette->getArcMode(),
					       palette->getFillRule());
    _palette->lock();
    adjust();
}

// --------------------------------------------------------------------------
void
IlvMapHook::transformerChanged(const IlvTransformer*,
			       const IlvTransformer*)
{
    adjust();
}

// --------------------------------------------------------------------------
void
IlvMapHook::viewResized()
{
    if (!_bitmap ||
	_bitmap->width() != getView()->width() ||
	_bitmap->height() != getView()->height()) {
	// Create a new bitmap with the new size
	delete _bitmap;
	_bitmap = new IlvBitmap(getView()->getDisplay(),
				getView()->width(), getView()->height(),
				getView()->depth());
	adjust();
    }
}

// --------------------------------------------------------------------------
void
IlvMapHook::adjust()
{
    // Redraw the map on the bitmap
    IlvRect bbox(0, 0, _bitmap->width(), _bitmap->height());
    _bitmap->fillRectangle(_palette, bbox);
    IlvRegion region(bbox);
    IlvManager* manager = getManager();
    IlvTransformer* t = manager->getTransformer(getView());
    for (IlUShort i = _startLayer; i <= _endLayer; ++i) {
	IlBoolean f = manager->isVisible((int)i);
	manager->setVisible((int)i, IlTrue);
	manager->getManagerLayer(i)->draw(_bitmap, t, &region, 0);
	manager->setVisible((int)i, f);
    }
}

// --------------------------------------------------------------------------
void
IlvMapHook::beforeDraw(IlvPort*              dst,
		       const IlvTransformer*,
		       const IlvRegion*      region,
		       const IlvRegion*)
{
    // Copy bitmap onto destination port
    if (region) {
	IlvRect bbox;
	for (IlUShort loop = 0; loop < region->getCardinal(); ++loop) {
	    bbox = region->getRect(loop);
	    dst->drawBitmap(_palette, _bitmap, bbox, bbox.orig());
	}
    }
    else
        dst->drawBitmap(_palette,
			_bitmap,
			IlvRect(0, 0, _bitmap->width(), _bitmap->height()),
			IlvPoint(0, 0));
}
