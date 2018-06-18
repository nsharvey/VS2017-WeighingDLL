// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/pointresourcedialog.cpp
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
// Definition of the PointResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/pointresourcedialog.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/optmenu.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/gadgets/spinbox.h>
#include <ilviews/gadgets/frame.h>

static IlvMarkerType table[10] = {
  IlvMarkerSquare,
  IlvMarkerDiamond,
  IlvMarkerCircle,
  IlvMarkerCross,
  IlvMarkerPlus,
  IlvMarkerTriangle,
  IlvMarkerFilledSquare,
  IlvMarkerFilledDiamond,
  IlvMarkerFilledCircle,
  IlvMarkerFilledTriangle
};

// --------------------------------------------------------------------------
void
PointResourceDialog::PointColorCB(IlvGraphic* g, IlvAny arg)
{
    PointResourceDialog* dialog = (PointResourceDialog*) arg;
    dialog->pointColor();
}

// --------------------------------------------------------------------------
void
PointResourceDialog::pointColor()
{
    IlvColorSelector selector(getDisplay(), getSystemView());
    selector.set(_marker->getForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	setPaletteForeground(color);
}

// --------------------------------------------------------------------------
void
PointResourceDialog::PointStyleCB(IlvGraphic* g, IlvAny arg)
{
    PointResourceDialog* dialog = (PointResourceDialog*) arg;
    dialog->pointStyle();
}

// --------------------------------------------------------------------------
void
PointResourceDialog::pointStyle()
{
    setPaletteStyle(table[_style->whichSelected()]);
}

// --------------------------------------------------------------------------
void
PointResourceDialog::PointSizeCB(IlvGraphic* g, IlvAny arg)
{
    PointResourceDialog* dialog = (PointResourceDialog*) arg;
    dialog->pointSize();
}

// --------------------------------------------------------------------------
void
PointResourceDialog::pointSize()
{
    IlBoolean error = IlFalse;
    IlUShort size = (IlUShort)
	_size->getValue((IlvNumberField*)_size->getObject(0), error);
    if (!error)
	setPaletteSize(size);
}

// --------------------------------------------------------------------------
PointResourceDialog::PointResourceDialog(IlvDisplay* display, 
					 const char* resourceName, 
					 Palette* palette)
: ResourceDialog(display, "tools/readers/vpf/data/pointresource.ilv",
		 resourceName, palette)
{
    _marker = (IlvMarker*)getObject("marker");
    _style = (IlvOptionMenu*)getObject("style");
    for (IlUShort i = 0; i < 10; i++)
	if (table[i] == palette->getMarkerType()) {
	    _style->setSelected(i);
	    break;
	}
    _style->setCallback(PointStyleCB, this);

    _size = (IlvSpinBox*) getObject("size");
    _size->setValue((IlvNumberField*)_size->getObject(0),
		    palette->getMarkerSize());
    _size->getObject(0)->setCallback(PointSizeCB, this);
    _size->setCallback(IlvSpinBox::IncrementCallbackType(), PointSizeCB, this);
    _size->setCallback(IlvSpinBox::DecrementCallbackType(), PointSizeCB, this);
    getObject("color")->setCallback(PointColorCB, this);
    setPaletteForeground(palette->getForeground());
    setPaletteStyle(palette->getMarkerType());
    setPaletteSize(palette->getMarkerSize());
}

// --------------------------------------------------------------------------
PointResourceDialog::~PointResourceDialog()
{
}

// --------------------------------------------------------------------------
void
PointResourceDialog::setPaletteForeground(IlvColor* color)
{
    _marker->setForeground(color);
    bufferedDraw(_marker);
}

// --------------------------------------------------------------------------
void
PointResourceDialog::setPaletteStyle(IlvMarkerType style)
{
    IlvRect oldbbox;
    IlvRect newbbox;
    _marker->boundingBox(oldbbox);
    _marker->setType(style);
    _marker->move(oldbbox.x(), oldbbox.y());
    _marker->boundingBox(newbbox);
    oldbbox.add(newbbox);

    // Tackle a views bug, some markers return a
    // too small bbox
    oldbbox.grow(2, 2); 

    bufferedDraw(oldbbox);
}

// --------------------------------------------------------------------------
void
PointResourceDialog::setPaletteSize(IlUShort size)
{
    IlvRect oldbbox;
    IlvRect newbbox;
    _marker->boundingBox(oldbbox);
    _marker->setSize(size);
    _marker->move(oldbbox.x(), oldbbox.y());
    _marker->boundingBox(newbbox);
    oldbbox.add(newbbox);

    // Tackle a views bug, some markers return a
    // too small bbox
    oldbbox.grow(2, 2);

    bufferedDraw(oldbbox);
}

// --------------------------------------------------------------------------
void
PointResourceDialog::apply() 
{
    Palette* palette = getPalette();
    palette->setForeground(_marker->getForeground());
    palette->setMarkerType(_marker->getType());
    palette->setMarkerSize(_marker->getSize());
    ResourceDialog::apply();
}
