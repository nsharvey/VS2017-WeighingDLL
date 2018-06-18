// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/arearesourcedialog.cpp
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
// Definition of the AreaResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/arearesourcedialog.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/frame.h>

// --------------------------------------------------------------------------
void
AreaResourceDialog::FaceColorCB(IlvGraphic* g, IlvAny arg)
{
    AreaResourceDialog* dialog = (AreaResourceDialog*) arg;
    dialog->faceColor();
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::faceColor()
{
    IlvColorSelector selector(getDisplay(), getSystemView());
    selector.set(_foregroundRect->getForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	setPaletteForeground(color);
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::FacePatternCB(IlvGraphic* g, IlvAny arg)
{
    AreaResourceDialog* dialog = (AreaResourceDialog*) arg;
    dialog->facePattern();
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::facePattern()
{
    setPalettePattern(getDisplay()->getPattern(_combo->getSelection()));
}

// --------------------------------------------------------------------------
AreaResourceDialog::AreaResourceDialog(IlvDisplay* display, 
				       const char* resourceName, 
				       Palette* palette)
: ResourceDialog(display, "tools/readers/vpf/data/arearesource.ilv",
		 resourceName, palette)
{
    _foregroundRect = (IlvFilledRectangle*)getObject("sample");
    _foregroundRect->setForeground(palette->getForeground());

    _patternRect = _foregroundRect;
    _patternRect->setPattern(palette->getPattern());

    _combo = (IlvScrolledComboBox*)getObject("pattern");
    _combo->setLabel(palette->getLineStyle()->getName());
    _combo->setCallback(FacePatternCB, this);

    getObject("color")->setCallback(FaceColorCB, this);
}

// --------------------------------------------------------------------------
AreaResourceDialog::~AreaResourceDialog()
{
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::setPaletteForeground(IlvColor* color)
{
    _foregroundRect->setForeground(color);
    bufferedDraw(_foregroundRect);
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::setPalettePattern(IlvPattern* pattern)
{
    _patternRect->setPattern(pattern);
    bufferedDraw(_patternRect);
}

// --------------------------------------------------------------------------
void
AreaResourceDialog::apply() 
{
    Palette* palette = getPalette();
    palette->setForeground(_foregroundRect->getForeground());
    palette->setPattern(_patternRect->getPattern());
    ResourceDialog::apply();
}
