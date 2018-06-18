// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/resourcedialog.h
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
// Declaration of the ResourceDialog class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_RESOURCEDIALOG_H
#define VPF_GUI_RESOURCEDIALOG_H

#include <ilviews/gadgets/idialog.h>
#include <vpf/gui/palette.h>

// --------------------------------------------------------------------------
class ResourceDialog
: public IlvDialog
{
public:
    ResourceDialog(IlvDisplay*,
		   const char* file,
		   const char* resourceName,
		   Palette* resourcePalette);
    ~ResourceDialog();
    // ____________________________________________________________
    Palette* getPalette() const { return _palette; };
protected:
    Palette* _palette;
    static void DialogClosedCB(IlvView*, IlvAny);
};

#endif /* VPF_GUI_RESOURCEDIALOG_H */
