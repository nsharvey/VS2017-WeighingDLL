// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/textresourcedialog.cpp
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
// Definition of the TextResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/textresourcedialog.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/fontsel.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/label.h>
#include <ilviews/gadgets/frame.h>

// --------------------------------------------------------------------------
void
TextResourceDialog::TextColorCB(IlvGraphic* g, IlvAny arg)
{
    TextResourceDialog* dialog = (TextResourceDialog*)arg;
    dialog->textColor();
}

// --------------------------------------------------------------------------
void
TextResourceDialog::textColor()
{
    IlvColorSelector selector(getDisplay(), getSystemView());
    selector.set(_text->getForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	setPaletteForeground(color);
}

// --------------------------------------------------------------------------
void
TextResourceDialog::TextStyleCB(IlvGraphic* g, IlvAny arg)
{
    TextResourceDialog* dialog = (TextResourceDialog*) arg;
    dialog->textStyle();
}

// --------------------------------------------------------------------------
void
TextResourceDialog::textStyle()
{
    IlvFontSelector selector(getDisplay(), getSystemView());
    selector.moveToMouse();
    IlvFont* font = selector.get();
    if (font)
	setPaletteStyle(font);
}

// --------------------------------------------------------------------------
TextResourceDialog::TextResourceDialog(IlvDisplay* display, 
				       const char* resourceName, 
				       Palette* palette)
: ResourceDialog(display, "tools/readers/vpf/data/textresource.ilv",
		 resourceName, palette)
{
    _text = (IlvLabel*)getObject("text");
    _text->setForeground(palette->getForeground());
    getObject("color")->setCallback(TextColorCB, this);
    getObject("font")->setCallback(TextStyleCB, this);
}

// --------------------------------------------------------------------------
TextResourceDialog::~TextResourceDialog()
{
}

// --------------------------------------------------------------------------
void
TextResourceDialog::setPaletteForeground(IlvColor* color)
{
    _text->setForeground(color);
    bufferedDraw(_text);
}

// --------------------------------------------------------------------------
void
TextResourceDialog::setPaletteStyle(IlvFont* style)
{
    IlvRect oldbbox;
    IlvRect newbbox;
    _text->boundingBox(oldbbox);
    _text->setFont(style);
    _text->move(oldbbox.x(), oldbbox.y());
    _text->boundingBox(newbbox);
    oldbbox.add(newbbox);
    bufferedDraw(oldbbox);
}

// --------------------------------------------------------------------------
void
TextResourceDialog::apply() 
{
    Palette* palette = getPalette();
    palette->setForeground(_text->getForeground());
    palette->setFont(_text->getFont());
    ResourceDialog::apply();
}
