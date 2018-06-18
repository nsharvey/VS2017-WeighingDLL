// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/strcombo.h
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
// Declaration of the IliStringsComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Strcombo_H
#define __Ili_Strcombo_H

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

#ifndef __Ili_Strdlg_H
#  include <ilviews/dataccess/dialogs/strdlg.h>
#endif

class ILV_DBG_EXPORTED IliStringsComboBox : public IliDialogComboBox
{
public:
    IliStringsComboBox(IlvDisplay* display,
		       const char* title,
		       const IlvRect&,
		       IlUShort thickness = IlvDefaultGadgetThickness,
		       IlvPalette* palette = 0);

    const IliStringsTable* getStringsTable() const { return _strings; }
    IliStringsTable*	getStringsTable() { return _strings; }

    // -- overrides IlvGadget

    DeclareTypeInfo();
    DeclareIOConstructors(IliStringsComboBox);

    // -- overrides IliDialogComboBox

    virtual void	onOpen();
    virtual void	onApply();

protected:
    IliStringsTable*	_strings;
    IliString		_dialogTitle;

    virtual void	onInitDialog();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliStringsComboBox);

#endif
