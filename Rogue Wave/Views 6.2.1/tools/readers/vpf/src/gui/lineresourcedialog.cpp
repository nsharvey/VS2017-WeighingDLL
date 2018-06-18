// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/lineresourcedialog.cpp
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
// Definition of the LineResourceDialog class
// --------------------------------------------------------------------------

#include <vpf/gui/lineresourcedialog.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/frame.h>
#if defined(ILVSTD)
# include <cstdio>
# include <cstdlib>
ILVSTDUSE
#else
# include <stdio.h>
# include <stdlib.h>
#endif

// --------------------------------------------------------------------------
void
LineResourceDialog::LineColorCB(IlvGraphic* g, IlvAny arg)
{
    LineResourceDialog* dialog = (LineResourceDialog*) arg;
    dialog->lineColor();
}

// --------------------------------------------------------------------------
void
LineResourceDialog::lineColor()
{
    IlvColorSelector selector(getDisplay(), getSystemView());
    selector.set(_line->getForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	setPaletteForeground(color);
}

// --------------------------------------------------------------------------
void
LineResourceDialog::LineStyleCB(IlvGraphic* g, IlvAny arg)
{
    LineResourceDialog* dialog = (LineResourceDialog*) arg;
    dialog->lineStyle();
}

// --------------------------------------------------------------------------
void
LineResourceDialog::lineStyle()
{
    setPaletteLineStyle(getDisplay()->getLineStyle(_style->getSelection()));
}

// --------------------------------------------------------------------------
void
LineResourceDialog::LineWidthCB(IlvGraphic* g, IlvAny arg)
{
    LineResourceDialog* dialog = (LineResourceDialog*) arg;
    dialog->lineWidth();
}

// --------------------------------------------------------------------------
void
LineResourceDialog::lineWidth()
{
    unsigned int i = atoi(_width->getSelection());
    setPaletteLineWidth(i);
}

// --------------------------------------------------------------------------
LineResourceDialog::LineResourceDialog(IlvDisplay* display, 
				       const char* resourceName, 
				       Palette* palette)
: ResourceDialog(display, "tools/readers/vpf/data/lineresource.ilv",
		 resourceName, palette)
{
    _line = (IlvLine*) getObject("line");
    _line->setForeground(palette->getForeground());
    _line->setLineStyle(palette->getLineStyle());

    _style = (IlvScrolledComboBox*) getObject("style");
    _style->setLabel(palette->getLineStyle()->getName());
    _style->setCallback(LineStyleCB, this);

    char buffer[16];
    sprintf(buffer, "%d", palette->getLineWidth());
    _width = (IlvScrolledComboBox*) getObject("width");
    _width->setLabel(buffer);
    _width->setCallback(LineWidthCB, this);

    getObject("color")->setCallback(LineColorCB, this);
}

// --------------------------------------------------------------------------
LineResourceDialog::~LineResourceDialog()
{
}

// --------------------------------------------------------------------------
void
LineResourceDialog::setPaletteForeground(IlvColor* color)
{
    _line->setForeground(color);
    bufferedDraw(_line);
}

// --------------------------------------------------------------------------
void
LineResourceDialog::setPaletteLineStyle(IlvLineStyle* style)
{
    _line->setLineStyle(style);
    bufferedDraw(_line);
}

// --------------------------------------------------------------------------
void
LineResourceDialog::setPaletteLineWidth(unsigned int i)
{
    _line->setLineWidth(i);
    bufferedDraw(_line);
}

// --------------------------------------------------------------------------
void
LineResourceDialog::apply() 
{
    Palette* palette = getPalette();
    palette->setForeground(_line->getForeground());
    palette->setLineStyle(_line->getLineStyle());
    palette->setLineWidth(_line->getLineWidth());
    ResourceDialog::apply();
}
