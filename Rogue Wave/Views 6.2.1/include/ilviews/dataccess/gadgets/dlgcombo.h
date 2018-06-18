// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dlgcombo.h
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
// Declaration of the IliDialogComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dlgcombo_H
#define __Ili_Dlgcombo_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ili_Abscombo_H
#  include <ilviews/dataccess/gadgets/abscombo.h>
#endif

class ILV_DBG_EXPORTED IliDialogComboBox : public IliAbstractComboBox
{
public:
    virtual ~IliDialogComboBox();
    virtual void	onApply();

    virtual void	open(IlBoolean grab);
    virtual void	openAt(const IlvPoint& where, IlBoolean grab);
    virtual void	close();
    virtual IlBoolean	isOpen() const;

    virtual IlBoolean	wasCanceled() const;

    virtual IlBoolean	f_opensADialog() const;

    // -- symbols

    static IlvSymbol*	ApplySymbol();

    // -- overrides IlvGadget

    DeclareTypeInfo();
    DeclareIOConstructors(IliDialogComboBox);

    virtual IlUInt	getCallbackTypes(const char* const**      names,
					 const IlvSymbol* const** types) const;

protected:
    IlBoolean		_isOpen;
    IlBoolean		_dialogOwner;

    IlvDialog*		_dialog;
    IliDialogComboBox(IlvDisplay* display,
		      const IlvRect& rect,
		      IlUShort thickness = IlvDefaultGadgetThickness,
		      IlvPalette* palette = 0);
    IlvDialog*		getDialog() const;
    void		setDialog(IlvDialog* dlg, IlBoolean owner = IlTrue);

    virtual IlBoolean	mustInvertArrowRect() const;
    virtual void	drawArrow(IlvPort* dst,
				  const IlvRect& bbox,
				  const IlvRegion* clip) const;
    virtual void	doOpen(IlBoolean grab);
    virtual void	showDialog(IlBoolean grab);
    virtual IlBoolean	hasDialog() const;
    virtual void	centerDialogInView(IlvAbstractView* view);
    virtual void	moveDialogTo(const IlvPoint& where);
    virtual void	onInitDialog();
    virtual void	onEndDialog();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDialogComboBox);

#endif



