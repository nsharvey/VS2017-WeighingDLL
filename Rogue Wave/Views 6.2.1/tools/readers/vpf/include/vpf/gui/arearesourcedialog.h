// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/arearesourcedialog.h
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
// Declaration of the AreaResourceDialog class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_AREARESOURCEDIALOG_H
#define VPF_GUI_AREARESOURCEDIALOG_H

#include <vpf/gui/resourcedialog.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/scombo.h>

// --------------------------------------------------------------------------
class AreaResourceDialog
: public ResourceDialog {
public:
    AreaResourceDialog(IlvDisplay*,
		       const char*	resourceName,
		       Palette*		resourcePalette);
    ~AreaResourceDialog();
    // ____________________________________________________________
    void faceColor();
    void facePattern();
    void apply();

    static void FaceColorCB(IlvGraphic*, IlvAny);
    static void FacePatternCB(IlvGraphic*, IlvAny);
protected:
    void setPaletteForeground(IlvColor*);
    void setPalettePattern(IlvPattern*);
    IlvFilledRectangle* _foregroundRect;
    IlvFilledRectangle* _patternRect;
    IlvScrolledComboBox* _combo;
};

#endif /* VPF_GUI_AREARESOURCEDIALOG_H */
