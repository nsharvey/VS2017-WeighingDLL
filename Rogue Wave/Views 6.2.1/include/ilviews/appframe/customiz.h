// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/customiz.h
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
// Declaration of the IlvDvCustomizeDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Customiz_H)
#define __Ilv_Appframe_Customiz_H

#if !defined(__Ilv_Appframe_Dialog_Dialog_H)
#include <ilviews/appframe/dialog/dialog.h>
#endif
class IlvDvSortedCommandsInspector;
class IlvDvDockableMainWindow;
#if !defined(__Ilv_Appframe_Dialog_Dlgassoc_H)
#include <ilviews/appframe/dialog/dlgassoc.h>
#endif

// --------------------------------------------------------------------------
// IlvDvMainMenuAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMainMenuAssoc : public IlvDvDialogAssoc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvMainMenuAssoc(IlvDvDialogAssoc* optionsAssoc,
		       IlvDvOptions* allOptions);
    ~IlvDvMainMenuAssoc();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initialize();
    virtual
    IlvDvNodeValue*	getChildDataVariable() const;

protected:
    IlvDvOptions*	_allOptions;
    IlvDvNodeValue*	_dataVariable;
};

// --------------------------------------------------------------------------
// IlvDvCustomizeDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvCustomizeDialog : public IlvDvPropertySheet
{
    IlvDeclareClassInfo();

public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvCustomizeDialog(IlvDvDockableMainWindow* mainWindow,
			 IlvSystemView transientFor = 0);
    virtual ~IlvDvCustomizeDialog();

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_CustomizeDialogProperty;
    static IlSymbol*	_SorterTypeSymbol;
    static IlSymbol*	_BarActiveDocumentSymbol;
    static const char*	_UserDefinedColor;
    static const char*	_DocItemsColor;

protected:
    IlvPalette*		_userDefinedPalette;
    IlvPalette*		_docItemsPalette;
    IlvDvOptions*	_allOptions;
    IlvDvDockableMainWindow* _mainWindow;
    IlvDvDialogAssoc*	_optionsAssoc;
    IlvDvDialogAssoc*	_mainMenuAssoc;
    IlvBitmap*		_eyeBmp;

    void internalInitialize();
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(customiz);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Customiz_H */
