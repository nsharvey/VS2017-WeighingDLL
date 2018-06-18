// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/textresourcedialog.h
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
// Declaration of the TextResourceDialog class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_TEXTRESOURCEDIALOG_H
#define VPF_GUI_TEXTRESOURCEDIALOG_H

#include <vpf/gui/resourcedialog.h>

class IlvLabel;

// --------------------------------------------------------------------------
class TextResourceDialog
: public ResourceDialog {
public:
    TextResourceDialog(IlvDisplay*,
		       const char*	resourceName,
		       Palette*		resourcePalette);
    ~TextResourceDialog();
    // ____________________________________________________________
    void textColor();
    void textStyle();
    void apply();

    static void TextColorCB(IlvGraphic*, IlvAny);
    static void TextStyleCB(IlvGraphic*, IlvAny);
protected:
    void setPaletteForeground(IlvColor*);
    void setPaletteStyle(IlvFont*);

    IlvLabel*	_text;
};

#endif /* VPF_GUI_TEXTRESOURCEDIALOG_H */

