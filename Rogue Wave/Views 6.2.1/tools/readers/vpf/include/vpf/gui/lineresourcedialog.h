// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/lineresourcedialog.h
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
// Declaration of the LineResourceDialog class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_LINERESOURCEDIALOG_H
#define VPF_GUI_LINERESOURCEDIALOG_H

#include <vpf/gui/resourcedialog.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/graphics/line.h>

// --------------------------------------------------------------------------
class LineResourceDialog
: public ResourceDialog {
public:
    LineResourceDialog(IlvDisplay*,
		       const char* resourceName,
		       Palette* resourcePalette);
    ~LineResourceDialog();
    // ____________________________________________________________
    void lineColor();
    void lineStyle();
    void lineWidth();
    void apply();

    static void LineColorCB(IlvGraphic*, IlvAny);
    static void LineStyleCB(IlvGraphic*, IlvAny);
    static void LineWidthCB(IlvGraphic*, IlvAny);
protected:
    void setPaletteForeground(IlvColor*);
    void setPaletteLineStyle(IlvLineStyle*);
    void setPaletteLineWidth(unsigned int i);

    IlvLine*			_line;
    IlvScrolledComboBox*	_width;
    IlvScrolledComboBox*	_style;
};

#endif /* VPF_GUI_LINERESOURCEDIALOG_H */
