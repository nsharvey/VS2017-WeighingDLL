// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/paleditor.h
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
// Declaration of the PaletteEditor class
// -------------------------------------------------------------------------
#ifndef _PaletteEditor_h_
#define _PaletteEditor_h_

#include <ilviews/gadgets/rectgadc.h>

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/mapfeature.h>

#include "coloreditor.h"
#include "lineeditor.h"
#include "dasheditor.h"
#include "pointeditor.h"

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
class PaletteEditor
    : public IlvGadgetContainerRectangle
{
public:
    PaletteEditor(IlvDisplay* display, const IlvRect& rect);
    virtual ~PaletteEditor();

    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    IlvPalette* getFillPalette() const;
    IlvPalette* getLinePalette() const;

    IlvBitmap* getMarkerBitmap() const;
    IlvMarkerType getMarkerType() const;
    IlInt getMarkerSize() const;
    IlvColor* getMarkerColor() const;
    IlvAntialiasingMode getAntialiasingMode() const;
    IlDouble getTransparency() const;

    void setFillEditingMode(IlBoolean set)
	{ _fillEdit = set; changeSensitivity(); }
    IlBoolean isFillEditingMode() const
	{ return _fillEdit; }

    void setLineEditingMode(IlBoolean set)
	{ _lineEdit = set; changeSensitivity(); }
    IlBoolean isLineEditingMode() const
	{ return _lineEdit; };

    void setPointEditingMode(IlBoolean set)
	{ _pointEdit = set; changeSensitivity(); }
    IlBoolean isPointEditingMode() const
	{ return _pointEdit; };

    void changeSensitivity();

    ColorEditor* getFillColorCombo() const
	{ return _fillColorCombo; }
    ColorEditor* getLineColorCombo() const
	{ return _lineColorCombo; }
    LineEditor* getLineThicknessCombo() const
	{ return _lineThicknessCombo; }
    DashEditor* getLineDashCombo() const
	{ return _lineDashCombo; }
    PointEditor* getPointSymbolCombo() const
	{ return _pointSymbolCombo; }
private:
    IlvLabel* _fillColorLabel;
    ColorEditor* _fillColorCombo;

    IlvLabel* _lineColorLabel;
    ColorEditor* _lineColorCombo;

    IlvLabel* _lineThicknessLabel;
    LineEditor* _lineThicknessCombo;

    IlvLabel* _lineDashLabel;
    DashEditor* _lineDashCombo;

    IlvLabel* _pointSymbolLabel;
    PointEditor* _pointSymbolCombo;

    IlBoolean _fillEdit;
    IlBoolean _lineEdit;
    IlBoolean _pointEdit;
};
#endif /*_PaletteEditor_h_*/
