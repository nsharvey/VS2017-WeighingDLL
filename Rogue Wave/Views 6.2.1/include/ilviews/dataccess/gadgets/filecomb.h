// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/filecomb.h
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
// Declaration of the IliFileNameComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Filecomb_H
#define __Ili_Filecomb_H

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

#define USE_FILE_BROWSER

#ifdef USE_FILE_BROWSER
#  include <ilviews/gadgets/fbrowser.h>
#endif

class ILV_DBG_EXPORTED IliFileNameComboBox : public IliDialogComboBox
{
public:
    IliFileNameComboBox(IlvDisplay* display,
			const char* title,
			const IlvRect&,
			IlUShort thickness = IlvDefaultGadgetThickness,
			IlvPalette* palette = 0);
    ~IliFileNameComboBox();

    const char*		getDirectory() const;
    void		setDirectory(const char*);

    const char*		getFilter() const;
    void		setFilter(const char*);

    // -- overrides IlvGadget
    DeclareTypeInfo();
    DeclareIOConstructors(IliFileNameComboBox);

    // -- overrides IliDialogComboBox
    virtual void	onOpen();
    virtual void	onApply();
    virtual void	close();

    virtual IlBoolean	wasCanceled() const;

protected:
    IliString		_dialogTitle;
    IliString		_directory;
    IliString		_filter;
#ifdef USE_FILE_BROWSER
    IlvFileBrowser*	_fileBrowser;
#endif

    virtual void	onInitDialog();
    virtual void	showDialog(IlBoolean grab);
    virtual IlBoolean	hasDialog() const;
    virtual void	centerDialogInView(IlvAbstractView* view);
    virtual void	moveDialogTo(const IlvPoint& where);
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliFileNameComboBox);

#endif
