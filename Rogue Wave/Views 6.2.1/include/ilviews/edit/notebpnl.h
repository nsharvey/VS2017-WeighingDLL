// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/notebpnl.h
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
// Declaration of the IlvNotebookPanel class
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Notebpnl_H
#define __Ilv_Edit_Notebpnl_H

#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Scombo_H)
#include <ilviews/gadgets/scombo.h>
#endif

class IlvColorSelector;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvNotebookPanel
: public IlvInspectorPanel
{
public:
    IlvNotebookPanel(IlvManager*, IlvSystemView transientFor = 0);
    virtual ~IlvNotebookPanel();
    // ____________________________________________________________
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
    IlvNotebook* getBook() const ;
    IlvGadgetContainer * getPage2() const
       { return (IlvGadgetContainer*)getBook()->getPages()[1]->getView(); }
    IlvGadgetContainer * getPage1() const
       { return (IlvGadgetContainer*)getBook()->getPages()[0]->getView(); }
    IlvTextField * getTabLabel() const;
    IlvTextField * getTabBitmap() const;
    IlvTextField * getTabFilename() const;
    IlvToggle * getTabTransparent() const;
    IlvToggle * getTabSensitive() const;
    IlvGraphic * getTabColor() const;
    IlvOptionMenu * getTabsPosition() const;
    IlvToggle * getTabsVertical() const;
    IlvToggle * getFlipLabels() const;
    IlvNumberField * getTabVMargin() const;
    IlvNumberField * getTabHMargin() const;
    IlvNumberField * getLeftMargin() const;
    IlvNumberField * getRightMargin() const;
    IlvNumberField * getTopMargin() const;
    IlvNumberField * getBottomMargin() const;
    IlvScrolledComboBox * getType() const;
    IlvStringList * getTabList() const;
    void bgSelectorDeleted() { _background = 0; }
    IlvNotebook* getEditedBook() const { return _book;}
    IlvColorSelector * getBackgroundPanel() const { return _background;}
protected:
    IlvNotebook*       _book;
    IlvColorSelector*  _background;

};

#endif /*  ! __Ilv_Edit_Notebpnl_H */
