// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/lineeditor.h
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
// Declaration of the LineEditor class
// -------------------------------------------------------------------------
#ifndef _LineEditor_h_
#define _LineEditor_h_

#include <ilviews/gadgets/rectgadc.h>

class IlvGadgetContainerRectangle;
class IlvComboBox;

// -------------------------------------------------------------------------
class LineEditor
    : public IlvGadgetContainerRectangle
{
public:
    LineEditor(IlvDisplay* display,
		const IlvRect& rect);
    virtual ~LineEditor();

    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    IlvPalette* getCurrentPalette();

    void setSensitive(IlBoolean set);

    IlvComboBox* getColorCombo() const
	{ return _colorCombo; }
    void setCurrentSelection(IlInt selection)
	{ _currentSelection = selection; }
private:
    void createStandardStyleItems(const IlvRect& size);
    void addStdStyleItem(IlvSimpleGraphic* preview);

    IlvComboBox* _colorCombo;
    IlInt _currentSelection;
    IlvRect _previewsize;
};
#endif
