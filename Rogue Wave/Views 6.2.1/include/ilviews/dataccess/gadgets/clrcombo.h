// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/clrcombo.h
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
// Declaration of the IliColorComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Clrcombo_H
#define __Ili_Clrcombo_H

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

class ILV_DBG_EXPORTED IliColorComboBox : public IliDialogComboBox
{
public:
    IliColorComboBox(IlvDisplay* display,
		     const char* dialogTitle,
		     const IlvRect& rect,
		     IlUShort thickness = IlvDefaultGadgetThickness,
		     IlvPalette* palette = 0);

    IlvColor*		getColor() const;
    void		setColor(IlvColor*);

    // -- overrides IlvGadget

    DeclareTypeInfo();
    DeclareIOConstructors(IliColorComboBox);

    // -- overrides IliDialogComboBox

    virtual void	onOpen();
    virtual void	onApply();

protected:
    IliString		_dialogTitle;

    virtual void	onInitDialog();
    virtual void	showDialog(IlBoolean grab);
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliColorComboBox);

#endif
