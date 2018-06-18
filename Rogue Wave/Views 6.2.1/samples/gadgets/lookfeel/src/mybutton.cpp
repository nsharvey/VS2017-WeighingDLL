// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/lookfeel/src/mybutton.cpp
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

#include <mybutton.h>

// --------------------------------------------------------------------------
MyButtonLFHandler::MyButtonLFHandler(IlvLookFeelHandler* lfh)
    : IlvButtonW95LFHandler(lfh),
      _button(0),
      _selbutton(0),
      _highbutton(0)
{
    _button = getDisplay()->getBitmap("button-green.png", IlTrue);
    if (_button)
	_button->lock();
    _selbutton = getDisplay()->getBitmap("pressedbutton-green.png", IlTrue);
    if (_selbutton)
	_selbutton->lock();
    _highbutton = getDisplay()->getBitmap("highbutton-green.png", IlTrue);
    if (_highbutton)
	_highbutton->lock();
}

// --------------------------------------------------------------------------
MyButtonLFHandler::~MyButtonLFHandler()
{
    if (_button)
	_button->unLock();
    if (_selbutton)
	_selbutton->unLock();
    if (_highbutton)
	_highbutton->unLock();
}

// --------------------------------------------------------------------------
void
MyButtonLFHandler::drawBackground(const IlvButton* button,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const
{
    IlvBitmap* bitmap = button->isInverted()
	? _selbutton
	: (button->isHighlighting()
	   ? _highbutton
	   : _button);
    if (!bitmap)
	return;
    IlvRect rect = button->getDefinitionRect();
    if (t)
	t->apply(rect);
    if (rect.w() == bitmap->width() && rect.h() == bitmap->height()) {
	IlvPushClip pushClip(*button->getPalette(), clip);
	dst->drawTransparentBitmap(button->getPalette(),
				   bitmap,
				   IlvRect(0,
					   0,
					   bitmap->width(),
					   bitmap->height()),
				   rect.upperLeft());
    } else {
	IlvRect clipRect;
	if (clip) 
	    clipRect = clip->boundingBox();
	dst->stretchTransparentBitmap(button->getPalette(),
				      rect,
				      bitmap,
				      clip? &clipRect : 0);
    }
}

// --------------------------------------------------------------------------
void
MyButtonLFHandler::drawFrame(const IlvButton*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const
{
}

// --------------------------------------------------------------------------
void
MyButtonLFHandler::drawFocus(const IlvButton*,
			     IlvPort*,
			     const IlvPalette*,
			     const IlvTransformer*,
			     const IlvRegion*) const
{
}

// --------------------------------------------------------------------------
void
MyButtonLFHandler::drawButtonAsDefault(const IlvButton*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const
{
}
