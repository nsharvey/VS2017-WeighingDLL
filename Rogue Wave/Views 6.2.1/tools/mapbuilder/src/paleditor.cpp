// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/paleditor.cpp
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
// The implementation of the PaletteEditor methods.
// --------------------------------------------------------------------------
#include "paleditor.h"

#include <ilviews/manager/manager.h>
#include <ilviews/manager/selinter.h>

#include <ilviews/graphics/rectview.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/graphics/relfline.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/handle.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/toggle.h>

#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/rendering/all.h>

#if defined(IL_STD)
#  include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#  include <string.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
PaletteEditor::PaletteEditor(IlvDisplay* display,
			     const IlvRect& rect)
: IlvGadgetContainerRectangle(display, rect),
  _fillColorLabel(0),
  _fillColorCombo(0),
  _lineColorLabel(0),
  _lineColorCombo(0),
  _lineThicknessLabel(0),
  _lineThicknessCombo(0),
  _lineDashLabel(0),
  _lineDashCombo(0),
  _pointSymbolLabel(0),
  _pointSymbolCombo(0),
  _fillEdit(IlTrue),
  _lineEdit(IlTrue),
  _pointEdit(IlTrue)
{
}

// --------------------------------------------------------------------------
PaletteEditor::~PaletteEditor()
{
}

// --------------------------------------------------------------------------
IlvPalette*
PaletteEditor::getLinePalette() const
{
    if (_lineEdit && _lineColorCombo) {
	IlvPalette* colorPal = _lineColorCombo->getCurrentPalette();
	if (!colorPal) {
	    return 0;
	}
	IlvPalette* linePal = _lineThicknessCombo->getCurrentPalette();
	IlvPalette* dashPal = _lineDashCombo->getCurrentPalette();
	IlvPalette* result =
		getDisplay()->getPalette(colorPal->getBackground(),
					 colorPal->getForeground(),
					 colorPal->getPattern(),
					 colorPal->getColorPattern(),
					 colorPal->getFont(),
					 dashPal->getLineStyle(),
					 linePal->getLineWidth(),
					 colorPal->getFillStyle(),
					 colorPal->getArcMode(),
					 colorPal->getFillRule());
	if (result) {
	    result->lock();
	}
	return result;
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvPalette*
PaletteEditor::getFillPalette() const
{
    if (_fillEdit && _fillColorCombo) {
	return _fillColorCombo->getCurrentPalette();
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvBitmap*
PaletteEditor::getMarkerBitmap() const
{
    if (_pointEdit && _pointSymbolCombo) {
	return _pointSymbolCombo->getCurrentMarkerBitmap();
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvMarkerType
PaletteEditor::getMarkerType() const
{
    if (_pointEdit && _pointSymbolCombo) {
	return _pointSymbolCombo->getCurrentMarker();
    }
    return 0;
}

// --------------------------------------------------------------------------
IlInt
PaletteEditor::getMarkerSize() const
{
    if (_pointEdit && _pointSymbolCombo) {
	return _pointSymbolCombo->getMarkerSize();
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvColor*
PaletteEditor::getMarkerColor() const
{
    if (_pointEdit && _pointSymbolCombo)
	return _pointSymbolCombo->getMarkerColor();
    return 0;
}

// --------------------------------------------------------------------------
void
PaletteEditor::changeSensitivity()
{
    if (!_fillColorLabel) {
	return;
    }
    // process fill style fields
    if (_fillEdit) {
	if (!_fillColorLabel->isSensitive()) {
	    _fillColorLabel->setSensitive(IlTrue);
	}
	if (!_fillColorCombo->isSensitive()) {
	    _fillColorCombo->setSensitive(IlTrue);
	}
    }
    else {
	if (_fillColorLabel->isSensitive()) {
	    _fillColorLabel->setSensitive(IlFalse);
	}
	if (_fillColorCombo->isSensitive()) {
	    _fillColorCombo->setSensitive(IlFalse);
	}
    }
    // process line style fields
    if (_lineEdit) {
	if (!_lineColorLabel->isSensitive()) {
	    _lineColorLabel->setSensitive(IlTrue);
	}
	if (!_lineColorCombo->isSensitive()) {
	    _lineColorCombo->setSensitive(IlTrue);
	}
	if (!_lineThicknessLabel->isSensitive()) {
	    _lineThicknessLabel->setSensitive(IlTrue);
	}
	if (!_lineThicknessCombo->isSensitive()) {
	    _lineThicknessCombo->setSensitive(IlTrue);
	}
	if (!_lineDashLabel->isSensitive()) {
	    _lineDashLabel->setSensitive(IlTrue);
	}
	if (!_lineDashCombo->isSensitive()) {
	    _lineDashCombo->setSensitive(IlTrue);
	}
    }
    else {
	if (_lineColorLabel->isSensitive()) {
	    _lineColorLabel->setSensitive(IlFalse);
	}
	if (_lineColorCombo->isSensitive()) {
	    _lineColorCombo->setSensitive(IlFalse);
	}
	if (_lineThicknessLabel->isSensitive()) {
	    _lineThicknessLabel->setSensitive(IlFalse);
	}
	if (_lineThicknessCombo->isSensitive()) {
	    _lineThicknessCombo->setSensitive(IlFalse);
	}
	if (_lineDashLabel->isSensitive()) {
	    _lineDashLabel->setSensitive(IlFalse);
	}
	if (_lineDashCombo->isSensitive()) {
	    _lineDashCombo->setSensitive(IlFalse);
	}
    }
    // process point style fields
    if (_pointEdit) {
	if (!_pointSymbolLabel->isSensitive()) {
	    _pointSymbolLabel->setSensitive(IlTrue);
	}
	if (!_pointSymbolCombo->isSensitive()) {
	    _pointSymbolCombo->setSensitive(IlTrue);
	}
    }
    else {
	if (_pointSymbolLabel->isSensitive()) {
	    _pointSymbolLabel->setSensitive(IlFalse);
	}
	if (_pointSymbolCombo->isSensitive()) {
	    _pointSymbolCombo->setSensitive(IlFalse);
	}
    }
}

// --------------------------------------------------------------------------
IlvView*
PaletteEditor::createView(IlvAbstractView* parent, const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent, rect);
    IlvGadgetContainer* container = (IlvGadgetContainer*)view;
    IlvDisplay* display = parent->getDisplay();
    IlvLabel dummy(display, IlvPoint(0, 0), "Dummy|");
    IlInt labelAlignment = 10;
    IlInt labelWidth = 70;
    IlInt labelHeight = dummy.h();
    IlInt comboHeight = labelHeight * 2 - 2;
    IlInt comboWidth = comboHeight * 5;
    IlInt verticalSpacing = 20;
    IlvColor* fg = display->getColor("maroon");
    //------------------------------------------
    // Create the label for 'fill style'
    //------------------------------------------
    IlvFrame* fillLabel = new IlvFrame(display, "Area",
				       IlvRect(5, 2, 250, 60));
    fillLabel->setForeground(fg);
    container->addObject(fillLabel);
    //---------------------------------------------
    // Create the color editor for the fill style
    //---------------------------------------------
    IlvRect fillColorRect(labelAlignment + labelWidth + 10,
			  fillLabel->y() + verticalSpacing,
			  comboWidth,
			  comboHeight);
    _fillColorCombo = new ColorEditor(display, fillColorRect, IlTrue);
    container->addObject(_fillColorCombo);
    _fillColorLabel = new IlvLabel(display,
				   IlvPoint(labelAlignment,
					    (IlvPos)
					    (fillColorRect.y()
					     + fillColorRect.h() / 1.5)),
				   "Color:");
    container->addObject(_fillColorLabel);
    //------------------------------------------
    // Create the label for 'fill style'
    //------------------------------------------
    IlvFrame* lineLabel = new IlvFrame(display, "Line or stroke",
				       IlvRect(5,
					       fillColorRect.y()
					       + fillColorRect.h()
					       + verticalSpacing - 2,
					       250, 160));
    lineLabel->setForeground(fg);
    container->addObject(lineLabel);
    //---------------------------------------------
    // Create the color editor for the line style
    //---------------------------------------------
    IlvRect lineColorRect(labelAlignment + labelWidth + 10,
			  lineLabel->y() + verticalSpacing,
			  comboWidth,
			  comboHeight);
    _lineColorCombo = new ColorEditor(display, lineColorRect, IlFalse);
    container->addObject(_lineColorCombo);
    _lineColorLabel = new IlvLabel(display, IlvPoint(0, 0), "Color:");
    _lineColorLabel->move(labelAlignment, lineColorRect.y() +
			  (lineColorRect.h() - _lineColorLabel->h()) / 2);
    container->addObject(_lineColorLabel);
    //----------------------------------------------
    // Create the line thickness editor
    //----------------------------------------------
    IlvRect lineThicknessRect(labelAlignment + labelWidth + 10,
			      lineColorRect.y()
			      + lineColorRect.h() + verticalSpacing,
			      comboWidth,
			      comboHeight);
    
    _lineThicknessCombo = new LineEditor(display,lineThicknessRect);
    container->addObject(_lineThicknessCombo);
    container->getHolder()->attach(_lineThicknessCombo, IlvHorizontal,
				   0, 0, 1);
    container->getHolder()->attach(_lineThicknessCombo, IlvVertical,
				   0, 0, 1);
    _lineThicknessLabel = new IlvLabel(display, IlvPoint(0, 0),
				       "Thickness:");
    _lineThicknessLabel->move(labelAlignment,
			      lineThicknessRect.y()
			      + (lineThicknessRect.h()
				 - _lineThicknessLabel->h()) / 2);
    container->addObject(_lineThicknessLabel);
    //----------------------------------------------
    // Create the line dash editor
    //----------------------------------------------
    IlvRect lineDashRect(labelAlignment + labelWidth + 10,
			 lineThicknessRect.y()
			 + lineThicknessRect.h() + verticalSpacing,
			 comboWidth, comboHeight);
    _lineDashCombo = new DashEditor(display,lineDashRect);
    container->addObject(_lineDashCombo);
    _lineDashLabel = new IlvLabel(display, IlvPoint(0, 0), "Dash:");
    _lineDashLabel->move(labelAlignment,
			 lineDashRect.y() +
			 (lineDashRect.h()-_lineDashLabel->h()) / 2);
    container->addObject(_lineDashLabel);
    //------------------------------------------
    // Create the label for 'point style'
    //------------------------------------------
    IlvRect lineLabelRect;
    lineLabel->boundingBox(lineLabelRect);
    IlvFrame* pointLabel = new IlvFrame(display,
					"Point",
					IlvRect(5,
						lineLabelRect.y()
						+ lineLabelRect.h()
						+ verticalSpacing - 17,
						250, 60));
    pointLabel->setForeground(fg);
    container->addObject(pointLabel);
    //------------------------------------------
    // Create the combo for 'point style'
    //------------------------------------------
    IlvRect pointSymbolRect(labelAlignment + labelWidth + 10,
			    pointLabel->y() + verticalSpacing,
			    comboWidth, comboHeight);
    
    _pointSymbolCombo = new PointEditor(display, pointSymbolRect, IlTrue);
    container->addObject(_pointSymbolCombo);
    _pointSymbolLabel = new IlvLabel(display, IlvPoint(0, 0), "Symbol:");
    _pointSymbolLabel->move(labelAlignment,
			    pointSymbolRect.y() +
			    (pointSymbolRect.h()-_pointSymbolLabel->h())/2);
    container->addObject(_pointSymbolLabel);
    //-----------------------------------------
    // Antialiasing and transparency (only with gdi+)
    //-----------------------------------------
    IlvFrame* aspectFrame = new IlvFrame(display,
					 "Aspect",
					 IlvRect(260, 2, 200, 120));
    aspectFrame->setForeground(fg);
    container->addObject(aspectFrame);
    IlvToggle* antialias = new IlvToggle(display, "Antialiasing",
					 IlvRect(275, 42, 150, 40));
    antialias->setName("antialias");
    container->addObject(antialias);
    IlvLabel* transLab = new IlvLabel(display, IlvPoint(275, 95),
				      "Transparency");
    container->addObject(transLab);
    IlvSlider* slider = new IlvSlider(display, IlvRect(375, 82, 60, 20));
    slider->setName("transparency");
    slider->setValue(0);
    container->addObject(slider);
#if !defined(WINDOWS)
    antialias->setSensitive(IlFalse);
    slider->setSensitive(IlFalse);
#endif
    IlvToggle* save = new IlvToggle(display, "Save rendering attributes",
				    IlvRect(275, 150, 180, 40));
    save->setName("saverendering");
    save->setState(IlTrue);
    container->addObject(save);    
    // Change sensitivity of application
    changeSensitivity();    
    return view;
}

// --------------------------------------------------------------------------
IlvAntialiasingMode
PaletteEditor::getAntialiasingMode() const
{
    IlvGraphic* g = getContainer()->getObject("antialias");
    if (!g) {
	return IlvDefaultAntialiasingMode;
    }
    IlBoolean state = ((IlvToggle*)g)->getState();
    if (state) {
	return IlvUseAntialiasingMode;
    }
    else {
	return IlvDefaultAntialiasingMode;
    }
}

// --------------------------------------------------------------------------
IlDouble
PaletteEditor::getTransparency() const
{
    IlvGraphic* g = getContainer()->getObject("transparency");
    if (!g) {
	return (IlDouble)0;
    }
    return ((IlDouble)((IlvSlider*)g)->getValue()) / (IlDouble)100;
}








