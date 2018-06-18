// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/coloreditor.cpp
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
// The implementation of ColorEditor methods.
// --------------------------------------------------------------------------
#include "builder.h"
#include "coloreditor.h"

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
ILVSTDUSE
#else  /* !IL_STD */
#  include <string.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
// Returns true if the color of the specified palette, if existent
// note : returns 0, if the palette is patterned
static IlvColor*
GetColor(const IlvPalette* pal)
{
    return pal->getForeground();
}

// --------------------------------------------------------------------------
static void
ColorChangedCB(IlvGraphic* graphic, IlAny arg)
{
    ColorEditor* editor = (ColorEditor*)arg;
    IlvDisplay* display = editor->getDisplay();

    int index = editor->getColorCombo()->whichSelected();
    if (index == editor->indexOfMoreColors()) {
	// case of menu item selected
	editor->setHasTexture(IlFalse);
	IlvColorSelector selector(editor->getDisplay(),
				  editor->getView()->getSystemView());
	IlvColor* current =
		       editor->colorFromIndex(editor->getCurrentSelection());
	if (current) {
	    selector.set(current);
	}
	selector.moveToView(GetBuilder()->getMainWindow()); 
	IlvColor* newColor = selector.get();
	if (!newColor) {
	    // case of cancel
	    editor->getColorCombo()->setSelected((IlUShort)
					      editor->getCurrentSelection());
	    return;
	}
	else {
	    // add a user color
	    IlvReliefRectangle* graphic =
		new IlvReliefRectangle(display, editor->getPreviewSize());
	    graphic->setBackground(newColor);
	    graphic->setForeground(newColor);
	    graphic->setThickness(1);
	    int insert = editor->addUserColorItem(graphic);
	    editor->setCurrentSelection(insert);
	    editor->getColorCombo()->setSelected(insert);
	    editor->colorChanged();
	}
    }
    else if (index == editor->indexOfTextureBitmap()) {
	// case of texture
	editor->setHasTexture(IlTrue);
	const char* filename = editor->getTextureBrowser()->get();
	if (!filename) {
	    editor->getColorCombo()->setSelected((IlUShort)
					      editor->getCurrentSelection());
	    return;
	}
	IlvMapAreaRenderingStyle* style =
	    new IlvMapAreaRenderingStyle(display);
	style->lock();
	IlvFilledRectangle* graphic =
	    new IlvFilledRectangle(display, editor->getPreviewSize());
	style->setFillPattern(filename);
	graphic->setPalette(style->getPalette());
	style->unLock();
	int insert = editor->addUserColorItem(graphic);
	editor->setCurrentSelection(insert);
	editor->getColorCombo()->setSelected(insert);
	editor->colorChanged();
    }
    else  {
	// case of color selected
	editor->setHasTexture(IlFalse);
	editor->setCurrentSelection(index);
	editor->colorChanged();
    }
}

// --------------------------------------------------------------------------
IlvPalette*
ColorEditor::getCurrentPalette()
{
    if (getCurrentSelection() == indexOfMoreColors()) {
	return 0;
    }
    else {
	if (getCurrentSelection() < _lastStdColorIndex) {
	    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)
	       getColorCombo()->getItemData((IlUShort)getCurrentSelection());
	    if (graphic == 0) {
		return 0;
	    }
	    return graphic->getPalette();
	}
	else {
	    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)
	       getColorCombo()->getItemData((IlUShort)getCurrentSelection());
	    return graphic->getPalette();
	}
    }
}

// --------------------------------------------------------------------------
IlvColor*
ColorEditor::colorFromIndex(int index)
{
    if (index == indexOfMoreColors()) {
	return 0;
    }
    else {
	if (index < _lastStdColorIndex) {
	    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)
		getColorCombo()->getItemData(index);
	    if (graphic == 0) {
		return 0;
	    }
	    IlvColor* color = GetColor(graphic->getPalette());
	    return color;
	}
	else {
	    IlvSimpleGraphic* graphic = (IlvSimpleGraphic*)
		getColorCombo()->getItemData(index);
	    IlvColor* color = GetColor(graphic->getPalette());
	    return color;
	}
    }
    return 0; // Unreachable
}

// --------------------------------------------------------------------------
// Constructor
ColorEditor::ColorEditor(IlvDisplay* display,
			 const IlvRect& rect,
			 IlBoolean allowTexture)
    : IlvGadgetContainerRectangle(display,rect),
      _colorCombo(0),
      _lastStdColorIndex(-1),
      _userColorCount(0),
      _currentSelection(1),
      _allowTextureBitmap(allowTexture),
      _hasTexture(IlFalse),
      _textureBrowser(0)
{
}

// --------------------------------------------------------------------------
ColorEditor::~ColorEditor()
{

}

// --------------------------------------------------------------------------
IlvView*
ColorEditor::createView(IlvAbstractView* parent, const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent,rect);

    IlvGadgetContainer* container = (IlvGadgetContainer*)view;
    IlvRect size(0, 0, rect.w(), rect.h());
    _colorCombo = new IlvComboBox(parent->getDisplay(), size, 0, 0, 0, 3);
    _colorCombo->setEditable(IlFalse);
    _colorCombo->getSubMenu()->setLabelPosition(IlvLeft);
    _colorCombo->addCallback(ColorChangedCB, (IlAny) this);
    container->addObject(_colorCombo);
    container->getHolder()->attach(_colorCombo, IlvHorizontal, 0, 1, 0);
    container->getHolder()->attach(_colorCombo, IlvVertical, 0, 1, 0);
    IlvRect colorsize(0, 0, size.w() - 40, size.h() - 8);
    _previewsize.x(colorsize.x());
    _previewsize.y(colorsize.y());
    _previewsize.w(colorsize.w());
    _previewsize.h(colorsize.h());
    createStandardColorItems(colorsize);
    // a separator
    IlvMenuItem* sep = new IlvMenuItem();
    sep->setReadOnly(IlTrue);
    _colorCombo->insertItem(sep);
    _lastStdColorIndex = _colorCombo->getCardinal();
    // an additionnal item for more colors
    IlvMenuItem* moreColors = new IlvMenuItem("More colors...");
    _colorCombo->insertItem(moreColors);
    // an additionnal item for color index
    if (_allowTextureBitmap) {
	IlvMenuItem* textureBitmap = new IlvMenuItem("Texture bitmap...");
	_colorCombo->insertItem(textureBitmap);
    }
    // selecto color 0
    _colorCombo->setSelected(1);

    // the file browsers
    _textureBrowser = new IlvFileBrowser(parent->getDisplay(),
					 parent->getSystemView(),
					 0,
					 0,
					 0);

    _textureBrowser->setType(IlvFileSelectorLoad);

    return view;
}

// --------------------------------------------------------------------------
void
ColorEditor::addStdColorItem(IlvSimpleGraphic* preview)
{
    if (preview) {
	IlvGraphicSet* set = new IlvGraphicSet();
	set->addObject(preview);
	IlvLine* line = new IlvLine(getDisplay(),
				    IlvPoint(preview->x() - 2,
					     preview->y() - 2),
				    IlvPoint(preview->x() - 2,
					     preview->y()
					     + preview->h() + 2));
	set->addObject(line);
	line->setForeground(getDisplay()->getColor("white"));
	_colorCombo->insertGraphic(set);
	_colorCombo->setItemData(_colorCombo->getCardinal() - 1,
				 (IlAny) preview);
    }
    else {
	IlvLabel* label = new IlvLabel(getDisplay(), IlvPoint(0, 0), "None");
	_colorCombo->insertGraphic(label);
	_colorCombo->setItemData(_colorCombo->getCardinal()-1,0);
    }
}

// --------------------------------------------------------------------------
int
ColorEditor::addUserColorItem(IlvSimpleGraphic* preview)
{
    int index = _lastStdColorIndex + _userColorCount;
  
    if (_userColorCount == 0) {
	IlvMenuItem* sep = new IlvMenuItem();
	sep->setReadOnly(IlTrue);
	_colorCombo->insertItem(sep,index);
    }
    IlvGraphicSet* set = new IlvGraphicSet();
    set->addObject(preview);
    IlvLine* line = new IlvLine(getDisplay(),
				IlvPoint(preview->x() - 2,
					 preview->y() - 2),
				IlvPoint(preview->x() - 2,
					 preview->y() + preview->h() + 2));
    set->addObject(line);
    line->setForeground(getDisplay()->getColor("white"));
    _colorCombo->insertGraphic(set,index);
    _colorCombo->setItemData(index, (IlAny) preview);

    _userColorCount ++;
    return index;
}

// --------------------------------------------------------------------------
static IlvColor*
GetColor(IlvDisplay*display,int r,int g,int b)
{
    return display->getColor((IlvIntensity)(r*255),
			     (IlvIntensity)(g*255),
			     (IlvIntensity)(b*255));
}

// --------------------------------------------------------------------------
void
ColorEditor::createStandardColorItems(const IlvRect& size)
{
    IlvDisplay* display = getDisplay();

    // add a "None" value
    addStdColorItem(0);

    // add std colors
    static const char *stdColor[] = {
	"black",
	"gray",
	"white",
	"red",
	"green",
	"blue",
	"cyan",
	"magenta",
	"yellow"
    };
    static const int stdColorNum = 9;

    for (int i=0; i < stdColorNum; i++) {
	IlvReliefRectangle* graphic = new IlvReliefRectangle(display,size);
	graphic->setBackground(display->getColor(stdColor[i]));
	graphic->setForeground(display->getColor(stdColor[i]));
	graphic->setThickness(1);
	addStdColorItem(graphic);
    }

    // some more colors, specified by their rgb values
    IlvReliefRectangle* graphic = 0;
    
    // a nice light orange
    graphic = new IlvReliefRectangle(display, size);
    graphic->setBackground(GetColor(display, 255, 153, 0));
    graphic->setForeground(GetColor(display, 255, 153, 0));
    graphic->setThickness(1);
    addStdColorItem(graphic);
    
    // a nice dark green
    graphic = new IlvReliefRectangle(display, size);
    graphic->setBackground(GetColor(display, 0, 128, 0));
    graphic->setForeground(GetColor(display, 0, 128, 0));
    graphic->setThickness(1);
    addStdColorItem(graphic);
    
    // a nice light blue
    graphic = new IlvReliefRectangle(display, size);
    graphic->setBackground(GetColor(display, 51, 102, 255));
    graphic->setForeground(GetColor(display, 51, 102, 255));
    graphic->setThickness(1);
    addStdColorItem(graphic);
    
    // a nice sky blue
    graphic = new IlvReliefRectangle(display, size);
    graphic->setBackground(GetColor(display, 0, 204, 255));
    graphic->setForeground(GetColor(display, 0, 204, 255));
    graphic->setThickness(1);
    addStdColorItem(graphic);
}


// --------------------------------------------------------------------------
// Returns the index of the 'more colors' item
int
ColorEditor::indexOfMoreColors()
{
    if (_allowTextureBitmap) {
	return _colorCombo->getCardinal() - 2;
    }
    return _colorCombo->getCardinal() - 1;
}

// --------------------------------------------------------------------------
// Returns the index of the 'texture bitmap' item
int
ColorEditor::indexOfTextureBitmap()
{
    if (!_allowTextureBitmap) {
	return -1;
    }
    return _colorCombo->getCardinal()-1;
}

// --------------------------------------------------------------------------
void
ColorEditor::setSensitive(IlBoolean set)
{
    _colorCombo->setSensitive(set);
    IlvGadgetContainerRectangle::setSensitive(set);
}

// --------------------------------------------------------------------------
void
ColorEditor::colorChanged()
{
}
