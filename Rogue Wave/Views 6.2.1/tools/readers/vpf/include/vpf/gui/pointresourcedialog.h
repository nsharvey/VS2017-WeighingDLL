// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/pointresourcedialog.h
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
// Declaration of the PointResourceDialog class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_POINTRESOURCEDIALOG_H
#define VPF_GUI_POINTRESOURCEDIALOG_H

#include <vpf/gui/resourcedialog.h>

class IlvOptionMenu;
class IlvMarker;
class IlvSpinBox;

// --------------------------------------------------------------------------
class PointResourceDialog
: public ResourceDialog {
public:
    PointResourceDialog(IlvDisplay*,
			const char*	resourceName,
			Palette*	resourcePalette);
    ~PointResourceDialog();
    // ____________________________________________________________
    void pointColor();
    void pointSize();
    void pointStyle();
    void apply();

    static void PointColorCB(IlvGraphic*, IlvAny);
    static void PointSizeCB(IlvGraphic*, IlvAny);
    static void PointStyleCB(IlvGraphic*, IlvAny);
protected:
    void setPaletteForeground(IlvColor*);
    void setPaletteStyle(IlvMarkerType);
    void setPaletteSize(IlUShort);

    IlvMarker*		_marker;
    IlvSpinBox*	_size;
    IlvOptionMenu*	_style;
};

#endif /* VPF_GUI_POINTRESOURCEDIALOG_H */
