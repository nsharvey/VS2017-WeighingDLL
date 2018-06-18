// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/fontcomb.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliFontComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Fontcomb_H
#define __Ili_Fontcomb_H

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

typedef void (*IliOnInitDialogHook)(IlvDialog*);

class ILV_DBG_EXPORTED IliFontComboBox : public IliDialogComboBox
{
public:
    IliFontComboBox(IlvDisplay* display,
		    const char* title,
		    const IlvRect& rect,
		    IlUShort thickness = IlvDefaultGadgetThickness,
		    IlvPalette* palette = 0);

    IlvFont*		getFontValue() const;
    void		setFontValue(IlvFont*);

    // -- overrides IlvGadget
    DeclareTypeInfo();
    DeclareIOConstructors(IliFontComboBox);

    // -- overrides IliDialogComboBox
    virtual void	onOpen();
    virtual void	onApply();

    static void		SetOnInitDialogHook(IliOnInitDialogHook);

protected:
    IliString			_dialogTitle;
    static IliOnInitDialogHook	_OnInitDialogHook;

    virtual void	onInitDialog();
    virtual void	showDialog(IlBoolean grab);
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliFontComboBox);

#endif
