// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/mblink.h
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
// Declaration of the IlvMakeMBLinkInteractor class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Mblink_H
#define __Ilv_Edit_Mblink_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class ILVGDTEXPORTED IlvAbstractBar;
class ILVGDTEXPORTED IlvPopupMenu;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvMakeMBLinkInteractor
    : public IlvManagerViewInteractor {
public:
    IlvMakeMBLinkInteractor(IlvManager* mgr,
			    IlvView* v)
	: IlvManagerViewInteractor(mgr, v),
        _menubar(0),
	_popup(0),
	_otherPopup(0),
	_graphic(0)
	    {}
    IlvMakeMBLinkInteractor()
	: IlvManagerViewInteractor(),
        _menubar(0),
	_popup(0),
	_otherPopup(0),
	_graphic(0)
	    {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void abort() ;
    virtual void init() ;
    virtual void drawGhost();
    virtual void doIt(IlvAbstractBar* mb,
		      IlvPopupMenu* popup,
		      IlShort item);
    virtual void doIt(IlvPopupMenu*,
		      IlvPopupMenu* popup,
		      IlShort item);
    virtual void doIt(IlvAbstractBar*,
		      IlvGraphic* obj,
		      IlShort item);
    virtual void doIt(IlvPopupMenu*,
		      IlvGraphic* obj,
		      IlShort item);
protected:
    IlvAbstractBar*   _menubar;
    IlvPopupMenu* _popup;
    IlvPopupMenu* _otherPopup;
    IlvGraphic*   _graphic;
    IlvPoint      _prev;
    IlvPoint      _first;
    IlShort      _item;
};

#endif /* !__Ilv_Edit_Mblink_H */
