// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/pointeditor.h
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
// Declaration of the PointEditor class
// -------------------------------------------------------------------------
#ifndef _PointEditor_h_
#define _PointEditor_h_

#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/fbrowser.h>

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/mapfeature.h>

class IlvGadgetContainerRectangle;
class IlvComboBox;
class IlvViewRectangle;
class IlvMapAdapter;
class IlvToggle;
class IlvTextField;
class IlvLabel;
class IlvSelector;
class IlvMatrix;
class IlvFileBrowser;
class IlvMarker;

// -------------------------------------------------------------------------
class PointEditor
    : public IlvGadgetContainerRectangle
{
public:
    PointEditor(IlvDisplay* display,
		const IlvRect& rect,
		IlBoolean allowTexture);
    virtual ~PointEditor();

    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    IlvPalette* getCurrentPalette();

    IlvMarkerType getCurrentMarker();
    IlInt getMarkerSize();
    IlvColor* getMarkerColor();
    IlvBitmap* getCurrentMarkerBitmap();

    IlvMarker* markerFromIndex(int index);
    int indexOfMoreMarkers();
    int indexOfTextureBitmap();

    // Returns the index
    int addUserPointItem(IlvSimpleGraphic *item);

    void setSensitive(IlBoolean set);

    IlvComboBox* getPointCombo() const
	{ return _pointCombo; }
    IlInt getCurrentSelection() const
	{ return _currentSelection; }
    void setCurrentSelection(IlInt selection)
	{ _currentSelection = selection; }
    const IlvRect& getPreviewsize() const
	{  return _previewsize; }
    void setHasTexture(IlBoolean h)
	{ _hasTexture  = h; }
    IlvFileBrowser* getTextureBrowser() const
	{ return _textureBrowser; }
private:
    void createStandardPointItems(const IlvRect& size);
    void addStdPointItem(IlvSimpleGraphic* preview);

    IlvComboBox* _pointCombo;
    IlInt _lastStdColorIndex;
    IlInt _userColorCount;
    IlInt _currentSelection;
    IlvRect _previewsize;
    IlBoolean _allowBitmap;
    IlBoolean _hasTexture;
    IlvFileBrowser* _textureBrowser;

};
#endif
