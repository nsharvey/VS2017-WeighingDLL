// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/lookfeel/src/mytree.cpp
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

#include <mytree.h>
#include <mylook.h>

// --------------------------------------------------------------------------
MyTreeLFHandler::MyTreeLFHandler(IlvLookFeelHandler* lfh)
    : IlvTreeGadgetW95LFHandler(lfh),
      _expandedBitmap(0),
      _shrunkBitmap(0)
{
    _expandedBitmap = getDisplay()->getBitmap("expanded.png", IlTrue);
    if (_expandedBitmap)
	_expandedBitmap->lock();
    _shrunkBitmap = getDisplay()->getBitmap("shrunk.png", IlTrue);
    if (_shrunkBitmap)
	_shrunkBitmap->lock();
}

// --------------------------------------------------------------------------
MyTreeLFHandler::~MyTreeLFHandler()
{
    if (_expandedBitmap)
	_expandedBitmap->unLock();
    if (_shrunkBitmap)
	_shrunkBitmap->unLock();
}

// --------------------------------------------------------------------------
void
MyTreeLFHandler::drawButton(const IlvTreeGadget* tree,
			    IlvPort* dst,
			    const IlvTreeGadgetItem* item,
			    const IlvRect& rect,
			    const IlvRegion* clip) const
{
    IlvBitmap* bitmap = item->isExpanded()
	? _expandedBitmap
	: _shrunkBitmap;
    if (!bitmap)
	return;
    IlvRect clipRect;
    if (clip) 
	clipRect = clip->boundingBox();
    dst->stretchTransparentBitmap(tree->getPalette(),
				  rect,
				  bitmap,
				  clip? &clipRect : 0);
}
