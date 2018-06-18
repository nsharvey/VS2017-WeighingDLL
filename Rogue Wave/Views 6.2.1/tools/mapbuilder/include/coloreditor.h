// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/coloreditor.h
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
// Declaration of the ColorEditor class
// -------------------------------------------------------------------------
#ifndef _ColorEditor_h_
#define _ColorEditor_h_

#include <ilviews/gadgets/rectgadc.h>

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/gadgets/fbrowser.h>

class IlvGadgetContainerRectangle;
class IlvComboBox;
class IlvViewRectangle;
class IlvMapAdapter;
class IlvToggle;
class IlvTextField;
class IlvLabel;
class IlvSelector;
class IlvMatrix;

// -------------------------------------------------------------------------
class ColorEditor
    : public IlvGadgetContainerRectangle
{
public:
    ColorEditor(IlvDisplay* display,
		const IlvRect& rect,
		IlBoolean allowTexture);
    virtual ~ColorEditor();

    virtual IlvView* createView(IlvAbstractView* parent,
				const IlvRect& size);

    IlvPalette* getCurrentPalette();

    IlvColor* colorFromIndex(int index);
    int indexOfMoreColors();
    int indexOfTextureBitmap();

    virtual void colorChanged();

    // returns the index
    int addUserColorItem(IlvSimpleGraphic *item);

    void setSensitive(IlBoolean set);

    void createStandardColorItems(const IlvRect& size);
    void addStdColorItem(IlvSimpleGraphic* preview);

    IlvComboBox* getColorCombo() const
	{ return _colorCombo; }
    IlInt getCurrentSelection() const
	{ return _currentSelection; }
    void setCurrentSelection(IlInt currentSelection) 
	{ _currentSelection = currentSelection; }
    const IlvRect& getPreviewSize() const
	{ return _previewsize; }
    IlBoolean hasTexture() const
	{ return _hasTexture; }
    void setHasTexture(IlBoolean h)
	{ _hasTexture  = h; }
    IlvFileBrowser* getTextureBrowser() const
	{ return _textureBrowser; }
private:
    IlvComboBox* _colorCombo;
    IlInt _lastStdColorIndex;
    IlInt _userColorCount;
    IlInt _currentSelection;
    IlvRect _previewsize;
    IlBoolean _allowTextureBitmap;
    IlBoolean _hasTexture;
    IlvFileBrowser* _textureBrowser;

};
#endif
