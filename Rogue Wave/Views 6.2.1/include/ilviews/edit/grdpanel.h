// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/grdpanel.h
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
// Declaration of the IlvGridPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Grdpanel_H
#define __Ilv_Edit_Grdpanel_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Manager_grid_H)
#include <ilviews/manager/grid.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Filesel_H)
#include <ilviews/gadgets/filesel.h>
#endif
#if !defined(__Ilv_Gadgets_Slider_H)
#include <ilviews/gadgets/slider.h>
#endif
#if !defined(__Ilv_Gadgets_Colorch_H)
#include <ilviews/gadgets/colorch.h>
#endif

class ILVVWSEXPORTED IlvManager;
class ILVEDTEXPORTED IlvWindowBackgroundSelector;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvGridPanel
: public IlvDialog {
public:
    IlvGridPanel(IlvManager*, IlvView*, IlvSystemView transientFor = 0);
    ~IlvGridPanel();
    // ____________________________________________________________
    IlvManager*     getManager() const { return _manager; }
    void            setManager(IlvManager* mgr, IlvView* view);
    IlvManagerGrid* getGrid() const { return _grid; }
    IlvView*        getView() const { return _view; }
    void            setView(IlvView*);
    virtual void    apply();
    virtual void    hide();
    void            selectBackground();
    void            selectBackgroundBitmap(const char*);
    void            adjustBackground();
protected:
    IlvManager*                  _manager;
    IlvView*                     _view;
    IlvManagerGrid*              _grid;
    IlvWindowBackgroundSelector* _bgSelector;
};

#endif /* !__Ilv_EditGrdpanel_H */
