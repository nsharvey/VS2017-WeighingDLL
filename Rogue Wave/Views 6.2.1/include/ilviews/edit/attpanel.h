// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/attpanel.h
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
// Declaration of the IlvAttachPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Attpanel_H
#define __Ilv_Edit_Attpanel_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif

class ILVVWSEXPORTED IlvManager;
class ILVGDTEXPORTED IlvPopupMenu;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvAttachPanel
    : public IlvDialog {
 public:
    IlvAttachPanel(IlvManager*,
		   IlvSystemView transientFor = 0);
    ~IlvAttachPanel();
    // ____________________________________________________________
    IlvManager*  getManager() const { return _manager; }
    void         setManager(IlvManager* mgr) { _manager = mgr; }
    void         reset(IlvGraphic* obj = 0);
    virtual void apply();
    virtual void show();
 protected:
    IlvManager*              _manager;
 public:
    IlvPopupMenu*            _smenu;
    IlvPopupMenu*            _menu;
    IlvGraphic*              _vertical;
    IlvGraphic*              _horizontal;
    IlvGraphic*              _left;
    IlvGraphic*              _right;
    IlvGraphic*              _top;
    IlvGraphic*              _bottom;
    IlvGraphic*              _width;
    IlvGraphic*              _height;
    IlvGraphic*              _fixleft;
    IlvGraphic*              _fixright;
    IlvGraphic*              _fixtop;
    IlvGraphic*              _fixbottom;
    IlvGraphicAttachment     _lefta;
    IlvGraphicAttachment     _righta;
    IlvGraphicAttachment     _topa;
    IlvGraphicAttachment     _bottoma;
    IlvGraphicAttachment     _widtha;
    IlvGraphicAttachment     _heighta;
    IlvViewObjectInteractor* _move;
    void setLeft(IlvGraphicAttachment,
		 IlBoolean redraw = IlTrue);
    void setRight(IlvGraphicAttachment,
		  IlBoolean redraw = IlTrue);
    void setTop(IlvGraphicAttachment,
		IlBoolean redraw = IlTrue);
    void setBottom(IlvGraphicAttachment,
		   IlBoolean redraw = IlTrue);
    void setWidth(IlvGraphicAttachment,
		  IlBoolean redraw = IlTrue);
    void setHeight(IlvGraphicAttachment,
		   IlBoolean redraw = IlTrue);
};

#endif /*  ! __Ilv_Edit_Attpanel_H */
