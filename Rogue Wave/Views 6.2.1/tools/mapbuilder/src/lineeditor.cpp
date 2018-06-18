// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/lineeditor.cpp
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
// The implementation of the LineEditor methods.
// --------------------------------------------------------------------------
#include "lineeditor.h"

#include <ilviews/manager/manager.h>
#include <ilviews/manager/selinter.h>

#include <ilviews/graphics/rectview.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/line.h>

#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/fbrowser.h>

#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/rendering/all.h>

#include <ilviews/bitmaps/io.h>

#if defined(IL_STD)
#  include <cstring>
#  include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#  include <string.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
static void
StyleChangedCB(IlvGraphic* graphic,IlvAny arg)
{
    LineEditor* editor = (LineEditor*)arg;
    int index = editor->getColorCombo()->whichSelected();
    editor->setCurrentSelection(index);
}

// --------------------------------------------------------------------------
IlvPalette*
LineEditor::getCurrentPalette()
{
    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)
	_colorCombo->getItemData((IlUShort)_currentSelection);
    return graphic->getPalette();
}

// --------------------------------------------------------------------------
LineEditor::LineEditor(IlvDisplay* display,
			 const IlvRect& rect)
: IlvGadgetContainerRectangle(display,rect),
  _colorCombo(0),
  _currentSelection(0)
{
}

// --------------------------------------------------------------------------
LineEditor::~LineEditor()
{

}

// --------------------------------------------------------------------------
IlvView*
LineEditor::createView(IlvAbstractView* parent, const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent,rect);
    
    IlvGadgetContainer* container = (IlvGadgetContainer*)view;

    IlvRect combosize(0,
		      0,
		      rect.w(),
		      rect.h());

    
    _colorCombo = new IlvComboBox(parent->getDisplay(),combosize,0,
				 0,0,3);
    _colorCombo->setEditable(IlFalse);

    _colorCombo->getSubMenu()->setLabelPosition(IlvLeft);
    _colorCombo->addCallback(StyleChangedCB,(IlvAny)this);
    
    container->addObject(_colorCombo);
    container->getHolder()->attach(_colorCombo,IlvHorizontal,0,1,0);
    container->getHolder()->attach(_colorCombo,IlvVertical,0,1,0);

    IlvRect colorsize(0,0,combosize.w()-40,combosize.h()-8);
    _previewsize.x(colorsize.x());
    _previewsize.y(colorsize.y());
    _previewsize.w(colorsize.w() - 20);
    _previewsize.h(colorsize.h());
    createStandardStyleItems(_previewsize);
  
    // selecto color 0
    _colorCombo->setSelected(0);
    return view;
}

// --------------------------------------------------------------------------
void LineEditor::addStdStyleItem(IlvSimpleGraphic* preview)
{
    IlvGraphicSet* set = new IlvGraphicSet();
    set->addObject(preview);
    int linewidth = preview->getLineWidth();
    char buf[50];
    sprintf(buf, "%d", linewidth);
    IlvLabel* lab = new IlvLabel(getDisplay(),
				 IlvPoint(0,0),
				 buf);

    lab->move(preview->x() + preview->w() + 5,
	      (int)(preview->y() + (((int)preview->h()-(int)lab->h()) / 2)));
    set->addObject(lab);
    IlvLine* line = new IlvLine(getDisplay(),
				IlvPoint(preview->x() - 2,
					 preview->y() - 8),
				IlvPoint(preview->x() - 2,
					 preview->y() + preview->h() + 8));
    set->addObject(line);
    line->setForeground(getDisplay()->getColor("white"));
    _colorCombo->insertGraphic(set);
    _colorCombo->setItemData(_colorCombo->getCardinal()-1,
			    (IlvAny)preview);

}

// --------------------------------------------------------------------------
void
LineEditor::createStandardStyleItems(const IlvRect& size)
{
    IlvDisplay* display = getDisplay();


    static const int stdStyleNum = 9;

    IlvPoint from(size.x(), size.y() + size.h() / 2);
    IlvPoint to(size.x()+size.w(), from.y());

    for (int i = 0; i < stdStyleNum; i++) {
	IlvLine* graphic = new IlvLine(display, from, to);
	graphic->setForeground(display->getColor("black"));
	graphic->setLineWidth(i);
	addStdStyleItem(graphic);
    }
}

// --------------------------------------------------------------------------
void LineEditor::setSensitive(IlBoolean set)
{
    _colorCombo->setSensitive(set);
    IlvGadgetContainerRectangle::setSensitive(set);
}
