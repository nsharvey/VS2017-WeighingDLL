// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/selecwin.h
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
// Declaration of the IlvDvSelectWindowDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Selecwin_H)
#define __Ilv_Appframe_Selecwin_H

#if !defined(__Ilv_Appframe_Dialog_Dialog_H)
#include <ilviews/appframe/dialog/dialog.h>
#endif

class IlvStringList;
class IlvDvDockableMainWindow;
class IlvViewFrame;
// --------------------------------------------------------------------------
// IlvDvSelectWindowDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvSelectWindowDialog : public IlvDvDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvSelectWindowDialog(IlvDisplay*,
			    IlvDvDockableMainWindow* mainWindow,
			    IlvSystemView transientFor = 0);

    virtual ~IlvDvSelectWindowDialog();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void initialize();

protected:
    IlvDvDockableMainWindow*	_mainWindow;
    IlvStringList*		_windowsList;

    const char*			getTitle(IlvViewFrame* frame) const;

    void			activateWindow();
    void			saveWindow();
    void			closeWindow();
    void			newSelectedWindow();

public:
    static void			ActivateWindowCallback(IlvGraphic*, IlAny);
    static void			CloseWindowCallback(IlvGraphic*, IlAny);
    static void			SaveWindowCallback(IlvGraphic*, IlAny);
    static void			CloseCallback(IlvGraphic*, IlAny);
    static void			SelectionChangeCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(selecwin);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Selecwin_H */
