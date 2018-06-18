// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/libdeps/src/objsel.cpp
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
// Definition of new selection objects:
// GraphLayoutNodeSelection and GraphLayoutLinkSelection
// --------------------------------------------------------------------------

#include <objsel.h>

// --------------------------------------------------------------------------
GraphLayoutNodeSelection::GraphLayoutNodeSelection(IlvDisplay* display,
						   IlvGraphic* object)
    : IlvGraphNodeSelection(display, object)
{
    IlvPalette* pal = display->getPalette(0, display->getColor("blue"));
    pal->lock();
    setPalette(pal);
    pal->unLock();
}

// --------------------------------------------------------------------------
void
GraphLayoutNodeSelection::draw(IlvPort* dst,
			       const IlvTransformer* t,
			       const IlvRegion* clip) const
{
    if (isVisible(dst)) {
	IlvPalette* pal = _palette;
	IlvPushClip pushClip(*pal, clip);
	IlvRect rect;
	getObject()->boundingBox(rect,t);
	dst->drawRectangle(pal, rect);
    }
}

// --------------------------------------------------------------------------
void
GraphLayoutNodeSelection::boundingBox(IlvRect& r,
				      const IlvTransformer* t) const
{
    getObject()->boundingBox(r, t);
}

// --------------------------------------------------------------------------
GraphLayoutLinkSelection::GraphLayoutLinkSelection(IlvDisplay* display,
						   IlvGraphic* object)
: IlvGraphLinkSelection(display, object)
{
    _layoutPalette = display->getPalette(0, display->getColor("red"));
    if (_layoutPalette)
	_layoutPalette->lock();
}

// --------------------------------------------------------------------------
GraphLayoutLinkSelection::~GraphLayoutLinkSelection()
{
    if (_layoutPalette)
	_layoutPalette->unLock();
}

// --------------------------------------------------------------------------
void
GraphLayoutLinkSelection::boundingBox(IlvRect& r,
				      const IlvTransformer* t) const
{
    getObject()->boundingBox(r, t);
}

// --------------------------------------------------------------------------
IlUInt
GraphLayoutLinkSelection::getHandlesCount(const IlvTransformer*) const
{
    return 0;
}

// --------------------------------------------------------------------------
void
GraphLayoutLinkSelection::draw(IlvPort* dst,
			       const IlvTransformer* t,
			       const IlvRegion* clip) const
{
    IlvLinkImage* link = getLink();
    link->drawPalette(_layoutPalette, dst, t, clip);
}

// --------------------------------------------------------------------------
void
GraphLayoutLinkSelection::computeRegion(IlvRegion& region, 
					const IlvTransformer* t) const
{
    IlvLinkImage* link = getLink();
    if (!link)
	return;
    IlvRect r;
    _object->boundingBox(r, t);
    region.add(r);
}

// --------------------------------------------------------------------------
